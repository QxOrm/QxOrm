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

#ifdef _QX_ENABLE_QT_NETWORK

#include <QxPrecompiled.h>

#include <QxService/QxThread.h>
#include <QxService/QxThreadPool.h>
#include <QxService/QxTools.h>
#include <QxService/QxConnect.h>

#include <QxCommon/QxException.h>
#include <QxCommon/QxExceptionCode.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace service {

bool QxThread::isAvailable()
{
   QMutexLocker locker(& m_mutex);
   return ((m_pTransaction.get() == NULL) && (m_iSocketDescriptor == 0));
}

void QxThread::stop()
{
   QMutexLocker locker(& m_mutex);
   m_bIsRunning = false;
}

void QxThread::execute(QX_TYPE_SOCKET_DESC socketDescriptor)
{
   QMutexLocker locker(& m_mutex);
   if (m_iSocketDescriptor != 0) { return; }
   m_iSocketDescriptor = socketDescriptor;
}

void QxThread::run()
{
   m_bIsRunning = true;
   while (m_bIsRunning)
   {
      while (m_iSocketDescriptor == 0) { if (! m_bIsRunning) { return; } msleep(5); }
      QTcpSocket socket;
      doProcess(socket);
      socket.disconnectFromHost();
      if (socket.state() != QAbstractSocket::UnconnectedState)
      { socket.waitForDisconnected(QxConnect::getSingleton()->getMaxWait()); }
      clearData();
      if (m_pThreadPool) { m_pThreadPool->setAvailable(this); }
   }
}

void QxThread::clearData()
{
   QMutexLocker locker(& m_mutex);
   m_pTransaction.reset();
   m_iSocketDescriptor = 0;
}

void QxThread::doProcess(QTcpSocket & socket)
{
   if (! socket.setSocketDescriptor(m_iSocketDescriptor))
   { Q_EMIT error("[QxOrm] invalid socket descriptor : cannot start transaction", QxTransaction_ptr()); return; }

   qx_bool bReadOk = readSocket(socket);
   if (! bReadOk) { Q_EMIT error(QString("[QxOrm] unable to read request from socket : '") + bReadOk.getDesc() + QString("'"), QxTransaction_ptr()); return; }
   if (! m_bIsRunning) { return; }

   Q_EMIT transactionStarted(m_pTransaction);
   try { m_pTransaction->executeServer(); }
   catch (const qx::exception & x) { qx_bool xb = x.toQxBool(); m_pTransaction->setMessageReturn(xb); }
   catch (const std::exception & e) { m_pTransaction->setMessageReturn(qx_bool(QX_ERROR_UNKNOWN, e.what())); }
   catch (...) { m_pTransaction->setMessageReturn(qx_bool(QX_ERROR_UNKNOWN, "unknown error")); }
   if (! m_bIsRunning) { return; }

   qx_bool bWriteOk = writeSocket(socket);
   if (! bWriteOk) { Q_EMIT error(QString("[QxOrm] unable to write reply to socket : '") + bWriteOk.getDesc() + QString("'"), m_pTransaction); }
   Q_EMIT transactionFinished(m_pTransaction);
}

qx_bool QxThread::readSocket(QTcpSocket & socket)
{
   quint32 uiTransactionSize = 0;
   m_pTransaction.reset(new QxTransaction());
   qx_bool bReadOk = QxTools::readSocket(socket, (* m_pTransaction), uiTransactionSize);
   if (! bReadOk) { m_pTransaction.reset(); return bReadOk; }
   m_pTransaction->setInputTransactionSize(uiTransactionSize);
   m_pTransaction->setTransactionRequestReceived(QDateTime::currentDateTime());
   return bReadOk;
}

qx_bool QxThread::writeSocket(QTcpSocket & socket)
{
   if (! m_pTransaction) { return qx_bool(QX_ERROR_SERVICE_NOT_SPECIFIED, "empty service transaction"); }

   quint32 uiTransactionSize = 0;
   IxParameter_ptr pInputBackup = m_pTransaction->getInputParameter();
   m_pTransaction->setInputParameter(IxParameter_ptr());
   m_pTransaction->setTransactionReplySent(QDateTime::currentDateTime());
   qx_bool bWriteOk = QxTools::writeSocket(socket, (* m_pTransaction), uiTransactionSize);
   m_pTransaction->setInputParameter(pInputBackup);
   m_pTransaction->setOutputTransactionSize(uiTransactionSize);
   return bWriteOk;
}

} // namespace service
} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
