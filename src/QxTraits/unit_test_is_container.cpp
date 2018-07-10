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

#include "../../include/QxPrecompiled.h"

#include <boost/static_assert.hpp>

#include "../../include/QxTraits/is_container.h"
#include "../../include/QxTraits/is_container_base_of.h"
#include "../../include/QxTraits/is_container_to_pod.h"
#include "../../include/QxTraits/is_container_key_value.h"

#include "../../include/QxCollection/QxCollection.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {
namespace unit_test {

void unit_test_is_container()
{
   BOOST_STATIC_ASSERT(! qx::trait::is_container<int>::value);
   BOOST_STATIC_ASSERT(! qx::trait::is_container<QString>::value);
   BOOST_STATIC_ASSERT(! qx::trait::is_container<QObject>::value);
   BOOST_STATIC_ASSERT(! qx::trait::is_container<double>::value);

   typedef qx::QxCollection<QString, double> qx_coll_string_to_double;
   typedef std::vector<QObject> std_vector_object;
   typedef QHash<double, QString> qt_hash_double_to_string;
   typedef std::set<int> std_set_int;
   typedef boost::unordered_map<std::string, QObject *> boost_unordered_map_string_to_object_ptr;

   BOOST_STATIC_ASSERT(qx::trait::is_container<qx_coll_string_to_double>::value);
   BOOST_STATIC_ASSERT(qx::trait::is_container<std_vector_object>::value);
   BOOST_STATIC_ASSERT(qx::trait::is_container<qt_hash_double_to_string>::value);
   BOOST_STATIC_ASSERT(qx::trait::is_container<std_set_int>::value);

   BOOST_STATIC_ASSERT(qx::trait::is_std_vector< std::vector<double> >::value);
   BOOST_STATIC_ASSERT(! qx::trait::is_qt_vector< std::vector<double> >::value);
   BOOST_STATIC_ASSERT(! qx::trait::is_boost_unordered_map< std::vector<double> >::value);

   typedef qx::trait::is_container_base_of<QObject, std_vector_object> is_container_base_of_std_vector_object;

   BOOST_STATIC_ASSERT(is_container_base_of_std_vector_object::value);
   BOOST_STATIC_ASSERT(qx::trait::is_container_to_pod<std_set_int>::value);
   BOOST_STATIC_ASSERT(qx::trait::is_container_key_value<qx_coll_string_to_double>::value);
   BOOST_STATIC_ASSERT(qx::trait::is_container_key_value<boost_unordered_map_string_to_object_ptr>::value);
}

} // namespace unit_test
} // namespace qx
