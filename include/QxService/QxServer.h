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

#if _QX_ENABLE_QT_NETWORK_DEPENDENCY
#ifndef _QX_SERVICE_SERVER_H_
#define _QX_SERVICE_SERVER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxServer.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Server side to manage a thread pool of incoming connections (new request from client)
 */

#include <QtNetwork/qtcpserver.h>

namespace qx {
namespace service {

class QxThreadPool;
class QxThread;

/*!
 * \ingroup QxService
 * \brief qx::service::QxServer : server side to manage a thread pool of incoming connections (new request from client)
 *
 * <a href="http://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
class QX_DLL_EXPORT QxServer : public QTcpServer
{

protected:

   QxThreadPool * m_pThreadPool;       //!< Parent thread pool to prevent from incoming connection
   QMutex m_mutex;                     //!< Mutex => 'QxServer' is thread-safe

public:

   QxServer(QxThreadPool * pool) : QTcpServer(), m_pThreadPool(pool) { qAssert(m_pThreadPool); }
   virtual ~QxServer() { ; }

protected:

   virtual void incomingConnection(int socketDescriptor);

   QxThread * getAvailable() const;

};

} // namespace service
} // namespace qx

#endif // _QX_SERVICE_SERVER_H_
#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
