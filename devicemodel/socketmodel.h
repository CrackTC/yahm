#ifndef SOCKETMODEL_H
#define SOCKETMODEL_H

#include "device/devicedata.h"
#include "command.h"

class SocketModel
{
public:
    explicit SocketModel(const DeviceData *data);
    SocketModel &operator=(const SocketModel &other)
    {
        name = other.name;
        watts = other.watts;
        power = other.power;
        return *this;
    }
    SocketModel(const SocketModel &other) { *this = other; }

    QString name;
    qreal watts;
    bool power;

    const Command powerOnCommand() const;
    const Command powerOffCommand() const;
};

#endif // SOCKETMODEL_H
