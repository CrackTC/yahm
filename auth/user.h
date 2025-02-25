#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(const int uid, const QString &username);
    const int uid;
    const QString &username;
};

#endif // USER_H
