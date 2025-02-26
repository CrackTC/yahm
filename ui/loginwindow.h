#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

#include "auth/session.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loggedIn(const Session &session);

public slots:
    void message(const QString &msg);
    void clear();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
