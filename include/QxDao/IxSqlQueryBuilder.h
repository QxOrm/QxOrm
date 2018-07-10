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

#ifndef _IX_SQL_QUERY_BUILDER_H_
#define _IX_SQL_QUERY_BUILDER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxSqlQueryBuilder.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Common interface to build SQL queries to communicate with database
 */

#include <QxDataMember/IxDataMemberX.h>

#include <QxDao/IxSqlRelation.h>
#include <QxDao/QxSoftDelete.h>
#include <QxDao/QxSqlRelationLinked.h>

namespace qx {
namespace dao {
namespace detail {

class IxDao_Helper;

} // namespace detail
} // namespace dao
} // namespace qx

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::IxSqlQueryBuilder : common interface to build SQL queries to communicate with database
 */
class QX_DLL_EXPORT IxSqlQueryBuilder
{

private:

   struct IxSqlQueryBuilderImpl;
   std::unique_ptr<IxSqlQueryBuilderImpl> m_pImpl; //!< Private implementation idiom

public:

   IxSqlQueryBuilder();
   virtual ~IxSqlQueryBuilder() = 0;

   IxDataMemberX * getDataMemberX() const;
   QxCollection<QString, IxDataMember *> * getLstDataMember() const;
   IxSqlRelationX * getLstRelation() const;
   qx::dao::detail::IxDao_Helper * getDaoHelper() const;
   void setDaoHelper(qx::dao::detail::IxDao_Helper * p);

   void setHashRelation(const QString & s);
   void setCartesianProduct(bool b);
   QString getSqlQuery() const;
   QString getHashRelation() const;
   QString table() const;
   QxSoftDelete getSoftDelete() const;
   bool getCartesianProduct() const;
   long getDataCount() const;
   long getRelationCount() const;
   IxDataMember * getDataId() const;
   IxDataMember * nextData(long & l) const;
   IxSqlRelation * nextRelation(long & l) const;

   void initIdX(long lAllRelationCount);
   bool insertIdX(long lIndex, const QVariant & idOwner, const QVariant & idData, void * ptr);
   void * existIdX(long lIndex, const QVariant & idOwner, const QVariant & idData);
   void setSqlQuery(const QString & sql, const QString & key = QString());
   void addSqlQueryAlias(const QString & sql, const QString & sqlAlias);
   bool getAddAutoIncrementIdToUpdateQuery() const;
   void replaceSqlQueryAlias(QString & sql) const;
   void displaySqlQuery(int time_ms = -1, int time_db = -1) const;

   virtual void init();
   virtual void clone(const IxSqlQueryBuilder & other);
   virtual IxSqlQueryBuilder & buildSql(const QStringList & columns = QStringList(), QxSqlRelationLinked * pRelationX = NULL) = 0;

   static QString addSqlCondition(const QString & sql) { return (sql.contains(" WHERE ") ? " AND " : " WHERE "); }

   static void sql_CreateTable(QString & sql, IxSqlQueryBuilder & builder);
   static void sql_DeleteById(QString & sql, IxSqlQueryBuilder & builder, bool bSoftDelete);
   static void sql_Exist(QString & sql, IxSqlQueryBuilder & builder);
   static void sql_FetchAll(QString & sql, IxSqlQueryBuilder & builder);
   static void sql_FetchAll(QString & sql, IxSqlQueryBuilder & builder, const QStringList & columns);
   static void sql_FetchAll_WithRelation(qx::QxSqlRelationLinked * pRelationX, QString & sql, IxSqlQueryBuilder & builder);
   static void sql_FetchById(QString & sql, IxSqlQueryBuilder & builder);
   static void sql_FetchById(QString & sql, IxSqlQueryBuilder & builder, const QStringList & columns);
   static void sql_FetchById_WithRelation(qx::QxSqlRelationLinked * pRelationX, QString & sql, IxSqlQueryBuilder & builder);
   static void sql_Insert(QString & sql, IxSqlQueryBuilder & builder);
   static void sql_Update(QString & sql, IxSqlQueryBuilder & builder);
   static void sql_Update(QString & sql, IxSqlQueryBuilder & builder, const QStringList & columns);

   static void resolveOutput_FetchAll(void * t, QSqlQuery & query, IxSqlQueryBuilder & builder);
   static void resolveOutput_FetchAll(void * t, QSqlQuery & query, IxSqlQueryBuilder & builder, const QStringList & columns);
   static void resolveOutput_FetchAll_WithRelation(qx::QxSqlRelationLinked * pRelationX, void * t, QSqlQuery & query, IxSqlQueryBuilder & builder);

   static void resolveInput_Insert(void * t, QSqlQuery & query, IxSqlQueryBuilder & builder);
   static void resolveInput_Update(void * t, QSqlQuery & query, IxSqlQueryBuilder & builder);
   static void resolveInput_Update(void * t, QSqlQuery & query, IxSqlQueryBuilder & builder, const QStringList & columns);

protected:

   bool verifyColumns(const QStringList & columns) const QX_USED;

   IxDataMember * isValid_DataMember(long lIndex) const;
   IxDataMember * isValid_SqlRelation(long lIndex) const;

   bool isInitDone() const;
   QxSoftDelete & softDelete();
   const QxSoftDelete & softDelete() const;
   void setSoftDelete(const QxSoftDelete & o);
   void setDataMemberX(IxDataMemberX * p);
   QHash<QString, QString> & listSqlQueryAlias();
   const QHash<QString, QString> & listSqlQueryAlias() const;
   static QHash<QString, QString> & listSqlQuery();
   static QHash<QString, QHash<QString, QString> > & listSqlAlias();

};

typedef std::shared_ptr<IxSqlQueryBuilder> IxSqlQueryBuilder_ptr;

} // namespace qx

#include <QxDao/IxDao_Helper.h>

#endif // _IX_SQL_QUERY_BUILDER_H_
