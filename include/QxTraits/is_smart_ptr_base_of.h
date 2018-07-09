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

#ifndef _QX_IS_SMART_PTR_BASE_OF_H_
#define _QX_IS_SMART_PTR_BASE_OF_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include "../../include/QxTraits/is_smart_ptr.h"

#define qx_smart_ptr_base_of_test_0() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr(b, d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_1() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_boost_scoped_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_2() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_boost_shared_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_3() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_boost_weak_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_4() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_boost_intrusive_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_5() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_qt_shared_data_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_6() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_qt_shared_ptr), d)) == sizeof(char))
#define qx_smart_ptr_base_of_test_7() (sizeof(qx::trait::is_smart_ptr_base_of<B, D>::removeSmartPtr((* b_qt_weak_ptr), d)) == sizeof(char))

#define qx_smart_ptr_base_of_all_test() \
qx_smart_ptr_base_of_test_1() || qx_smart_ptr_base_of_test_2() || qx_smart_ptr_base_of_test_3() || \
qx_smart_ptr_base_of_test_4() || qx_smart_ptr_base_of_test_5() || qx_smart_ptr_base_of_test_6() || \
qx_smart_ptr_base_of_test_7()

namespace qx {
namespace trait {

template <typename B, typename D>
class is_smart_ptr_base_of
{

private:

   template <typename V, typename W>
   static typename boost::mpl::if_c<boost::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const boost::scoped_ptr<V> &, const boost::scoped_ptr<W> &);

   template <typename V, typename W>
   static typename boost::mpl::if_c<boost::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const boost::shared_ptr<V> &, const boost::shared_ptr<W> &);

   template <typename V, typename W>
   static typename boost::mpl::if_c<boost::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const boost::weak_ptr<V> &, const boost::weak_ptr<W> &);

   template <typename V, typename W>
   static typename boost::mpl::if_c<boost::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const boost::intrusive_ptr<V> &, const boost::intrusive_ptr<W> &);

   template <typename V, typename W>
   static typename boost::mpl::if_c<boost::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const QSharedDataPointer<V> &, const QSharedDataPointer<W> &);

   template <typename V, typename W>
   static typename boost::mpl::if_c<boost::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const QSharedPointer<V> &, const QSharedPointer<W> &);

   template <typename V, typename W>
   static typename boost::mpl::if_c<boost::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const QWeakPointer<V> &, const QWeakPointer<W> &);

   static int removeSmartPtr(...);
   static B b;
   static D d;

   static boost::scoped_ptr<B> * b_boost_scoped_ptr;
   static boost::shared_ptr<B> * b_boost_shared_ptr;
   static boost::weak_ptr<B> * b_boost_weak_ptr;
   static boost::intrusive_ptr<B> * b_boost_intrusive_ptr;
   static QSharedDataPointer<B> * b_qt_shared_data_ptr;
   static QSharedPointer<B> * b_qt_shared_ptr;
   static QWeakPointer<B> * b_qt_weak_ptr;

   enum { value_0 = (qx::trait::is_smart_ptr<D>::value) };
   enum { value_1 = (qx::trait::is_smart_ptr<B>::value) };
   enum { value_2 = ((value_0 && value_1) ? qx_smart_ptr_base_of_test_0() : 0) };
   enum { value_3 = ((value_0 && ! value_1) ? qx_smart_ptr_base_of_all_test() : 0) };

public:

   enum { value = (qx::trait::is_smart_ptr_base_of<B, D>::value_2 || qx::trait::is_smart_ptr_base_of<B, D>::value_3) };

   typedef typename boost::mpl::if_c<qx::trait::is_smart_ptr_base_of<B, D>::value, boost::mpl::true_, boost::mpl::false_>::type type;

};

} // namespace trait
} // namespace qx

#endif // _QX_IS_SMART_PTR_BASE_OF_H_
