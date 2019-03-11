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

#include <QxPrecompiled.h>

#include <QxHttpServer/QxHttpCookie.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QxHttpCookie::QxHttpCookie() : path("/"), maxAge(0), secure(false), httpOnly(false) { ; }

QxHttpCookie::QxHttpCookie(const QByteArray & name_, const QByteArray & value_, const QByteArray & domain_ /* = QByteArray() */, const QByteArray & path_ /* = QByteArray("/") */, qlonglong maxAge_ /* = 0 */, bool secure_ /* = false */, bool httpOnly_ /* = false */) : name(name_), value(value_), domain(domain_), path(path_), maxAge(maxAge_), secure(secure_), httpOnly(httpOnly_) { ; }

QxHttpCookie::~QxHttpCookie() { ; }

QByteArray QxHttpCookie::toString() const
{
   QByteArray result = name;
   if (! value.isEmpty()) { result += "=" + value; }
   if (! domain.isEmpty()) { result += "; Domain=" + domain; }
   if (! path.isEmpty()) { result += "; Path=" + path; }
   if (maxAge != 0) { result += "; Max-Age=" + QByteArray::number(maxAge); }
   if (secure) { result += "; Secure"; }
   if (httpOnly) { result += "; HttpOnly"; }
   return result;
}

QHash<QByteArray, QxHttpCookie> QxHttpCookie::parse(const QByteArray & cookies)
{
   QHash<QByteArray, QxHttpCookie> result;
   QList<QByteArray> lst = cookies.split(';');
   Q_FOREACH(QByteArray data, lst)
   {
      QByteArray name, value;
      int pos = data.indexOf('=');
      if (pos <= 0) { name = data.trimmed(); }
      else { name = data.left(pos).trimmed(); value = data.mid(pos + 1).trimmed(); }
      if (name.isEmpty()) { continue; }

      QxHttpCookie cookie(name, value);
      result.insert(cookie.name, cookie);
   }
   return result;
}

} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
