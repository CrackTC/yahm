#ifndef DEVICECARD_H
#define DEVICECARD_H

#include <QMouseEvent>
#include <QWidget>

#include "device/devicedata.h"

// widget shown in MainWindow
// with a primary command (e.g. a button that shows a dialog for
// target temperature adjustment),
// some properties (e.g. name, status)，
// primary sensor point (e.g. current temperature for aircon)
class DeviceCard : public QWidget
{
    Q_OBJECT
public:
    // constructor of subclasses should use initData for initial painting
    DeviceCard(const DeviceData *initData, QWidget *parent = nullptr);

    // one primary command, e.g.
    // void targetTemperatureChanged(float temperature);
public slots:
    // responsible for updating ui to reflect data change
    virtual void onDataUpdate(const DeviceData *newData) = 0;

private:
    // don't save DeviceData here, it's owned by upstream code
    // and could be deleted at any time.
    // just keep it local in update function and discard it after return.
};

#endif // DEVICECARD_H
