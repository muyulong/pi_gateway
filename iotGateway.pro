QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dataBase.cpp \
    log.cpp \
    login.cpp \
    main.cpp \
    regist.cpp \
    system.cpp \
    task.cpp \
    tcpserver.cpp \
    user.cpp \
    welcome.cpp \
    widget.cpp

HEADERS += \
    dataBase.h \
    log.h \
    login.h \
    regist.h \
    system.h \
    task.h \
    tcpserver.h \
    user.h \
    welcome.h \
    widget.h

FORMS += \
    log.ui \
    login.ui \
    regist.ui \
    welcome.ui \
    widget.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32-msvc*: {
    QMAKE_CFLAGS *= /utf-8
    QMAKE_CXXFLAGS *= /utf-8
}
