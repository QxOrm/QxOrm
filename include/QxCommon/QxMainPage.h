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

/* -- Main page for Doxygen documentation -- */

/*!
 * \mainpage QxOrm - C++ Object Relational Mapping library
 *
 * QxOrm is a C++ library designed to provide Object Relational Mapping (ORM) feature to C++/Qt developers (like Hibernate in Java, or NHibernate in .Net).<br>
 * QxOrm engine is based on a simple and non intrusive mapping function per class to provide :
 *
 * - <a href="http://www.qxorm.com/qxorm_en/manual.html#manual_30" target="_blank"><b>Persistence</b></a> (based on QtSql Qt module) ;
 * - <a href="http://www.qxorm.com/qxorm_en/manual.html#manual_60" target="_blank"><b>Serialization</b></a> (XML and binary, based on Qt and boost serialization engines) ;
 * - <a href="http://www.qxorm.com/qxorm_en/manual.html#manual_70" target="_blank"><b>Reflection</b></a> or <a href="http://www.qxorm.com/qxorm_en/manual.html#manual_70" target="_blank"><b>Introspection</b></a> (invoke dynamically class methods and access to properties).
 *
 * QxOrm is developed by Lionel Marty, a software development engineer since 2003.<br>
 * QxOrm library has been accepted into the <a href="http://forum.qt.io/category/24/qt-ambassador-program" target="_blank">Qt Ambassador Program</a>.
 *
 * For more information about QxOrm library (quick sample, tutorial and forum), please visit : <a href="http://www.qxorm.com/" target="_blank">http://www.qxorm.com/</a>.<br>
 * <a href="http://www.qxorm.com/qxorm_en/manual.html" target="_blank">A manual (user guide) to learn how to work with QxOrm library is available on QxOrm website</a>.
 * <br><br>
 *
 * \section quick_sample Quick sample using QxOrm library
 *
 * 1- <i>drug.h</i> file : drug class definition with 3 properties : <i>id</i>, <i>name</i> and <i>description</i>
 * \code
#ifndef _CLASS_DRUG_H_
#define _CLASS_DRUG_H_

class drug
{
public:
   long id;
   QString name;
   QString description;

   drug() : id(0) { ; }
   virtual ~drug() { ; }
};

QX_REGISTER_HPP_MY_TEST_EXE(drug, qx::trait::no_base_class_defined, 1)

// This macro is necessary to register 'drug' class in QxOrm context
// param 1 : the current class to register => 'drug'
// param 2 : the base class, if no base class, use the qx trait => 'qx::trait::no_base_class_defined'
// param 3 : the class version used by serialization to provide 'ascendant compatibility'

#endif // _CLASS_DRUG_H_
 * \endcode
 *
 * <br>
 * 2- <i>drug.cpp</i> file : setting function implementation - <i>void qx::register_class()</i>
 * \code
#include "precompiled.h"   // Precompiled-header with '#include <QxOrm.h>' and '#include "export.h"'
#include "drug.h"          // Class definition 'drug'
#include <QxOrm_Impl.h>    // Automatic memory leak detection and boost serialization export macro

QX_REGISTER_CPP_MY_TEST_EXE(drug)   // This macro is necessary to register 'drug' class in QxOrm context

namespace qx {
template <> void register_class(QxClass<drug> & t)
{
  t.id(& drug::id, "id");               // Register 'drug::id' <=> primary key in your database
  t.data(& drug::name, "name", 1);      // Register 'drug::name' property with key 'name' and version '1'
  t.data(& drug::description, "desc");  // Register 'drug::description' property with key 'desc'
}}
 * \endcode
 *
 * <br>
 * 3- <i>main.cpp</i> file : basic functionalities of QxOrm library with drug class
 * \code
#include "precompiled.h"
#include "drug.h"
#include <QxOrm_Impl.h>

int main(int argc, char * argv[])
{
   QApplication app(argc, argv); // Qt application

   // Create 3 new drugs
   // It is possible to use 'boost' and 'Qt' smart pointer : 'boost::shared_ptr', 'QSharedPointer', etc...
   typedef boost::shared_ptr<drug> drug_ptr;
   drug_ptr d1; d1.reset(new drug()); d1->name = "name1"; d1->description = "desc1";
   drug_ptr d2; d2.reset(new drug()); d2->name = "name2"; d2->description = "desc2";
   drug_ptr d3; d3.reset(new drug()); d3->name = "name3"; d3->description = "desc3";

   // Insert drugs into container
   // It is possible to use a lot of containers from 'std', 'boost', 'Qt' and 'qx::QxCollection<Key, Value>'
   typedef std::vector<drug_ptr> type_lst_drug;
   type_lst_drug lst_drug;
   lst_drug.push_back(d1);
   lst_drug.push_back(d2);
   lst_drug.push_back(d3);

   // Init parameters to communicate with a database
   qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
   qx::QxSqlDatabase::getSingleton()->setDatabaseName("./test_qxorm.db");
   qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
   qx::QxSqlDatabase::getSingleton()->setUserName("root");
   qx::QxSqlDatabase::getSingleton()->setPassword("");

   // Create table 'drug' into database to store drugs
   QSqlError daoError = qx::dao::create_table<drug>();

   // Insert drugs from container to database
   // 'id' property of 'd1', 'd2' and 'd3' are auto-updated
   daoError = qx::dao::insert(lst_drug);

   // Modify and update the second drug into database
   d2->name = "name2 modified";
   d2->description = "desc2 modified";
   daoError = qx::dao::update(d2);

   // Delete the first drug from database
   daoError = qx::dao::delete_by_id(d1);

   // Count drugs into database
   long lDrugCount = qx::dao::count<drug>();

   // Fetch drug with id '3' into a new variable
   drug_ptr d_tmp; d_tmp.reset(new drug());
   d_tmp->id = 3;
   daoError = qx::dao::fetch_by_id(d_tmp);

   // Export drugs from container to a file under XML format (serialization)
   qx::serialization::xml::to_file(lst_drug, "./export_drugs.xml");

   // Import drugs from XML file into a new container
   type_lst_drug lst_drug_tmp;
   qx::serialization::xml::from_file(lst_drug_tmp, "./export_drugs.xml");

   // Clone a drug
   drug_ptr d_clone = qx::clone(* d1);

   // Create a new drug by class name (factory)
   boost::any d_any = qx::create("drug");

   // Insert drugs container into 'qx::cache'
   qx::cache::set("drugs", lst_drug);

   // Remove all elements from 'qx::cache'
   qx::cache::clear();

   // Create a dummy memory leak
   drug * pDummy = new drug();

   return 0;
}
 * \endcode
 *
 * <br>
 * 4- execute program and trace output debug
 * \code
[QxOrm] qx::QxSqlDatabase : create new database connection in thread '3616' with key '{d315250c-b5c9-46e0-9402-f800368a6673}'
[QxOrm] sql query (78 ms) : CREATE TABLE drug (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name TEXT, desc TEXT)
[QxOrm] sql query (63 ms) : INSERT INTO drug (name, desc) VALUES (:name, :desc)
[QxOrm] sql query (62 ms) : UPDATE drug SET id = :id, name = :name, desc = :desc WHERE id = :id_bis
[QxOrm] sql query (63 ms) : DELETE FROM drug WHERE id = :id
[QxOrm] sql query (0 ms) : SELECT COUNT(*) FROM drug
[QxOrm] sql query (0 ms) : SELECT drug.id AS drug_id_0, drug.name AS drug_name_0, drug.desc AS drug_desc_0 FROM drug WHERE drug_id_0 = :id
[QxOrm] Leaked object at 0xf52ad8 (size 16, src\main.cpp:74)
[QxOrm] **** 1 memory leaks found ****
 * \endcode
 *
 * <br>
 * 5- <i>export_drugs.xml</i> file created by the program
 * \code
<std.vector-boost.shared_ptr-drug-- class_id="0" tracking_level="0" version="0">
	<count>3</count>
	<item_version>1</item_version>
	<item class_id="1" tracking_level="0" version="1">
		<px class_id="2" tracking_level="1" version="1" object_id="_0">
			<id>1</id>
			<name class_id="3" tracking_level="0" version="0">name1</name>
			<desc>desc1</desc>
		</px>
	</item>
	<item>
		<px class_id_reference="2" object_id="_1">
			<id>2</id>
			<name>name2 modified</name>
			<desc>desc2 modified</desc>
		</px>
	</item>
	<item>
		<px class_id_reference="2" object_id="_2">
			<id>3</id>
			<name>name3</name>
			<desc>desc3</desc>
		</px>
	</item>
</std.vector-boost.shared_ptr-drug-->
 * \endcode
 */

/*!
 * \brief Root namespace for all QxOrm library features
 */
namespace qx {

/*!
 * \ingroup QxCache
 * \brief Provide basic thread-safe cache feature to backup and restore any kind of objects (for example, object fetched from database)
 */
namespace cache {

/*!
 * \ingroup QxCache
 * \brief Internal helper tools for qx::cache namespace
 */
namespace detail {
} // namespace detail

} // namespace cache

/*!
 * \ingroup QxDao
 * \brief Database communication used by persistence engine (ORM - Object Relational Mapping)
 */
namespace dao {

/*!
 * \ingroup QxDao
 * \brief Internal helper tools for qx::dao namespace
 */
namespace detail {
} // namespace detail

} // namespace dao

/*!
 * \ingroup QxFunction
 * \brief Register function into QxOrm context used by introspection engine
 */
namespace function {

/*!
 * \ingroup QxFunction
 * \brief Internal helper tools for qx::function namespace
 */
namespace detail {
} // namespace detail

} // namespace function

/*!
 * \ingroup QxMemLeak
 * \brief QxOrm library memory leak detection (by Wu Yongwei)
 */
namespace memory {
} // namespace memory

/*!
 * \ingroup QxSerialize
 * \brief QxOrm library serialization engine based on boost::serialization library
 */
namespace serialization {

/*!
 * \ingroup QxSerialize
 * \brief Internal helper tools for qx::serialization namespace
 */
namespace detail {
} // namespace detail

/*!
 * \ingroup QxSerialize
 * \brief QxOrm library serialization engine for wide archive
 */
namespace wide {
} // namespace wide

} // namespace serialization

/*!
 * \ingroup QxService
 * \brief QxOrm library services engine to provide easy and powerful way to create C++ application server (to transfer data over network)
 */
namespace service {
} // namespace service

/*!
 * \ingroup QxTraits
 * \brief QxOrm library traits (template metaprogramming) not available in boost::type_traits library
 */
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief Internal helper tools for qx::trait namespace
 */
namespace detail {
} // namespace detail

} // namespace trait

/*!
 * \ingroup QxCollection
 * \brief Foreach-style (based on BOOST_FOREACH macro) to iterate over all stl, boost and Qt containers + qx::QxCollection<Key, Value> QxOrm library container
 */
namespace foreach {
} // namespace foreach

/*!
 * \ingroup QxCommon
 * \brief Provide global functions to convert any kind of objects to/from QString and QVariant format
 */
namespace cvt {

/*!
 * \ingroup QxCommon
 * \brief Internal helper tools for qx::cvt namespace
 */
namespace detail {
} // namespace detail

} // namespace cvt

} // namespace qx
