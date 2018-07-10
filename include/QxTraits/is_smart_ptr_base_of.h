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

#ifndef _QX_IS_SMART_PTR_BASE_OF_H_
#define _QX_IS_SMART_PTR_BASE_OF_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_base_of.hpp>

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

#define qx_smart_ptr_base_of_all_test() \
qx_smart_ptr_base_of_test_1() || qx_smart_ptr_base_of_test_2() || qx_smart_ptr_base_of_test_3() || \
qx_smart_ptr_base_of_test_4() || qx_smart_ptr_base_of_test_5() || qx_smart_ptr_base_of_test_6() || \
qx_smart_ptr_base_of_test_7() || qx_smart_ptr_base_of_test_8()

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

   template <typename V, typename W>
   static typename boost::mpl::if_c<boost::is_base_of<V, W>::value, char, int>::type removeSmartPtr(const qx::dao::ptr<V> &, const qx::dao::ptr<W> &);

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
   static qx::dao::ptr<B> * b_qx_dao_ptr;

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
