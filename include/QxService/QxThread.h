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

#include <QxCommon/QxConfig.h> // Need to include this file for the 'moc' process

#if _QX_ENABLE_QT_NETWORK_DEPENDENCY
#ifndef _QX_SERVICE_THREAD_H_
#define _QX_SERVICE_THREAD_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxThread.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Thread to execute a transaction of QxService module
 */

#include <QtNetwork/qtcpsocket.h>

#include <QxService/QxTransaction.h>

namespace qx {
namespace service {

class QxThreadPool;

/*!
 * \ingroup QxService
 * \brief qx::service::QxThread : thread to execute a transaction of QxService module
 *
 * <a href="http://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
class QX_DLL_EXPORT QxThread : public QThread
{ Q_OBJECT

protected:

   int m_iSocketDescriptor;               //!< Socket descriptor to retrieve 'QTcpSocket'
   QxThreadPool * m_pThreadPool;          //!< Parent thread pool to set available
   QxTransaction_ptr m_pTransaction;      //!< Current service transaction
   bool m_bIsRunning;                     //!< Set this flag to 'false' to terminate thread
   QMutex m_mutex;                        //!< Mutex => 'QxThread' is thread-safe

public:

   QxThread(QxThreadPool * pool) : QThread(), m_iSocketDescriptor(0), m_pThreadPool(pool), m_bIsRunning(false) { qAssert(m_pThreadPool); }
   virtual ~QxThread() { clearData(); }

   bool isAvailable();
   void stop();
   void execute(int socketDescriptor);

protected:

   virtual void run();

   void clearData();
   void doProcess(QTcpSocket & socket);
   qx_bool readSocket(QTcpSocket & socket);
   qx_bool writeSocket(QTcpSocket & socket);

Q_SIGNALS:

   void error(const QString & err, qx::service::QxTransaction_ptr transaction);
   void transactionStarted(qx::service::QxTransaction_ptr transaction);
   void transactionFinished(qx::service::QxTransaction_ptr transaction);

};

} // namespace service
} // namespace qx

#endif // _QX_SERVICE_THREAD_H_
#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
