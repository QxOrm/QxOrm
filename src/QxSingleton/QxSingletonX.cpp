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
