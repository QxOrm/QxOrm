#################################################################################################
## File created by QxEntityEditor 1.2.1 (2018/11/28 12:31) : please, do NOT modify this file ! ##
#################################################################################################

cmake_minimum_required(VERSION 3.1)

project(ChildModelSavingBugModel LANGUAGES CXX)

if(NOT TARGET QxOrm)
   add_subdirectory("../../../" ./QxOrm)
endif() # NOT TARGET QxOrm
if(NOT TARGET ChildModelSavingBug)
   add_subdirectory("../C/" ./ChildModelSavingBug)
endif() # NOT TARGET ChildModelSavingBug

include("../../../QxOrm.cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_DEBUG_POSTFIX "d")

set(CHILDMODELSAVINGBUG_MODEL_HEADERS
    ./include/ChildModelSavingBug_precompiled_header.model_view.gen.h
    ./include/ChildModelSavingBug_export.model_view.gen.h
    ./include/Child.model_view.gen.h
    ./include/Grandchild.model_view.gen.h
    ./include/Parent.model_view.gen.h
    ./custom/include/Child.model_view.h
    ./custom/include/Grandchild.model_view.h
    ./custom/include/Parent.model_view.h
   )

if(_QX_UNITY_BUILD)

   set(CHILDMODELSAVINGBUG_MODEL_SRCS ./src/ChildModelSavingBug_all.model_view.gen.cpp)

else() # _QX_UNITY_BUILD

   set(CHILDMODELSAVINGBUG_MODEL_SRCS
       ./src/Child.model_view.gen.cpp
       ./src/Grandchild.model_view.gen.cpp
       ./src/Parent.model_view.gen.cpp
       ./custom/src/Child.model_view.cpp
       ./custom/src/Grandchild.model_view.cpp
       ./custom/src/Parent.model_view.cpp
       ./src/ChildModelSavingBug_main.model_view.gen.cpp
      )

endif() # _QX_UNITY_BUILD

add_library(ChildModelSavingBugModel SHARED ${CHILDMODELSAVINGBUG_MODEL_SRCS} ${CHILDMODELSAVINGBUG_MODEL_HEADERS})

target_compile_definitions(ChildModelSavingBugModel PRIVATE -D_BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG )

target_link_libraries(ChildModelSavingBugModel ${QX_LIBRARIES} QxOrm ChildModelSavingBug )

set_target_properties(ChildModelSavingBugModel PROPERTIES
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

qx_auto_source_group("${CHILDMODELSAVINGBUG_MODEL_SRCS};${CHILDMODELSAVINGBUG_MODEL_HEADERS}")
