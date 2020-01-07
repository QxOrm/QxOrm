include(../../QxOrm.pri)

!contains(DEFINES, _QX_ENABLE_MONGODB) {
error(unable to use QxOrm MongoDB database driver : please define _QX_ENABLE_MONGODB compilation option in QxOrm.pri configuration file)
} # !contains(DEFINES, _QX_ENABLE_MONGODB)

TEMPLATE = app
DEFINES += _BUILDING_QX_BLOG
INCLUDEPATH += ../../../QxOrm/include/
DESTDIR = ../../../QxOrm/test/_bin/
LIBS += -L"../../../QxOrm/lib"

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER = ./include/precompiled.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

macx:CONFIG-=app_bundle

CONFIG(debug, debug|release) {
TARGET = qxBlogMongoDBd
LIBS += -l"QxOrmd"
} else {
TARGET = qxBlogMongoDB
LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)

HEADERS += ./include/precompiled.h
HEADERS += ./include/export.h
HEADERS += ./include/author.h
HEADERS += ./include/blog.h
HEADERS += ./include/category.h
HEADERS += ./include/comment.h
HEADERS += ./include/TestQtProperty.h

SOURCES += ./src/author.cpp
SOURCES += ./src/blog.cpp
SOURCES += ./src/category.cpp
SOURCES += ./src/comment.cpp
SOURCES += ./src/TestQtProperty.cpp
SOURCES += ./src/main.cpp
