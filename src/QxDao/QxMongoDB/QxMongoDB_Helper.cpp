/****************************************************************************
**
** https://www.qxorm.com/
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

#ifdef _QX_ENABLE_MONGODB

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

#include <bson.h>
#include <mongoc.h>

#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#if (QT_VERSION >= 0x051200)
#include <QtCore/qregularexpression.h>
#else // (QT_VERSION >= 0x051200)
#include <QtCore/qregexp.h>
#endif // (QT_VERSION >= 0x051200)

#include <QxPrecompiled.h>

#include <QxDao/QxMongoDB/QxMongoDB_Helper.h>
#include <QxDao/QxSqlDatabase.h>
#include <QxDao/IxDao_Helper.h>
#include <QxDao/QxSqlQuery.h>

#include <QxRegister/IxClass.h>
#include <QxRegister/QxClassX.h>

#include <QxSerialize/QJson/QxSerializeQJson_QVariantMap.h>
#include <QxSerialize/QxSerializeQJson.h>

QX_DLL_EXPORT_QX_SINGLETON_CPP(qx::dao::mongodb::QxMongoDB_Helper)

namespace qx {
namespace dao {
namespace mongodb {

struct qx_engine { ; };
struct qx_reply { ; };
struct qx_opts { ; };

template <class T>
struct qx_scoped_wrapper { ; };

template <>
struct qx_scoped_wrapper<qx::dao::mongodb::qx_engine>
{
   qx_scoped_wrapper<qx::dao::mongodb::qx_engine>() { mongoc_init(); }
   ~qx_scoped_wrapper<qx::dao::mongodb::qx_engine>() { mongoc_cleanup(); }
};

template <>
struct qx_scoped_wrapper<mongoc_uri_t>
{
   mongoc_uri_t * m_uri;
   qx_scoped_wrapper<mongoc_uri_t>(const std::string & uri) : m_uri(NULL) { m_uri = mongoc_uri_new(uri.c_str()); }
   ~qx_scoped_wrapper<mongoc_uri_t>() { if (m_uri) { mongoc_uri_destroy(m_uri); } }
   mongoc_uri_t * get() { return m_uri; }
};

template <>
struct qx_scoped_wrapper<mongoc_client_pool_t>
{
   mongoc_client_pool_t * m_pool;
   qx_scoped_wrapper<mongoc_client_pool_t>(mongoc_uri_t * uri) : m_pool(NULL) { if (uri) { m_pool = mongoc_client_pool_new(uri); }; }
   ~qx_scoped_wrapper<mongoc_client_pool_t>() { if (m_pool) { mongoc_client_pool_destroy(m_pool); } }
   mongoc_client_pool_t * get() { return m_pool; }
};

template <>
struct qx_scoped_wrapper<mongoc_client_t>
{
   mongoc_client_t * m_client;
   mongoc_client_pool_t * m_pool;
   qx_scoped_wrapper<mongoc_client_t>(mongoc_client_pool_t * pool) : m_client(NULL), m_pool(pool) { if (m_pool) { m_client = mongoc_client_pool_pop(m_pool); }; }
   ~qx_scoped_wrapper<mongoc_client_t>() { if (m_pool && m_client) { mongoc_client_pool_push(m_pool, m_client); } }
   mongoc_client_t * get() { return m_client; }
};

template <>
struct qx_scoped_wrapper<mongoc_database_t>
{
   mongoc_database_t * m_db;
   qx_scoped_wrapper<mongoc_database_t>(mongoc_client_t * client, const std::string & name) : m_db(NULL) { if (client) { m_db = mongoc_client_get_database(client, name.c_str()); }; }
   ~qx_scoped_wrapper<mongoc_database_t>() { if (m_db) { mongoc_database_destroy(m_db); } }
   mongoc_database_t * get() { return m_db; }
};

template <>
struct qx_scoped_wrapper<mongoc_collection_t>
{
   mongoc_collection_t * m_collection;
   qx_scoped_wrapper<mongoc_collection_t>(mongoc_client_t * client, const std::string & db, const std::string & name) : m_collection(NULL) { if (client) { m_collection = mongoc_client_get_collection(client, db.c_str(), name.c_str()); }; }
   ~qx_scoped_wrapper<mongoc_collection_t>() { if (m_collection) { mongoc_collection_destroy(m_collection); } }
   mongoc_collection_t * get() { return m_collection; }
};

template <>
struct qx_scoped_wrapper<mongoc_cursor_t>
{
   mongoc_cursor_t * m_cursor;
   qx_scoped_wrapper<mongoc_cursor_t>(mongoc_cursor_t * cursor) : m_cursor(cursor) { ; }
   ~qx_scoped_wrapper<mongoc_cursor_t>() { if (m_cursor) { mongoc_cursor_destroy(m_cursor); } }
   mongoc_cursor_t * get() { return m_cursor; }
};

template <>
struct qx_scoped_wrapper<bson_t>
{
   bson_t * m_doc;
   bson_error_t m_err;
   qx_scoped_wrapper<bson_t>(bson_t * doc) : m_doc(doc) { ; }
   qx_scoped_wrapper<bson_t>(const std::string & json) : m_doc(NULL) { if (json.empty()) { m_doc = bson_new(); } else { m_doc = bson_new_from_json((const uint8_t *)(json.c_str()), -1, (& m_err)); } }
   ~qx_scoped_wrapper<bson_t>() { if (m_doc) { bson_destroy(m_doc); } }
   bson_error_t * err() { return (& m_err); }
   bson_t * get() { return m_doc; }
};

template <>
struct qx_scoped_wrapper< std::vector<bson_t> >
{
   bson_error_t m_err;
   std::vector<bson_t *> m_docs;
   qx_scoped_wrapper< std::vector<bson_t> >(int size) { m_docs.reserve(size); }
   ~qx_scoped_wrapper< std::vector<bson_t> >() { for (bson_t * doc : m_docs) { if (doc) { bson_destroy(doc); } } }
   bool append(const std::string & json) { if (! json.empty()) { bson_t * doc = bson_new_from_json((const uint8_t *)(json.c_str()), -1, (& m_err)); if (doc) { m_docs.push_back(doc); return true; } }; return false; }
   std::vector<bson_t *> * get() { return (& m_docs); }
   bson_error_t * err() { return (& m_err); }
};

template <>
struct qx_scoped_wrapper<mongoc_bulk_operation_t>
{
   mongoc_bulk_operation_t * m_bulk;
   qx_scoped_wrapper<mongoc_bulk_operation_t>(mongoc_collection_t * coll, const bson_t * opts) : m_bulk(NULL) { if (coll) { m_bulk = mongoc_collection_create_bulk_operation_with_opts(coll, opts); } }
   ~qx_scoped_wrapper<mongoc_bulk_operation_t>() { if (m_bulk) { mongoc_bulk_operation_destroy(m_bulk); } }
   mongoc_bulk_operation_t * get() { return m_bulk; }
};

template <>
struct qx_scoped_wrapper<qx::dao::mongodb::qx_opts>
{
   bson_t * m_opts;
   bson_error_t m_err;
   qx_scoped_wrapper<qx::dao::mongodb::qx_opts>(const std::string & json) : m_opts(NULL) { if (! json.empty()) { m_opts = bson_new_from_json((const uint8_t *)(json.c_str()), -1, (& m_err)); } }
   ~qx_scoped_wrapper<qx::dao::mongodb::qx_opts>() { if (m_opts) { bson_destroy(m_opts); } }
   const bson_t * get() const { return const_cast<const bson_t *>(m_opts); }
   bson_error_t * err() { return (& m_err); }
};
typedef std::unique_ptr< qx_scoped_wrapper<qx::dao::mongodb::qx_opts> > qx_opts_ptr;

template <>
struct qx_scoped_wrapper<qx::dao::mongodb::qx_reply>
{
   bson_t m_reply; bool m_destroy;
   QString m_json; QVariantMap m_values;
   qx_scoped_wrapper<qx::dao::mongodb::qx_reply>() : m_destroy(true) { ; }
   ~qx_scoped_wrapper<qx::dao::mongodb::qx_reply>() { if (m_destroy) { bson_destroy(& m_reply); } }
   QString toString() { if (! m_json.isEmpty()) { return m_json; }; char * s = bson_as_relaxed_extended_json((& m_reply), NULL); m_json = QString(s); bson_free(s); return m_json; }
   QVariantMap & values() { if (m_values.isEmpty()) { QString txt = toString(); qx::serialization::json::from_string(m_values, txt); }; return m_values; }
   QVariant value(const QString & key) { return (values().contains(key) ? values().value(key) : QVariant()); }
   void log() { QString txt = toString(); qDebug("[QxOrm] MongoDB database reply : %s", qPrintable(txt)); }
   bson_t * get() { return (& m_reply); }
};
typedef std::unique_ptr< qx_scoped_wrapper<qx::dao::mongodb::qx_reply> > qx_reply_ptr;

struct qx_db_collection
{
   std::shared_ptr<qx_scoped_wrapper<mongoc_client_t> > client;
   std::shared_ptr<qx_scoped_wrapper<mongoc_database_t> > db;
   std::shared_ptr<qx_scoped_wrapper<mongoc_collection_t> > collection;
};

struct Q_DECL_HIDDEN QxMongoDB_Helper::QxMongoDB_HelperImpl
{

   QMutex m_oDbMutex;                                                                  //!< Mutex => 'QxMongoDB_Helper' is thread-safe
   std::unique_ptr<qx_scoped_wrapper<qx::dao::mongodb::qx_engine> > m_pInstance;       //!< MongoDB database driver instance
   std::unique_ptr<qx_scoped_wrapper<mongoc_uri_t> > m_pUri;                           //!< MongoDB database uri (connection string)
   std::unique_ptr<qx_scoped_wrapper<mongoc_client_pool_t> > m_pPool;                  //!< MongoDB database pool to get client connections
   QHash<int, QString> m_lstOpts;                                                      //!< MongoDB database options per action (based on QxMongoDB_Helper::opts enum)
   bool m_bLogDatabaseReply;                                                           //!< Log MongoDB database replies
   bool m_bLogDatabaseInfo;                                                            //!< Log MongoDB database info (ping, server name, etc...)

#if (QT_VERSION >= 0x051200)
   QRegularExpression m_regExpCheckNumber;                                             //!< Regular expression to check if a string contains only numbers
#endif // (QT_VERSION >= 0x051200)

#if (QT_VERSION >= 0x051200)
   QxMongoDB_HelperImpl() : m_bLogDatabaseReply(false), m_bLogDatabaseInfo(true) { m_pInstance.reset(new qx_scoped_wrapper<qx::dao::mongodb::qx_engine>()); m_regExpCheckNumber = QRegularExpression(QRegularExpression::anchoredPattern("\\d*")); }
#else // (QT_VERSION >= 0x051200)
   QxMongoDB_HelperImpl() : m_bLogDatabaseReply(false), m_bLogDatabaseInfo(true) { m_pInstance.reset(new qx_scoped_wrapper<qx::dao::mongodb::qx_engine>()); }
#endif // (QT_VERSION >= 0x051200)
   ~QxMongoDB_HelperImpl() { m_pPool.reset(); m_pUri.reset(); m_pInstance.reset(); }

   QSqlError insertOne_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, QString & insertedId);
   QSqlError insertMany_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, QStringList & insertedId);
   QSqlError updateOne_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, const qx::QxSqlQuery * query);
   QSqlError updateMany_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, const qx::QxSqlQuery * query);
   QSqlError deleteOne_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, const qx::QxSqlQuery * query);
   QSqlError deleteMany_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, const qx::QxSqlQuery * query);
   QSqlError findOne_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QString & json, const qx::QxSqlQuery * query);
   QSqlError findMany_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QStringList & json, const qx::QxSqlQuery * query, QxMongoDB_Fetcher * pFetcher);
   QSqlError aggregate_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QStringList & json, const qx::QxSqlQuery * query, const QString & lookup, QxMongoDB_Fetcher * pFetcher, bool bModeDelete = false);
   QSqlError count_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, long & cnt, const qx::QxSqlQuery * query);
   QSqlError executeCommand_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, qx::QxSqlQuery * query);

   QSqlError initPool()
   {
      {
         if (m_pPool) { return QSqlError(); }
         QMutexLocker locker(& m_oDbMutex);
         if (m_pPool) { return QSqlError(); }

         QString uri;
         qx::QxSqlDatabase * db = qx::QxSqlDatabase::getSingleton();
         int port = db->getPort(); if (port == -1) { port = 27017; }
         if (! db->getUserName().isEmpty()) { uri += db->getUserName(); }
         if (! db->getUserName().isEmpty() && ! db->getPassword().isEmpty()) { uri += ":" + db->getPassword() + "@"; }
         if (! db->getHostName().isEmpty()) { uri += db->getHostName() + ":" + QString::number(port); }
         if (! db->getConnectOptions().isEmpty()) { uri += "/?" + db->getConnectOptions(); }
         if (! uri.isEmpty()) { uri = "mongodb://" + uri; }
         if (uri.isEmpty()) { return QSqlError("[QxOrm] Please define a connection string to a MongoDB database through 'qx::QxSqlDatabase::getSingleton()' settings", "", QSqlError::UnknownError); }
         if (m_bLogDatabaseInfo) { qDebug("[QxOrm] Connect to MongoDB database : %s", qPrintable(uri)); }

         std::string uri_ = toStdString(uri);
         m_pUri.reset(new qx_scoped_wrapper<mongoc_uri_t>(uri_));
         if (! m_pUri->get()) { m_pUri.reset(); return QSqlError("[QxOrm] Unable to create a 'mongoc_uri_t' instance to connect to MongoDB database (" + uri + ")", "", QSqlError::UnknownError); }
         m_pPool.reset(new qx_scoped_wrapper<mongoc_client_pool_t>(m_pUri->get()));
         if (! m_pPool->get()) { m_pPool.reset(); m_pUri.reset(); return QSqlError("[QxOrm] Unable to create a 'mongoc_client_pool_t' instance to connect to MongoDB database (" + uri + ")", "", QSqlError::UnknownError); }
      }

#ifdef Q_COMPILER_INITIALIZER_LISTS
      qx_query ping{ { "ping", 1 } };
#else // Q_COMPILER_INITIALIZER_LISTS
      qx_query ping("{ \"ping\": 1 }");
#endif // Q_COMPILER_INITIALIZER_LISTS
      QSqlError err = executeCommand_(NULL, NULL, (& ping));
      if (err.isValid()) { m_pPool.reset(); m_pUri.reset(); return err; }
      else { if (m_bLogDatabaseInfo) { qDebug("[QxOrm] Ping to MongoDB database server : %s", "OK"); } }

#ifdef Q_COMPILER_INITIALIZER_LISTS
      qx_query buildInfo{ { "buildInfo", 1 } };
#else // Q_COMPILER_INITIALIZER_LISTS
      qx_query buildInfo("{ \"buildInfo\": 1 }");
#endif // Q_COMPILER_INITIALIZER_LISTS
      err = executeCommand_(NULL, NULL, (& buildInfo));
      if (err.isValid()) { m_pPool.reset(); m_pUri.reset(); return err; }
      else { if (m_bLogDatabaseInfo) { QString resp = buildInfo.response().toString(); qDebug("[QxOrm] Fetch build info from MongoDB database server : \n%s", qPrintable(resp)); } }

      return QSqlError();
   }

   QSqlError initCollection(qx::IxClass * pClass, qx_db_collection & coll)
   {
      if (! pClass) { return QSqlError("[QxOrm] Parameter 'qx::IxClass' is required to get MongoDB database collection name", "", QSqlError::UnknownError); }
      QSqlError err = initDatabase(coll); if (err.isValid()) { return err; }
      std::string dbName = toStdString(qx::QxSqlDatabase::getSingleton()->getDatabaseName());
      coll.collection = std::make_shared<qx_scoped_wrapper<mongoc_collection_t> >(coll.client->get(), dbName, toStdString(pClass->getName()));
      if (! coll.collection->get()) { return QSqlError("[QxOrm] Unable to create a 'mongoc_collection_t' instance from MongoDB database (" + qx::QxSqlDatabase::getSingleton()->getDatabaseName() + " - " + pClass->getName() + ")", "", QSqlError::UnknownError); }
      return QSqlError();
   }

   QSqlError initDatabase(qx_db_collection & coll)
   {
      QSqlError err = initPool(); if (err.isValid()) { return err; }
      coll.client = std::make_shared<qx_scoped_wrapper<mongoc_client_t> >(m_pPool->get());
      if (! coll.client->get()) { return QSqlError("[QxOrm] Unable to get a MongoDB client connection from pool of type 'mongoc_client_t'", "", QSqlError::UnknownError); }
      std::string dbName = toStdString(qx::QxSqlDatabase::getSingleton()->getDatabaseName());
      if (dbName.empty()) { return QSqlError("[QxOrm] Unable to connect to MongoDB database : please define a database name using qx::QxSqlDatabase::getSingleton()->setDatabaseName()", "", QSqlError::UnknownError); }
      coll.db = std::make_shared<qx_scoped_wrapper<mongoc_database_t> >(coll.client->get(), dbName);
      if (! coll.db->get()) { return QSqlError("[QxOrm] Unable to create a 'mongoc_database_t' instance from MongoDB database (" + qx::QxSqlDatabase::getSingleton()->getDatabaseName() + ")", "", QSqlError::UnknownError); }
      return QSqlError();
   }

   std::string toStdString(const QString & s) const
   {
#ifndef QT_NO_STL
      return s.toStdString();
#else // QT_NO_STL
      return s.toLatin1().constData();
#endif // QT_NO_STL
   }

   QString asJson(const QString & s) const
   {
#if (QT_VERSION >= 0x051200)
      QString json = s; bool isNumber = m_regExpCheckNumber.match(s).hasMatch();
#else // (QT_VERSION >= 0x051200)
      QString json = s; QRegExp regexp("\\d*"); bool isNumber = regexp.exactMatch(s);
#endif // (QT_VERSION >= 0x051200)
      if (s.startsWith("qx_oid:")) { return "{ \"$oid\": \"" + s.right(s.size() - 7) + "\" }"; }
      return ((isNumber ? QString() : QString("\"")) + json.replace("\"", "\\\"") + (isNumber ? QString() : QString("\"")));
   }

   QSqlError checkInsertOID(bson_t * doc, qx::IxClass * pClass, QString & insertedId)
   {
      bson_iter_t itr;
      if (! bson_iter_init_find((& itr), doc, "_id"))
      {
         bson_oid_t oid; bson_oid_init((& oid), NULL);
         if (! bson_append_oid(doc, "_id", -1, (& oid))) { return QSqlError("[QxOrm] Unable to append 'bson_oid_t' to document (" + pClass->getName() + ")", "", QSqlError::UnknownError); }
         char str[25]; bson_oid_to_string((& oid), str); insertedId = "qx_oid:" + QString(str);
      }
      return QSqlError();
   }

   bool setOptions_(QxMongoDB_Helper::opts e, const QString & optsAsJson)
   {
      int i = static_cast<int>(e);
      if (optsAsJson.isEmpty()) { m_lstOpts.remove(i); return true; }
      m_lstOpts.insert(i, optsAsJson);
      return true;
   }

   QSqlError getOptions_(QxMongoDB_Helper::opts e, qx_opts_ptr & opts, const QString & customOpts = QString())
   {
      opts.reset(); int i = static_cast<int>(e);
      QString json = (customOpts.isEmpty() ? m_lstOpts.value(i) : customOpts); if (json.isEmpty()) { return QSqlError(); }
      opts.reset(new qx_scoped_wrapper<qx::dao::mongodb::qx_opts>(toStdString(json)));
      if (! opts->get()) { QString msg(opts->err()->message); opts.reset(); return QSqlError("[QxOrm] Unable to create a 'bson_t' options instance (" + QString::number(i) + " - " + json + ") from JSON : " + msg, "", QSqlError::UnknownError); }
      return QSqlError();
   }

   QString buildLookup(qx::dao::detail::IxDao_Helper * pDaoHelper, bool idAsArray, qx::QxSqlRelationLinked * pSubHierarchy = NULL, const QString & sTab = QString("\t"), QStringList * pSubFieldsAs = NULL)
   {
      qx::QxSqlRelationLinked * pHierarchy = (pSubHierarchy ? pSubHierarchy : (pDaoHelper ? pDaoHelper->getSqlRelationLinked() : NULL)); if (! pHierarchy) { return QString(); }
      QString templFrom = "\n\t" + sTab + "\"from\": \"%COLL_TARGET%\"";
      QString templLet = "\n\t" + sTab + "\"let\": { \"%COLL_LET_KEY%\": \"$%COLL_LET_VAL%\" }";
      QString templPipeline = "\n\t" + sTab + "\"pipeline\": [ { \"$match\": { \"$expr\": { \"$" + (idAsArray ? QString("in") : QString("eq")) + "\": [ \"$%COLL_EQ%\", \"$$%COLL_LET_KEY%\" ] } } } %NEXT_LEVEL_LOOKUP% %PROJECTION% ]";
      QString templAs = "\n\t" + sTab + "\"as\": \"%COLL_AS%\"";
      QString templOneToMany = "\n" + sTab + "{ \"$lookup\": { " + templFrom + ", " + templLet + ", " + templPipeline + ", " + templAs + " } }";
      QString templManyToOne = templOneToMany + ",\n" + sTab + "{ \"$addFields\": { \"%COLL_AS%\": { \"$arrayElemAt\": [ \"$%COLL_AS%\", 0 ] } } }";
      QString templOneToOne = templManyToOne;
      qx::QxSqlRelationLinked::type_lst_relation_linked pRelationsLinked = pHierarchy->getRelationLinkedX();
      qx::QxSqlRelationLinked::type_lst_relation pRelations = pHierarchy->getRelationX();
      QString result; QStringList projectionFields; QStringList subProjectionFields;

      for (auto itr = pRelations.begin(); itr != pRelations.end(); ++itr)
      {
         const QxSqlRelationLinked::type_relation & item = itr->second;
         qx::IxSqlRelation * pRelation = std::get<1>(item); if (! pRelation) { continue; }
         qx::IxSqlRelation::relation_type type = pRelation->getRelationType();
         if ((type != qx::IxSqlRelation::many_to_one) && (type != qx::IxSqlRelation::one_to_many) && (type != qx::IxSqlRelation::one_to_one)) { continue; }
         qx::IxDataMember * pDataMember = pRelation->getDataMember(); if (! pDataMember) { continue; }
         qx::IxDataMember * pFromId = pRelation->getDataIdOwner(); if (! pFromId) { continue; }
         qx::IxDataMember * pTargetId = pRelation->getDataId(); if (! pTargetId) { continue; }
         qx::IxClass * pFrom = pRelation->getClassOwner(); if (! pFrom) { continue; }
         qx::IxClass * pTarget = pRelation->getClass(); if (! pTarget) { continue; }
         qx::QxSqlRelationLinked::type_ptr pRelationLinked = pRelationsLinked.value(pRelation->getKey());
         QString subLookup = (pRelationLinked ? buildLookup(pDaoHelper, false, pRelationLinked.get(), (sTab + "\t"), (& subProjectionFields)) : QString());
         if (! subLookup.isEmpty()) { subLookup = ", " + subLookup; }

         QString lookup = ((type == qx::IxSqlRelation::many_to_one) ? templManyToOne : ((type == qx::IxSqlRelation::one_to_many) ? templOneToMany : templOneToOne));
         lookup.replace("%COLL_TARGET%", pTarget->getName());
         lookup.replace("%NEXT_LEVEL_LOOKUP%", subLookup);
         lookup.replace("%COLL_AS%", pDataMember->getKey());
         if (pSubFieldsAs) { (* pSubFieldsAs) << pDataMember->getKey(); }
         else { projectionFields << pDataMember->getKey(); }

         if (type == qx::IxSqlRelation::many_to_one)
         {
            lookup.replace("%COLL_LET_KEY%", pDataMember->getKey());
            lookup.replace("%COLL_LET_VAL%", pDataMember->getKey());
            lookup.replace("%COLL_EQ%", "_id");
         }
         else if (type == qx::IxSqlRelation::one_to_many)
         {
            lookup.replace("%COLL_LET_KEY%", pRelation->getForeignKey());
            lookup.replace("%COLL_LET_VAL%", "_id");
            lookup.replace("%COLL_EQ%", pRelation->getForeignKey());
         }
         else if (type == qx::IxSqlRelation::one_to_one)
         {
            lookup.replace("%COLL_LET_KEY%", pDataMember->getKey());
            lookup.replace("%COLL_LET_VAL%", pDataMember->getKey());
            lookup.replace("%COLL_EQ%", "_id");
         }

         QString projection;
         QSet<QString> columns = std::get<2>(item).first;
         if (columns.count() > 0)
         {
            long l = 0; qx::IxDataMember * p = NULL;
            while ((p = pRelation->nextData(l))) { if (p && columns.contains(p->getKey())) { projection += ((projection.isEmpty() ? QString("\"") : QString(", \"")) + p->getKey() + "\": 1"); } }
            if (! projection.isEmpty()) { Q_FOREACH(QString s, subProjectionFields) { projection += ((projection.isEmpty() ? QString("\"") : QString(", \"")) + s + "\": 1"); } }
            if (! projection.isEmpty()) { projection = ",\n\t" + sTab + "{ \"$project\": { " + projection + " } }"; }
         }
         lookup.replace("%PROJECTION%", projection);

         result += ((result.isEmpty() ? QString() : QString(", ")) + lookup);
      }

      QString project;
      if (pDaoHelper && pHierarchy && ! pSubHierarchy && ! result.isEmpty())
      {
         long l = 0; qx::IxDataMember * p = NULL; bool bIncludeAllFields = true;
         while ((p = pDaoHelper->builder().nextData(l))) { if (p && pHierarchy->checkRootColumns(p->getKey())) { project += ((project.isEmpty() ? QString("\"") : QString(", \"")) + p->getKey() + "\": 1"); } else { bIncludeAllFields = false; } }
         if (! project.isEmpty()) { Q_FOREACH(QString s, projectionFields) { project += ((project.isEmpty() ? QString("\"") : QString(", \"")) + s + "\": 1"); } }
         if (! project.isEmpty()) { project = ",\n" + sTab + "{ \"$project\": { " + project + " } }"; }
         if (bIncludeAllFields) { project = ""; }
      }

      return (result + project);
   }

};

QxMongoDB_Fetcher::QxMongoDB_Fetcher() { ; }

QxMongoDB_Fetcher::~QxMongoDB_Fetcher() { ; }

QxMongoDB_Helper::QxMongoDB_Helper() : QxSingleton<QxMongoDB_Helper>("qx::dao::mongodb::QxMongoDB_Helper"), m_pImpl(new QxMongoDB_HelperImpl()) { ; }

QxMongoDB_Helper::~QxMongoDB_Helper() { ; }

QSqlError QxMongoDB_Helper::insertOne(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, QString & insertedId)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->insertOne_(pDaoHelper, pClass, json, insertedId);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::insertOne_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, QString & insertedId)
{
   if (json.count() <= 0) { return QSqlError(); }
   qx_db_collection coll; QSqlError err = initCollection(pClass, coll); if (err.isValid()) { return err; }
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB insert one '" + (pClass ? pClass->getName() : QString()) + "' :\n" + json); }

   qx_scoped_wrapper<bson_t> doc(toStdString(json));
   if (! doc.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document instance (" + pClass->getName() + ") from JSON : " + QString(doc.err()->message), "", QSqlError::UnknownError); }
   err = checkInsertOID(doc.get(), pClass, insertedId); if (err.isValid()) { return err; }

   bson_error_t bsonError; qx_opts_ptr opts; qx_reply_ptr reply;
   if (m_bLogDatabaseReply) { reply.reset(new qx_scoped_wrapper<qx::dao::mongodb::qx_reply>()); }
   err = getOptions_(QxMongoDB_Helper::opts_collection_insert_one, opts); if (err.isValid()) { return err; }
   bool ok = mongoc_collection_insert_one(coll.collection->get(), doc.get(), (opts ? opts->get() : NULL), (reply ? reply->get() : NULL), (& bsonError));
   if (! ok) { return QSqlError("[QxOrm] Unable to insert one 'bson_t' document (" + pClass->getName() + ") to MongoDB database : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   if (reply) { reply->log(); }
   return QSqlError();
}

QSqlError QxMongoDB_Helper::insertMany(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, QStringList & insertedId)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->insertMany_(pDaoHelper, pClass, json, insertedId);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::insertMany_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, QStringList & insertedId)
{
   if (json.count() <= 0) { return QSqlError(); }
   qx_db_collection coll; QSqlError err = initCollection(pClass, coll); if (err.isValid()) { return err; }
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB insert many '" + (pClass ? pClass->getName() : QString()) + "' :\n" + json.join(", \n")); }
   insertedId.clear(); insertedId.reserve(json.count());

   qx_scoped_wrapper< std::vector<bson_t> > docs(json.count());
   Q_FOREACH(QString s, json)
   {
      if (s.isEmpty()) { continue; }
      if (! docs.append(toStdString(s))) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document instance (" + pClass->getName() + ") from JSON : " + QString(docs.err()->message), "", QSqlError::UnknownError); }
      QString oid; err = checkInsertOID(docs.m_docs.back(), pClass, oid); if (err.isValid()) { return err; }; insertedId.append(oid);
   }

   bson_error_t bsonError; qx_opts_ptr opts; qx_reply_ptr reply;
   const bson_t ** docs_ = const_cast<const bson_t **>(docs.get()->data());
   if (m_bLogDatabaseReply) { reply.reset(new qx_scoped_wrapper<qx::dao::mongodb::qx_reply>()); }
   err = getOptions_(QxMongoDB_Helper::opts_collection_insert_many, opts); if (err.isValid()) { return err; }
   bool ok = mongoc_collection_insert_many(coll.collection->get(), docs_, docs.get()->size(), (opts ? opts->get() : NULL), (reply ? reply->get() : NULL), (& bsonError));
   if (! ok) { return QSqlError("[QxOrm] Unable to insert many 'bson_t' documents (" + pClass->getName() + ") to MongoDB database : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   if (reply) { reply->log(); }
   return QSqlError();
}

QSqlError QxMongoDB_Helper::updateOne(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, const qx::QxSqlQuery * query /* = NULL */)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->updateOne_(pDaoHelper, pClass, json, query);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::updateOne_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, const qx::QxSqlQuery * query)
{
   if (json.count() <= 0) { return QSqlError(); }
   qx_db_collection coll; QSqlError err = initCollection(pClass, coll); if (err.isValid()) { return err; }
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB update one '" + (pClass ? pClass->getName() : QString()) + "' :\n" + json + "\n" + (query ? query->queryAt(0) : QString())); }

   qx_scoped_wrapper<bson_t> doc(toStdString(json));
   if (! doc.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document instance (" + pClass->getName() + ") from JSON : " + QString(doc.err()->message), "", QSqlError::UnknownError); }

   qx_scoped_wrapper<bson_t> query_(toStdString((query ? query->queryAt(0) : QString())));
   if (! query_.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document/query instance (" + pClass->getName() + ") from JSON : " + QString(query_.err()->message), "", QSqlError::UnknownError); }
   if (! query || query->queryAt(0).isEmpty())
   {
      bson_iter_t itr; const bson_value_t * oid = (bson_iter_init_find((& itr), doc.get(), "_id") ? bson_iter_value(& itr) : NULL);
      if (! oid) { return QSqlError("[QxOrm] Unable to find/fetch document oid '_id' (" + pClass->getName() + ")", "", QSqlError::UnknownError); }
      if (! bson_append_value(query_.get(), "_id", -1, oid)) { return QSqlError("[QxOrm] Unable to append 'bson_value_t' oid value to document (" + pClass->getName() + ")", "", QSqlError::UnknownError); }
   }

   qx_scoped_wrapper<bson_t> update_("");
   const bson_t * doc_ = const_cast<const bson_t *>(doc.get());
   if (! bson_append_document(update_.get(), "$set", -1, doc_)) { return QSqlError("[QxOrm] Unable to append 'bson_t' document for update query (" + pClass->getName() + ")", "", QSqlError::UnknownError); }

   bson_error_t bsonError; qx_opts_ptr opts; qx_reply_ptr reply; reply.reset(new qx_scoped_wrapper<qx::dao::mongodb::qx_reply>());
   err = getOptions_(QxMongoDB_Helper::opts_collection_update_one, opts, (query ? query->queryAt(1) : QString())); if (err.isValid()) { return err; }
   bool ok = mongoc_collection_update_one(coll.collection->get(), query_.get(), update_.get(), (opts ? opts->get() : NULL), (reply ? reply->get() : NULL), (& bsonError));
   if (! ok) { return QSqlError("[QxOrm] Unable to update one 'bson_t' document (" + pClass->getName() + ") to MongoDB database : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   if (reply && (reply->value("matchedCount").toInt() < 1)) { return QSqlError("[QxOrm] Nothing has been updated (" + pClass->getName() + ") in MongoDB database", "", QSqlError::UnknownError); }
   if (reply && m_bLogDatabaseReply) { reply->log(); }
   return QSqlError();
}

QSqlError QxMongoDB_Helper::updateMany(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, const qx::QxSqlQuery * query /* = NULL */)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->updateMany_(pDaoHelper, pClass, json, query);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::updateMany_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, const qx::QxSqlQuery * query)
{
   if (json.count() <= 0) { return QSqlError(); }
   qx_db_collection coll; QSqlError err = initCollection(pClass, coll); if (err.isValid()) { return err; }
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB update many '" + (pClass ? pClass->getName() : QString()) + "' :\n" + json.join(", \n") + "\n" + (query ? query->queryAt(0) : QString())); }

   qx_opts_ptr optsBulk; err = getOptions_(QxMongoDB_Helper::opts_collection_create_bulk_operation, optsBulk); if (err.isValid()) { return err; }
   qx_scoped_wrapper<mongoc_bulk_operation_t> bulk(coll.collection->get(), (optsBulk ? optsBulk->get() : NULL));
   if (! bulk.get()) { return QSqlError("[QxOrm] Unable to create 'mongoc_bulk_operation_t' bulk operation instance (" + pClass->getName() + ")", "", QSqlError::UnknownError); }
   qx_opts_ptr opts; err = getOptions_(QxMongoDB_Helper::opts_bulk_operation_update_one, opts, (query ? query->queryAt(1) : QString())); if (err.isValid()) { return err; }
   int iUpdateCount = 0;

   Q_FOREACH(QString s, json)
   {
      if (s.isEmpty()) { continue; }
      qx_scoped_wrapper<bson_t> doc(toStdString(s));
      if (! doc.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document instance (" + pClass->getName() + ") from JSON : " + QString(doc.err()->message), "", QSqlError::UnknownError); }

      qx_scoped_wrapper<bson_t> query_(toStdString((query ? query->queryAt(0) : QString())));
      if (! query_.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document/query instance (" + pClass->getName() + ") from JSON : " + QString(query_.err()->message), "", QSqlError::UnknownError); }
      if (! query || query->queryAt(0).isEmpty())
      {
         bson_iter_t itr; const bson_value_t * oid = (bson_iter_init_find((& itr), doc.get(), "_id") ? bson_iter_value(& itr) : NULL);
         if (! oid) { return QSqlError("[QxOrm] Unable to find/fetch document oid '_id' (" + pClass->getName() + ")", "", QSqlError::UnknownError); }
         if (! bson_append_value(query_.get(), "_id", -1, oid)) { return QSqlError("[QxOrm] Unable to append 'bson_value_t' oid value to document (" + pClass->getName() + ")", "", QSqlError::UnknownError); }
      }

      qx_scoped_wrapper<bson_t> update_("");
      const bson_t * doc_ = const_cast<const bson_t *>(doc.get());
      if (! bson_append_document(update_.get(), "$set", -1, doc_)) { return QSqlError("[QxOrm] Unable to append 'bson_t' document for update query (" + pClass->getName() + ")", "", QSqlError::UnknownError); }

      bson_error_t bsonErr;
      if (! mongoc_bulk_operation_update_one_with_opts(bulk.get(), query_.get(), update_.get(), (opts ? opts->get() : NULL), (& bsonErr)))
      { return QSqlError("[QxOrm] Unable to append update bulk operation (" + pClass->getName() + ") : " + QString(bsonErr.message), "", QSqlError::UnknownError); }
      iUpdateCount++;
   }

   bson_error_t bsonError; qx_reply_ptr reply;
   reply.reset(new qx_scoped_wrapper<qx::dao::mongodb::qx_reply>());
   bool ok = mongoc_bulk_operation_execute(bulk.get(), reply->get(), (& bsonError));
   if (! ok) { return QSqlError("[QxOrm] Unable to update many 'bson_t' documents (" + pClass->getName() + ") to MongoDB database (bulk operation) : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   if (reply && (reply->value("nMatched").toInt() != iUpdateCount)) { return QSqlError("[QxOrm] Not everything has been updated (" + pClass->getName() + ") in MongoDB database (result:'" + QString::number(reply->value("nMatched").toInt()) + "', expected:'" + QString::number(iUpdateCount) + "')", "", QSqlError::UnknownError); }
   if (m_bLogDatabaseReply && reply) { reply->log(); }
   return QSqlError();
}

QSqlError QxMongoDB_Helper::deleteOne(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, const qx::QxSqlQuery * query /* = NULL */)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->deleteOne_(pDaoHelper, pClass, json, query);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::deleteOne_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, const qx::QxSqlQuery * query)
{
   if (json.isEmpty() && ! query) { return QSqlError(); }
   qx_db_collection coll; QSqlError err = initCollection(pClass, coll); if (err.isValid()) { return err; }
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB delete one '" + (pClass ? pClass->getName() : QString()) + "' :\n" + json + "\n" + (query ? query->queryAt(0) : QString())); }

   qx_scoped_wrapper<bson_t> query_(toStdString((query ? query->queryAt(0) : json)));
   if (! query_.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document/query instance (" + pClass->getName() + ") from JSON : " + QString(query_.err()->message), "", QSqlError::UnknownError); }

   bson_error_t bsonError; qx_opts_ptr opts; qx_reply_ptr reply; reply.reset(new qx_scoped_wrapper<qx::dao::mongodb::qx_reply>());
   err = getOptions_(QxMongoDB_Helper::opts_collection_delete_one, opts, (query ? query->queryAt(1) : QString())); if (err.isValid()) { return err; }
   bool ok = mongoc_collection_delete_one(coll.collection->get(), query_.get(), (opts ? opts->get() : NULL), (reply ? reply->get() : NULL), (& bsonError));
   if (! ok) { return QSqlError("[QxOrm] Unable to delete one 'bson_t' document (" + pClass->getName() + ") in MongoDB database : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   if (reply && (reply->value("deletedCount").toInt() < 1)) { return QSqlError("[QxOrm] Nothing has been deleted (" + pClass->getName() + ") in MongoDB database", "", QSqlError::UnknownError); }
   if (reply && m_bLogDatabaseReply) { reply->log(); }
   return QSqlError();
}

QSqlError QxMongoDB_Helper::deleteMany(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, const qx::QxSqlQuery * query /* = NULL */)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->deleteMany_(pDaoHelper, pClass, json, query);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::deleteMany_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, const qx::QxSqlQuery * query)
{
   if ((json.count() <= 0) && (! query)) { return QSqlError(); }
   if (query && (query->type() == "aggregate")) { QStringList empty; return aggregate_(pDaoHelper, pClass, empty, query, "", NULL, true); }
   QString listId = (query ? QString() : ((json.count() > 0) ? QString("{ \"_id\": { \"$in\": [ %ID% ] } }") : QString()));
   if (! listId.isEmpty()) { QString ids; Q_FOREACH(QString s, json) { ids += asJson(s) + ", "; }; ids = ids.left(ids.count() - 2); listId.replace("%ID%", ids); }
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB delete many '" + (pClass ? pClass->getName() : QString()) + "' :\n" + json.join(", \n") + "\n" + (query ? query->queryAt(0) : QString())); }
   qx_db_collection coll; QSqlError err = initCollection(pClass, coll); if (err.isValid()) { return err; }

   qx_scoped_wrapper<bson_t> query_(toStdString((query ? query->queryAt(0) : listId)));
   if (! query_.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document/query instance (" + pClass->getName() + ") from JSON : " + QString(query_.err()->message), "", QSqlError::UnknownError); }

   bson_error_t bsonError; qx_opts_ptr opts; qx_reply_ptr reply;
   if (m_bLogDatabaseReply) { reply.reset(new qx_scoped_wrapper<qx::dao::mongodb::qx_reply>()); }
   err = getOptions_(QxMongoDB_Helper::opts_collection_delete_many, opts, (query ? query->queryAt(1) : QString())); if (err.isValid()) { return err; }
   bool ok = mongoc_collection_delete_many(coll.collection->get(), query_.get(), (opts ? opts->get() : NULL), (reply ? reply->get() : NULL), (& bsonError));
   if (! ok) { return QSqlError("[QxOrm] Unable to delete many 'bson_t' documents (" + pClass->getName() + ") in MongoDB database : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   if (reply) { reply->log(); }
   return QSqlError();
}

QSqlError QxMongoDB_Helper::findOne(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QString & json, const qx::QxSqlQuery * query /* = NULL */)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->findOne_(pDaoHelper, pClass, json, query);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::findOne_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QString & json, const qx::QxSqlQuery * query)
{
   QString lookup = buildLookup(pDaoHelper, false); QSqlError err;
   if ((! lookup.isEmpty()) || (query && (query->type() == "aggregate")))
   {
      QStringList result;
      if ((! query) && (! json.isEmpty())) { qx_query query_tmp(json); err = aggregate_(pDaoHelper, pClass, result, (& query_tmp), lookup, NULL); }
      else { err = aggregate_(pDaoHelper, pClass, result, query, lookup, NULL); }
      json = ((result.count() > 0) ? result.at(0) : QString());
      return err;
   }

   QString id = (query ? QString() : json); json = QString();
   qx_db_collection coll; err = initCollection(pClass, coll); if (err.isValid()) { return err; }

   QString findQuery = (query ? query->queryAt(0) : id);
   qx_scoped_wrapper<bson_t> query_(toStdString(findQuery));
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB find one '" + (pClass ? pClass->getName() : QString()) + "' :\n" + findQuery); }
   if (! query_.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document/query instance (" + pClass->getName() + ") from JSON : " + QString(query_.err()->message), "", QSqlError::UnknownError); }

   QStringList columns = (pDaoHelper ? pDaoHelper->getSqlColumns() : QStringList());
   QString projection; Q_FOREACH(QString col, columns) { projection += (col.isEmpty() ? QString() : ((projection.isEmpty() ? QString("\"") : QString(", \"")) + col + "\": 1")); }
   projection = (projection.isEmpty() ? QString() : QString("{ \"projection\": { " + projection + " } }"));

   QString customOpts = ((query && ! query->queryAt(1).isEmpty()) ? query->queryAt(1) : projection);
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB find one '" + (pClass ? pClass->getName() : QString()) + "' :\n" + findQuery + "\n" + customOpts); }
   qx_opts_ptr opts; err = getOptions_(QxMongoDB_Helper::opts_collection_find, opts, customOpts); if (err.isValid()) { return err; }
   mongoc_cursor_t * cursor_ = mongoc_collection_find_with_opts(coll.collection->get(), query_.get(), (opts ? opts->get() : NULL), NULL);

   qx_scoped_wrapper<mongoc_cursor_t> cursor(cursor_);
   if (! cursor.get()) { return QSqlError("[QxOrm] Unable to create a 'mongoc_cursor_t' cursor instance (" + pClass->getName() + ")", "", QSqlError::UnknownError); }

   const bson_t * doc = NULL;
   if (mongoc_cursor_next(cursor.get(), (& doc)))
   { char * val = bson_as_relaxed_extended_json(doc, NULL); json = QString(val); bson_free(val); }

   bson_error_t bsonError;
   if (mongoc_cursor_error(cursor.get(), (& bsonError)))
   { return QSqlError("[QxOrm] MongoDB cursor error trying to find one document (" + pClass->getName() + ") : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   return QSqlError();
}

QSqlError QxMongoDB_Helper::findMany(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QStringList & json, const qx::QxSqlQuery * query /* = NULL */, QxMongoDB_Fetcher * pFetcher /* = NULL */)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->findMany_(pDaoHelper, pClass, json, query, pFetcher);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::findMany_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QStringList & json, const qx::QxSqlQuery * query, QxMongoDB_Fetcher * pFetcher)
{
   QString lookup = buildLookup(pDaoHelper, false);
   if ((! lookup.isEmpty()) || (query && (query->type() == "aggregate")))
   { return aggregate_(pDaoHelper, pClass, json, query, lookup, pFetcher); }

   QString listId = (query ? QString() : ((json.count() > 0) ? QString("{ \"_id\": { \"$in\": [ %ID% ] } }") : QString()));
   if (! listId.isEmpty()) { QString ids; Q_FOREACH(QString s, json) { ids += asJson(s) + ", "; }; ids = ids.left(ids.count() - 2); listId.replace("%ID%", ids); }
   json.clear(); qx_db_collection coll; QSqlError err = initCollection(pClass, coll); if (err.isValid()) { return err; }

   QString findQuery = (query ? query->queryAt(0) : listId);
   qx_scoped_wrapper<bson_t> query_(toStdString((findQuery)));
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB find many '" + (pClass ? pClass->getName() : QString()) + "' :\n" + findQuery); }
   if (! query_.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document/query instance (" + pClass->getName() + ") from JSON : " + QString(query_.err()->message), "", QSqlError::UnknownError); }

   QStringList columns = (pDaoHelper ? pDaoHelper->getSqlColumns() : QStringList());
   QString projection; Q_FOREACH(QString col, columns) { projection += (col.isEmpty() ? QString() : ((projection.isEmpty() ? QString("\"") : QString(", \"")) + col + "\": 1")); }
   projection = (projection.isEmpty() ? QString() : QString("{ \"projection\": { " + projection + " } }"));

   QString customOpts = ((query && ! query->queryAt(1).isEmpty()) ? query->queryAt(1) : projection);
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB find many '" + (pClass ? pClass->getName() : QString()) + "' :\n" + findQuery + "\n" + customOpts); }
   qx_opts_ptr opts; err = getOptions_(QxMongoDB_Helper::opts_collection_find, opts, customOpts); if (err.isValid()) { return err; }
   mongoc_cursor_t * cursor_ = mongoc_collection_find_with_opts(coll.collection->get(), query_.get(), (opts ? opts->get() : NULL), NULL);

   qx_scoped_wrapper<mongoc_cursor_t> cursor(cursor_);
   if (! cursor.get()) { return QSqlError("[QxOrm] Unable to create a 'mongoc_cursor_t' cursor instance (" + pClass->getName() + ")", "", QSqlError::UnknownError); }

   const bson_t * doc = NULL;
   while (mongoc_cursor_next(cursor.get(), (& doc)))
   {
      char * val = bson_as_relaxed_extended_json(doc, NULL);
      if (pFetcher) { QString tmp(val); pFetcher->fetch(tmp); if (pDaoHelper && (! pDaoHelper->isValid())) { bson_free(val); return pDaoHelper->error(); } }
      else { json << QString(val); }
      bson_free(val);
   }

   bson_error_t bsonError;
   if (mongoc_cursor_error(cursor.get(), (& bsonError)))
   { return QSqlError("[QxOrm] MongoDB cursor error trying to find many documents (" + pClass->getName() + ") : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   return QSqlError();
}

QSqlError QxMongoDB_Helper::aggregate(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QStringList & json, const qx::QxSqlQuery * query /* = NULL */, const QString & lookup /* = QString() */, QxMongoDB_Fetcher * pFetcher /* = NULL */)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->aggregate_(pDaoHelper, pClass, json, query, lookup, pFetcher);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::aggregate_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QStringList & json, const qx::QxSqlQuery * query, const QString & lookup, QxMongoDB_Fetcher * pFetcher, bool bModeDelete /* = false */)
{
   QString listId = (query ? QString() : ((json.count() > 0) ? QString("{ \"_id\": { \"$in\": [ %ID% ] } }") : QString()));
   if (! listId.isEmpty()) { QString ids; Q_FOREACH(QString s, json) { ids += asJson(s) + ", "; }; ids = ids.left(ids.count() - 2); listId.replace("%ID%", ids); }
   json.clear(); qx_db_collection coll; QSqlError err = initCollection(pClass, coll); if (err.isValid()) { return err; }

   QString findQuery = (query ? query->queryAt(0) : listId);
   if (! lookup.isEmpty() && ! findQuery.isEmpty()) { findQuery = "[ { \"$match\": " + findQuery + " }, " + lookup + " ]"; }
   else if (! lookup.isEmpty() && findQuery.isEmpty()) { findQuery = "[ " + lookup + " ]"; }

   qx_scoped_wrapper<bson_t> query_(toStdString((findQuery)));
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB aggregate '" + (pClass ? pClass->getName() : QString()) + "' :\n" + findQuery); }
   if (! query_.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document/query instance (" + pClass->getName() + ") from JSON : " + QString(query_.err()->message), "", QSqlError::UnknownError); }

   qx_opts_ptr opts; err = getOptions_(QxMongoDB_Helper::opts_collection_aggregate, opts, (query ? query->queryAt(1) : QString())); if (err.isValid()) { return err; }
   mongoc_cursor_t * cursor_ = mongoc_collection_aggregate(coll.collection->get(), MONGOC_QUERY_NONE, query_.get(), (opts ? opts->get() : NULL), NULL);

   qx_scoped_wrapper<mongoc_cursor_t> cursor(cursor_);
   if (! cursor.get()) { return QSqlError("[QxOrm] Unable to create a 'mongoc_cursor_t' cursor instance (" + pClass->getName() + ")", "", QSqlError::UnknownError); }

   const bson_t * doc = NULL; QStringList listIdsToDelete;
   while (mongoc_cursor_next(cursor.get(), (& doc)))
   {
      char * val = bson_as_relaxed_extended_json(doc, NULL);
      if (bModeDelete)
      {
         QJsonValue obj; QString tmp(val);
         qx::cvt::from_string(tmp, obj);
         if (obj.isObject())
         {
            QJsonValue id = obj.toObject().value("_id");
            qx::cvt::from_json(id, tmp, "mongodb");
            if (! tmp.isEmpty()) { listIdsToDelete.append(tmp); }
         }
      }
      else if (pFetcher) { QString tmp(val); pFetcher->fetch(tmp); if (pDaoHelper && (! pDaoHelper->isValid())) { bson_free(val); return pDaoHelper->error(); } }
      else { json << QString(val); }
      bson_free(val);
   }

   bson_error_t bsonError;
   if (mongoc_cursor_error(cursor.get(), (& bsonError)))
   { return QSqlError("[QxOrm] MongoDB cursor error trying to find many documents (" + pClass->getName() + ") : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   if (bModeDelete && (listIdsToDelete.count() > 0)) { return deleteMany_(pDaoHelper, pClass, listIdsToDelete, NULL); }
   return QSqlError();
}

QSqlError QxMongoDB_Helper::executeCommand(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, qx::QxSqlQuery * query)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->executeCommand_(pDaoHelper, pClass, query);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::executeCommand_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, qx::QxSqlQuery * query)
{
   if (! query) { return QSqlError("[QxOrm] Unable to execute command in MongoDB database : 'query' parameter is required", "", QSqlError::UnknownError); }
   query->setResponse(QVariant()); qx_db_collection coll;
   QSqlError err = (pClass ? initCollection(pClass, coll) : initDatabase(coll)); if (err.isValid()) { return err; }
   QString collName = (pClass ? pClass->getName() : QString());

   qx_scoped_wrapper<bson_t> cmd_(toStdString((query ? query->queryAt(0) : QString())));
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB command '" + (pClass ? pClass->getName() : QString()) + "' :\n" + (query ? query->queryAt(0) : QString())); }
   if (! cmd_.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document/command instance (" + collName + ") from JSON : " + QString(cmd_.err()->message), "", QSqlError::UnknownError); }

   bson_error_t bsonError; qx_opts_ptr opts; qx_reply_ptr reply;
   reply.reset(new qx_scoped_wrapper<qx::dao::mongodb::qx_reply>());
   err = getOptions_(QxMongoDB_Helper::opts_collection_command, opts, (query ? query->queryAt(1) : QString())); if (err.isValid()) { return err; }

   if (! pClass)
   {
      if (! mongoc_database_command_with_opts(coll.db->get(), cmd_.get(), NULL, (opts ? opts->get() : NULL), reply->get(), (& bsonError)))
      { return QSqlError("[QxOrm] Unable to execute command in MongoDB database : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   }
   else
   {
      if (! mongoc_collection_command_with_opts(coll.collection->get(), cmd_.get(), NULL, (opts ? opts->get() : NULL), reply->get(), (& bsonError)))
      { return QSqlError("[QxOrm] Unable to execute command (" + collName + ") in MongoDB database : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   }

   if (query && (query->type() == "cursor"))
   {
      reply->m_destroy = false;
      qx_scoped_wrapper<mongoc_cursor_t> cursor(mongoc_cursor_new_from_command_reply(coll.client->get(), reply->get(), 0));
      if (! cursor.get()) { return QSqlError("[QxOrm] Unable to create a 'mongoc_cursor_t' cursor instance from reply (" + pClass->getName() + ")", "", QSqlError::UnknownError); }

      const bson_t * doc = NULL; QString json;
      while (mongoc_cursor_next(cursor.get(), (& doc)))
      { char * val = bson_as_relaxed_extended_json(doc, NULL); json += ((json.isEmpty() ? QString() : QString(",\n")) + QString(val)); bson_free(val); }
      if (! json.isEmpty()) { json = "[ " + json + " ]"; }
      query->setResponse(QVariant(json));

      bson_error_t bsonError;
      if (mongoc_cursor_error(cursor.get(), (& bsonError)))
      { return QSqlError("[QxOrm] MongoDB cursor error trying to find many documents from reply (" + pClass->getName() + ") : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   }
   else
   {
      const bson_t * reply_ = const_cast<const bson_t *>(reply->get());
      char * val = bson_as_relaxed_extended_json(reply_, NULL);
      query->setResponse(QVariant(QString(val))); bson_free(val);
   }

   return QSqlError();
}

QSqlError QxMongoDB_Helper::count(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, long & cnt, const qx::QxSqlQuery * query /* = NULL */)
{
   qx::dao::detail::IxDao_Timer timer(pDaoHelper, qx::dao::detail::IxDao_Helper::timer_db_exec);
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QSqlError err = pSingleton->m_pImpl->count_(pDaoHelper, pClass, cnt, query);
   return (pDaoHelper ? pDaoHelper->updateError(err) : err);
}

QSqlError QxMongoDB_Helper::QxMongoDB_HelperImpl::count_(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, long & cnt, const qx::QxSqlQuery * query)
{
   cnt = 0; qx_db_collection coll;
   QSqlError err = initCollection(pClass, coll); if (err.isValid()) { return err; }

   qx_scoped_wrapper<bson_t> query_(toStdString((query ? query->queryAt(0) : QString())));
   if (pDaoHelper) { pDaoHelper->qxQuery().queryAt(0, "MongoDB count '" + (pClass ? pClass->getName() : QString()) + "' :\n" + (query ? query->queryAt(0) : QString())); }
   if (! query_.get()) { return QSqlError("[QxOrm] Unable to create a 'bson_t' document/query instance (" + pClass->getName() + ") from JSON : " + QString(query_.err()->message), "", QSqlError::UnknownError); }

   bson_error_t bsonError; qx_opts_ptr opts;
   err = getOptions_(QxMongoDB_Helper::opts_collection_count, opts, (query ? query->queryAt(1) : QString())); if (err.isValid()) { return err; }
   cnt = static_cast<long>(mongoc_collection_count_with_opts(coll.collection->get(), MONGOC_QUERY_NONE, query_.get(), 0, 0, (opts ? opts->get() : NULL), NULL, (& bsonError)));
   if (cnt < 0) { cnt = 0; return QSqlError("[QxOrm] Unable to count 'bson_t' documents (" + pClass->getName() + ") in MongoDB database : " + QString(bsonError.message), "", QSqlError::UnknownError); }
   return QSqlError();
}

QSqlError QxMongoDB_Helper::autoCreateIndexes(bool log /* = true */)
{
   qx::QxClassX::registerAllClasses(true);
   qx::QxCollection<QString, qx::IxClass *> * pAllClasses = qx::QxClassX::getAllClasses();
   if (! pAllClasses) { return QSqlError("[QxOrm] Unable to get all classes registered in QxOrm context", "", QSqlError::UnknownError); }

   for (auto itr = pAllClasses->begin(); itr != pAllClasses->end(); ++itr)
   {
      qx::IxClass * pClass = itr->second; if (! pClass || pClass->isAbstract()) { continue; }
      QString collectionName = pClass->getName();

      do {
         qx::IxDataMemberX * pDataMemberX = pClass->getDataMemberX();
         long cnt = (pDataMemberX ? pDataMemberX->count() : 0);
         for (long l = 0; l < cnt; l++)
         {
            qx::IxDataMember * pDataMember = pDataMemberX->get(l);
            if (! pDataMember || ! pDataMember->getDao() || pDataMember->getIsPrimaryKey()) { continue; }
            qx::IxSqlRelation * pRelation = pDataMember->getSqlRelation();
            bool isIndex = pDataMember->getIsIndex(); if (! isIndex && ! pRelation) { continue; }
            qx::IxSqlRelation::relation_type eRelationType = (pRelation ? pRelation->getRelationType() : qx::IxSqlRelation::no_relation);
            bool isUnique = pDataMember->getIsUnique();

            QString idxName;
            if (eRelationType == qx::IxSqlRelation::many_to_one) { idxName = "idx_" + collectionName + "_" + pDataMember->getKey() + "_many_to_one"; }
            else if (eRelationType == qx::IxSqlRelation::one_to_one) { idxName = "idx_" + collectionName + "_" + pDataMember->getKey() + "_one_to_one"; }
            else if (isIndex) { idxName = "idx_" + collectionName + "_" + pDataMember->getKey(); }
            if (idxName.isEmpty()) { continue; }

            QString query_ = "{ \"createIndexes\": \"" + collectionName + "\", \"indexes\": ";
            query_ += "[ { \"key\": { \"" + pDataMember->getKey() + "\": 1 }, \"name\": \"" + idxName + "\"" + (isUnique ? QString(", \"unique\": true") : QString()) + " } ] }";
            qx_query query(query_);

            if (log) { QString msg = "MongoDB create index for '" + collectionName + "::" + pDataMember->getKey() + "', request : " + query_; qDebug("[QxOrm] %s", qPrintable(msg)); }
            QSqlError err = executeCommand(NULL, NULL, (& query)); if (err.isValid()) { return err; }
            if (log) { QString response = query.response().toString(); QString msg = "MongoDB create index for '" + collectionName + "::" + pDataMember->getKey() + "', response : " + response; qDebug("[QxOrm] %s", qPrintable(msg)); }
         }
         pClass = pClass->getBaseClass();
      }
      while (pClass != NULL);
   }

   return QSqlError();
}

bool QxMongoDB_Helper::setOptions(QxMongoDB_Helper::opts e, const QString & optsAsJson)
{
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   return pSingleton->m_pImpl->setOptions_(e, optsAsJson);
}

void QxMongoDB_Helper::setLogDatabaseReply(bool b)
{
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   pSingleton->m_pImpl->m_bLogDatabaseReply = b;
}

void QxMongoDB_Helper::setLogDatabaseInfo(bool b)
{
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   pSingleton->m_pImpl->m_bLogDatabaseInfo = b;
}

void QxMongoDB_Helper::clearPoolConnection()
{
   QxMongoDB_Helper * pSingleton = QxMongoDB_Helper::getSingleton(); qAssert(pSingleton != NULL);
   QMutexLocker locker(& pSingleton->m_pImpl->m_oDbMutex);
   pSingleton->m_pImpl->m_pPool.reset();
   pSingleton->m_pImpl->m_pUri.reset();
}

} // namespace mongodb
} // namespace dao
} // namespace qx

#endif // _QX_ENABLE_MONGODB
