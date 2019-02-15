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

#ifndef _IX_PERSISTABLE_COLLECTION_H_
#define _IX_PERSISTABLE_COLLECTION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxPersistableCollection.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Common interface (abstract class) for collection persistent classes based on qx::IxPersistable and qx::IxCollection
 */

#include <QxDao/IxPersistable.h>

#include <QxCollection/QxCollection.h>

#include <QxTraits/get_primary_key.h>
#include <QxTraits/is_qx_registered.h>

#ifndef _QX_NO_JSON
#include <QxSerialize/QxSerializeQJson.h>
#endif // _QX_NO_JSON

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::IxPersistableCollection : common interface (abstract class) for collection persistent classes based on qx::IxPersistable and qx::IxCollection
 */
class QX_DLL_EXPORT IxPersistableCollection : public qx::IxPersistable
{

public:

   IxPersistableCollection();
   virtual ~IxPersistableCollection();

   virtual long __count() const = 0;
   virtual void __clear() = 0;
   virtual bool __remove(long idx) = 0;
   virtual qx::IxPersistable_ptr __at(long idx) const = 0;

};

typedef std::shared_ptr<qx::IxPersistableCollection> IxPersistableCollection_ptr;

/*!
 * \ingroup QxDao
 * \brief qx::QxPersistableCollection<Key, Value, T> : concrete class for collection persistent classes based on qx::IxPersistableCollection and qx::QxCollection<Key, Value>
 */
template <typename Key, typename Value, typename T>
class QxPersistableCollection : public qx::IxPersistableCollection, public qx::QxCollection<Key, Value>
{

   enum { qx_is_valid = qx::trait::is_qx_registered<T>::value };

public:

   QxPersistableCollection() : qx::IxPersistableCollection(), qx::QxCollection<Key, Value>() { static_assert(qx_is_valid, "qx_is_valid"); }
   virtual ~QxPersistableCollection() { ; }

   virtual long __count() const                          { const qx::QxCollection<Key, Value> * coll = this; return coll->count(); }
   virtual void __clear()                                { qx::QxCollection<Key, Value> * coll = this; coll->clear(); }
   virtual bool __remove(long idx)                       { qx::QxCollection<Key, Value> * coll = this; return coll->removeByIndex(idx); }
   virtual qx::IxPersistable_ptr __at(long idx) const    { const qx::QxCollection<Key, Value> * coll = this; Value val = coll->getByIndex(idx); return std::static_pointer_cast<qx::IxPersistable>(val); }

   virtual long qxCount(const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL, const QStringList & relation = QStringList())
   {
      if (relation.count() == 0) { return qx::dao::count<T>(query, pDatabase); }
      else { long lCount(0); qx::dao::count_with_relation<T>(lCount, relation, query, pDatabase); return lCount; }
   }

   virtual QSqlError qxCount(long & lCount, const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL, const QStringList & relation = QStringList())
   {
      if (relation.count() == 0) { return qx::dao::count<T>(lCount, query, pDatabase); }
      else { return qx::dao::count_with_relation<T>(lCount, relation, query, pDatabase); }
   }

   virtual QSqlError qxFetchById(const QVariant & id = QVariant(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      Q_UNUSED(id); QSqlError err; qx::QxCollection<Key, Value> * coll = this;
      if (relation.count() == 0) { err = qx::dao::fetch_by_id((* coll), pDatabase, columns); }
      else { err = qx::dao::fetch_by_id_with_relation(relation, (* coll), pDatabase); }
      return err;
   }

   virtual QSqlError qxFetchAll(qx::IxPersistableCollection * list = NULL, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      Q_UNUSED(list); QSqlError err; qx::QxCollection<Key, Value> * coll = this;
      if (relation.count() == 0) { err = qx::dao::fetch_all((* coll), pDatabase, columns); }
      else { err = qx::dao::fetch_all_with_relation(relation, (* coll), pDatabase); }
      return err;
   }

   virtual QSqlError qxFetchByQuery(const qx::QxSqlQuery & query, qx::IxPersistableCollection * list = NULL, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      Q_UNUSED(list); QSqlError err; qx::QxCollection<Key, Value> * coll = this;
      if (relation.count() == 0) { err = qx::dao::fetch_by_query(query, (* coll), pDatabase, columns); }
      else { err = qx::dao::fetch_by_query_with_relation(relation, query, (* coll), pDatabase); }
      return err;
   }

   virtual QSqlError qxInsert(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      QSqlError err; qx::QxCollection<Key, Value> * coll = this;
      if (relation.count() == 0) { err = qx::dao::insert((* coll), pDatabase); }
      else { err = qx::dao::insert_with_relation(relation, (* coll), pDatabase); }
      return err;
   }

   virtual QSqlError qxUpdate(const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      QSqlError err; qx::QxCollection<Key, Value> * coll = this;
      if (relation.count() == 0) { err = qx::dao::update_by_query(query, (* coll), pDatabase, columns); }
      else { err = qx::dao::update_by_query_with_relation(relation, query, (* coll), pDatabase); }
      return err;
   }

   virtual QSqlError qxSave(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL, qx::dao::save_mode::e_save_mode eSaveRecursiveMode = qx::dao::save_mode::e_none)
   {
      QSqlError err; qx::QxCollection<Key, Value> * coll = this;
      if (eSaveRecursiveMode != qx::dao::save_mode::e_none) { err = qx::dao::save_with_relation_recursive((* coll), eSaveRecursiveMode, pDatabase); }
      else if (relation.count() == 0) { err = qx::dao::save((* coll), pDatabase); }
      else { err = qx::dao::save_with_relation(relation, (* coll), pDatabase); }
      return err;
   }

   virtual QSqlError qxDeleteById(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL)
   { Q_UNUSED(id); qx::QxCollection<Key, Value> * coll = this; return qx::dao::delete_by_id((* coll), pDatabase); }

   virtual QSqlError qxDeleteAll(QSqlDatabase * pDatabase = NULL)
   { return qx::dao::delete_all<T>(pDatabase); }

   virtual QSqlError qxDeleteByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   { return qx::dao::delete_by_query<T>(query, pDatabase); }

   virtual QSqlError qxDestroyById(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL)
   { Q_UNUSED(id); qx::QxCollection<Key, Value> * coll = this; return qx::dao::destroy_by_id((* coll), pDatabase); }

   virtual QSqlError qxDestroyAll(QSqlDatabase * pDatabase = NULL)
   { return qx::dao::destroy_all<T>(pDatabase); }

   virtual QSqlError qxDestroyByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   { return qx::dao::destroy_by_query<T>(query, pDatabase); }

   virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   { qx::QxCollection<Key, Value> * coll = this; return qx::dao::execute_query(query, (* coll), pDatabase); }

   virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, qx::IxPersistableCollection * list = NULL, QSqlDatabase * pDatabase = NULL)
   { Q_UNUSED(list); return qxExecuteQuery(query, pDatabase); }

   virtual qx_bool qxExist(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL)
   { Q_UNUSED(id); qx::QxCollection<Key, Value> * coll = this; return qx::dao::exist((* coll), pDatabase); }

   virtual qx::QxInvalidValueX qxValidate(const QStringList & groups = QStringList())
   { qx::QxCollection<Key, Value> * coll = this; return qx::validate((* coll), groups); }

   virtual std::shared_ptr<qx::IxPersistableCollection> qxNewPersistableCollection(bool bAsList = false) const
   { Q_UNUSED(bAsList); std::shared_ptr<qx::IxPersistableCollection> coll = std::make_shared<qx::QxPersistableCollection<Key, Value, T> >(); return coll; }

   virtual qx::IxClass * qxClass() const
   { return qx::QxClass<T>::getSingleton(); }

#ifndef _QX_NO_JSON

   virtual QString toJson(const QString & format = QString()) const
   { const qx::QxCollection<Key, Value> * coll = this; return qx::serialization::json::to_string((* coll), 1, format); }

   virtual QJsonValue toJson_(const QString & format = QString()) const
   { const qx::QxCollection<Key, Value> * coll = this; return qx::cvt::to_json((* coll), format); }

   virtual qx_bool fromJson(const QString & json, const QString & format = QString())
   { qx::QxCollection<Key, Value> * coll = this; return qx::serialization::json::from_string((* coll), json, 1, format); }

   virtual qx_bool fromJson_(const QJsonValue & json, const QString & format = QString())
   { qx::QxCollection<Key, Value> * coll = this; return qx::cvt::from_json(json, (* coll), format); }

#endif // _QX_NO_JSON

};

/*!
 * \ingroup QxDao
 * \brief qx::QxPersistableCollectionHelper<T>::type : return the collection type used by qx::IxPersistable interface, qx::QxPersistableCollection<type_primary_key, std::shared_ptr<my_type>>
 */
template <typename T>
class QxPersistableCollectionHelper
{

private:

   typedef typename qx::trait::get_primary_key<T>::type qx_type_primary_key;
   typedef std::shared_ptr<T> qx_type_ptr;

public:

   typedef qx::QxPersistableCollection<qx_type_primary_key, qx_type_ptr, T> type;
   typedef qx::QxCollection<qx_type_primary_key, qx_type_ptr> type_coll;

};

} // namespace qx

QX_REGISTER_CLASS_NAME(qx::IxPersistableCollection)
QX_REGISTER_CLASS_NAME_TEMPLATE_3(qx::QxPersistableCollection)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(qx::QxPersistableCollectionHelper)

#endif // _IX_PERSISTABLE_COLLECTION_H_
