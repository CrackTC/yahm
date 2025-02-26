#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "device/devicemonitor.h"
#include "ui/devicecard.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void logout();

public slots:
    void addDevice(const DeviceMonitor &monitor);
    void removeDevice(const int deviceId);
    void message(const QString &msg);
    void clear();

private:
    Ui::MainWindow *ui;
    QHash<int, const DeviceMonitor *> devices;
    QHash<int, DeviceCard *> cards;
    QLabel lblUser;
    QLabel lblGroup;
};
#endif // MAINWINDOW_H
