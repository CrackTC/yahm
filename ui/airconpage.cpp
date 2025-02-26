#include <QInputDialog>

#include "airconpage.h"
#include "di/mainmodule.h"
#include "ui_airconpage.h"

AirconPage::AirconPage(int id, const AirconModel model, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AirconPage)
    , id(id)
    , model(model)
{
    ui->setupUi(this);
    updateUi();

    connect(ui->btnMode, &QPushButton::clicked, [&] {
        mainModule->deviceRepository()->send(this->id, this->model.setModeCommand());
    });
    connect(ui->btnPower, &QPushButton::clicked, [&] {
        mainModule->deviceRepository()->send(this->id,
                                             this->model.power ? this->model.powerOffCommand()
                                                         : this->model.powerOnCommand());
    });
    connect(ui->btnTgtTemp, &QPushButton::clicked, [&] {
        bool ok;
        auto tgtTemp = QInputDialog::getInt(this,
                                            "Input",
                                            "Target Temperature",
                                            this->model.tgtTemp,
                                            0,
                                            100,
                                            1,
                                            &ok);
        if (!ok)
            return;
        mainModule->deviceRepository()->send(this->id, this->model.setTgtTempCommand(tgtTemp));
    });
}

AirconPage::~AirconPage()
{
    delete ui;
}

void AirconPage::onModelUpdate(const AirconModel model)
{
    this->model = model;
    updateUi();
}

void AirconPage::updateUi()
{
    ui->lblMode->setText(model.mode);
    ui->lblPower->setText(model.power ? "On" : "Off");
    ui->lblTgtTemp->setText(QString::number(model.tgtTemp) + "°C");
    ui->lblTemp->setText(model.temp);
    ui->lblHumidity->setText(model.humidity);
}
