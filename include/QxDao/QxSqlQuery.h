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

#ifndef _QX_SQL_QUERY_H_
#define _QX_SQL_QUERY_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtSql/qsqlquery.h>

#include "../../include/QxCollection/QxCollection.h"

namespace qx {

class QX_DLL_EXPORT QxSqlQuery
{

protected:

   QString m_sQuery;                               // Query sql with place-holder
   QxCollection<QString, QVariant> m_lstValue;     // Bind value in this array

public:

   QxSqlQuery() { ; }
   QxSqlQuery(const QString & sQuery) : m_sQuery(sQuery) { ; }
   QxSqlQuery(const char * sQuery) : m_sQuery(sQuery) { ; }
   virtual ~QxSqlQuery() { ; }

   QString query() const   { return m_sQuery; }
   bool isEmpty() const    { return m_sQuery.isEmpty(); }

   QxSqlQuery & query(const QString & sQuery);

   QxSqlQuery & bind(const QVariant & vValue);
   QxSqlQuery & bind(const QString & sKey, const QVariant & vValue);

   void resolve(QSqlQuery & query) const;

};

} // namespace qx

#endif // _QX_SQL_QUERY_H_
