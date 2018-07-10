include(../../../QxOrm.pri)

TEMPLATE = lib
CONFIG += dll
DEFINES += _BUILDING_QX_SERVICE
INCLUDEPATH += ../../../../QxOrm/include/
DESTDIR = ../../../../QxOrm/test/_bin/
LIBS += -L"../../../../QxOrm/test/_bin"

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER = ./include/precompiled.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

CONFIG(debug, debug|release) {
LIBS += -l"QxOrmd"
} else {
LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)

HEADERS += ./include/precompiled.h
HEADERS += ./include/export.h
HEADERS += ./include/service/server_infos.h
HEADERS += ./include/service/user_service.h
HEADERS += ./include/business_object/user.h
HEADERS += ./include/business_object/user_search.h
HEADERS += ./include/dao/user_manager.h

SOURCES += ./src/service/server_infos.cpp
SOURCES += ./src/service/user_service.cpp
SOURCES += ./src/business_object/user.cpp
SOURCES += ./src/business_object/user_search.cpp
SOURCES += ./src/dao/user_manager.cpp
SOURCES += ./src/main.cpp
