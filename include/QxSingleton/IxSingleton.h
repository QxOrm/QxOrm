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

#ifndef _IX_SINGLETON_H_
#define _IX_SINGLETON_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxSingleton.h
 * \author Lionel Marty
 * \ingroup QxSingleton
 * \brief Common interface for all singleton of QxOrm library
 */

#include <boost/noncopyable.hpp>

namespace qx {

class QxSingletonX;

/*!
 * \ingroup QxSingleton
 * \brief qx::IxSingleton : common interface for all singleton of QxOrm library
 */
class QX_DLL_EXPORT IxSingleton : private boost::noncopyable
{

   friend class QxSingletonX;

protected:

   QString m_sKeySingleton;   //!< Singleton key used by 'QxSingletonX' container

protected:

   IxSingleton(const QString & sKey);
   virtual ~IxSingleton();

   virtual void deleteInstance() = 0;

   static void initQxSingletonX();

};

} // namespace qx

#endif // _IX_SINGLETON_H_
