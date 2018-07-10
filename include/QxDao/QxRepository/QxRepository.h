/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_REPOSITORY_H_
#define _QX_REPOSITORY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxRepository.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Repository to provide a common interface to communicate with database
 */

#include <boost/type_traits/is_base_of.hpp>

#include <QxDao/QxRepository/IxRepository.h>
#include <QxDao/QxRepository/QxRepositoryX.h>

#include <QxDao/QxDao.h>
#include <QxDao/QxSession.h>
#include <QxDao/QxSqlError.h>

#include <QxRegister/QxClass.h>

#include <QxCollection/QxCollection.h>

#include <QxTraits/get_primary_key.h>

namespace qx {

template <class T>
inline void register_repository(const QString & sKey);

/*!
 * \ingroup QxDao
 * \brief qx::QxRepository<T> : repository to provide a common interface to communicate with database
 */
template <class T>
class QxRepository : public IxRepository
{

   template <class U>
   friend inline void register_repository(const QString & sKey);

private:

   QxRepository(const QString & sKey) : IxRepository(true, sKey) { ; }

public:

   QxRepository() : IxRepository(false, QString("")) { ; }
   QxRepository(const QSqlDatabase & database) : IxRepository(false, QString(""), database) { ; }
   QxRepository(QxSession * pSession) : IxRepository(false, QString(""), pSession) { ; }
   virtual ~QxRepository() { ; }

   long count(const qx::QxSqlQuery & query = qx::QxSqlQuery())
   { return qx::dao::count<T>(query, this->database()); }

   T * fetchById(const QVariant & id, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      IxDataMemberX * pDataMemberX = QxClass<T>::getSingleton()->getDataMemberX();
      IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL);
      if (! pDataMemberId) { qAssert(false); return NULL; }
      T * t = new T(); QSqlError err;
      pDataMemberId->fromVariant(t, id);
      if (relation.count() == 0) { err = qx::dao::fetch_by_id((* t), this->database(), columns); }
      else { err = qx::dao::fetch_by_id_with_relation(relation, (* t), this->database()); }
      if (err.isValid() && m_pSession) { delete t; t = NULL; (* m_pSession) += err; }
      else if (err.isValid()) { delete t; t = NULL; }
      return t;
   }

   template <class U>
   QSqlError fetchById(U & u, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::fetch_by_id(u, this->database(), columns); }
      else { err = qx::dao::fetch_by_id_with_relation(relation, u, this->database()); }
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   template <class U>
   QSqlError fetchAll(U & u, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::fetch_all(u, this->database(), columns); }
      else { err = qx::dao::fetch_all_with_relation(relation, u, this->database()); }
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   template <class U>
   QSqlError fetchByQuery(const qx::QxSqlQuery & query, U & u, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::fetch_by_query(query, u, this->database(), columns); }
      else { err = qx::dao::fetch_by_query_with_relation(relation, query, u, this->database()); }
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   template <class U>
   QSqlError insert(U & u, const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::insert(u, this->database()); }
      else { err = qx::dao::insert_with_relation(relation, u, this->database()); }
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   template <class U>
   QSqlError update(U & u, const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::update_by_query(query, u, this->database(), columns); }
      else { err = qx::dao::update_by_query_with_relation(relation, query, u, this->database()); }
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   template <class U>
   QSqlError save(U & u, const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::save(u, this->database()); }
      else { err = qx::dao::save_with_relation(relation, u, this->database()); }
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   QSqlError deleteById(const QVariant & id)
   {
      IxDataMemberX * pDataMemberX = QxClass<T>::getSingleton()->getDataMemberX();
      IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL);
      if (! pDataMemberId) { qAssert(false); return QSqlError(); }
      boost::shared_ptr<T> t; t.reset(new T());
      pDataMemberId->fromVariant(t.get(), id);
      QSqlError err = qx::dao::delete_by_id((* t), this->database());
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   template <class U>
   QSqlError deleteById(U & u)
   {
      QSqlError err = qx::dao::delete_by_id(u, this->database());
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   QSqlError deleteAll()
   {
      QSqlError err = qx::dao::delete_all<T>(this->database());
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   QSqlError deleteByQuery(const qx::QxSqlQuery & query)
   {
      QSqlError err = qx::dao::delete_by_query<T>(query, this->database());
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   QSqlError destroyById(const QVariant & id)
   {
      IxDataMemberX * pDataMemberX = QxClass<T>::getSingleton()->getDataMemberX();
      IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL);
      if (! pDataMemberId) { qAssert(false); return QSqlError(); }
      boost::shared_ptr<T> t; t.reset(new T());
      pDataMemberId->fromVariant(t.get(), id);
      QSqlError err = qx::dao::destroy_by_id((* t), this->database());
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   template <class U>
   QSqlError destroyById(U & u)
   {
      QSqlError err = qx::dao::destroy_by_id(u, this->database());
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   QSqlError destroyAll()
   {
      QSqlError err = qx::dao::destroy_all<T>(this->database());
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   QSqlError destroyByQuery(const qx::QxSqlQuery & query)
   {
      QSqlError err = qx::dao::destroy_by_query<T>(query, this->database());
      if (err.isValid() && m_pSession) { (* m_pSession) += err; }
      return err;
   }

   template <class U>
   qx_bool exist(U & u)
   { return qx::dao::exist(u, this->database()); }

private:

   typedef typename qx::trait::get_primary_key<T>::type type_primary_key;
   typedef QSharedPointer<T> type_object_ptr;
   typedef qx::QxCollection<type_primary_key, type_object_ptr> type_collection;

   template <bool bIsQObject /* = false */, int dummy>
   struct qxVerifyPointer
   { static inline T * get(QObject * p) { Q_UNUSED(p); throw qx::dao::sql_error(QSqlError("[QxOrm] qx::QxRepository<T> : 'invalid pointer, need to inherit from QObject class to use qx::IxRepository interface'")); return NULL; } };

   template <int dummy>
   struct qxVerifyPointer<true, dummy>
   { static inline T * get(QObject * p) { T * t = dynamic_cast<T *>(p); if (! t) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::QxRepository<T> : 'invalid pointer, dynamic_cast failed'")); }; return t; } };

   type_collection * qxVerifyPointer_Collection(qx::IxCollection * p)
   { type_collection * x = dynamic_cast<type_collection *>(p); if (! x) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::QxRepository<T> : 'invalid collection pointer, dynamic_cast failed'")); }; return x; }

public:

   virtual long _count(const qx::QxSqlQuery & query = qx::QxSqlQuery())
   { return this->count(query); }

   virtual void * _fetchById(const QVariant & id, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   { return static_cast<void *>(this->fetchById(id, columns, relation)); }

   virtual QSqlError _fetchById(QObject * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   { T * t = qxVerifyPointer<boost::is_base_of<QObject, T>::value, 0>::get(p); return this->fetchById((* t), columns, relation); }

   virtual QSqlError _fetchById(qx::IxCollection * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   { type_collection * x = qxVerifyPointer_Collection(p); return this->fetchById((* x), columns, relation); }

   virtual QSqlError _fetchAll(QObject * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   { T * t = qxVerifyPointer<boost::is_base_of<QObject, T>::value, 0>::get(p); return this->fetchAll((* t), columns, relation); }

   virtual QSqlError _fetchAll(qx::IxCollection * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   { type_collection * x = qxVerifyPointer_Collection(p); return this->fetchAll((* x), columns, relation); }

   virtual QSqlError _fetchByQuery(const qx::QxSqlQuery & query, QObject * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   { T * t = qxVerifyPointer<boost::is_base_of<QObject, T>::value, 0>::get(p); return this->fetchByQuery(query, (* t), columns, relation); }

   virtual QSqlError _fetchByQuery(const qx::QxSqlQuery & query, qx::IxCollection * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   { type_collection * x = qxVerifyPointer_Collection(p); return this->fetchByQuery(query, (* x), columns, relation); }

   virtual QSqlError _insert(QObject * p, const QStringList & relation = QStringList())
   { T * t = qxVerifyPointer<boost::is_base_of<QObject, T>::value, 0>::get(p); return this->insert((* t), relation); }

   virtual QSqlError _insert(qx::IxCollection * p, const QStringList & relation = QStringList())
   { type_collection * x = qxVerifyPointer_Collection(p); return this->insert((* x), relation); }

   virtual QSqlError _update(QObject * p, const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   { T * t = qxVerifyPointer<boost::is_base_of<QObject, T>::value, 0>::get(p); return this->update((* t), query, columns, relation); }

   virtual QSqlError _update(qx::IxCollection * p, const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   { type_collection * x = qxVerifyPointer_Collection(p); return this->update((* x), query, columns, relation); }

   virtual QSqlError _save(QObject * p, const QStringList & relation = QStringList())
   { T * t = qxVerifyPointer<boost::is_base_of<QObject, T>::value, 0>::get(p); return this->save((* t), relation); }

   virtual QSqlError _save(qx::IxCollection * p, const QStringList & relation = QStringList())
   { type_collection * x = qxVerifyPointer_Collection(p); return this->save((* x), relation); }

   virtual QSqlError _deleteById(const QVariant & id)
   { return this->deleteById(id); }

   virtual QSqlError _deleteById(QObject * p)
   { T * t = qxVerifyPointer<boost::is_base_of<QObject, T>::value, 0>::get(p); return this->deleteById(* t); }

   virtual QSqlError _deleteById(qx::IxCollection * p)
   { type_collection * x = qxVerifyPointer_Collection(p); return this->deleteById(* x); }

   virtual QSqlError _deleteAll()
   { return this->deleteAll(); }

   virtual QSqlError _deleteByQuery(const qx::QxSqlQuery & query)
   { return this->deleteByQuery(query); }

   virtual QSqlError _destroyById(const QVariant & id)
   { return this->destroyById(id); }

   virtual QSqlError _destroyById(QObject * p)
   { T * t = qxVerifyPointer<boost::is_base_of<QObject, T>::value, 0>::get(p); return this->destroyById(* t); }

   virtual QSqlError _destroyById(qx::IxCollection * p)
   { type_collection * x = qxVerifyPointer_Collection(p); return this->destroyById(* x); }

   virtual QSqlError _destroyAll()
   { return this->destroyAll(); }

   virtual QSqlError _destroyByQuery(const qx::QxSqlQuery & query)
   { return this->destroyByQuery(query); }

   virtual qx_bool _exist(QObject * p)
   { T * t = qxVerifyPointer<boost::is_base_of<QObject, T>::value, 0>::get(p); return this->exist(* t); }

   virtual qx_bool _exist(qx::IxCollection * p)
   { type_collection * x = qxVerifyPointer_Collection(p); return this->exist(* x); }

public:

   static T * getById(const QVariant & id, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      IxDataMemberX * pDataMemberX = QxClass<T>::getSingleton()->getDataMemberX();
      IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL);
      if (! pDataMemberId) { qAssert(false); return NULL; }
      T * t = new T(); QSqlError err;
      pDataMemberId->fromVariant(t, id);
      if (relation.count() == 0) { err = qx::dao::fetch_by_id((* t), NULL, columns); }
      else { err = qx::dao::fetch_by_id_with_relation(relation, (* t), NULL); }
      if (err.isValid()) { delete t; t = NULL; }
      return t;
   }

};

template <class T>
inline void register_repository(const QString & sKey)
{
   // 'pNewRepository' instance will be destroyed by 'qx::QxRepositoryX::unregisterRepository()' method
   qx::QxRepository<T> * pNewRepository = new qx::QxRepository<T>(sKey);
   Q_UNUSED(pNewRepository);
}

} // namespace qx

#endif // _QX_REPOSITORY_H_
