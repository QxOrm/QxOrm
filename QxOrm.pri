#############################################################################
##
## Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
## Contact: QxOrm France Information (contact@qxorm.com)
##
## This file is part of the QxOrm library
##
## Commercial Usage
## Licensees holding valid QxOrm Commercial licenses may use this file in
## accordance with the QxOrm Commercial License Agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and QxOrm France
##
## GNU General Public License Usage
## Alternatively, this file may be used under the terms of the GNU
## General Public License version 3.0 as published by the Free Software
## Foundation and appearing in the file 'license.gpl3.txt' included in the
## packaging of this file. Please review the following information to
## ensure the GNU General Public License version 3.0 requirements will be
## met: http://www.gnu.org/copyleft/gpl.html
##
## If you are unsure which license is appropriate for your use, please
## contact the support department at support@qxorm.com
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
LIBS += -l"boost_serialization-vc90-mt-gd-1_40"
} else {
LIBS += -l"boost_serialization-vc90-mt-1_40"
} # CONFIG(debug, debug|release)
} # win32

unix {
CONFIG(debug, debug|release) {
LIBS += -l"boost_serialization-mt-d"
} else {
LIBS += -l"boost_serialization-mt"
} # CONFIG(debug, debug|release)
} # unix
