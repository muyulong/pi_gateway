QT       += core gui sql network serialport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database\dataBase.cpp \
    instruction\instruction.cpp \
    log\log.cpp \
    thchart\thchart.cpp \
    user\login.cpp \
    main.cpp \
    user\regist.cpp \
    com\net\netcom.cpp \
    node\node.cpp \
    com\serial\serialcom.cpp \
    task\task.cpp \
    user\user.cpp \
    welcome\welcome.cpp \
    mainfrm\mainfrm.cpp

HEADERS += \
    com\net\heartbeat.h \
    database\dataBase.h \
    instruction\instruction.h \
    log\log.h \
    thchart\thchart.h \
    user\login.h \
    user\regist.h \
    com\net\netcom.h \
    node\node.h \
    com\serial\serialcom.h \
    task\task.h \
    user\user.h \
    welcome\welcome.h \
    mainfrm\mainfrm.h

FORMS += \
    instruction\instruction.ui \
    log\log.ui \
    thchart\thchart.ui \
    user\login.ui \
    user\regist.ui \
    welcome\welcome.ui \
    mainfrm\mainfrm.ui \
    com\net\netcom.ui \
    node\node.ui \
    com\serial\serialcom.ui \
    task\task.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resource.qrc

DISTFILES +=
