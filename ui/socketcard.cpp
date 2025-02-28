#include "socketcard.h"
#include "di/mainmodule.h"
#include "ui_socketcard.h"

SocketCard::SocketCard(const DeviceData *data, QWidget *parent)
    : DeviceCard(data, parent)
    , ui(new Ui::SocketCard)
    , id(data->info()->id())
    , model(SocketModel(data))
{
    ui->setupUi(this);
    updateUi();
    connect(ui->btnPower, &QPushButton::clicked, this, [this] {
        mainModule->deviceRepository()->send(this->id,
                                             this->model.power ? this->model.powerOffCommand()
                                                               : this->model.powerOnCommand());
    });
}

SocketCard::~SocketCard()
{
    delete ui;
}

void SocketCard::updateUi()
{
    ui->lblName->setText(model.name);
    ui->lblWatts->setText(QString::number(model.watts) + "W");
    ui->btnPower->setText(model.power ? "Running" : "Stopped");
}

void SocketCard::onDataUpdate(const DeviceData *newData)
{
    model = SocketModel(newData);
    updateUi();
    if (page != nullptr) {
        page->onModelUpdate(model);
    }
};

void SocketCard::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    page = new SocketPage(id, model);
    connect(page, &SocketPage::close, this, [&] {
        page->deleteLater();
        page = nullptr;
    });

    page->show();
}
