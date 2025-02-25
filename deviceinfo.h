#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QString>

class DeviceInfo
{
public:
    DeviceInfo(const int id, const QString &type);

    const int id;
    const QString &type;
};

#endif // DEVICEINFO_H
