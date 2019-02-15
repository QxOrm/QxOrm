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

#ifndef _IX_PERSISTABLE_LIST_H_
#define _IX_PERSISTABLE_LIST_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxPersistableList.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Common interface (abstract class) for list persistent classes based on qx::IxPersistable
 */

#include <QxDao/IxPersistable.h>
#include <QxDao/IxPersistableCollection.h>

#include <QxTraits/get_primary_key.h>
#include <QxTraits/is_qx_registered.h>

#ifndef _QX_NO_JSON
#include <QxSerialize/QxSerializeQJson.h>
#endif // _QX_NO_JSON

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxPersistableList<T> : concrete class for list persistent classes based on qx::IxPersistableCollection (as an array instead of key/value hash-map)
 */
template <typename T>
class QxPersistableList : public qx::IxPersistableCollection
{

   enum { qx_is_valid = qx::trait::is_qx_registered<T>::value };

protected:

   QList<std::shared_ptr<T> > m_list; //!< List of persistable instances

public:

   QxPersistableList() : qx::IxPersistableCollection() { static_assert(qx_is_valid, "qx_is_valid"); }
   virtual ~QxPersistableList() { ; }

   virtual long __count() const                          { return static_cast<long>(m_list.size()); }
   virtual void __clear()                                { m_list.clear(); }
   virtual bool __remove(long idx)                       { if ((idx < 0) || (idx >= static_cast<long>(m_list.size()))) { return false; } m_list.removeAt(idx); return true; }
   virtual qx::IxPersistable_ptr __at(long idx) const    { if ((idx < 0) || (idx >= static_cast<long>(m_list.size()))) { return qx::IxPersistable_ptr(); } return std::static_pointer_cast<qx::IxPersistable>(m_list.at(idx)); }

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
      Q_UNUSED(id); QSqlError err;
      if (relation.count() == 0) { err = qx::dao::fetch_by_id(m_list, pDatabase, columns); }
      else { err = qx::dao::fetch_by_id_with_relation(relation, m_list, pDatabase); }
      return err;
   }

   virtual QSqlError qxFetchAll(qx::IxPersistableCollection * list = NULL, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      Q_UNUSED(list); QSqlError err;
      if (relation.count() == 0) { err = qx::dao::fetch_all(m_list, pDatabase, columns); }
      else { err = qx::dao::fetch_all_with_relation(relation, m_list, pDatabase); }
      return err;
   }

   virtual QSqlError qxFetchByQuery(const qx::QxSqlQuery & query, qx::IxPersistableCollection * list = NULL, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      Q_UNUSED(list); QSqlError err;
      if (relation.count() == 0) { err = qx::dao::fetch_by_query(query, m_list, pDatabase, columns); }
      else { err = qx::dao::fetch_by_query_with_relation(relation, query, m_list, pDatabase); }
      return err;
   }

   virtual QSqlError qxInsert(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::insert(m_list, pDatabase); }
      else { err = qx::dao::insert_with_relation(relation, m_list, pDatabase); }
      return err;
   }

   virtual QSqlError qxUpdate(const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::update_by_query(query, m_list, pDatabase, columns); }
      else { err = qx::dao::update_by_query_with_relation(relation, query, m_list, pDatabase); }
      return err;
   }

   virtual QSqlError qxSave(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL, qx::dao::save_mode::e_save_mode eSaveRecursiveMode = qx::dao::save_mode::e_none)
   {
      QSqlError err;
      if (eSaveRecursiveMode != qx::dao::save_mode::e_none) { err = qx::dao::save_with_relation_recursive(m_list, eSaveRecursiveMode, pDatabase); }
      else if (relation.count() == 0) { err = qx::dao::save(m_list, pDatabase); }
      else { err = qx::dao::save_with_relation(relation, m_list, pDatabase); }
      return err;
   }

   virtual QSqlError qxDeleteById(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL)
   { Q_UNUSED(id); return qx::dao::delete_by_id(m_list, pDatabase); }

   virtual QSqlError qxDeleteAll(QSqlDatabase * pDatabase = NULL)
   { return qx::dao::delete_all<T>(pDatabase); }

   virtual QSqlError qxDeleteByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   { return qx::dao::delete_by_query<T>(query, pDatabase); }

   virtual QSqlError qxDestroyById(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL)
   { Q_UNUSED(id); return qx::dao::destroy_by_id(m_list, pDatabase); }

   virtual QSqlError qxDestroyAll(QSqlDatabase * pDatabase = NULL)
   { return qx::dao::destroy_all<T>(pDatabase); }

   virtual QSqlError qxDestroyByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   { return qx::dao::destroy_by_query<T>(query, pDatabase); }

   virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   { return qx::dao::execute_query(query, m_list, pDatabase); }

   virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, qx::IxPersistableCollection * list = NULL, QSqlDatabase * pDatabase = NULL)
   { Q_UNUSED(list); return qxExecuteQuery(query, pDatabase); }

   virtual qx_bool qxExist(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL)
   { Q_UNUSED(id); return qx::dao::exist(m_list, pDatabase); }

   virtual qx::QxInvalidValueX qxValidate(const QStringList & groups = QStringList())
   { return qx::validate(m_list, groups); }

   virtual std::shared_ptr<qx::IxPersistableCollection> qxNewPersistableCollection(bool bAsList = false) const
   { Q_UNUSED(bAsList); std::shared_ptr<qx::IxPersistableCollection> coll = std::make_shared<qx::QxPersistableList<T> >(); return coll; }

   virtual qx::IxClass * qxClass() const
   { return qx::QxClass<T>::getSingleton(); }

#ifndef _QX_NO_JSON

   virtual QString toJson(const QString & format = QString()) const
   { return qx::serialization::json::to_string(m_list, 1, format); }

   virtual QJsonValue toJson_(const QString & format = QString()) const
   { return qx::cvt::to_json(m_list, format); }

   virtual qx_bool fromJson(const QString & json, const QString & format = QString())
   { return qx::serialization::json::from_string(m_list, json, 1, format); }

   virtual qx_bool fromJson_(const QJsonValue & json, const QString & format = QString())
   { return qx::cvt::from_json(json, m_list, format); }

#endif // _QX_NO_JSON

};

} // namespace qx

QX_REGISTER_CLASS_NAME_TEMPLATE_1(qx::QxPersistableList)

#endif // _IX_PERSISTABLE_LIST_H_
