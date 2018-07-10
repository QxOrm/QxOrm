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

#ifndef _QX_SQL_GENERATOR_H_
#define _QX_SQL_GENERATOR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxDao/QxSqlGenerator/IxSqlGenerator.h>

#include <QxDao/QxSqlGenerator/QxSqlGenerator_Standard.h>
#include <QxDao/QxSqlGenerator/QxSqlGenerator_MySQL.h>
#include <QxDao/QxSqlGenerator/QxSqlGenerator_Oracle.h>
#include <QxDao/QxSqlGenerator/QxSqlGenerator_PostgreSQL.h>
#include <QxDao/QxSqlGenerator/QxSqlGenerator_SQLite.h>
#include <QxDao/QxSqlGenerator/QxSqlGenerator_MSSQLServer.h>

#endif // _QX_SQL_GENERATOR_H_
