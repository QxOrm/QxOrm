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

#ifndef _QX_SINGLETON_H_
#define _QX_SINGLETON_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtCore/qmutex.h>
#include <QtCore/qcoreapplication.h>

#include "../../include/QxSingleton/IxSingleton.h"

namespace qx {

template <class T>
class QxSingleton : public IxSingleton
{

private:

   static T *     m_pSingleton;        // Singleton -> only 1 instance allowed
   static QMutex  m_oMutexSingleton;   // Mutex -> 'QxSingleton' is thread-safe

protected:

   QxSingleton(const QString & sKey) : IxSingleton(sKey) { ; }
   virtual ~QxSingleton() { ; }

public:

   static T * getSingleton();
   static void deleteSingleton();

protected:

   static bool isSingletonNull() { return (m_pSingleton == NULL); }

   virtual void deleteInstance() { QxSingleton<T>::deleteSingleton(); }

};

} // namespace qx

#include "../../inl/QxSingleton/QxSingleton.inl"

#endif // _QX_SINGLETON_H_
