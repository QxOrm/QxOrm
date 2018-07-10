include(../../../QxOrm.pri)

TEMPLATE = app
DEFINES += _QX_BUILDING_EXE
INCLUDEPATH += ../../../../QxOrm/include/
DESTDIR = ../../../../QxOrm/test/_bin/

QT += gui
greaterThan(QT_MAJOR_VERSION, 4) { QT += widgets }

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER = ./include/precompiled.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

macx:CONFIG-=app_bundle

CONFIG(debug, debug|release) {
TARGET = exed
} else {
TARGET = exe
} # CONFIG(debug, debug|release)

LIBS += -L"../../../../QxOrm/test/_bin"

CONFIG(debug, debug|release) {
LIBS += -l"QxOrmd"
LIBS += -l"dll1d"
LIBS += -l"dll2d"
} else {
LIBS += -l"QxOrm"
LIBS += -l"dll1"
LIBS += -l"dll2"
} # CONFIG(debug, debug|release)

HEADERS += ./include/precompiled.h
HEADERS += ./include/export.h

SOURCES += ./src/main.cpp
