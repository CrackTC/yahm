#ifndef SOCKETCARD_H
#define SOCKETCARD_H

#include <QWidget>

#include "devicemodel/socketmodel.h"
#include "ui/devicecard.h"
#include "ui/socketpage.h"

namespace Ui {
class SocketCard;
}

class SocketCard : public DeviceCard
{
    Q_OBJECT

public:
    explicit SocketCard(const DeviceData *data, QWidget *parent = nullptr);
    ~SocketCard();

public slots:
    void onDataUpdate(const DeviceData *newData) override;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::SocketCard *ui;
    void updateUi();
    int id;
    SocketModel model;
    SocketPage *page;
};

#endif // SOCKETCARD_H
