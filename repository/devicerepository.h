#ifndef DEVICEREPOSITORY_H
#define DEVICEREPOSITORY_H

#include <QObject>
#include "accountrepository.h"
#include "apirepository.h"
#include "auth/session.h"
#include "device/devicemonitor.h"
#include "device/point.h"
#include "command.h"

class DeviceRepository : public QObject
{
    Q_OBJECT
public:
    DeviceRepository(ApiRepository &apiRepository, AccountRepository &accountRepository, QObject *parent = nullptr);

    int queryHistory(int deviceId, int sensorId);

signals:
    void message(const QString &msg);
    void attached(const DeviceMonitor &monitor);
    void detached(const int deviceId);
    void historyRecved(int tag, QList<Point> points);

public slots:
    void connectSession(const Session &session);
    void disconnect();
    void send(const int deviceId, const Command &cmd);

private:
    ApiRepository &m_apiRepository;
    AccountRepository &m_accountRepository;
    WebSocketClient *m_wsClient = nullptr;
    QHash<int, DeviceMonitor *> m_devices{};
};

#endif // DEVICEREPOSITORY_H
