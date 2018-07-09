/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
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
