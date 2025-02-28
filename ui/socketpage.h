#ifndef SOCKETPAGE_H
#define SOCKETPAGE_H

#include <QWidget>
#include <QChartView>

#include "devicemodel/socketmodel.h"

namespace Ui {
class SocketPage;
}

class SocketPage : public QWidget
{
    Q_OBJECT

public:
    SocketPage(int id, const SocketModel model, QWidget *parent = nullptr);
    ~SocketPage();

public slots:
    void onModelUpdate(const SocketModel model);

private:
    int id;
    SocketModel model;
    void updateUi();
    QChartView wattsView;
    Ui::SocketPage *ui;
};

#endif // SOCKETPAGE_H
