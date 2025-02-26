#include "devicemonitor.h"

DeviceMonitor::DeviceMonitor(DeviceData *init, QObject *parent)
    : QObject{parent}
    , m_data(init)
{}

DeviceMonitor::~DeviceMonitor()
{
    delete m_data;
}

void DeviceMonitor::update(const DeviceData *data)
{
    if (m_data != nullptr) {
        delete m_data;
    }
    m_data = data;
    emit updated(data);
}
