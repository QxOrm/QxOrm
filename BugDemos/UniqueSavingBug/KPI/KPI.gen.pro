#################################################################################################
## File created by QxEntityEditor 1.2.3 (2018/12/02 15:06) : please, do NOT modify this file ! ##
#################################################################################################

include($$PWD/../../../QxOrm.pri)

TEMPLATE = lib
CONFIG += dll
DEFINES += _BUILDING_KPI
INCLUDEPATH += $$PWD/../../../include
DESTDIR = $$PWD/bin/

CONFIG(debug, debug|release) {
TARGET = KPId
} else {
TARGET = KPI
} # CONFIG(debug, debug|release)

LIBS += -L"$$PWD/../../../lib$${LIBDIR}"

CONFIG(debug, debug|release) {
LIBS += -l"QxOrmd"
} else {
LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)

include($$PWD/KPI.gen.pri)

!contains(DEFINES, _QX_UNITY_BUILD) {
SOURCES += $$PWD/src/KPI_main.gen.cpp
} # !contains(DEFINES, _QX_UNITY_BUILD)
