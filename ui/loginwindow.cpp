
#include <QMessageBox>

#include "di/mainmodule.h"
#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    setFixedSize(400, 300);
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, [=] {
        mainModule->accountRepository()->login(
            Credential(ui->userEdit->text(), ui->pwdEdit->text()));
    });
    connect(mainModule->accountRepository(),
            &AccountRepository::loggedIn,
            this,
            &LoginWindow::loggedIn);
    connect(mainModule->accountRepository(),
            &AccountRepository::message,
            this,
            &LoginWindow::message);
}

void LoginWindow::message(const QString &msg)
{
    QMessageBox::warning(this, "Login Failed", msg);
}

void LoginWindow::clear()
{
    ui->userEdit->clear();
    ui->pwdEdit->clear();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
