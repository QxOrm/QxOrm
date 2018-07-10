include(../../QxOrm.pri)

TEMPLATE = app
DEFINES += _BUILDING_QX_BLOG
INCLUDEPATH += ../../../QxOrm/include/
DESTDIR = ../../../QxOrm/test/_bin/
LIBS += -L"../../../QxOrm/test/_bin"
QT += gui

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER = ./include/precompiled.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

greaterThan(QT_MAJOR_VERSION, 4) {
QT += widgets
QT += quick
QT += qml
} else {
QT += declarative
}

CONFIG(debug, debug|release) {
TARGET = qxBlogModelViewd
LIBS += -l"QxOrmd"
} else {
TARGET = qxBlogModelView
LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)

HEADERS += ./include/precompiled.h
HEADERS += ./include/export.h
HEADERS += ./include/author.h
HEADERS += ./include/blog.h
HEADERS += ./include/category.h
HEADERS += ./include/comment.h

HEADERS += ./include/model_view_from_qxee/author.model_view.gen.h
HEADERS += ./include/model_view_from_qxee/blog.model_view.gen.h
HEADERS += ./include/model_view_from_qxee/category.model_view.gen.h
HEADERS += ./include/model_view_from_qxee/comment.model_view.gen.h

SOURCES += ./src/author.cpp
SOURCES += ./src/blog.cpp
SOURCES += ./src/category.cpp
SOURCES += ./src/comment.cpp
SOURCES += ./src/main.cpp

SOURCES += ./src/model_view_from_qxee/author.model_view.gen.cpp
SOURCES += ./src/model_view_from_qxee/blog.model_view.gen.cpp
SOURCES += ./src/model_view_from_qxee/category.model_view.gen.cpp
SOURCES += ./src/model_view_from_qxee/comment.model_view.gen.cpp

RESOURCES += ./qt/rcc/qxBlogModelView.qrc
