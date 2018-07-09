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
