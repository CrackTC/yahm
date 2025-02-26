#ifndef AIRCONCARD_H
#define AIRCONCARD_H

#include <QWidget>
#include <QMouseEvent>

#include "ui/devicecard.h"
#include "devicemodel/airconmodel.h"
#include "ui/airconpage.h"

namespace Ui {
class AirconCard;
}

class AirconCard : public DeviceCard
{
    Q_OBJECT

public:
    explicit AirconCard(const DeviceData *initData, QWidget *parent = nullptr);
    ~AirconCard();

public slots:
    void onDataUpdate(const DeviceData *newData) override;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::AirconCard *ui;
    int id;
    AirconModel model;
    AirconPage *page = nullptr;
    void updateUi();
};

#endif // AIRCONCARD_H
