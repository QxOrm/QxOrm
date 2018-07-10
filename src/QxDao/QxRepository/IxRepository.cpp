/****************************************************************************
**
** http://www.qxorm.com/
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

#include <QxPrecompiled.h>

#include <QxDao/QxRepository/IxRepository.h>
#include <QxDao/QxRepository/QxRepositoryX.h>

#include <QxDao/QxSession.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxRepository::IxRepository(bool bRegister, const QString & sKey) : m_bRegister(bRegister), m_sKeyRepository(sKey), m_pSession(NULL)
{
   if (m_bRegister && ! m_sKeyRepository.isEmpty())
   { QxRepositoryX::getSingleton()->registerRepository(m_sKeyRepository, this); }
}

IxRepository::IxRepository(bool bRegister, const QString & sKey, const QSqlDatabase & database) : m_bRegister(bRegister), m_sKeyRepository(sKey), m_database(database), m_pSession(NULL)
{
   if (m_bRegister && ! m_sKeyRepository.isEmpty())
   { QxRepositoryX::getSingleton()->registerRepository(m_sKeyRepository, this); }
}

IxRepository::IxRepository(bool bRegister, const QString & sKey, QxSession * pSession) : m_bRegister(bRegister), m_sKeyRepository(sKey), m_pSession(pSession)
{
   if (m_bRegister && ! m_sKeyRepository.isEmpty())
   { QxRepositoryX::getSingleton()->registerRepository(m_sKeyRepository, this); }
}

IxRepository::~IxRepository()
{
   if (m_bRegister && ! m_sKeyRepository.isEmpty() && ! QxRepositoryX::isSingletonNull())
   { QxRepositoryX::getSingleton()->unregisterRepository(m_sKeyRepository); }
}

QSqlDatabase * IxRepository::database()
{
   if (m_pSession) { return (m_pSession->database()->isValid() ? m_pSession->database() : NULL); }
   return (m_database.isValid() ? (& m_database) : NULL);
}

QxSession * IxRepository::session() const
{
   return m_pSession;
}

qx::IxCollection_ptr IxRepository::_fetchAll(const QString & repositoryKey, const QStringList & columns /* = QStringList() */, const QStringList & relation /* = QStringList() */)
{
   IxRepository * pRepository = QxRepositoryX::get(repositoryKey);
   if (! pRepository) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxRepository::_fetchAll() : 'invalid repository key, unable to get repository pointer'", "", QSqlError::UnknownError)); }
   qx::IxCollection_ptr lst = pRepository->_newCollection();
   if (! lst) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxRepository::_fetchAll() : 'unable to create a new collection from repository'", "", QSqlError::UnknownError)); }
   QSqlError daoError = pRepository->_fetchAll(lst.get(), columns, relation);
   if (daoError.isValid()) { throw qx::dao::sql_error(daoError); }
   return lst;
}

qx::IxCollection_ptr IxRepository::_fetchByQuery(const QString & repositoryKey, const qx::QxSqlQuery & query, const QStringList & columns /* = QStringList() */, const QStringList & relation /* = QStringList() */)
{
   IxRepository * pRepository = QxRepositoryX::get(repositoryKey);
   if (! pRepository) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxRepository::_fetchByQuery() : 'invalid repository key, unable to get repository pointer'", "", QSqlError::UnknownError)); }
   qx::IxCollection_ptr lst = pRepository->_newCollection();
   if (! lst) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxRepository::_fetchByQuery() : 'unable to create a new collection from repository'", "", QSqlError::UnknownError)); }
   QSqlError daoError = pRepository->_fetchByQuery(query, lst.get(), columns, relation);
   if (daoError.isValid()) { throw qx::dao::sql_error(daoError); }
   return lst;
}

} // namespace qx
