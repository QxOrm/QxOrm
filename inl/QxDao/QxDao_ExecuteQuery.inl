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
struct QxDao_ExecuteQuery_Generic
{

   static QSqlError executeQuery(qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "execute custom sql query or stored procedure", new qx::QxSqlQueryBuilder_Count<T>());
      if (! dao.isValid()) { return dao.error(); }

      QString sql = query.query();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      dao.builder().setSqlQuery(sql);
      if (! dao.query().prepare(sql)) { return dao.errFailed(true); }
      query.resolve(dao.query());
      if (! dao.query().exec()) { return dao.errFailed(); }
      query.resolveOutput(dao.query(), false);
      if (! dao.nextRecord()) { return dao.error(); }
      qx::dao::on_before_fetch<T>((& t), (& dao));
      if (! dao.isValid()) { return dao.error(); }

      qx::IxDataMemberX * pDataMemberX = dao.builder().getDataMemberX();
      if (! pDataMemberX) { qAssert(false); return dao.error(); }
      QSqlRecord record = dao.query().record();
      for (int i = 0; i < record.count(); i++)
      {
         if (! pDataMemberX->exist_WithDaoStrategy(record.fieldName(i))) { continue; }
         qx::IxDataMember * pDataMember = pDataMemberX->get_WithDaoStrategy(record.fieldName(i));
         if (pDataMember) { pDataMember->fromVariant((& t), record.value(i), -1, qx::cvt::context::e_database); }
      }

      qx::dao::on_after_fetch<T>((& t), (& dao));
      return dao.error();
   }

};

template <class T>
struct QxDao_ExecuteQuery_Container
{

   static QSqlError executeQuery(qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      typedef typename qx::trait::generic_container<T>::type_value_qx type_item;

      qx::trait::generic_container<T>::clear(t);
      qx::IxSqlQueryBuilder * pBuilder = new qx::QxSqlQueryBuilder_Count<type_item>();
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "execute custom sql query or stored procedure", pBuilder);
      if (! dao.isValid()) { return dao.error(); }

      QString sql = query.query();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      dao.builder().setSqlQuery(sql);
      if (! dao.query().prepare(sql)) { return dao.errFailed(true); }
      query.resolve(dao.query());
      if (! dao.query().exec()) { return dao.errFailed(); }
      query.resolveOutput(dao.query(), false);

      QVector< QPair<int, qx::IxDataMember *> > vColumnToFetch;
      bool bSize = (dao.hasFeature(QSqlDriver::QuerySize) && (dao.query().size() > 0));
      if (bSize) { qx::trait::generic_container<T>::reserve(t, dao.query().size()); }
      while (dao.nextRecord()) { insertNewItem(t, dao, vColumnToFetch); if (! dao.isValid()) { return dao.error(); } }
      if (bSize) { qAssert(qx::trait::generic_container<T>::size(t) == static_cast<long>(dao.query().size())); }

      return dao.error();
   }

private:

   static void insertNewItem(T & t, qx::dao::detail::QxDao_Helper_Container<T> & dao, QVector< QPair<int, qx::IxDataMember *> > & vColumnToFetch)
   {
      typedef typename qx::trait::generic_container<T>::type_item type_item;
      typedef typename type_item::type_value_qx type_value_qx;

      type_item item = qx::trait::generic_container<T>::createItem();
      type_value_qx & item_val = item.value_qx();
      qx::IxDataMember * pId = dao.getDataId(); QVariant vId;
      qx::dao::on_before_fetch<type_value_qx>((& item_val), (& dao));
      if (! dao.isValid()) { return; }

      if (vColumnToFetch.count() <= 0)
      {
         qx::IxDataMemberX * pDataMemberX = dao.builder().getDataMemberX();
         if (! pDataMemberX) { qAssert(false); return; }
         QSqlRecord record = dao.query().record();
         vColumnToFetch.reserve(record.count());
         for (int i = 0; i < record.count(); i++)
         {
            if (! pDataMemberX->exist_WithDaoStrategy(record.fieldName(i))) { continue; }
            qx::IxDataMember * pDataMember = pDataMemberX->get_WithDaoStrategy(record.fieldName(i));
            if (pDataMember) { vColumnToFetch.append(qMakePair(i, pDataMember)); }
         }
      }

      for (int j = 0; j < vColumnToFetch.count(); j++)
      {
         QVariant vValue = dao.query().value(vColumnToFetch[j].first);
         vColumnToFetch[j].second->fromVariant((& item_val), vValue, -1, qx::cvt::context::e_database);
         if (pId == vColumnToFetch[j].second) { vId = vValue; }
      }

      if (! vId.isValid())
      { vId = QVariant(static_cast<qlonglong>(qx::trait::generic_container<T>::size(t))); }
      qx::cvt::from_variant(vId, item.key(), "", -1, qx::cvt::context::e_database);
      qx::dao::on_after_fetch<type_value_qx>((& item_val), (& dao)); if (! dao.isValid()) { return; }
      qx::dao::detail::QxDao_Keep_Original<type_item>::backup(item);
      qx::trait::generic_container<T>::insertItem(t, item);
   }

};

template <class T>
struct QxDao_ExecuteQuery_Ptr
{

   static inline QSqlError executeQuery(qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   { if (! t) { qx::trait::construct_ptr<T>::get(t); }; return qx::dao::execute_query(query, (* t), pDatabase); }

};

template <class T>
struct QxDao_ExecuteQuery
{

   static inline QSqlError executeQuery(qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
   {
      typedef typename boost::mpl::if_c< boost::is_pointer<T>::value, qx::dao::detail::QxDao_ExecuteQuery_Ptr<T>, qx::dao::detail::QxDao_ExecuteQuery_Generic<T> >::type type_dao_1;
      typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_ExecuteQuery_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_ExecuteQuery_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::executeQuery(query, t, pDatabase);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
