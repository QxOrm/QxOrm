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

#ifndef _QX_SQL_QUERY_BUILDER_H_
#define _QX_SQL_QUERY_BUILDER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlQueryBuilder.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Concrete SQL query builder by class with a cache mechanism to backup and restore queries already builded by the program
 */

#include <QtCore/qmutex.h>

#include <QxDao/IxSqlQueryBuilder.h>
#include <QxDao/QxSqlQueryHelper.h>

#include <QxRegister/QxClass.h>

#include <QxTraits/remove_attr.h>
#include <QxTraits/remove_smart_ptr.h>

#define QX_SQL_ERR_NO_DATA_MEMBER_REGISTERED    "'QxSqlQueryBuilder<T>' error : 'qx::register_class()' not called or no data member registered"
#define QX_SQL_ERR_NO_ID_REGISTERED             "'QxSqlQueryBuilder<T>' error : no id registered"

#define QX_SQL_BUILDER_INIT_FCT() \
static QString sql = ""; \
QMutexLocker locker(& QxSqlQueryBuilder<T>::m_oMutex); \
if (! sql.isEmpty()) { setSqlQuery(sql); return (* this); }

#define QX_SQL_BUILDER_INIT_FCT_WITH_RELATION() \
static QHash<QString, QString> sqlX; \
static QHash<QString, QHash<QString, QString> > sqlAliasX; \
QMutexLocker locker(& QxSqlQueryBuilder<T>::m_oMutex); \
QString sql = sqlX.value(m_sHashRelation); \
if (! sql.isEmpty()) { setSqlQuery(sql); m_lstSqlQueryAlias = sqlAliasX.value(m_sHashRelation); return (* this); }

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder<T> : concrete SQL query builder for the class T with a cache mechanism to backup and restore queries already builded by the program
 */
template <class T>
class QxSqlQueryBuilder : public IxSqlQueryBuilder
{

private:

   typedef typename qx::trait::remove_attr<T>::type type_sql_tmp_1;
   typedef typename qx::trait::remove_smart_ptr<type_sql_tmp_1>::type type_sql_tmp_2;

public:

   typedef typename qx::QxSqlQueryBuilder<T>::type_sql_tmp_2 type_sql;

protected:

   QxDataMemberX<type_sql> * m_pDataMemberX;                         //!< 'QxDataMemberX' singleton

   static QxCollection<QString, IxDataMember *> m_lstDataMember;     //!< Collection of 'IxDataMember' to build SQL query
   static IxSqlRelationX m_lstSqlRelation;                           //!< Collection of 'IxSqlRelation' to build SQL query
   static QMutex m_oMutex;                                           //!< Mutex => 'QxSqlQueryBuilder' is thread-safe

public:

   QxSqlQueryBuilder() : IxSqlQueryBuilder(), m_pDataMemberX(NULL) { ; }
   QxSqlQueryBuilder(const QString & sql) : IxSqlQueryBuilder(sql), m_pDataMemberX(NULL) { ; }
   virtual ~QxSqlQueryBuilder() { ; }

   virtual IxDataMemberX * getDataMemberX() const { return m_pDataMemberX; }

   virtual IxSqlQueryBuilder & count()
   {
      QX_SQL_BUILDER_INIT_FCT()
      sql = "SELECT COUNT(*) FROM " + qx::IxDataMember::getSqlFromTable(m_sTableName);
      if (! m_oSoftDelete.isEmpty()) { sql += " WHERE " + m_oSoftDelete.buildSqlQueryToFetch(); }
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & exist()
   {
      QX_SQL_BUILDER_INIT_FCT()
      if (! getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_Exist<type_sql>::sql(sql, (* this));
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & fetchAll()
   {
      QX_SQL_BUILDER_INIT_FCT()
      qx::dao::detail::QxSqlQueryHelper_FetchAll<type_sql>::sql(sql, (* this));
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & fetchById()
   {
      QX_SQL_BUILDER_INIT_FCT()
      if (! getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_FetchById<type_sql>::sql(sql, (* this));
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & insert()
   {
      QX_SQL_BUILDER_INIT_FCT()
      qx::dao::detail::QxSqlQueryHelper_Insert<type_sql>::sql(sql, (* this));
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & update()
   {
      QX_SQL_BUILDER_INIT_FCT()
      if (! getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_Update<type_sql>::sql(sql, (* this));
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & deleteAll()
   {
      QX_SQL_BUILDER_INIT_FCT()
      sql = "DELETE FROM " + m_sTableName;
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & softDeleteAll()
   {
      QX_SQL_BUILDER_INIT_FCT()
      if (! m_oSoftDelete.isEmpty()) { sql = "UPDATE " + m_sTableName + " SET " + m_oSoftDelete.buildSqlQueryToUpdate(); }
      else { qAssert(false); }
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & deleteById()
   {
      QX_SQL_BUILDER_INIT_FCT()
      if (! getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_DeleteById<type_sql>::sql(sql, (* this), false);
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & softDeleteById()
   {
      QX_SQL_BUILDER_INIT_FCT()
      if (! getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      if (m_oSoftDelete.isEmpty()) { qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_DeleteById<type_sql>::sql(sql, (* this), true);
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & createTable()
   {
      QX_SQL_BUILDER_INIT_FCT()
      qx::dao::detail::QxSqlQueryHelper_CreateTable<type_sql>::sql(sql, (* this));
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & fetchAll_WithRelation(QxSqlRelationLinked * pRelationX)
   {
      QX_SQL_BUILDER_INIT_FCT_WITH_RELATION()
      qx::dao::detail::QxSqlQueryHelper_FetchAll_WithRelation<type_sql>::sql(pRelationX, sql, (* this));
      if (! m_sHashRelation.isEmpty()) { sqlX.insert(m_sHashRelation, sql); }
      if (! m_sHashRelation.isEmpty()) { sqlAliasX.insert(m_sHashRelation, m_lstSqlQueryAlias); }
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & fetchById_WithRelation(QxSqlRelationLinked * pRelationX)
   {
      QX_SQL_BUILDER_INIT_FCT_WITH_RELATION()
      if (! getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_FetchById_WithRelation<type_sql>::sql(pRelationX, sql, (* this));
      if (! m_sHashRelation.isEmpty()) { sqlX.insert(m_sHashRelation, sql); }
      if (! m_sHashRelation.isEmpty()) { sqlAliasX.insert(m_sHashRelation, m_lstSqlQueryAlias); }
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & fetchAll(const QStringList & columns)
   {
      QString sql;
      if (columns.count() <= 0) { return fetchAll(); }
      if (columns.at(0) == "*") { return fetchAll(); }
      if (! verifyColumns(columns)) { qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_FetchAll<type_sql>::sql(sql, (* this), columns);
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & fetchById(const QStringList & columns)
   {
      QString sql;
      if (columns.count() <= 0) { return fetchById(); }
      if (columns.at(0) == "*") { return fetchById(); }
      if (! verifyColumns(columns)) { qAssert(false); return (* this); }
      if (! getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_FetchById<type_sql>::sql(sql, (* this), columns);
      setSqlQuery(sql);
      return (* this);
   }

   virtual IxSqlQueryBuilder & update(const QStringList & columns)
   {
      QString sql;
      if (columns.count() <= 0) { return update(); }
      if (columns.at(0) == "*") { return update(); }
      if (! verifyColumns(columns)) { qAssert(false); return (* this); }
      if (! getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_Update<type_sql>::sql(sql, (* this), columns);
      setSqlQuery(sql);
      return (* this);
   }

   virtual void init()
   {
      QMutexLocker locker(& QxSqlQueryBuilder<T>::m_oMutex);
      m_pDataMemberX = QxClass<type_sql>::getSingleton()->dataMemberX();
      m_pDataMemberId = m_pDataMemberX->getId_WithDaoStrategy();
      m_sTableName = m_pDataMemberX->getName();
      m_lstDataMemberPtr = (& QxSqlQueryBuilder<T>::m_lstDataMember);
      m_lstSqlRelationPtr = (& QxSqlQueryBuilder<T>::m_lstSqlRelation);
      m_oSoftDelete = QxClass<type_sql>::getSingleton()->getSoftDelete();
      if (getDataCount() > 0 || getRelationCount() > 0) { return; }
      IxDataMember * p = NULL; long lCount = m_pDataMemberX->count_WithDaoStrategy();
      for (long l = 0; l < lCount; ++l) { if ((p = isValid_DataMember(l))) { m_lstDataMember.insert(p->getKey(), p); } }
      for (long l = 0; l < lCount; ++l) { if ((p = isValid_SqlRelation(l))) { m_lstSqlRelation.insert(p->getKey(), p->getSqlRelation()); } }
   }

private:

   IxDataMember * isValid_DataMember(long lIndex) const
   {
      IxDataMember * p = m_pDataMemberX->get_WithDaoStrategy(lIndex);
      bool bValid = (p && p->getDao() && ! p->hasSqlRelation());
      bValid = (bValid && (p != m_pDataMemberId));
      return (bValid ? p : NULL);
   }

   IxDataMember * isValid_SqlRelation(long lIndex) const
   {
      IxDataMember * p = m_pDataMemberX->get_WithDaoStrategy(lIndex);
      bool bIsValid = (p && p->getDao() && p->hasSqlRelation());
      if (bIsValid) { p->getSqlRelation()->init(); }
      return (bIsValid ? p : NULL);
   }

private:

#ifndef _QX_MODE_RELEASE
   inline bool verifyColumns(const QStringList & columns) const
   {
      if (! m_pDataMemberX) { return false; }
      for (int i = 0; i < columns.count(); i++)
      { if (! m_pDataMemberX->exist_WithDaoStrategy(columns.at(i))) { return false; } }
      return true;
   }
#else // _QX_MODE_RELEASE
   inline bool verifyColumns(const QStringList & columns) const
   { Q_UNUSED(columns); return true; }
#endif // _QX_MODE_RELEASE

};

template <class T> QMutex QxSqlQueryBuilder<T>::m_oMutex(QMutex::Recursive);
template <class T> QxCollection<QString, IxDataMember *> QxSqlQueryBuilder<T>::m_lstDataMember;
template <class T> IxSqlRelationX QxSqlQueryBuilder<T>::m_lstSqlRelation;

} // namespace qx

#endif // _QX_SQL_QUERY_BUILDER_H_
