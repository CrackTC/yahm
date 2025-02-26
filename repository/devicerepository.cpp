#include "devicerepository.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

DeviceRepository::DeviceRepository(ApiRepository &apiRepository,
                                   AccountRepository &accountRepository,
                                   QObject *parent)
    : QObject{parent}
    , m_apiRepository(apiRepository)
    , m_accountRepository(accountRepository)
{}

static DeviceData *parseDeviceData(QJsonObject json)
{
    auto id = json.value("id").toInt();
    auto type = json.value("type").toString();
    auto info = new DeviceInfo(id, type);

    auto propObj = json.value("properties").toObject();
    auto name = propObj.value("name").toString();
    auto ownerUser = propObj.value("owner_user").toInt();
    auto ownerGroup = propObj.value("owner_group").toInt();
    auto perm = propObj.value("perm_flag").toInt();
    auto extraProps = QHash<QString, QVariant>();
    auto extraPropsObj = propObj.value("extraProps").toObject();
    for (auto key : extraPropsObj.keys()) {
        auto value = extraPropsObj.value(key);
        extraProps.insert(key, value.toVariant());
    }

    auto properties = new DeviceProperties(name,
                                           ownerUser,
                                           ownerGroup,
                                           static_cast<Permission>(perm),
                                           extraProps);

    auto sensorsArr = json.value("sensors").toArray();

    auto sensors = QList<SensorMonitor *>();

    for (auto sensorRef : sensorsArr) {
        auto sensorObj = sensorRef.toObject();
        auto id = sensorObj.value("id").toInt();
        auto name = sensorObj.value("name").toString();
        auto type = sensorObj.value("type").toString();

        auto pointObj = sensorObj.value("point").toObject();
        auto value = pointObj.value("value").toVariant();
        auto timestamp = pointObj.value("timestamp").toInteger();
        auto point = Point(value, timestamp);

        auto sensorMonitor = new SensorMonitor(name, id, type, point);
        sensors.append(sensorMonitor);
    }

    return new DeviceData(info, properties, sensors);
}

void DeviceRepository::connectSession(const Session &session)
{
    m_wsClient = m_apiRepository.connectSesssion(session.sessionId);
    QObject::connect(m_wsClient, &WebSocketClient::msgRecved, [=](const QString &msg) {
        auto json = QJsonDocument::fromJson(msg.toUtf8()).object();
        auto type = json.value("type").toString();

        if (type == "attach") {
            auto data = parseDeviceData(json.value("data").toObject());
            auto monitor = new DeviceMonitor(data);
            m_devices.insert(data->info()->id(), monitor);
            emit attached(*monitor);
        } else if (type == "detach") {
            auto id = json.value("data").toObject().value("id").toInt();
            emit detached(id);
            auto monitor = m_devices.value(id);
            delete monitor;
            m_devices.remove(id);
        } else if (type == "update") {

            auto arr = json.value("data").toArray();

            for (auto dataObj : arr) {
                qDebug() << dataObj;
                auto data = parseDeviceData(dataObj.toObject());
                auto newSensorPoints = QHash<int, Point>();

                for (auto sensor : data->sensors()) {
                    newSensorPoints.insert(sensor->id(), sensor->point());
                }

                auto monitor = m_devices.value(data->info()->id());
                monitor->update(data);
                for (auto sensor : monitor->data()->sensors()) {
                    auto newPoint = newSensorPoints.value(sensor->id());
                    if (newPoint.timestamp != sensor->point().timestamp) {
                        sensor->update(newPoint);
                    }
                }
            }
        } else {
            qDebug() << "unknown ws message type";
        }
    });
}

void DeviceRepository::disconnect()
{
    m_wsClient->close();
    m_wsClient->deleteLater();
    m_wsClient = nullptr;

    for (auto device : m_devices) {
        device->deleteLater();
    }
    m_devices.clear();
}

void DeviceRepository::send(const int deviceId, const Command &cmd)
{
    QJsonDocument document;
    QJsonObject root;

    root.insert("sessionId", m_accountRepository.session()->sessionId);
    root.insert("type", cmd.type);

    auto args = QJsonArray();
    for (auto arg : cmd.args) {
        args.append(arg);
    }

    root.insert("args", args);
    document.setObject(root);

    auto reply = m_apiRepository.post("/api/device/" + QString::number(deviceId) + "/command",
                                      document);
    QObject::connect(reply, &QNetworkReply::finished, [=] {
        auto resp = QJsonDocument::fromJson(reply->readAll());
        reply->deleteLater();

        if (resp.object().value("success").toBool() == false) {
            emit message(resp.object().value("message").toString());
        }
    });
}

int DeviceRepository::queryHistory(int deviceId, int sensorId)
{
    static int currentTag = 0;
    int tag = currentTag++;

    QJsonDocument document;
    QJsonObject root;

    root.insert("sessionId", m_accountRepository.session()->sessionId);
    document.setObject(root);

    auto reply = m_apiRepository.post("/api/device/" + QString::number(deviceId) + "/sensor/"
                                          + QString::number(sensorId) + "/history",
                                      document);

    QObject::connect(reply, &QNetworkReply::finished, [=] {
        auto resp = QJsonDocument::fromJson(reply->readAll());
        reply->deleteLater();

        if (resp.object().value("success").toBool() == false) {
            emit message(resp.object().value("message").toString());
            emit historyRecved(tag, {});
        }

        auto result = QList<Point>();

        for (auto pointVal : resp.object().value("points").toArray()) {
            auto value = pointVal.toObject().value("value").toVariant();
            auto timestamp = pointVal.toObject().value("timestamp").toInteger();
            auto point = Point(value, timestamp);
            result.append(point);
        }

        emit historyRecved(tag, result);
    });

    return tag;
}
