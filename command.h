#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

class Command
{
public:
    Command(const QString &type, const QList<QString> &args);

    const QString &type;
    const QList<QString> &args;
};

#endif // COMMAND_H
