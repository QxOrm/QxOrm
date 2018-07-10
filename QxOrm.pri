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

###########################################
# QxOrm library requires a C++11 compiler #
###########################################

# Qt framework requires a C++11 compiler since version Qt 5.7
# So for all previous Qt versions, we need to define CONFIG += c++11
# Please note that QxOrm library doesn't require a full compliant C++11 compiler : for example, QxOrm library can be built and used with MSVC 2012, GCC 4.5 or Clang 3.2

lessThan(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
# QMAKE_CXXFLAGS += -std=c++11
} else {
equals(QT_MAJOR_VERSION, 5) {
lessThan(QT_MINOR_VERSION, 7) {
CONFIG += c++11
} # lessThan(QT_MINOR_VERSION, 7)
} # equals(QT_MAJOR_VERSION, 5)
} # lessThan(QT_MAJOR_VERSION, 5)

###########################################
# Boost Header-Only Dependency (optional) #
###########################################

# Since QxOrm 1.4.4, QxOrm library doesn't depend on boost framework anymore (the boost dependency has been fully removed, replaced by some C++11 features)
# So QxOrm library is now a pure Qt library which depends only on QtCore and QtSql by default
# QxOrm library still supports some boost classes (boost smart-pointers, unordered containers, boost::optional, etc...) : you have to define _QX_ENABLE_BOOST compilation option to enable these features

# DEFINES += _QX_ENABLE_BOOST

############################################################
# Boost Serialization Shared Library Dependency (optional) #
############################################################

# By default, QxOrm library doesn't depend on boost::serialization shared library, but it is possible to enable it defining the compilation option : _QX_ENABLE_BOOST_SERIALIZATION
# Without this compilation option, QxOrm is a much lighter library, generated binaries based on QxOrm are smaller, and QxOrm depends only on Qt binaries (and boost header files)
# But in this case, serialization features are limited (based on QDataStream and QJson engines) : limited qx::clone, no XML serialization, limited binary serialization, limited QxService module (network transactions), etc...
# If you define _QX_ENABLE_BOOST_SERIALIZATION compilation option, then boost serialization is enabled with XML and binary engine by default (see _QX_ENABLE_BOOST_SERIALIZATION_BINARY and _QX_ENABLE_BOOST_SERIALIZATION_XML for more details)
# Note : if you are not using serialization functions in projects based on QxOrm library, then you can define or not _QX_ENABLE_BOOST_SERIALIZATION compilation option without changing any line of your source code
# Other note : to persist containers in database (not relationships, for example : std::vector<int>), without _QX_ENABLE_BOOST_SERIALIZATION it is stored as QByteArray (based on QDataStream engine), with _QX_ENABLE_BOOST_SERIALIZATION it is stored as XML (based on boost serialization XML engine) => so be careful, in this case it is not compatible

# DEFINES += _QX_ENABLE_BOOST_SERIALIZATION

contains(DEFINES, _QX_ENABLE_BOOST_SERIALIZATION) {
!contains(DEFINES, _QX_ENABLE_BOOST) {
DEFINES += _QX_ENABLE_BOOST
} # !contains(DEFINES, _QX_ENABLE_BOOST)
} # contains(DEFINES, _QX_ENABLE_BOOST_SERIALIZATION)

######################################
# Boost Library Configuration / Path #
######################################

# In this section, it's necessary to specify boost directories (lib + include) and boost serialization module name (debug + release) :
#  - QX_BOOST_INCLUDE_PATH (required) : your boost include path (by default, environment variable named BOOST_INCLUDE)
#  - QX_BOOST_LIB_PATH (optional) : your boost lib path (by default, environment variable named BOOST_LIB)
#  - QX_BOOST_LIB_SERIALIZATION_DEBUG (optional) : your boost serialization module name in debug mode (by default, environment variable named BOOST_LIB_SERIALIZATION_DEBUG)
#  - QX_BOOST_LIB_SERIALIZATION_RELEASE (optional) : your boost serialization module name in release mode (by default, environment variable named BOOST_LIB_SERIALIZATION_RELEASE)
#  - QX_BOOST_LIB_WIDE_SERIALIZATION_DEBUG (optional) : your boost wide serialization module name in debug mode (default is empty)
#  - QX_BOOST_LIB_WIDE_SERIALIZATION_RELEASE (optional) : your boost wide serialization module name in release mode (default is empty)
# Note : if _QX_ENABLE_BOOST_SERIALIZATION is not defined, then the only option used is QX_BOOST_INCLUDE_PATH (other options are ignored, QxOrm just needs to know how to find boost header files)

contains(DEFINES, _QX_ENABLE_BOOST) {
isEmpty(QX_BOOST_INCLUDE_PATH) { QX_BOOST_INCLUDE_PATH = $$quote($$(BOOST_INCLUDE)) }
contains(DEFINES, _QX_ENABLE_BOOST_SERIALIZATION) {

isEmpty(QX_BOOST_LIB_PATH) { QX_BOOST_LIB_PATH = $$quote($$(BOOST_LIB)) }
isEmpty(QX_BOOST_LIB_SERIALIZATION_DEBUG) { QX_BOOST_LIB_SERIALIZATION_DEBUG = "$$(BOOST_LIB_SERIALIZATION_DEBUG)" }
isEmpty(QX_BOOST_LIB_SERIALIZATION_RELEASE) { QX_BOOST_LIB_SERIALIZATION_RELEASE = "$$(BOOST_LIB_SERIALIZATION_RELEASE)" }
# isEmpty(QX_BOOST_LIB_WIDE_SERIALIZATION_DEBUG) { QX_BOOST_LIB_WIDE_SERIALIZATION_DEBUG = "$$(BOOST_LIB_WIDE_SERIALIZATION_DEBUG)" }
# isEmpty(QX_BOOST_LIB_WIDE_SERIALIZATION_RELEASE) { QX_BOOST_LIB_WIDE_SERIALIZATION_RELEASE = "$$(BOOST_LIB_WIDE_SERIALIZATION_RELEASE)" }

} # contains(DEFINES, _QX_ENABLE_BOOST_SERIALIZATION)
} # contains(DEFINES, _QX_ENABLE_BOOST)

####################################
# Check Boost Configuration / Path #
####################################

contains(DEFINES, _QX_ENABLE_BOOST) {
isEmpty(QX_BOOST_INCLUDE_PATH) {
error("Error in QxOrm.pri configuration file : QX_BOOST_INCLUDE_PATH variable is empty, please define in QX_BOOST_INCLUDE_PATH variable where boost header files *.hpp are located, or define an environment variable named BOOST_INCLUDE (read QxOrm.pri configuration file for more details)")
} # isEmpty(QX_BOOST_INCLUDE_PATH)
QX_CHECK_BOOST_INCLUDE_PATH = $${QX_BOOST_INCLUDE_PATH}/boost/version.hpp
greaterThan(QT_MAJOR_VERSION, 4) {
QX_CHECK_BOOST_INCLUDE_PATH = $$clean_path($${QX_CHECK_BOOST_INCLUDE_PATH})
} else { # greaterThan(QT_MAJOR_VERSION, 4)
QX_CHECK_BOOST_INCLUDE_PATH = $$replace(QX_CHECK_BOOST_INCLUDE_PATH, \\\\, /)
QX_CHECK_BOOST_INCLUDE_PATH = $$replace(QX_CHECK_BOOST_INCLUDE_PATH, \\, /)
} # greaterThan(QT_MAJOR_VERSION, 4)
!exists($${QX_CHECK_BOOST_INCLUDE_PATH}) {
message("Check if boost header file exists : $${QX_CHECK_BOOST_INCLUDE_PATH}")
error("Error in QxOrm.pri configuration file : QX_BOOST_INCLUDE_PATH variable is not valid ($${QX_BOOST_INCLUDE_PATH}), please define in QX_BOOST_INCLUDE_PATH variable where boost header files *.hpp are located, or define an environment variable named BOOST_INCLUDE (read QxOrm.pri configuration file for more details)")
} # !exists($${QX_CHECK_BOOST_INCLUDE_PATH})
} # contains(DEFINES, _QX_ENABLE_BOOST)

############################
# Qt GUI Module Dependency #
############################

# By default, QxOrm library doesn't depend on Qt GUI shared library
# If you want to serialize Qt GUI objects (QBrush, QColor, QFont, QImage, QMatrix, QPicture, QPixmap, QRegion), then you have to define _QX_ENABLE_QT_GUI compilation option

# DEFINES += _QX_ENABLE_QT_GUI

contains(DEFINES, _QX_ENABLE_QT_GUI) {
QT += gui
} # contains(DEFINES, _QX_ENABLE_QT_GUI)

################################
# Qt Network Module Dependency #
################################

# By default, QxOrm library doesn't depend on Qt Network shared library => it means that QxService module (network transactions to transfer your persistent layer) is not enabled by default
# To enable this feature, just define the compilation option : _QX_ENABLE_QT_NETWORK
# For more details about QxService module, a tutorial (qxClientServer) is available on QxOrm website : http://www.qxorm.com/qxorm_en/tutorial_2.html

# DEFINES += _QX_ENABLE_QT_NETWORK

contains(DEFINES, _QX_ENABLE_QT_NETWORK) {
QT += network
} # contains(DEFINES, _QX_ENABLE_QT_NETWORK)

############################################
# QxOrm Library Boost Serialization Engine #
############################################

# In this section, you can enable/disable different boost serialization engine, by default, there is :
#  - _QX_ENABLE_BOOST_SERIALIZATION_BINARY
#  - _QX_ENABLE_BOOST_SERIALIZATION_XML
# Note : if _QX_ENABLE_BOOST_SERIALIZATION is not defined, then these options are not used

contains(DEFINES, _QX_ENABLE_BOOST_SERIALIZATION) {

DEFINES += _QX_ENABLE_BOOST_SERIALIZATION_BINARY
DEFINES += _QX_ENABLE_BOOST_SERIALIZATION_XML

# DEFINES += _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC
# DEFINES += _QX_ENABLE_BOOST_SERIALIZATION_TEXT
# DEFINES += _QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY
# DEFINES += _QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY
# DEFINES += _QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT
# DEFINES += _QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML

} # contains(DEFINES, _QX_ENABLE_BOOST_SERIALIZATION)

#####################
# Global Parameters #
#####################

QT += sql
CONFIG += debug_and_release
DEPENDPATH += .
INCLUDEPATH += ./include
MOC_DIR = ./qt/moc
RCC_DIR = ./qt/rcc/src
UI_DIR = ./qt/ui
UI_HEADERS_DIR = ./qt/ui/include
UI_SOURCES_DIR = ./qt/ui/src

contains(DEFINES, _QX_ENABLE_BOOST) {
INCLUDEPATH += $${QX_BOOST_INCLUDE_PATH}
} # contains(DEFINES, _QX_ENABLE_BOOST)

CONFIG(debug, debug|release) {
DEFINES += _QX_MODE_DEBUG
} else {
DEFINES += _QX_MODE_RELEASE
} # CONFIG(debug, debug|release)

#######################
# Externals Libraries #
#######################

# If _QX_ENABLE_BOOST_SERIALIZATION compilation option is not defined, then there is no external dependency : QxOrm library depends only on Qt binaries

contains(DEFINES, _QX_ENABLE_BOOST_SERIALIZATION) {

LIBS += -L$${QX_BOOST_LIB_PATH}

CONFIG(debug, debug|release) {
LIBS += -l$${QX_BOOST_LIB_SERIALIZATION_DEBUG}
!isEmpty(QX_BOOST_LIB_WIDE_SERIALIZATION_DEBUG) { LIBS += -l$${QX_BOOST_LIB_WIDE_SERIALIZATION_DEBUG} }
} else {
LIBS += -l$${QX_BOOST_LIB_SERIALIZATION_RELEASE}
!isEmpty(QX_BOOST_LIB_WIDE_SERIALIZATION_RELEASE) { LIBS += -l$${QX_BOOST_LIB_WIDE_SERIALIZATION_RELEASE} }
} # CONFIG(debug, debug|release)

} # contains(DEFINES, _QX_ENABLE_BOOST_SERIALIZATION)

#####################################
# Output Binaries Size Optimization #
#####################################

# To compile faster classes registered into QxOrm context and to produce smaller binaries size, you should :
# - not define the compilation option _QX_ENABLE_BOOST_SERIALIZATION to disable boost::serialization dependency ;
# - or define only the _QX_ENABLE_BOOST_SERIALIZATION_BINARY compilation option (and disable the default _QX_ENABLE_BOOST_SERIALIZATION_XML compilation option) ;
# - if you need the XML engine, you could consider enable only the _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC compilation option ;
# - under Windows, use MSVC++ instead of MinGW GCC ;
# - with GCC compiler, use the following optimizations options (uncomment it) :

# QMAKE_CXXFLAGS_RELEASE += -ffunction-sections -fdata-sections -Os -pipe
# QMAKE_CFLAGS_RELEASE += -ffunction-sections -fdata-sections -Os -pipe
# QMAKE_LFLAGS_RELEASE += -Wl,--gc-sections -s

#########################
# No Precompiled Header #
#########################

# Some versions of MinGW on Windows have a bug with large precompiled headers (for example, MinGW GCC 4.8)
# More detais about this problem here : https://gcc.gnu.org/bugzilla/show_bug.cgi?id=56926
# And here : http://stackoverflow.com/questions/10841306/cc1plus-exe-crash-when-using-large-precompiled-header-file
# To fix the crash during compilation, you have to disable precompiled headers : just enable the following compilation option _QX_NO_PRECOMPILED_HEADER
# Note : there is a side effect disabling precompiled headers => compilation times are considerably increased !
# Other note : to reduce compilation times, it is recommended to define _QX_UNITY_BUILD compilation option

# DEFINES += _QX_NO_PRECOMPILED_HEADER

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
CONFIG += precompile_header
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

################################
# No RTTI C++ Type Information #
################################

# You can build QxOrm library without C++ RTTI type information defining the compilation option : _QX_NO_RTTI
# With _QX_NO_RTTI compilation option, dynamic_cast and typeid from QxOrm library are removed
# Note : you cannot define this compilation option if you enable boost serialization feature (_QX_ENABLE_BOOST_SERIALIZATION)
# Other note : it seems that on Unix system, CONFIG += rtti_off doesn't add the compilation flag -fno-rtti for GCC (there is a Qt bug report here : https://bugreports.qt.io/browse/QTBUG-26595), so in this case, just add the compilation flag to QMAKE_CXXFLAGS and QMAKE_CFLAGS variables

# DEFINES += _QX_NO_RTTI

contains(DEFINES, _QX_NO_RTTI) {
CONFIG -= rtti
CONFIG += rtti_off

# unix {
# QMAKE_CXXFLAGS += -fno-rtti
# QMAKE_CFLAGS += -fno-rtti
# } # unix
} # contains(DEFINES, _QX_NO_RTTI)

##############################
# QxOrm Library Static Build #
##############################

# To create only 1 EXE including Qt, boost serialization and QxOrm libraries without any dependency :
#   1- be sure to build Qt and boost::serialization using static mode
#   2- in "./QxOrm.pri" file, add the following line : "DEFINES += _QX_STATIC_BUILD"
#   3- BUT PLEASE : in your program, add a "readme.txt" file and a "about my program..." window to indicate that your application is based on Qt, boost and QxOrm libraries !
# Note : on Windows, static mode works with only 1 EXE, it will never work mixing DLL and EXE (because of singleton implementation of boost::serialization and QxOrm libraries)

# DEFINES += _QX_STATIC_BUILD

################################
# No JSON Serialization Engine #
################################

# QxOrm library supports JSON serialization : this feature is enabled by default if you are not working with Qt4 (JSON engine requires Qt5)
# To disable this feature, you can define the compilation option : _QX_NO_JSON
# Using _QX_NO_JSON compilation option, qx::serialization::json namespace will be not available

# DEFINES += _QX_NO_JSON

##########################################
# Unity Build : Reduce Compilation Times #
##########################################

# QxOrm provides a way to compile the library faster using the Unity Build system : http://stackoverflow.com/questions/543697/include-all-cpp-files-into-a-single-compilation-unit
# To enable QxOrm Unity Build feature, just define the _QX_UNITY_BUILD compilation option
# This compilation option changes the make file : instead of compiling each *.cpp files separately, QxOrm is compiled using a unique 'all.cpp' file (which #include all QxOrm *.cpp files)
# Note : your environment must have enough memory to support this compilation option, and your compiler must support it too, otherwise your compiler can crash with a memory error
# Other note : C++ projects generated by QxEntityEditor application support this compilation option => this is a way to reduce compilation times of C++ persistent classes generated by QxEntityEditor
# Other note : if you define _QX_UNITY_BUILD compilation option, it can be interesting too to define the _QX_NO_PRECOMPILED_HEADER compilation option to reduce compilation times (it depends on number of other *.cpp files to compile, like moc files for example)

# DEFINES += _QX_UNITY_BUILD

contains(DEFINES, _QX_UNITY_BUILD) {
win32-msvc*: QMAKE_CXXFLAGS += -bigobj
# win32-g++: QMAKE_CXXFLAGS += -Wa,-mbig-obj
} # contains(DEFINES, _QX_UNITY_BUILD)

##########################################
# More Efficient Qt QString Construction #
##########################################

# Qt provides some optimizations for QString class (construction, concatenation, etc...)
# More details about these optimizations are available on Qt web site : http://doc.qt.io/qt-5/qstring.html#more-efficient-string-construction
# To enable these optimizations, you can define QT_USE_QSTRINGBUILDER compilation option

# DEFINES *= QT_USE_QSTRINGBUILDER
