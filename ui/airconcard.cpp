#include "airconcard.h"
#include "airconpage.h"
#include "di/mainmodule.h"
#include "ui_airconcard.h"

AirconCard::AirconCard(const DeviceData *initData, QWidget *parent)
    : DeviceCard(initData, parent)
    , ui(new Ui::AirconCard)
    , model(AirconModel(initData))
{
    ui->setupUi(this);
    updateUi();

    id = initData->info()->id();
    connect(ui->btnPower, &QPushButton::clicked, [&] {
        mainModule->deviceRepository()->send(id,
                                             model.power ? model.powerOffCommand()
                                                         : model.powerOnCommand());
    });
}

AirconCard::~AirconCard()
{
    delete ui;
}

void AirconCard::updateUi()
{
    const static QPixmap flake = QPixmap(":/drawables/flake.png");
    const static QPixmap sun = QPixmap(":/drawables/sun.png");

    ui->lblName->setText(model.name);
    ui->lblTgtTemp->setText(QString::number(model.tgtTemp) + "°C");
    ui->btnPower->setText(model.power ? "Running" : "Stopped");
    ui->lblMode->setPixmap(model.mode == "cool" ? flake : sun);
    ui->lblTemp->setText(model.temp);
}

void AirconCard::onDataUpdate(const DeviceData *data)
{
    model = AirconModel(data);
    updateUi();
    if (page != nullptr) {
        page->onModelUpdate(model);
    }
}

void AirconCard::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    page = new AirconPage(id, model);
    connect(page, &AirconPage::close, [&] {
        page->deleteLater();
        page = nullptr;
    });

    page->show();
}
