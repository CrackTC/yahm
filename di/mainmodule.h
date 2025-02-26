#ifndef MAINMODULE_H
#define MAINMODULE_H

#include <QObject>
#include "repository/accountrepository.h"
#include "repository/apirepository.h"
#include "repository/devicerepository.h"

// owns repositories
class MainModule : public QObject
{
    Q_OBJECT
public:
    MainModule(AccountRepository *accountRepository,
               ApiRepository *apiRepository,
               DeviceRepository *deviceRepository,
               QObject *parent = nullptr);

    Q_PROPERTY(AccountRepository *accountRepository READ accountRepository)
    Q_PROPERTY(ApiRepository *apiRepository READ apiRepository)
    Q_PROPERTY(DeviceRepository *deviceRepository READ deviceRepository)

    AccountRepository *accountRepository() const { return m_accountRepository; }
    ApiRepository *apiRepository() const { return m_apiRepository; }
    DeviceRepository *deviceRepository() const { return m_deviceRepository; }

private:
    AccountRepository *m_accountRepository;
    ApiRepository *m_apiRepository;
    DeviceRepository *m_deviceRepository;
};

extern const MainModule *mainModule;

#endif // MAINMODULE_H
