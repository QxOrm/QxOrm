/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxSqlQueryHelper_FetchById_WithRelation
{

   static void sql(qx::IxSqlRelationX * pRelationX, QString & sql, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      if (! pRelationX || (pRelationX->count() <= 0)) { qAssert(false); QxSqlQueryHelper_FetchById<T>::sql(sql, builder); return; }
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      QString table = builder.table();
      sql = builder.fetchAll_WithRelation(pRelationX).getSqlQuery();
      sql += " WHERE " + pId->getSqlAlias(& table) + " = " + pId->getSqlPlaceHolder();
   }

   static void resolveInput(qx::IxSqlRelationX * pRelationX, T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   {
      Q_UNUSED(pRelationX);
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      if (! pRelationX || (pRelationX->count() <= 0)) { qAssert(false); QxSqlQueryHelper_FetchById<T>::resolveInput(t, query, builder); return; }
      qx::IxDataMember * pId = builder.getDataId(); qAssert(pId);
      pId->setSqlPlaceHolder(query, (& t));
   }

   static void resolveOutput(qx::IxSqlRelationX * pRelationX, T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   { QxSqlQueryHelper_FetchAll_WithRelation<T>::resolveOutput(pRelationX, t, query, builder); }

};

} // namespace detail
} // namespace dao
} // namespace qx
