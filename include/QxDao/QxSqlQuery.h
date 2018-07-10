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

#ifndef _QX_SQL_QUERY_H_
#define _QX_SQL_QUERY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlQuery.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Define a user SQL query added to default SQL query builded by QxOrm library, and used by qx::dao::xxx functions to filter elements fetched from database
 */

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#endif // _QX_ENABLE_BOOST_SERIALIZATION

#include <QtCore/qdatastream.h>

#ifndef _QX_NO_JSON
#include <QtCore/qjsonvalue.h>
#endif // _QX_NO_JSON

#include <QtSql/qsqlquery.h>

#include <QxCollection/QxCollection.h>

#include <QxDao/QxSqlElement/QxSqlElement.h>

#include <QxSerialize/QxSerializeFastCompil.h>

#include <QxTraits/get_class_name.h>

#include <QxRegister/QxVersion.h>

#include <QxConvert/QxConvert.h>

namespace qx {
class QxSqlQuery;
} // namespace qx

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
namespace boost {
namespace serialization {

template <class Archive> inline void qx_save(Archive & ar, const qx::QxSqlQuery & t, const unsigned int file_version);
template <class Archive> inline void qx_load(Archive & ar, qx::QxSqlQuery & t, const unsigned int file_version);

} // namespace serialization
} // namespace boost
#endif // _QX_ENABLE_BOOST_SERIALIZATION

QX_DLL_EXPORT QDataStream & operator<< (QDataStream & stream, const qx::QxSqlQuery & t) QX_USED;
QX_DLL_EXPORT QDataStream & operator>> (QDataStream & stream, qx::QxSqlQuery & t) QX_USED;

#ifndef _QX_NO_JSON
namespace qx {
namespace cvt {
namespace detail {
template <> struct QxConvert_ToJson< qx::QxSqlQuery >;
template <> struct QxConvert_FromJson< qx::QxSqlQuery >;
QX_DLL_EXPORT QJsonValue QxConvert_ToJson_Helper(const qx::QxSqlQuery & t, const QString & format) QX_USED;
QX_DLL_EXPORT qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, qx::QxSqlQuery & t, const QString & format) QX_USED;
} // namespace detail
} // namespace cvt
} // namespace qx
#endif // _QX_NO_JSON

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlQuery : define a user SQL query added to default SQL query builded by QxOrm library, and used by qx::dao::xxx functions to filter elements fetched from database
 *
 * The class <i>qx::QxSqlQuery</i> (or its typedef <i>qx_query</i>) is used to communicate with database (to filter, to sort, etc.) in two different ways :
 * - writing manually SQL query ;
 * - using C++ methods with a syntax similar to SQL (same concept than the great library <i>SubSonic</i> for .Net).
 *
 * With the first method (writing manually SQL query), you can use some optimizations specific for each database.
 * The second method (using C++ code to build SQL query) binds automatically SQL parameters without using <i>qx::QxSqlQuery::bind()</i> function.
 *
 * Here is an example with <i>qx::QxSqlQuery</i> class writing manually a SQL query :
 * \code
// Build a SQL query to fetch only 'author' of type 'female'
qx::QxSqlQuery query("WHERE author.sex = :sex");
query.bind(":sex", author::female);

QList<author> list_of_female;
QSqlError daoError = qx::dao::fetch_by_query(query, list_of_female);

// Here we can work with the collection provided by database
for (long l = 0; l < list_of_female.count(); l++) { ; }
 * \endcode
 *
 * QxOrm library provides 3 styles to write SQL parameters.
 * This style can be modified for a project using the following method <i>qx::QxSqlDatabase::getSingleton()->setSqlPlaceHolderStyle()</i> :
 * - <i>ph_style_2_point_name</i> : "WHERE author.sex = :sex" (default style) ;
 * - <i>ph_style_at_name</i> : "WHERE author.sex = @sex" ;
 * - <i>ph_style_question_mark</i> : "WHERE author.sex = ?".
 *
 * Here is the same example using C++ code of the class <i>qx::QxSqlQuery</i> (or its typedef <i>qx_query</i>) to build query automatically :
 * \code
// Build a SQL query to fetch only 'author' of type 'female'
qx_query query;
query.where("author.sex").isEqualTo(author::female);

QList<author> list_of_female;
QSqlError daoError = qx::dao::fetch_by_query(query, list_of_female);

// Here we can work with the collection provided by database
for (long l = 0; l < list_of_female.count(); l++) { ; }
 * \endcode
 *
 * With C++ methods of <i>qx::QxSqlQuery</i> class, you don't have to bind any SQL parameter, and the syntax is similar to real SQL.
 * All SQL parameters will be provided to database automatically with the following style : <i>qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle()</i>.
 *
 * Here is an example with many methods of <i>qx::QxSqlQuery</i> class (or its typedef <i>qx_query</i>) :
 * \code
qx_query query;
query.where("sex").isEqualTo(author::female)
     .and_("age").isGreaterThan(38)
     .or_("last_name").isNotEqualTo("Dupont")
     .or_("first_name").like("Alfred")
     .and_OpenParenthesis("id").isLessThanOrEqualTo(999)
     .and_("birth_date").isBetween(date1, date2)
     .closeParenthesis()
     .or_("id").in(50, 999, 11, 23, 78945)
     .and_("is_deleted").isNotNull()
     .orderAsc("last_name", "first_name", "sex")
     .limit(50, 150);
 * \endcode
 *
 * This code will produce following SQL for <i>MySQL</i>, <i>PostgreSQL</i> and <i>SQLite</i> databases (for <i>Oracle</i> and <i>SQLServer</i>, there is a specific process for <i>limit()</i> method) :
 * \code
WHERE sex = :sex_1_0 
AND age > :age_3_0 
OR last_name <> :last_name_5_0 
OR first_name LIKE :first_name_7_0 
AND ( id <= :id_10_0 AND birth_date BETWEEN :birth_date_12_0_1 AND :birth_date_12_0_2 ) 
OR id IN (:id_15_0_0, :id_15_0_1, :id_15_0_2, :id_15_0_3, :id_15_0_4) 
AND is_deleted IS NOT NULL 
ORDER BY last_name ASC, first_name ASC, sex ASC 
LIMIT :limit_rows_count_19_0 OFFSET :offset_start_row_19_0
 * \endcode
 *
 * Here is the list of all functions available to use <i>qx::QxSqlQuery</i> class (or its typedef <i>qx_query</i>) :
 * \code
// with functions into namespace qx::dao
qx::dao::count<T>()
qx::dao::fetch_by_query<T>()
qx::dao::update_by_query<T>()
qx::dao::delete_by_query<T>()
qx::dao::destroy_by_query<T>()
qx::dao::fetch_by_query_with_relation<T>()
qx::dao::fetch_by_query_with_all_relation<T>()
qx::dao::update_by_query_with_relation<T>()
qx::dao::update_by_query_with_all_relation<T>()
qx::dao::update_optimized_by_query<T>()

// with qx::QxSession class
qx::QxSession::count<T>()
qx::QxSession::fetchByQuery<T>()
qx::QxSession::update<T>()
qx::QxSession::deleteByQuery<T>()
qx::QxSession::destroyByQuery<T>()

// with qx::QxRepository<T> class
qx::QxRepository<T>::count()
qx::QxRepository<T>::fetchByQuery()
qx::QxRepository<T>::update()
qx::QxRepository<T>::deleteByQuery()
qx::QxRepository<T>::destroyByQuery()
 * \endcode
 *
 * <i>Note :</i> those functions have 2 other optionals parameters :
 * - <i>const QStringList & columns</i> : to indicate columns to fetch (by default, all columns are fetched) ;
 * - <i>const QStringList & relation</i> : to indicate relations to fetch (<i>one-to-one</i>, <i>one-to-many</i>, <i>many-to-one</i> and <i>many-to-many</i> defined into <i>void qx::register_class<T>()</i> mapping function by class), by default there is no relation fetched.
 *
 * <i>Other note :</i> it's possible to call a stored procedure using <i>qx::QxSqlQuery</i> class, for example :
 * \code
qx_query query("CALL MyStoredProc(:param1, :param2)");
query.bind(":param1", "myValue1");
query.bind(":param2", 5024, QSql::InOut);
QSqlError daoError = qx::dao::call_query(query);
QVariant vNewValue = query.boundValue(":param2");
query.dumpSqlResult();
 * \endcode
 *
 * If the stored procedure returns a resultset, you can iterate over each rows and fields using the following methods (after calling <i>qx::dao::call_query()</i> function) :
 * - <i>long qx::QxSqlQuery::getSqlResultRowCount() const;</i>
 * - <i>long qx::QxSqlQuery::getSqlResultColumnCount() const;</i>
 * - <i>QVariant qx::QxSqlQuery::getSqlResultAt(long row, long column) const;</i>
 * - <i>QVariant qx::QxSqlQuery::getSqlResultAt(long row, const QString & column) const;</i>
 * - <i>QVector qx::QxSqlQuery::getSqlResultAllColumns() const;</i>
 * - <i>void qx::QxSqlQuery::dumpSqlResult();</i>
 *
 * <i>Other note :</i> to add your own SQL query methods (for example, some databases provide non-standard specifics SQL functions) :
 * - create a derived class based on <i>qx::QxSqlQuery</i> class ;
 * - if your C++ compiler supports covariant return type, add the macro <i>QX_SQL_QUERY_DERIVED_IMPL_COVARIANT_RETURN_TYPE_HPP(myClass)</i> in the definition of your class (<i>myClass.h</i>) ;
 * - if your C++ compiler supports covariant return type, add the macro <i>QX_SQL_QUERY_DERIVED_IMPL_COVARIANT_RETURN_TYPE_CPP(myClass)</i> in the implementation of your class (<i>myClass.cpp</i>) ;
 * - add all SQL specifics functions in your derived class.
 */
class QX_DLL_EXPORT QxSqlQuery
{

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
   template <class Archive> friend inline void boost::serialization::qx_save(Archive & ar, const qx::QxSqlQuery & t, const unsigned int file_version);
   template <class Archive> friend inline void boost::serialization::qx_load(Archive & ar, qx::QxSqlQuery & t, const unsigned int file_version);
#endif // _QX_ENABLE_BOOST_SERIALIZATION

   friend QDataStream & ::operator<< (QDataStream & stream, const qx::QxSqlQuery & t);
   friend QDataStream & ::operator>> (QDataStream & stream, qx::QxSqlQuery & t);

#ifndef _QX_NO_JSON
   friend struct qx::cvt::detail::QxConvert_ToJson< qx::QxSqlQuery >;
   friend struct qx::cvt::detail::QxConvert_FromJson< qx::QxSqlQuery >;
   friend QJsonValue qx::cvt::detail::QxConvert_ToJson_Helper(const qx::QxSqlQuery & t, const QString & format);
   friend qx_bool qx::cvt::detail::QxConvert_FromJson_Helper(const QJsonValue & j, qx::QxSqlQuery & t, const QString & format);
#endif // _QX_NO_JSON

protected:

   struct QxSqlResult
   { QHash<QString, int> positionByKey; QVector< QVector<QVariant> > values; };

   typedef std::tuple<QVariant, QSql::ParamType> type_bind_value;

   QString                                   m_sQuery;               //!< Query SQL with place-holder
   QxCollection<QString, type_bind_value>    m_lstValue;             //!< Bind value in this array
   qx::dao::detail::IxSqlElement_ptr         m_pSqlElementTemp;      //!< Temporary SQL element
   QList<qx::dao::detail::IxSqlElement_ptr>  m_lstSqlElement;        //!< List of all SQL elements to build SQL query
   int                                       m_iSqlElementIndex;     //!< Current index of SQL element
   int                                       m_iParenthesisCount;    //!< Current parenthesis count
   bool                                      m_bDistinct;            //!< Replace SELECT by SELECT DISTINCT in SQL query
   std::shared_ptr<QxSqlResult>              m_pSqlResult;           //!< All results returning by SQL query or stored procedure (after calling qx::dao::call_query function)

public:

   QxSqlQuery() : m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false) { ; }
   QxSqlQuery(const QString & sQuery) : m_sQuery(sQuery), m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false) { ; }
   QxSqlQuery(const char * sQuery) : m_sQuery(sQuery), m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false) { ; }
   virtual ~QxSqlQuery() { ; }

   QString query();
   bool isEmpty() const;
   bool isDistinct() const;
   void clear();
   void resolve(QSqlQuery & query) const;
   void resolveOutput(QSqlQuery & query, bool bFetchSqlResult);
   void postProcess(QString & sql) const;

   QxSqlQuery & query(const QString & sQuery);
   QxSqlQuery & bind(const QVariant & vValue, QSql::ParamType paramType = QSql::In);
   QxSqlQuery & bind(const QString & sKey, const QVariant & vValue, QSql::ParamType paramType = QSql::In);

   QVariant boundValue(const QString & sKey) const;
   QVariant boundValue(int iPosition) const;

   long getSqlResultRowCount() const;
   long getSqlResultColumnCount() const;
   QVariant getSqlResultAt(long row, long column) const;
   QVariant getSqlResultAt(long row, const QString & column) const;
   QVector<QVariant> getSqlResultAt(long row) const;
   QVector<QString> getSqlResultAllColumns() const;
   void dumpSqlResult();

   static void dumpBoundValues(const QSqlQuery & query);

private:

   void verifyQuery() const QX_USED;
   void fetchSqlResult(QSqlQuery & query);

public:

   /* -- All methods to build SQL query using C++ syntax -- */

   virtual QxSqlQuery & distinct();

   virtual QxSqlQuery & where(const QString & column);
   virtual QxSqlQuery & where_OpenParenthesis(const QString & column);
   virtual QxSqlQuery & and_(const QString & column);
   virtual QxSqlQuery & and_OpenParenthesis(const QString & column);
   virtual QxSqlQuery & or_(const QString & column);
   virtual QxSqlQuery & or_OpenParenthesis(const QString & column);

   virtual QxSqlQuery & openParenthesis();
   virtual QxSqlQuery & closeParenthesis();

   virtual QxSqlQuery & orderAsc(const QStringList & columns);
   virtual QxSqlQuery & orderAsc(const QString & col1);
   virtual QxSqlQuery & orderAsc(const QString & col1, const QString & col2);
   virtual QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3);
   virtual QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4);
   virtual QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5);
   virtual QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6);
   virtual QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7);
   virtual QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8);
   virtual QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9);

   virtual QxSqlQuery & orderDesc(const QStringList & columns);
   virtual QxSqlQuery & orderDesc(const QString & col1);
   virtual QxSqlQuery & orderDesc(const QString & col1, const QString & col2);
   virtual QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3);
   virtual QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4);
   virtual QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5);
   virtual QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6);
   virtual QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7);
   virtual QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8);
   virtual QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9);

   virtual QxSqlQuery & groupBy(const QStringList & columns);
   virtual QxSqlQuery & groupBy(const QString & col1);
   virtual QxSqlQuery & groupBy(const QString & col1, const QString & col2);
   virtual QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3);
   virtual QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4);
   virtual QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5);
   virtual QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6);
   virtual QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7);
   virtual QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8);
   virtual QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9);

   virtual QxSqlQuery & limit(int rowsCount, int startRow = 0);

   virtual QxSqlQuery & like(const QString & val);
   virtual QxSqlQuery & notLike(const QString & val);
   virtual QxSqlQuery & startsWith(const QString & val);
   virtual QxSqlQuery & endsWith(const QString & val);
   virtual QxSqlQuery & containsString(const QString & val);

   virtual QxSqlQuery & isEqualTo(const QVariant & val);
   virtual QxSqlQuery & isNotEqualTo(const QVariant & val);
   virtual QxSqlQuery & isGreaterThan(const QVariant & val);
   virtual QxSqlQuery & isGreaterThanOrEqualTo(const QVariant & val);
   virtual QxSqlQuery & isLessThan(const QVariant & val);
   virtual QxSqlQuery & isLessThanOrEqualTo(const QVariant & val);
   virtual QxSqlQuery & customOperator(const QString & sCustomOperator, const QVariant & val);

   virtual QxSqlQuery & in(const QVariantList & values);
   virtual QxSqlQuery & in(const QVariant & val1);
   virtual QxSqlQuery & in(const QVariant & val1, const QVariant & val2);
   virtual QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3);
   virtual QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4);
   virtual QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5);
   virtual QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6);
   virtual QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7);
   virtual QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8);
   virtual QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9);

   virtual QxSqlQuery & notIn(const QVariantList & values);
   virtual QxSqlQuery & notIn(const QVariant & val1);
   virtual QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2);
   virtual QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3);
   virtual QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4);
   virtual QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5);
   virtual QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6);
   virtual QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7);
   virtual QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8);
   virtual QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9);

   virtual QxSqlQuery & in_Select(const QString & sql);
   virtual QxSqlQuery & notIn_Select(const QString & sql);

   virtual QxSqlQuery & isNull();
   virtual QxSqlQuery & isNotNull();

   virtual QxSqlQuery & isBetween(const QVariant & val1, const QVariant & val2);
   virtual QxSqlQuery & isNotBetween(const QVariant & val1, const QVariant & val2);

   virtual QxSqlQuery & freeText(const QString & text);

private:

   QxSqlQuery & addSqlExpression(const QString & column, qx::dao::detail::QxSqlExpression::type type);
   QxSqlQuery & addSqlCompare(const QVariant & val, qx::dao::detail::QxSqlCompare::type type, const QString & sCustomOperator = QString());
   QxSqlQuery & addSqlSort(const QStringList & columns, qx::dao::detail::QxSqlSort::type type);
   QxSqlQuery & addSqlIn(const QVariantList & values, qx::dao::detail::QxSqlIn::type type);
   QxSqlQuery & addSqlIsNull(qx::dao::detail::QxSqlIsNull::type type);
   QxSqlQuery & addSqlIsBetween(const QVariant & val1, const QVariant & val2, qx::dao::detail::QxSqlIsBetween::type type);

};

} // namespace qx

typedef qx::QxSqlQuery qx_query;

namespace qx {
namespace dao {

/*!
 * \ingroup QxDao
 * \brief qx::dao::call_query function can be used to call a custom SQL query or a stored procedure
 *
 * To get an output value parameter (must be pass as <i>QSql::Out</i> or <i>QSql::InOut</i>) returned by a stored procedure, just call the following method : <i>QVariant qx::QxSqlQuery::boundValue(const QString & sKey) const;</i>.<br/>
 * To iterate over all resultset, just use the following methods :
 * - <i>long qx::QxSqlQuery::getSqlResultRowCount() const;</i>
 * - <i>long qx::QxSqlQuery::getSqlResultColumnCount() const;</i>
 * - <i>QVariant qx::QxSqlQuery::getSqlResultAt(long row, long column) const;</i>
 * - <i>QVariant qx::QxSqlQuery::getSqlResultAt(long row, const QString & column) const;</i>
 * - <i>QVector qx::QxSqlQuery::getSqlResultAllColumns() const;</i>
 * - <i>void qx::QxSqlQuery::dumpSqlResult();</i>
 *
 * Here is an example of code using <i>qx::dao::call_query</i> function :
 * \code
qx_query query("CALL MyStoredProc(:param1, :param2)");
query.bind(":param1", "myValue1");
query.bind(":param2", 5024, QSql::InOut);
QSqlError daoError = qx::dao::call_query(query);
QVariant vNewValue = query.boundValue(":param2");
query.dumpSqlResult();
 * \endcode
 */
QX_DLL_EXPORT QSqlError call_query(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL);

/*!
 * \ingroup QxDao
 * \brief qx::dao::call_query_without_prepare function can be used to call a custom SQL query or a stored procedure : same as qx::dao::call_query() function without calling prepare() QSqlQuery class method (can be useful to execute some specific SQL queries)
 */
QX_DLL_EXPORT QSqlError call_query_without_prepare(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL);

namespace helper {

QX_DLL_EXPORT QSqlError call_query_helper(qx::QxSqlQuery & query, QSqlDatabase * pDatabase, bool bPrepare);

} // namespace helper
} // namespace dao
} // namespace qx

QX_REGISTER_CLASS_NAME(qx_query)

QX_CLASS_VERSION(qx::QxSqlQuery, 0)

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_HPP(QX_DLL_EXPORT, qx::QxSqlQuery)
#endif // _QX_ENABLE_BOOST_SERIALIZATION

#define QX_SQL_QUERY_DERIVED_IMPL_COVARIANT_RETURN_TYPE_HPP(className) \
public: \
\
virtual className & distinct(); \
\
virtual className & where(const QString & column); \
virtual className & where_OpenParenthesis(const QString & column); \
virtual className & and_(const QString & column); \
virtual className & and_OpenParenthesis(const QString & column); \
virtual className & or_(const QString & column); \
virtual className & or_OpenParenthesis(const QString & column); \
\
virtual className & openParenthesis(); \
virtual className & closeParenthesis(); \
\
virtual className & orderAsc(const QStringList & columns); \
virtual className & orderAsc(const QString & col1); \
virtual className & orderAsc(const QString & col1, const QString & col2); \
virtual className & orderAsc(const QString & col1, const QString & col2, const QString & col3); \
virtual className & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4); \
virtual className & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5); \
virtual className & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6); \
virtual className & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7); \
virtual className & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8); \
virtual className & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9); \
\
virtual className & orderDesc(const QStringList & columns); \
virtual className & orderDesc(const QString & col1); \
virtual className & orderDesc(const QString & col1, const QString & col2); \
virtual className & orderDesc(const QString & col1, const QString & col2, const QString & col3); \
virtual className & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4); \
virtual className & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5); \
virtual className & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6); \
virtual className & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7); \
virtual className & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8); \
virtual className & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9); \
\
virtual className & groupBy(const QStringList & columns); \
virtual className & groupBy(const QString & col1); \
virtual className & groupBy(const QString & col1, const QString & col2); \
virtual className & groupBy(const QString & col1, const QString & col2, const QString & col3); \
virtual className & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4); \
virtual className & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5); \
virtual className & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6); \
virtual className & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7); \
virtual className & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8); \
virtual className & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9); \
\
virtual className & limit(int rowsCount, int startRow = 0); \
\
virtual className & like(const QString & val); \
virtual className & notLike(const QString & val); \
virtual className & startsWith(const QString & val); \
virtual className & endsWith(const QString & val); \
virtual className & containsString(const QString & val); \
\
virtual className & isEqualTo(const QVariant & val); \
virtual className & isNotEqualTo(const QVariant & val); \
virtual className & isGreaterThan(const QVariant & val); \
virtual className & isGreaterThanOrEqualTo(const QVariant & val); \
virtual className & isLessThan(const QVariant & val); \
virtual className & isLessThanOrEqualTo(const QVariant & val); \
virtual className & customOperator(const QString & sCustomOperator, const QVariant & val); \
\
virtual className & in(const QVariantList & values); \
virtual className & in(const QVariant & val1); \
virtual className & in(const QVariant & val1, const QVariant & val2); \
virtual className & in(const QVariant & val1, const QVariant & val2, const QVariant & val3); \
virtual className & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4); \
virtual className & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5); \
virtual className & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6); \
virtual className & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7); \
virtual className & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8); \
virtual className & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9); \
\
virtual className & notIn(const QVariantList & values); \
virtual className & notIn(const QVariant & val1); \
virtual className & notIn(const QVariant & val1, const QVariant & val2); \
virtual className & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3); \
virtual className & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4); \
virtual className & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5); \
virtual className & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6); \
virtual className & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7); \
virtual className & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8); \
virtual className & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9); \
\
virtual className & in_Select(const QString & sql); \
virtual className & notIn_Select(const QString & sql); \
\
virtual className & isNull(); \
virtual className & isNotNull(); \
\
virtual className & isBetween(const QVariant & val1, const QVariant & val2); \
virtual className & isNotBetween(const QVariant & val1, const QVariant & val2); \
\
virtual className & freeText(const QString & text);

#define QX_SQL_QUERY_DERIVED_IMPL_COVARIANT_RETURN_TYPE_CPP(className) \
\
className & className::distinct() { return static_cast<className &>(qx::QxSqlQuery::distinct()); } \
\
className & className::where(const QString & column) { return static_cast<className &>(qx::QxSqlQuery::where(column)); } \
className & className::where_OpenParenthesis(const QString & column) { return static_cast<className &>(qx::QxSqlQuery::where_OpenParenthesis(column)); } \
className & className::and_(const QString & column) { return static_cast<className &>(qx::QxSqlQuery::and_(column)); } \
className & className::and_OpenParenthesis(const QString & column) { return static_cast<className &>(qx::QxSqlQuery::and_OpenParenthesis(column)); } \
className & className::or_(const QString & column) { return static_cast<className &>(qx::QxSqlQuery::or_(column)); } \
className & className::or_OpenParenthesis(const QString & column) { return static_cast<className &>(qx::QxSqlQuery::or_OpenParenthesis(column)); } \
\
className & className::openParenthesis() { return static_cast<className &>(qx::QxSqlQuery::openParenthesis()); } \
className & className::closeParenthesis() { return static_cast<className &>(qx::QxSqlQuery::closeParenthesis()); } \
\
className & className::orderAsc(const QStringList & columns) { return static_cast<className &>(qx::QxSqlQuery::orderAsc(columns)); } \
className & className::orderAsc(const QString & col1) { return static_cast<className &>(qx::QxSqlQuery::orderAsc(col1)); } \
className & className::orderAsc(const QString & col1, const QString & col2) { return static_cast<className &>(qx::QxSqlQuery::orderAsc(col1, col2)); } \
className & className::orderAsc(const QString & col1, const QString & col2, const QString & col3) { return static_cast<className &>(qx::QxSqlQuery::orderAsc(col1, col2, col3)); } \
className & className::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4) { return static_cast<className &>(qx::QxSqlQuery::orderAsc(col1, col2, col3, col4)); } \
className & className::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5) { return static_cast<className &>(qx::QxSqlQuery::orderAsc(col1, col2, col3, col4, col5)); } \
className & className::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6) { return static_cast<className &>(qx::QxSqlQuery::orderAsc(col1, col2, col3, col4, col5, col6)); } \
className & className::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7) { return static_cast<className &>(qx::QxSqlQuery::orderAsc(col1, col2, col3, col4, col5, col6, col7)); } \
className & className::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8) { return static_cast<className &>(qx::QxSqlQuery::orderAsc(col1, col2, col3, col4, col5, col6, col7, col8)); } \
className & className::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9) { return static_cast<className &>(qx::QxSqlQuery::orderAsc(col1, col2, col3, col4, col5, col6, col7, col8, col9)); } \
\
className & className::orderDesc(const QStringList & columns) { return static_cast<className &>(qx::QxSqlQuery::orderDesc(columns)); } \
className & className::orderDesc(const QString & col1) { return static_cast<className &>(qx::QxSqlQuery::orderDesc(col1)); } \
className & className::orderDesc(const QString & col1, const QString & col2) { return static_cast<className &>(qx::QxSqlQuery::orderDesc(col1, col2)); } \
className & className::orderDesc(const QString & col1, const QString & col2, const QString & col3) { return static_cast<className &>(qx::QxSqlQuery::orderDesc(col1, col2, col3)); } \
className & className::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4) { return static_cast<className &>(qx::QxSqlQuery::orderDesc(col1, col2, col3, col4)); } \
className & className::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5) { return static_cast<className &>(qx::QxSqlQuery::orderDesc(col1, col2, col3, col4, col5)); } \
className & className::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6) { return static_cast<className &>(qx::QxSqlQuery::orderDesc(col1, col2, col3, col4, col5, col6)); } \
className & className::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7) { return static_cast<className &>(qx::QxSqlQuery::orderDesc(col1, col2, col3, col4, col5, col6, col7)); } \
className & className::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8) { return static_cast<className &>(qx::QxSqlQuery::orderDesc(col1, col2, col3, col4, col5, col6, col7, col8)); } \
className & className::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9) { return static_cast<className &>(qx::QxSqlQuery::orderDesc(col1, col2, col3, col4, col5, col6, col7, col8, col9)); } \
\
className & className::groupBy(const QStringList & columns) { return static_cast<className &>(qx::QxSqlQuery::groupBy(columns)); } \
className & className::groupBy(const QString & col1) { return static_cast<className &>(qx::QxSqlQuery::groupBy(col1)); } \
className & className::groupBy(const QString & col1, const QString & col2) { return static_cast<className &>(qx::QxSqlQuery::groupBy(col1, col2)); } \
className & className::groupBy(const QString & col1, const QString & col2, const QString & col3) { return static_cast<className &>(qx::QxSqlQuery::groupBy(col1, col2, col3)); } \
className & className::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4) { return static_cast<className &>(qx::QxSqlQuery::groupBy(col1, col2, col3, col4)); } \
className & className::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5) { return static_cast<className &>(qx::QxSqlQuery::groupBy(col1, col2, col3, col4, col5)); } \
className & className::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6) { return static_cast<className &>(qx::QxSqlQuery::groupBy(col1, col2, col3, col4, col5, col6)); } \
className & className::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7) { return static_cast<className &>(qx::QxSqlQuery::groupBy(col1, col2, col3, col4, col5, col6, col7)); } \
className & className::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8) { return static_cast<className &>(qx::QxSqlQuery::groupBy(col1, col2, col3, col4, col5, col6, col7, col8)); } \
className & className::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9) { return static_cast<className &>(qx::QxSqlQuery::groupBy(col1, col2, col3, col4, col5, col6, col7, col8, col9)); } \
\
className & className::limit(int rowsCount, int startRow) { return static_cast<className &>(qx::QxSqlQuery::limit(rowsCount, startRow)); } \
\
className & className::like(const QString & val) { return static_cast<className &>(qx::QxSqlQuery::like(val)); } \
className & className::notLike(const QString & val) { return static_cast<className &>(qx::QxSqlQuery::notLike(val)); } \
className & className::startsWith(const QString & val) { return static_cast<className &>(qx::QxSqlQuery::startsWith(val)); } \
className & className::endsWith(const QString & val) { return static_cast<className &>(qx::QxSqlQuery::endsWith(val)); } \
className & className::containsString(const QString & val) { return static_cast<className &>(qx::QxSqlQuery::containsString(val)); } \
\
className & className::isEqualTo(const QVariant & val) { return static_cast<className &>(qx::QxSqlQuery::isEqualTo(val)); } \
className & className::isNotEqualTo(const QVariant & val) { return static_cast<className &>(qx::QxSqlQuery::isNotEqualTo(val)); } \
className & className::isGreaterThan(const QVariant & val) { return static_cast<className &>(qx::QxSqlQuery::isGreaterThan(val)); } \
className & className::isGreaterThanOrEqualTo(const QVariant & val) { return static_cast<className &>(qx::QxSqlQuery::isGreaterThanOrEqualTo(val)); } \
className & className::isLessThan(const QVariant & val) { return static_cast<className &>(qx::QxSqlQuery::isLessThan(val)); } \
className & className::isLessThanOrEqualTo(const QVariant & val) { return static_cast<className &>(qx::QxSqlQuery::isLessThanOrEqualTo(val)); } \
className & className::customOperator(const QString & sCustomOperator, const QVariant & val) { return static_cast<className &>(qx::QxSqlQuery::customOperator(sCustomOperator, val)); } \
\
className & className::in(const QVariantList & values) { return static_cast<className &>(qx::QxSqlQuery::in(values)); } \
className & className::in(const QVariant & val1) { return static_cast<className &>(qx::QxSqlQuery::in(val1)); } \
className & className::in(const QVariant & val1, const QVariant & val2) { return static_cast<className &>(qx::QxSqlQuery::in(val1, val2)); } \
className & className::in(const QVariant & val1, const QVariant & val2, const QVariant & val3) { return static_cast<className &>(qx::QxSqlQuery::in(val1, val2, val3)); } \
className & className::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4) { return static_cast<className &>(qx::QxSqlQuery::in(val1, val2, val3, val4)); } \
className & className::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5) { return static_cast<className &>(qx::QxSqlQuery::in(val1, val2, val3, val4, val5)); } \
className & className::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6) { return static_cast<className &>(qx::QxSqlQuery::in(val1, val2, val3, val4, val5, val6)); } \
className & className::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7) { return static_cast<className &>(qx::QxSqlQuery::in(val1, val2, val3, val4, val5, val6, val7)); } \
className & className::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8) { return static_cast<className &>(qx::QxSqlQuery::in(val1, val2, val3, val4, val5, val6, val7, val8)); } \
className & className::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9) { return static_cast<className &>(qx::QxSqlQuery::in(val1, val2, val3, val4, val5, val6, val7, val8, val9)); } \
\
className & className::notIn(const QVariantList & values) { return static_cast<className &>(qx::QxSqlQuery::notIn(values)); } \
className & className::notIn(const QVariant & val1) { return static_cast<className &>(qx::QxSqlQuery::notIn(val1)); } \
className & className::notIn(const QVariant & val1, const QVariant & val2) { return static_cast<className &>(qx::QxSqlQuery::notIn(val1, val2)); } \
className & className::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3) { return static_cast<className &>(qx::QxSqlQuery::notIn(val1, val2, val3)); } \
className & className::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4) { return static_cast<className &>(qx::QxSqlQuery::notIn(val1, val2, val3, val4)); } \
className & className::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5) { return static_cast<className &>(qx::QxSqlQuery::notIn(val1, val2, val3, val4, val5)); } \
className & className::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6) { return static_cast<className &>(qx::QxSqlQuery::notIn(val1, val2, val3, val4, val5, val6)); } \
className & className::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7) { return static_cast<className &>(qx::QxSqlQuery::notIn(val1, val2, val3, val4, val5, val6, val7)); } \
className & className::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8) { return static_cast<className &>(qx::QxSqlQuery::notIn(val1, val2, val3, val4, val5, val6, val7, val8)); } \
className & className::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9) { return static_cast<className &>(qx::QxSqlQuery::notIn(val1, val2, val3, val4, val5, val6, val7, val8, val9)); } \
\
className & className::in_Select(const QString & sql) { return static_cast<className &>(qx::QxSqlQuery::in_Select(sql)); } \
className & className::notIn_Select(const QString & sql) { return static_cast<className &>(qx::QxSqlQuery::notIn_Select(sql)); } \
\
className & className::isNull() { return static_cast<className &>(qx::QxSqlQuery::isNull()); } \
className & className::isNotNull() { return static_cast<className &>(qx::QxSqlQuery::isNotNull()); } \
\
className & className::isBetween(const QVariant & val1, const QVariant & val2) { return static_cast<className &>(qx::QxSqlQuery::isBetween(val1, val2)); } \
className & className::isNotBetween(const QVariant & val1, const QVariant & val2) { return static_cast<className &>(qx::QxSqlQuery::isNotBetween(val1, val2)); } \
\
className & className::freeText(const QString & text) { return static_cast<className &>(qx::QxSqlQuery::freeText(text)); }

#endif // _QX_SQL_QUERY_H_
