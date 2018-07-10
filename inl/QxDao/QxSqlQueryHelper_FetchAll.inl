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

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxSqlQueryHelper_FetchAll
{

   static void sql(QString & sql, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      long l1(0), l2(0), l3(0), l4(0);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId();
      qx::IxSqlRelation * pRelation = NULL;
      qx::QxSqlRelationParams params(0, 0, (& sql), (& builder), NULL, NULL);
      QString table = builder.table();
      sql = "SELECT ";
      if (pId) { sql += (table + "." + pId->getName() + " AS " + pId->getSqlAlias(& table) + ", "); }
      while ((p = builder.nextData(l1))) { sql += (table + "." + p->getName() + " AS " + p->getSqlAlias(& table) + ", "); }
      while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazySelect(params); }
      sql = sql.left(sql.count() - 2); // Remove last ", "
      sql += " FROM " + table + ", ";
      while ((pRelation = builder.nextRelation(l3))) { params.setIndex(l3); pRelation->lazyFrom(params); }
      sql = sql.left(sql.count() - 2); // Remove last ", "
      while ((pRelation = builder.nextRelation(l4))) { params.setIndex(l4); pRelation->lazyJoin(params); }
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
      short iOffset = (pId ? 1 : 0);
      if (pId) { pId->fromVariant((& t), query.value(0)); }
      while ((p = builder.nextData(l1))) { p->fromVariant((& t), query.value(l1 + iOffset - 1)); }
      qx::QxSqlRelationParams params(0, (builder.getDataCount() + iOffset), NULL, (& builder), (& query), (& t));
      while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyFetch_ResolveOutput(params); }
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
