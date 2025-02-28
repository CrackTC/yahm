#ifndef AIRCONMODEL_H
#define AIRCONMODEL_H

#include "command.h"
#include "device/devicedata.h"

class AirconModel
{
public:
    explicit AirconModel(const DeviceData *data);
    AirconModel &operator=(const AirconModel &other)
    {
        name = other.name;
        temp = other.temp;
        tgtTemp = other.tgtTemp;
        humidity = other.humidity;
        power = other.power;
        mode = other.mode;
        return *this;
    }
    AirconModel(const AirconModel &other) { *this = other; }

    QString name;
    qreal temp;
    int tgtTemp;
    qreal humidity;
    bool power;
    QString mode;

    const Command powerOnCommand() const;
    const Command powerOffCommand() const;
    const Command setTgtTempCommand(int tgt) const;
    const Command setModeCommand() const;
};

#endif // AIRCONMODEL_H
