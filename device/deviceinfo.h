#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QObject>

class DeviceInfo : public QObject
{
    Q_OBJECT
public:
    DeviceInfo(const int id, const QString &type, QObject *parent = nullptr);

    Q_PROPERTY(int id READ id)
    Q_PROPERTY(const QString &type READ type)

    int id() const { return m_id; }
    const QString &type() const { return m_type; }

private:
    const int m_id;
    const QString m_type;
};

#endif // DEVICEINFO_H
