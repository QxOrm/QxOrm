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
struct QxSqlQueryHelper_FetchById_WithRelation
{

   static void sql(qx::QxSqlRelationLinked * pRelationX, QString & sql, qx::IxSqlQueryBuilder & builder)
   {
      static_assert(qx::trait::is_qx_registered<T>::value, "qx::trait::is_qx_registered<T>::value");
      if (! pRelationX) { qAssert(false); QxSqlQueryHelper_FetchById<T>::sql(sql, builder); return; }
      qx::IxSqlQueryBuilder::sql_FetchById_WithRelation(pRelationX, sql, builder);
   }

   static void resolveInput(qx::QxSqlRelationLinked * pRelationX, T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   {
      static_assert(qx::trait::is_qx_registered<T>::value, "qx::trait::is_qx_registered<T>::value");
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
