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
#ifndef _QX_HTTP_RESPONSE_H_
#define _QX_HTTP_RESPONSE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxHttpResponse.h
 * \author Lionel Marty
 * \ingroup QxHttpServer
 * \brief HTTP response (headers + body)
 */

#include <QxHttpServer/QxHttpCookie.h>

#ifndef Q_MOC_RUN
#include <QxCommon/QxBool.h>
#endif // Q_MOC_RUN

namespace qx {

class QxHttpTransaction;

/*!
 * \ingroup QxHttpServer
 * \brief qx::QxHttpResponse : HTTP response (headers + body)
 */
class QX_DLL_EXPORT QxHttpResponse
{

private:

   struct QxHttpResponseImpl;
   std::unique_ptr<QxHttpResponseImpl> m_pImpl; //!< Private implementation idiom

public:

   QxHttpResponse(QxHttpTransaction * transaction);
   virtual ~QxHttpResponse();

   int & status();
   QByteArray & data();
   QByteArray statusDesc();
   QHash<QByteArray, QByteArray> & headers();
   QByteArray header(const QByteArray & key);
   QHash<QByteArray, QxHttpCookie> & cookies();
   QxHttpCookie cookie(const QByteArray & name);
   qx_bool writeChunked(const QByteArray & data);
   bool isChunked() const;

};

typedef std::shared_ptr<QxHttpResponse> QxHttpResponse_ptr;

} // namespace qx

typedef qx::QxHttpResponse qx_http_response;

#endif // _QX_HTTP_RESPONSE_H_
#endif // _QX_ENABLE_QT_NETWORK
