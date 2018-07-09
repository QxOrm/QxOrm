/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
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

#include "../../include/QxFactory/IxFactory.h"

#include "../../include/QxTraits/get_base_class.h"
#include "../../include/QxTraits/get_class_name.h"
#include "../../include/QxTraits/get_primary_key.h"

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
