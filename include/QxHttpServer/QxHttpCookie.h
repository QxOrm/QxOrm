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
#ifndef _QX_HTTP_COOKIE_H_
#define _QX_HTTP_COOKIE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxHttpCookie.h
 * \author Lionel Marty
 * \ingroup QxHttpServer
 * \brief HTTP cookie (https://www.qxorm.com/qxorm_en/manual.html#manual_999)
 */

namespace qx {

/*!
 * \ingroup QxHttpServer
 * \brief qx::QxHttpCookie : HTTP cookie (https://www.qxorm.com/qxorm_en/manual.html#manual_999)
 */
struct QX_DLL_EXPORT QxHttpCookie
{

   QByteArray name;     //!< Cookie name
   QByteArray value;    //!< Cookie value
   QByteArray domain;   //!< Cookie domain : specifies those hosts to which the cookie will be sent, if not specified defaults to the host portion of the current document location (but not including subdomains)
   QByteArray path;     //!< Cookie path : indicates a URL path that must exist in the requested resource before sending the Cookie header
   qlonglong maxAge;    //!< Cookie max-age : number of seconds until the cookie expires (a zero or negative number will expire the cookie immediately)
   bool secure;         //!< Cookie secure : a secure cookie will only be sent to the server when a request is made using SSL and the HTTPS protocol
   bool httpOnly;       //!< Cookie http-only : HTTP-only cookies aren't accessible via JavaScript through the Document.cookie property, the XMLHttpRequest and Request APIs to mitigate attacks against cross-site scripting

   QxHttpCookie();
   QxHttpCookie(const QByteArray & name_, const QByteArray & value_, const QByteArray & domain_ = QByteArray(), const QByteArray & path_ = QByteArray("/"), qlonglong maxAge_ = 0, bool secure_ = false, bool httpOnly_ = false);
   ~QxHttpCookie();

   QByteArray toString() const;
   static QHash<QByteArray, QxHttpCookie> parse(const QByteArray & cookies);

};

} // namespace qx

#endif // _QX_HTTP_COOKIE_H_
#endif // _QX_ENABLE_QT_NETWORK
