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
   virtual qx::any _at(long index) const = 0;

   template <typename T>
   T _get(long index) const
   { return qx::any_cast_dynamic<T>::get(_at(index)); }

};

typedef std::shared_ptr<qx::IxCollection> IxCollection_ptr;

} // namespace qx

QX_REGISTER_CLASS_NAME(IxCollection)

#endif // _IX_COLLECTION_H_
