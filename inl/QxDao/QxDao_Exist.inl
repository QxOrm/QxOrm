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
struct QxDao_Exist_Generic
{

   static qx_bool exist(T & t, QSqlDatabase * pDatabase)
   {
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "exist", new qx::QxSqlQueryBuilder_Exist<T>());
      if (! dao.isValid()) { return qx_bool(false); }

      QString sql = dao.builder().buildSql().getSqlQuery();
      if (! dao.getDataId() || sql.isEmpty()) { dao.errEmpty(); return qx_bool(false); }
      if (! dao.query().prepare(sql)) { dao.errFailed(true); return qx_bool(false); }
      qx::dao::detail::QxSqlQueryHelper_Exist<T>::resolveInput(t, dao.query(), dao.builder());
      if (! dao.query().exec()) { dao.errFailed(); return qx_bool(false); }

      return qx_bool(dao.nextRecord());
   }

};

template <class T>
struct QxDao_Exist_Container
{

   static qx_bool exist(T & t, QSqlDatabase * pDatabase)
   {
      typedef typename qx::trait::generic_container<T>::type_value_qx type_item;

      if (qx::trait::generic_container<T>::size(t) <= 0) { return qx_bool(false); }
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "exist", new qx::QxSqlQueryBuilder_Exist<type_item>());
      if (! dao.isValid()) { return qx_bool(false); }

      QString sql = dao.builder().buildSql().getSqlQuery();
      if (sql.isEmpty()) { dao.errEmpty(); return qx_bool(false); }
      if (! dao.query().prepare(sql)) { dao.errFailed(true); return qx_bool(false); }

      for (typename T::iterator it = t.begin(); it != t.end(); ++it)
      { if (! existItem((* it), dao)) { return qx_bool(false); } }

      return qx_bool(true);
   }

private:

   template <typename U>
   static inline bool existItem(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   { return existItem_Helper<U, std::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::exist(item, dao); }

   template <typename U, bool bIsPointer /* = true */>
   struct existItem_Helper
   {
      static inline bool exist(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return (item ? qx::dao::detail::QxDao_Exist_Container<T>::existItem((* item), dao) : false); }
   };

   template <typename U1, typename U2>
   struct existItem_Helper<std::pair<U1, U2>, false>
   {
      static inline bool exist(std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Exist_Container<T>::existItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct existItem_Helper<const std::pair<U1, U2>, false>
   {
      static inline bool exist(const std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Exist_Container<T>::existItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct existItem_Helper<QPair<U1, U2>, false>
   {
      static inline bool exist(QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Exist_Container<T>::existItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct existItem_Helper<const QPair<U1, U2>, false>
   {
      static inline bool exist(const QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Exist_Container<T>::existItem(item.second, dao); }
   };

   template <typename U>
   struct existItem_Helper<U, false>
   {
      static bool exist(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      {
         qx::dao::detail::QxSqlQueryHelper_Exist<U>::resolveInput(item, dao.query(), dao.builder());
         if (! dao.query().exec()) { dao.errFailed(); return false; }

         return dao.nextRecord();
      }
   };

};

template <class T>
struct QxDao_Exist_Ptr
{

   static inline qx_bool exist(T & t, QSqlDatabase * pDatabase)
   { return (t ? qx::dao::exist((* t), pDatabase) : qx_bool(false)); }

};

template <class T>
struct QxDao_Exist
{

   static inline qx_bool exist(T & t, QSqlDatabase * pDatabase)
   {
      typedef typename std::conditional< std::is_pointer<T>::value, qx::dao::detail::QxDao_Exist_Ptr<T>, qx::dao::detail::QxDao_Exist_Generic<T> >::type type_dao_1;
      typedef typename std::conditional< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_Exist_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename std::conditional< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_Exist_Container<T>, type_dao_2 >::type type_dao_3;
      return type_dao_3::exist(t, pDatabase);
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
