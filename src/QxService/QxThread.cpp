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

#if _QX_ENABLE_QT_NETWORK_DEPENDENCY

#include <QxService/QxThread.h>
#include <QxService/QxThreadPool.h>
#include <QxService/QxTools.h>
#include <QxService/QxConnect.h>

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

void QxThread::execute(int socketDescriptor)
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
   catch (const std::exception & e) { m_pTransaction->setMessageReturn(qx_bool(0, e.what())); }
   catch (...) { m_pTransaction->setMessageReturn(qx_bool(0, "unknown error")); }
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
   if (! m_pTransaction) { return qx_bool(0, "empty service transaction"); }

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

#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
