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
#ifndef _QX_HTTP_SESSION_H_
#define _QX_HTTP_SESSION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxHttpSession.h
 * \author Lionel Marty
 * \ingroup QxHttpServer
 * \brief HTTP session (https://www.qxorm.com/qxorm_en/manual.html#manual_998)
 */

namespace qx {

class QxHttpSessionManager;

/*!
 * \ingroup QxHttpServer
 * \brief qx::QxHttpSession : HTTP session (https://www.qxorm.com/qxorm_en/manual.html#manual_998)
 */
class QX_DLL_EXPORT QxHttpSession
{

   friend class qx::QxHttpSessionManager;

private:

   struct QxHttpSessionImpl;
   std::unique_ptr<QxHttpSessionImpl> m_pImpl; //!< Private implementation idiom

#if (QT_VERSION < 0x050000)
public: // Some older compilers don't support std::shared_ptr with private custom deleter, but for Qt5 we assume that all compilers should support it
#endif // (QT_VERSION < 0x050000)

   QxHttpSession();
   ~QxHttpSession();

public:

   QByteArray id();
   QDateTime lastAccess();
   void lastAccess(const QDateTime & dt);
   QVariant get(const QByteArray & key);
   void set(const QByteArray & key, const QVariant & value);
   QHash<QByteArray, QVariant> getAll();
   void remove(const QByteArray & key);
   void clear();

};

typedef std::shared_ptr<QxHttpSession> QxHttpSession_ptr;

} // namespace qx

typedef qx::QxHttpSession qx_http_session;
typedef qx::QxHttpSession_ptr qx_http_session_ptr;

#endif // _QX_HTTP_SESSION_H_
#endif // _QX_ENABLE_QT_NETWORK
