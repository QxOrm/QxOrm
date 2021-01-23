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

#include <QtCore/qmutex.h>
#include <QtCore/qtimer.h>

#include <QxHttpServer/QxHttpSessionManager.h>

#include <QxService/QxConnect.h>

#include <QxMemLeak/mem_leak.h>

QX_DLL_EXPORT_QX_SINGLETON_CPP(qx::QxHttpSessionManager)

namespace qx {

struct Q_DECL_HIDDEN QxHttpSessionManager::QxHttpSessionManagerImpl
{

   QMutex m_mutex;                                       //!< Mutex => 'QxHttpSessionManager' is thread-safe
   QTimer m_timer;                                       //!< Timer to remove automatically expired sessions
   QHash<QByteArray, qx::QxHttpSession_ptr> m_sessions;  //!< List of sessions

   QxHttpSessionManagerImpl() { ; }
   ~QxHttpSessionManagerImpl() { ; }

   QByteArray getSessionId(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QByteArray & cookieName)
   {
      QByteArray id = response.cookie(cookieName).value;
      if (id.isEmpty()) { id = request.cookie(cookieName).value; }
      if ((! id.isEmpty()) && (! m_sessions.contains(id))) { id = QByteArray(); }
      return id;
   }

   qx::QxHttpSession_ptr getSession(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QByteArray & cookieName, bool autoCreateSession)
   {
      do
      {
         QMutexLocker locker(& m_mutex);
         QByteArray id = getSessionId(request, response, cookieName);
         if (id.isEmpty() || (! m_sessions.contains(id))) { break; }
         qx::QxHttpSession_ptr session = m_sessions.value(id);
         if (session) { session->lastAccess(QDateTime::currentDateTime()); }
         return session;
      }
      while (false);
      if (autoCreateSession) { return createSession(request, response, cookieName); }
      return qx::QxHttpSession_ptr();
   }

   qx::QxHttpSession_ptr createSession(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QByteArray & cookieName)
   {
      removeSession(request, response, cookieName);
      QMutexLocker locker(& m_mutex);
      qx::QxHttpSession_ptr session(new qx::QxHttpSession(), (& QxHttpSessionManager::deleteSession));
      QByteArray id = session->id();
      m_sessions.insert(id, session);

      qx::QxHttpCookie cookie;
      cookie.name = cookieName;
      cookie.value = id;
      response.cookies().insert(cookieName, cookie);
      return session;
   }

   void removeSession(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QByteArray & cookieName)
   {
      QMutexLocker locker(& m_mutex);
      QByteArray id = getSessionId(request, response, cookieName);
      if (id.isEmpty() || (! m_sessions.contains(id))) { return; }
      m_sessions.remove(id);
   }

};

QxHttpSessionManager::QxHttpSessionManager() : QObject(), qx::QxSingleton<QxHttpSessionManager>("qx::QxHttpSessionManager"), m_pImpl(new QxHttpSessionManagerImpl())
{
   QObject::connect((& m_pImpl->m_timer), SIGNAL(timeout()), this, SLOT(onCheckSessionTimeOut()));
   m_pImpl->m_timer.start(60000);
}

QxHttpSessionManager::~QxHttpSessionManager() { m_pImpl->m_timer.stop(); }

void QxHttpSessionManager::deleteSession(qx::QxHttpSession * p) { delete p; }

qx::QxHttpSession_ptr QxHttpSessionManager::getSession(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QByteArray & cookieName /* = QByteArray("qx_session_id") */, bool autoCreateSession /* = true */)
{
   return QxHttpSessionManager::getSingleton()->m_pImpl->getSession(request, response, cookieName, autoCreateSession);
}

qx::QxHttpSession_ptr QxHttpSessionManager::createSession(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QByteArray & cookieName /* = QByteArray("qx_session_id") */)
{
   return QxHttpSessionManager::getSingleton()->m_pImpl->createSession(request, response, cookieName);
}

void QxHttpSessionManager::removeSession(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QByteArray & cookieName /* = QByteArray("qx_session_id") */)
{
   QxHttpSessionManager::getSingleton()->m_pImpl->removeSession(request, response, cookieName);
}

void QxHttpSessionManager::onCheckSessionTimeOut()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   qlonglong lTimeOut = qx::service::QxConnect::getSingleton()->getSessionTimeOut();
   QMutableHashIterator<QByteArray, qx::QxHttpSession_ptr> itr(m_pImpl->m_sessions);
   QDateTime dt = QDateTime::currentDateTime();

   while (itr.hasNext())
   {
      itr.next();
      qx::QxHttpSession_ptr session = itr.value();
      if (! session) { itr.remove(); continue; }
      QDateTime lastAccess = session->lastAccess();
      if (! lastAccess.isValid()) { qAssert(false); itr.remove(); continue; }
      if (lastAccess.addMSecs(lTimeOut) < dt) { itr.remove(); continue; }
   }
}

} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
