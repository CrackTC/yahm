#ifndef DEVICEPROPERTIES_H
#define DEVICEPROPERTIES_H

#include <QHash>
#include <QObject>
#include <QString>
#include <QVariant>

enum class Permission {
    OthersWrite = 0b10,
    OthersRead = 0b100,
    GroupWrite = 0b10000,
    GroupRead = 0b100000,
    UserWrite = 0b10000000,
    UserRead = 0b100000000
};

class DeviceProperties : public QObject
{
    Q_OBJECT
public:
    DeviceProperties(const QString &name,
                     const int ownerUser,
                     const int ownerGroup,
                     const Permission perm,
                     const QHash<QString, QVariant> extraProps,
                     QObject *parent = nullptr);

    Q_PROPERTY(const QString &name READ name)
    Q_PROPERTY(int ownerUser READ ownerUser)
    Q_PROPERTY(int ownerGroup READ ownerGroup)
    Q_PROPERTY(Permission perm READ perm)
    Q_PROPERTY(const QHash<QString, QVariant> extraProps READ extraProps)

    const QString &name() const { return m_name; }
    int ownerUser() const { return m_ownerUser; }
    int ownerGroup() const { return m_ownerGroup; }
    Permission perm() const { return m_perm; }
    const QHash<QString, QVariant> extraProps() const { return m_extraProps; }

private:
    const QString m_name;
    const int m_ownerUser;
    const int m_ownerGroup;
    const Permission m_perm;
    const QHash<QString, QVariant> m_extraProps;
};

#endif // DEVICEPROPERTIES_H
