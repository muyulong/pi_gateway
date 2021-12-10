QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database\dataBase.cpp \
    frame\log.cpp \
    frame\login.cpp \
    main.cpp \
    frame\regist.cpp \
    node.cpp \
    system.cpp \
    task\task.cpp \
    user\user.cpp \
    frame\welcome.cpp \
    frame\mainfrm.cpp

HEADERS += \
    database\dataBase.h \
    frame\log.h \
    frame\login.h \
    frame\regist.h \
    node.h \
    system.h \
    task\task.h \
    user\user.h \
    frame\welcome.h \
    frame\mainfrm.h

FORMS += \
    frame\log.ui \
    frame\login.ui \
    frame\regist.ui \
    frame\welcome.ui \
    frame\mainfrm.ui \
    node.ui

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

RESOURCES += \
    resource.qrc

DISTFILES +=
