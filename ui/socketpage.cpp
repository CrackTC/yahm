#include "socketpage.h"
#include "di/mainmodule.h"
#include "ui_socketpage.h"

#include <QDateTimeAxis>
#include <QSplineSeries>
#include <QValueAxis>
#include <QPainter>

SocketPage::SocketPage(int id, const SocketModel model, QWidget *parent)
    : QWidget(parent)
    , id(id)
    , model(model)
    , ui(new Ui::SocketPage)
{
    ui->setupUi(this);

    auto wattsChart = new QChart;
    {
        wattsChart->legend()->hide();
        wattsChart->setAnimationOptions(QChart::SeriesAnimations);

        auto series = new QSplineSeries;
        wattsChart->addSeries(series);

        auto axisX = new QDateTimeAxis;
        axisX->setTickCount(5);
        axisX->setFormat("hh:mm:ss");
        axisX->setTitleText("Time");
        wattsChart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        auto axisY = new QValueAxis;
        axisY->setLabelFormat("%f");
        axisY->setTickCount(5);
        axisY->setTitleText("Watts");
        wattsChart->addAxis(axisY, Qt::AlignRight);
        series->attachAxis(axisY);
    }

    this->wattsView.setChart(wattsChart);
    this->wattsView.setRenderHint(QPainter::Antialiasing);
    ui->rowWatts->addWidget(&this->wattsView);

    connect(ui->btnPower, &QPushButton::clicked, this, [this] {
        mainModule->deviceRepository()->send(this->id,
                                             this->model.power ? this->model.powerOffCommand()
                                                               : this->model.powerOnCommand());
    });
}

void SocketPage::onModelUpdate(const SocketModel model)
{
    this->model = model;
    updateUi();
}

void SocketPage::updateUi()
{
    ui->lblPower->setText(model.power ? "Running" : "Stopped");
    {
        static qreal min = 100, max = 0;

        auto chart = this->wattsView.chart();
        auto series = static_cast<QLineSeries *>(chart->series().at(0));
        auto currentTime = QDateTime::currentMSecsSinceEpoch();
        series->append(currentTime, model.watts);
        chart->axes().at(0)->setRange(QDateTime::fromMSecsSinceEpoch(currentTime - 30000),
                                      QDateTime::fromMSecsSinceEpoch(currentTime));

        min = std::min(min, model.watts);
        max = std::max(max, model.watts);
        chart->axes().at(1)->setRange(min - 1, max + 1);
    }
}

SocketPage::~SocketPage()
{
    delete ui;
}
