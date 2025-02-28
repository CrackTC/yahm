#include <QMessageBox>
#include <QStringList>

#include "di/mainmodule.h"
#include "mainwindow.h"
#include "ui/airconcard.h"
#include "ui/socketcard.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->addWidget(&lblUser);
    ui->statusBar->addWidget(&lblGroup);
    lblUser.setMinimumWidth(100);
    lblGroup.setMinimumWidth(100);

    connect(ui->actionExit, &QAction::triggered, this, [=] { this->close(); });
    connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::logout);
    connect(ui->actionAbout, &QAction::triggered, this, [=] {
        QMessageBox::about(this, "About", "Yet Another Home Monitor v0.1.0");
    });

    connect(mainModule->deviceRepository(),
            &DeviceRepository::attached,
            this,
            &MainWindow::addDevice);
    connect(mainModule->deviceRepository(),
            &DeviceRepository::detached,
            this,
            &MainWindow::removeDevice);
    connect(mainModule->deviceRepository(), &DeviceRepository::message, this, &MainWindow::message);
    connect(mainModule->accountRepository(), &AccountRepository::loggedIn, this, [&] {
        auto session = mainModule->accountRepository()->session();
        lblUser.setText(
            QString("User: %1(%2)").arg(session->user->username).arg(session->user->uid));

        auto groupStrList = QStringList();
        for (auto group : session->groups) {
            groupStrList.append("Groups: "
                                + QString("%1(%2)").arg(group->groupname).arg(group->gid));
        }
        lblGroup.setText(groupStrList.join(','));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    for (auto card : std::as_const(cards)) {
        card->deleteLater();
    }
}

void MainWindow::addDevice(const DeviceMonitor &device)
{
    auto info = device.data()->info();
    devices.insert(info->id(), &device);

    DeviceCard *card = nullptr;

    if (info->type() == "air_conditioner") {
        card = new AirconCard(device.data());
    } else if (info->type() == "socket") {
        card = new SocketCard(device.data());
    } else {
        qDebug() << "unknown device type";
    }

    if (card != nullptr) {
        connect(&device, &DeviceMonitor::updated, card, &DeviceCard::onDataUpdate);
        ui->centralwidget->layout()->addWidget(card);
        cards.insert(info->id(), card);
    }
}

void MainWindow::removeDevice(const int deviceId)
{
    auto device = devices.value(deviceId);
    auto card = cards.value(deviceId);
    if (card != nullptr) {
        cards.remove(deviceId);
        ui->centralwidget->layout()->removeWidget(card);
        card->deleteLater();
    }
    if (device != nullptr) {
        devices.remove(deviceId);
    }
}

void MainWindow::message(const QString &msg)
{
    QMessageBox::warning(this, "Warning", msg);
}

void MainWindow::clear()
{
    for (auto card : std::as_const(cards)) {
        card->deleteLater();
    }
    cards.clear();
    devices.clear();
}
