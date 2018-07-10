include(../../QxOrm.pri)

TEMPLATE = app
DEFINES += _BUILDING_QX_BLOG
INCLUDEPATH += ../../../QxOrm/include/
DESTDIR = ../../../QxOrm/test/_bin/
LIBS += -L"../../../QxOrm/test/_bin"

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER = ./include/precompiled.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

## Should be defined in QxOrm.pri config file
DEFINES += _QX_CPP_11_SMART_PTR
DEFINES += _QX_CPP_11_CONTAINER
DEFINES += _QX_CPP_11_TUPLE

CONFIG += c++11

macx:CONFIG-=app_bundle

CONFIG(debug, debug|release) {
TARGET = qxBlogCpp11d
LIBS += -l"QxOrmd"
} else {
TARGET = qxBlogCpp11
LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)

HEADERS += ./include/precompiled.h
HEADERS += ./include/export.h
HEADERS += ./include/author.h
HEADERS += ./include/blog.h
HEADERS += ./include/category.h
HEADERS += ./include/comment.h

SOURCES += ./src/author.cpp
SOURCES += ./src/blog.cpp
SOURCES += ./src/category.cpp
SOURCES += ./src/comment.cpp
SOURCES += ./src/main.cpp
