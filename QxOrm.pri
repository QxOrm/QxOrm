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

######################
# Globals Parameters #
######################

CONFIG += debug_and_release
CONFIG += precompile_header
DEPENDPATH += .
INCLUDEPATH += .
QT += network
QT += xml
QT += sql
MOC_DIR = ./qt/moc
RCC_DIR = ./qt/rcc/src
UI_DIR = ./qt/ui
UI_HEADERS_DIR = ./qt/ui/include
UI_SOURCES_DIR = ./qt/ui/src

#############################
# Compiler / Linker Options #
#############################

win32 {
CONFIG(debug, debug|release) {
} else {
DEFINES += NDEBUG
QMAKE_LFLAGS += /OPT:NOREF
} # CONFIG(debug, debug|release)
} # win32

#######################
# Externals Libraries #
#######################

win32 {
LIBS += -L"D:/Dvlp/_Libs/Boost/lib"
} # win32

unix {
LIBS += -L"/usr/lib"
} # unix

win32 {
CONFIG(debug, debug|release) {
LIBS += -l"boost_serialization-vc90-mt-gd-1_42"
} else {
LIBS += -l"boost_serialization-vc90-mt-1_42"
} # CONFIG(debug, debug|release)
} # win32

unix {
CONFIG(debug, debug|release) {
LIBS += -l"boost_serialization-mt-d"
} else {
LIBS += -l"boost_serialization-mt"
} # CONFIG(debug, debug|release)
} # unix
