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

#include <QxPrecompiled.h>

#include <QxDao/IxDao_Helper.h>

#include <QxRegister/IxClass.h>

#include <QxMemLeak/mem_leak.h>

#define QX_DAO_ERR_INTERNAL                  "[QxOrm] 'qx::dao' internal error"
#define QX_DAO_ERR_UNKNOWN_ERROR             "[QxOrm] 'qx::dao' unknown error"
#define QX_DAO_ERR_NO_CONNECTION             "[QxOrm] error retrieving valid sql connection to database"
#define QX_DAO_ERR_OPEN_CONNECTION           "[QxOrm] unable to open connection to database"
#define QX_DAO_ERR_BUILD_SQL_QUERY           "[QxOrm] error building sql query : %s"
#define QX_DAO_ERR_EXECUTE_SQL_QUERY         "[QxOrm] execute sql query failed : %s"
#define QX_DAO_ERR_PREPARE_SQL_QUERY         "[QxOrm] prepare sql query failed : %s"
#define QX_DAO_ERR_NO_DATA                   "[QxOrm] sql query returns no data"
#define QX_DAO_ERR_NO_QUERY_BUILDER          "[QxOrm] unable to construct sql query builder"
#define QX_DAO_ERR_NO_ELEMENT_IN_CONTAINER   "[QxOrm] no element in container"
#define QX_DAO_ERR_INVALID_PRIMARY_KEY       "[QxOrm] invalid primary key"
#define QX_DAO_ERR_INVALID_SQL_RELATION      "[QxOrm] invalid sql relation"
#define QX_DAO_ERR_INVALID_VALUES_DETECTED   "[QxOrm] validator engine : invalid values detected"
#define QX_DAO_ERR_READ_ONLY                 "[QxOrm] cannot execute INSERT, UPDATE or DELETE query with a read only entity"

#define QX_CONSTRUCT_IX_DAO_HELPER() \
m_timeDatabase(0), m_lDataCount(0), m_bTransaction(false), m_bQuiet(false), \
m_bTraceQuery(true), m_bTraceRecord(false), m_bCartesianProduct(false), \
m_bValidatorThrowable(false), m_pDataMemberX(NULL), m_pDataId(NULL), \
m_pSqlGenerator(NULL)

namespace qx {
namespace dao {
namespace detail {

struct IxDao_Helper::IxDao_HelperImpl
{

   QTime          m_time;                 //!< Time (in ms) to execute query (total time : SQL + fetch C++ classes)
   int            m_timeDatabase;         //!< Time (in ms) to execute SQL query in database
   QSqlDatabase   m_database;             //!< Connection to database to execute query
   QSqlQuery      m_query;                //!< Query to execute
   QSqlError      m_error;                //!< Error executing query
   QString        m_context;              //!< Description of context : fetch, insert, update, delete, etc...
   long           m_lDataCount;           //!< Data member collection count
   bool           m_bTransaction;         //!< Transaction in progress : commit if valid, rollback if error
   bool           m_bQuiet;               //!< Display message and assert in debug mode
   bool           m_bTraceQuery;          //!< Trace sql query
   bool           m_bTraceRecord;         //!< Trace sql record
   bool           m_bCartesianProduct;    //!< Recordset can return cartesian product => same id in multiple records
   bool           m_bValidatorThrowable;  //!< An exception of type qx::validator_error is thrown when invalid values are detected inserting or updating an element into database
   QStringList    m_lstColumns;           //!< List of columns to execute sql query (if empty => all columns)

   qx::IxSqlQueryBuilder_ptr     m_pQueryBuilder;        //!< Sql query builder
   qx::IxDataMemberX *           m_pDataMemberX;         //!< Collection of data member
   qx::IxDataMember *            m_pDataId;              //!< Data member id
   qx::QxSqlQuery                m_qxQuery;              //!< Query sql with place-holder
   IxSqlGenerator *              m_pSqlGenerator;        //!< SQL generator to build SQL query specific for each database
   qx::QxInvalidValueX           m_lstInvalidValues;     //!< List of invalid values using validator engine
   qx::QxSqlRelationLinked_ptr   m_pSqlRelationLinked;   //!< List of relation linked to build a hierarchy of relationships

   IxDao_HelperImpl(qx::IxSqlQueryBuilder * pBuilder) : QX_CONSTRUCT_IX_DAO_HELPER() { m_pQueryBuilder.reset(pBuilder); }
   ~IxDao_HelperImpl() { ; }

};

IxDao_Helper::IxDao_Helper(qx::IxSqlQueryBuilder * pBuilder) : m_pImpl(new IxDao_HelperImpl(pBuilder)) { ; }

IxDao_Helper::~IxDao_Helper() { terminate(); }

bool IxDao_Helper::isValid() const { return (! m_pImpl->m_error.isValid() && m_pImpl->m_pQueryBuilder); }

bool IxDao_Helper::hasFeature(QSqlDriver::DriverFeature ft) const { return (m_pImpl->m_database.driver() ? m_pImpl->m_database.driver()->hasFeature(ft) : false); }

QSqlDatabase & IxDao_Helper::database() { return m_pImpl->m_database; }

const QSqlDatabase & IxDao_Helper::database() const { return m_pImpl->m_database; }

QSqlQuery & IxDao_Helper::query() { return m_pImpl->m_query; }

const QSqlQuery & IxDao_Helper::query() const { return m_pImpl->m_query; }

QSqlError & IxDao_Helper::error() { return m_pImpl->m_error; }

const QSqlError & IxDao_Helper::error() const { return m_pImpl->m_error; }

qx::QxSqlQuery & IxDao_Helper::qxQuery() { return m_pImpl->m_qxQuery; }

const qx::QxSqlQuery & IxDao_Helper::qxQuery() const { return m_pImpl->m_qxQuery; }

qx::IxDataMemberX * IxDao_Helper::getDataMemberX() const { return m_pImpl->m_pDataMemberX; }

long IxDao_Helper::getDataCount() const { return m_pImpl->m_lDataCount; }

qx::IxDataMember * IxDao_Helper::getDataId() const { return m_pImpl->m_pDataId; }

qx::IxDataMember * IxDao_Helper::nextData(long & l) const { return (m_pImpl->m_pQueryBuilder ? m_pImpl->m_pQueryBuilder->nextData(l) : NULL); }

QString IxDao_Helper::sql() const { return (m_pImpl->m_pQueryBuilder ? m_pImpl->m_pQueryBuilder->getSqlQuery() : ""); }

qx::QxSqlRelationLinked * IxDao_Helper::getSqlRelationLinked() const { return m_pImpl->m_pSqlRelationLinked.get(); }

bool IxDao_Helper::getCartesianProduct() const { return m_pImpl->m_bCartesianProduct; }

QStringList IxDao_Helper::getSqlColumns() const { return m_pImpl->m_lstColumns; }

void IxDao_Helper::setSqlColumns(const QStringList & lst) { m_pImpl->m_lstColumns = lst; }

IxSqlGenerator * IxDao_Helper::getSqlGenerator() const { return m_pImpl->m_pSqlGenerator; }

void IxDao_Helper::quiet() { m_pImpl->m_bQuiet = true; }

bool IxDao_Helper::isReadOnly() const { return ((m_pImpl->m_pDataMemberX && m_pImpl->m_pDataMemberX->getClass()) ? m_pImpl->m_pDataMemberX->getClass()->isDaoReadOnly() : false); }

bool IxDao_Helper::getAddAutoIncrementIdToUpdateQuery() const { return qx::QxSqlDatabase::getSingleton()->getAddAutoIncrementIdToUpdateQuery(); }

bool IxDao_Helper::exec()
{
   bool bExec = false; QTime timeDB; timeDB.start();
   if (m_pImpl->m_qxQuery.isEmpty()) { bExec = this->query().exec(this->builder().getSqlQuery()); }
   else { bExec = this->query().exec(); }
   m_pImpl->m_timeDatabase = timeDB.elapsed();
   return bExec;
}

void IxDao_Helper::addInvalidValues(const qx::QxInvalidValueX & lst)
{
   m_pImpl->m_lstInvalidValues.insert(lst);
   if (m_pImpl->m_lstInvalidValues.count() > 0)
   {
      QString sInvalidValues = QX_DAO_ERR_INVALID_VALUES_DETECTED;
      sInvalidValues += QString("\n") + m_pImpl->m_lstInvalidValues.text();
      updateError(sInvalidValues);
      if (m_pImpl->m_bValidatorThrowable) { QString tmp = m_pImpl->m_lstInvalidValues.text(); qDebug("[QxOrm] invalid values detected, throw 'qx::validator_error' exception : '%s'", qPrintable(tmp)); }
      if (m_pImpl->m_bValidatorThrowable) { throw qx::validator_error(m_pImpl->m_lstInvalidValues); }
   }
}

qx::IxSqlQueryBuilder & IxDao_Helper::builder()
{
   qAssert(m_pImpl->m_pQueryBuilder);
   return (* m_pImpl->m_pQueryBuilder);
}

const qx::IxSqlQueryBuilder & IxDao_Helper::builder() const
{
   qAssert(m_pImpl->m_pQueryBuilder);
   return (* m_pImpl->m_pQueryBuilder);
}

QSqlError IxDao_Helper::errFailed(bool bPrepare /* = false */)
{
   QString sql = this->sql();
   if (bPrepare) { qDebug(QX_DAO_ERR_PREPARE_SQL_QUERY, qPrintable(sql)); }
   else { qDebug(QX_DAO_ERR_EXECUTE_SQL_QUERY, qPrintable(sql)); }
   return updateError(m_pImpl->m_query.lastError());
}

QSqlError IxDao_Helper::errEmpty()
{
   QString sql = this->sql();
   qDebug(QX_DAO_ERR_BUILD_SQL_QUERY, qPrintable(sql));
   return updateError(m_pImpl->m_query.lastError());
}

QSqlError IxDao_Helper::errNoData() { return updateError(QX_DAO_ERR_NO_DATA); }

QSqlError IxDao_Helper::errInvalidId() { return updateError(QX_DAO_ERR_INVALID_PRIMARY_KEY); }

QSqlError IxDao_Helper::errInvalidRelation() { return updateError(QX_DAO_ERR_INVALID_SQL_RELATION); }

QSqlError IxDao_Helper::errReadOnly() { return updateError(QX_DAO_ERR_READ_ONLY); }

bool IxDao_Helper::transaction()
{
   if (isValid() && hasFeature(QSqlDriver::Transactions))
   { m_pImpl->m_bTransaction = m_pImpl->m_database.transaction(); }
   return m_pImpl->m_bTransaction;
}

bool IxDao_Helper::nextRecord()
{
   if (! m_pImpl->m_query.next()) { return false; }
   if (m_pImpl->m_bTraceRecord) { dumpRecord(); }
   return true;
}

bool IxDao_Helper::updateSqlRelationX(const QStringList & relation)
{
   m_pImpl->m_bCartesianProduct = false;
   m_pImpl->m_pSqlRelationLinked.reset(new qx::QxSqlRelationLinked());
   qx_bool bBuildOk = m_pImpl->m_pSqlRelationLinked->buildHierarchy(this->builder().getLstRelation(), relation);
   if (! bBuildOk) { m_pImpl->m_pSqlRelationLinked.reset(); }
   if (! bBuildOk) { QString txt = bBuildOk.getDesc(); qDebug("[QxOrm] %s", qPrintable(txt)); return false; }
   m_pImpl->m_bCartesianProduct = m_pImpl->m_pSqlRelationLinked->getCartesianProduct();
   if (m_pImpl->m_pQueryBuilder) { m_pImpl->m_pQueryBuilder->setCartesianProduct(m_pImpl->m_bCartesianProduct); }
   if (m_pImpl->m_pQueryBuilder) { m_pImpl->m_pQueryBuilder->setHashRelation(relation.join("|")); }
   if (m_pImpl->m_bCartesianProduct) { m_pImpl->m_pQueryBuilder->initIdX(m_pImpl->m_pSqlRelationLinked->getAllRelationCount()); }
   return bBuildOk.getValue();
}

void IxDao_Helper::dumpRecord() const
{
   if (! m_pImpl->m_query.isValid()) { return; }
   QString sDump; QVariant v;
   QSqlRecord record = m_pImpl->m_query.record();
   int iCount = record.count();
   if (iCount <= 0) { return; }
   for (int i = 0; i < iCount; ++i)
   { v = record.value(i); sDump += (v.isNull() ? QString("NULL") : v.toString()) + QString("|"); }
   sDump = sDump.left(sDump.count() - 1); // Remove last "|"
   qDebug("[QxOrm] dump sql record : %s", qPrintable(sDump));
}

void IxDao_Helper::addQuery(const qx::QxSqlQuery & query, bool bResolve)
{
   m_pImpl->m_qxQuery = query;
   if (m_pImpl->m_qxQuery.isEmpty()) { return; }
   QString sql = this->builder().getSqlQuery();
   QString sqlToAdd = m_pImpl->m_qxQuery.query().trimmed();
   bool bAddSqlCondition = false;
   if (sqlToAdd.left(6).contains("WHERE ", Qt::CaseInsensitive)) { sqlToAdd = sqlToAdd.right(sqlToAdd.size() - 6); bAddSqlCondition = true; }
   else if (sqlToAdd.left(4).contains("AND ", Qt::CaseInsensitive)) { sqlToAdd = sqlToAdd.right(sqlToAdd.size() - 4); bAddSqlCondition = true; }
   this->builder().replaceSqlQueryAlias(sqlToAdd);
   sql += (bAddSqlCondition ? qx::IxSqlQueryBuilder::addSqlCondition(sql) : QString(" ")) + sqlToAdd;
   if (m_pImpl->m_qxQuery.isDistinct() && sql.left(7).contains("SELECT ", Qt::CaseInsensitive))
   { sql = "SELECT DISTINCT " + sql.right(sql.size() - 7); }
   m_pImpl->m_qxQuery.postProcess(sql);
   this->builder().setSqlQuery(sql);

   if (bResolve)
   {
      if (! this->query().prepare(sql)) { this->errFailed(true); }
      m_pImpl->m_qxQuery.resolve(this->query());
   }
}

QSqlError IxDao_Helper::updateError(const QString & sError)
{
   QString sDriverText = (QX_DAO_ERR_INTERNAL + QString(" <") + m_pImpl->m_context + QString(">"));
   sDriverText += (sql().isEmpty() ? QString("") : (QString(" : ") + sql()));
   QSqlError err = QSqlError(sDriverText, sError, QSqlError::UnknownError);
   return updateError(err);
}

QSqlError IxDao_Helper::updateError(const QSqlError & error)
{
   if (! m_pImpl->m_error.isValid())
   {
      m_pImpl->m_error = error;
      return m_pImpl->m_error;
   }

   if ((error.databaseText() != m_pImpl->m_error.databaseText()) && (! error.databaseText().isEmpty())) { m_pImpl->m_error.setDatabaseText(m_pImpl->m_error.databaseText() + "\n" + error.databaseText()); }
   if ((error.driverText() != m_pImpl->m_error.driverText()) && (! error.driverText().isEmpty())) { m_pImpl->m_error.setDriverText(m_pImpl->m_error.driverText() + "\n" + error.driverText()); }
   if (((m_pImpl->m_error.type() == QSqlError::NoError) || (m_pImpl->m_error.type() == QSqlError::UnknownError)) && (error.type() != QSqlError::NoError)) { m_pImpl->m_error.setType(error.type()); }
   if (m_pImpl->m_error.number() == -1) { m_pImpl->m_error.setNumber(error.number()); }

   return m_pImpl->m_error;
}

void IxDao_Helper::init(QSqlDatabase * pDatabase, const QString & sContext)
{
   m_pImpl->m_time.start();
   m_pImpl->m_context = sContext;
   m_pImpl->m_bTraceQuery = qx::QxSqlDatabase::getSingleton()->getTraceSqlQuery();
   m_pImpl->m_bTraceRecord = qx::QxSqlDatabase::getSingleton()->getTraceSqlRecord();
   qAssert(! m_pImpl->m_context.isEmpty());

   QSqlError dbError;
   m_pImpl->m_database = (pDatabase ? (* pDatabase) : qx::QxSqlDatabase::getDatabase(dbError));
   if (dbError.isValid()) { updateError(dbError); return; }
   if (! m_pImpl->m_database.isValid()) { updateError(QX_DAO_ERR_NO_CONNECTION); return; }
   if (! m_pImpl->m_database.isOpen() && ! m_pImpl->m_database.open()) { updateError(QX_DAO_ERR_OPEN_CONNECTION); return; }
   if (! m_pImpl->m_pQueryBuilder) { updateError(QX_DAO_ERR_NO_QUERY_BUILDER); return; }

   m_pImpl->m_pQueryBuilder->init();
   m_pImpl->m_pQueryBuilder->setDaoHelper(this);
   m_pImpl->m_query = QSqlQuery(m_pImpl->m_database);
   m_pImpl->m_query.setForwardOnly(true);
   m_pImpl->m_pDataMemberX = (m_pImpl->m_pQueryBuilder ? m_pImpl->m_pQueryBuilder->getDataMemberX() : NULL);
   m_pImpl->m_lDataCount = (m_pImpl->m_pQueryBuilder ? m_pImpl->m_pQueryBuilder->getDataCount() : 0);
   m_pImpl->m_pDataId = (m_pImpl->m_pQueryBuilder ? m_pImpl->m_pQueryBuilder->getDataId() : NULL);
   m_pImpl->m_pSqlGenerator = qx::QxSqlDatabase::getSingleton()->getSqlGenerator();
   m_pImpl->m_bValidatorThrowable = qx::QxSqlDatabase::getSingleton()->getValidatorThrowable();
}

void IxDao_Helper::terminate()
{
   if ((m_pImpl->m_lstInvalidValues.count() > 0) && m_pImpl->m_bValidatorThrowable)
   {
      if (m_pImpl->m_bTransaction) { m_pImpl->m_database.rollback(); }
   }
   else if (! isValid())
   {
      if (m_pImpl->m_bTransaction) { m_pImpl->m_database.rollback(); }
      if (! m_pImpl->m_bQuiet) { int ierr = m_pImpl->m_error.number(); QString tmp = m_pImpl->m_error.driverText(); qDebug("Database error number '%d' : %s", ierr, qPrintable(tmp)); tmp = m_pImpl->m_error.databaseText(); qDebug("%s", qPrintable(tmp)); }
   }
   else if (m_pImpl->m_pQueryBuilder)
   {
      if (m_pImpl->m_bTransaction) { m_pImpl->m_database.commit(); }
      if (! m_pImpl->m_bQuiet && m_pImpl->m_bTraceQuery) { m_pImpl->m_pQueryBuilder->displaySqlQuery(m_pImpl->m_time.elapsed(), m_pImpl->m_timeDatabase); }
   }
   else
   {
      if (m_pImpl->m_bTransaction) { m_pImpl->m_database.rollback(); }
      if (! m_pImpl->m_bQuiet) { qDebug("%s", QX_DAO_ERR_UNKNOWN_ERROR); qAssert(false); }
   }

   m_pImpl->m_bTransaction = false;
   dumpBoundValues();
}

void IxDao_Helper::dumpBoundValues() const
{
   qx::QxSqlDatabase * pDatabase = qx::QxSqlDatabase::getSingleton(); if (! pDatabase) { return; }
   bool bBoundValues = pDatabase->getTraceSqlBoundValues();
   bool bBoundValuesOnError = pDatabase->getTraceSqlBoundValuesOnError();

   if ((! isValid() && bBoundValuesOnError) || (bBoundValues))
   { qx::QxSqlQuery::dumpBoundValues(m_pImpl->m_query); }
}

} // namespace detail
} // namespace dao
} // namespace qx
