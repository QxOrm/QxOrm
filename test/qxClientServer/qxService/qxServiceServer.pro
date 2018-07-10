include(./qxService.pri)

CONFIG(debug, debug|release) {
OBJECTS_DIR = ./debug/debug_server/
TARGET = qxServiceServerd
} else {
OBJECTS_DIR = ./release/release_server/
TARGET = qxServiceServer
} # CONFIG(debug, debug|release)
