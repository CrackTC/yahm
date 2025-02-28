#ifndef AIRCONPAGE_H
#define AIRCONPAGE_H

#include <QWidget>
#include <QChartView>

#include "devicemodel/airconmodel.h"

namespace Ui {
class AirconPage;
}

class AirconPage : public QWidget
{
    Q_OBJECT

public:
    explicit AirconPage(int id, const AirconModel model, QWidget *parent = nullptr);
    ~AirconPage();

public slots:
    void onModelUpdate(const AirconModel model);

private:
    Ui::AirconPage *ui;
    int id;
    AirconModel model;
    void updateUi();
    QChartView tempView;
    QChartView humidityView;
};

#endif // AIRCONPAGE_H
