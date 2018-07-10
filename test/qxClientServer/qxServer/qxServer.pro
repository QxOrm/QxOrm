include(../../../QxOrm.pri)

TEMPLATE = app
DEFINES += _BUILDING_QX_SERVER
INCLUDEPATH += ../../../../QxOrm/include/
DESTDIR = ../../../../QxOrm/test/_bin/
LIBS += -L"../../../../QxOrm/test/_bin"
PRECOMPILED_HEADER = ./include/precompiled.h

CONFIG(debug, debug|release) {
TARGET = qxServerd
LIBS += -l"QxOrmd"
LIBS += -l"qxServiceServerd"
} else {
TARGET = qxServer
LIBS += -l"QxOrm"
LIBS += -l"qxServiceServer"
} # CONFIG(debug, debug|release)

HEADERS += ./include/precompiled.h
HEADERS += ./include/export.h
HEADERS += ./include/main_dlg.h

SOURCES += ./src/main_dlg.cpp
SOURCES += ./src/main.cpp

FORMS += ./qt/ui/qxServer.ui

RESOURCES += ./qt/rcc/_qxServer.qrc
