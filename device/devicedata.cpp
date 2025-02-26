#include "devicedata.h"

DeviceData::DeviceData(const DeviceInfo *info,
                       const DeviceProperties *properties,
                       const QList<SensorMonitor *> sensors,
                       QObject *parent)
    : QObject{parent}
    , m_info(info)
    , m_properties(properties)
    , m_sensors(sensors)
{}

DeviceData::~DeviceData()
{
    delete m_info;
    delete m_properties;
    for (auto sensor : m_sensors) {
        delete sensor;
    }
}
