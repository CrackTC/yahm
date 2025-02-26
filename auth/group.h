#ifndef GROUP_H
#define GROUP_H

#include <QString>

class Group
{
public:
    Group(const int gid, const QString &groupname);
    const int gid;
    const QString groupname;
};

#endif // GROUP_H
