#include "airconmodel.h"

AirconModel::AirconModel(const DeviceData *data)
    : name(data->properties()->name())
    , tgtTemp(data->properties()->extraProps().value("tgtTemperature").toInt())
    , power(data->properties()->extraProps().value("power").toBool())
    , mode(data->properties()->extraProps().value("mode").toString())
{
    for (auto sensor : data->sensors()) {
        if (sensor->name() == "Temperature") {
            temp = sensor->point().value.toString() + "°C";
        } else if (sensor->name() == "Humidity") {
            humidity = sensor->point().value.toString() + "%";
        }
    }
}

const Command AirconModel::powerOnCommand() const
{
    static auto cmd = Command("poweron", {});
    return cmd;
}

const Command AirconModel::powerOffCommand() const
{
    static auto cmd = Command("poweroff", {});
    return cmd;
}

const Command AirconModel::setTgtTempCommand(int tgt) const
{
    return Command("set", {"tgtTemperature", QString::number(tgt)});
}

const Command AirconModel::setModeCommand() const
{
    return Command("set", {"mode", this->mode == "cool" ? "heat" : "cool"});
}
