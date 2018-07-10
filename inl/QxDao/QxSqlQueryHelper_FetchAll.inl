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
      static_assert(qx::trait::is_qx_registered<T>::value, "qx::trait::is_qx_registered<T>::value");
      qx::IxSqlQueryBuilder::sql_FetchAll(sql, builder);
   }

   static void resolveInput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   { Q_UNUSED(t); Q_UNUSED(query); Q_UNUSED(builder); }

   static void resolveOutput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   {
      static_assert(qx::trait::is_qx_registered<T>::value, "qx::trait::is_qx_registered<T>::value");
      qx::IxSqlQueryBuilder::resolveOutput_FetchAll((& t), query, builder);
   }

   static void sql(QString & sql, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   {
      if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_FetchAll<T>::sql(sql, builder); return; }
      static_assert(qx::trait::is_qx_registered<T>::value, "qx::trait::is_qx_registered<T>::value");
      qx::IxSqlQueryBuilder::sql_FetchAll(sql, builder, columns);
   }

   static void resolveInput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   { if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_FetchAll<T>::resolveInput(t, query, builder); return; } }

   static void resolveOutput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder, const QStringList & columns)
   {
      if ((columns.count() <= 0) || (columns.at(0) == "*")) { QxSqlQueryHelper_FetchAll<T>::resolveOutput(t, query, builder); return; }
      static_assert(qx::trait::is_qx_registered<T>::value, "qx::trait::is_qx_registered<T>::value");
      qx::IxSqlQueryBuilder::resolveOutput_FetchAll((& t), query, builder, columns);
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
