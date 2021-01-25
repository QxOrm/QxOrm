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
struct QxDao_Update_Generic
{

   static QSqlError update(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "update", new qx::QxSqlQueryBuilder_Update<T>(), (& query));
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }
      if (! dao.isValidPrimaryKey(t)) { return dao.errInvalidId(); }
      if (! dao.validateInstance(t)) { return dao.error(); }

#ifdef _QX_ENABLE_MONGODB
      if (dao.isMongoDB())
      {
         qx::dao::on_before_update<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
         QString ctx = QString("mongodb") + ((columns.count() > 0) ? (QString(":columns{,") + columns.join(",") + QString(",}")) : QString());
         qx::dao::mongodb::QxMongoDB_Helper::updateOne((& dao), dao.getDataMemberX()->getClass(), qx::serialization::json::to_string(t, 1, ctx), (& query)); if (! dao.isValid()) { return dao.error(); }
         qx::dao::on_after_update<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }
         return dao.error();
      }
#endif // _QX_ENABLE_MONGODB

      QString sql = dao.builder().buildSql(columns).getSqlQuery();
      if (! dao.getDataId() || sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(false); sql = dao.builder().getSqlQuery(); }
      if (! pDatabase) { dao.transaction(); }
      if (! dao.prepare(sql)) { return dao.errFailed(true); }

      IxSqlGenerator * pSqlGenerator = dao.getSqlGenerator();
      if (pSqlGenerator) { pSqlGenerator->onBeforeUpdate((& dao), (& t)); }
      qx::dao::on_before_update<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }

      {
         qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_read_instance);
         qx::dao::detail::QxSqlQueryHelper_Update<T>::resolveInput(t, dao.query(), dao.builder(), columns);
      }

      if (! query.isEmpty()) { query.resolve(dao.query()); }
      if (! dao.exec(true)) { return dao.errFailed(); }
      if (pSqlGenerator) { pSqlGenerator->onAfterUpdate((& dao), (& t)); }
      qx::dao::on_after_update<T>((& t), (& dao)); if (! dao.isValid()) { return dao.error(); }

      return dao.error();
   }

};

template <class T>
struct QxDao_Update_Container
{

   static QSqlError update(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      typedef typename qx::trait::generic_container<T>::type_value_qx type_item;

      if (qx::trait::generic_container<T>::size(t) <= 0) { return QSqlError(); }
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "update", new qx::QxSqlQueryBuilder_Update<type_item>(), (& query));
      if (! dao.isValid()) { return dao.error(); }
      if (dao.isReadOnly()) { return dao.errReadOnly(); }
      if (! dao.validateInstance(t)) { return dao.error(); }

#ifdef _QX_ENABLE_MONGODB
      if (dao.isMongoDB())
      {
         dao.setSqlColumns(columns);
         for (typename T::iterator it = t.begin(); it != t.end(); ++it) { if (! updateItem((* it), dao)) { return dao.error(); } }
         QStringList & itemsAsJson = dao.itemsAsJson();
         qx::dao::mongodb::QxMongoDB_Helper::updateMany((& dao), dao.getDataMemberX()->getClass(), itemsAsJson, (& query)); if (! dao.isValid()) { return dao.error(); }
         dao.qxQuery().queryAt(2, "<done>"); dao.itemsAsJson().clear();
         for (typename T::iterator it = t.begin(); it != t.end(); ++it) { if (! updateItem((* it), dao)) { return dao.error(); } }
         return dao.error();
      }
#endif // _QX_ENABLE_MONGODB

      QString sql = dao.builder().buildSql(columns).getSqlQuery();
      if (! dao.getDataId() || sql.isEmpty()) { return dao.errEmpty(); }
      if (! query.isEmpty()) { dao.addQuery(false); sql = dao.builder().getSqlQuery(); }
      if (! pDatabase) { dao.transaction(); }
      if (! dao.prepare(sql)) { return dao.errFailed(true); }
      dao.setSqlColumns(columns);

      for (typename T::iterator it = t.begin(); it != t.end(); ++it)
      { if (! updateItem((* it), dao)) { return dao.error(); } }

      return dao.error();
   }

private:

   template <typename U>
   static inline bool updateItem(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   {
      bool bUpdateOk = updateItem_Helper<U, std::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::update(item, dao);
      if (bUpdateOk) { qx::dao::detail::QxDao_Keep_Original<U>::backup(item); }
      return bUpdateOk;
   }

   template <typename U, bool bIsPointer /* = true */>
   struct updateItem_Helper
   {
      static inline bool update(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return (item ? qx::dao::detail::QxDao_Update_Container<T>::updateItem((* item), dao) : true); }
   };

   template <typename U1, typename U2>
   struct updateItem_Helper<std::pair<U1, U2>, false>
   {
      static inline bool update(std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Update_Container<T>::updateItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct updateItem_Helper<const std::pair<U1, U2>, false>
   {
      static inline bool update(const std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Update_Container<T>::updateItem(item.second, dao); }
   };

#if (QT_VERSION < 0x060000)
   template <typename U1, typename U2>
   struct updateItem_Helper<QPair<U1, U2>, false>
   {
      static inline bool update(QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Update_Container<T>::updateItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct updateItem_Helper<const QPair<U1, U2>, false>
   {
      static inline bool update(const QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Update_Container<T>::updateItem(item.second, dao); }
   };
#endif // (QT_VERSION < 0x060000)

   template <typename U>
   struct updateItem_Helper<U, false>
   {
      static bool update(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      {
         QStringList columns = dao.getSqlColumns();

#ifdef _QX_ENABLE_MONGODB
         if (dao.isMongoDB())
         {
            if (dao.qxQuery().queryAt(2) == "<done>") { qx::dao::on_after_update<U>((& item), (& dao)); return dao.isValid(); }
            QString ctx = QString("mongodb") + ((columns.count() > 0) ? (QString(":columns{,") + columns.join(",") + QString(",}")) : QString());
            qx::dao::on_before_update<U>((& item), (& dao)); if (! dao.isValid()) { return false; }
            dao.itemsAsJson().append(qx::serialization::json::to_string(item, 1, ctx));
            return dao.isValid();
         }
#endif // _QX_ENABLE_MONGODB

         if (! dao.isValidPrimaryKey(item)) { dao.errInvalidId(); return false; }
         IxSqlGenerator * pSqlGenerator = dao.getSqlGenerator();
         if (pSqlGenerator) { pSqlGenerator->onBeforeUpdate((& dao), (& item)); }
         qx::dao::on_before_update<U>((& item), (& dao)); if (! dao.isValid()) { return false; }

         {
            qx::dao::detail::IxDao_Timer timer((& dao), qx::dao::detail::IxDao_Helper::timer_cpp_read_instance);
            qx::dao::detail::QxSqlQueryHelper_Update<U>::resolveInput(item, dao.query(), dao.builder(), columns);
         }

         if (! dao.qxQuery().isEmpty()) { dao.qxQuery().resolve(dao.query()); }
         if (! dao.exec(true)) { dao.errFailed(); return false; }
         if (pSqlGenerator) { pSqlGenerator->onAfterUpdate((& dao), (& item)); }
         qx::dao::on_after_update<U>((& item), (& dao)); if (! dao.isValid()) { return false; }

         return dao.isValid();
      }
   };

};

template <class T>
struct QxDao_Update_Ptr
{

   static inline QSqlError update(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   { return (t ? qx::dao::update_by_query(query, (* t), pDatabase, columns) : QSqlError()); }

};

template <class T>
struct QxDao_Update
{

   static inline QSqlError update(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
   {
      typedef typename std::conditional< std::is_pointer<T>::value, qx::dao::detail::QxDao_Update_Ptr<T>, qx::dao::detail::QxDao_Update_Generic<T> >::type type_dao_1;
      typedef typename std::conditional< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_Update_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename std::conditional< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_Update_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::update(query, t, pDatabase, columns);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
