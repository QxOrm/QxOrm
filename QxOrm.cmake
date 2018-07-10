#############################################################################
##
## http://www.qxorm.com/
## Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
##
## This file is part of the QxOrm library
##
## This software is provided 'as-is', without any express or implied
## warranty. In no event will the authors be held liable for any
## damages arising from the use of this software
##
## Commercial Usage
## Licensees holding valid commercial QxOrm licenses may use this file in
## accordance with the commercial license agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and Lionel Marty
##
## GNU General Public License Usage
## Alternatively, this file may be used under the terms of the GNU
## General Public License version 3.0 as published by the Free Software
## Foundation and appearing in the file 'license.gpl3.txt' included in the
## packaging of this file. Please review the following information to
## ensure the GNU General Public License version 3.0 requirements will be
## met : http://www.gnu.org/copyleft/gpl.html
##
## If you are unsure which license is appropriate for your use, or
## if you have questions regarding the use of this file, please contact :
## contact@qxorm.com
##
#############################################################################

# QxOrm.cmake is the configuration file for QxOrm library if you are using CMake as build tool
# QxOrm.cmake file is equivalent to QxOrm.pri configuration file for qmake projects
# QxOrm.cmake file should be included by all projects which depend on QxOrm library
# QxOrm.cmake file contains some settings to enable/disable QxOrm library features
# QxOrm.cmake file also tries to find Qt and boost libraries required by QxOrm library

if(NOT QXORM_CMAKE_CONFIG_FILE_INCLUDED)
set(QXORM_CMAKE_CONFIG_FILE_INCLUDED TRUE)

######################
# QxOrm Library Path #
######################

set(QXORM_DIR ${CMAKE_CURRENT_LIST_DIR})
set(QXORM_INCLUDE_DIR ${QXORM_DIR}/include)
include_directories(${QXORM_INCLUDE_DIR})

######################################
# Boost Library Configuration / Path #
######################################

set(QX_BOOST_DIR "" CACHE STRING "Define where boost library is located, or leave QX_BOOST_DIR parameter empty and define a BOOST_ROOT environment variable")

if(NOT QX_BOOST_DIR STREQUAL "")
   set(BOOST_ROOT ${QX_BOOST_DIR})
endif()

find_package(Boost 1.38.0 REQUIRED)

if(NOT Boost_FOUND)
   message(FATAL_ERROR "boost library not found : please define where boost library is located using QX_BOOST_DIR parameter, or leave QX_BOOST_DIR parameter empty and define a BOOST_ROOT environment variable")
endif()

include_directories(${Boost_INCLUDE_DIRS})

###########################
# Qt Library Dependencies #
###########################

set(QX_QT_DIR "" CACHE STRING "Define where Qt library is located if CMake doesn't find it by default")

if(NOT QX_QT_DIR STREQUAL "")
   set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QX_QT_DIR})
endif()

find_package(Qt5Core REQUIRED)
find_package(Qt5Sql REQUIRED)

set(QX_LIBRARIES Qt5::Core Qt5::Sql)

##############################
# Build Mode Debug / Release #
##############################

set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
             $<$<CONFIG:Debug>:_QX_MODE_DEBUG>
             $<$<CONFIG:Release>:_QX_MODE_RELEASE>
             $<$<CONFIG:RelWithDebInfo>:_QX_MODE_RELEASE>
             $<$<CONFIG:MinSizeRel>:_QX_MODE_RELEASE>
             $<$<CONFIG:None>:_QX_MODE_RELEASE>
             $<$<CONFIG:>:_QX_MODE_RELEASE>
            )

#########################
# No Precompiled Header #
#########################

# By default, CMake doesn't support precompiled headers natively, so _QX_NO_PRECOMPILED_HEADER compilation option is defined with CMake
# There is a project named 'cotire' (compile time reducer) which is not deployed with CMake but can be used to support precompiled headers, more details here : https://github.com/sakra/cotire
# Moreover, some versions of MinGW on Windows have a bug with large precompiled headers (for example, MinGW GCC 4.8)
# More detais about this problem here : https://gcc.gnu.org/bugzilla/show_bug.cgi?id=56926
# And here : http://stackoverflow.com/questions/10841306/cc1plus-exe-crash-when-using-large-precompiled-header-file
# To fix the crash during compilation, you have to disable precompiled headers : just enable the following compilation option _QX_NO_PRECOMPILED_HEADER
# Note : there is a side effect disabling precompiled headers => compilation times are considerably increased !
# Other note : to reduce compilation times, it is recommended to define _QX_UNITY_BUILD compilation option

add_definitions(-D_QX_NO_PRECOMPILED_HEADER)

##############################
# QxOrm Library Static Build #
##############################

# To create only 1 EXE including Qt, boost serialization (optional) and QxOrm libraries without any dependency :
#   1- be sure to build Qt and boost::serialization using static mode
#   2- in "./QxOrm.cmake" file, enable the _QX_STATIC_BUILD option
#   3- BUT PLEASE : in your program, add a "readme.txt" file and a "about my program..." window to indicate that your application is based on Qt, boost and QxOrm libraries !
# Note : on Windows, static mode works with only 1 EXE, it will never work mixing DLL and EXE (because of singleton implementation of boost::serialization and QxOrm libraries)

option(_QX_STATIC_BUILD "Enable _QX_STATIC_BUILD option to build QxOrm as a static library" OFF)

if(_QX_STATIC_BUILD)
   add_definitions(-D_QX_STATIC_BUILD)
endif()

############################################################
# Boost Serialization Shared Library Dependency (optional) #
############################################################

# By default, QxOrm library doesn't depend on boost::serialization shared library, but it is possible to enable it defining the compilation option : _QX_ENABLE_BOOST_SERIALIZATION
# Without this compilation option, QxOrm is a much lighter library, generated binaries based on QxOrm are smaller, and QxOrm depends only on Qt binaries (and boost header files)
# But in this case, serialization features are limited (based on QDataStream and QJson engines) : limited qx::clone, no XML serialization, limited binary serialization, limited QxService module (network transactions), etc...
# If you define _QX_ENABLE_BOOST_SERIALIZATION compilation option, then boost serialization is enabled with XML and binary engine by default (see _QX_ENABLE_BOOST_SERIALIZATION_BINARY and _QX_ENABLE_BOOST_SERIALIZATION_XML for more details)
# Note : if you are not using serialization functions in projects based on QxOrm library, then you can define or not _QX_ENABLE_BOOST_SERIALIZATION compilation option without changing any line of your source code
# Other note : to persist containers in database (not relationships, for example : std::vector<int>), without _QX_ENABLE_BOOST_SERIALIZATION it is stored as QByteArray (based on QDataStream engine), with _QX_ENABLE_BOOST_SERIALIZATION it is stored as XML (based on boost serialization XML engine) => so be careful, in this case it is not compatible

option(_QX_ENABLE_BOOST_SERIALIZATION "If you enable _QX_ENABLE_BOOST_SERIALIZATION option, then QxOrm library will provide a serialization engine based on boost::serialization (you have to build boost::serialization shared libray to use this feature)" OFF)

if(_QX_ENABLE_BOOST_SERIALIZATION)

   add_definitions(-D_QX_ENABLE_BOOST_SERIALIZATION)

   option(_QX_ENABLE_BOOST_SERIALIZATION_BINARY "Enable boost::serialization binary engine" ON)
   option(_QX_ENABLE_BOOST_SERIALIZATION_XML "Enable boost::serialization XML engine" ON)
   option(_QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC "Enable boost::serialization polymorphic engine" OFF)
   option(_QX_ENABLE_BOOST_SERIALIZATION_TEXT "Enable boost::serialization text engine" OFF)
   option(_QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY "Enable boost::serialization portable binary engine" OFF)
   option(_QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY "Enable boost::serialization wide binary engine" OFF)
   option(_QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT "Enable boost::serialization wide text engine" OFF)
   option(_QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML "Enable boost::serialization wide XML engine" OFF)

   if(_QX_ENABLE_BOOST_SERIALIZATION_BINARY)
      add_definitions(-D_QX_ENABLE_BOOST_SERIALIZATION_BINARY)
   endif()

   if(_QX_ENABLE_BOOST_SERIALIZATION_XML)
      add_definitions(-D_QX_ENABLE_BOOST_SERIALIZATION_XML)
   endif()

   if(_QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC)
      add_definitions(-D_QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC)
   endif()

   if(_QX_ENABLE_BOOST_SERIALIZATION_TEXT)
      add_definitions(-D_QX_ENABLE_BOOST_SERIALIZATION_TEXT)
   endif()

   if(_QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY)
      add_definitions(-D_QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY)
   endif()

   if(_QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY)
      add_definitions(-D_QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY)
   endif()

   if(_QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT)
      add_definitions(-D_QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT)
   endif()

   if(_QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML)
      add_definitions(-D_QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML)
   endif()

   find_package(Boost 1.38.0 REQUIRED COMPONENTS serialization)

   if(NOT Boost_SERIALIZATION_FOUND)
      message(FATAL_ERROR "boost::serialization library not found (with _QX_ENABLE_BOOST_SERIALIZATION option enabled, QxOrm library depends on boost::serialization binary)")
   endif()

   set(QX_LIBRARIES ${QX_LIBRARIES} ${Boost_SERIALIZATION_LIBRARY})

endif() # _QX_ENABLE_BOOST_SERIALIZATION

############################
# Qt Gui Module Dependency #
############################

# By default, QxOrm library doesn't depend on Qt Gui shared library
# If you want to serialize Qt Gui objects (QBrush, QColor, QFont, QImage, QMatrix, QPicture, QPixmap, QRegion), then you have to define _QX_ENABLE_QT_GUI compilation option

option(_QX_ENABLE_QT_GUI "If you enable _QX_ENABLE_QT_GUI option, then QxOrm library will be able to serialize Qt Gui objects (QBrush, QColor, QFont, QImage, QMatrix, QPicture, QPixmap, QRegion)" OFF)

if(_QX_ENABLE_QT_GUI)
   add_definitions(-D_QX_ENABLE_QT_GUI)
   find_package(Qt5Gui REQUIRED)
   set(QX_LIBRARIES ${QX_LIBRARIES} Qt5::Gui)
endif() # _QX_ENABLE_QT_GUI

################################
# Qt Network Module Dependency #
################################

# By default, QxOrm library doesn't depend on Qt Network shared library => it means that QxService module (network transactions to transfer your persistent layer) is not enabled by default
# To enable this feature, just define the compilation option : _QX_ENABLE_QT_NETWORK
# For more details about QxService module, a tutorial (qxClientServer) is available on QxOrm website : http://www.qxorm.com/qxorm_en/tutorial_2.html

option(_QX_ENABLE_QT_NETWORK "If you enable _QX_ENABLE_QT_NETWORK option, then QxService module of QxOrm library will be available (network transactions to transfer persistent data layer)" OFF)

if(_QX_ENABLE_QT_NETWORK)
   add_definitions(-D_QX_ENABLE_QT_NETWORK)
   find_package(Qt5Network REQUIRED)
   set(QX_LIBRARIES ${QX_LIBRARIES} Qt5::Network)
endif() # _QX_ENABLE_QT_NETWORK

#######################################
# C++11 Smart Pointers And Containers #
#######################################

# By default, QxOrm library supports smart pointers and containers of Qt library and boost library : QHash, QList, QSharedPointer, boost::shared_ptr, boost::unordered_map, etc...
# QxOrm library supports also by default containers of previous C++03 standard library : std::vector, std::list, std::map, std::set
# If you want to enable smart pointers and containers of the new C++11 standard library, you can define the compilation options _QX_CPP_11_SMART_PTR, _QX_CPP_11_CONTAINER and _QX_CPP_11_TUPLE :
# - With _QX_CPP_11_SMART_PTR : std::unique_ptr, std::shared_ptr, std::weak_ptr
# - With _QX_CPP_11_CONTAINER : std::unordered_map, std::unordered_set, std::unordered_multimap, std::unordered_multiset
# - With _QX_CPP_11_TUPLE : std::tuple

option(_QX_ENABLE_CPP_11 "If you enable _QX_ENABLE_CPP_11 option, then QxOrm library will support C++11 types like smart-pointers (std::unique_ptr, std::shared_ptr, std::weak_ptr), containers (std::unordered_map, std::unordered_set, std::unordered_multimap, std::unordered_multiset) and tuple (std::tuple)" OFF)

if(_QX_ENABLE_CPP_11)
   set(CMAKE_CXX_STANDARD 11)
   add_definitions(-D_QX_CPP_11_SMART_PTR)
   add_definitions(-D_QX_CPP_11_CONTAINER)
   add_definitions(-D_QX_CPP_11_TUPLE)
endif() # _QX_ENABLE_CPP_11

################################
# No JSON Serialization Engine #
################################

# QxOrm library supports JSON serialization : this feature is enabled by default if you are not working with Qt4 (JSON engine requires Qt5)
# To disable this feature, you can define the compilation option : _QX_NO_JSON
# Using _QX_NO_JSON compilation option, qx::serialization::json namespace will be not available

option(_QX_NO_JSON "If you enable _QX_NO_JSON option, then QxOrm library will not provide JSON serialization engine" OFF)

if(_QX_NO_JSON)
   add_definitions(-D_QX_NO_JSON)
endif()

##########################################
# Unity Build : Reduce Compilation Times #
##########################################

# QxOrm provides a way to compile the library faster using the Unity Build system : http://stackoverflow.com/questions/543697/include-all-cpp-files-into-a-single-compilation-unit
# To enable QxOrm Unity Build feature, just define the _QX_UNITY_BUILD compilation option
# This compilation option changes the make file : instead of compiling each *.cpp files separately, QxOrm is compiled using a unique 'all.cpp' file (which #include all QxOrm *.cpp files)
# Note : your environment must have enough memory to support this compilation option, and your compiler must support it too, otherwise your compiler can crash with a memory error
# Other note : C++ projects generated by QxEntityEditor application support this compilation option => this is a way to reduce compilation times of C++ persistent classes generated by QxEntityEditor
# Other note : if you define _QX_UNITY_BUILD compilation option, it can be interesting too to define the _QX_NO_PRECOMPILED_HEADER compilation option to reduce compilation times (it depends on number of other *.cpp files to compile, like moc files for example)

option(_QX_UNITY_BUILD "If you enable _QX_UNITY_BUILD option, then QxOrm library will be built faster (using only 1 'all.cpp' source file)" OFF)

if(_QX_UNITY_BUILD)
   add_definitions(-D_QX_UNITY_BUILD)
   if(WIN32 AND MSVC)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -bigobj")
   elseif(WIN32 AND MINGW)
      # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
   endif() # WIN32 AND MSVC
endif() # _QX_UNITY_BUILD

#############################
# Compiler / Linker Options #
#############################

if(WIN32)
   if(MSVC)
      if(MSVC_VERSION LESS 1700)
         set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /OPT:NOREF")
      endif() # MSVC_VERSION LESS 1700
   elseif(MINGW)
         set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-export-all-symbols -Wl,-enable-auto-import")
   endif() # MSVC
endif() # WIN32

####################################################
# Macro To Source Group By Folder For MSVC / XCode #
####################################################

macro(qx_auto_source_group QX_ALL_FILES)
   foreach(QX_FILE ${QX_ALL_FILES})
      get_filename_component(QX_PARENT_DIR "${QX_FILE}" DIRECTORY)
      string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" QX_GROUP "${QX_PARENT_DIR}")
      string(REPLACE "./" "" QX_GROUP "${QX_GROUP}")
      string(REPLACE "/" "\\" QX_GROUP "${QX_GROUP}")
      source_group("${QX_GROUP}" FILES "${QX_FILE}")
   endforeach()
endmacro() # qx_auto_source_group

endif() # QXORM_CMAKE_CONFIG_FILE_INCLUDED
