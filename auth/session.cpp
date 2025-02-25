#include "session.h"

Session::Session(const QString &sessionId, const User &user, const Group &group)
    : sessionId(sessionId)
    , user(user)
    , group(group)
{}
