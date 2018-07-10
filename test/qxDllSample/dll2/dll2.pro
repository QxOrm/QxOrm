include(../../../QxOrm.pri)

TEMPLATE = lib
CONFIG += dll
DEFINES += _QX_BUILDING_DLL2
INCLUDEPATH += ../../../../QxOrm/include/
DESTDIR = ../../../../QxOrm/test/_bin/
QT += gui

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER = ./include/precompiled.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

CONFIG(debug, debug|release) {
TARGET = dll2d
} else {
TARGET = dll2
} # CONFIG(debug, debug|release)

LIBS += -L"../../../../QxOrm/test/_bin"

CONFIG(debug, debug|release) {
LIBS += -l"QxOrmd"
LIBS += -l"dll1d"
} else {
LIBS += -l"QxOrm"
LIBS += -l"dll1"
} # CONFIG(debug, debug|release)

HEADERS += ./include/precompiled.h
HEADERS += ./include/export.h
HEADERS += ./include/CUser.h
HEADERS += ./include/CTestAll.h
HEADERS += ./include/Bar.h
HEADERS += ./include/Foo.h
HEADERS += ./include/BaseClassTrigger.h

SOURCES += ./qx/CUser.qx.cpp
SOURCES += ./qx/CTestAll.qx.cpp
SOURCES += ./qx/Bar.qx.cpp
SOURCES += ./qx/Foo.qx.cpp
SOURCES += ./qx/BaseClassTrigger.qx.cpp

SOURCES += ./src/CUser.cpp
SOURCES += ./src/CTestAll.cpp
SOURCES += ./src/Bar.cpp
SOURCES += ./src/Foo.cpp
SOURCES += ./src/BaseClassTrigger.cpp
SOURCES += ./src/main.cpp
