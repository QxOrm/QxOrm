/****************************************************************************
**
** https://www.qxorm.com/
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
struct QxDao_Insert_Generic
{

   static QSqlError insert(T & t, QSqlDatabase * pDatabase, bool bUseExecBatch)
   {
      Q_UNUSED(bUseExecBatch); // Useful only with containers
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "insert", new qx::QxSqlQueryBuilder_Insert<T>());
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }
      if (! dao.validateInstance(t)) { return dao.error(); }

#ifdef _QX_ENABLE_MONGODB
      if (dao.isMongoDB())
      {
         qx::dao::on_before_insert<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
         QString insertedId; qx::dao::mongodb::QxMongoDB_Helper::insertOne((& dao), dao.getDataMemberX()->getClass(), qx::serialization::json::to_string(t, 1, "mongodb"), insertedId); if (! dao.isValid()) { return dao.error(); }
         if (! insertedId.isEmpty() && dao.getDataId()) { dao.getDataId()->fromVariant((& t), insertedId, -1, qx::cvt::context::e_database); }
         qx::dao::on_after_insert<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
         return dao.error();
      }
#endif // _QX_ENABLE_MONGODB

      IxSqlGenerator * pSqlGenerator = dao.getSqlGenerator();
      QString sql = dao.builder().buildSql().getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! pDatabase) { dao.transaction(); }
      if (pSqlGenerator) { pSqlGenerator->checkSqlInsert((& dao), sql); }
      if (! dao.prepare(sql)) { return dao.errFailed(true); }

      if (pSqlGenerator) { pSqlGenerator->onBeforeInsert((& dao), (& t)); }
      qx::dao::on_before_insert<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }

      {
         qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_read_instance);
         qx::dao::detail::QxSqlQueryHelper_Insert<T>::resolveInput(t, dao.query(), dao.builder());
      }

      if (! dao.exec(true)) { return dao.errFailed(); }
      dao.updateLastInsertId(t);
      if (pSqlGenerator) { pSqlGenerator->onAfterInsert((& dao), (& t)); }
      qx::dao::on_after_insert<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }

      return dao.error();
   }

};

template <class T>
struct QxDao_Insert_Container
{

   static QSqlError insert(T & t, QSqlDatabase * pDatabase, bool bUseExecBatch)
   {
      typedef typename qx::trait::generic_container<T>::type_value_qx type_item;

      if (qx::trait::generic_container<T>::size(t) <= 0) { return QSqlError(); }
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "insert", new qx::QxSqlQueryBuilder_Insert<type_item>());
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }
      if (! dao.validateInstance(t)) { return dao.error(); }
      dao.setUseExecBatch(bUseExecBatch);

#ifdef _QX_ENABLE_MONGODB
      if (dao.isMongoDB())
      {
         for (typename T::iterator it = t.begin(); it != t.end(); ++it) { if (! insertItem((* it), dao)) { return dao.error(); } }
         QStringList & itemsAsJson = dao.itemsAsJson(); QStringList insertedId;
         qx::dao::mongodb::QxMongoDB_Helper::insertMany((& dao), dao.getDataMemberX()->getClass(), itemsAsJson, insertedId); if (! dao.isValid()) { return dao.error(); }
         dao.qxQuery().queryAt(2, "<done>"); dao.itemsAsJson().clear(); dao.itemsAsJson().append(insertedId);
         for (typename T::iterator it = t.begin(); it != t.end(); ++it) { if (! insertItem((* it), dao)) { return dao.error(); } }
         return dao.error();
      }
#endif // _QX_ENABLE_MONGODB

      IxSqlGenerator * pSqlGenerator = dao.getSqlGenerator();
      QString sql = dao.builder().buildSql().getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! pDatabase) { dao.transaction(); }
      if (pSqlGenerator) { pSqlGenerator->checkSqlInsert((& dao), sql); }
      if (! dao.prepare(sql)) { return dao.errFailed(true); }

      for (typename T::iterator it = t.begin(); it != t.end(); ++it)
      { if (! insertItem((* it), dao)) { return dao.error(); } }

      if (bUseExecBatch && (! dao.exec())) { return dao.errFailed(); }
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
      { return (item ? qx::dao::detail::QxDao_Insert_Container<T>::insertItem((* item), dao) : true); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<std::pair<U1, U2>, false>
   {
      static inline bool insert(std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_Container<T>::insertItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<const std::pair<U1, U2>, false>
   {
      static inline bool insert(const std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_Container<T>::insertItem(item.second, dao); }
   };

#if (QT_VERSION < 0x060000)
   template <typename U1, typename U2>
   struct insertItem_Helper<QPair<U1, U2>, false>
   {
      static inline bool insert(QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_Container<T>::insertItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<const QPair<U1, U2>, false>
   {
      static inline bool insert(const QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_Container<T>::insertItem(item.second, dao); }
   };
#endif // (QT_VERSION < 0x060000)

   template <typename U>
   struct insertItem_Helper<U, false>
   {
      static bool insert(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      {
#ifdef _QX_ENABLE_MONGODB
         if (dao.isMongoDB())
         {
            if (dao.qxQuery().queryAt(2) == "<done>")
            {
               if (! dao.itemsAsJson().isEmpty()) { QString oid = dao.itemsAsJson().takeFirst(); if (! oid.isEmpty() && dao.getDataId()) { dao.getDataId()->fromVariant((& item), oid, -1, qx::cvt::context::e_database); } }
               qx::dao::on_after_insert<U>((& item), (& dao)); return dao.isValid();
            }
            qx::dao::on_before_insert<U>((& item), (& dao)); if (! dao.isValid()) { return false; }
            dao.itemsAsJson().append(qx::serialization::json::to_string(item, 1, "mongodb"));
            return dao.isValid();
         }
#endif // _QX_ENABLE_MONGODB

         IxSqlGenerator * pSqlGenerator = dao.getSqlGenerator();
         if (pSqlGenerator) { pSqlGenerator->onBeforeInsert((& dao), (& item)); }
         qx::dao::on_before_insert<U>((& item), (& dao)); if (! dao.isValid()) { return false; }

         {
            qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_read_instance);
            qx::dao::detail::QxSqlQueryHelper_Insert<U>::resolveInput(item, dao.query(), dao.builder());
         }

         if (dao.getUseExecBatch()) { return dao.isValid(); }
         if (! dao.exec(true)) { dao.errFailed(); return false; }
         dao.updateLastInsertId(item);
         if (pSqlGenerator) { pSqlGenerator->onAfterInsert((& dao), (& item)); }
         qx::dao::on_after_insert<U>((& item), (& dao)); if (! dao.isValid()) { return false; }

         return dao.isValid();
      }
   };

};

template <class T>
struct QxDao_Insert_Ptr
{

   static inline QSqlError insert(T & t, QSqlDatabase * pDatabase, bool bUseExecBatch)
   { return (t ? qx::dao::insert((* t), pDatabase, bUseExecBatch) : QSqlError()); }

};

template <class T>
struct QxDao_Insert
{

   static inline QSqlError insert(T & t, QSqlDatabase * pDatabase, bool bUseExecBatch = false)
   {
      typedef typename std::conditional< std::is_pointer<T>::value, qx::dao::detail::QxDao_Insert_Ptr<T>, qx::dao::detail::QxDao_Insert_Generic<T> >::type type_dao_1;
      typedef typename std::conditional< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_Insert_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename std::conditional< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_Insert_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::insert(t, pDatabase, bUseExecBatch);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
