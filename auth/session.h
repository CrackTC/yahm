#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include "group.h"
#include "user.h"

class Session
{
public:
    Session(const QString &sessionId, const User &user, const Group &group);

    const QString &sessionId;
    const User &user;
    const Group &group;
};

#endif // SESSION_H
