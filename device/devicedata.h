#ifndef DEVICEDATA_H
#define DEVICEDATA_H

class DeviceData;

#include "deviceinfo.h"
#include "deviceproperties.h"
#include "sensormonitor.h"

#include <QObject>

class DeviceData : public QObject
{
    Q_OBJECT
public:
    DeviceData(const DeviceInfo *info,
               const DeviceProperties *properties,
               const QList<SensorMonitor *> sensors,
               QObject *parent = nullptr);
    ~DeviceData();

    Q_PROPERTY(const DeviceInfo *info READ info)
    Q_PROPERTY(const DeviceProperties *properties READ properties)
    Q_PROPERTY(const QList<SensorMonitor *> &sensors READ sensors)

    const DeviceInfo *info() const { return m_info; }
    const DeviceProperties *properties() const { return m_properties; }
    const QList<SensorMonitor *> sensors() const { return m_sensors; }

private:
    const DeviceInfo *m_info;
    const DeviceProperties *m_properties;
    const QList<SensorMonitor *> m_sensors;
};

#endif // DEVICEDATA_H
