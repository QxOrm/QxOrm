include(../../../QxOrm.pri)

!contains(DEFINES, _QX_ENABLE_QT_NETWORK) {
error(unable to use QxOrm QxService module : please define _QX_ENABLE_QT_NETWORK compilation option in QxOrm.pri configuration file)
} # !contains(DEFINES, _QX_ENABLE_QT_NETWORK)

TEMPLATE = app
DEFINES += _BUILDING_QX_CLIENT
INCLUDEPATH += ../../../../QxOrm/include/
DESTDIR = ../../../../QxOrm/test/_bin/
LIBS += -L"../../../../QxOrm/test/_bin"

QT += gui
greaterThan(QT_MAJOR_VERSION, 4) { QT += widgets }

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER = ./include/precompiled.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

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
