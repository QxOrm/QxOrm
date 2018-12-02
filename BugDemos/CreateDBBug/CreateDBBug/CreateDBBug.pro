
CONFIG(debug, debug|release) {
FILESUFFIX = d
}

include($$PWD/../../../QxOrm.pri)
QT += core
QT -= gui

CONFIG += c++11

TARGET = CreateDBBug
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../../../include
UI_DIR = ./GeneratedFiles
INCLUDEPATH += ./GeneratedFiles/conf$${FILESUFFIX}

LIBS += -L"$$PWD/../../../lib$${LIBDIR}"
LIBS += -lQxOrm$${FILESUFFIX}
