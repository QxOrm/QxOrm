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

#ifndef _QX_SINGLETON_X_H_
#define _QX_SINGLETON_X_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtCore/qhash.h>

#include <QxSingleton/QxSingleton.h>

#include <QxCollection/QxForeach.h>

namespace qx {

class QX_DLL_EXPORT QxSingletonX : public QxSingleton<QxSingletonX>
{

   friend class QxSingleton<QxSingletonX>;
   friend class IxSingleton;

private:

   static QHash<QString, IxSingleton *> m_mapSingletonX; // Collection of all 'IxSingleton' pointer
   static QMutex m_oMutexSingletonX;                     // Mutex -> 'QxSingletonX' is thread-safe
   static bool m_bOnClearSingletonX;                     // Clear collection of 'IxSingleton' in event

private:

   QxSingletonX();
   virtual ~QxSingletonX() { ; }

   static bool addSingleton(const QString & sKey, IxSingleton * pSingleton);
   static bool removeSingleton(const QString & sKey);
   static void deleteAllSingleton();

};

} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::QxSingletonX)

#endif // _QX_SINGLETON_X_H_
