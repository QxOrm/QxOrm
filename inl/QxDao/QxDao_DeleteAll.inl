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
struct QxDao_DeleteAll
{

   static QSqlError deleteAll(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase, bool bVerifySoftDelete)
   {
      T t; Q_UNUSED(t);
      qx::IxSqlQueryBuilder * pBuilder = new qx::QxSqlQueryBuilder_DeleteAll<T>(); pBuilder->init();
      qx::QxSoftDelete oSoftDelete = pBuilder->getSoftDelete();
      if (bVerifySoftDelete && ! oSoftDelete.isEmpty())
      { delete pBuilder; pBuilder = new qx::QxSqlQueryBuilder_SoftDeleteAll<T>(); }

      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "delete all", pBuilder);
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }

      QString sql = dao.builder().buildSql().getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! pDatabase) { dao.transaction(); }
      if (! query.isEmpty()) { dao.addQuery(query, true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { return dao.errFailed(); }

      return dao.error();
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
