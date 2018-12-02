#################################################################################################
## File created by QxEntityEditor 1.2.1 (2018/11/28 12:31) : please, do NOT modify this file ! ##
#################################################################################################

include($$PWD/../../../QxOrm.pri)

TEMPLATE = lib
CONFIG += dll
DEFINES += _BUILDING_CHILDMODELSAVINGBUG
INCLUDEPATH += $$PWD/../../../include
DESTDIR = $$PWD/bin/

CONFIG(debug, debug|release) {
TARGET = ChildModelSavingBugd
} else {
TARGET = ChildModelSavingBug
} # CONFIG(debug, debug|release)

LIBS += -L"$$PWD/../../../lib$${LIBDIR}"

CONFIG(debug, debug|release) {
LIBS += -l"QxOrmd"
} else {
LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)

include($$PWD/ChildModelSavingBug.gen.pri)

!contains(DEFINES, _QX_UNITY_BUILD) {
SOURCES += $$PWD/src/ChildModelSavingBug_main.gen.cpp
} # !contains(DEFINES, _QX_UNITY_BUILD)
