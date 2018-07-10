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
struct QxDao_DeleteAll
{

   static QSqlError deleteAll(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase, bool bVerifySoftDelete)
   {
      T t; Q_UNUSED(t);
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "delete all");
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }

      QString sql; qx::QxSoftDelete oSoftDelete = dao.builder().getSoftDelete();
      if (bVerifySoftDelete && ! oSoftDelete.isEmpty()) { sql = dao.builder().softDeleteAll().getSqlQuery(); }
      else { sql = dao.builder().deleteAll().getSqlQuery(); }
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
