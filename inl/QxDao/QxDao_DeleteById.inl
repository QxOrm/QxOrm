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
struct QxDao_DeleteById_Generic
{

   static QSqlError deleteById(T & t, QSqlDatabase * pDatabase)
   {
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "delete by id");
      if (! dao.isValid()) { return dao.error(); }
      if (! dao.isValidPrimaryKey(t)) { return dao.errInvalidId(); }

      QString sql = dao.builder().deleteById().getSqlQuery();
      if (! dao.getDataId() || sql.isEmpty()) { return dao.errEmpty(); }
      dao.query().prepare(sql);

      qx::dao::on_before_delete<T>((& t), (& dao));
      qx::dao::detail::QxSqlQueryHelper_DeleteById<T>::resolveInput(t, dao.query(), dao.builder());
      if (! dao.query().exec()) { return dao.errFailed(); }
      qx::dao::on_after_delete<T>((& t), (& dao));

      return dao.error();
   }

};

template <class T>
struct QxDao_DeleteById_Container
{

   static QSqlError deleteById(T & t, QSqlDatabase * pDatabase)
   {
      if (qx::trait::generic_container<T>::size(t) <= 0) { return QSqlError(); }
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "delete by id");
      if (! dao.isValid()) { return dao.error(); }

      QString sql = dao.builder().deleteById().getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      dao.query().prepare(sql);

      for (typename T::iterator it = t.begin(); it != t.end(); ++it)
      { if (! deleteItem((* it), dao)) { return dao.error(); } }

      return dao.error();
   }

private:

   template <typename U>
   static inline bool deleteItem(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   { return deleteItem_Helper<U, boost::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::deleteById(item, dao); }

   template <typename U, bool bIsPointer /* = true */>
   struct deleteItem_Helper
   {
      static inline bool deleteById(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return (item ? qx::dao::detail::QxDao_DeleteById_Container<T>::deleteItem((* item), dao) : true); }
   };

   template <typename U1, typename U2>
   struct deleteItem_Helper<std::pair<U1, U2>, false>
   {
      static inline bool deleteById(std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_DeleteById_Container<T>::deleteItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct deleteItem_Helper<const std::pair<U1, U2>, false>
   {
      static inline bool deleteById(const std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_DeleteById_Container<T>::deleteItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct deleteItem_Helper<QPair<U1, U2>, false>
   {
      static inline bool deleteById(QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_DeleteById_Container<T>::deleteItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct deleteItem_Helper<const QPair<U1, U2>, false>
   {
      static inline bool deleteById(const QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_DeleteById_Container<T>::deleteItem(item.second, dao); }
   };

   template <typename U>
   struct deleteItem_Helper<U, false>
   {
      static bool deleteById(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      {
         if (! dao.isValidPrimaryKey(item)) { dao.errInvalidId(); return false; }
         qx::dao::on_before_delete<U>((& item), (& dao));
         qx::dao::detail::QxSqlQueryHelper_DeleteById<U>::resolveInput(item, dao.query(), dao.builder());
         if (! dao.query().exec()) { dao.errFailed(); return false; }
         qx::dao::on_after_delete<U>((& item), (& dao));

         return dao.isValid();
      }
   };

};

template <class T>
struct QxDao_DeleteById_Ptr
{

   static inline QSqlError deleteById(T & t, QSqlDatabase * pDatabase)
   { qAssert(t != NULL); return (t ? qx::dao::delete_by_id((* t), pDatabase) : QSqlError()); }

};

template <class T>
struct QxDao_DeleteById
{

   static inline QSqlError deleteById(T & t, QSqlDatabase * pDatabase)
   {
      typedef typename boost::mpl::if_c< boost::is_pointer<T>::value, qx::dao::detail::QxDao_DeleteById_Ptr<T>, qx::dao::detail::QxDao_DeleteById_Generic<T> >::type type_dao_1;
      typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_DeleteById_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_DeleteById_Container<T>, type_dao_2 >::type type_dao_3;
      return type_dao_3::deleteById(t, pDatabase);
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
