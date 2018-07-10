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
struct QxSqlQueryHelper_FetchAll_WithRelation
{

   static void sql(qx::QxSqlRelationLinked * pRelationX, QString & sql, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      if (! pRelationX) { qAssert(false); QxSqlQueryHelper_FetchAll<T>::sql(sql, builder); return; }
      long l(0);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId();
      qx::QxSqlRelationParams params(0, 0, (& sql), (& builder), NULL, NULL);
      qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
      QString table = builder.table();
      sql = "SELECT ";
      if (pId) { sql += (pId->getSqlTablePointNameAsAlias(table) + ", "); }
      while ((p = builder.nextData(l))) { sql += (p->getSqlTablePointNameAsAlias(table) + ", "); }
      if (! oSoftDelete.isEmpty()) { l++; sql += (oSoftDelete.buildSqlTablePointName() + ", "); }
      pRelationX->hierarchySelect(params);
      sql = sql.left(sql.count() - 2); // Remove last ", "
      sql += " FROM " + qx::IxDataMember::getSqlFromTable(table) + ", ";
      pRelationX->hierarchyFrom(params);
      sql = sql.left(sql.count() - 2); // Remove last ", "
      pRelationX->hierarchyJoin(params);
      if (! oSoftDelete.isEmpty()) { sql += " WHERE " + oSoftDelete.buildSqlQueryToFetch(); }
      pRelationX->hierarchyWhereSoftDelete(params);
   }

   static void resolveInput(qx::QxSqlRelationLinked * pRelationX, T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   { Q_UNUSED(pRelationX); Q_UNUSED(t); Q_UNUSED(query); Q_UNUSED(builder); }

   static void resolveOutput(qx::QxSqlRelationLinked * pRelationX, T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      if (! pRelationX) { qAssert(false); QxSqlQueryHelper_FetchAll<T>::resolveOutput(t, query, builder); return; }
      long l(0); QVariant vId;
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId();
      qx::QxSoftDelete oSoftDelete = builder.getSoftDelete();
      short iOffsetId = (pId ? pId->getNameCount() : 0);
      if (pId) { QString sId; for (int i = 0; i < pId->getNameCount(); i++) { sId += query.value(i).toString() + "|"; }; vId = sId; }
      bool bComplex = builder.getCartesianProduct();
      bool bByPass = (bComplex && builder.existIdX(0, vId, vId));

      if (! bByPass)
      {
         if (pId) { for (int i = 0; i < pId->getNameCount(); i++) { pId->fromVariant((& t), query.value(i), i); } }
         while ((p = builder.nextData(l))) { p->fromVariant((& t), query.value(l + iOffsetId - 1)); }
         if (bComplex) { builder.insertIdX(0, vId, vId, (& t)); }
      }

      short iOffset = (builder.getDataCount() + iOffsetId + (oSoftDelete.isEmpty() ? 0 : 1));
      qx::QxSqlRelationParams params(0, iOffset, NULL, (& builder), (& query), (& t), vId);
      pRelationX->hierarchyResolveOutput(params);
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
