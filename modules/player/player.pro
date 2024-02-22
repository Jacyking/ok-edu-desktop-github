TEMPLATE = lib
TARGET = player
CONFIG += staticlib

QT += widgets
#av avwidgets

INCLUDEPATH +=  $$PWD/../..                     \
                $$PWD/../../3rdparty            \

if(Q_OS_WIN){

}else{
    DEFINES += Q_OS_LINUX WEBRTC_POSIX
}

SOURCES += \
    playerwindow.cpp \


HEADERS += \
    playerwindow.h \


FORMS += \



