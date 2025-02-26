#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(QObject *parent = nullptr);
    ~WebSocketClient();

    void connectUrl(const QUrl &url, const QString &sessionId);
    void close();
    void send(const QString &msg);
    bool isConnected() const;

signals:
    void msgRecved(const QString &msg);

private:
    QWebSocket *m_webSocket;
    bool m_connected = false;
};

#endif // WEBSOCKETCLIENT_H
