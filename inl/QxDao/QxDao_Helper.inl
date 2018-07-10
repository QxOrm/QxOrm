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

#define QX_DAO_ERR_INTERNAL                  "[QxOrm] 'qx::dao' internal error"
#define QX_DAO_ERR_UNKNOWN_ERROR             "[QxOrm] 'qx::dao' unknown error"
#define QX_DAO_ERR_NO_CONNECTION             "[QxOrm] error retrieving valid sql connection to database"
#define QX_DAO_ERR_OPEN_CONNECTION           "[QxOrm] unable to open connection to database"
#define QX_DAO_ERR_BUILD_SQL_QUERY           "[QxOrm] error building sql query : %s"
#define QX_DAO_ERR_EXECUTE_SQL_QUERY         "[QxOrm] execute sql query failed : %s"
#define QX_DAO_ERR_NO_DATA                   "[QxOrm] sql query returns no data"
#define QX_DAO_ERR_NO_QUERY_BUILDER          "[QxOrm] unable to construct sql query builder"
#define QX_DAO_ERR_NO_ELEMENT_IN_CONTAINER   "[QxOrm] no element in container"
#define QX_DAO_ERR_INVALID_PRIMARY_KEY       "[QxOrm] invalid primary key"
#define QX_DAO_ERR_INVALID_SQL_RELATION      "[QxOrm] invalid sql relation"

namespace qx {
namespace dao {
namespace detail {

struct IxDao_Helper
{

protected:

   QTime          m_time;                 // Time (in ms) to execute query
   QSqlDatabase   m_database;             // Connection to database to execute query
   QSqlQuery      m_query;                // Query to execute
   QSqlError      m_error;                // Error executing query
   QString        m_context;              // Description of context : fetch, insert, update, delete, etc...
   long           m_lDataCount;           // Data member collection count
   bool           m_bTransaction;         // Transaction in progress : commit if valid, rollback if error
   bool           m_bQuiet;               // Display message and assert in debug mode
   bool           m_bTraceQuery;          // Trace sql query
   bool           m_bTraceRecord;         // Trace sql record
   bool           m_bCartesianProduct;    // Recordset can return cartesian product => same id in multiple records
   QStringList    m_lstColumns;           // List of columns to execute sql query (if empty => all columns)

   qx::IxSqlQueryBuilder_ptr  m_pQueryBuilder;  // Sql query builder
   qx::IxDataMemberX *        m_pDataMemberX;   // Collection of data member
   qx::IxDataMember *         m_pDataId;        // Data member id
   qx::QxSqlQuery             m_qxQuery;        // Query sql with place-holder

   typedef qx::QxCollection<QString, qx::IxSqlRelation *> type_lst_relation;
   typedef boost::scoped_ptr< type_lst_relation > type_lst_relation_ptr;
   type_lst_relation_ptr m_pSqlRelationX;

protected:

   IxDao_Helper() : m_lDataCount(0), m_bTransaction(false), m_bQuiet(false), m_bTraceQuery(true), m_bTraceRecord(false), m_bCartesianProduct(false), m_pDataMemberX(NULL), m_pDataId(NULL) { ; }
   virtual ~IxDao_Helper() { terminate(); }

public:

   inline bool isValid() const                                 { return (! m_error.isValid() && m_pQueryBuilder); }
   inline bool hasFeature(QSqlDriver::DriverFeature ft) const  { return (m_database.driver() ? m_database.driver()->hasFeature(ft) : false); }

   inline QSqlDatabase & database()                            { return m_database; }
   inline const QSqlDatabase & database() const                { return m_database; }
   inline QSqlQuery & query()                                  { return m_query; }
   inline const QSqlQuery & query() const                      { return m_query; }
   inline QSqlError & error()                                  { return m_error; }
   inline const QSqlError & error() const                      { return m_error; }
   inline qx::IxSqlQueryBuilder & builder()                    { qAssert(m_pQueryBuilder); return (* m_pQueryBuilder); }
   inline const qx::IxSqlQueryBuilder & builder() const        { qAssert(m_pQueryBuilder); return (* m_pQueryBuilder); }
   inline qx::IxDataMemberX * getDataMemberX() const           { return m_pDataMemberX; }
   inline long getDataCount() const                            { return m_lDataCount; }
   inline qx::IxDataMember * getDataId() const                 { return m_pDataId; }
   inline qx::IxDataMember * nextData(long & l) const          { return (m_pQueryBuilder ? m_pQueryBuilder->nextData(l) : NULL); }
   inline QString sql() const                                  { return (m_pQueryBuilder ? m_pQueryBuilder->getSqlQuery() : ""); }
   inline type_lst_relation * getSqlRelationX() const          { return m_pSqlRelationX.get(); }
   inline bool getCartesianProduct() const                     { return m_bCartesianProduct; }
   inline QStringList getSqlColumns() const                    { return m_lstColumns; }
   inline void setSqlColumns(const QStringList & lst)          { m_lstColumns = lst; }

   QSqlError errFailed()            { qDebug(QX_DAO_ERR_EXECUTE_SQL_QUERY, qPrintable(sql())); m_error = m_query.lastError(); return m_error; }
   QSqlError errEmpty()             { qDebug(QX_DAO_ERR_BUILD_SQL_QUERY, qPrintable(sql())); m_error = m_query.lastError(); return m_error; }
   QSqlError errNoData()            { updateError(QX_DAO_ERR_NO_DATA); return m_error; }
   QSqlError errInvalidId()         { updateError(QX_DAO_ERR_INVALID_PRIMARY_KEY); return m_error; }
   QSqlError errInvalidRelation()   { updateError(QX_DAO_ERR_INVALID_SQL_RELATION); return m_error; }

   inline bool transaction()                          { if (isValid() && hasFeature(QSqlDriver::Transactions)) { m_bTransaction = m_database.transaction(); }; return m_bTransaction; }
   inline bool nextRecord()                           { if (! m_query.next()) { return false; } if (m_bTraceRecord) { dumpRecord(); } return true; }
   inline void updateError(const QSqlError & error)   { m_error = error; }
   inline void quiet()                                { m_bQuiet = true; }
   inline bool exec()                                 { return (m_qxQuery.isEmpty() ? this->query().exec(this->builder().getSqlQuery()) : this->query().exec()); }

   bool updateSqlRelationX(const QStringList & relation)
   {
      m_bCartesianProduct = false;
      bool bError = false; QString sHashRelation;
      m_pSqlRelationX.reset(new type_lst_relation());
      qx::IxSqlRelationX * pAllRelation = this->builder().getLstRelation();
      if ((relation.count() == 1) && (relation.at(0) == "*")) { sHashRelation = "*"; (* m_pSqlRelationX) = (* pAllRelation); }
      else if (relation.count() == pAllRelation->count()) { sHashRelation = "*"; (* m_pSqlRelationX) = (* pAllRelation); }
      else { Q_FOREACH(QString sKey, relation) { if (pAllRelation->exist(sKey)) { sHashRelation += (sKey + "|"); m_pSqlRelationX->insert(sKey, pAllRelation->getByKey(sKey)); } else { bError = true; } } }
      if (bError || (m_pSqlRelationX->count() <= 0)) { m_pSqlRelationX.reset(NULL); }
      if (m_pSqlRelationX) { _foreach(qx::IxSqlRelation * p, (* m_pSqlRelationX)) { m_bCartesianProduct = (m_bCartesianProduct || p->getCartesianProduct()); } }
      if (! bError && m_pQueryBuilder) { m_pQueryBuilder->setHashRelation(sHashRelation); m_pQueryBuilder->setCartesianProduct(m_bCartesianProduct); }
      return (! bError && (m_pSqlRelationX.get() != NULL));
   }

   void dumpRecord() const
   {
      if (! m_query.isValid()) { return; }
      QString sDump; QVariant v;
      QSqlRecord record = m_query.record();
      int iCount = record.count();
      if (iCount <= 0) { return; }
      for (int i = 0; i < iCount; ++i)
      { v = record.value(i); sDump += (v.isNull() ? QString("NULL") : v.toString()) + QString("|"); }
      sDump = sDump.left(sDump.count() - 1); // Remove last "|"
      qDebug("[QxOrm] dump sql record : %s", qPrintable(sDump));
   }

   void addQuery(const qx::QxSqlQuery & query, bool bResolve)
   {
      m_qxQuery = query;
      if (m_qxQuery.isEmpty()) { return; }
      QString sql = this->builder().getSqlQuery();
      sql += " " + m_qxQuery.query();
      this->builder().setSqlQuery(sql);
      if (bResolve) { this->query().prepare(sql); m_qxQuery.resolve(this->query()); }
   }

   template <class U>
   inline bool isValidPrimaryKey(const U & u)
   { return (m_pDataId && qx::trait::is_valid_primary_key(m_pDataId->toVariant(& u))); }

   template <class U>
   inline void updateLastInsertId(U & u)
   {
      if (m_pDataId && m_pDataId->getAutoIncrement() && this->hasFeature(QSqlDriver::LastInsertId))
      { m_pDataId->fromVariant((& u), m_query.lastInsertId()); }
   }

protected:

   virtual void updateQueryBuilder() { ; }

   QSqlError updateError(const QString & sError)
   {
      m_error = QSqlError((QX_DAO_ERR_INTERNAL + QString(" <") + m_context + QString(">") + (sql().isEmpty() ? QString("") : (QString(" : ") + sql()))), sError, QSqlError::UnknownError);
      return m_error;
   }

   void init(QSqlDatabase * pDatabase, const QString & sContext)
   {
      m_time.start();
      m_context = sContext;
      m_bTraceQuery = qx::QxSqlDatabase::getSingleton()->getTraceSqlQuery();
      m_bTraceRecord = qx::QxSqlDatabase::getSingleton()->getTraceSqlRecord();
      qAssert(! m_context.isEmpty());

      m_database = (pDatabase ? (* pDatabase) : qx::QxSqlDatabase::getDatabase());
      if (! m_database.isValid()) { updateError(QX_DAO_ERR_NO_CONNECTION); return; }
      if (! m_database.isOpen() && ! m_database.open()) { updateError(QX_DAO_ERR_OPEN_CONNECTION); return; }

      updateQueryBuilder();
      if (! m_pQueryBuilder) { updateError(QX_DAO_ERR_NO_QUERY_BUILDER); return; }

      m_pQueryBuilder->init();
      m_query = QSqlQuery(m_database);
      m_query.setForwardOnly(true);
      m_pDataMemberX = (m_pQueryBuilder ? m_pQueryBuilder->getDataMemberX() : NULL);
      m_lDataCount = (m_pQueryBuilder ? m_pQueryBuilder->getDataCount() : 0);
      m_pDataId = (m_pQueryBuilder ? m_pQueryBuilder->getDataId() : NULL);
   }

   void terminate()
   {
      if (! isValid())
      {
         if (m_bTransaction) { m_database.rollback(); }
         if (! m_bQuiet) { qDebug("%s", qPrintable(m_error.driverText())); qDebug("%s", qPrintable(m_error.databaseText())); }
      }
      else if (m_pQueryBuilder)
      {
         if (m_bTransaction) { m_database.commit(); }
         if (! m_bQuiet && m_bTraceQuery) { m_pQueryBuilder->displaySqlQuery(m_time.elapsed()); }
      }
      else
      {
         if (m_bTransaction) { m_database.rollback(); }
         if (! m_bQuiet) { qDebug("%s", QX_DAO_ERR_UNKNOWN_ERROR); qAssert(false); }
      }

      m_bTransaction = false;
   }

};

template <class T>
struct QxDao_Helper : public IxDao_Helper
{

public:

   QxDao_Helper(T & t, QSqlDatabase * pDatabase, const QString & sContext) : IxDao_Helper() { Q_UNUSED(t); init(pDatabase, sContext); }
   virtual ~QxDao_Helper() { BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<typename qx::QxSqlQueryBuilder<T>::type_sql>::value); }

protected:

   virtual void updateQueryBuilder() { m_pQueryBuilder.reset(new qx::QxSqlQueryBuilder<T>()); }

};

template <class T>
struct QxDao_Keep_Original
{ static inline void backup(T & t) { Q_UNUSED(t); } };

template <typename T>
struct QxDao_Keep_Original< qx::dao::ptr<T> >
{ static inline void backup(qx::dao::ptr<T> & t) { if (t) { t.resetOriginal(qx::clone_to_qt_shared_ptr(* t)); } } };

} // namespace qx
} // namespace dao
} // namespace detail

#include "../../inl/QxDao/QxDao_Helper_Container.inl"
