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

#ifndef _IX_COLLECTION_H_
#define _IX_COLLECTION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxCollection.h
 * \author Lionel Marty
 * \ingroup QxCollection
 * \brief Common interface for all QxOrm containers qx::QxCollection<Key, Value>
 */

#include <boost/any.hpp>

#include <QxTraits/get_class_name.h>

#include <QxCommon/QxAnyCastDynamic.h>

namespace qx {

/*!
 * \ingroup QxCollection
 * \brief qx::IxCollection : common interface for all QxOrm containers qx::QxCollection<Key, Value>
 */
class QX_DLL_EXPORT IxCollection
{

public:

   IxCollection() { ; }
   virtual ~IxCollection() = 0;

   virtual long _count() const = 0;
   virtual void _clear() = 0;
   virtual bool _remove(long index) = 0;
   virtual boost::any _at(long index) const = 0;

   template <typename T>
   T _get(long index) const
   { return qx::any_cast_dynamic<T>::get(_at(index)); }

};

typedef boost::shared_ptr<qx::IxCollection> IxCollection_ptr;

} // namespace qx

QX_REGISTER_CLASS_NAME(IxCollection)

#endif // _IX_COLLECTION_H_
