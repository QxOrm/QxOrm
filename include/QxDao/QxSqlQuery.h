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

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

#include <QtSql/qsqlquery.h>

#include <QxCollection/QxCollection.h>

#include <QxDao/QxSqlElement/QxSqlElement.h>

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
 */
class QX_DLL_EXPORT QxSqlQuery
{

protected:

   struct QxSqlResult
   { QHash<QString, int> positionByKey; QVector< QVector<QVariant> > values; };

   typedef boost::tuple<QVariant, QSql::ParamType> type_bind_value;

   QString                                   m_sQuery;               //!< Query SQL with place-holder
   QxCollection<QString, type_bind_value>    m_lstValue;             //!< Bind value in this array
   qx::dao::detail::IxSqlElement_ptr         m_pSqlElementTemp;      //!< Temporary SQL element
   QList<qx::dao::detail::IxSqlElement_ptr>  m_lstSqlElement;        //!< List of all SQL elements to build SQL query
   int                                       m_iSqlElementIndex;     //!< Current index of SQL element
   int                                       m_iParenthesisCount;    //!< Current parenthesis count
   bool                                      m_bDistinct;            //!< Replace SELECT by SELECT DISTINCT in SQL query
   boost::shared_ptr<QxSqlResult>            m_pSqlResult;           //!< All results returning by SQL query or stored procedure (after calling qx::dao::call_query function)

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

private:

#ifndef NDEBUG
   void verifyQuery() const;
#else
   inline void verifyQuery() const { ; }
#endif // NDEBUG

   void fetchSqlResult(QSqlQuery & query);

public:

   /* -- All methods to build SQL query using C++ syntax -- */

   QxSqlQuery & distinct();

   QxSqlQuery & where(const QString & column);
   QxSqlQuery & where_OpenParenthesis(const QString & column);
   QxSqlQuery & and_(const QString & column);
   QxSqlQuery & and_OpenParenthesis(const QString & column);
   QxSqlQuery & or_(const QString & column);
   QxSqlQuery & or_OpenParenthesis(const QString & column);

   QxSqlQuery & openParenthesis();
   QxSqlQuery & closeParenthesis();

   QxSqlQuery & orderAsc(const QStringList & columns);
   QxSqlQuery & orderAsc(const QString & col1);
   QxSqlQuery & orderAsc(const QString & col1, const QString & col2);
   QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3);
   QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4);
   QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5);
   QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6);
   QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7);
   QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8);
   QxSqlQuery & orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9);

   QxSqlQuery & orderDesc(const QStringList & columns);
   QxSqlQuery & orderDesc(const QString & col1);
   QxSqlQuery & orderDesc(const QString & col1, const QString & col2);
   QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3);
   QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4);
   QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5);
   QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6);
   QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7);
   QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8);
   QxSqlQuery & orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9);

   QxSqlQuery & groupBy(const QStringList & columns);
   QxSqlQuery & groupBy(const QString & col1);
   QxSqlQuery & groupBy(const QString & col1, const QString & col2);
   QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3);
   QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4);
   QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5);
   QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6);
   QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7);
   QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8);
   QxSqlQuery & groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9);

   QxSqlQuery & limit(int rowsCount, int startRow = 0);

   QxSqlQuery & like(const QString & val);
   QxSqlQuery & notLike(const QString & val);
   QxSqlQuery & startsWith(const QString & val);
   QxSqlQuery & endsWith(const QString & val);
   QxSqlQuery & containsString(const QString & val);

   QxSqlQuery & isEqualTo(const QVariant & val);
   QxSqlQuery & isNotEqualTo(const QVariant & val);
   QxSqlQuery & isGreaterThan(const QVariant & val);
   QxSqlQuery & isGreaterThanOrEqualTo(const QVariant & val);
   QxSqlQuery & isLessThan(const QVariant & val);
   QxSqlQuery & isLessThanOrEqualTo(const QVariant & val);

   QxSqlQuery & in(const QVariantList & values);
   QxSqlQuery & in(const QVariant & val1);
   QxSqlQuery & in(const QVariant & val1, const QVariant & val2);
   QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3);
   QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4);
   QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5);
   QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6);
   QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7);
   QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8);
   QxSqlQuery & in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9);

   QxSqlQuery & notIn(const QVariantList & values);
   QxSqlQuery & notIn(const QVariant & val1);
   QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2);
   QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3);
   QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4);
   QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5);
   QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6);
   QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7);
   QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8);
   QxSqlQuery & notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9);

   QxSqlQuery & in_Select(const QString & sql);
   QxSqlQuery & notIn_Select(const QString & sql);

   QxSqlQuery & isNull();
   QxSqlQuery & isNotNull();

   QxSqlQuery & isBetween(const QVariant & val1, const QVariant & val2);
   QxSqlQuery & isNotBetween(const QVariant & val1, const QVariant & val2);

   QxSqlQuery & freeText(const QString & text);

private:

   QxSqlQuery & addSqlExpression(const QString & column, qx::dao::detail::QxSqlExpression::type type);
   QxSqlQuery & addSqlCompare(const QVariant & val, qx::dao::detail::QxSqlCompare::type type);
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

} // namespace dao
} // namespace qx

#endif // _QX_SQL_QUERY_H_
