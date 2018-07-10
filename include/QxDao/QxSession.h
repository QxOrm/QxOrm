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

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqldriver.h>

#include <QtCore/qlist.h>

#include <QxDao/QxSqlError.h>

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSession : define a session to manage automatically database transactions (using C++ RAII)
 *
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

};

} // namespace qx

#endif // _QX_DAO_SESSION_H_
