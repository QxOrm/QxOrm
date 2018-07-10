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
#include <QxDao/QxSqlSaveMode.h>

#include <QxCollection/QxCollection.h>

namespace qx {

class QxSqlRelationLinked;
class IxSqlQueryBuilder;
class IxSqlRelation;

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlRelationParams : define list of parameters to transfer to relationships to manage SQL queries builded by QxOrm library
 */
class QX_DLL_EXPORT QxSqlRelationParams
{

public:

   typedef std::shared_ptr<QxSqlRelationLinked> type_relation_linked_ptr;
   typedef QHash<QString, type_relation_linked_ptr> type_lst_relation_linked;

protected:

   QVariant                         m_vId;                  //!< Current id
   long                             m_lIndex;               //!< Current SQL relation index
   long                             m_lIndexOwner;          //!< Current SQL relation owner index
   long                             m_lOffset;              //!< Current SQL query offset
   QString *                        m_sql;                  //!< Current SQL query
   IxSqlQueryBuilder *              m_builder;              //!< Current SQL query builder
   QSqlQuery *                      m_query;                //!< Current SQL query connected to database
   QSqlDatabase *                   m_database;             //!< Current SQL database connexion
   void *                           m_pOwner;               //!< Owner to current object to resolve input/output
   qx::dao::sql_join::join_type     m_eJoinType;            //!< Current join type to build SQL query : LEFT OUTER JOIN, INNER JOIN, etc...
   type_lst_relation_linked *       m_pRelationX;           //!< Current list of relations used by qx::QxSqlRelationLinked class
   QString                          m_sTableAlias;          //!< Current SQL table alias : useful for relationships defined in base class
   qx::dao::save_mode::e_save_mode  m_eSaveMode;            //!< Used to improve performance, if you know that you are just inserting or updating items in database
   bool                             m_bRecursiveMode;       //!< Recursive mode to iterate over each level of relationship
   QSet<void *>                     m_lstRecursiveItems;    //!< Used by recursive process to avoid infinite loop
   QPair<QSet<QString>, long> *     m_pColumns;             //!< List of relation columns to fetch (syntax : my_relation { column_1, column_2, etc... }), if empty then fetch all columns

public:

   QxSqlRelationParams();
   QxSqlRelationParams(long lIndex, long lOffset, QString * sql, IxSqlQueryBuilder * builder, QSqlQuery * query, void * pOwner);
   QxSqlRelationParams(long lIndex, long lOffset, QString * sql, IxSqlQueryBuilder * builder, QSqlQuery * query, void * pOwner, const QVariant & vId);
   virtual ~QxSqlRelationParams();

   inline QVariant id() const                               { return m_vId; }
   inline long index() const                                { return m_lIndex; }
   inline long indexOwner() const                           { return m_lIndexOwner; }
   inline long offset() const                               { return m_lOffset; }
   inline QString & sql()                                   { qAssert(m_sql); return (* m_sql); }
   inline const QString & sql() const                       { qAssert(m_sql); return (* m_sql); }
   inline QSqlQuery & query()                               { qAssert(m_query); return (* m_query); }
   inline const QSqlQuery & query() const                   { qAssert(m_query); return (* m_query); }
   inline QSqlDatabase & database()                         { qAssert(m_database); return (* m_database); }
   inline const QSqlDatabase & database() const             { qAssert(m_database); return (* m_database); }
   inline IxSqlQueryBuilder & builder()                     { qAssert(m_builder); return (* m_builder); }
   inline const IxSqlQueryBuilder & builder() const         { qAssert(m_builder); return (* m_builder); }
   inline void * owner() const                              { return m_pOwner; }
   inline qx::dao::sql_join::join_type joinType() const     { return m_eJoinType; }
   inline type_lst_relation_linked * relationX() const      { return m_pRelationX; }
   inline QString getTableAlias() const                     { return m_sTableAlias; }
   inline qx::dao::save_mode::e_save_mode saveMode() const  { return m_eSaveMode; }
   inline bool recursiveMode() const                        { return m_bRecursiveMode; }
   inline bool existRecursiveItem(void * p) const           { return m_lstRecursiveItems.contains(p); }
   inline QSet<QString> getColumns() const                  { return (m_pColumns ? m_pColumns->first : QSet<QString>()); }
   inline bool checkColumns(const QString & s) const        { return (! m_pColumns || m_pColumns->first.isEmpty() || m_pColumns->first.contains(s)); }
   inline long getColumnsCount() const                      { return (m_pColumns ? m_pColumns->first.count() : 0); }
   inline long getColumnsOffset() const                     { return (m_pColumns ? m_pColumns->second : 0); }

   inline void setId(const QVariant & vId)                     { m_vId = vId; }
   inline void setIndex(long lIndex)                           { m_lIndex = lIndex; }
   inline void setIndexOwner(long lIndex)                      { m_lIndexOwner = lIndex; }
   inline void setOffset(long lOffset)                         { m_lOffset = lOffset; }
   inline void setSql(QString * sql)                           { m_sql = sql; }
   inline void setBuilder(IxSqlQueryBuilder * builder)         { m_builder = builder; }
   inline void setQuery(QSqlQuery * query)                     { m_query = query; }
   inline void setDatabase(QSqlDatabase * database)            { m_database = database; }
   inline void setOwner(void * pOwner)                         { m_pOwner = pOwner; }
   inline void setJoinType(qx::dao::sql_join::join_type e)     { m_eJoinType = e; }
   inline void setRelationX(type_lst_relation_linked * p)      { m_pRelationX = p; }
   inline void setTableAlias(const QString & s)                { m_sTableAlias = s; }
   inline void setSaveMode(qx::dao::save_mode::e_save_mode e)  { m_eSaveMode = e; }
   inline void setRecursiveMode(bool b)                        { m_bRecursiveMode = b; }
   inline void insertRecursiveItem(void * p)                   { if (p) { m_lstRecursiveItems.insert(p); } }
   inline void setColumns(QPair<QSet<QString>, long> * p)      { m_pColumns = p; }
   inline void setColumnsOffset(long l)                        { if (m_pColumns) { m_pColumns->second = l; } }

};

} // namespace qx

#endif // _QX_SQL_RELATION_PARAMS_H_
