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
struct QxSqlQueryHelper_FetchById
{

   static void sql(QString & sql, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      QString table = builder.table();
      sql = builder.fetchAll().getSqlQuery();
      sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
      sql += pId->getSqlAliasEqualToPlaceHolder(table, true);
   }

   static void resolveInput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      pId->setSqlPlaceHolder(query, (& t));
   }

   static void resolveOutput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   { QxSqlQueryHelper_FetchAll<T>::resolveOutput(t, query, builder); }

   static void sql(QString & sql, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   {
      if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_FetchById<T>::sql(sql, builder); return; }
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      QString table = builder.table();
      sql = builder.fetchAll(columns).getSqlQuery();
      sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
      sql += pId->getSqlAliasEqualToPlaceHolder(table, true);
   }

   static void resolveInput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   {
      if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_FetchById<T>::resolveInput(t, query, builder); return; }
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      pId->setSqlPlaceHolder(query, (& t));
   }

   static void resolveOutput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   { QxSqlQueryHelper_FetchAll<T>::resolveOutput(t, query, builder, columns); }

};

} // namespace detail
} // namespace dao
} // namespace qx
