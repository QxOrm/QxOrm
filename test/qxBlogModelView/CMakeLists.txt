cmake_minimum_required(VERSION 3.1)

project(qxBlogModelView LANGUAGES CXX)

include(../../QxOrm.cmake)

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
    ./include/model_view_from_qxee/author.model_view.gen.h
    ./include/model_view_from_qxee/blog.model_view.gen.h
    ./include/model_view_from_qxee/category.model_view.gen.h
    ./include/model_view_from_qxee/comment.model_view.gen.h
   )

set(SRCS
    ./src/author.cpp
    ./src/blog.cpp
    ./src/category.cpp
    ./src/comment.cpp
    ./src/main.cpp
    ./src/model_view_from_qxee/author.model_view.gen.cpp
    ./src/model_view_from_qxee/blog.model_view.gen.cpp
    ./src/model_view_from_qxee/category.model_view.gen.cpp
    ./src/model_view_from_qxee/comment.model_view.gen.cpp
   )

set(QRCS
    ./qt/rcc/qxBlogModelView.qrc
   )

qt5_add_resources(QRCS_HDRS ${QRCS})

add_executable(qxBlogModelView ${SRCS} ${HEADERS} ${QRCS_HDRS})

target_compile_definitions(qxBlogModelView PRIVATE -D_BUILDING_QX_BLOG)

target_link_libraries(qxBlogModelView ${QX_LIBRARIES} QxOrm Qt5::Gui Qt5::Widgets Qt5::Quick Qt5::Qml)

set_target_properties(qxBlogModelView PROPERTIES
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

set_target_properties(qxBlogModelView PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
