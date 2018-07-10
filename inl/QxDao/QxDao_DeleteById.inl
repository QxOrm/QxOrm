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
struct QxDao_DeleteById_Generic
{

   static QSqlError deleteById(T & t, QSqlDatabase * pDatabase, bool bVerifySoftDelete)
   {
      qx::IxSqlQueryBuilder * pBuilder = new qx::QxSqlQueryBuilder_DeleteById<T>(); pBuilder->init();
      qx::QxSoftDelete oSoftDelete = pBuilder->getSoftDelete();
      if (bVerifySoftDelete && ! oSoftDelete.isEmpty())
      { delete pBuilder; pBuilder = new qx::QxSqlQueryBuilder_SoftDeleteById<T>(); }

      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "delete by id", pBuilder);
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }
      if (! dao.isValidPrimaryKey(t)) { return dao.errInvalidId(); }

      QString sql = dao.builder().buildSql().getSqlQuery();
      if (! dao.getDataId() || sql.isEmpty()) { return dao.errEmpty(); }
      if (! dao.query().prepare(sql)) { return dao.errFailed(true); }

      IxSqlGenerator * pSqlGenerator = dao.getSqlGenerator();
      if (pSqlGenerator) { pSqlGenerator->onBeforeDelete((& dao), (& t)); }
      qx::dao::on_before_delete<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
      qx::dao::detail::QxSqlQueryHelper_DeleteById<T>::resolveInput(t, dao.query(), dao.builder());
      if (! dao.query().exec()) { return dao.errFailed(); }
      if (pSqlGenerator) { pSqlGenerator->onAfterDelete((& dao), (& t)); }
      qx::dao::on_after_delete<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }

      return dao.error();
   }

};

template <class T>
struct QxDao_DeleteById_Container
{

   static QSqlError deleteById(T & t, QSqlDatabase * pDatabase, bool bVerifySoftDelete)
   {
      typedef typename qx::trait::generic_container<T>::type_value_qx type_item;

      qx::IxSqlQueryBuilder * pBuilder = new qx::QxSqlQueryBuilder_DeleteById<type_item>(); pBuilder->init();
      qx::QxSoftDelete oSoftDelete = pBuilder->getSoftDelete();
      if (bVerifySoftDelete && ! oSoftDelete.isEmpty())
      { delete pBuilder; pBuilder = new qx::QxSqlQueryBuilder_SoftDeleteById<type_item>(); }

      if (qx::trait::generic_container<T>::size(t) <= 0) { return QSqlError(); }
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "delete by id", pBuilder);
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }

      QString sql = dao.builder().buildSql().getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! dao.query().prepare(sql)) { return dao.errFailed(true); }

      for (typename T::iterator it = t.begin(); it != t.end(); ++it)
      { if (! deleteItem((* it), dao)) { return dao.error(); } }

      return dao.error();
   }

private:

   template <typename U>
   static inline bool deleteItem(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   { return deleteItem_Helper<U, std::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::deleteById(item, dao); }

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
         IxSqlGenerator * pSqlGenerator = dao.getSqlGenerator();
         if (pSqlGenerator) { pSqlGenerator->onBeforeDelete((& dao), (& item)); }
         qx::dao::on_before_delete<U>((& item), (& dao)); if (! dao.isValid()) { return false; }
         qx::dao::detail::QxSqlQueryHelper_DeleteById<U>::resolveInput(item, dao.query(), dao.builder());
         if (! dao.query().exec()) { dao.errFailed(); return false; }
         if (pSqlGenerator) { pSqlGenerator->onAfterDelete((& dao), (& item)); }
         qx::dao::on_after_delete<U>((& item), (& dao)); if (! dao.isValid()) { return false; }

         return dao.isValid();
      }
   };

};

template <class T>
struct QxDao_DeleteById_Ptr
{

   static inline QSqlError deleteById(T & t, QSqlDatabase * pDatabase, bool bVerifySoftDelete)
   {
      if (! t) { return QSqlError(); }
      if (bVerifySoftDelete) { return qx::dao::delete_by_id((* t), pDatabase); }
      return qx::dao::destroy_by_id((* t), pDatabase);
   }

};

template <class T>
struct QxDao_DeleteById
{

   static inline QSqlError deleteById(T & t, QSqlDatabase * pDatabase, bool bVerifySoftDelete)
   {
      typedef typename std::conditional< std::is_pointer<T>::value, qx::dao::detail::QxDao_DeleteById_Ptr<T>, qx::dao::detail::QxDao_DeleteById_Generic<T> >::type type_dao_1;
      typedef typename std::conditional< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_DeleteById_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename std::conditional< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_DeleteById_Container<T>, type_dao_2 >::type type_dao_3;
      return type_dao_3::deleteById(t, pDatabase, bVerifySoftDelete);
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
