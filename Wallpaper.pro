#-------------------------------------------------
#
# Project created by QtCreator 2018-06-05T20:29:07
#
#-------------------------------------------------

QT       += core gui
QT       += webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wallpaper
TEMPLATE = app
LIBS  += -luser32

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8
win32:RC_FILE = icon.rc

SOURCES += main.cpp\
        wallpaper.cpp \
    utils.cpp

HEADERS  += wallpaper.h \
    utils.h

FORMS    += wallpaper.ui

RESOURCES += \
    icon.qrc
