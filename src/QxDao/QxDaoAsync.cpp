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

#include <QxDao/QxDaoAsync.h>
#include <QxDao/QxSqlError.h>

#include <QxFactory/QxFactoryX.h>

#include <QxRegister/QxClassX.h>

#include <QxMemLeak/mem_leak.h>

#define QX_DAO_ASYNC_QUERY_ALREADY_RUNNING   qDebug("[QxOrm] qx::QxDaoAsync : '%s'", "another query is already running");

namespace qx {

QxDaoAsync::QxDaoAsync() : QThread() { ; }

QxDaoAsync::~QxDaoAsync()
{
   if (! isRunning()) { return; }
   qDebug("[QxOrm] qx::QxDaoAsync thread is running : %s", "quit and wait");
   quit(); wait();
}

void QxDaoAsync::run()
{
   qx::dao::detail::QxDaoAsyncRunner daoRunner;
   qRegisterMetaType<QSqlError>("QSqlError");
   qRegisterMetaType<qx::dao::detail::QxDaoAsyncParams_ptr>("qx::dao::detail::QxDaoAsyncParams_ptr");
   QObject::connect(this, SIGNAL(queryStarted(qx::dao::detail::QxDaoAsyncParams_ptr)), (& daoRunner), SLOT(onQueryStarted(qx::dao::detail::QxDaoAsyncParams_ptr)));
   QObject::connect((& daoRunner), SIGNAL(queryFinished(const QSqlError &, qx::dao::detail::QxDaoAsyncParams_ptr)), this, SLOT(onQueryFinished(const QSqlError &, qx::dao::detail::QxDaoAsyncParams_ptr)));
   if (m_pDaoParams && (m_pDaoParams->daoAction != qx::dao::detail::QxDaoAsyncParams::dao_none)) { daoRunner.onQueryStarted(m_pDaoParams); }
   exec();
}

void QxDaoAsync::startQuery()
{
   if (! m_pDaoParams) { qAssert(false); return; }
   if (isRunning()) { Q_EMIT queryStarted(m_pDaoParams); }
   else { start(); }
}

void QxDaoAsync::onQueryFinished(const QSqlError & daoError, qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams)
{
   m_pDaoParams.reset();
   Q_EMIT queryFinished(daoError, pDaoParams);
}

bool QxDaoAsync::asyncCount(const QString & className, const qx::QxSqlQuery & query /* = qx::QxSqlQuery() */, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_count;
   m_pDaoParams->className = className;
   m_pDaoParams->query = query;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncFetchById(IxPersistable_ptr pToFetch, const QVariant & id /* = QVariant() */, const QStringList & columns /* = QStringList() */, const QStringList & relation /* = QStringList() */, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_fetch_by_id;
   m_pDaoParams->pInstance = pToFetch;
   m_pDaoParams->id = id;
   m_pDaoParams->listColumns = columns;
   m_pDaoParams->listRelations = relation;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncFetchAll(const QString & className, const QStringList & columns /* = QStringList() */, const QStringList & relation /* = QStringList() */, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_fetch_all;
   m_pDaoParams->className = className;
   m_pDaoParams->listColumns = columns;
   m_pDaoParams->listRelations = relation;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncFetchByQuery(const QString & className, const qx::QxSqlQuery & query, const QStringList & columns /* = QStringList() */, const QStringList & relation /* = QStringList() */, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_fetch_by_query;
   m_pDaoParams->className = className;
   m_pDaoParams->query = query;
   m_pDaoParams->listColumns = columns;
   m_pDaoParams->listRelations = relation;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncInsert(IxPersistable_ptr pToInsert, const QStringList & relation /* = QStringList() */, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_insert;
   m_pDaoParams->pInstance = pToInsert;
   m_pDaoParams->listRelations = relation;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncUpdate(IxPersistable_ptr pToUpdate, const qx::QxSqlQuery & query /* = qx::QxSqlQuery() */, const QStringList & columns /* = QStringList() */, const QStringList & relation /* = QStringList() */, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_update;
   m_pDaoParams->pInstance = pToUpdate;
   m_pDaoParams->query = query;
   m_pDaoParams->listColumns = columns;
   m_pDaoParams->listRelations = relation;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncSave(IxPersistable_ptr pToSave, const QStringList & relation /* = QStringList() */, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_save;
   m_pDaoParams->pInstance = pToSave;
   m_pDaoParams->listRelations = relation;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncDeleteById(IxPersistable_ptr pToDelete, const QVariant & id /* = QVariant() */, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_delete_by_id;
   m_pDaoParams->pInstance = pToDelete;
   m_pDaoParams->id = id;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncDeleteAll(const QString & className, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_delete_all;
   m_pDaoParams->className = className;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncDeleteByQuery(const QString & className, const qx::QxSqlQuery & query, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_delete_by_query;
   m_pDaoParams->className = className;
   m_pDaoParams->query = query;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncDestroyById(IxPersistable_ptr pToDestroy, const QVariant & id /* = QVariant() */, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_destroy_by_id;
   m_pDaoParams->pInstance = pToDestroy;
   m_pDaoParams->id = id;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncDestroyAll(const QString & className, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_destroy_all;
   m_pDaoParams->className = className;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncDestroyByQuery(const QString & className, const qx::QxSqlQuery & query, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_destroy_by_query;
   m_pDaoParams->className = className;
   m_pDaoParams->query = query;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncExecuteQuery(const QString & className, qx::QxSqlQuery & query, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_execute_query;
   m_pDaoParams->className = className;
   m_pDaoParams->query = query;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

bool QxDaoAsync::asyncCallQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase /* = NULL */)
{
   QMutexLocker locker(& m_mutex);
   if (m_pDaoParams) { QX_DAO_ASYNC_QUERY_ALREADY_RUNNING; return false; }
   m_pDaoParams.reset(new qx::dao::detail::QxDaoAsyncParams());
   m_pDaoParams->daoAction = qx::dao::detail::QxDaoAsyncParams::dao_call_query;
   m_pDaoParams->query = query;
   m_pDaoParams->pDatabase = pDatabase;
   startQuery();
   return true;
}

namespace dao {
namespace detail {

QxDaoAsyncRunner::QxDaoAsyncRunner() : QObject() { ; }

QxDaoAsyncRunner::~QxDaoAsyncRunner() { ; }

void QxDaoAsyncRunner::onQueryStarted(qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams)
{
   QSqlError daoError = this->runQuery(pDaoParams);
   Q_EMIT queryFinished(daoError, pDaoParams);
}

QSqlError QxDaoAsyncRunner::runQuery(qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams)
{
   if (! pDaoParams)
   { qAssert(false); return QSqlError("[QxOrm] qx::QxDaoAsync : 'null dao parameters'", "", QSqlError::UnknownError); }

   QSqlError daoError;
   QSqlDatabase * pDatabase(NULL);
   QSqlDatabase db; QString dbKey;

   try
   {
      if (! pDaoParams->className.isEmpty() && ! pDaoParams->pInstance)
      { pDaoParams->pInstance.reset(static_cast<qx::IxPersistable *>(qx::create_void_ptr(pDaoParams->className))); }
      if (! pDaoParams->pInstance && (pDaoParams->daoAction != qx::dao::detail::QxDaoAsyncParams::dao_call_query))
      { qAssert(false); return QSqlError("[QxOrm] qx::QxDaoAsync : 'null instance implementing qx::IxPersistable interface'", "", QSqlError::UnknownError); }
      qx::IxPersistable_ptr pInstance = pDaoParams->pInstance;

      if ((pDaoParams->daoAction == qx::dao::detail::QxDaoAsyncParams::dao_fetch_all) || 
          (pDaoParams->daoAction == qx::dao::detail::QxDaoAsyncParams::dao_fetch_by_query) || 
          (pDaoParams->daoAction == qx::dao::detail::QxDaoAsyncParams::dao_execute_query))
      { pDaoParams->pListOfInstances = pInstance->qxNewPersistableCollection(); }

      if (pDaoParams->pDatabase != NULL)
      { dbKey = QUuid::createUuid().toString(); db = QSqlDatabase::cloneDatabase((* pDaoParams->pDatabase), dbKey); }
      pDatabase = (pDaoParams->pDatabase ? (& db) : NULL);

      switch (pDaoParams->daoAction)
      {
         case qx::dao::detail::QxDaoAsyncParams::dao_count:             daoError = pInstance->qxCount(pDaoParams->daoCount, pDaoParams->query, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_fetch_by_id:       daoError = pInstance->qxFetchById(pDaoParams->id, pDaoParams->listColumns, pDaoParams->listRelations, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_fetch_all:         daoError = pInstance->qxFetchAll((* pDaoParams->pListOfInstances), pDaoParams->listColumns, pDaoParams->listRelations, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_fetch_by_query:    daoError = pInstance->qxFetchByQuery(pDaoParams->query, (* pDaoParams->pListOfInstances), pDaoParams->listColumns, pDaoParams->listRelations, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_insert:            daoError = pInstance->qxInsert(pDaoParams->listRelations, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_update:            daoError = pInstance->qxUpdate(pDaoParams->query, pDaoParams->listColumns, pDaoParams->listRelations, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_save:              daoError = pInstance->qxSave(pDaoParams->listRelations, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_delete_by_id:      daoError = pInstance->qxDeleteById(pDaoParams->id, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_delete_all:        daoError = pInstance->qxDeleteAll(pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_delete_by_query:   daoError = pInstance->qxDeleteByQuery(pDaoParams->query, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_destroy_by_id:     daoError = pInstance->qxDestroyById(pDaoParams->id, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_destroy_all:       daoError = pInstance->qxDestroyAll(pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_destroy_by_query:  daoError = pInstance->qxDestroyByQuery(pDaoParams->query, pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_execute_query:     daoError = pInstance->qxExecuteQuery(pDaoParams->query, (* pDaoParams->pListOfInstances), pDatabase); break;
         case qx::dao::detail::QxDaoAsyncParams::dao_call_query:        daoError = qx::dao::call_query(pDaoParams->query, pDatabase); break;
         default:                                                       qAssert(false); break;
      }
   }
   catch (const qx::dao::sql_error & sqlErr) { daoError = sqlErr.get(); }
   catch (const std::exception & err) { daoError = QSqlError(err.what(), "", QSqlError::UnknownError); }
   catch (...) { daoError = QSqlError("[QxOrm] qx::QxDaoAsync : 'unknown error executing query'", "", QSqlError::UnknownError); }

   if (pDatabase) { pDatabase->close(); }
   if (pDatabase && ! dbKey.isEmpty()) { QSqlDatabase::removeDatabase(dbKey); }
   return daoError;
}

} // namespace detail
} // namespace dao
} // namespace qx
