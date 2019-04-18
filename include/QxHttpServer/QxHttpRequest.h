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
#ifndef _QX_HTTP_REQUEST_H_
#define _QX_HTTP_REQUEST_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxHttpRequest.h
 * \author Lionel Marty
 * \ingroup QxHttpServer
 * \brief HTTP request (headers + body)
 */

#include <QtCore/qurl.h>

#include <QxHttpServer/QxHttpCookie.h>

namespace qx {

class QxHttpTransaction;

/*!
 * \ingroup QxHttpServer
 * \brief qx::QxHttpRequest : HTTP request (headers + body)
 */
class QX_DLL_EXPORT QxHttpRequest
{

private:

   struct QxHttpRequestImpl;
   std::unique_ptr<QxHttpRequestImpl> m_pImpl; //!< Private implementation idiom

public:

   QxHttpRequest(QxHttpTransaction * transaction);
   virtual ~QxHttpRequest();

   QUrl & url();
   QString & command();
   QString & version();
   QByteArray & data();
   QHash<QByteArray, QByteArray> & headers();
   QByteArray header(const QByteArray & key);
   QHash<QByteArray, QxHttpCookie> & cookies();
   QxHttpCookie cookie(const QByteArray & name);
   QHash<QString, QVariant> & dispatchParams();
   QHash<QString, QString> & params();
   QString param(const QString & key);
   QString & sourceAddress();
   long & sourcePort();
   QString guid() const;

};

typedef std::shared_ptr<QxHttpRequest> QxHttpRequest_ptr;

} // namespace qx

typedef qx::QxHttpRequest qx_http_request;

#endif // _QX_HTTP_REQUEST_H_
#endif // _QX_ENABLE_QT_NETWORK
