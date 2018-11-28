#################################################################################################
## File created by QxEntityEditor 1.2.1 (2018/11/28 12:18) : please, do NOT modify this file ! ##
#################################################################################################

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER += $$PWD/include/ChildModelSavingBug_precompiled_header.model_view.gen.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

HEADERS += $$PWD/include/ChildModelSavingBug_precompiled_header.model_view.gen.h
HEADERS += $$PWD/include/ChildModelSavingBug_export.model_view.gen.h

HEADERS += $$PWD/include/Child.model_view.gen.h
HEADERS += $$PWD/include/Grandchild.model_view.gen.h
HEADERS += $$PWD/include/Parent.model_view.gen.h

HEADERS += $$PWD/custom/include/Child.model_view.h
HEADERS += $$PWD/custom/include/Grandchild.model_view.h
HEADERS += $$PWD/custom/include/Parent.model_view.h

contains(DEFINES, _QX_UNITY_BUILD) {

SOURCES += $$PWD/src/ChildModelSavingBug_all.model_view.gen.cpp

} else {

SOURCES += $$PWD/src/Child.model_view.gen.cpp
SOURCES += $$PWD/src/Grandchild.model_view.gen.cpp
SOURCES += $$PWD/src/Parent.model_view.gen.cpp

SOURCES += $$PWD/custom/src/Child.model_view.cpp
SOURCES += $$PWD/custom/src/Grandchild.model_view.cpp
SOURCES += $$PWD/custom/src/Parent.model_view.cpp

} # contains(DEFINES, _QX_UNITY_BUILD)

include($$PWD/custom/ChildModelSavingBug.model_view.pri)
