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

############################################################
# Boost Serialization Shared Library Dependency (optional) #
############################################################

# By default, QxOrm library doesn't depend on boost::serialization shared library, but it is possible to enable it defining the compilation option : _QX_ENABLE_BOOST_SERIALIZATION
# Without this compilation option, QxOrm is a much lighter library, generated binaries based on QxOrm are smaller, and QxOrm depends only on Qt binaries (and boost header files)
# But in this case, serialization features are limited (based on QDataStream Qt engine) : limited qx::clone, no qx::dump, no XML serialization, limited binary serialization, limited QxService module (network transactions), etc...
# If you define _QX_ENABLE_BOOST_SERIALIZATION compilation option, then boost serialization is enabled with XML and binary engine by default (see _QX_ENABLE_BOOST_SERIALIZATION_BINARY and _QX_ENABLE_BOOST_SERIALIZATION_XML for more details)
# Note : if you are not using serialization functions in projects based on QxOrm library, then you can define or not _QX_ENABLE_BOOST_SERIALIZATION compilation option without changing any line of your source code
# Other note : to persist containers in database (not relationships, for example : std::vector<int>), without _QX_ENABLE_BOOST_SERIALIZATION it is stored as QByteArray (based on QDataStream engine), with _QX_ENABLE_BOOST_SERIALIZATION it is stored as XML (based on boost serialization XML engine) => so be careful, in this case it is not compatible

# DEFINES += _QX_ENABLE_BOOST_SERIALIZATION

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

isEmpty(QX_BOOST_INCLUDE_PATH) { QX_BOOST_INCLUDE_PATH = $$quote($$(BOOST_INCLUDE)) }

contains(DEFINES, _QX_ENABLE_BOOST_SERIALIZATION) {

isEmpty(QX_BOOST_LIB_PATH) { QX_BOOST_LIB_PATH = $$quote($$(BOOST_LIB)) }
isEmpty(QX_BOOST_LIB_SERIALIZATION_DEBUG) { QX_BOOST_LIB_SERIALIZATION_DEBUG = "$$(BOOST_LIB_SERIALIZATION_DEBUG)" }
isEmpty(QX_BOOST_LIB_SERIALIZATION_RELEASE) { QX_BOOST_LIB_SERIALIZATION_RELEASE = "$$(BOOST_LIB_SERIALIZATION_RELEASE)" }
# isEmpty(QX_BOOST_LIB_WIDE_SERIALIZATION_DEBUG) { QX_BOOST_LIB_WIDE_SERIALIZATION_DEBUG = "$$(BOOST_LIB_WIDE_SERIALIZATION_DEBUG)" }
# isEmpty(QX_BOOST_LIB_WIDE_SERIALIZATION_RELEASE) { QX_BOOST_LIB_WIDE_SERIALIZATION_RELEASE = "$$(BOOST_LIB_WIDE_SERIALIZATION_RELEASE)" }

} # contains(DEFINES, _QX_ENABLE_BOOST_SERIALIZATION)

####################################
# Check Boost Configuration / Path #
####################################

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

#######################################
# C++11 Smart Pointers And Containers #
#######################################

# By default, QxOrm library supports smart pointers and containers of Qt library and boost library : QHash, QList, QSharedPointer, boost::shared_ptr, boost::unordered_map, etc...
# QxOrm library supports also by default containers of previous C++03 standard library : std::vector, std::list, std::map, std::set
# If you want to enable smart pointers and containers of the new C++11 standard library, you can define the compilation options _QX_CPP_11_SMART_PTR, _QX_CPP_11_CONTAINER and _QX_CPP_11_TUPLE :
# - With _QX_CPP_11_SMART_PTR : std::unique_ptr, std::shared_ptr, std::weak_ptr
# - With _QX_CPP_11_CONTAINER : std::unordered_map, std::unordered_set, std::unordered_multimap, std::unordered_multiset
# - With _QX_CPP_11_TUPLE : std::tuple

# CONFIG += c++11
# DEFINES += _QX_CPP_11_SMART_PTR
# DEFINES += _QX_CPP_11_CONTAINER
# DEFINES += _QX_CPP_11_TUPLE

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
INCLUDEPATH += $${QX_BOOST_INCLUDE_PATH}
MOC_DIR = ./qt/moc
RCC_DIR = ./qt/rcc/src
UI_DIR = ./qt/ui
UI_HEADERS_DIR = ./qt/ui/include
UI_SOURCES_DIR = ./qt/ui/src

CONFIG(debug, debug|release) {
DEFINES += _QX_MODE_DEBUG
} else {
DEFINES += _QX_MODE_RELEASE
} # CONFIG(debug, debug|release)

#############################
# Compiler / Linker Options #
#############################

win32 {
CONFIG(debug, debug|release) {
} else {
DEFINES += NDEBUG
win32-msvc2005: QMAKE_LFLAGS += /OPT:NOREF
win32-msvc2008: QMAKE_LFLAGS += /OPT:NOREF
win32-msvc2010: QMAKE_LFLAGS += /OPT:NOREF
} # CONFIG(debug, debug|release)
win32-g++: QMAKE_LFLAGS += -Wl,-export-all-symbols -Wl,-enable-auto-import
} # win32

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
# Other note : _QX_NO_RTTI requires at least boost 1.57 (because boost::any has removed typeid dependency since boost 1.57)
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
