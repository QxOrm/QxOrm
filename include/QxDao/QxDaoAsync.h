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

#ifndef _QX_DAO_ASYNC_H_
#define _QX_DAO_ASYNC_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxDaoAsync.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Helper class to execute SQL queries in another thread (asynchronous way) using qx::IxPersistable interface
 */

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include <QxPrecompiled.h> // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include <QtCore/qqueue.h>

#include <QtSql/qsqlerror.h>

#ifndef Q_MOC_RUN
#include <QxDao/IxPersistable.h>
#include <QxDao/QxSqlQuery.h>
#endif // Q_MOC_RUN

namespace qx {
namespace dao {
namespace detail {

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::QxDaoAsyncParams : all parameters for qx::QxDaoAsync class to execute queries
 */
struct QxDaoAsyncParams
{

   enum dao_action { dao_none, dao_count, dao_fetch_by_id, dao_fetch_all, dao_fetch_by_query, dao_insert, 
                     dao_update, dao_save, dao_delete_by_id, dao_delete_all, dao_delete_by_query, 
                     dao_destroy_by_id, dao_destroy_all, dao_destroy_by_query, dao_execute_query, dao_call_query };

   dao_action           daoAction;           //!< Action to execute into the thread (asynchronous way)
   QString              className;           //!< Classname parameter to execute action (must implement qx::IxPersistable interface)
   qx::QxSqlQuery       query;               //!< Query parameter to execute action
   QSqlDatabase *       pDatabase;           //!< Database parameter to execute action
   IxPersistable_ptr    pInstance;           //!< Current instance parameter to execute action
   IxCollection_ptr     pListOfInstances;    //!< List of instances fetched by query
   QStringList          listColumns;         //!< List of columns parameter to execute action
   QStringList          listRelations;       //!< List of relationships parameter to execute action
   QVariant             id;                  //!< Current instance id parameter to execute action
   long                 daoCount;            //!< Dao count value returned by qx::dao::count query

   QxDaoAsyncParams() : daoAction(dao_none), pDatabase(NULL), daoCount(0) { ; }
   ~QxDaoAsyncParams() { ; }

};

typedef qx_shared_ptr<QxDaoAsyncParams> QxDaoAsyncParams_ptr;

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::QxDaoAsyncRunner : class with a slot to execute queries in another thread
 */
class QX_DLL_EXPORT QxDaoAsyncRunner : public QObject
{

   Q_OBJECT

public:

   QxDaoAsyncRunner();
   virtual ~QxDaoAsyncRunner();

protected:

   QSqlError runQuery(qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams);

Q_SIGNALS:

   void queryFinished(const QSqlError & daoError, qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams);

public Q_SLOTS:

   void onQueryStarted(qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams);

};

} // namespace detail
} // namespace dao

/*!
 * \ingroup QxDao
 * \brief qx::QxDaoAsync : helper class to execute SQL queries in another thread (asynchronous way) using qx::IxPersistable interface
 *
 * To use <i>qx::QxDaoAsync</i> helper class :
 * 1- be careful to work only with classes implementing <i>qx::IxPersistable</i> interface ;
 * 2- create an instance of <i>qx::QxDaoAsync</i> type (for example, a property of a QWidget derived class) ;
 * 3- connect a SLOT to the <i>qx::QxDaoAsync::queryFinished()</i> SIGNAL (for example, a SLOT of a QWidget derived class) ;
 * 4- run a query using one of <i>qx::QxDaoAsync::asyncXXXX()</i> methods.
 *
 * For example, with a <i>MyWidget</i> class :
 * \code
class MyWidget : public QWidget
{
   Q_OBJECT
   //...
   qx::QxDaoAsync m_daoAsync;
   //...
Q_SLOTS:
   void onQueryFinished(const QSqlError & daoError, qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams);
   //...
};
 * \endcode
 * And here is the implementation of <i>MyWidget</i> class :
 * \code
MyWidget::MyWidget() : QObject()
{
   //...
   QObject::connect((& m_daoAsync), SIGNAL(queryFinished(const QSqlError &, qx::dao::detail::QxDaoAsyncParams_ptr)), this, SLOT(onQueryFinished(const QSqlError &, qx::dao::detail::QxDaoAsyncParams_ptr)));
   //...
}
void MyWidget::onQueryFinished(const QSqlError & daoError, qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams)
{
   if (! pDaoParams) { return; }
   qx::QxSqlQuery query = pDaoParams->query;
   if (! daoError.isValid()) { ; }
   // If the async query is associated to a simple object, just use 'pDaoParams->pInstance' method
   qx::IxPersistable_ptr ptr = pDaoParams->pInstance;
   // If the async query is associated to a list of objects, just use 'pDaoParams->pListOfInstances' method
   qx::IxCollection_ptr lst = pDaoParams->pListOfInstances;
   //...
}
 * \endcode
 */
class QX_DLL_EXPORT QxDaoAsync : public QThread
{

   Q_OBJECT

protected:

   QMutex m_mutex;                                       //!< Mutex => qx::QxDaoAsync is thread-safe
   qx::dao::detail::QxDaoAsyncParams_ptr m_pDaoParams;   //!< Parameters to execute query

public:

   QxDaoAsync();
   virtual ~QxDaoAsync();

   bool asyncCount(const QString & className, const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL);
   bool asyncFetchById(IxPersistable_ptr pToFetch, const QVariant & id = QVariant(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   bool asyncFetchAll(const QString & className, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   bool asyncFetchByQuery(const QString & className, const qx::QxSqlQuery & query, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   bool asyncInsert(IxPersistable_ptr pToInsert, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   bool asyncUpdate(IxPersistable_ptr pToUpdate, const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   bool asyncSave(IxPersistable_ptr pToSave, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   bool asyncDeleteById(IxPersistable_ptr pToDelete, const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL);
   bool asyncDeleteAll(const QString & className, QSqlDatabase * pDatabase = NULL);
   bool asyncDeleteByQuery(const QString & className, const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL);
   bool asyncDestroyById(IxPersistable_ptr pToDestroy, const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL);
   bool asyncDestroyAll(const QString & className, QSqlDatabase * pDatabase = NULL);
   bool asyncDestroyByQuery(const QString & className, const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL);
   bool asyncExecuteQuery(const QString & className, qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL);
   bool asyncCallQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL);

   bool isQueryRunning() const { return (m_pDaoParams.get() != NULL); }

protected:

   virtual void run();

   void startQuery();

Q_SIGNALS:

   void queryStarted(qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams);
   void queryFinished(const QSqlError & daoError, qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams);

private Q_SLOTS:

   void onQueryFinished(const QSqlError & daoError, qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams);

};

typedef qx_shared_ptr<QxDaoAsync> QxDaoAsync_ptr;

} // namespace qx

#endif // _QX_DAO_ASYNC_H_
