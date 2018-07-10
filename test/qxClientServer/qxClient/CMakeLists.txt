cmake_minimum_required(VERSION 3.1)

project(qxClient LANGUAGES CXX)

include(../../../QxOrm.cmake)

if(_QX_ENABLE_QT_NETWORK)

find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_DEBUG_POSTFIX "d")

set(HEADERS
    ./include/precompiled.h
    ./include/export.h
    ./include/main_dlg.h
   )

set(SRCS
    ./src/main_dlg.cpp
    ./src/main.cpp
   )

set(UIS
    ./qt/ui/qxClient.ui
   )

qt5_wrap_ui(UIS_HDRS ${UIS})

add_executable(qxClient ${SRCS} ${HEADERS} ${UIS_HDRS})

target_compile_definitions(qxClient PRIVATE -D_BUILDING_QX_CLIENT)

target_link_libraries(qxClient ${QX_LIBRARIES} Qt5::Gui Qt5::Widgets QxOrm qxServiceClient)

set_target_properties(qxClient PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                      RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../_bin"
                     )

set_target_properties(qxClient PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

else() # _QX_ENABLE_QT_NETWORK

message(STATUS "qxClient project not loaded because _QX_ENABLE_QT_NETWORK option not enabled (QxOrm QxService module is disabled)")

endif() # _QX_ENABLE_QT_NETWORK
