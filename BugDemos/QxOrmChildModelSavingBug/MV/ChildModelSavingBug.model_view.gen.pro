#################################################################################################
## File created by QxEntityEditor 1.2.1 (2018/11/28 12:31) : please, do NOT modify this file ! ##
#################################################################################################

include($$PWD/../../../QxOrm.pri)

TEMPLATE = lib
CONFIG += dll
DEFINES += _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
INCLUDEPATH += $$PWD/../../../include
DESTDIR = $$PWD/bin/

LIBS += -L"$$PWD/../../../lib"
LIBS += -L"$$PWD/../C/bin"

CONFIG(debug, debug|release) {
LIBS += -l"QxOrmd"
LIBS += -l"ChildModelSavingBugd"
} else {
LIBS += -l"QxOrm"
LIBS += -l"ChildModelSavingBug"
} # CONFIG(debug, debug|release)

CONFIG(debug, debug|release) {
TARGET = ChildModelSavingBugModeld
} else {
TARGET = ChildModelSavingBugModel
} # CONFIG(debug, debug|release)

include($$PWD/ChildModelSavingBug.model_view.gen.pri)

!contains(DEFINES, _QX_UNITY_BUILD) {
SOURCES += $$PWD/src/ChildModelSavingBug_main.model_view.gen.cpp
} # !contains(DEFINES, _QX_UNITY_BUILD)
