#include "session.h"

Session::Session(const QString &sessionId, const User *user, const QList<Group *> &groups)
    : sessionId(sessionId)
    , user(user)
    , groups(groups)
{}

Session::~Session()
{
    delete user;
    for (auto group : groups) {
        delete group;
    }
}
