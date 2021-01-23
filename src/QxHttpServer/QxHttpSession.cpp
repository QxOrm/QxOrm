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

#include <QtCore/quuid.h>

#include <QxHttpServer/QxHttpSession.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

struct Q_DECL_HIDDEN QxHttpSession::QxHttpSessionImpl
{

   QMutex m_mutex;                           //!< Mutex => 'QxHttpSession' is thread-safe
   QHash<QByteArray, QVariant> m_storage;    //!< Session storage based on key/values
   QByteArray m_id;                          //!< Session unique identifier
   QDateTime m_lastAccess;                   //!< Session last access date-time to check if expired

   QxHttpSessionImpl() { m_id = QUuid::createUuid().toString().toLatin1(); m_lastAccess = QDateTime::currentDateTime(); }
   ~QxHttpSessionImpl() { ; }

};

QxHttpSession::QxHttpSession() : m_pImpl(new QxHttpSessionImpl()) { ; }

QxHttpSession::~QxHttpSession() { ; }

QByteArray QxHttpSession::id()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_id;
}

QDateTime QxHttpSession::lastAccess()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_lastAccess;
}

void QxHttpSession::lastAccess(const QDateTime & dt)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_lastAccess = dt;
}

QVariant QxHttpSession::get(const QByteArray & key)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_storage.value(key);
}

void QxHttpSession::set(const QByteArray & key, const QVariant & value)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_storage.insert(key, value);
}

QHash<QByteArray, QVariant> QxHttpSession::getAll()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_storage;
}

void QxHttpSession::remove(const QByteArray & key)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_storage.remove(key);
}

void QxHttpSession::clear()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_storage.clear();
}

} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
