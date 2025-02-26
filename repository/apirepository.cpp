#include "apirepository.h"

#include <QtNetwork>

ApiRepository::ApiRepository(const QString &apiUrl, QObject *parent)
    : QObject{parent}
    , m_apiUrl(apiUrl)
    , m_netManager(nullptr)
{}

QNetworkReply *ApiRepository::post(const QString &endpoint, const QJsonDocument &data)
{
    if (m_netManager == nullptr) {
        QNetworkProxyFactory::setUseSystemConfiguration(true);
        auto proxies = QNetworkProxyFactory::systemProxyForQuery();

        m_netManager = new QNetworkAccessManager(this);
        m_netManager->setProxy(proxies[0]);
    }

    auto url = QUrl("http://" + m_apiUrl + endpoint);
    auto request = QNetworkRequest(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    return m_netManager->post(request, data.toJson(QJsonDocument::Compact));
}

WebSocketClient *ApiRepository::connectSesssion(const QString &sessionId) const
{
    auto url = QUrl("ws://" + m_apiUrl + "/api/connection");
    auto client = new WebSocketClient();
    client->connectUrl(url, sessionId);
    return client;
}
