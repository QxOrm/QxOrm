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

#ifndef _QX_SQL_DATABASE_H_
#define _QX_SQL_DATABASE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlDatabase.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Define all parameters to connect to database and retrieve a valid connection by thread
 */

#include <QtCore/qhash.h>
#include <QtCore/qmutex.h>
#include <QtCore/qthread.h>
#include <QtCore/quuid.h>

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>

#include <QxSingleton/QxSingleton.h>

#include <QxDao/QxSqlGenerator/IxSqlGenerator.h>

namespace qx {
namespace dao {
namespace detail {

class IxDao_Helper;

} // namespace detail
} // namespace dao
} // namespace qx

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlDatabase : define all parameters to connect to database and retrieve a valid connection by thread (this class is a singleton and is thread-safe)
 */
class QX_DLL_EXPORT QxSqlDatabase : public QxSingleton<QxSqlDatabase>
{

   friend class QxSingleton<QxSqlDatabase>;
   friend class qx::dao::detail::IxDao_Helper;

public:

   enum ph_style { ph_style_question_mark, ph_style_2_point_name, ph_style_at_name };

   typedef std::function<void (QSqlDatabase &)> type_fct_db_open;

private:

   struct QxSqlDatabaseImpl;
   std::unique_ptr<QxSqlDatabaseImpl> m_pImpl; //!< Private implementation idiom

   QxSqlDatabase();
   virtual ~QxSqlDatabase();

public:

   QString getDriverName() const;
   QString getConnectOptions() const;
   QString getDatabaseName() const;
   QString getUserName() const;
   QString getPassword() const;
   QString getHostName() const;
   int getPort() const;
   bool getTraceSqlQuery() const;
   bool getTraceSqlRecord() const;
   bool getTraceSqlBoundValues() const;
   bool getTraceSqlBoundValuesOnError() const;
   ph_style getSqlPlaceHolderStyle() const;
   bool getSessionThrowable() const;
   bool getSessionAutoTransaction() const;
   bool getValidatorThrowable() const;
   bool getAutoReplaceSqlAliasIntoQuery() const;
   bool getVerifyOffsetRelation() const;
   bool getAddAutoIncrementIdToUpdateQuery() const;
   bool getForceParentIdToAllChildren() const;
   type_fct_db_open getFctDatabaseOpen() const;
   bool getAddSqlSquareBracketsForTableName() const;
   bool getAddSqlSquareBracketsForColumnName() const;
   bool getFormatSqlQueryBeforeLogging() const;
   QStringList getSqlDelimiterForTableName() const;
   QStringList getSqlDelimiterForColumnName() const;
   int getTraceSqlOnlySlowQueriesDatabase() const;
   int getTraceSqlOnlySlowQueriesTotal() const;
   bool getDisplayTimerDetails() const;

   void setDriverName(const QString & s, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setConnectOptions(const QString & s, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setDatabaseName(const QString & s, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setUserName(const QString & s, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setPassword(const QString & s, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setHostName(const QString & s, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setPort(int i, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setTraceSqlQuery(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setTraceSqlRecord(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setTraceSqlBoundValues(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setTraceSqlBoundValuesOnError(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setSqlPlaceHolderStyle(ph_style e, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setSessionThrowable(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setSessionAutoTransaction(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setValidatorThrowable(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setSqlGenerator(qx::dao::detail::IxSqlGenerator_ptr p, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setAutoReplaceSqlAliasIntoQuery(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setVerifyOffsetRelation(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setAddAutoIncrementIdToUpdateQuery(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setForceParentIdToAllChildren(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setFctDatabaseOpen(type_fct_db_open fct, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setAddSqlSquareBracketsForTableName(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setAddSqlSquareBracketsForColumnName(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setFormatSqlQueryBeforeLogging(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setSqlDelimiterForTableName(const QStringList & lst, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setSqlDelimiterForColumnName(const QStringList & lst, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setTraceSqlOnlySlowQueriesDatabase(int i, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setTraceSqlOnlySlowQueriesTotal(int i, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);
   void setDisplayTimerDetails(bool b, bool bJustForCurrentThread = false, QSqlDatabase * pJustForThisDatabase = NULL);

   static QSqlDatabase getDatabase();
   static QSqlDatabase getDatabase(QSqlError & dbError);
   static QSqlDatabase getDatabaseCloned();
   static QSqlDatabase checkDatabaseByThread();
   static void closeAllDatabases();
   static void clearAllDatabases();
   static bool isEmpty();

   qx::dao::detail::IxSqlGenerator * getSqlGenerator();

   void clearAllSettingsForCurrentThread();
   void clearAllSettingsForDatabase(QSqlDatabase * p);

protected:

   bool setCurrentDatabaseByThread(QSqlDatabase * p);
   void clearCurrentDatabaseByThread();

};

} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::QxSqlDatabase)

#endif // _QX_SQL_DATABASE_H_
