cmake_minimum_required(VERSION 3.1)

project(qxBlogRestApi LANGUAGES CXX)

include(../../QxOrm.cmake)

if(NOT _QX_NO_JSON)

find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Qml REQUIRED)

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

qt5_add_resources(QRCS_HDRS ${QRCS})

add_executable(qxBlogRestApi ${SRCS} ${HEADERS} ${QRCS_HDRS})

target_compile_definitions(qxBlogRestApi PRIVATE -D_BUILDING_QX_BLOG)

target_link_libraries(qxBlogRestApi ${QX_LIBRARIES} QxOrm Qt5::Gui Qt5::Widgets Qt5::Quick Qt5::Qml)

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
