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

#ifndef _QX_IS_SMART_PTR_BASE_OF_H_
#define _QX_IS_SMART_PTR_BASE_OF_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_smart_ptr_base_of.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_smart_ptr_base_of<B, D>::value : return true if B and D are smart-pointers of boost, Qt or QxOrm libraries and if (*B) is a base class of (*D), otherwise return false
 */

#include <QxTraits/is_smart_ptr.h>

#define qx_smart_ptr_base_of_test_0() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr(b, d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_1() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_boost_scoped_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_2() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_boost_shared_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_3() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_boost_weak_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_4() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_boost_intrusive_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_5() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_qt_shared_data_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_6() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_qt_shared_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_7() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_qt_weak_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_8() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_qx_dao_ptr), d)) == sizeof(char))

#define qx_smart_ptr_base_of_test_9()  (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_std_unique_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_10() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_std_shared_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_11() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_std_weak_ptr), d)) == sizeof(char))

#define qx_smart_ptr_base_of_all_test() \
qx_smart_ptr_base_of_test_1() || qx_smart_ptr_base_of_test_2() || qx_smart_ptr_base_of_test_3() || \
qx_smart_ptr_base_of_test_4() || qx_smart_ptr_base_of_test_5() || qx_smart_ptr_base_of_test_6() || \
qx_smart_ptr_base_of_test_7() || qx_smart_ptr_base_of_test_8() || qx_smart_ptr_base_of_test_9() || \
qx_smart_ptr_base_of_test_10() || qx_smart_ptr_base_of_test_11()

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_smart_ptr_base_of<B, D>::value : return true if B and D are smart-pointers of boost, Qt or QxOrm libraries and if (*B) is a base class of (*D), otherwise return false
 */
template <typename B, typename D>
class is_smart_ptr_base_of
{

private:

#ifdef _QX_ENABLE_BOOST

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const boost::scoped_ptr<V> &, const boost::scoped_ptr<W> &);

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const boost::shared_ptr<V> &, const boost::shared_ptr<W> &);

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const boost::weak_ptr<V> &, const boost::weak_ptr<W> &);

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const boost::intrusive_ptr<V> &, const boost::intrusive_ptr<W> &);

#endif // _QX_ENABLE_BOOST

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const QSharedDataPointer<V> &, const QSharedDataPointer<W> &);

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const QSharedPointer<V> &, const QSharedPointer<W> &);

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const QWeakPointer<V> &, const QWeakPointer<W> &);

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const qx::dao::ptr<V> &, const qx::dao::ptr<W> &);

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const std::unique_ptr<V> &, const std::unique_ptr<W> &);

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const std::shared_ptr<V> &, const std::shared_ptr<W> &);

   template <typename V, typename W>
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const std::weak_ptr<V> &, const std::weak_ptr<W> &);

   static int removeSmartPtr(...);
   static B b;
   static D d;

#ifdef _QX_ENABLE_BOOST

   static boost::scoped_ptr<B> * b_boost_scoped_ptr;
   static boost::shared_ptr<B> * b_boost_shared_ptr;
   static boost::weak_ptr<B> * b_boost_weak_ptr;
   static boost::intrusive_ptr<B> * b_boost_intrusive_ptr;

#endif // _QX_ENABLE_BOOST

   static QSharedDataPointer<B> * b_qt_shared_data_ptr;
   static QSharedPointer<B> * b_qt_shared_ptr;
   static QWeakPointer<B> * b_qt_weak_ptr;
   static qx::dao::ptr<B> * b_qx_dao_ptr;

   static std::unique_ptr<B> * b_std_unique_ptr;
   static std::shared_ptr<B> * b_std_shared_ptr;
   static std::weak_ptr<B> * b_std_weak_ptr;

   enum { value_0 = (qx::trait::is_smart_ptr<D>::value) };
   enum { value_1 = (qx::trait::is_smart_ptr<B>::value) };
   enum { value_2 = ((value_0 && value_1) ? qx_smart_ptr_base_of_test_0() : 0) };
   enum { value_3 = ((value_0 && ! value_1) ? qx_smart_ptr_base_of_all_test() : 0) };

public:

   enum { value = (qx::trait::is_smart_ptr_base_of<B, D>::value_2 || qx::trait::is_smart_ptr_base_of<B, D>::value_3) };

   typedef typename std::conditional<qx::trait::is_smart_ptr_base_of<B, D>::value, std::true_type, std::false_type>::type type;

};

} // namespace trait
} // namespace qx

#endif // _QX_IS_SMART_PTR_BASE_OF_H_
