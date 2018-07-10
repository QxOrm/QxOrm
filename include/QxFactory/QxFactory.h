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

#ifndef _QX_FACTORY_H_
#define _QX_FACTORY_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_abstract.hpp>

#include <QxFactory/IxFactory.h>

#include <QxTraits/get_base_class.h>
#include <QxTraits/get_class_name.h>
#include <QxTraits/get_primary_key.h>

#define QX_STR_CANNOT_INSTANTIATE_ABSTRACT_CLASS "[QxOrm] qx::QxFactory<T> ---> cannot instantiate abstract class '%s'"

namespace qx {

template <class T>
class QxClass;

template <class T>
class QxFactory : public IxFactory
{

public:

   QxFactory(const QString & sKey) : IxFactory(sKey) { ; }
   virtual ~QxFactory() { ; }

   virtual boost::any createObject() const
   { QxClass<T>::getSingleton(); return qxCreateInstance<boost::is_abstract<T>::value, 0>::create(); }

private:

   template <bool bIsAbstract /* = false */, int dummy>
   struct qxCreateInstance
   { static inline boost::any create() { boost::shared_ptr<T> ptr; ptr.reset(new T()); return boost::any(ptr); } };

   template <int dummy>
   struct qxCreateInstance<true, dummy>
   { static inline boost::any create() { qDebug(QX_STR_CANNOT_INSTANTIATE_ABSTRACT_CLASS, qx::trait::get_class_name<T>::get()); return boost::any(); } };

};

} // namespace qx

#include "../../inl/QxFactory/QxFactory.inl"

#endif // _QX_FACTORY_H_
