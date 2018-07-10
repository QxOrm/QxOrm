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

#include <QxService/QxServer.h>
#include <QxService/QxThreadPool.h>
#include <QxService/QxThread.h>
#include <QxService/QxTransaction.h>
#include <QxService/QxConnect.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace service {

void QxServer::incomingConnection(int socketDescriptor)
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

#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
