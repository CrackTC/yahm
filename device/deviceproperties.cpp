#include "deviceproperties.h"

DeviceProperties::DeviceProperties(const QString &name,
                                   const int ownerUser,
                                   const int ownerGroup,
                                   const Permission perm,
                                   const QHash<QString, QVariant> extraProps,
                                   QObject *parent)
    : QObject{parent}
    , m_name(name)
    , m_ownerUser(ownerUser)
    , m_ownerGroup(ownerGroup)
    , m_perm(perm)
    , m_extraProps(extraProps)
{}
