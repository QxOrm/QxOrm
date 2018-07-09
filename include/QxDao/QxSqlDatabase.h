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

#ifndef _QX_SQL_DATABASE_H_
#define _QX_SQL_DATABASE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtCore/qhash.h>
#include <QtCore/qmutex.h>
#include <QtCore/qthread.h>
#include <QtCore/quuid.h>

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>

#include "../../include/QxSingleton/QxSingleton.h"

namespace qx {

class QX_DLL_EXPORT QxSqlDatabase : public QxSingleton<QxSqlDatabase>
{

   friend class QxSingleton<QxSqlDatabase>;

public:

   enum ph_style { ph_style_question_mark, ph_style_2_point_name, ph_style_at_name };

private:

   QHash<Qt::HANDLE, QString> m_lstDbByThread;  // Collection of databases connexions by thread id
   QMutex m_oDbMutex;                           // Mutex => 'QxSqlDatabase' is thread-safe
   QString m_sDriverName;                       // Driver name to connect to database
   QString m_sConnectOptions;                   // Connect options to database
   QString m_sDatabaseName;                     // Database name
   QString m_sUserName;                         // Connection's user name
   QString m_sPassword;                         // Connection's password
   QString m_sHostName;                         // Connection's host name
   int m_iPort;                                 // Connection's port number
   bool m_bTraceSqlQuery;                       // Trace each sql query executed
   bool m_bTraceSqlRecord;                      // Trace each sql record
   ph_style m_ePlaceHolderStyle;                // Place holder style to build sql query

private:

   QxSqlDatabase() : QxSingleton<QxSqlDatabase>("qx::QxSqlDatabase"), m_iPort(-1), m_bTraceSqlQuery(true), m_bTraceSqlRecord(false), m_ePlaceHolderStyle(ph_style_2_point_name) { ; }
   virtual ~QxSqlDatabase() { ; }

public:

   QString getDriverName() const                { return m_sDriverName; }
   QString getConnectOptions() const            { return m_sConnectOptions; }
   QString getDatabaseName() const              { return m_sDatabaseName; }
   QString getUserName() const                  { return m_sUserName; }
   QString getPassword() const                  { return m_sPassword; }
   QString getHostName() const                  { return m_sHostName; }
   int getPort() const                          { return m_iPort; }
   bool getTraceSqlQuery() const                { return m_bTraceSqlQuery; }
   bool getTraceSqlRecord() const               { return m_bTraceSqlRecord; }
   ph_style getSqlPlaceHolderStyle() const      { return m_ePlaceHolderStyle; }

   void setDriverName(const QString & s)        { m_sDriverName = s; }
   void setConnectOptions(const QString & s)    { m_sConnectOptions = s; }
   void setDatabaseName(const QString & s)      { m_sDatabaseName = s; }
   void setUserName(const QString & s)          { m_sUserName = s; }
   void setPassword(const QString & s)          { m_sPassword = s; }
   void setHostName(const QString & s)          { m_sHostName = s; }
   void setPort(int i)                          { m_iPort = i; }
   void setTraceSqlQuery(bool b)                { m_bTraceSqlQuery = b; }
   void setTraceSqlRecord(bool b)               { m_bTraceSqlRecord = b; }
   void setSqlPlaceHolderStyle(ph_style e)      { m_ePlaceHolderStyle = e; }

   static QSqlDatabase getDatabase() { return qx::QxSqlDatabase::getSingleton()->getDatabaseByCurrThreadId(); }

private:

   QSqlDatabase getDatabaseByCurrThreadId();
   QSqlDatabase createDatabase();

   void displayLastError(const QSqlDatabase & db, const QString & sDesc) const;
   QString formatLastError(const QSqlDatabase & db) const;

   bool isValid() const { return (! m_sDriverName.isEmpty() && ! m_sDatabaseName.isEmpty()); }

};

} // namespace qx

#endif // _QX_SQL_DATABASE_H_
