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
struct QxSqlQueryHelper_Update
{

   static void sql(QString & sql, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      long l1(0), l2(0);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      qx::IxSqlRelation * pRelation = NULL;
      qx::QxSqlRelationParams params(0, 0, (& sql), (& builder), NULL, NULL);
      QString table = builder.table();
      sql = "UPDATE " + table + " SET ";
      sql += pId->getSqlNameEqualToPlaceHolder("", ", ") + ", ";
      while ((p = builder.nextData(l1))) { sql += p->getSqlNameEqualToPlaceHolder("", ", ") + ", "; }
      while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyUpdate(params); }
      sql = sql.left(sql.count() - 2); // Remove last ", "
      sql += " WHERE " + pId->getSqlNameEqualToPlaceHolder("_bis", " AND ");
   }

   static void resolveInput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      long l1(0), l2(0);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      qx::IxSqlRelation * pRelation = NULL;
      qx::QxSqlRelationParams params(0, 0, NULL, (& builder), (& query), (& t));
      pId->setSqlPlaceHolder(query, (& t));
      while ((p = builder.nextData(l1))) { p->setSqlPlaceHolder(query, (& t)); }
      while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyUpdate_ResolveInput(params); }
      pId->setSqlPlaceHolder(query, (& t), "_bis");
   }

   static void resolveOutput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   { Q_UNUSED(t); Q_UNUSED(query); Q_UNUSED(builder); }

   static void sql(QString & sql, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   {
      if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_Update<T>::sql(sql, builder); return; }
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      qx::IxDataMemberX * pDataMemberX = builder.getDataMemberX(); qAssert(pDataMemberX);
      QString table = builder.table();
      sql = "UPDATE " + table + " SET ";
      sql += pId->getSqlNameEqualToPlaceHolder("", ", ") + ", ";
      for (int i = 0; i < columns.count(); i++)
      { p = pDataMemberX->get_WithDaoStrategy(columns.at(i)); if (p && (p != pId)) { sql += p->getSqlNameEqualToPlaceHolder("", ", ") + ", "; } }
      sql = sql.left(sql.count() - 2); // Remove last ", "
      sql += " WHERE " + pId->getSqlNameEqualToPlaceHolder("_bis", " AND ");
   }

   static void resolveInput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   {
      if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_Update<T>::resolveInput(t, query, builder); return; }
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      qx::IxDataMemberX * pDataMemberX = builder.getDataMemberX(); qAssert(pDataMemberX);
      pId->setSqlPlaceHolder(query, (& t));
      for (int i = 0; i < columns.count(); i++)
      { p = pDataMemberX->get_WithDaoStrategy(columns.at(i)); if (p && (p != pId)) { p->setSqlPlaceHolder(query, (& t)); } }
      pId->setSqlPlaceHolder(query, (& t), "_bis");
   }

   static void resolveOutput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   { if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_Update<T>::resolveOutput(t, query, builder); return; } }

};

} // namespace detail
} // namespace dao
} // namespace qx
