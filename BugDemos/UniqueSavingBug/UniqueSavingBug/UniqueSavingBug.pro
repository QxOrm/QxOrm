#-------------------------------------------------
#
# Project created by QtCreator 2018-11-30T09:14:10
#
#-------------------------------------------------

CONFIG(debug, debug|release) {
FILESUFFIX = d
}

include($$PWD/../../../QxOrm.pri)

QT       += core

TARGET = UniqueSavingBug
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../../../include ../KPI/include
UI_DIR = ./GeneratedFiles
INCLUDEPATH += ./GeneratedFiles/conf$${FILESUFFIX}

LIBS += -L"../KPI/bin" \
    -L"$$PWD/../../../lib$${LIBDIR}"
LIBS += -lKPI$${FILESUFFIX} \
    -lQxOrm$${FILESUFFIX}

SOURCES += \
        main.cpp \
