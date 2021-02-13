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

#include <QxPrecompiled.h>

#include <QxDao/QxSession.h>
#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

struct Q_DECL_HIDDEN QxSession::QxSessionImpl
{

   QSqlDatabase m_database;            //!< Database connexion of current session
   QList<QSqlError> m_lstSqlError;     //!< List of SQL errors
   bool m_bTransaction;                //!< Flag to know if a transaction is opened or not
   bool m_bThrowable;                  //!< When a SQL error is appended, an exception of type qx::dao::sql_error is thrown
   bool m_bThrowInEvent;               //!< An exception of type qx::dao::sql_error is throwing
   bool m_bAutoOpenClose;              //!< Open and close automatically connection to database
   bool m_bIgnoreSoftDelete;           //!< Ignore soft delete behavior even if it has been defined for registered classes
   QStringList m_lstIgnoreSoftDelete;  //!< List of registered classes to ignore soft delete behavior (if empty and m_bIgnoreSoftDelete is true, then all classes are ignored)
   bool m_bAutoRollbackWhenDestroyed;  //!< If true, then database rollback is called when this session instance destructor (or close() method) is invoked

   static QMutex m_mutex;                                         //!< Mutex => qx::QxSession is thread-safe
   static QHash<QString, qx::QxSession *> m_lstActiveSessions;    //!< List of active sessions by database connection name

   QxSessionImpl() : m_bTransaction(false), m_bThrowable(false), m_bThrowInEvent(false), m_bAutoOpenClose(false), m_bIgnoreSoftDelete(false), m_bAutoRollbackWhenDestroyed(false) { ; }
   QxSessionImpl(const QSqlDatabase & database) : m_database(database), m_bTransaction(false), m_bThrowable(false), m_bThrowInEvent(false), m_bAutoOpenClose(false), m_bIgnoreSoftDelete(false), m_bAutoRollbackWhenDestroyed(false) { ; }
   QxSessionImpl(const QSqlDatabase & database, bool bThrowable, bool bAutoRollbackWhenDestroyed) : m_database(database), m_bTransaction(false), m_bThrowable(bThrowable), m_bThrowInEvent(false), m_bAutoOpenClose(false), m_bIgnoreSoftDelete(false), m_bAutoRollbackWhenDestroyed(bAutoRollbackWhenDestroyed) { ; }
   ~QxSessionImpl() { ; }

   void appendSqlError(const QSqlError & err)
   {
      if (! err.isValid()) { return; }
      m_lstSqlError.append(err);
      if (m_bThrowInEvent) { return; }
      if (m_bThrowable) { QString msg = err.text(); qDebug("[QxOrm] qx::QxSession throw 'qx::dao::sql_error' exception : '%s'", qPrintable(msg)); }
      if (m_bThrowable) { m_bThrowInEvent = true; throw qx::dao::sql_error(err); }
      m_bThrowInEvent = false;
   }

   void clear()
   {
      m_lstSqlError.clear();
      m_bTransaction = false;
   }

};

QMutex qx::QxSession::QxSessionImpl::m_mutex;
QHash<QString, qx::QxSession *> qx::QxSession::QxSessionImpl::m_lstActiveSessions;

QxSession::QxSession() : m_pImpl(new QxSessionImpl())
{
   m_pImpl->m_database = qx::QxSqlDatabase::getDatabaseCloned();
   m_pImpl->m_bThrowable = qx::QxSqlDatabase::getSingleton()->getSessionThrowable();
   if (qx::QxSqlDatabase::getSingleton()->getSessionAutoTransaction()) { open(); }
   QMutexLocker locker(& QxSessionImpl::m_mutex);
   QString connectionName = m_pImpl->m_database.connectionName();
   if (! connectionName.isEmpty()) { QxSessionImpl::m_lstActiveSessions.insert(connectionName, this); }
}

QxSession::QxSession(const QSqlDatabase & database) : m_pImpl(new QxSessionImpl(database))
{
   m_pImpl->m_bThrowable = qx::QxSqlDatabase::getSingleton()->getSessionThrowable();
   if (qx::QxSqlDatabase::getSingleton()->getSessionAutoTransaction()) { open(); }
   QMutexLocker locker(& QxSessionImpl::m_mutex);
   QString connectionName = m_pImpl->m_database.connectionName();
   if (! connectionName.isEmpty()) { QxSessionImpl::m_lstActiveSessions.insert(connectionName, this); }
}

QxSession::QxSession(const QSqlDatabase & database, bool bOpenTransaction) : m_pImpl(new QxSessionImpl(database))
{
   m_pImpl->m_bThrowable = qx::QxSqlDatabase::getSingleton()->getSessionThrowable();
   if (bOpenTransaction) { open(); }
   QMutexLocker locker(& QxSessionImpl::m_mutex);
   QString connectionName = m_pImpl->m_database.connectionName();
   if (! connectionName.isEmpty()) { QxSessionImpl::m_lstActiveSessions.insert(connectionName, this); }
}

QxSession::QxSession(const QSqlDatabase & database, bool bOpenTransaction, bool bThrowable, bool bAutoRollbackWhenDestroyed /* = false */) : m_pImpl(new QxSessionImpl(database, bThrowable, bAutoRollbackWhenDestroyed))
{
   if (bOpenTransaction) { open(); }
   QMutexLocker locker(& QxSessionImpl::m_mutex);
   QString connectionName = m_pImpl->m_database.connectionName();
   if (! connectionName.isEmpty()) { QxSessionImpl::m_lstActiveSessions.insert(connectionName, this); }
}

QxSession::~QxSession()
{
   close();
   QMutexLocker locker(& QxSessionImpl::m_mutex);
   QString connectionName = m_pImpl->m_database.connectionName();
   if (! connectionName.isEmpty()) { QxSessionImpl::m_lstActiveSessions.remove(connectionName); }
}

QxSession * QxSession::getActiveSession(QSqlDatabase * db)
{
   if (! db) { return NULL; }
   QString connectionName = db->connectionName();
   if (connectionName.isEmpty()) { return NULL; }
   QMutexLocker locker(& QxSessionImpl::m_mutex);
   return (QxSessionImpl::m_lstActiveSessions.contains(connectionName) ? QxSessionImpl::m_lstActiveSessions.value(connectionName) : NULL);
}

bool QxSession::isThrowable() const { return m_pImpl->m_bThrowable; }

bool QxSession::isOpened() const { return m_pImpl->m_bTransaction; }

bool QxSession::isValid() const { return (m_pImpl->m_lstSqlError.count() <= 0); }

bool QxSession::isAutoRollbackWhenDestroyed() const { return m_pImpl->m_bAutoRollbackWhenDestroyed; }

void QxSession::setAutoRollbackWhenDestroyed(bool b) { m_pImpl->m_bAutoRollbackWhenDestroyed = b; }

QSqlError QxSession::firstError() const { return ((m_pImpl->m_lstSqlError.count() > 0) ? m_pImpl->m_lstSqlError.first() : QSqlError()); }

QSqlError QxSession::lastError() const { return ((m_pImpl->m_lstSqlError.count() > 0) ? m_pImpl->m_lstSqlError.last() : QSqlError()); }

QList<QSqlError> QxSession::allErrors() const { return m_pImpl->m_lstSqlError; }

const QSqlDatabase * QxSession::database() const { return (& m_pImpl->m_database); }

QSqlDatabase * QxSession::database() { return (& m_pImpl->m_database); }

bool QxSession::open()
{
   if (m_pImpl->m_bTransaction) { return true; }
   if (! m_pImpl->m_database.isOpen()) { m_pImpl->m_bAutoOpenClose = m_pImpl->m_database.open(); if (! m_pImpl->m_bAutoOpenClose) { m_pImpl->appendSqlError(m_pImpl->m_database.lastError()); return false; } }
   if (! m_pImpl->m_database.driver() || ! m_pImpl->m_database.driver()->hasFeature(QSqlDriver::Transactions)) { return false; }
   m_pImpl->m_bTransaction = m_pImpl->m_database.transaction();
   return m_pImpl->m_bTransaction;
}

bool QxSession::close()
{
   bool bCloseOk = true;
   if (m_pImpl->m_bTransaction && m_pImpl->m_bAutoRollbackWhenDestroyed) { bCloseOk = rollback(); }
   else if (m_pImpl->m_bTransaction && isValid()) { bCloseOk = commit(); }
   else if (m_pImpl->m_bTransaction) { bCloseOk = rollback(); }
   if (m_pImpl->m_bAutoOpenClose) { m_pImpl->m_database.close(); m_pImpl->m_bAutoOpenClose = false; }
   return bCloseOk;
}

bool QxSession::commit()
{
   if (m_pImpl->m_bTransaction && ! isValid()) { qDebug("[QxOrm] %s", "qx::QxSession is not valid and 'commit()' method is called"); }
   if (! m_pImpl->m_bTransaction) { m_pImpl->clear(); return false; }
   bool bCommit = m_pImpl->m_database.commit();
   if (bCommit) { m_pImpl->clear(); return true; }
   m_pImpl->appendSqlError(m_pImpl->m_database.lastError());
   m_pImpl->m_bTransaction = false;
   return false;
}

bool QxSession::rollback()
{
   if (! m_pImpl->m_bTransaction) { m_pImpl->clear(); return false; }
   qDebug("[QxOrm] qx::QxSession : '%s'", "rollback transaction");
   bool bRollback = m_pImpl->m_database.rollback();
   if (bRollback) { m_pImpl->clear(); return true; }
   m_pImpl->appendSqlError(m_pImpl->m_database.lastError());
   m_pImpl->m_bTransaction = false;
   return false;
}

QxSession & QxSession::operator+= (const QSqlError & err)
{
   m_pImpl->appendSqlError(err);
   return (* this);
}

void QxSession::ignoreSoftDelete(bool bIgnoreSoftDelete /* = true */, const QStringList & classesToIgnore /* = QStringList() */)
{
   m_pImpl->m_bIgnoreSoftDelete = bIgnoreSoftDelete;
   m_pImpl->m_lstIgnoreSoftDelete = classesToIgnore;
   m_pImpl->m_lstIgnoreSoftDelete.sort();
}

bool QxSession::checkIgnoreSoftDelete(const QString & classKey) const
{
   if (! m_pImpl->m_bIgnoreSoftDelete) { return false; }
   if (m_pImpl->m_lstIgnoreSoftDelete.isEmpty()) { return true; }
   if (m_pImpl->m_lstIgnoreSoftDelete.contains(classKey)) { return true; }
   return false;
}

QString QxSession::getIgnoreSoftDeleteHash() const
{
   if (! m_pImpl->m_bIgnoreSoftDelete) { return ""; }
   if (m_pImpl->m_lstIgnoreSoftDelete.isEmpty()) { return "[ALL]"; }
   return m_pImpl->m_lstIgnoreSoftDelete.join("_");
}

} // namespace qx
