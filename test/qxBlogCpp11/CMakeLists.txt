cmake_minimum_required(VERSION 3.1)

project(qxBlogCpp11 LANGUAGES CXX)

include(../../QxOrm.cmake)

if(_QX_ENABLE_CPP_11)

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

add_executable(qxBlogCpp11 ${SRCS} ${HEADERS})

target_compile_definitions(qxBlogCpp11 PRIVATE -D_BUILDING_QX_BLOG)

target_link_libraries(qxBlogCpp11 ${QX_LIBRARIES} QxOrm)

set_target_properties(qxBlogCpp11 PROPERTIES
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

set_target_properties(qxBlogCpp11 PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

else() # _QX_ENABLE_CPP_11

message(STATUS "qxBlogCpp11 project not loaded because _QX_ENABLE_CPP_11 option not enabled (QxOrm C++11 features are disabled)")

endif() # _QX_ENABLE_CPP_11
