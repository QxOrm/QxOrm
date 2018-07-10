include(../../../QxOrm.pri)

TEMPLATE = lib
CONFIG += dll
DEFINES += _QX_BUILDING_DLL1
INCLUDEPATH += ../../../../QxOrm/include/
DESTDIR = ../../../../QxOrm/test/_bin/

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER = ./include/precompiled.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

CONFIG(debug, debug|release) {
TARGET = dll1d
} else {
TARGET = dll1
} # CONFIG(debug, debug|release)

LIBS += -L"../../../../QxOrm/test/_bin"

CONFIG(debug, debug|release) {
LIBS += -l"QxOrmd"
} else {
LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)

HEADERS += ./include/precompiled.h
HEADERS += ./include/export.h
HEADERS += ./include/CPerson.h
HEADERS += ./include/TestQtProperty.h
HEADERS += ./include/QxPersistable.h

SOURCES += ./qx/CPerson.qx.cpp

SOURCES += ./src/CPerson.cpp
SOURCES += ./src/TestQtProperty.cpp
SOURCES += ./src/QxPersistable.cpp
SOURCES += ./src/main.cpp
