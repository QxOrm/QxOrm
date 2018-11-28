#################################################################################################
## File created by QxEntityEditor 1.2.1 (2018/11/28 12:31) : please, do NOT modify this file ! ##
#################################################################################################

cmake_minimum_required(VERSION 3.1)

project(ChildModelSavingBug LANGUAGES CXX)

if(NOT TARGET QxOrm)
   add_subdirectory("../../../" ./QxOrm)
endif() # NOT TARGET QxOrm

include("../../../QxOrm.cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_DEBUG_POSTFIX "d")

set(CHILDMODELSAVINGBUG_HEADERS
    ./include/ChildModelSavingBug_precompiled_header.gen.h
    ./include/ChildModelSavingBug_export.gen.h
    ./include/Child.gen.h
    ./include/Grandchild.gen.h
    ./include/Parent.gen.h
    ./custom/include/Child.h
    ./custom/include/Grandchild.h
    ./custom/include/Parent.h
   )

if(_QX_UNITY_BUILD)

   set(CHILDMODELSAVINGBUG_SRCS ./src/ChildModelSavingBug_all.gen.cpp)

else() # _QX_UNITY_BUILD

   set(CHILDMODELSAVINGBUG_SRCS
       ./src/Child.gen.cpp
       ./src/Grandchild.gen.cpp
       ./src/Parent.gen.cpp
       ./custom/src/Child.cpp
       ./custom/src/Grandchild.cpp
       ./custom/src/Parent.cpp
       ./src/ChildModelSavingBug_main.gen.cpp
      )

endif() # _QX_UNITY_BUILD

add_library(ChildModelSavingBug SHARED ${CHILDMODELSAVINGBUG_SRCS} ${CHILDMODELSAVINGBUG_HEADERS})

target_compile_definitions(ChildModelSavingBug PRIVATE -D_BUILDING_CHILDMODELSAVINGBUG)

target_link_libraries(ChildModelSavingBug ${QX_LIBRARIES} QxOrm)

set_target_properties(ChildModelSavingBug PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                      RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/bin"
                     )

qx_auto_source_group("${CHILDMODELSAVINGBUG_SRCS};${CHILDMODELSAVINGBUG_HEADERS}")
