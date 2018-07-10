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

#ifndef _QX_SQL_RELATION_PARAMS_H_
#define _QX_SQL_RELATION_PARAMS_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlRelationParams.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Define list of parameters to transfer to relationships to manage SQL queries builded by QxOrm library
 */

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>

#include <QxDao/QxSqlJoin.h>

namespace qx {

class IxSqlQueryBuilder;

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlRelationParams : define list of parameters to transfer to relationships to manage SQL queries builded by QxOrm library
 */
class QxSqlRelationParams
{

protected:

   QVariant                      m_vId;            //!< Current id
   long                          m_lIndex;         //!< Current SQL relation index
   long                          m_lIndexOwner;    //!< Current SQL relation owner index
   long                          m_lOffset;        //!< Current SQL query offset
   QString *                     m_sql;            //!< Current SQL query
   IxSqlQueryBuilder *           m_builder;        //!< Current SQL query builder
   QSqlQuery *                   m_query;          //!< Current SQL query connected to database
   QSqlDatabase *                m_database;       //!< Current SQL database connexion
   void *                        m_pOwner;         //!< Owner to current object to resolve input/output
   qx::dao::sql_join::join_type  m_eJoinType;      //!< Current join type to build SQL query : LEFT OUTER JOIN, INNER JOIN, etc...

public:

   QxSqlRelationParams() : m_lIndex(0), m_lIndexOwner(0), m_lOffset(0), m_sql(NULL), m_builder(NULL), m_query(NULL), m_database(NULL), m_pOwner(NULL), m_eJoinType(qx::dao::sql_join::no_join) { ; }
   QxSqlRelationParams(long lIndex, long lOffset, QString * sql, IxSqlQueryBuilder * builder, QSqlQuery * query, void * pOwner) : m_lIndex(lIndex), m_lIndexOwner(0), m_lOffset(lOffset), m_sql(sql), m_builder(builder), m_query(query), m_database(NULL), m_pOwner(pOwner), m_eJoinType(qx::dao::sql_join::no_join) { ; }
   QxSqlRelationParams(long lIndex, long lOffset, QString * sql, IxSqlQueryBuilder * builder, QSqlQuery * query, void * pOwner, const QVariant & vId) : m_vId(vId), m_lIndex(lIndex), m_lIndexOwner(0), m_lOffset(lOffset), m_sql(sql), m_builder(builder), m_query(query), m_database(NULL), m_pOwner(pOwner), m_eJoinType(qx::dao::sql_join::no_join) { ; }
   virtual ~QxSqlRelationParams() { ; }

   inline QVariant id() const                            { return m_vId; }
   inline long index() const                             { return m_lIndex; }
   inline long indexOwner() const                        { return m_lIndexOwner; }
   inline long offset() const                            { return m_lOffset; }
   inline QString & sql()                                { qAssert(m_sql); return (* m_sql); }
   inline const QString & sql() const                    { qAssert(m_sql); return (* m_sql); }
   inline QSqlQuery & query()                            { qAssert(m_query); return (* m_query); }
   inline const QSqlQuery & query() const                { qAssert(m_query); return (* m_query); }
   inline QSqlDatabase & database()                      { qAssert(m_database); return (* m_database); }
   inline const QSqlDatabase & database() const          { qAssert(m_database); return (* m_database); }
   inline IxSqlQueryBuilder & builder()                  { qAssert(m_builder); return (* m_builder); }
   inline const IxSqlQueryBuilder & builder() const      { qAssert(m_builder); return (* m_builder); }
   inline void * owner() const                           { return m_pOwner; }
   inline qx::dao::sql_join::join_type joinType() const  { return m_eJoinType; }

   inline void setId(const QVariant & vId)                  { m_vId = vId; }
   inline void setIndex(long lIndex)                        { m_lIndex = lIndex; }
   inline void setIndexOwner(long lIndex)                   { m_lIndexOwner = lIndex; }
   inline void setOffset(long lOffset)                      { m_lOffset = lOffset; }
   inline void setSql(QString * sql)                        { m_sql = sql; }
   inline void setBuilder(IxSqlQueryBuilder * builder)      { m_builder = builder; }
   inline void setQuery(QSqlQuery * query)                  { m_query = query; }
   inline void setDatabase(QSqlDatabase * database)         { m_database = database; }
   inline void setOwner(void * pOwner)                      { m_pOwner = pOwner; }
   inline void setJoinType(qx::dao::sql_join::join_type e)  { m_eJoinType = e; }

};

} // namespace qx

#endif // _QX_SQL_RELATION_PARAMS_H_
