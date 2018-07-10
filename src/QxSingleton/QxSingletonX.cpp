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

#include <stdlib.h>

#include <QtCore/qcoreapplication.h>

#include <QxSingleton/QxSingletonX.h>

#include <QxMemLeak/mem_leak.h>

#ifdef _QX_STATIC_BUILD
#undef _QX_USE_QX_SINGLETON_X
#define _QX_USE_QX_SINGLETON_X 0
#endif // _QX_STATIC_BUILD

QX_DLL_EXPORT_QX_SINGLETON_CPP(qx::QxSingletonX)

namespace qx {

QHash<QString, IxSingleton *> QxSingletonX::m_mapSingletonX;
QMutex QxSingletonX::m_oMutexSingletonX;
bool QxSingletonX::m_bOnClearSingletonX = false;

QxSingletonX::QxSingletonX() : QxSingleton<QxSingletonX>("qx::QxSingletonX")
{
#if _QX_USE_QX_SINGLETON_X
   int iResult = std::atexit(& QxSingletonX::deleteAllSingleton);
   qAssert(iResult == 0); Q_UNUSED(iResult);
#endif // _QX_USE_QX_SINGLETON_X
}

bool QxSingletonX::addSingleton(const QString & sKey, IxSingleton * pSingleton)
{
#if _QX_USE_QX_SINGLETON_X
   QMutexLocker locker(QCoreApplication::instance() ? (& m_oMutexSingletonX) : NULL);
   bool bExist = m_mapSingletonX.contains(sKey);
   qAssert(! bExist && ! sKey.isEmpty());

   if (! pSingleton || bExist || sKey.isEmpty()) { return false; }
   m_mapSingletonX.insert(sKey, pSingleton);

   return true;
#else // _QX_USE_QX_SINGLETON_X
   Q_UNUSED(sKey); Q_UNUSED(pSingleton);
   return false;
#endif // _QX_USE_QX_SINGLETON_X
}

bool QxSingletonX::removeSingleton(const QString & sKey)
{
#if _QX_USE_QX_SINGLETON_X
   if (m_bOnClearSingletonX)
      return false;

   QMutexLocker locker(QCoreApplication::instance() ? (& m_oMutexSingletonX) : NULL);
   qAssert(m_mapSingletonX.contains(sKey));
   bool bRemoveOk = (m_mapSingletonX.remove(sKey) > 0);

   return bRemoveOk;
#else // _QX_USE_QX_SINGLETON_X
   Q_UNUSED(sKey);
   return false;
#endif // _QX_USE_QX_SINGLETON_X
}

void QxSingletonX::deleteAllSingleton()
{
#if _QX_USE_QX_SINGLETON_X
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
#endif // _QX_USE_QX_SINGLETON_X
}

} // namespace qx
