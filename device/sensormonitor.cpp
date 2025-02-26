#include "sensormonitor.h"

SensorMonitor::SensorMonitor(
    const QString &name, const int id, const QString &type, const Point &initPoint, QObject *parent)
    : QObject{parent}
    , m_name(name)
    , m_id(id)
    , m_type(type)
    , m_point(initPoint)
{}

void SensorMonitor::update(const Point &point)
{
    emit updated(point);
}
