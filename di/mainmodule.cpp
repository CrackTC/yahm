#include "mainmodule.h"

MainModule::MainModule(AccountRepository *accountRepository,
                       ApiRepository *apiRepository,
                       DeviceRepository *deviceRepository,
                       QObject *parent)
    : QObject{parent}
    , m_accountRepository(accountRepository)
    , m_apiRepository(apiRepository)
    , m_deviceRepository(deviceRepository)
{}
