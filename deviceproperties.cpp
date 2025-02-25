#include "deviceproperties.h"

DeviceProperties::DeviceProperties(const QString &name,
                                   const int ownerUser,
                                   const int ownerGroup,
                                   const Permission perm,
                                   const QHash<QString, QVariant> &extraProps)
    : name(name)
    , ownerUser(ownerUser)
    , ownerGroup(ownerGroup)
    , perm(perm)
    , extraProps(extraProps)
{}
