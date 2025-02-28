#include <QChart>
#include <QDateTimeAxis>
#include <QInputDialog>
#include <QPainter>
#include <QSplineSeries>
#include <QValueAxis>

#include "airconpage.h"
#include "di/mainmodule.h"
#include "ui_airconpage.h"

AirconPage::AirconPage(int id, const AirconModel model, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AirconPage)
    , id(id)
    , model(model)
    , tempView(this)
    , humidityView(this)
{
    ui->setupUi(this);

    ui->rowTemp->addWidget(&this->tempView);
    ui->rowHumidity->addWidget(&this->humidityView);

    auto tempChart = new QChart;
    {
        tempChart->legend()->hide();
        tempChart->setAnimationOptions(QChart::SeriesAnimations);

        auto series = new QSplineSeries;
        tempChart->addSeries(series);

        auto axisX = new QDateTimeAxis;
        axisX->setTickCount(5);
        axisX->setFormat("hh:mm:ss");
        axisX->setTitleText("Time");
        tempChart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        auto axisY = new QValueAxis;
        axisY->setLabelFormat("%f");
        axisY->setTickCount(5);
        axisY->setTitleText("Temperature");
        tempChart->addAxis(axisY, Qt::AlignRight);
        series->attachAxis(axisY);
    }

    auto humidityChart = new QChart;
    {
        humidityChart->legend()->hide();
        humidityChart->setAnimationOptions(QChart::SeriesAnimations);

        auto series = new QSplineSeries;
        humidityChart->addSeries(series);

        auto axisX = new QDateTimeAxis;
        axisX->setTickCount(5);
        axisX->setFormat("hh:mm:ss");
        axisX->setTitleText("Time");
        humidityChart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        auto axisY = new QValueAxis;
        axisY->setLabelFormat("%f");
        axisY->setTickCount(5);
        axisY->setTitleText("Humidity");
        humidityChart->addAxis(axisY, Qt::AlignRight);
        series->attachAxis(axisY);
    }

    this->tempView.setChart(tempChart);
    this->tempView.setRenderHint(QPainter::Antialiasing);

    this->humidityView.setChart(humidityChart);
    this->humidityView.setRenderHint(QPainter::Antialiasing);

    tempChart->setMargins({0, 0, 0, 0});
    humidityChart->setMargins({0, 0, 0, 0});

    updateUi();

    connect(ui->btnMode, &QPushButton::clicked, this, [&] {
        mainModule->deviceRepository()->send(this->id, this->model.setModeCommand());
    });
    connect(ui->btnPower, &QPushButton::clicked, this, [&] {
        mainModule->deviceRepository()->send(this->id,
                                             this->model.power ? this->model.powerOffCommand()
                                                               : this->model.powerOnCommand());
    });
    connect(ui->btnTgtTemp, &QPushButton::clicked, this, [&] {
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

    {
        static qreal min = 100, max = 0;

        auto chart = this->tempView.chart();
        auto series = static_cast<QLineSeries *>(chart->series().at(0));
        auto currentTime = QDateTime::currentMSecsSinceEpoch();
        series->append(currentTime, model.temp);
        chart->axes().at(0)->setRange(QDateTime::fromMSecsSinceEpoch(currentTime - 30000),
                                      QDateTime::fromMSecsSinceEpoch(currentTime));

        min = std::min(min, model.temp);
        max = std::max(max, model.temp);
        chart->axes().at(1)->setRange(min - 1, max + 1);
    }

    {
        static qreal min = 100, max = 0;

        auto chart = this->humidityView.chart();
        auto series = static_cast<QLineSeries *>(chart->series().at(0));
        auto currentTime = QDateTime::currentMSecsSinceEpoch();
        series->append(currentTime, model.humidity);
        chart->axes().at(0)->setRange(QDateTime::fromMSecsSinceEpoch(currentTime - 30000),
                                      QDateTime::fromMSecsSinceEpoch(currentTime));

        min = std::min(min, model.humidity);
        max = std::max(max, model.humidity);
        chart->axes().at(1)->setRange(min - 1, max + 1);
    }
}
