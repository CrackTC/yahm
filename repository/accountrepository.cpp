#include "accountrepository.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "auth/group.h"
#include "auth/user.h"

AccountRepository::AccountRepository(ApiRepository &apiRepository, QObject *parent)
    : QObject{parent}
    , m_apiRepository(apiRepository)
{}

void AccountRepository::login(const Credential &credential)
{
    QJsonDocument document;
    QJsonObject root;

    root.insert("username", credential.username);
    root.insert("password", credential.password);
    document.setObject(root);

    auto reply = m_apiRepository.post("/api/user/login", document);
    connect(reply, &QNetworkReply::finished, [=] {
        auto resp = QJsonDocument::fromJson(reply->readAll());
        reply->deleteLater();
        if (resp.object().value("success").toBool() == false) {
            emit message(resp.object().value("message").toString());
        } else {
            auto sessionId = resp.object().value("sessionId").toString();

            auto uid = resp.object().value("user").toObject().value("uid").toInt();
            auto username = resp.object().value("user").toObject().value("username").toString();
            auto user = new User(uid, username);

            auto groups = QList<Group *>{};
            for (auto groupObj : resp.object().value("groups").toArray()) {
                auto gid = groupObj.toObject().value("gid").toInt();
                auto groupname = groupObj.toObject().value("groupname").toString();
                auto group = new Group(gid, groupname);
                groups.append(group);
            }

            m_session = new Session(sessionId, user, groups);
            emit loggedIn(*m_session);
        }
    });
}

void AccountRepository::logout()
{
    QJsonDocument document;
    QJsonObject root;

    root.insert("sessionId", m_session->sessionId);
    document.setObject(root);

    auto reply = m_apiRepository.post("/api/user/logout", document);
    connect(reply, &QNetworkReply::finished, [=] {
        auto resp = QJsonDocument::fromJson(reply->readAll());
        reply->deleteLater();
        if (resp.object().value("success").toBool() == false) {
            emit message(resp.object().value("msesage").toString());
        } else {
            emit loggedOut();
        }

        if (m_session != nullptr) {
            delete m_session;
            m_session = nullptr;
        }
    });
}

