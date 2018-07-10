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

#include <QxService/QxServer.h>
#include <QxService/QxThreadPool.h>
#include <QxService/QxThread.h>
#include <QxService/QxTransaction.h>
#include <QxService/QxConnect.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace service {

#if (QT_VERSION >= 0x050000)
void QxServer::incomingConnection(qintptr socketDescriptor)
#else // (QT_VERSION >= 0x050000)
void QxServer::incomingConnection(int socketDescriptor)
#endif // (QT_VERSION >= 0x050000)
{
   QMutexLocker locker(& m_mutex);
   QxThread * pThread = getAvailable();
   if (! pThread) { if (m_pThreadPool) { m_pThreadPool->raiseError("[QxOrm] no service available : cannot accept incoming connection (increase thread count value)", QxTransaction_ptr()); } return; }
   pThread->execute(socketDescriptor);
}

QxThread * QxServer::getAvailable() const
{
   if (! m_pThreadPool) { qAssert(false); return NULL; }
   QxThread * pThread = m_pThreadPool->getAvailable();
   if (pThread) { return pThread; }
   qDebug("[QxOrm] qx::service::QxServer no service available : %s", "need to wait (try to increase thread count value)");

   int iCurrRetryCount = 0;
   int iMaxRetryCount = (QxConnect::getSingleton()->getMaxWait() / 50);
   while ((! pThread) && (iCurrRetryCount < iMaxRetryCount))
   {
      m_pThreadPool->sleepThread(50);
      pThread = m_pThreadPool->getAvailable();
      iCurrRetryCount++;
   }

   return pThread;
}

} // namespace service
} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
