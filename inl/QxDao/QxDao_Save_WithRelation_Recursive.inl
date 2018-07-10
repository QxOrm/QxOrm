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
struct QxDao_Save_WithRelation_Recursive_Generic
{

   static QSqlError save(T & t, qx::dao::save_mode::e_save_mode eSaveMode, QSqlDatabase * pDatabase, qx::QxSqlRelationParams * pRelationParams)
   {
      QStringList relation("*");
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "save with relation recursive", new qx::QxSqlQueryBuilder_Update<T>());
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }
      if (! dao.updateSqlRelationX(relation)) { return dao.errInvalidRelation(); }
      if (! pDatabase) { dao.transaction(); }
      dao.quiet();

      qx::QxSqlRelationParams params(0, 0, NULL, (& dao.builder()), (& dao.query()), (& t));
      if (! pRelationParams) { params.setDatabase((& dao.database())); params.setSaveMode(eSaveMode); params.setRecursiveMode(true); }
      else { params = (* pRelationParams); params.setOwner(& t); }
      if (params.existRecursiveItem(& t)) { return dao.error(); }
      params.insertRecursiveItem(& t);

      qx::QxSqlRelationLinked * pRelationLinked = dao.getSqlRelationLinked();
      if (pRelationLinked) { dao.updateError(pRelationLinked->hierarchyOnBeforeSave(params)); }
      if (! dao.isValid()) { return dao.error(); }

      if (eSaveMode == qx::dao::save_mode::e_check_insert_or_update)
      {
         qx_bool bExist = dao.isValidPrimaryKey(t);
         if (bExist) { bExist = qx::dao::exist(t, (& dao.database())); }
         if (bExist) { dao.updateError(qx::dao::update(t, (& dao.database()))); }
         else { dao.updateError(qx::dao::insert(t, (& dao.database()))); }
      }
      else if (eSaveMode == qx::dao::save_mode::e_insert_only)
      { dao.updateError(qx::dao::insert(t, (& dao.database()))); }
      else if (eSaveMode == qx::dao::save_mode::e_update_only)
      { dao.updateError(qx::dao::update(t, (& dao.database()))); }
      else { qAssert(false); }

      if (! dao.isValid()) { return dao.error(); }
      if (pRelationLinked) { dao.updateError(pRelationLinked->hierarchyOnAfterSave(params)); }
      if (! dao.isValid()) { return dao.error(); }

      return dao.error();
   }

};

template <class T>
struct QxDao_Save_WithRelation_Recursive_Container
{

   static QSqlError save(T & t, qx::dao::save_mode::e_save_mode eSaveMode, QSqlDatabase * pDatabase, qx::QxSqlRelationParams * pRelationParams)
   {
      typedef typename qx::trait::generic_container<T>::type_value_qx type_item;

      QStringList relation("*");
      if (qx::trait::generic_container<T>::size(t) <= 0) { return QSqlError(); }
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "save with relation recursive", new qx::QxSqlQueryBuilder_Update<type_item>());
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }
      if (! dao.updateSqlRelationX(relation)) { return dao.errInvalidRelation(); }
      if (! pDatabase) { dao.transaction(); }
      dao.quiet();

      if (eSaveMode == qx::dao::save_mode::e_check_insert_or_update)
      {
         for (typename T::iterator it = t.begin(); it != t.end(); ++it)
         { if (! saveItem(eSaveMode, pRelationParams, (* it), dao)) { return dao.error(); } }
      }
      else if (eSaveMode == qx::dao::save_mode::e_insert_only)
      {
         for (typename T::iterator it = t.begin(); it != t.end(); ++it)
         { if (! hierarchyOnBeforeSave(eSaveMode, pRelationParams, (* it), dao)) { return dao.error(); } }
         dao.updateError(qx::dao::insert(t, (& dao.database())));
         if (! dao.isValid()) { return dao.error(); }
         for (typename T::iterator it = t.begin(); it != t.end(); ++it)
         { if (! hierarchyOnAfterSave(eSaveMode, pRelationParams, (* it), dao)) { return dao.error(); } }
      }
      else if (eSaveMode == qx::dao::save_mode::e_update_only)
      {
         for (typename T::iterator it = t.begin(); it != t.end(); ++it)
         { if (! hierarchyOnBeforeSave(eSaveMode, pRelationParams, (* it), dao)) { return dao.error(); } }
         dao.updateError(qx::dao::update(t, (& dao.database())));
         if (! dao.isValid()) { return dao.error(); }
         for (typename T::iterator it = t.begin(); it != t.end(); ++it)
         { if (! hierarchyOnAfterSave(eSaveMode, pRelationParams, (* it), dao)) { return dao.error(); } }
      }
      else { qAssert(false); }

      return dao.error();
   }

private:

   template <typename U>
   static inline bool saveItem(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   {
      bool bSaveOk = saveItem_Helper<U, boost::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::save(eSaveMode, pRelationParams, item, dao);
      if (bSaveOk) { qx::dao::detail::QxDao_Keep_Original<U>::backup(item); }
      return bSaveOk;
   }

   template <typename U>
   static inline bool hierarchyOnBeforeSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   {
      bool bBeforeSaveOk = saveItem_Helper<U, boost::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::hierarchyOnBeforeSave(eSaveMode, pRelationParams, item, dao);
      if (bBeforeSaveOk) { qx::dao::detail::QxDao_Keep_Original<U>::backup(item); }
      return bBeforeSaveOk;
   }

   template <typename U>
   static inline bool hierarchyOnAfterSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   {
      bool bAfterSaveOk = saveItem_Helper<U, boost::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::hierarchyOnAfterSave(eSaveMode, pRelationParams, item, dao);
      if (bAfterSaveOk) { qx::dao::detail::QxDao_Keep_Original<U>::backup(item); }
      return bAfterSaveOk;
   }

   template <typename U, bool bIsPointer /* = true */>
   struct saveItem_Helper
   {
      static inline bool save(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return (item ? qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::saveItem(eSaveMode, pRelationParams, (* item), dao) : false); }
      static inline bool hierarchyOnBeforeSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return (item ? qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::hierarchyOnBeforeSave(eSaveMode, pRelationParams, (* item), dao) : false); }
      static inline bool hierarchyOnAfterSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return (item ? qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::hierarchyOnAfterSave(eSaveMode, pRelationParams, (* item), dao) : false); }
   };

   template <typename U1, typename U2>
   struct saveItem_Helper<std::pair<U1, U2>, false>
   {
      static inline bool save(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::saveItem(eSaveMode, pRelationParams, item.second, dao); }
      static inline bool hierarchyOnBeforeSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::hierarchyOnBeforeSave(eSaveMode, pRelationParams, item.second, dao); }
      static inline bool hierarchyOnAfterSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::hierarchyOnAfterSave(eSaveMode, pRelationParams, item.second, dao); }
   };

   template <typename U1, typename U2>
   struct saveItem_Helper<const std::pair<U1, U2>, false>
   {
      static inline bool save(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, const std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::saveItem(eSaveMode, pRelationParams, item.second, dao); }
      static inline bool hierarchyOnBeforeSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, const std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::hierarchyOnBeforeSave(eSaveMode, pRelationParams, item.second, dao); }
      static inline bool hierarchyOnAfterSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, const std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::hierarchyOnAfterSave(eSaveMode, pRelationParams, item.second, dao); }
   };

   template <typename U1, typename U2>
   struct saveItem_Helper<QPair<U1, U2>, false>
   {
      static inline bool save(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::saveItem(eSaveMode, pRelationParams, item.second, dao); }
      static inline bool hierarchyOnBeforeSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::hierarchyOnBeforeSave(eSaveMode, pRelationParams, item.second, dao); }
      static inline bool hierarchyOnAfterSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::hierarchyOnAfterSave(eSaveMode, pRelationParams, item.second, dao); }
   };

   template <typename U1, typename U2>
   struct saveItem_Helper<const QPair<U1, U2>, false>
   {
      static inline bool save(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, const QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::saveItem(eSaveMode, pRelationParams, item.second, dao); }
      static inline bool hierarchyOnBeforeSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, const QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::hierarchyOnBeforeSave(eSaveMode, pRelationParams, item.second, dao); }
      static inline bool hierarchyOnAfterSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, const QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>::hierarchyOnAfterSave(eSaveMode, pRelationParams, item.second, dao); }
   };

   template <typename U>
   struct saveItem_Helper<U, false>
   {
      static bool save(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      {
         qx::QxSqlRelationParams params(0, 0, NULL, (& dao.builder()), (& dao.query()), (& item));
         if (! pRelationParams) { params.setDatabase((& dao.database())); params.setSaveMode(eSaveMode); params.setRecursiveMode(true); }
         else { params = (* pRelationParams); params.setOwner(& item); }
         if (params.existRecursiveItem(& item)) { return true; }
         params.insertRecursiveItem(& item);

         qx::QxSqlRelationLinked * pRelationLinked = dao.getSqlRelationLinked();
         if (pRelationLinked) { dao.updateError(pRelationLinked->hierarchyOnBeforeSave(params)); }
         if (! dao.isValid()) { return false; }

         if (eSaveMode == qx::dao::save_mode::e_check_insert_or_update)
         {
            qx_bool bExist = dao.isValidPrimaryKey(item);
            if (bExist) { bExist = qx::dao::exist(item, (& dao.database())); }
            if (bExist) { dao.updateError(qx::dao::update(item, (& dao.database()))); }
            else { dao.updateError(qx::dao::insert(item, (& dao.database()))); }
         }
         else if (eSaveMode == qx::dao::save_mode::e_insert_only)
         { dao.updateError(qx::dao::insert(item, (& dao.database()))); }
         else if (eSaveMode == qx::dao::save_mode::e_update_only)
         { dao.updateError(qx::dao::update(item, (& dao.database()))); }
         else { qAssert(false); }

         if (! dao.isValid()) { return false; }
         if (pRelationLinked) { dao.updateError(pRelationLinked->hierarchyOnAfterSave(params)); }
         if (! dao.isValid()) { return false; }

         return dao.isValid();
      }

      static bool hierarchyOnBeforeSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      {
         qx::QxSqlRelationParams params(0, 0, NULL, (& dao.builder()), (& dao.query()), (& item));
         if (! pRelationParams) { params.setDatabase((& dao.database())); params.setSaveMode(eSaveMode); params.setRecursiveMode(true); }
         else { params = (* pRelationParams); params.setOwner(& item); }

         qx::QxSqlRelationLinked * pRelationLinked = dao.getSqlRelationLinked();
         if (pRelationLinked) { dao.updateError(pRelationLinked->hierarchyOnBeforeSave(params)); }
         return dao.isValid();
      }

      static bool hierarchyOnAfterSave(qx::dao::save_mode::e_save_mode eSaveMode, qx::QxSqlRelationParams * pRelationParams, U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      {
         qx::QxSqlRelationParams params(0, 0, NULL, (& dao.builder()), (& dao.query()), (& item));
         if (! pRelationParams) { params.setDatabase((& dao.database())); params.setSaveMode(eSaveMode); params.setRecursiveMode(true); }
         else { params = (* pRelationParams); params.setOwner(& item); }
         if (params.existRecursiveItem(& item)) { return true; }
         params.insertRecursiveItem(& item);

         qx::QxSqlRelationLinked * pRelationLinked = dao.getSqlRelationLinked();
         if (pRelationLinked) { dao.updateError(pRelationLinked->hierarchyOnAfterSave(params)); }
         return dao.isValid();
      }
   };

};

template <class T>
struct QxDao_Save_WithRelation_Recursive_Ptr
{

   static inline QSqlError save(T & t, qx::dao::save_mode::e_save_mode eSaveMode, QSqlDatabase * pDatabase, qx::QxSqlRelationParams * pRelationParams)
   { return (t ? qx::dao::save_with_relation_recursive((* t), eSaveMode, pDatabase, pRelationParams) : QSqlError()); }

};

template <class T>
struct QxDao_Save_WithRelation_Recursive
{

   static inline QSqlError save(T & t, qx::dao::save_mode::e_save_mode eSaveMode, QSqlDatabase * pDatabase, qx::QxSqlRelationParams * pRelationParams)
   {
      typedef typename boost::mpl::if_c< boost::is_pointer<T>::value, qx::dao::detail::QxDao_Save_WithRelation_Recursive_Ptr<T>, qx::dao::detail::QxDao_Save_WithRelation_Recursive_Generic<T> >::type type_dao_1;
      typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_Save_WithRelation_Recursive_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_Save_WithRelation_Recursive_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::save(t, eSaveMode, pDatabase, pRelationParams);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
