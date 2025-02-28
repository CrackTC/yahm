#include "socketmodel.h"

SocketModel::SocketModel(const DeviceData *data)
{
    this->name = data->properties()->name();
    this->power = data->properties()->extraProps().value("power").toBool();
    for (auto sensor : data->sensors()) {
        if (sensor->name() == "Watts") {
            this->watts = sensor->point().value.toReal();
        }
    }
}

const Command SocketModel::powerOnCommand() const
{
    return Command("poweron", {});
}

const Command SocketModel::powerOffCommand() const
{
    return Command("poweroff", {});
}
