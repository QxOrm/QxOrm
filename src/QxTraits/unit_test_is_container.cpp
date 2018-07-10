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

#include <QxTraits/is_container.h>
#include <QxTraits/is_container_to_pod.h>
#include <QxTraits/is_container_key_value.h>

#include <QxCollection/QxCollection.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace unit_test {

void unit_test_is_container()
{
   static_assert(! qx::trait::is_container<int>::value, "unit_test_is_container");
   static_assert(! qx::trait::is_container<QString>::value, "unit_test_is_container");
   static_assert(! qx::trait::is_container<QObject>::value, "unit_test_is_container");
   static_assert(! qx::trait::is_container<double>::value, "unit_test_is_container");

   typedef qx::QxCollection<QString, double> qx_coll_string_to_double;
   typedef std::vector<QObject> std_vector_object;
   typedef QHash<double, QString> qt_hash_double_to_string;
   typedef std::set<int> std_set_int;

   static_assert(qx::trait::is_container<qx_coll_string_to_double>::value, "unit_test_is_container");
   static_assert(qx::trait::is_container<std_vector_object>::value, "unit_test_is_container");
   static_assert(qx::trait::is_container<qt_hash_double_to_string>::value, "unit_test_is_container");
   static_assert(qx::trait::is_container<std_set_int>::value, "unit_test_is_container");

   static_assert(qx::trait::is_std_vector< std::vector<double> >::value, "unit_test_is_container");
   static_assert(! qx::trait::is_qt_vector< std::vector<double> >::value, "unit_test_is_container");

   static_assert(qx::trait::is_container_to_pod<std_set_int>::value, "unit_test_is_container");
   static_assert(qx::trait::is_container_key_value<qx_coll_string_to_double>::value, "unit_test_is_container");

#ifdef _QX_ENABLE_BOOST

   typedef boost::unordered_map<std::string, QObject *> boost_unordered_map_string_to_object_ptr;

   static_assert(! qx::trait::is_boost_unordered_map< std::vector<double> >::value, "unit_test_is_container");
   static_assert(qx::trait::is_container_key_value<boost_unordered_map_string_to_object_ptr>::value, "unit_test_is_container");

#endif // _QX_ENABLE_BOOST
}

} // namespace unit_test
} // namespace qx

#endif // _QX_MODE_RELEASE
