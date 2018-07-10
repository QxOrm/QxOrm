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

#include <QxPrecompiled.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxDao/QxSqlGenerator/QxSqlGenerator.h>

#include <QxMemLeak/mem_leak.h>

QX_DLL_EXPORT_QX_SINGLETON_CPP(qx::QxSqlDatabase)

namespace qx {

QSqlDatabase QxSqlDatabase::getDatabaseByCurrThreadId()
{
   QMutexLocker locker(& m_oDbMutex);
   if (! isValid()) { qDebug("[QxOrm] qx::QxSqlDatabase : %s", "parameters are not valid"); qAssert(false); return QSqlDatabase(); }
   Qt::HANDLE lCurrThreadId = QThread::currentThreadId();
   if (! lCurrThreadId) { qDebug("[QxOrm] qx::QxSqlDatabase : %s", "unable to find current thread id"); qAssert(false); return QSqlDatabase(); }
   if (! m_lstDbByThread.contains(lCurrThreadId)) { return createDatabase(); }
   QString sDbKey = m_lstDbByThread.value(lCurrThreadId);
   if (! QSqlDatabase::contains(sDbKey)) { return createDatabase(); }

   return QSqlDatabase::database(sDbKey);
}

QSqlDatabase QxSqlDatabase::createDatabase()
{
   Qt::HANDLE lCurrThreadId = QThread::currentThreadId();
   QString sDbKeyNew = QUuid::createUuid().toString();
   bool bError = false;

   {
      QSqlDatabase db = QSqlDatabase::addDatabase(m_sDriverName, sDbKeyNew);
      db.setConnectOptions(m_sConnectOptions);
      db.setDatabaseName(m_sDatabaseName);
      db.setUserName(m_sUserName);
      db.setPassword(m_sPassword);
      db.setHostName(m_sHostName);
      if (m_iPort != -1) { db.setPort(m_iPort); }
      if (! db.open()) { displayLastError(db, "unable to open connection to database"); bError = true; qAssert(false); }
   }

   if (bError) { QSqlDatabase::removeDatabase(sDbKeyNew); return QSqlDatabase(); }
   m_lstDbByThread.insert(lCurrThreadId, sDbKeyNew);
   qDebug("[QxOrm] qx::QxSqlDatabase : create new database connection in thread '%ld' with key '%s'", (long)(lCurrThreadId), qPrintable(sDbKeyNew));

   return QSqlDatabase::database(sDbKeyNew);
}

void QxSqlDatabase::displayLastError(const QSqlDatabase & db, const QString & sDesc) const
{
   if (sDesc.isEmpty()) { qDebug("[QxOrm] qx::QxSqlDatabase : %s", qPrintable(formatLastError(db))); }
   else                 { qDebug("[QxOrm] qx::QxSqlDatabase : %s\n%s", qPrintable(sDesc), qPrintable(formatLastError(db))); }
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
   return m_pSqlGenerator.get();
}

} // namespace qx
