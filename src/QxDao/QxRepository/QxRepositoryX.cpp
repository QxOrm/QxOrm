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

#include <QxDao/QxRepository/QxRepositoryX.h>

#include <QxMemLeak/mem_leak.h>

QX_DLL_EXPORT_QX_SINGLETON_CPP(qx::QxRepositoryX)

namespace qx {

void QxRepositoryX::registerRepository(const QString & sKey, IxRepository * pRepository)
{
   QMutexLocker locker(& m_oMutexRepositoryX);
   qAssert(! sKey.isEmpty() && ! m_mapRepositoryX.contains(sKey));
   if (! pRepository || sKey.isEmpty() || m_mapRepositoryX.contains(sKey)) { return; }
   m_mapRepositoryX.insert(sKey, pRepository);
}

void QxRepositoryX::unregisterRepository(const QString & sKey)
{
   if (m_bUnregisterAllRepository) { return; }
   QMutexLocker locker(& m_oMutexRepositoryX);
   IxRepository * pRepository = (m_mapRepositoryX.contains(sKey) ? m_mapRepositoryX.value(sKey) : NULL);
   if (pRepository) { delete pRepository; pRepository = NULL; }
   m_mapRepositoryX.remove(sKey);
}

void QxRepositoryX::unregisterAllRepository()
{
   m_bUnregisterAllRepository = true;
   QMutexLocker locker(& m_oMutexRepositoryX);
   QHashIterator<QString, IxRepository *> itr(m_mapRepositoryX);
   while (itr.hasNext()) { itr.next(); delete itr.value(); }
   m_mapRepositoryX.clear();
   m_bUnregisterAllRepository = false;
}

IxRepository * QxRepositoryX::get(const QString & sKey)
{
   if (! QxRepositoryX::getSingleton()->m_mapRepositoryX.contains(sKey)) { return NULL; }
   return QxRepositoryX::getSingleton()->m_mapRepositoryX.value(sKey);
}

} // namespace qx
