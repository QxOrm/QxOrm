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

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxSqlQueryHelper_FetchAll
{

   static void sql(QString & sql, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      long l1(0), l2(0), l3(0), l4(0), l5(0);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId();
      qx::IxSqlRelation * pRelation = NULL;
      qx::QxSqlRelationParams params(0, 0, (& sql), (& builder), NULL, NULL);
      qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
      QString table = builder.table();
      sql = "SELECT ";
      if (pId) { sql += (pId->getSqlTablePointNameAsAlias(table) + ", "); }
      while ((p = builder.nextData(l1))) { sql += (p->getSqlTablePointNameAsAlias(table) + ", "); }
      if (! oSoftDelete.isEmpty()) { l1++; sql += (oSoftDelete.buildSqlTablePointName() + ", "); }
      while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazySelect(params); }
      sql = sql.left(sql.count() - 2); // Remove last ", "
      sql += " FROM " + qx::IxDataMember::getSqlFromTable(table) + ", ";
      while ((pRelation = builder.nextRelation(l3))) { params.setIndex(l3); pRelation->lazyFrom(params); }
      sql = sql.left(sql.count() - 2); // Remove last ", "
      while ((pRelation = builder.nextRelation(l4))) { params.setIndex(l4); pRelation->lazyJoin(params); }
      if (! oSoftDelete.isEmpty()) { sql += " WHERE " + oSoftDelete.buildSqlQueryToFetch(); }
      while ((pRelation = builder.nextRelation(l5))) { params.setIndex(l5); pRelation->lazyWhereSoftDelete(params); }
   }

   static void resolveInput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   { Q_UNUSED(t); Q_UNUSED(query); Q_UNUSED(builder); }

   static void resolveOutput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      long l1(0), l2(0);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId();
      qx::IxSqlRelation * pRelation = NULL;
      qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
      short iOffset = (pId ? pId->getNameCount() : 0);
      if (pId) { for (int i = 0; i < pId->getNameCount(); i++) { pId->fromVariant((& t), query.value(i), i); } }
      while ((p = builder.nextData(l1))) { p->fromVariant((& t), query.value(l1 + iOffset - 1)); }
      iOffset = (builder.getDataCount() + iOffset + (oSoftDelete.isEmpty() ? 0 : 1));
      qx::QxSqlRelationParams params(0, iOffset, NULL, (& builder), (& query), (& t));
      while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyFetch_ResolveOutput(params); }
   }

   static void sql(QString & sql, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   {
      if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_FetchAll<T>::sql(sql, builder); return; }
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId();
      qx::IxDataMemberX * pDataMemberX = builder.getDataMemberX(); qAssert(pDataMemberX);
      qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
      QString table = builder.table();
      sql = "SELECT ";
      if (pId) { sql += (pId->getSqlTablePointNameAsAlias(table) + ", "); }
      for (int i = 0; i < columns.count(); i++)
      { p = pDataMemberX->get_WithDaoStrategy(columns.at(i)); if (p && (p != pId)) { sql += (p->getSqlTablePointNameAsAlias(table) + ", "); } }
      sql = sql.left(sql.count() - 2); // Remove last ", "
      if (! oSoftDelete.isEmpty()) { sql += ", " + oSoftDelete.buildSqlTablePointName(); }
      sql += " FROM " + qx::IxDataMember::getSqlFromTable(table);
      if (! oSoftDelete.isEmpty()) { sql += " WHERE " + oSoftDelete.buildSqlQueryToFetch(); }
   }

   static void resolveInput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   { if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_FetchAll<T>::resolveInput(t, query, builder); return; } }

   static void resolveOutput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   {
      if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_FetchAll<T>::resolveOutput(t, query, builder); return; }
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId();
      qx::IxDataMemberX * pDataMemberX = builder.getDataMemberX(); qAssert(pDataMemberX);
      short iOffset = (pId ? pId->getNameCount() : 0);
      if (pId) { for (int i = 0; i < pId->getNameCount(); i++) { pId->fromVariant((& t), query.value(i), i); } }
      for (int i = 0; i < columns.count(); i++)
      { p = pDataMemberX->get_WithDaoStrategy(columns.at(i)); if (p && (p != pId)) { p->fromVariant((& t), query.value(i + iOffset)); } }
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
