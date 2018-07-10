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
struct QxDao_Insert_WithRelation_Generic
{

   static QSqlError insert(const QStringList & relation, T & t, QSqlDatabase * pDatabase)
   {
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "insert with relation", new qx::QxSqlQueryBuilder_Insert<T>());
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }
      if (! dao.updateSqlRelationX(relation)) { return dao.errInvalidRelation(); }
      if (! pDatabase) { dao.transaction(); }
      dao.quiet();

      qx::QxSqlRelationParams params(0, 0, NULL, (& dao.builder()), (& dao.query()), (& t));
      params.setDatabase((& dao.database()));

      qx::QxSqlRelationLinked * pRelationLinked = dao.getSqlRelationLinked();
      if (pRelationLinked) { dao.updateError(pRelationLinked->hierarchyOnBeforeSave(params)); }
      if (! dao.isValid()) { return dao.error(); }

      dao.updateError(qx::dao::insert(t, (& dao.database())));
      if (! dao.isValid()) { return dao.error(); }

      if (pRelationLinked) { dao.updateError(pRelationLinked->hierarchyOnAfterSave(params)); }
      if (! dao.isValid()) { return dao.error(); }

      return dao.error();
   }

};

template <class T>
struct QxDao_Insert_WithRelation_Container
{

   static QSqlError insert(const QStringList & relation, T & t, QSqlDatabase * pDatabase)
   {
      typedef typename qx::trait::generic_container<T>::type_value_qx type_item;

      if (qx::trait::generic_container<T>::size(t) <= 0) { return QSqlError(); }
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "insert with relation", new qx::QxSqlQueryBuilder_Insert<type_item>());
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }
      if (! dao.updateSqlRelationX(relation)) { return dao.errInvalidRelation(); }
      if (! pDatabase) { dao.transaction(); }
      dao.quiet();

      for (typename T::iterator it = t.begin(); it != t.end(); ++it)
      { if (! insertItem((* it), dao)) { return dao.error(); } }

      return dao.error();
   }

private:

   template <typename U>
   static inline bool insertItem(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   {
      bool bInsertOk = insertItem_Helper<U, std::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::insert(item, dao);
      if (bInsertOk) { qx::dao::detail::QxDao_Keep_Original<U>::backup(item); }
      return bInsertOk;
   }

   template <typename U, bool bIsPointer /* = true */>
   struct insertItem_Helper
   {
      static inline bool insert(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return (item ? qx::dao::detail::QxDao_Insert_WithRelation_Container<T>::insertItem((* item), dao) : true); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<std::pair<U1, U2>, false>
   {
      static inline bool insert(std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_WithRelation_Container<T>::insertItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<const std::pair<U1, U2>, false>
   {
      static inline bool insert(const std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_WithRelation_Container<T>::insertItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<QPair<U1, U2>, false>
   {
      static inline bool insert(QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_WithRelation_Container<T>::insertItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<const QPair<U1, U2>, false>
   {
      static inline bool insert(const QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_WithRelation_Container<T>::insertItem(item.second, dao); }
   };

   template <typename U>
   struct insertItem_Helper<U, false>
   {
      static bool insert(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      {
         qx::QxSqlRelationParams params(0, 0, NULL, (& dao.builder()), (& dao.query()), (& item));
         params.setDatabase((& dao.database()));

         qx::QxSqlRelationLinked * pRelationLinked = dao.getSqlRelationLinked();
         if (pRelationLinked) { dao.updateError(pRelationLinked->hierarchyOnBeforeSave(params)); }
         if (! dao.isValid()) { return false; }

         dao.updateError(qx::dao::insert(item, (& dao.database())));
         if (! dao.isValid()) { return false; }

         if (pRelationLinked) { dao.updateError(pRelationLinked->hierarchyOnAfterSave(params)); }
         if (! dao.isValid()) { return false; }

         return dao.isValid();
      }
   };

};

template <class T>
struct QxDao_Insert_WithRelation_Ptr
{

   static inline QSqlError insert(const QStringList & relation, T & t, QSqlDatabase * pDatabase)
   { return (t ? qx::dao::insert_with_relation(relation, (* t), pDatabase) : QSqlError()); }

};

template <class T>
struct QxDao_Insert_WithRelation
{

   static inline QSqlError insert(const QString & relation, T & t, QSqlDatabase * pDatabase)
   {
      QStringList lst;
      if (! relation.isEmpty()) { lst = relation.split("|"); }
      return QxDao_Insert_WithRelation<T>::insert(lst, t, pDatabase);
   }

   static inline QSqlError insert(const QStringList & relation, T & t, QSqlDatabase * pDatabase)
   {
      typedef typename std::conditional< std::is_pointer<T>::value, qx::dao::detail::QxDao_Insert_WithRelation_Ptr<T>, qx::dao::detail::QxDao_Insert_WithRelation_Generic<T> >::type type_dao_1;
      typedef typename std::conditional< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_Insert_WithRelation_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename std::conditional< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_Insert_WithRelation_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::insert(relation, t, pDatabase);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
