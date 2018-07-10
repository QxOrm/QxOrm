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
struct QxDao_FetchAll_Generic
{

   static QSqlError fetchAll(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "fetch all");
      if (! dao.isValid()) { return dao.error(); }

      QString sql = dao.builder().fetchAll(columns).getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(query, true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { return dao.errFailed(); }
      if (dao.nextRecord()) { qx::dao::detail::QxSqlQueryHelper_FetchAll<T>::resolveOutput(t, dao.query(), dao.builder(), columns); }

      return dao.error();
   }

};

template <class T>
struct QxDao_FetchAll_Container
{

   static QSqlError fetchAll(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      qx::trait::generic_container<T>::clear(t);
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "fetch all");
      if (! dao.isValid()) { return dao.error(); }

      QString sql = dao.builder().fetchAll(columns).getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(query, true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { return dao.errFailed(); }
      dao.setSqlColumns(columns);

      bool bSize = (dao.hasFeature(QSqlDriver::QuerySize) && (dao.query().size() > 0));
      if (bSize) { qx::trait::generic_container<T>::reserve(t, dao.query().size()); }
      while (dao.nextRecord()) { insertNewItem(t, dao); }
      if (bSize) { qAssert(qx::trait::generic_container<T>::size(t) == static_cast<long>(dao.query().size())); }

      return dao.error();
   }

private:

   static void insertNewItem(T & t, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   {
      typedef typename qx::trait::generic_container<T>::type_item type_item;
      typedef typename type_item::type_value_qx type_value_qx;
      type_item item = qx::trait::generic_container<T>::createItem();
      type_value_qx & item_val = item.value_qx();
      qx::IxDataMember * pId = dao.getDataId(); qAssert(pId);
      QStringList columns = dao.getSqlColumns();
      if (pId) { for (int i = 0; i < pId->getNameCount(); i++) { QVariant v = dao.query().value(i); qx::cvt::from_variant(v, item.key(), "", i); } }
      qx::dao::detail::QxSqlQueryHelper_FetchAll<type_value_qx>::resolveOutput(item_val, dao.query(), dao.builder(), columns);
      qx::dao::detail::QxDao_Keep_Original<type_item>::backup(item);
      qx::trait::generic_container<T>::insertItem(t, item);
   }

};

template <class T>
struct QxDao_FetchAll_Ptr
{

   static inline QSqlError fetchAll(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   { qAssert(t != NULL); return (t ? qx::dao::fetch_by_query(query, (* t), pDatabase, columns) : QSqlError()); }

};

template <class T>
struct QxDao_FetchAll
{

   static inline QSqlError fetchAll(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      typedef typename boost::mpl::if_c< boost::is_pointer<T>::value, qx::dao::detail::QxDao_FetchAll_Ptr<T>, qx::dao::detail::QxDao_FetchAll_Generic<T> >::type type_dao_1;
      typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_FetchAll_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_FetchAll_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::fetchAll(query, t, pDatabase, columns);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
