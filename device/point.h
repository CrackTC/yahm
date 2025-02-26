#ifndef POINT_H
#define POINT_H

#include <QVariant>

class Point
{
public:
    Point() = default;
    Point(const QVariant &value, const qint64 timestamp);

    QVariant value;
    qint64 timestamp;
};

#endif // POINT_H
