include(./qxService.pri)

DEFINES += _QX_SERVICE_MODE_CLIENT

CONFIG(debug, debug|release) {
OBJECTS_DIR = ./debug/debug_client/
TARGET = qxServiceClientd
} else {
OBJECTS_DIR = ./release/release_client/
TARGET = qxServiceClient
} # CONFIG(debug, debug|release)
