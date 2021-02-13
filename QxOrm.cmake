#############################################################################
##
## https://www.qxorm.com/
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

###########################################
# QxOrm library requires a C++11 compiler #
###########################################

# Qt framework requires a C++11 compiler since version Qt 5.7
# So for all previous Qt versions, we need to define CONFIG += c++11
# Please note that QxOrm library doesn't require a full compliant C++11 compiler : for example, QxOrm library can be built and used with MSVC 2012, GCC 4.5 or Clang 3.2

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

######################
# QxOrm Library Path #
######################

set(QXORM_DIR ${CMAKE_CURRENT_LIST_DIR})
set(QXORM_INCLUDE_DIR ${QXORM_DIR}/include)
include_directories(${QXORM_INCLUDE_DIR})

###########################################
# Boost Header-Only Dependency (optional) #
###########################################

# Since QxOrm 1.4.4, QxOrm library doesn't depend on boost framework anymore (the boost dependency has been fully removed, replaced by some C++11 features)
# So QxOrm library is now a pure Qt library which depends only on QtCore and QtSql by default
# QxOrm library still supports some boost classes (boost smart-pointers, unordered containers, boost::optional, etc...) : you have to define _QX_ENABLE_BOOST compilation option to enable these features

option(_QX_ENABLE_BOOST "If you enable _QX_ENABLE_BOOST option, then QxOrm library will support some boost header-only classes like boost::optional, boost::shared_ptr, boost::unordered_map, etc..." OFF)

######################################
# Boost Library Configuration / Path #
######################################

if(_QX_ENABLE_BOOST)

   add_definitions(-D_QX_ENABLE_BOOST)
   set(QX_BOOST_DIR "" CACHE STRING "Define where boost library is located, or leave QX_BOOST_DIR parameter empty and define a BOOST_ROOT environment variable")

   if(NOT QX_BOOST_DIR STREQUAL "")
      set(BOOST_ROOT ${QX_BOOST_DIR})
   endif()

   find_package(Boost 1.38.0 REQUIRED)

   if(NOT Boost_FOUND)
      message(FATAL_ERROR "boost library not found : please define where boost library is located using QX_BOOST_DIR parameter, or leave QX_BOOST_DIR parameter empty and define a BOOST_ROOT environment variable")
   endif()

   include_directories(${Boost_INCLUDE_DIRS})

endif() # _QX_ENABLE_BOOST

###########################
# Qt Library Dependencies #
###########################

set(QX_QT_DIR "" CACHE STRING "Define where Qt library is located if CMake doesn't find it by default")

if(NOT QX_QT_DIR STREQUAL "")
   set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QX_QT_DIR})
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)

if(_QX_ENABLE_QT_GUI AND _QX_ENABLE_QT_NETWORK)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql Gui Network REQUIRED)
set(QX_LIBRARIES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Network)
elseif(_QX_ENABLE_QT_GUI)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql Gui REQUIRED)
set(QX_LIBRARIES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Gui)
elseif(_QX_ENABLE_QT_NETWORK)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql Network REQUIRED)
set(QX_LIBRARIES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Network)
else() # (_QX_ENABLE_QT_GUI AND _QX_ENABLE_QT_NETWORK)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql REQUIRED)
set(QX_LIBRARIES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql)
endif() # (_QX_ENABLE_QT_GUI AND _QX_ENABLE_QT_NETWORK)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif() # (${QT_VERSION_MAJOR} GREATER_EQUAL 6)

#######################################
# MongoDB Driver Library Dependencies #
#######################################

option(_QX_ENABLE_MONGODB "If you enable _QX_ENABLE_MONGODB option, then QxOrm library will be able to use mongoc driver to store all QxOrm registered classes in a MongoDB database" OFF)

if(_QX_ENABLE_MONGODB)

   add_definitions(-D_QX_ENABLE_MONGODB)

   set(QX_MONGOC_INCLUDE "$ENV{MONGOC_INCLUDE}")
   if(NOT QX_MONGOC_INCLUDE STREQUAL "")

      include_directories("$ENV{BSON_INCLUDE}")
      include_directories("${QX_MONGOC_INCLUDE}")

      link_directories("$ENV{BSON_LIB}")
      link_directories("$ENV{MONGOC_LIB}")

      set(QX_LIBRARIES ${QX_LIBRARIES} bson-1.0 mongoc-1.0)

   else() # (NOT QX_MONGOC_INCLUDE STREQUAL "")

      find_package(libbson-1.0 REQUIRED)
      find_package(libmongoc-1.0 REQUIRED)

      include_directories(${BSON_INCLUDE_DIRS})
      include_directories(${MONGOC_INCLUDE_DIRS})

      set(QX_LIBRARIES ${QX_LIBRARIES} ${BSON_LIBRARIES} ${MONGOC_LIBRARIES})

   endif() # (NOT QX_MONGOC_INCLUDE STREQUAL "")

endif() # _QX_ENABLE_MONGODB

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

if(NOT COMMAND target_precompile_headers)
add_definitions(-D_QX_NO_PRECOMPILED_HEADER)
endif() # (NOT COMMAND target_precompile_headers)

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

if(_QX_ENABLE_BOOST)

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
endif() # _QX_ENABLE_BOOST

############################
# Qt Gui Module Dependency #
############################

# By default, QxOrm library doesn't depend on Qt Gui shared library
# If you want to serialize Qt Gui objects (QBrush, QColor, QFont, QImage, QMatrix, QPicture, QPixmap, QRegion), then you have to define _QX_ENABLE_QT_GUI compilation option

option(_QX_ENABLE_QT_GUI "If you enable _QX_ENABLE_QT_GUI option, then QxOrm library will be able to serialize Qt Gui objects (QBrush, QColor, QFont, QImage, QMatrix, QPicture, QPixmap, QRegion)" OFF)

if(_QX_ENABLE_QT_GUI)
   add_definitions(-D_QX_ENABLE_QT_GUI)
endif() # _QX_ENABLE_QT_GUI

################################
# Qt Network Module Dependency #
################################

# By default, QxOrm library doesn't depend on Qt Network shared library => it means that QxService module (network transactions to transfer your persistent layer) and QxHttpServer module (standalone multi-threaded HTTP 1.1 web server) are not enabled by default
# To enable these features (QxService and QxHttpServer modules), just define the compilation option : _QX_ENABLE_QT_NETWORK
# For more details about QxService module, a tutorial (qxClientServer) is available on QxOrm website : https://www.qxorm.com/qxorm_en/tutorial_2.html
# For more details about QxHttpServer module, a manual is available on QxOrm website : https://www.qxorm.com/qxorm_en/manual.html#manual_96

option(_QX_ENABLE_QT_NETWORK "If you enable _QX_ENABLE_QT_NETWORK option, then QxService and QxHttpServer modules of QxOrm library will be available (network transactions to transfer persistent data layer + standalone multi-threaded HTTP 1.1 web server)" OFF)

if(_QX_ENABLE_QT_NETWORK)
   add_definitions(-D_QX_ENABLE_QT_NETWORK)
endif() # _QX_ENABLE_QT_NETWORK

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

##########################################
# More Efficient Qt QString Construction #
##########################################

# Qt provides some optimizations for QString class (construction, concatenation, etc...)
# More details about these optimizations are available on Qt web site : http://doc.qt.io/qt-5/qstring.html#more-efficient-string-construction
# To enable these optimizations, you can define QT_USE_QSTRINGBUILDER compilation option

option(_QX_USE_QSTRINGBUILDER "If you enable _QX_USE_QSTRINGBUILDER option, then QxOrm library will define QT_USE_QSTRINGBUILDER compilation option of Qt library to provide some optimizations with QString class" OFF)

if(_QX_USE_QSTRINGBUILDER)
   add_definitions(-DQT_USE_QSTRINGBUILDER)
endif()

#############################
# Compiler / Linker Options #
#############################

if(WIN32)
   if(MSVC)
      if(MSVC_VERSION LESS 1700)
         set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /OPT:NOREF")
      endif() # MSVC_VERSION LESS 1700
   elseif(MINGW)
         # For MinGW : we need to add these linker flags because of some issues to dll export extern template instantiations from shared library
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
