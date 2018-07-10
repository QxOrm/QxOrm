/****************************************************************************
**
** https://www.qxorm.com/
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

#ifndef _QX_ANY_H_
#define _QX_ANY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxAny.h
 * \author Lionel Marty
 * \ingroup QxCommon
 * \brief qx::any : basic implementation of boost::any (written by Kevlin Henney) when boost dependency is not available
 */

#ifndef _QX_NO_RTTI
#include <typeinfo>
#define QX_TYPE_ID(T) typeid(T)
#else // _QX_NO_RTTI
#include <QxTraits/get_class_name.h>
#include <QxTraits/get_class_name_primitive.h>
#define QX_TYPE_ID(T) std::string(qx::trait::get_class_name< T >::get())
#endif // _QX_NO_RTTI

#ifndef Q_OS_WIN
#if (__GNUC__ >= 4)
#define QX_ANY_FORCE_HIDDEN_VISIBILITY __attribute__ ((visibility("hidden"))) // To avoid a GCC warning : 'qx::any::holder<T>' declared with greater visibility than the type of its field 'qx::any::holder<T>::held' [-Wattributes]
#endif // (__GNUC__ >= 4)
#endif // Q_OS_WIN

#ifndef QX_ANY_FORCE_HIDDEN_VISIBILITY
#define QX_ANY_FORCE_HIDDEN_VISIBILITY /* Nothing */
#endif // QX_ANY_FORCE_HIDDEN_VISIBILITY

namespace qx {

class any;
template <typename ValueType> ValueType * any_cast(any *);
template <typename ValueType> ValueType * unsafe_any_cast(any *);

class any
{

   template <typename ValueType> friend ValueType * qx::any_cast(any *);
   template <typename ValueType> friend ValueType * qx::unsafe_any_cast(any *);

public:

#ifndef _QX_NO_RTTI
   typedef const std::type_info & type_check;
#else // _QX_NO_RTTI
   typedef std::string type_check;
#endif // _QX_NO_RTTI

   any() : content(NULL) { ; }
   any(const any & other) : content(other.content ? other.content->clone() : NULL) { ; }
   ~any() { if (content) { delete content; } }

   template <typename ValueType>
   any(const ValueType & value) : content(new holder<typename std::remove_cv<typename std::decay<const ValueType>::type>::type>(value)) { ; }

   any & swap(any & other) { std::swap(content, other.content); return (* this); }

   template <typename ValueType>
   any & operator=(const ValueType & other) { any(other).swap(* this); return (* this); }

   any & operator=(any other) { any(other).swap(* this); return (* this); }
   bool empty() const { return (! content); }
   void clear() { any().swap(* this); }
   type_check type() const { return (content ? content->type() : QX_TYPE_ID(void)); }

private:

   struct placeholder
   {
      virtual ~placeholder() { ; }
      virtual type_check type() const = 0;
      virtual placeholder * clone() const = 0;
   };

   template <typename ValueType>
   struct QX_ANY_FORCE_HIDDEN_VISIBILITY holder : public placeholder
   {
      holder(const ValueType & value) : held(value) { ; }
      virtual type_check type() const { return QX_TYPE_ID(ValueType); }
      virtual placeholder * clone() const { return new holder(held); }
      ValueType held;

      private:
      holder & operator=(const holder &);
   };

   placeholder * content;

};

inline void swap(any & lhs, any & other) { lhs.swap(other); }

struct bad_any_cast : public std::exception
{ virtual const char * what() const throw() { return "qx::bad_any_cast : failed conversion using qx::any_cast"; } };

template <typename ValueType>
ValueType * any_cast(any * operand)
{ return ((operand && (operand->type() == QX_TYPE_ID(ValueType))) ? (& static_cast<any::holder<typename std::remove_cv<ValueType>::type> *>(operand->content)->held) : NULL); }

template <typename ValueType>
const ValueType * any_cast(const any * operand)
{ return any_cast<ValueType>(const_cast<any *>(operand)); }

template <typename ValueType>
ValueType any_cast(any & operand)
{
   typedef typename std::remove_reference<ValueType>::type nonref;
   nonref * result = any_cast<nonref>(& operand);
   if (! result) { throw qx::bad_any_cast(); }
   return static_cast<ValueType>(* result);
}

template <typename ValueType>
ValueType any_cast(const any & operand)
{
   typedef typename std::remove_reference<ValueType>::type nonref;
   return any_cast<const nonref &>(const_cast<any &>(operand));
}

template <typename ValueType>
ValueType * unsafe_any_cast(any * operand)
{ return (& static_cast<any::holder<ValueType> *>(operand->content)->held); }

template <typename ValueType>
const ValueType * unsafe_any_cast(const any * operand)
{ return unsafe_any_cast<ValueType>(const_cast<any *>(operand)); }

} // namespace qx

#endif // _QX_ANY_H_
