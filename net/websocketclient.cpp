#include "websocketclient.h"

WebSocketClient::WebSocketClient(QObject *parent)
    : QObject{parent}
{
    m_webSocket = new QWebSocket();

    QObject::connect(m_webSocket, &QWebSocket::connected, [=] {
        m_connected = true;

        QObject::connect(m_webSocket,
                         &QWebSocket::textMessageReceived,
                         this,
                         &WebSocketClient::msgRecved);
    });

    QObject::connect(m_webSocket, &QWebSocket::disconnected, [=] { m_connected = false; });

    QObject::connect(m_webSocket,
                     &QWebSocket::errorOccurred,
                     [=](QAbstractSocket::SocketError error) {
                         qDebug() << (int) error << m_webSocket->errorString();
                     });
}

WebSocketClient::~WebSocketClient()
{
    m_webSocket->deleteLater();
}

void WebSocketClient::connectUrl(const QUrl &url, const QString &sessionId)
{
    QNetworkRequest request(url);
    QString authorizationHeader = "Basic " + sessionId;

    request.setRawHeader("Authorization", authorizationHeader.toUtf8());

    m_webSocket->open(request);
}

void WebSocketClient::close()
{
    m_webSocket->close();
}

void WebSocketClient::send(const QString &msg) {
    m_webSocket->sendTextMessage(msg);
}

bool WebSocketClient::isConnected() const {
    return m_connected;
}
