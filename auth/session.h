#ifndef SESSION_H
#define SESSION_H

#include <QList>
#include <QString>

#include "group.h"
#include "user.h"

class Session
{
public:
    Session(const QString &sessionId, const User *user, const QList<Group *> &groups);
    ~Session();

    const QString sessionId;
    const User *user;
    const QList<Group *> groups;
};

#endif // SESSION_H
