cmake_minimum_required(VERSION 3.15)

project(qxBlogRestApi LANGUAGES CXX)

include(../../QxOrm.cmake)

if(NOT _QX_NO_JSON)

if(NOT _QX_NO_GUI)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql Gui Widgets Quick Qml REQUIRED)
else() # _QX_NO_GUI
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql REQUIRED)
endif() # _QX_NO_GUI

option(_QX_TEST_WITH_MONGODB "If you enable _QX_TEST_WITH_MONGODB option, then persistent classes of 'qxBlogRestApi' project change definition, identifiers as 'QString' instead of 'long' to support MongoDB (used to create Docker images)" OFF)

if(_QX_TEST_WITH_MONGODB)
   add_definitions(-D_QX_TEST_WITH_MONGODB)
endif() # _QX_TEST_WITH_MONGODB

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_DEBUG_POSTFIX "d")

set(HEADERS
    ./include/precompiled.h
    ./include/export.h
    ./include/author.h
    ./include/blog.h
    ./include/category.h
    ./include/comment.h
   )

set(SRCS
    ./src/author.cpp
    ./src/blog.cpp
    ./src/category.cpp
    ./src/comment.cpp
    ./src/main.cpp
   )

set(QRCS
    ./qt/rcc/qxBlogRestApi.qrc
   )

if(COMMAND qt_add_resources)
qt_add_resources(QRCS_HDRS ${QRCS})
else() # (COMMAND qt_add_resources)
qt5_add_resources(QRCS_HDRS ${QRCS})
endif() # (COMMAND qt_add_resources)

add_executable(qxBlogRestApi ${SRCS} ${HEADERS} ${QRCS_HDRS})

target_compile_definitions(qxBlogRestApi PRIVATE -D_BUILDING_QX_BLOG)

if(COMMAND target_precompile_headers)
   target_precompile_headers(qxBlogRestApi PRIVATE ./include/precompiled.h)
endif() # (COMMAND target_precompile_headers)

if(NOT _QX_NO_GUI)
target_link_libraries(qxBlogRestApi ${QX_LIBRARIES} QxOrm Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Qml)
else() # _QX_NO_GUI
target_link_libraries(qxBlogRestApi ${QX_LIBRARIES} QxOrm)
endif() # _QX_NO_GUI

set_target_properties(qxBlogRestApi PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                      RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../_bin"
                     )

set_target_properties(qxBlogRestApi PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

else() # _QX_NO_JSON

message(STATUS "qxBlogRestApi project not loaded because _QX_NO_JSON option is defined (QxOrm REST API requires JSON serialization)")

endif() # _QX_NO_JSON
