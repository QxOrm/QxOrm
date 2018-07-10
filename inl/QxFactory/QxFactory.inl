/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4094)
#endif // _MSC_VER

#include "../../include/QxSerialize/QxSerialize.h"

#ifndef QX_REGISTER_FACTORY_HPP
#define QX_REGISTER_FACTORY_COMPLEX_CLASS_NAME_HPP(className, classNameFormatted) \
extern qx::QxFactory< className > G_QX_REGISTER_FACTORY_##classNameFormatted;
#define QX_REGISTER_FACTORY_HPP(className) \
QX_REGISTER_FACTORY_COMPLEX_CLASS_NAME_HPP(className, className)
#endif // QX_REGISTER_FACTORY_HPP

#ifndef QX_REGISTER_FACTORY_CPP
#define QX_REGISTER_FACTORY_COMPLEX_CLASS_NAME_CPP(className, classNameFormatted) \
qx::QxFactory< className > G_QX_REGISTER_FACTORY_##classNameFormatted(QString(#className));
#define QX_REGISTER_FACTORY_CPP(className) \
QX_REGISTER_FACTORY_COMPLEX_CLASS_NAME_CPP(className, className)
#endif // QX_REGISTER_FACTORY_CPP

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER
