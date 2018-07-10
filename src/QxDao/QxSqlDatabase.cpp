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

#include <QxPrecompiled.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxDao/QxSqlGenerator/QxSqlGenerator.h>

#include <QxMemLeak/mem_leak.h>

QX_DLL_EXPORT_QX_SINGLETON_CPP(qx::QxSqlDatabase)

namespace qx {

QSqlDatabase QxSqlDatabase::getDatabase(QSqlError & dbError)
{
   return QxSqlDatabase::getSingleton()->getDatabaseByCurrThreadId(dbError);
}

QSqlDatabase QxSqlDatabase::getDatabase()
{
   QSqlError dbError; Q_UNUSED(dbError);
   return QxSqlDatabase::getDatabase(dbError);
}

QSqlDatabase QxSqlDatabase::getDatabaseCloned()
{
   QSqlError dbError; Q_UNUSED(dbError);
   QString sKeyClone = QUuid::createUuid().toString();
   return QSqlDatabase::cloneDatabase(QxSqlDatabase::getDatabase(dbError), sKeyClone);
}

QSqlDatabase QxSqlDatabase::getDatabaseByCurrThreadId(QSqlError & dbError)
{
   QMutexLocker locker(& m_oDbMutex);
   dbError = QSqlError();

   if (! isValid())
   {
      qDebug("[QxOrm] qx::QxSqlDatabase : '%s'", "parameters are not valid");
      dbError = QSqlError("[QxOrm] qx::QxSqlDatabase : 'parameters are not valid'", "", QSqlError::UnknownError);
      qAssert(false); return QSqlDatabase();
   }

   Qt::HANDLE lCurrThreadId = QThread::currentThreadId();
   if (! lCurrThreadId)
   {
      qDebug("[QxOrm] qx::QxSqlDatabase : '%s'", "unable to find current thread id");
      dbError = QSqlError("[QxOrm] qx::QxSqlDatabase : 'unable to find current thread id'", "", QSqlError::UnknownError);
      qAssert(false); return QSqlDatabase();
   }

   if (! m_lstDbByThread.contains(lCurrThreadId)) { return createDatabase(dbError); }
   QString sDbKey = m_lstDbByThread.value(lCurrThreadId);
   if (! QSqlDatabase::contains(sDbKey)) { return createDatabase(dbError); }
   return QSqlDatabase::database(sDbKey);
}

namespace helper {

template <typename T, bool bIsPointer>
struct CvtQtHandle
{ static QString toString(T t) { return QString::number(static_cast<qlonglong>(t)); } };

template <typename T>
struct CvtQtHandle<T, true>
{
   static QString toString(T t)
   {
      const void * ptr = static_cast<const void *>(t);
      QString value; QTextStream stream(& value);
      stream << ptr;
      return value;
   }
};

} // namespace helper

QSqlDatabase QxSqlDatabase::createDatabase(QSqlError & dbError)
{
   Qt::HANDLE lCurrThreadId = QThread::currentThreadId();
   QString sCurrThreadId = qx::helper::CvtQtHandle<Qt::HANDLE, std::is_pointer<Qt::HANDLE>::value>::toString(lCurrThreadId);
   QString sDbKeyNew = QUuid::createUuid().toString();
   dbError = QSqlError();
   bool bError = false;

   {
      QSqlDatabase db = QSqlDatabase::addDatabase(m_sDriverName, sDbKeyNew);
      db.setConnectOptions(m_sConnectOptions);
      db.setDatabaseName(m_sDatabaseName);
      db.setUserName(m_sUserName);
      db.setPassword(m_sPassword);
      db.setHostName(m_sHostName);
      if (m_iPort != -1) { db.setPort(m_iPort); }
      if (! db.open()) { displayLastError(db, "unable to open connection to database"); bError = true; }
      if (bError) { dbError = db.lastError(); }
      if (bError && ! dbError.isValid())
      { dbError = QSqlError("[QxOrm] qx::QxSqlDatabase : 'unable to open connection to database'", "", QSqlError::UnknownError); }
   }

   if (bError) { QSqlDatabase::removeDatabase(sDbKeyNew); return QSqlDatabase(); }
   m_lstDbByThread.insert(lCurrThreadId, sDbKeyNew);
   qDebug("[QxOrm] qx::QxSqlDatabase : create new database connection in thread '%s' with key '%s'", qPrintable(sCurrThreadId), qPrintable(sDbKeyNew));
   QSqlDatabase dbconn = QSqlDatabase::database(sDbKeyNew);
   if (m_fctDatabaseOpen) { m_fctDatabaseOpen(dbconn); }
   return dbconn;
}

void QxSqlDatabase::displayLastError(const QSqlDatabase & db, const QString & sDesc) const
{
   QString sLastError = formatLastError(db);
   if (sDesc.isEmpty()) { qDebug("[QxOrm] qx::QxSqlDatabase : '%s'", qPrintable(sLastError)); }
   else { qDebug("[QxOrm] qx::QxSqlDatabase : '%s'\n%s", qPrintable(sDesc), qPrintable(sLastError)); }
}

QString QxSqlDatabase::formatLastError(const QSqlDatabase & db) const
{
   QString sLastError;
   if (db.lastError().number() != -1) { sLastError += QString("Error number '") + QString::number(db.lastError().number()) + QString("' : "); }
   if (! db.lastError().text().isEmpty()) { sLastError += db.lastError().text(); }
   else { sLastError += "<no error description>"; }
   return sLastError;
}

qx::dao::detail::IxSqlGenerator * QxSqlDatabase::getSqlGenerator()
{
   if (m_pSqlGenerator) { return m_pSqlGenerator.get(); }
   QMutexLocker locker(& m_oDbMutex);

   if (m_sDriverName == "QMYSQL")         { m_pSqlGenerator.reset(new qx::dao::detail::QxSqlGenerator_MySQL()); }
   else if (m_sDriverName == "QPSQL")     { m_pSqlGenerator.reset(new qx::dao::detail::QxSqlGenerator_PostgreSQL()); }
   else if (m_sDriverName == "QSQLITE")   { m_pSqlGenerator.reset(new qx::dao::detail::QxSqlGenerator_SQLite()); }
   else if (m_sDriverName == "QOCI")      { m_pSqlGenerator.reset(new qx::dao::detail::QxSqlGenerator_Oracle()); }

   if (! m_pSqlGenerator) { m_pSqlGenerator.reset(new qx::dao::detail::QxSqlGenerator_Standard()); }
   m_pSqlGenerator->init();
   return m_pSqlGenerator.get();
}

void QxSqlDatabase::closeAllDatabases()
{
   qx::QxSqlDatabase * pSingleton = qx::QxSqlDatabase::getSingleton();
   if (! pSingleton) { qAssert(false); return; }
   Q_FOREACH(QString sDbKey, pSingleton->m_lstDbByThread)
   { QSqlDatabase::database(sDbKey).close(); }
}

void QxSqlDatabase::clearAllDatabases()
{
   qx::QxSqlDatabase::closeAllDatabases();
   qx::QxSqlDatabase * pSingleton = qx::QxSqlDatabase::getSingleton();
   if (! pSingleton) { qAssert(false); return; }
   pSingleton->m_lstDbByThread.clear();
   pSingleton->m_sDriverName = "";
   pSingleton->m_sConnectOptions = "";
   pSingleton->m_sDatabaseName = "";
   pSingleton->m_sUserName = "";
   pSingleton->m_sPassword = "";
   pSingleton->m_sHostName = "";
   pSingleton->m_iPort = -1;
}

} // namespace qx
