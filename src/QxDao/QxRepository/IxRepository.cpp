/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
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

} // namespace qx
