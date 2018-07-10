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

/* -- We replaced these static class members by static class methods to avoid (with some compilers) the 'static initialization order fiasco' --
QHash<QString, IxSingleton *> QxSingletonX::m_mapSingletonX; // replaced by 'getMapSingletonX()'
QMutex QxSingletonX::m_oMutexSingletonX; // replaced by 'getMutexSingletonX()'
bool QxSingletonX::m_bOnClearSingletonX = false; // replaced by 'getOnClearSingletonX()'
*/

QxSingletonX::QxSingletonX() : QxSingleton<QxSingletonX>("qx::QxSingletonX")
{
#if _QX_USE_QX_SINGLETON_X
   int iResult = std::atexit(& QxSingletonX::deleteAllSingleton); Q_UNUSED(iResult);
   QString sAssertMsg = QString("cannot register 'qx::QxSingletonX::deleteAllSingleton()' function at exit program (using 'std::atexit')"); Q_UNUSED(sAssertMsg);
   qAssertMsg((iResult == 0), "[QxOrm] qx::QxSingletonX() constructor", qPrintable(sAssertMsg));
#endif // _QX_USE_QX_SINGLETON_X
}

QHash<QString, IxSingleton *> & QxSingletonX::getMapSingletonX()
{
   // There is a 'very small' memory leak here : this is to avoid (with some compilers) the 'static initialization order fiasco'
   // More details here : https://isocpp.org/wiki/faq/ctors#static-init-order
   static QHash<QString, IxSingleton *> * p = new QHash<QString, IxSingleton *>();
   return (* p);
}

QMutex * QxSingletonX::getMutexSingletonX()
{
   // There is a 'very small' memory leak here : this is to avoid (with some compilers) the 'static initialization order fiasco'
   // More details here : https://isocpp.org/wiki/faq/ctors#static-init-order
   static QMutex * p = new QMutex();
   return p;
}

bool & QxSingletonX::getOnClearSingletonX()
{
   // There is a 'very small' memory leak here : this is to avoid (with some compilers) the 'static initialization order fiasco'
   // More details here : https://isocpp.org/wiki/faq/ctors#static-init-order
   static bool * p = new bool(false);
   return (* p);
}

bool QxSingletonX::addSingleton(const QString & sKey, IxSingleton * pSingleton)
{
#if _QX_USE_QX_SINGLETON_X
#ifdef _QX_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::QxSingletonX::addSingleton() : '%s'", qPrintable(sKey));
#endif // _QX_TRACE_CONSTRUCTOR_DESTRUCTOR
   QMutex * pMutex = (QCoreApplication::instance() ? getMutexSingletonX() : NULL);
   QMutexLocker locker(pMutex);
   bool bExist = getMapSingletonX().contains(sKey);
   QString sAssertMsg = QString("singleton key '%1' already exists or is empty").arg(sKey); Q_UNUSED(sAssertMsg);
   qAssertMsg((! bExist && ! sKey.isEmpty()), "[QxOrm] qx::QxSingletonX::addSingleton()", qPrintable(sAssertMsg));
   if (! pSingleton || bExist || sKey.isEmpty()) { return false; }
   getMapSingletonX().insert(sKey, pSingleton);
   return true;
#else // _QX_USE_QX_SINGLETON_X
   Q_UNUSED(sKey); Q_UNUSED(pSingleton);
   return false;
#endif // _QX_USE_QX_SINGLETON_X
}

bool QxSingletonX::removeSingleton(const QString & sKey)
{
#if _QX_USE_QX_SINGLETON_X
   bool & bOnClearSingletonX = getOnClearSingletonX();
   if (bOnClearSingletonX) { return false; }
#ifdef _QX_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::QxSingletonX::removeSingleton() : '%s'", qPrintable(sKey));
#endif // _QX_TRACE_CONSTRUCTOR_DESTRUCTOR
   QMutex * pMutex = (QCoreApplication::instance() ? getMutexSingletonX() : NULL);
   QMutexLocker locker(pMutex);
   QString sAssertMsg = QString("singleton key '%1' doesn't exist in the singleton manager").arg(sKey); Q_UNUSED(sAssertMsg);
   qAssertMsg((getMapSingletonX().contains(sKey)), "[QxOrm] qx::QxSingletonX::removeSingleton()", qPrintable(sAssertMsg));
   bool bRemoveOk = (getMapSingletonX().remove(sKey) > 0);
   return bRemoveOk;
#else // _QX_USE_QX_SINGLETON_X
   Q_UNUSED(sKey);
   return false;
#endif // _QX_USE_QX_SINGLETON_X
}

void QxSingletonX::deleteAllSingleton()
{
#if _QX_USE_QX_SINGLETON_X
#ifdef _QX_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::QxSingletonX : %s", "execute deleteAllSingleton() function");
#endif // _QX_TRACE_CONSTRUCTOR_DESTRUCTOR
   QMutex * pMutex = (QCoreApplication::instance() ? getMutexSingletonX() : NULL);
   QMutexLocker locker(pMutex);
   bool & bOnClearSingletonX = getOnClearSingletonX();
   bOnClearSingletonX = true;

   QHash<QString, IxSingleton *> & mapSingletonX = getMapSingletonX();
   QHashIterator<QString, IxSingleton *> itr(mapSingletonX);
   while (itr.hasNext())
   {
      itr.next(); IxSingleton * pSingleton = itr.value();
      if (pSingleton && (pSingleton != QxSingletonX::getSingleton()))
         pSingleton->deleteInstance();
   }

   QxSingletonX::deleteSingleton();
   mapSingletonX.clear();
   bOnClearSingletonX = false;
#endif // _QX_USE_QX_SINGLETON_X
}

} // namespace qx
