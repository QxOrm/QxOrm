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

#ifndef _QX_DAO_SESSION_H_
#define _QX_DAO_SESSION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSession.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Define a session to manage automatically database transactions (using C++ RAII)
 */

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqldriver.h>

#include <QtCore/qlist.h>

#include <QxCommon/QxBool.h>

#include <QxDao/QxDao.h>
#include <QxDao/QxSqlQuery.h>
#include <QxDao/QxSqlError.h>

#include <QxRegister/QxClass.h>

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSession : define a session to manage automatically database transactions (using C++ RAII)
 *
 * A database <b>transaction</b> is a sequence of operations performed as a single logical unit of work.
 * If no errors occurred during the execution of the transaction then the system <b>commits</b> the transaction.
 * If an error occurs during the transaction, or if the user specifies a <b>rollback</b> operation, the data manipulations within the transaction are not persisted to the database.
 *
 * The <i>qx::QxSession</i> class of QxOrm library is designed to manage automatically database transactions (using <i>C++ RAII</i>) :
 * \code
{ // Start a scope where a new session is instantiated

  // Create a session : a valid database connexion by thread is automatically assigned to the session and a transaction is opened
  qx::QxSession session;

  // Execute some operations with database (using += operator of qx::QxSession class and session database connexion)
  session += qx::dao::insert(my_object, session.database());
  session += qx::dao::update(my_object, session.database());
  session += qx::dao::fetch_by_id(my_object, session.database());
  session += qx::dao::delete_by_id(my_object, session.database());

  // If the session is not valid (so an error occured) => display first error
  if (! session.isValid()) { qDebug("[QxOrm] session error : '%s'", qPrintable(session.firstError().text())); }

} // End of scope : session is destroyed (transaction => automatically commit or rollback if there is an error)
 * \endcode
 *
 * <i>Note :</i> a session can throw a <i>qx::dao::sql_error</i> exception when a SQL error occured (by default, there is no exception).
 * You can setup this feature using :
 * - <i>qx::QxSession</i> constructor (for a specific session) ;
 * - <i>qx::QxSqlDatabase::getSingleton()->setSessionThrowable(bool b)</i> parameter (for all sessions).
 *
 * <i>Other note :</i> don't forget to pass the session database connexion to each <i>qx::dao::xxx</i> functions (using <i>session.database()</i> method).
 * Moreover, you can manage your own database connexion (from a connexion pool for example) using constructor of <i>qx::QxSession</i> class.
 *
 * <i>qx::QxSession</i> class provides also persistent methods (CRUD) to make easier to write C++ code.
 * Here is the same example using methods of <i>qx::QxSession</i> class instead of functions into namespace <i>qx::dao</i> :
 * \code
{ // Start a scope where a new session is instantiated

  // Create a session : a valid database connexion by thread is automatically assigned to the session and a transaction is opened
  qx::QxSession session;

  // Execute some operations with database
  session.insert(my_object);
  session.update(my_object);
  session.fetchById(my_object);
  session.deleteById(my_object);

  // If the session is not valid (so an error occured) => display first error
  if (! session.isValid()) { qDebug("[QxOrm] session error : '%s'", qPrintable(session.firstError().text())); }

} // End of scope : session is destroyed (transaction => automatically commit or rollback if there is an error)
 * \endcode
 */
class QX_DLL_EXPORT QxSession : private boost::noncopyable
{

private:

   QSqlDatabase m_database;            //!< Database connexion of current session
   QList<QSqlError> m_lstSqlError;     //!< List of SQL errors
   bool m_bTransaction;                //!< Flag to know if a transaction is opened or not
   bool m_bThrowable;                  //!< When a SQL error is appended, an exception of type qx::dao::sql_error is thrown
   bool m_bThrowInEvent;               //!< An exception of type qx::dao::sql_error is throwing
   bool m_bAutoOpenClose;              //!< Open and close automatically connection to database

public:

   QxSession();
   QxSession(const QSqlDatabase & database);
   QxSession(const QSqlDatabase & database, bool bOpenTransaction);
   QxSession(const QSqlDatabase & database, bool bOpenTransaction, bool bThrowable);
   virtual ~QxSession() { close(); }

   inline bool isThrowable() const              { return m_bThrowable; }
   inline bool isOpened() const                 { return m_bTransaction; }
   inline bool isValid() const                  { return (m_lstSqlError.count() <= 0); }
   inline QSqlError firstError() const          { return ((m_lstSqlError.count() > 0) ? m_lstSqlError.first() : QSqlError()); }
   inline QSqlError lastError() const           { return ((m_lstSqlError.count() > 0) ? m_lstSqlError.last() : QSqlError()); }
   inline QList<QSqlError> allErrors() const    { return m_lstSqlError; }
   inline const QSqlDatabase * database() const { return (& m_database); }
   inline QSqlDatabase * database()             { return (& m_database); }

   bool open();
   bool close();
   bool commit();
   bool rollback();

   QxSession & operator+= (const QSqlError & err);

private:

   void appendSqlError(const QSqlError & err);
   void clear();

public:

   template <class T>
   long count(const qx::QxSqlQuery & query = qx::QxSqlQuery())
   { return qx::dao::count<T>(query, this->database()); }

   template <class T>
   QSqlError count(long & lCount, const qx::QxSqlQuery & query = qx::QxSqlQuery())
   { return qx::dao::count<T>(lCount, query, this->database()); }

   template <class T>
   T * fetchById(const QVariant & id, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      IxDataMemberX * pDataMemberX = QxClass<T>::getSingleton()->getDataMemberX();
      IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL);
      if (! pDataMemberId) { qAssert(false); return NULL; }
      T * t = new T(); QSqlError err;
      pDataMemberId->fromVariant(t, id, -1, qx::cvt::context::e_database);
      if (relation.count() == 0) { err = qx::dao::fetch_by_id((* t), this->database(), columns); }
      else { err = qx::dao::fetch_by_id_with_relation(relation, (* t), this->database()); }
      if (err.isValid()) { delete t; t = NULL; (* this) += err; }
      return t;
   }

   template <class T>
   QSqlError fetchById(T & t, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::fetch_by_id(t, this->database(), columns); }
      else { err = qx::dao::fetch_by_id_with_relation(relation, t, this->database()); }
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError fetchAll(T & t, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::fetch_all(t, this->database(), columns); }
      else { err = qx::dao::fetch_all_with_relation(relation, t, this->database()); }
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError fetchByQuery(const qx::QxSqlQuery & query, T & t, const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::fetch_by_query(query, t, this->database(), columns); }
      else { err = qx::dao::fetch_by_query_with_relation(relation, query, t, this->database()); }
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError insert(T & t, const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::insert(t, this->database()); }
      else { err = qx::dao::insert_with_relation(relation, t, this->database()); }
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError update(T & t, const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::update_by_query(query, t, this->database(), columns); }
      else { err = qx::dao::update_by_query_with_relation(relation, query, t, this->database()); }
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError save(T & t, const QStringList & relation = QStringList())
   {
      QSqlError err;
      if (relation.count() == 0) { err = qx::dao::save(t, this->database()); }
      else { err = qx::dao::save_with_relation(relation, t, this->database()); }
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError deleteById(const QVariant & id)
   {
      IxDataMemberX * pDataMemberX = QxClass<T>::getSingleton()->getDataMemberX();
      IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL);
      if (! pDataMemberId) { qAssert(false); return QSqlError(); }
      qx_shared_ptr<T> t; t.reset(new T());
      pDataMemberId->fromVariant(t.get(), id, -1, qx::cvt::context::e_database);
      QSqlError err = qx::dao::delete_by_id((* t), this->database());
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError deleteById(T & t)
   {
      QSqlError err = qx::dao::delete_by_id(t, this->database());
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError deleteAll()
   {
      QSqlError err = qx::dao::delete_all<T>(this->database());
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError deleteByQuery(const qx::QxSqlQuery & query)
   {
      QSqlError err = qx::dao::delete_by_query<T>(query, this->database());
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError destroyById(const QVariant & id)
   {
      IxDataMemberX * pDataMemberX = QxClass<T>::getSingleton()->getDataMemberX();
      IxDataMember * pDataMemberId = (pDataMemberX ? pDataMemberX->getId_WithDaoStrategy() : NULL);
      if (! pDataMemberId) { qAssert(false); return QSqlError(); }
      qx_shared_ptr<T> t; t.reset(new T());
      pDataMemberId->fromVariant(t.get(), id, -1, qx::cvt::context::e_database);
      QSqlError err = qx::dao::destroy_by_id((* t), this->database());
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError destroyById(T & t)
   {
      QSqlError err = qx::dao::destroy_by_id(t, this->database());
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError destroyAll()
   {
      QSqlError err = qx::dao::destroy_all<T>(this->database());
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError destroyByQuery(const qx::QxSqlQuery & query)
   {
      QSqlError err = qx::dao::destroy_by_query<T>(query, this->database());
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   QSqlError executeQuery(qx::QxSqlQuery & query, T & t)
   {
      QSqlError err = qx::dao::execute_query<T>(query, t, this->database());
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   QSqlError callQuery(qx::QxSqlQuery & query)
   {
      QSqlError err = qx::dao::call_query(query, this->database());
      if (err.isValid()) { (* this) += err; }
      return err;
   }

   template <class T>
   qx_bool exist(T & t)
   { return qx::dao::exist(t, this->database()); }

};

} // namespace qx

#endif // _QX_DAO_SESSION_H_
