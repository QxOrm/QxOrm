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

#ifdef _QX_ENABLE_QT_NETWORK

#include <QxPrecompiled.h>

#include <QtNetwork/qhostaddress.h>

#include <QxService/QxThreadPool.h>
#include <QxService/QxThread.h>
#include <QxService/QxConnect.h>

#include <QxHttpServer/QxHttpSessionManager.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace service {

bool QxThreadPool::isStopped() const { return m_bIsStopped; }

QxThread * QxThreadPool::getAvailable()
{
   if (m_bIsStopped) { return NULL; }
   QMutexLocker locker(& m_mutex);
   QxThread * p = (m_lstAvailable.isEmpty() ? NULL : m_lstAvailable.dequeue());
   if (p) { qAssert(p->isAvailable()); }
   return ((p && p->isAvailable()) ? p : NULL);
}

void QxThreadPool::setAvailable(QxThread * p)
{
   if (m_bIsStopped) { return; }
   QMutexLocker locker(& m_mutex);
   if ((p == NULL) || (! p->isAvailable())) { qAssert(false); return; }
   for (long l = 0; l < m_lstAvailable.count(); l++)
   { if (m_lstAvailable.at(l) == p) { qAssert(false); return; } }
   m_lstAvailable.enqueue(p);
}

void QxThreadPool::raiseError(const QString & err, QxTransaction_ptr transaction)
{
   qAssert(! err.isEmpty());
   if (! err.isEmpty()) { Q_EMIT error(err, transaction); }
}

void QxThreadPool::run()
{
   // To be sure that HTTP session manager event loop is running on this thread
   qx::QxHttpSessionManager::deleteSingleton();
   qx::QxHttpSessionManager::getSingleton();

   initServices();
   runServer();
   m_bIsStopped = true;
   clearServices();
   qx::QxHttpSessionManager::deleteSingleton();
}

void QxThreadPool::runServer()
{
   QxServer server(this);
   server.setMaxPendingConnections(QxConnect::getSingleton()->getThreadCount());
   quint16 serverPort = (quint16)(QxConnect::getSingleton()->getPort());
   if (! server.listen(QHostAddress::Any, serverPort))
   { raiseError(QString("[QxOrm] cannot run server : '") + server.errorString() + QString("'"), QxTransaction_ptr()); return; }
   Q_EMIT serverIsRunning(true, (& server));
   exec();
   Q_EMIT serverIsRunning(false, NULL);
}

void QxThreadPool::initServices()
{
   QMutexLocker locker(& m_mutex);
   qRegisterMetaType<qx::service::QxTransaction_ptr>("qx::service::QxTransaction_ptr");
   qRegisterMetaType<qx::service::QxTransaction_ptr>("QxTransaction_ptr");
   for (long l = 0; l < QxConnect::getSingleton()->getThreadCount(); l++)
   {
      QThread * pThread = new QThread();
      QxThread * pWorker = new QxThread(this, pThread);
      pWorker->moveToThread(pThread);
      QObject::connect(pWorker, SIGNAL(error(const QString &, qx::service::QxTransaction_ptr)), this, SIGNAL(error(const QString &, qx::service::QxTransaction_ptr)));
      QObject::connect(pWorker, SIGNAL(transactionStarted(qx::service::QxTransaction_ptr)), this, SIGNAL(transactionStarted(qx::service::QxTransaction_ptr)));
      QObject::connect(pWorker, SIGNAL(transactionFinished(qx::service::QxTransaction_ptr)), this, SIGNAL(transactionFinished(qx::service::QxTransaction_ptr)));
      QObject::connect(pWorker, SIGNAL(customRequestHandler(qx::service::QxTransaction_ptr)), this, SIGNAL(customRequestHandler(qx::service::QxTransaction_ptr)), Qt::DirectConnection);
      QObject::connect(pWorker, SIGNAL(finished()), pThread, SLOT(quit()));
      QObject::connect(pThread, SIGNAL(finished()), pThread, SLOT(deleteLater()));
      m_lstAllServices.append(pWorker);
      m_lstAvailable.enqueue(pWorker);
      pWorker->init();
      pThread->start();
   }
}

void QxThreadPool::clearServices()
{
   QMutexLocker locker(& m_mutex);
   for (long l = 0; l < m_lstAllServices.count(); l++) { m_lstAllServices.at(l)->stop(); }
   for (long l = 0; l < m_lstAllServices.count(); l++) { m_lstAllServices.at(l)->wait(); }
   for (long l = 0; l < m_lstAllServices.count(); l++) { delete m_lstAllServices.at(l); }
   m_lstAllServices.clear();
   m_lstAvailable.clear();
}

} // namespace service
} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
