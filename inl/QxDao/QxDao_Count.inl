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
struct QxDao_Count
{

   static long count(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase)
   {
      T t; Q_UNUSED(t);
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "count", new qx::QxSqlQueryBuilder_Count<T>());
      if (! dao.isValid()) { return 0; }

      QString sql = dao.builder().buildSql().getSqlQuery();
      if (sql.isEmpty()) { dao.errEmpty(); return 0; }
      if (! query.isEmpty()) { dao.addQuery(query, true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { dao.errFailed(); return 0; }
      if (! dao.nextRecord()) { dao.errNoData(); return 0; }

      return static_cast<long>(dao.query().value(0).toLongLong());
   }

   static QSqlError count(long & lCount, const qx::QxSqlQuery & query, QSqlDatabase * pDatabase)
   {
      T t; Q_UNUSED(t); lCount = 0;
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "count", new qx::QxSqlQueryBuilder_Count<T>());
      if (! dao.isValid()) { return dao.error(); }

      QString sql = dao.builder().buildSql().getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(query, true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { return dao.errFailed(); }
      if (! dao.nextRecord()) { return dao.errNoData(); }
      lCount = static_cast<long>(dao.query().value(0).toLongLong());

      return dao.error();
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
