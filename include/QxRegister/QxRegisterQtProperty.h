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

#ifndef _QX_REGISTER_QT_META_PROPERTY_H_
#define _QX_REGISTER_QT_META_PROPERTY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxRegisterQtProperty.h
 * \author Lionel Marty
 * \ingroup QxRegister
 * \brief Register automatically Qt meta-property defined with Q_PROPERTY() macro into QxOrm context
 */

#include <boost/static_assert.hpp>

#include <QtCore/qmetaobject.h>
#include <QtCore/qmetatype.h>

#include <QxRegister/QxClass.h>

#include <QxTraits/qt_meta_object.h>

#define QX_REGISTER_ALL_QT_PROPERTIES(className, propertyId) \
namespace qx { \
template <> void register_class(QxClass< className > & t) \
{ qx::register_all_qt_properties< className >(t, propertyId); } }

namespace qx {

template <typename T>
void register_all_qt_properties(QxClass<T> & t, const QString & sPropertyId)
{
   BOOST_STATIC_ASSERT(qx::trait::qt_meta_object<T>::is_valid);

   const QMetaObject * pMetaObject = qx::trait::qt_meta_object<T>::get();
   int iIndexId = (sPropertyId.isEmpty() ? -2 : (pMetaObject ? pMetaObject->indexOfProperty(qPrintable(sPropertyId)) : -1));
   if (! pMetaObject || (iIndexId == -1)) { qAssert(false); return; }

   for (int i = pMetaObject->propertyOffset(); i < pMetaObject->propertyCount(); i++)
   {
      QMetaProperty prop = pMetaObject->property(i);
      if (i == iIndexId) { t.id(sPropertyId, 0); }
      else { t.data(prop.name(), 0); }
   }
}

} // namespace qx

#endif // _QX_REGISTER_QT_META_PROPERTY_H_
