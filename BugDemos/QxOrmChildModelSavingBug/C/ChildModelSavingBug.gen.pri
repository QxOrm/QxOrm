#################################################################################################
## File created by QxEntityEditor 1.2.1 (2018/11/28 12:17) : please, do NOT modify this file ! ##
#################################################################################################

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER += $$PWD/include/ChildModelSavingBug_precompiled_header.gen.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

HEADERS += $$PWD/include/ChildModelSavingBug_precompiled_header.gen.h
HEADERS += $$PWD/include/ChildModelSavingBug_export.gen.h

HEADERS += $$PWD/include/Child.gen.h
HEADERS += $$PWD/include/Grandchild.gen.h
HEADERS += $$PWD/include/Parent.gen.h

HEADERS += $$PWD/custom/include/Child.h
HEADERS += $$PWD/custom/include/Grandchild.h
HEADERS += $$PWD/custom/include/Parent.h

contains(DEFINES, _QX_UNITY_BUILD) {

SOURCES += $$PWD/src/ChildModelSavingBug_all.gen.cpp

} else {

SOURCES += $$PWD/src/Child.gen.cpp
SOURCES += $$PWD/src/Grandchild.gen.cpp
SOURCES += $$PWD/src/Parent.gen.cpp

SOURCES += $$PWD/custom/src/Child.cpp
SOURCES += $$PWD/custom/src/Grandchild.cpp
SOURCES += $$PWD/custom/src/Parent.cpp

} # contains(DEFINES, _QX_UNITY_BUILD)

include($$PWD/custom/ChildModelSavingBug.pri)
