#ifndef SENSORMONITOR_H
#define SENSORMONITOR_H

#include <QObject>
#include "point.h"

class SensorMonitor : public QObject
{
    Q_OBJECT
public:
    SensorMonitor(const QString &name,
                  const int id,
                  const QString &type,
                  const Point &initPoint,
                  QObject *parent = nullptr);

    Q_PROPERTY(const QString &name READ name)
    Q_PROPERTY(int id READ id)
    Q_PROPERTY(const QString &type READ type)
    Q_PROPERTY(const Point point READ point)

    const QString &name() const { return m_name; }
    int id() const { return m_id; }
    const QString &type() const { return m_type; }
    const Point point() const { return m_point; }

public slots:
    void update(const Point &point);

signals:
    void updated(const Point &point);

private:
    const QString m_name;
    const int m_id;
    const QString m_type;
    const Point m_point;
};

#endif // SENSORMONITOR_H
