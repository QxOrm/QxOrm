/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#include "../../include/QxPrecompiled.h"

#include "../../include/QxDao/QxSqlDatabase.h"

#include "../../include/QxMemLeak/mem_leak.h"

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

} // namespace qx
