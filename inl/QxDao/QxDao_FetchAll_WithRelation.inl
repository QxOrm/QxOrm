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
struct QxDao_FetchAll_WithRelation_Generic
{

   typedef qx::dao::detail::QxDao_Helper<T> type_dao_helper;
   typedef qx::dao::detail::QxSqlQueryHelper_FetchAll_WithRelation<T> type_query_helper;

   static QSqlError fetchAll(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      type_dao_helper dao(t, pDatabase, "fetch all with relation");
      if (! dao.isValid()) { return dao.error(); }
      if (! dao.updateSqlRelationX(relation)) { return dao.errInvalidRelation(); }

      QString sql = dao.builder().fetchAll_WithRelation(dao.getSqlRelationX()).getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(query, true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { return dao.errFailed(); }

      qx::dao::on_before_fetch<T>((& t), (& dao));
      if (dao.getCartesianProduct()) { fetchAll_Complex(t, dao); }
      else { fetchAll_Simple(t, dao); }
      qx::dao::on_after_fetch<T>((& t), (& dao));

      return dao.error();
   }

private:

   static inline void fetchAll_Simple(T & t, type_dao_helper & dao)
   {
      if (dao.nextRecord())
      { type_query_helper::resolveOutput(dao.getSqlRelationX(), t, dao.query(), dao.builder()); }
   }

   static inline void fetchAll_Complex(T & t, type_dao_helper & dao)
   {
      while (dao.nextRecord())
      { type_query_helper::resolveOutput(dao.getSqlRelationX(), t, dao.query(), dao.builder()); }
   }

};

template <class T>
struct QxDao_FetchAll_WithRelation_Container
{

   typedef qx::dao::detail::QxDao_Helper_Container<T> type_dao_helper;
   typedef qx::dao::detail::QxDao_FetchAll_WithRelation_Container<T> type_this;
   typedef qx::trait::generic_container<T> type_generic_container;
   typedef typename type_generic_container::type_item type_item;
   typedef typename type_item::type_value_qx type_value_qx;
   typedef qx::dao::detail::QxSqlQueryHelper_FetchAll_WithRelation<type_value_qx> type_query_helper;

   static QSqlError fetchAll(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      type_generic_container::clear(t);
      type_dao_helper dao(t, pDatabase, "fetch all with relation");
      if (! dao.isValid()) { return dao.error(); }
      if (! dao.updateSqlRelationX(relation)) { return dao.errInvalidRelation(); }

      bool bComplex = dao.getCartesianProduct(); QVariant vId;
      QString sql = dao.builder().fetchAll_WithRelation(dao.getSqlRelationX()).getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(query, true); sql = dao.builder().getSqlQuery(); }
      if (! dao.exec()) { return dao.errFailed(); }
      bool bSize = (dao.hasFeature(QSqlDriver::QuerySize) && (dao.query().size() > 0));
      if (bSize) { type_generic_container::reserve(t, dao.query().size()); }

      while (dao.nextRecord())
      {
         qx::IxDataMember * pId = dao.getDataId(); qAssert(pId);
         if (pId) { QString sId; for (int i = 0; i < pId->getNameCount(); i++) { sId += dao.query().value(i).toString() + "|"; }; vId = sId; }
         void * pItemTmp = (bComplex ? dao.builder().existIdX(0, vId, vId) : NULL);
         if (! pItemTmp) { insertNewItem(t, dao); continue; }
         type_value_qx * pItem = static_cast<type_value_qx *>(pItemTmp);
         type_query_helper::resolveOutput(dao.getSqlRelationX(), (* pItem), dao.query(), dao.builder());
      }

      if (bSize) { type_generic_container::reserve(t, type_generic_container::size(t)); }
      return dao.error();
   }

private:

   static void insertNewItem(T & t, type_dao_helper & dao)
   {
      type_item item = type_generic_container::createItem();
      type_value_qx & item_val = item.value_qx();
      qx::IxDataMember * pId = dao.getDataId(); qAssert(pId);
      if (pId) { for (int i = 0; i < pId->getNameCount(); i++) { QVariant v = dao.query().value(i); qx::cvt::from_variant(v, item.key(), "", i); } }
      qx::dao::on_before_fetch<type_value_qx>((& item_val), (& dao));
      type_query_helper::resolveOutput(dao.getSqlRelationX(), item_val, dao.query(), dao.builder());
      qx::dao::on_after_fetch<type_value_qx>((& item_val), (& dao));
      type_generic_container::insertItem(t, item);
      qx::dao::detail::QxDao_Keep_Original<type_item>::backup(item);
   }

};

template <class T>
struct QxDao_FetchAll_WithRelation_Ptr
{

   static inline QSqlError fetchAll(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   { return (t ? qx::dao::fetch_by_query_with_relation(relation, query, (* t), pDatabase) : QSqlError()); }

};

template <class T>
struct QxDao_FetchAll_WithRelation
{

   static inline QSqlError fetchAll(const QString & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      QStringList lst;
      if (! relation.isEmpty()) { lst = relation.split("|"); }
      return QxDao_FetchAll_WithRelation<T>::fetchAll(lst, query, t, pDatabase);
   }

   static inline QSqlError fetchAll(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      typedef typename boost::mpl::if_c< boost::is_pointer<T>::value, qx::dao::detail::QxDao_FetchAll_WithRelation_Ptr<T>, qx::dao::detail::QxDao_FetchAll_WithRelation_Generic<T> >::type type_dao_1;
      typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_FetchAll_WithRelation_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_FetchAll_WithRelation_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::fetchAll(relation, query, t, pDatabase);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
