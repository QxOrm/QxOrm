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
 * \brief Concrete SQL query builder by class with a cache mechanism to backup and restore queries already built by the program
 */

#include <QxDao/IxSqlQueryBuilder.h>
#include <QxDao/QxSqlQueryHelper.h>

#include <QxRegister/QxClass.h>

#include <QxTraits/remove_attr.h>
#include <QxTraits/remove_smart_ptr.h>
#include <QxTraits/is_qx_registered.h>

#define QX_SQL_ERR_NO_DATA_MEMBER_REGISTERED    "'QxSqlQueryBuilder<T>' error : 'qx::register_class()' not called or no data member registered"
#define QX_SQL_ERR_NO_ID_REGISTERED             "'QxSqlQueryBuilder<T>' error : no id registered"

#define QX_SQL_BUILDER_INIT_FCT(oper) \
QString key = QxClass<type_sql>::getSingleton()->getKey() + oper; \
QString sql = IxSqlQueryBuilder::listSqlQuery().value(key); \
if (! sql.isEmpty()) { this->setSqlQuery(sql); return (* this); }

#define QX_SQL_BUILDER_INIT_FCT_WITH_RELATION(oper) \
QString key = QxClass<type_sql>::getSingleton()->getKey() + this->getHashRelation() + oper; \
QString sql = IxSqlQueryBuilder::listSqlQuery().value(key); \
if (! sql.isEmpty()) { this->setSqlQuery(sql); this->listSqlQueryAlias() = IxSqlQueryBuilder::listSqlAlias().value(key); return (* this); }

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder<T> : concrete SQL query builder for class T with a cache mechanism to backup and restore queries already built by the program
 */
template <class T>
class QxSqlQueryBuilder : public IxSqlQueryBuilder
{

private:

   typedef typename qx::trait::remove_attr<T>::type type_sql_tmp_1;
   typedef typename qx::trait::remove_smart_ptr<type_sql_tmp_1>::type type_sql_tmp_2;

public:

   typedef typename qx::QxSqlQueryBuilder<T>::type_sql_tmp_2 type_sql;

public:

   QxSqlQueryBuilder() : IxSqlQueryBuilder() { ; }
   virtual ~QxSqlQueryBuilder() { static_assert(qx::trait::is_qx_registered<type_sql>::value, "qx::trait::is_qx_registered<type_sql>::value"); }

   virtual void init()
   {
      if (isInitDone()) { return; }
      setDataMemberX(QxClass<type_sql>::getSingleton()->dataMemberX());
      setSoftDelete(QxClass<type_sql>::getSingleton()->getSoftDelete());
      IxSqlQueryBuilder::init();
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_Count<T> : concrete SQL query builder for class T to build a COUNT SQL query
 */
template <class T>
class QxSqlQueryBuilder_Count : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_Count() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_Count() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(columns); Q_UNUSED(pRelationX);
      QX_SQL_BUILDER_INIT_FCT("Count")
      sql = "SELECT COUNT(*) FROM " + qx::IxDataMember::getSqlFromTable(this->table());
      if (! this->softDelete().isEmpty()) { sql += " WHERE " + this->softDelete().buildSqlQueryToFetch(); }
      this->setSqlQuery(sql, key);
      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_Exist<T> : concrete SQL query builder for class T to build an EXIST SQL query
 */
template <class T>
class QxSqlQueryBuilder_Exist : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_Exist() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_Exist() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(columns); Q_UNUSED(pRelationX);
      QX_SQL_BUILDER_INIT_FCT("Exist")
      if (! this->getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_Exist<type_sql>::sql(sql, (* this));
      this->setSqlQuery(sql, key);
      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_FetchAll<T> : concrete SQL query builder for class T to build a FETCH ALL SQL query
 */
template <class T>
class QxSqlQueryBuilder_FetchAll : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_FetchAll() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_FetchAll() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(pRelationX);

      if ((columns.count() <= 0) || (columns.at(0) == "*"))
      {
         QX_SQL_BUILDER_INIT_FCT("FetchAll")
         qx::dao::detail::QxSqlQueryHelper_FetchAll<type_sql>::sql(sql, (* this));
         this->setSqlQuery(sql, key);
      }
      else
      {
         QString sql;
         if (! this->verifyColumns(columns)) { return (* this); }
         qx::dao::detail::QxSqlQueryHelper_FetchAll<type_sql>::sql(sql, (* this), columns);
         this->setSqlQuery(sql);
      }

      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_FetchById<T> : concrete SQL query builder for class T to build a FETCH BY ID SQL query
 */
template <class T>
class QxSqlQueryBuilder_FetchById : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_FetchById() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_FetchById() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(pRelationX);
      if (! this->getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      QxSqlQueryBuilder_FetchAll<type_sql> builder; builder.clone(* this);

      if ((columns.count() <= 0) || (columns.at(0) == "*"))
      {
         QX_SQL_BUILDER_INIT_FCT("FetchById")
         qx::dao::detail::QxSqlQueryHelper_FetchById<type_sql>::sql(sql, builder);
         this->setSqlQuery(sql, key);
      }
      else
      {
         QString sql;
         if (! this->verifyColumns(columns)) { return (* this); }
         qx::dao::detail::QxSqlQueryHelper_FetchById<type_sql>::sql(sql, builder, columns);
         this->setSqlQuery(sql);
      }

      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_Insert<T> : concrete SQL query builder for class T to build an INSERT SQL query
 */
template <class T>
class QxSqlQueryBuilder_Insert : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_Insert() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_Insert() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(columns); Q_UNUSED(pRelationX);
      QX_SQL_BUILDER_INIT_FCT("Insert")
      qx::dao::detail::QxSqlQueryHelper_Insert<type_sql>::sql(sql, (* this));
      this->setSqlQuery(sql, key);
      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_Update<T> : concrete SQL query builder for class T to build an UPDATE SQL query
 */
template <class T>
class QxSqlQueryBuilder_Update : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_Update() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_Update() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(pRelationX);
      if (! this->getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }

      if ((columns.count() <= 0) || (columns.at(0) == "*"))
      {
         QX_SQL_BUILDER_INIT_FCT("Update")
         qx::dao::detail::QxSqlQueryHelper_Update<type_sql>::sql(sql, (* this));
         this->setSqlQuery(sql, key);
      }
      else
      {
         QString sql;
         if (! this->verifyColumns(columns)) { return (* this); }
         qx::dao::detail::QxSqlQueryHelper_Update<type_sql>::sql(sql, (* this), columns);
         this->setSqlQuery(sql);
      }

      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_DeleteAll<T> : concrete SQL query builder for class T to build a DELETE ALL SQL query
 */
template <class T>
class QxSqlQueryBuilder_DeleteAll : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_DeleteAll() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_DeleteAll() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(columns); Q_UNUSED(pRelationX);
      QX_SQL_BUILDER_INIT_FCT("DeleteAll")
      sql = "DELETE FROM " + this->table();
      this->setSqlQuery(sql, key);
      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_SoftDeleteAll<T> : concrete SQL query builder for class T to build a SOFT DELETE ALL SQL query
 */
template <class T>
class QxSqlQueryBuilder_SoftDeleteAll : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_SoftDeleteAll() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_SoftDeleteAll() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(columns); Q_UNUSED(pRelationX);
      QX_SQL_BUILDER_INIT_FCT("SoftDeleteAll")
      if (! this->softDelete().isEmpty()) { sql = "UPDATE " + this->table() + " SET " + this->softDelete().buildSqlQueryToUpdate(); }
      else { qAssert(false); }
      this->setSqlQuery(sql, key);
      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_DeleteById<T> : concrete SQL query builder for class T to build a DELETE BY ID SQL query
 */
template <class T>
class QxSqlQueryBuilder_DeleteById : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_DeleteById() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_DeleteById() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(columns); Q_UNUSED(pRelationX);
      QX_SQL_BUILDER_INIT_FCT("DeleteById")
      if (! this->getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_DeleteById<type_sql>::sql(sql, (* this), false);
      this->setSqlQuery(sql, key);
      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_SoftDeleteById<T> : concrete SQL query builder for class T to build a SOFT DELETE BY ID SQL query
 */
template <class T>
class QxSqlQueryBuilder_SoftDeleteById : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_SoftDeleteById() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_SoftDeleteById() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(columns); Q_UNUSED(pRelationX);
      QX_SQL_BUILDER_INIT_FCT("SoftDeleteById")
      if (! this->getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      if (this->softDelete().isEmpty()) { qAssert(false); return (* this); }
      qx::dao::detail::QxSqlQueryHelper_DeleteById<type_sql>::sql(sql, (* this), true);
      this->setSqlQuery(sql, key);
      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_CreateTable<T> : concrete SQL query builder for class T to build a CREATE TABLE SQL query
 */
template <class T>
class QxSqlQueryBuilder_CreateTable : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_CreateTable() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_CreateTable() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(columns); Q_UNUSED(pRelationX);
      QX_SQL_BUILDER_INIT_FCT("CreateTable")
      qx::dao::detail::QxSqlQueryHelper_CreateTable<type_sql>::sql(sql, (* this));
      this->setSqlQuery(sql, key);
      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_FetchAll_WithRelation<T> : concrete SQL query builder for class T to build a FETCH ALL WITH RELATION SQL query
 */
template <class T>
class QxSqlQueryBuilder_FetchAll_WithRelation : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_FetchAll_WithRelation() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_FetchAll_WithRelation() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(columns);
      QX_SQL_BUILDER_INIT_FCT_WITH_RELATION("FetchAll_WithRelation")
      qx::dao::detail::QxSqlQueryHelper_FetchAll_WithRelation<type_sql>::sql(pRelationX, sql, (* this));
      IxSqlQueryBuilder::listSqlAlias().insert(key, this->listSqlQueryAlias());
      this->setSqlQuery(sql, key);
      return (* this);
   }

};

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQueryBuilder_FetchById_WithRelation<T> : concrete SQL query builder for class T to build a FETCH BY ID WITH RELATION SQL query
 */
template <class T>
class QxSqlQueryBuilder_FetchById_WithRelation : public QxSqlQueryBuilder<T>
{

public:

   typedef typename QxSqlQueryBuilder<T>::type_sql type_sql;

   QxSqlQueryBuilder_FetchById_WithRelation() : QxSqlQueryBuilder<T>() { ; }
   virtual ~QxSqlQueryBuilder_FetchById_WithRelation() { ; }

   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL)
   {
      Q_UNUSED(columns);
      QX_SQL_BUILDER_INIT_FCT_WITH_RELATION("FetchById_WithRelation")
      if (! this->getDataId()) { qDebug("[QxOrm] %s", QX_SQL_ERR_NO_ID_REGISTERED); qAssert(false); return (* this); }
      QxSqlQueryBuilder_FetchAll_WithRelation<type_sql> builder; builder.clone(* this);
      qx::dao::detail::QxSqlQueryHelper_FetchById_WithRelation<type_sql>::sql(pRelationX, sql, builder);
      IxSqlQueryBuilder::listSqlAlias().insert(key, this->listSqlQueryAlias());
      this->setSqlQuery(sql, key);
      return (* this);
   }

};

} // namespace qx

#endif // _QX_SQL_QUERY_BUILDER_H_
