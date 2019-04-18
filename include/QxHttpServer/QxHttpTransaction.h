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

#ifdef Q_MOC_RUN
#include <QxCommon/QxConfig.h> // Need to include this file for the 'moc' process
#endif // Q_MOC_RUN

#ifdef _QX_ENABLE_QT_NETWORK
#ifndef _QX_HTTP_TRANSACTION_H_
#define _QX_HTTP_TRANSACTION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxHttpTransaction.h
 * \author Lionel Marty
 * \ingroup QxHttpServer
 * \brief HTTP transaction (contains request from client and reply from server)
 */

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include <QxPrecompiled.h> // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include <QxService/QxTransaction.h>

#include <QxHttpServer/QxHttpRequest.h>
#include <QxHttpServer/QxHttpResponse.h>

namespace qx {

/*!
 * \ingroup QxHttpServer
 * \brief qx::QxHttpTransaction : HTTP transaction (contains request from client and reply from server)
 */
class QX_DLL_EXPORT QxHttpTransaction : public qx::service::QxTransaction
{

   Q_OBJECT

private:

   struct QxHttpTransactionImpl;
   std::unique_ptr<QxHttpTransactionImpl> m_pImpl; //!< Private implementation idiom

public:

   QxHttpTransaction();
   virtual ~QxHttpTransaction();

   qx::QxHttpRequest & request();
   qx::QxHttpResponse & response();
   qx_bool writeChunked(const QByteArray & data);

   virtual void clear();
   virtual void executeServer();
   virtual qx_bool writeSocketServer(QTcpSocket & socket);
   virtual qx_bool readSocketServer(QTcpSocket & socket);

};

typedef std::shared_ptr<QxHttpTransaction> QxHttpTransaction_ptr;

} // namespace qx

typedef qx::QxHttpTransaction qx_http_transaction;

#endif // _QX_HTTP_TRANSACTION_H_
#endif // _QX_ENABLE_QT_NETWORK
