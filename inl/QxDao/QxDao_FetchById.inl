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
struct QxDao_FetchById_Generic
{

   static QSqlError fetchById(T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "fetch by id", new qx::QxSqlQueryBuilder_FetchById<T>());
      if (! dao.isValid()) { return dao.error(); }
      if (! dao.isValidPrimaryKey(t)) { return dao.errInvalidId(); }

      QString sql = dao.builder().buildSql(columns).getSqlQuery();
      if (! dao.getDataId() || sql.isEmpty()) { return dao.errEmpty(); }
      if (! dao.query().prepare(sql)) { return dao.errFailed(true); }

      qx::dao::on_before_fetch<T>((& t), (& dao));
      if (! dao.isValid()) { return dao.error(); }
      qx::dao::detail::QxSqlQueryHelper_FetchById<T>::resolveInput(t, dao.query(), dao.builder(), columns);
      if (! dao.query().exec()) { return dao.errFailed(); }
      if (! dao.nextRecord()) { return dao.errNoData(); }
      qx::dao::detail::QxSqlQueryHelper_FetchById<T>::resolveOutput(t, dao.query(), dao.builder(), columns);
      qx::dao::on_after_fetch<T>((& t), (& dao));

      return dao.error();
   }

};

template <class T>
struct QxDao_FetchById_Container
{

   static QSqlError fetchById(T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      typedef typename qx::trait::generic_container<T>::type_value_qx type_item;

      if (qx::trait::generic_container<T>::size(t) <= 0) { return QSqlError(); }
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "fetch by id", new qx::QxSqlQueryBuilder_FetchById<type_item>());
      if (! dao.isValid()) { return dao.error(); }

      QString sql = dao.builder().buildSql(columns).getSqlQuery();
      if (! dao.getDataId() || sql.isEmpty()) { return dao.errEmpty(); }
      if (! dao.query().prepare(sql)) { return dao.errFailed(true); }
      dao.setSqlColumns(columns);

      for (typename T::iterator it = t.begin(); it != t.end(); ++it)
      { if (! fetchItem((* it), dao)) { return dao.error(); } }

      return dao.error();
   }

private:

   template <typename U>
   static inline bool fetchItem(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   {
      bool bFetchOk = fetchItem_Helper<U, std::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::fetch(item, dao);
      if (bFetchOk) { qx::dao::detail::QxDao_Keep_Original<U>::backup(item); }
      return bFetchOk;
   }

   template <typename U, bool bIsPointer /* = true */>
   struct fetchItem_Helper
   {
      static inline bool fetch(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return (item ? qx::dao::detail::QxDao_FetchById_Container<T>::fetchItem((* item), dao) : true); }
   };

   template <typename U1, typename U2>
   struct fetchItem_Helper<std::pair<U1, U2>, false>
   {
      static inline bool fetch(std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_FetchById_Container<T>::fetchItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct fetchItem_Helper<const std::pair<U1, U2>, false>
   {
      static inline bool fetch(const std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_FetchById_Container<T>::fetchItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct fetchItem_Helper<QPair<U1, U2>, false>
   {
      static inline bool fetch(QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_FetchById_Container<T>::fetchItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct fetchItem_Helper<const QPair<U1, U2>, false>
   {
      static inline bool fetch(const QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_FetchById_Container<T>::fetchItem(item.second, dao); }
   };

   template <typename U>
   struct fetchItem_Helper<U, false>
   {
      static bool fetch(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      {
         QStringList columns = dao.getSqlColumns();
         if (! dao.isValidPrimaryKey(item)) { dao.errInvalidId(); return false; }
         qx::dao::on_before_fetch<U>((& item), (& dao)); if (! dao.isValid()) { return false; }
         qx::dao::detail::QxSqlQueryHelper_FetchById<U>::resolveInput(item, dao.query(), dao.builder(), columns);
         if (! dao.query().exec()) { dao.errFailed(); return false; }
         if (! dao.nextRecord()) { dao.errNoData(); return false; }
         qx::dao::detail::QxSqlQueryHelper_FetchById<U>::resolveOutput(item, dao.query(), dao.builder(), columns);
         qx::dao::on_after_fetch<U>((& item), (& dao));

         return dao.isValid();
      }
   };

};

template <class T>
struct QxDao_FetchById_Ptr
{

   static inline QSqlError fetchById(T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   { if (! t) { qx::trait::construct_ptr<T>::get(t); }; return qx::dao::fetch_by_id((* t), pDatabase, columns); }

};

template <class T>
struct QxDao_FetchById
{

   static inline QSqlError fetchById(T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      typedef typename std::conditional< std::is_pointer<T>::value, qx::dao::detail::QxDao_FetchById_Ptr<T>, qx::dao::detail::QxDao_FetchById_Generic<T> >::type type_dao_1;
      typedef typename std::conditional< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_FetchById_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename std::conditional< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_FetchById_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::fetchById(t, pDatabase, columns);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
