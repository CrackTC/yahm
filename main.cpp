#include "mainwindow.h"

#include <QApplication>

#include "di/mainmodule.h"
#include "repository/accountrepository.h"
#include "repository/apirepository.h"
#include "repository/devicerepository.h"
#include "ui/loginwindow.h"

const MainModule *mainModule;

void initMainModule()
{
    auto apiRepository = new ApiRepository("127.0.0.1:8000");
    auto accountRepository = new AccountRepository(*apiRepository);
    auto deviceRepository = new DeviceRepository(*apiRepository, *accountRepository);
    mainModule = new MainModule(accountRepository, apiRepository, deviceRepository);
}

int main(int argc, char *argv[])
{
    initMainModule();
    QApplication a(argc, argv);

    MainWindow *mainWindow = new MainWindow;
    LoginWindow *loginWindow = new LoginWindow();

    auto onLoggedIn = [&](const Session &session) {
        qDebug() << session.sessionId;
        mainModule->deviceRepository()->connectSession(session);
        loginWindow->close();
        loginWindow->clear();
        mainWindow->show();
    };

    auto onLoggedOut = [&] {
        mainModule->deviceRepository()->disconnect();
        mainModule->accountRepository()->logout();
        mainWindow->close();
        mainWindow->clear();
        loginWindow->show();
    };

    QObject::connect(loginWindow, &LoginWindow::loggedIn, onLoggedIn);
    QObject::connect(mainWindow, &MainWindow::logout, onLoggedOut);

    loginWindow->show();
    return a.exec();
}
