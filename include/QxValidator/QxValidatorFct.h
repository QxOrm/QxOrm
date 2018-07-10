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

#ifndef _QX_VALIDATOR_FUNCTION_H_
#define _QX_VALIDATOR_FUNCTION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxValidatorFct.h
 * \author Lionel Marty
 * \ingroup QxValidator
 * \brief Implementation of qx::validate<T>() function (validator engine)
 */

#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include <QxValidator/IxValidatorX.h>
#include <QxValidator/QxInvalidValueX.h>

#include <QxRegister/QxClass.h>

#include <QxTraits/is_container.h>
#include <QxTraits/is_smart_ptr.h>
#include <QxTraits/is_qx_registered.h>

namespace qx {
template <class T>
QxInvalidValueX validate(T & t, const QString & group);
} // namespace qx

namespace qx {
namespace validator {
namespace detail {

template <class T>
struct QxValidator_Helper_Generic
{

   static inline qx::QxInvalidValueX validate(T & t, const QString & group)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);

      qx::QxInvalidValueX invalidValues;
      qx::IxClass * pClass = qx::QxClass<T>::getSingleton();
      if (! pClass) { qAssert(false); return invalidValues; }
      qx::IxValidatorX * pAllValidator = pClass->getAllValidator();
      if (! pAllValidator) { return invalidValues; }
      invalidValues.setCurrentPath(pClass->getName());
      invalidValues.insert(pAllValidator->validate((& t), group));
      return invalidValues;
   }

};

template <class T>
struct QxValidator_Helper_Container
{

   static inline qx::QxInvalidValueX validate(T & t, const QString & group)
   {
      qx::QxInvalidValueX invalidValues; long lIndex = 0;
      for (typename T::iterator it = t.begin(); it != t.end(); ++it)
      {
         invalidValues.setCurrentPath("[" + QString::number(lIndex) + "]");
         invalidValues.insert(validateItem((* it), group));
         lIndex++;
      }
      return invalidValues;
   }

private:

   template <typename U>
   static inline qx::QxInvalidValueX validateItem(U & item, const QString & group)
   { return validateItem_Helper<U, boost::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::validate(item, group); }

   template <typename U, bool bIsPointer /* = true */>
   struct validateItem_Helper
   {
      static inline qx::QxInvalidValueX validate(U & item, const QString & group)
      { return (item ? qx::validator::detail::QxValidator_Helper_Container<T>::validateItem((* item), group) : qx::QxInvalidValueX()); }
   };

   template <typename U1, typename U2>
   struct validateItem_Helper<std::pair<U1, U2>, false>
   {
      static inline qx::QxInvalidValueX validate(std::pair<U1, U2> & item, const QString & group)
      { return qx::validator::detail::QxValidator_Helper_Container<T>::validateItem(item.second, group); }
   };

   template <typename U1, typename U2>
   struct validateItem_Helper<const std::pair<U1, U2>, false>
   {
      static inline qx::QxInvalidValueX validate(const std::pair<U1, U2> & item, const QString & group)
      { return qx::validator::detail::QxValidator_Helper_Container<T>::validateItem(item.second, group); }
   };

   template <typename U1, typename U2>
   struct validateItem_Helper<QPair<U1, U2>, false>
   {
      static inline qx::QxInvalidValueX validate(QPair<U1, U2> & item, const QString & group)
      { return qx::validator::detail::QxValidator_Helper_Container<T>::validateItem(item.second, group); }
   };

   template <typename U1, typename U2>
   struct validateItem_Helper<const QPair<U1, U2>, false>
   {
      static inline qx::QxInvalidValueX validate(const QPair<U1, U2> & item, const QString & group)
      { return qx::validator::detail::QxValidator_Helper_Container<T>::validateItem(item.second, group); }
   };

   template <typename U>
   struct validateItem_Helper<U, false>
   { static qx::QxInvalidValueX validate(U & item, const QString & group) { return qx::validate(item, group); } };

};

template <class T>
struct QxValidator_Helper_Ptr
{

   static inline qx::QxInvalidValueX validate(T & t, const QString & group)
   { return (t ? qx::validate((* t), group) : qx::QxInvalidValueX()); }

};

template <class T>
struct QxValidator_Helper
{

   static inline qx::QxInvalidValueX validate(T & t, const QString & group)
   {
      typedef typename boost::mpl::if_c< boost::is_pointer<T>::value, qx::validator::detail::QxValidator_Helper_Ptr<T>, qx::validator::detail::QxValidator_Helper_Generic<T> >::type type_validator_1;
      typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<T>::value, qx::validator::detail::QxValidator_Helper_Ptr<T>, type_validator_1 >::type type_validator_2;
      typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::validator::detail::QxValidator_Helper_Container<T>, type_validator_2 >::type type_validator_3;

      return type_validator_3::validate(t, group);
   }

};

} // namespace detail
} // namespace validator
} // namespace qx

namespace qx {

template <class T>
QxInvalidValueX validate(T & t, const QString & group)
{ return qx::validator::detail::QxValidator_Helper<T>::validate(t, group); }

template <class T>
QxInvalidValueX validate(T & t)
{ return qx::validator::detail::QxValidator_Helper<T>::validate(t, ""); }

template <class T>
QxInvalidValueX validate(T & t, const QStringList & groups)
{
   QxInvalidValueX invalidValues;
   for (long l = 0; l < groups.count(); l++)
   { invalidValues.insert(qx::validate(t, groups.at(l))); }
   return invalidValues;
}

} // namespace qx

#endif // _QX_VALIDATOR_FUNCTION_H_
