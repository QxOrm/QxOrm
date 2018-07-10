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

#ifndef _QX_MODE_RELEASE

#include <QxPrecompiled.h>

#include <QxTraits/is_smart_ptr.h>
#include <QxTraits/is_smart_ptr_to_pod.h>
#include <QxTraits/is_ptr_base_of.h>
#include <QxTraits/is_ptr_to_pod.h>
#include <QxTraits/is_qx_registered.h>

#include <QxConvert/QxConvert.h>
#include <QxConvert/QxConvert_Impl.h>

#include <QxDao/QxDao.h>
#include <QxDao/QxDao_Impl.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace unit_test {

void unit_test_is_smart_ptr()
{
#ifdef _QX_ENABLE_BOOST

   static_assert(! qx::trait::is_boost_intrusive_ptr<int>::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_intrusive_ptr< boost::shared_ptr<int> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_intrusive_ptr< boost::scoped_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_boost_intrusive_ptr< boost::intrusive_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_boost_intrusive_ptr< boost::intrusive_ptr<char *> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_boost_scoped_ptr<double>::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_scoped_ptr< boost::shared_ptr<int> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_scoped_ptr< boost::weak_ptr<QString> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_scoped_ptr< QWeakPointer<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_boost_scoped_ptr< boost::scoped_ptr<QObject> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_boost_shared_ptr<QObject>::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_shared_ptr< boost::scoped_ptr<QString> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_shared_ptr< boost::intrusive_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_shared_ptr< QSharedPointer<double> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_boost_shared_ptr< boost::shared_ptr<int> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_boost_weak_ptr<int>::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_weak_ptr< QWeakPointer<int> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_weak_ptr< boost::scoped_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_weak_ptr< boost::intrusive_ptr<QString> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_boost_weak_ptr< boost::weak_ptr<QObject> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_qt_shared_data_ptr< boost::scoped_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_qt_shared_data_ptr< boost::weak_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_qt_shared_ptr< boost::shared_ptr<int> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_qt_shared_ptr< boost::scoped_ptr<QString> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_qt_weak_ptr< boost::scoped_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_qt_weak_ptr< boost::weak_ptr<QString> >::value, "unit_test_is_smart_ptr");

   static_assert(qx::trait::is_smart_ptr< boost::scoped_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr< boost::weak_ptr<int> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr< boost::shared_ptr<QString> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr< boost::intrusive_ptr<QObject> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_boost_shared_ptr< std::shared_ptr<double> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_scoped_ptr< std::weak_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_weak_ptr< std::weak_ptr<int> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_intrusive_ptr< std::unique_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_shared_ptr< std::unique_ptr<QString> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_boost_weak_ptr< std::unique_ptr<QObject> >::value, "unit_test_is_smart_ptr");

#endif // _QX_ENABLE_BOOST

   static_assert(! qx::trait::is_qt_shared_data_ptr<QString>::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_qt_shared_data_ptr< QWeakPointer<int> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_qt_shared_data_ptr< QSharedDataPointer<QString> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_qt_shared_ptr<int>::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_qt_shared_ptr< QSharedDataPointer<QString> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_qt_shared_ptr< QSharedPointer<QObject> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_qt_weak_ptr<bool>::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_qt_weak_ptr< QSharedPointer<int> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_qt_weak_ptr< QWeakPointer<QObject> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_smart_ptr<QObject>::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_smart_ptr<int>::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr< QSharedDataPointer<double> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr< QWeakPointer<QString> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr< QSharedPointer<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr< qx::dao::ptr<QString> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr< qx::dao::ptr<int> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_smart_ptr_to_pod< QWeakPointer<QString> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr_to_pod< QSharedDataPointer<double> >::value, "unit_test_is_smart_ptr");

   static_assert(qx::trait::is_std_shared_ptr< std::shared_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_std_weak_ptr< std::shared_ptr<int> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr< std::shared_ptr<QObject> >::value, "unit_test_is_smart_ptr");

   static_assert(! qx::trait::is_qt_shared_data_ptr< std::weak_ptr<int> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_std_weak_ptr< std::weak_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(qx::trait::is_smart_ptr< std::weak_ptr<QString> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_smart_ptr_to_pod< std::weak_ptr<QString> >::value, "unit_test_is_smart_ptr");

   static_assert(qx::trait::is_std_unique_ptr< std::unique_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_qt_shared_data_ptr< std::unique_ptr<QObject> >::value, "unit_test_is_smart_ptr");
   static_assert(! qx::trait::is_qt_shared_ptr< std::unique_ptr<QString> >::value, "unit_test_is_smart_ptr");
}

} // namespace unit_test
} // namespace qx

#endif // _QX_MODE_RELEASE
