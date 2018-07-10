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

#ifndef _IX_FACTORY_H_
#define _IX_FACTORY_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/noncopyable.hpp>
#include <boost/any.hpp>

namespace qx {

class QX_DLL_EXPORT IxFactory : private boost::noncopyable
{

protected:

   QString m_sKeyFactory;  // Factory key used by 'QxFactoryX'

public:

   IxFactory(const QString & sKey);
   virtual ~IxFactory();

   virtual boost::any createObject() const = 0;

};

} // namespace qx

#endif // _IX_FACTORY_H_
