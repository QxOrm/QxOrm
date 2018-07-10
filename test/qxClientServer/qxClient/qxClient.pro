include(../../../QxOrm.pri)

TEMPLATE = app
DEFINES += _BUILDING_QX_CLIENT
INCLUDEPATH += ../../../../QxOrm/include/
DESTDIR = ../../../../QxOrm/test/_bin/
LIBS += -L"../../../../QxOrm/test/_bin"
PRECOMPILED_HEADER = ./include/precompiled.h

CONFIG(debug, debug|release) {
TARGET = qxClientd
LIBS += -l"QxOrmd"
LIBS += -l"qxServiceClientd"
} else {
TARGET = qxClient
LIBS += -l"QxOrm"
LIBS += -l"qxServiceClient"
} # CONFIG(debug, debug|release)

HEADERS += ./include/precompiled.h
HEADERS += ./include/export.h
HEADERS += ./include/main_dlg.h

SOURCES += ./src/main_dlg.cpp
SOURCES += ./src/main.cpp

FORMS += ./qt/ui/qxClient.ui
