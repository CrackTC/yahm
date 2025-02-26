#ifndef DEVICEMONITOR_H
#define DEVICEMONITOR_H

#include <QObject>
#include <device/devicedata.h>

class DeviceMonitor : public QObject
{
    Q_OBJECT
public:
    DeviceMonitor(DeviceData *init, QObject *parent = nullptr);
    ~DeviceMonitor();

    Q_PROPERTY(const DeviceData *data READ data)

    const DeviceData *data() const { return m_data; }

signals:
    void updated(const DeviceData *data);

public slots:
    void update(const DeviceData *data);

private:
    const DeviceData *m_data;
};

#endif // DEVICEMONITOR_H
