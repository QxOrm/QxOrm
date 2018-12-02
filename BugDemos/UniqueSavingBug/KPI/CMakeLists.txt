#################################################################################################
## File created by QxEntityEditor 1.2.3 (2018/11/30 09:04) : please, do NOT modify this file ! ##
#################################################################################################

cmake_minimum_required(VERSION 3.1)

project(KPI LANGUAGES CXX)

if(NOT TARGET QxOrm)
   add_subdirectory("../../../" ./QxOrm)
endif() # NOT TARGET QxOrm

include("../../../QxOrm.cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_DEBUG_POSTFIX "d")

set(KPI_HEADERS
    ./include/KPI_precompiled_header.gen.h
    ./include/KPI_export.gen.h
    ./include/kpi_KPI.gen.h
    ./include/kpi_MetaData.gen.h
    ./include/kpi_MetaDataKey.gen.h
    ./include/kpi_Type.gen.h
    ./custom/include/kpi_KPI.h
    ./custom/include/kpi_MetaData.h
    ./custom/include/kpi_MetaDataKey.h
    ./custom/include/kpi_Type.h
   )

if(_QX_UNITY_BUILD)

   set(KPI_SRCS ./src/KPI_all.gen.cpp)

else() # _QX_UNITY_BUILD

   set(KPI_SRCS
       ./src/kpi_KPI.gen.cpp
       ./src/kpi_MetaData.gen.cpp
       ./src/kpi_MetaDataKey.gen.cpp
       ./src/kpi_Type.gen.cpp
       ./custom/src/kpi_KPI.cpp
       ./custom/src/kpi_MetaData.cpp
       ./custom/src/kpi_MetaDataKey.cpp
       ./custom/src/kpi_Type.cpp
       ./src/KPI_main.gen.cpp
      )

endif() # _QX_UNITY_BUILD

add_library(KPI SHARED ${KPI_SRCS} ${KPI_HEADERS})

target_compile_definitions(KPI PRIVATE -D_BUILDING_KPI)

target_link_libraries(KPI ${QX_LIBRARIES} QxOrm)

set_target_properties(KPI PROPERTIES
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

qx_auto_source_group("${KPI_SRCS};${KPI_HEADERS}")
