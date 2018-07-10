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
struct QxSqlQueryHelper_FetchById_WithRelation
{

   static void sql(qx::QxSqlRelationLinked * pRelationX, QString & sql, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      if (! pRelationX) { qAssert(false); QxSqlQueryHelper_FetchById<T>::sql(sql, builder); return; }
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      QString table = builder.table();
      sql = builder.fetchAll_WithRelation(pRelationX).getSqlQuery();
      sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
      sql += pId->getSqlAliasEqualToPlaceHolder(table, true);
   }

   static void resolveInput(qx::QxSqlRelationLinked * pRelationX, T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      if (! pRelationX) { qAssert(false); QxSqlQueryHelper_FetchById<T>::resolveInput(t, query, builder); return; }
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      pId->setSqlPlaceHolder(query, (& t));
   }

   static void resolveOutput(qx::QxSqlRelationLinked * pRelationX, T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   { QxSqlQueryHelper_FetchAll_WithRelation<T>::resolveOutput(pRelationX, t, query, builder); }

};

} // namespace detail
} // namespace dao
} // namespace qx
