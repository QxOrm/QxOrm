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

#ifndef _IX_DAO_HELPER_H_
#define _IX_DAO_HELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxDao_Helper.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Helper class to communicate with database
 */

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqldriver.h>
#include <QtSql/qsqlrecord.h>

#include <QxTraits/get_primary_key.h>
#include <QxTraits/is_valid_primary_key.h>

#include <QxDao/QxSqlDatabase.h>
#include <QxDao/IxSqlQueryBuilder.h>
#include <QxDao/QxSqlQuery.h>
#include <QxDao/IxSqlRelation.h>
#include <QxDao/QxSqlRelationLinked.h>

#include <QxDao/QxSqlGenerator/IxSqlGenerator.h>

#include <QxCollection/QxCollection.h>

#include <QxDataMember/IxDataMemberX.h>

#include <QxValidator/QxInvalidValueX.h>
#include <QxValidator/QxValidatorError.h>

namespace qx {
template <class T>
QxInvalidValueX validate(T & t, const QString & group);
class QxSession;
} // namespace qx

namespace qx {
namespace dao {
namespace detail {

struct IxDao_Timer;

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::IxDao_Helper : helper class to communicate with database
 */
class QX_DLL_EXPORT IxDao_Helper
{

   friend struct IxDao_Timer;

public:

   enum timer_type { timer_none, timer_total, timer_db_exec, timer_db_next, timer_db_prepare, timer_cpp_build_hierarchy, 
                     timer_cpp_build_instance, timer_cpp_read_instance, timer_build_sql, timer_db_open, timer_db_transaction };

private:

   struct IxDao_HelperImpl;
   std::unique_ptr<IxDao_HelperImpl> m_pImpl; //!< Private implementation idiom

protected:

   IxDao_Helper(qx::IxSqlQueryBuilder * pBuilder, const qx::QxSqlQuery * pQuery = NULL);
   virtual ~IxDao_Helper();

public:

   bool isValid() const;
   bool hasFeature(QSqlDriver::DriverFeature ft) const;

   QSqlDatabase & database();
   const QSqlDatabase & database() const;
   QSqlQuery & query();
   const QSqlQuery & query() const;
   QSqlError & error();
   const QSqlError & error() const;
   qx::QxSqlQuery & qxQuery();
   const qx::QxSqlQuery & qxQuery() const;
   qx::IxSqlQueryBuilder & builder();
   const qx::IxSqlQueryBuilder & builder() const;
   qx::IxDataMemberX * getDataMemberX() const;
   long getDataCount() const;
   qx::IxDataMember * getDataId() const;
   qx::IxDataMember * nextData(long & l) const;
   QString sql() const;
   qx::QxSqlRelationLinked * getSqlRelationLinked() const;
   qx::QxSession * getSession() const;
   QString getIgnoreSoftDeleteHash() const;
   bool getCartesianProduct() const;
   QStringList getSqlColumns() const;
   void setSqlColumns(const QStringList & lst);
   IxSqlGenerator * getSqlGenerator() const;
   void addInvalidValues(const qx::QxInvalidValueX & lst);
   bool getAddAutoIncrementIdToUpdateQuery() const;
   QStringList & itemsAsJson();
   bool isReadOnly() const;
   bool isMongoDB() const;

   QSqlError errFailed(bool bPrepare = false);
   QSqlError errEmpty();
   QSqlError errNoData();
   QSqlError errInvalidId();
   QSqlError errInvalidRelation();
   QSqlError errReadOnly();

   bool transaction();
   bool nextRecord();
   void quiet();
   bool exec(bool bForceEmptyExec = false);
   bool prepare(QString & sql);

   QSqlError updateError(const QSqlError & error);
   bool updateSqlRelationX(const QStringList & relation);
   void addQuery(bool bResolve);
   void dumpRecord() const;

   template <class U>
   inline bool isValidPrimaryKey(const U & u)
   { return (getDataId() && qx::trait::is_valid_primary_key(getDataId()->toVariant((& u), -1, qx::cvt::context::e_database))); }

   template <class U>
   inline void updateLastInsertId(U & u)
   {
      if (getDataId() && getDataId()->getAutoIncrement() && this->hasFeature(QSqlDriver::LastInsertId))
      { getDataId()->fromVariant((& u), query().lastInsertId(), -1, qx::cvt::context::e_database); }
   }

   template <class U>
   inline bool validateInstance(U & u)
   {
      qx::QxInvalidValueX invalidValues = qx::validate(u, "");
      this->addInvalidValues(invalidValues);
      return (invalidValues.count() <= 0);
   }

protected:

   void dumpBoundValues() const;
   QSqlError updateError(const QString & sError);
   void timerStart(IxDao_Helper::timer_type timer);
   qint64 timerElapsed(IxDao_Helper::timer_type timer);
   void init(QSqlDatabase * pDatabase, const QString & sContext);
   void terminate();

};

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::IxDao_Timer : scoped timer to measure database elapsed times (using C++ RAII)
 */
struct IxDao_Timer
{

   IxDao_Helper * m_pDaoHelper;              //!< Pointer to dao helper class
   IxDao_Helper::timer_type m_eTimerType;    //!< Timer type (database or C++ action)

   IxDao_Timer(IxDao_Helper * pDaoHelper, IxDao_Helper::timer_type timer) : m_pDaoHelper(pDaoHelper), m_eTimerType(timer) { if (m_pDaoHelper) { m_pDaoHelper->timerStart(m_eTimerType); } }
   ~IxDao_Timer() { if (m_pDaoHelper) { m_pDaoHelper->timerElapsed(m_eTimerType); } }

};

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _IX_DAO_HELPER_H_
