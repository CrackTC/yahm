#ifndef APIREPOSITORY_H
#define APIREPOSITORY_H

#include <QJsonDocument>
#include <QNetworkReply>
#include <QObject>

#include "net/websocketclient.h"

class ApiRepository : public QObject
{
    Q_OBJECT
public:
    ApiRepository(const QString &apiUrl, QObject *parent = nullptr);

    QNetworkReply *post(const QString &endpoint, const QJsonDocument &data);
    WebSocketClient *connectSesssion(const QString &sessionId) const;

    Q_PROPERTY(const QString &apiUrl READ apiUrl WRITE setApiUrl)

    void setApiUrl(const QString &apiUrl) { m_apiUrl = apiUrl; }

    const QString &apiUrl() const { return m_apiUrl; }

private:
    QString m_apiUrl;
    QNetworkAccessManager *m_netManager;
};

#endif // APIREPOSITORY_H
