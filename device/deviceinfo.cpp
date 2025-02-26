#include "deviceinfo.h"

DeviceInfo::DeviceInfo(const int id, const QString &type, QObject *parent)
    : QObject{parent}
    , m_id(id)
    , m_type(type)
{}
