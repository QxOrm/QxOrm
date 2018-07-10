/****************************************************************************
**
** http://www.qxorm.com/
** Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software
**
** Commercial Usage
** Licensees holding valid commercial QxOrm licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Lionel Marty
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met : http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, or
** if you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_SQL_GENERATOR_MSSQLSERVER_H_
#define _QX_SQL_GENERATOR_MSSQLSERVER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlGenerator_MSSQLServer.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief SQL generator for Microsoft SQL Server database
 */

#include <QxDao/QxSqlGenerator/QxSqlGenerator_Standard.h>

namespace qx {
namespace dao {
namespace detail {

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::QxSqlGenerator_MSSQLServer : SQL generator for Microsoft SQL Server database
 */
class QX_DLL_EXPORT QxSqlGenerator_MSSQLServer : public QxSqlGenerator_Standard
{

public:

   QxSqlGenerator_MSSQLServer();
   virtual ~QxSqlGenerator_MSSQLServer();

   virtual void init();
   virtual QString getLimit(const QxSqlLimit * pLimit) const;
   virtual void resolveLimit(QSqlQuery & query, const QxSqlLimit * pLimit) const;
   virtual void postProcess(QString & sql, const QxSqlLimit * pLimit) const;

private:

   void initSqlTypeByClassName() const;

};

typedef qx_shared_ptr<QxSqlGenerator_MSSQLServer> QxSqlGenerator_MSSQLServer_ptr;

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _QX_SQL_GENERATOR_MSSQLSERVER_H_
