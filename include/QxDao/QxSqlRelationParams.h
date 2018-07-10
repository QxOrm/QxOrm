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

#ifndef _QX_SQL_RELATION_PARAMS_H_
#define _QX_SQL_RELATION_PARAMS_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>

namespace qx {

class IxSqlQueryBuilder;

class QxSqlRelationParams
{

protected:

   long                 m_lIndex;      // Current sql relation index
   long                 m_lOffset;     // Current sql query offset
   QString *            m_sql;         // Current sql query
   IxSqlQueryBuilder *  m_builder;     // Current sql query builder
   QSqlQuery *          m_query;       // Current sql query connected to database
   QSqlDatabase *       m_database;    // Current sql database connexion
   void *               m_pOwner;      // Owner to current object to resolve input/output

public:

   QxSqlRelationParams() : m_lIndex(0), m_lOffset(0), m_sql(NULL), m_builder(NULL), m_query(NULL), m_database(NULL), m_pOwner(NULL) { ; }
   QxSqlRelationParams(long lIndex, long lOffset, QString * sql, IxSqlQueryBuilder * builder, QSqlQuery * query, void * pOwner) : m_lIndex(lIndex), m_lOffset(lOffset), m_sql(sql), m_builder(builder), m_query(query), m_database(NULL), m_pOwner(pOwner) { ; }
   virtual ~QxSqlRelationParams() { ; }

   inline long index() const                          { return m_lIndex; }
   inline long offset() const                         { return m_lOffset; }
   inline QString & sql()                             { qAssert(m_sql); return (* m_sql); }
   inline const QString & sql() const                 { qAssert(m_sql); return (* m_sql); }
   inline QSqlQuery & query()                         { qAssert(m_query); return (* m_query); }
   inline const QSqlQuery & query() const             { qAssert(m_query); return (* m_query); }
   inline QSqlDatabase & database()                   { qAssert(m_database); return (* m_database); }
   inline const QSqlDatabase & database() const       { qAssert(m_database); return (* m_database); }
   inline IxSqlQueryBuilder & builder()               { qAssert(m_builder); return (* m_builder); }
   inline const IxSqlQueryBuilder & builder() const   { qAssert(m_builder); return (* m_builder); }
   inline void * owner() const                        { return m_pOwner; }

   inline void setIndex(long lIndex)                     { m_lIndex = lIndex; }
   inline void setOffset(long lOffset)                   { m_lOffset = lOffset; }
   inline void setSql(QString * sql)                     { m_sql = sql; }
   inline void setBuilder(IxSqlQueryBuilder * builder)   { m_builder = builder; }
   inline void setQuery(QSqlQuery * query)               { m_query = query; }
   inline void setDatabase(QSqlDatabase * database)      { m_database = database; }
   inline void setOwner(void * pOwner)                   { m_pOwner = pOwner; }

};

} // namespace qx

#endif // _QX_SQL_RELATION_PARAMS_H_
