#include "command.h"

Command::Command(const QString &type, const QList<QString> &args)
    : type(type)
    , args(args)
{}
