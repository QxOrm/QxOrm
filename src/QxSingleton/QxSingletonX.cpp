/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#include "../../include/QxPrecompiled.h"

#include <stdlib.h>

#include <QtCore/qcoreapplication.h>

#include "../../include/QxSingleton/QxSingletonX.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {

QHash<QString, IxSingleton *> QxSingletonX::m_mapSingletonX;
QMutex QxSingletonX::m_oMutexSingletonX;
bool QxSingletonX::m_bOnClearSingletonX = false;

QxSingletonX::QxSingletonX() : QxSingleton<QxSingletonX>("qx::QxSingletonX")
{
   int iResult = std::atexit(& QxSingletonX::deleteAllSingleton);
   qAssert(iResult == 0); Q_UNUSED(iResult);
}

bool QxSingletonX::addSingleton(const QString & sKey, IxSingleton * pSingleton)
{
   QMutexLocker locker(& m_oMutexSingletonX);
   bool bExist = m_mapSingletonX.contains(sKey);
   qAssert(! bExist && ! sKey.isEmpty());

   if (! pSingleton || bExist || sKey.isEmpty()) { return false; }
   m_mapSingletonX.insert(sKey, pSingleton);

   return true;
}

bool QxSingletonX::removeSingleton(const QString & sKey)
{
   if (m_bOnClearSingletonX)
      return false;

   QMutexLocker locker(& m_oMutexSingletonX);
   qAssert(m_mapSingletonX.contains(sKey));
   bool bRemoveOk = (m_mapSingletonX.remove(sKey) > 0);

   return bRemoveOk;
}

void QxSingletonX::deleteAllSingleton()
{
   QMutexLocker locker(QCoreApplication::instance() ? (& m_oMutexSingletonX) : NULL);
   m_bOnClearSingletonX = true;

   _foreach(IxSingleton * pSingleton, m_mapSingletonX)
   {
      if (pSingleton && (pSingleton != QxSingletonX::getSingleton()))
         pSingleton->deleteInstance();
   }

   QxSingletonX::deleteSingleton();
   m_mapSingletonX.clear();
   m_bOnClearSingletonX = false;
}

} // namespace qx
