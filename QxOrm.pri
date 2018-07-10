#############################################################################
##
## http://www.qxorm.com/
## http://sourceforge.net/projects/qxorm/
## Original file by Lionel Marty
##
## This file is part of the QxOrm library
##
## This software is provided 'as-is', without any express or implied
## warranty. In no event will the authors be held liable for any
## damages arising from the use of this software.
##
## GNU Lesser General Public License Usage
## This file must be used under the terms of the GNU Lesser
## General Public License version 2.1 as published by the Free Software
## Foundation and appearing in the file 'license.lgpl.txt' included in the
## packaging of this file.  Please review the following information to
## ensure the GNU Lesser General Public License version 2.1 requirements
## will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## If you have questions regarding the use of this file, please contact :
## contact@qxorm.com
##
#############################################################################

############################
# Qt GUI module dependency #
############################

# To remove QtGui dependency :
#   1- in "./include/QxCommon/QxConfig.h" file, modify "_QX_ENABLE_QT_GUI_DEPENDENCY" constant to : "#define _QX_ENABLE_QT_GUI_DEPENDENCY 0"
#   2- in "./QxOrm.pri" file, add the following line : "QT -= gui"

# QT -= gui

###############################
# boost Library Configuration #
###############################

QX_BOOST_INCLUDE_PATH = $$quote(D:/Dvlp/_Libs/Boost/1_42/include)
QX_BOOST_LIB_PATH = $$quote(D:/Dvlp/_Libs/Boost/1_42/lib_shared)
QX_BOOST_LIB_SERIALIZATION_DEBUG = "boost_serialization-vc90-mt-gd-1_42"
QX_BOOST_LIB_SERIALIZATION_RELEASE = "boost_serialization-vc90-mt-1_42"

unix {
QX_BOOST_INCLUDE_PATH = $$quote(/usr/include)
QX_BOOST_LIB_PATH = $$quote(/usr/lib)
QX_BOOST_LIB_SERIALIZATION_DEBUG = "boost_serialization-mt-d"
QX_BOOST_LIB_SERIALIZATION_RELEASE = "boost_serialization-mt"
} # unix

######################
# Globals Parameters #
######################

CONFIG += debug_and_release
CONFIG += precompile_header
DEPENDPATH += .
INCLUDEPATH += ./include
INCLUDEPATH += $${QX_BOOST_INCLUDE_PATH}
QT += network
QT += xml
QT += sql
MOC_DIR = ./qt/moc
RCC_DIR = ./qt/rcc/src

gui {
UI_DIR = ./qt/ui
UI_HEADERS_DIR = ./qt/ui/include
UI_SOURCES_DIR = ./qt/ui/src
} # gui

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
win32-g++: QMAKE_LFLAGS += -export-all-symbols
} # win32

#######################
# Externals Libraries #
#######################

LIBS += -L$${QX_BOOST_LIB_PATH}

CONFIG(debug, debug|release) {
LIBS += -l$${QX_BOOST_LIB_SERIALIZATION_DEBUG}
} else {
LIBS += -l$${QX_BOOST_LIB_SERIALIZATION_RELEASE}
} # CONFIG(debug, debug|release)
