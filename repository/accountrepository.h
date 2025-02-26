#ifndef ACCOUNTREPOSITORY_H
#define ACCOUNTREPOSITORY_H

#include <QObject>
#include "apirepository.h"
#include "auth/credential.h"
#include "auth/session.h"

class AccountRepository : public QObject
{
    Q_OBJECT
public:
    AccountRepository(ApiRepository &apiRepository, QObject *parent = nullptr);

    Q_PROPERTY(const Session *session READ session)

    const Session *session() const { return m_session; }

signals:
    void message(const QString &msg);
    void loggedIn(const Session &session);
    void loggedOut();

public slots:
    void login(const Credential &credential);
    void logout();

private:
    const Session *m_session;
    ApiRepository &m_apiRepository;
};

#endif // ACCOUNTREPOSITORY_H
