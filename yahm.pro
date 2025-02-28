QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth/credential.cpp \
    auth/group.cpp \
    auth/session.cpp \
    auth/user.cpp \
    command.cpp \
    device/devicedata.cpp \
    device/devicemonitor.cpp \
    device/point.cpp \
    device/deviceinfo.cpp \
    device/deviceproperties.cpp \
    device/sensormonitor.cpp \
    devicemodel/airconmodel.cpp \
    devicemodel/socketmodel.cpp \
    di/mainmodule.cpp \
    main.cpp \
    mainwindow.cpp \
    net/websocketclient.cpp \
    repository/accountrepository.cpp \
    repository/apirepository.cpp \
    repository/devicerepository.cpp \
    ui/airconcard.cpp \
    ui/airconpage.cpp \
    ui/devicecard.cpp \
    ui/loginwindow.cpp \
    ui/socketcard.cpp \
    ui/socketpage.cpp

HEADERS += \
    auth/credential.h \
    auth/group.h \
    auth/session.h \
    auth/user.h \
    command.h \
    device/devicedata.h \
    device/devicemonitor.h \
    device/point.h \
    device/deviceinfo.h \
    device/deviceproperties.h \
    device/sensormonitor.h \
    devicemodel/airconmodel.h \
    devicemodel/socketmodel.h \
    di/mainmodule.h \
    mainwindow.h \
    net/websocketclient.h \
    repository/accountrepository.h \
    repository/apirepository.h \
    repository/devicerepository.h \
    ui/airconcard.h \
    ui/airconpage.h \
    ui/devicecard.h \
    ui/loginwindow.h \
    ui/socketcard.h \
    ui/socketpage.h

FORMS += \
    mainwindow.ui \
    ui/airconcard.ui \
    ui/airconpage.ui \
    ui/loginwindow.ui \
    ui/socketcard.ui \
    ui/socketpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ui/drawables.qrc

DISTFILES +=
