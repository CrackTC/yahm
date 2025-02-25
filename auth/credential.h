#ifndef CREDENTIAL_H
#define CREDENTIAL_H

#include <QString>

class Credential
{
public:
    Credential(const QString &username, const QString &password);

    const QString &username;
    const QString &password;
};

#endif // CREDENTIAL_H
