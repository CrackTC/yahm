#ifndef DEVICEPROPERTIES_H
#define DEVICEPROPERTIES_H

#include <QHash>
#include <QString>

enum class Permission {
    OthersWrite = 0b10,
    OthersRead = 0b100,
    GroupWrite = 0b10000,
    GroupRead = 0b100000,
    UserWrite = 0b10000000,
    UserRead = 0b100000000
};

class DeviceProperties
{
public:
    DeviceProperties(const QString &name,
                     const int ownerUser,
                     const int ownerGroup,
                     const Permission perm,
                     const QHash<QString, QVariant> &extraProps);

    const QString &name;
    const int ownerUser;
    const int ownerGroup;
    const Permission perm;
    const QHash<QString, QVariant> &extraProps;
};

#endif // DEVICEPROPERTIES_H
