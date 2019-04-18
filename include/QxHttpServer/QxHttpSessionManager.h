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
#ifndef _QX_HTTP_SESSION_MANAGER_H_
#define _QX_HTTP_SESSION_MANAGER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxHttpSessionManager.h
 * \author Lionel Marty
 * \ingroup QxHttpServer
 * \brief HTTP session manager (https://www.qxorm.com/qxorm_en/manual.html#manual_998)
 */

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include <QxPrecompiled.h> // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#ifndef Q_MOC_RUN
#include <QxSingleton/QxSingleton.h>
#endif // Q_MOC_RUN

#include <QxHttpServer/QxHttpSession.h>
#include <QxHttpServer/QxHttpRequest.h>
#include <QxHttpServer/QxHttpResponse.h>

namespace qx {

/*!
 * \ingroup QxHttpServer
 * \brief qx::QxHttpSessionManager : HTTP session manager (https://www.qxorm.com/qxorm_en/manual.html#manual_998)
 */
class QX_DLL_EXPORT QxHttpSessionManager : public QObject, public qx::QxSingleton<QxHttpSessionManager>
{

   Q_OBJECT
   friend class qx::QxSingleton<QxHttpSessionManager>;

private:

   struct QxHttpSessionManagerImpl;
   std::unique_ptr<QxHttpSessionManagerImpl> m_pImpl; //!< Private implementation idiom

   QxHttpSessionManager();
   virtual ~QxHttpSessionManager();

public:

   static qx::QxHttpSession_ptr getSession(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QByteArray & cookieName = QByteArray("qx_session_id"), bool autoCreateSession = true);
   static qx::QxHttpSession_ptr createSession(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QByteArray & cookieName = QByteArray("qx_session_id"));
   static void removeSession(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QByteArray & cookieName = QByteArray("qx_session_id"));

private Q_SLOTS:

   void onCheckSessionTimeOut();

private:

   static void deleteSession(qx::QxHttpSession * p);

};

} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::QxHttpSessionManager)

#endif // _QX_HTTP_SESSION_MANAGER_H_
#endif // _QX_ENABLE_QT_NETWORK
