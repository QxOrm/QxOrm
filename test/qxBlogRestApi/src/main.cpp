#include "../include/precompiled.h"

#include <QtCore/qcoreapplication.h>
#include <QtCore/qsysinfo.h>

#ifdef QT_GUI_LIB
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qtableview.h>
#include <QtQuick/qquickview.h>
#include <QtQml/qqmlcontext.h>
#else // (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtGui/qapplication.h>
#include <QtGui/qtableview.h>
#include <QtDeclarative/qdeclarativeview.h>
#include <QtDeclarative/qdeclarativecontext.h>
#endif // (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))

#include <QtGui/qdesktopservices.h>
#endif // QT_GUI_LIB

#include "../include/blog.h"
#include "../include/author.h"
#include "../include/comment.h"
#include "../include/category.h"

#include <QxOrm_Impl.h>

void displayQML();
void runHTTPServer();
void checkAppArguments();
QString getFileText(const QString & fileName);

#ifdef _QX_ENABLE_QT_NETWORK
void defineHTTPDispatch(qx::QxHttpServer & httpServer);
#endif // _QX_ENABLE_QT_NETWORK

void connectDatabase();
void connectDatabaseSQLite();
void connectDatabaseMongoDB();
void connectDatabasePostgreSQL();
void connectDatabaseMySQL();
void connectDatabaseMariaDB();
void connectDatabaseOracle();
void connectDatabaseMSSqlServer();

void prepareDatabase();
void prepareDatabaseGeneric(bool createTables);
void prepareDatabaseSQLite();
void prepareDatabaseMongoDB();
void prepareDatabasePostgreSQL();
void prepareDatabaseMySQL();
void prepareDatabaseMariaDB();
void prepareDatabaseOracle();
void prepareDatabaseMSSqlServer();

QString pingDatabase();
QString pingDatabaseSQLite();
QString pingDatabaseMongoDB();
QString pingDatabasePostgreSQL();
QString pingDatabaseMySQL();
QString pingDatabaseMariaDB();
QString pingDatabaseOracle();
QString pingDatabaseMSSqlServer();

#ifdef _QX_TEST_WITH_MONGODB
void mongoBasicCRUDOnAuthor(bool withDelete);
void mongoBasicCRUDOnCategory();
void mongoBasicCRUDOnBlog();
void mongoComplexQueriesOnBlog();
void mongoMiscellaneousOperations();
#endif // _QX_TEST_WITH_MONGODB

#if (QT_VERSION < QT_VERSION_CHECK(5, 10, 0))
#define qEnvironmentVariable qgetenv
#endif // (QT_VERSION < QT_VERSION_CHECK(5, 10, 0))

int main(int argc, char * argv[])
{
#ifdef QT_GUI_LIB
   QApplication app(argc, argv);
#else // QT_GUI_LIB
   QCoreApplication app(argc, argv);
#endif // QT_GUI_LIB

   checkAppArguments();

   qx::QxClassX::registerAllClasses(); // This command is recommanded to initialize QxOrm introspection engine
   qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true); // Only for debug purpose : assert if invalid offset detected fetching a relation
   qx::QxSqlDatabase::getSingleton()->setFormatSqlQueryBeforeLogging(true); // To have better SQL queries output logs

   connectDatabase();
   prepareDatabase();

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
   displayQML();
#ifdef _QX_ENABLE_QT_NETWORK
   runHTTPServer();
#else // _QX_ENABLE_QT_NETWORK
   qDebug("[QxOrm] qxBlogRestApi example project : %s", "cannot start QxOrm HTTP server because _QX_ENABLE_QT_NETWORK compilation option is not defined");
#endif // _QX_ENABLE_QT_NETWORK
#else // (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
   qDebug("[QxOrm] %s", "qxBlogRestApi example project only works with Qt5 or +");
#endif // (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))

   return 0;
}

void runHTTPServer()
{
#ifdef _QX_ENABLE_QT_NETWORK
   // Just to be sure to have static files on the system
   QDir appPath(QDir::currentPath()); appPath.mkdir("files");
   QFile::copy(":/documents/test_http_server.html", appPath.filePath("files/test_http_server.html"));
   QFile::copy(":/documents/logo_qxorm_and_qxee.png", appPath.filePath("files/logo_qxorm_and_qxee.png"));
   QFile::copy(":/documents/jquery.js", appPath.filePath("files/jquery.js"));

   int port = 9642; // Port number by default
   QCoreApplication * app = QCoreApplication::instance();
   QString argPort = app->property("port").toString();
   if ((! argPort.isEmpty()) && (argPort.toInt() > 0)) { port = argPort.toInt(); }

   // HTTP server settings
   qx::service::QxConnect * serverSettings = qx::service::QxConnect::getSingleton();
   serverSettings->setKeepAlive(5000);
   serverSettings->setCompressData(true);
   serverSettings->setThreadCount(50);
   serverSettings->setPort(port);

#ifndef QT_NO_SSL
   if (false) // If you want to test SSL/TLS secured connection, just force this condition to 'true'
   {
      // Certificates created with this tutorial : https://deliciousbrains.com/ssl-certificate-authority-for-local-https-development/
      QFile::copy(":/documents/cert_qxorm_ca.pem", appPath.filePath("files/cert_qxorm_ca.pem"));
      QFile::copy(":/documents/cert_qxorm_server.crt", appPath.filePath("files/cert_qxorm_server.crt"));
      QFile::copy(":/documents/cert_qxorm_server.key", appPath.filePath("files/cert_qxorm_server.key"));

      QFile fileCertCA(appPath.filePath("files/cert_qxorm_ca.pem"));
      fileCertCA.open(QIODevice::ReadOnly);
      QList<QSslCertificate> certCA; certCA << QSslCertificate(fileCertCA.readAll());

      QFile fileCertServerPublic(appPath.filePath("files/cert_qxorm_server.crt"));
      fileCertServerPublic.open(QIODevice::ReadOnly);
      QSslCertificate certServerPublic(fileCertServerPublic.readAll());

      QFile fileCertServerPrivate(appPath.filePath("files/cert_qxorm_server.key"));
      fileCertServerPrivate.open(QIODevice::ReadOnly);
      QSslKey certServerPrivate(fileCertServerPrivate.readAll(), QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, "qxorm");

      serverSettings->setSSLEnabled(true);
      serverSettings->setSSLCACertificates(certCA);
      serverSettings->setSSLLocalCertificate(certServerPublic);
      serverSettings->setSSLPrivateKey(certServerPrivate);
   }
#endif // QT_NO_SSL

   // Create a QxOrm HTTP server instance
   qx::QxHttpServer httpServer;
   defineHTTPDispatch(httpServer);

   // Start HTTP server
   QString url = "http" + QString(serverSettings->getSSLEnabled() ? "s" : "") + "://localhost:" + QString::number(port) + "/files/test_http_server.html";
   QString log = "Start QxOrm HTTP server, go to : " + url;
   QString dbType = qEnvironmentVariable("QX_DB");
   if (! dbType.isEmpty()) // Means inside Docker container
   {
      // Don't write 'http://' full URL in output logs to avoid automatic VSCode port forwarding
      QString portDocker = QString((port == 9642) ? "8080" : "8081"); // Release or Debug mode
      log = "Start QxOrm HTTP server inside Docker container (database type : " + dbType + "), on the host machine open a web browser and go to 'localhost', port '" + portDocker + "'";
   }
   qDebug("[QxOrm] %s", qPrintable(log));
   httpServer.startServer();

#ifdef QT_GUI_LIB
   // Open default web browser to connect to QxOrm HTTP server instance
   QDesktopServices::openUrl(QUrl(url));

   QQuickView qmlView;
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
   QString sQmlFile = "qrc:/documents/test_http_server_qt6.qml";
#else // (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
   QString sQmlFile = "qrc:/documents/test_http_server.qml";
#endif // (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))

   qmlView.rootContext()->setContextProperty("qxHttpServer", (& httpServer));
   qmlView.setResizeMode(QQuickView::SizeRootObjectToView);
   qmlView.setSource(QUrl(sQmlFile));
   qmlView.show();
#endif // QT_GUI_LIB

   qApp->exec();
#endif // _QX_ENABLE_QT_NETWORK
}

#ifdef _QX_ENABLE_QT_NETWORK
void defineHTTPDispatch(qx::QxHttpServer & httpServer)
{
   // Define all HTTP server routes (dispatcher) to handle requests
   // Each callback is executed in a dedicated thread, so QxOrm HTTP server can handle several requests in parallel
   httpServer.dispatch("GET", "/files/*", [](qx::QxHttpRequest & request, qx::QxHttpResponse & response) {
      qx::QxHttpServer::buildResponseStaticFile(request, response, QDir::currentPath(), 5000);
   });
   httpServer.dispatch("POST", "/qx", [](qx::QxHttpRequest & request, qx::QxHttpResponse & response) {
      qx::QxHttpServer::buildResponseQxRestApi(request, response);

      // Not useful here but this is how to get a server session per user
      // If this is the first time to access to session, then a cookie is created automatically and attached to the response
      // Then each request sent by web browser will contain a cookie with the session id
      // The session expires on server side after qx::service::QxConnect::setSessionTimeOut() milliseconds
      qx::QxHttpSession_ptr session = qx::QxHttpSessionManager::getSession(request, response);
      if (session) { session->set("last_request_per_user", QDateTime::currentDateTime()); }
   });
   httpServer.dispatch("POST", "/ping", [](qx::QxHttpRequest & request, qx::QxHttpResponse & response) {
      QJsonObject pong; Q_UNUSED(request);
      pong.insert("qxorm_version", QString(QX_VERSION_STR));
      pong.insert("qt_version", QString(QT_VERSION_STR));
#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
      pong.insert("os_kernel_type", QSysInfo::kernelType());
      pong.insert("os_kernel_version", QSysInfo::kernelVersion());
      pong.insert("os_product_type", QSysInfo::productType());
      pong.insert("os_product_version", QSysInfo::productVersion());
#endif // (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
      QString dbType = qEnvironmentVariable("QX_DB");
      if (dbType.isEmpty()) { dbType = "sqlite"; }
      pong.insert("database_type", dbType);
      QString dbVersion = pingDatabase();
      pong.insert("database_version", dbVersion);
      QDateTime dt = QDateTime::currentDateTime();
      QString dtPretty = dt.toString("dd-MM-yyyy hh:mm:ss");
      pong.insert("current_date_time", dtPretty);

      QJsonDocument doc(pong);
      response.headers().insert("Content-Type", "application/json; charset=utf-8");
      response.data() = doc.toJson();
   });
   httpServer.dispatch("GET", "/params/<var1>/<var2:int>", [](qx::QxHttpRequest & request, qx::QxHttpResponse & response) {
      response.data() = "Test URL dispatch parameters :\r\n";
      response.data() += " - var1 = " + request.dispatchParams().value("var1").toByteArray() + "\r\n";
      response.data() += " - var2 = " + request.dispatchParams().value("var2").toByteArray() + "\r\n";
   });
   httpServer.dispatch("GET", "/test_big_json", [](qx::QxHttpRequest & request, qx::QxHttpResponse & response) {
      // To compare with this benchmark : https://blog.binaryspaceship.com/2017/cpp-rest-api-frameworks-benchmark/
      // This is more a JSON benchmark than HTTP server benchmark (RapidJSON is faster than Qt QJson engine)
      QJsonArray arr; Q_UNUSED(request);
      for (int i = 0; i < 10000; ++i)
      {
         QJsonObject item;
         item.insert("id", QString::number(i));
         item.insert("name", QString("Hello World"));
         item.insert("type", QString("application"));
         arr.append(item);
      }
      QJsonDocument doc(arr);
      response.headers().insert("Content-Type", "application/json; charset=utf-8");
      response.data() = doc.toJson(QJsonDocument::Compact);
   });
}
#endif // _QX_ENABLE_QT_NETWORK

void displayQML()
{
#ifdef QT_GUI_LIB
   qx::QxRestApi api;

   QQuickView qmlView;
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
   QString sQmlFile = "qrc:/documents/test_rest_api_qt6.qml";
#else // (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
   QString sQmlFile = "qrc:/documents/test_rest_api.qml";
#endif // (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))

   qmlView.rootContext()->setContextProperty("qxRestApi", (& api));
   qmlView.setResizeMode(QQuickView::SizeRootObjectToView);
   qmlView.setSource(QUrl(sQmlFile));
   qmlView.show();
   qApp->exec();
#endif // QT_GUI_LIB
}

void checkAppArguments()
{
   QCoreApplication * app = QCoreApplication::instance();
   QStringList args = QCoreApplication::arguments();
   for (int i = 0; i < args.count(); i++)
   {
      // Get each argument key/value
      QString key = "";
      QString value = "";
      QString arg = args.at(i);
      qDebug("[QxOrm] app arguments (%d) : %s", i, qPrintable(arg));
      QStringList lst = arg.split("=");
      if (i == 0) { continue; }
      else if (lst.count() == 1) { value = lst.at(0); }
      else if (lst.count() == 2) { key = lst.at(0); value = lst.at(1); }
      else { continue; }
      value.replace("\"", "");
      if (key.isEmpty() && value.isEmpty()) { continue; }

      // Put arguments as application meta-data
      if (key == "--port") { app->setProperty("port", value); }
   }
}

QString getFileText(const QString & fileName)
{
   QFile file(fileName);
   if (! file.exists()) { qAssert(false); return QString(); }
   if (! file.open(QIODevice::ReadOnly | QIODevice::Text)) { qAssert(false); return QString(); }
   QTextStream in(& file);
   QString text = in.readAll();
   file.close();
   return text;
}

void connectDatabase()
{
   try
   {
      QString dbType = qEnvironmentVariable("QX_DB");
      if ((dbType.isEmpty()) || (dbType == "sqlite")) { connectDatabaseSQLite(); }
      else if (dbType == "mongodb") { connectDatabaseMongoDB(); }
      else if (dbType == "postgresql") { connectDatabasePostgreSQL(); }
      else if (dbType == "mysql") { connectDatabaseMySQL(); }
      else if (dbType == "mariadb") { connectDatabaseMariaDB(); }
      else if (dbType == "oracle") { connectDatabaseOracle(); }
      else if (dbType == "mssqlserver") { connectDatabaseMSSqlServer(); }
      else { QString msg = "Unknown database type '" + dbType + "'"; qDebug("[QxOrm] %s", qPrintable(msg)); qAssert(false); }
   }
   catch(...)
   {
      QString err = "An error occurred connecting to database";
      qDebug("[QxOrm] %s", qPrintable(err));
   }
}

void connectDatabaseSQLite()
{
   QFile::remove("./qxBlogRestApi.sqlite");

   // Parameters to connect to SQLite database
   qx::QxSqlDatabase * pDatabase = qx::QxSqlDatabase::getSingleton();
   pDatabase->setDriverName("QSQLITE");
   pDatabase->setDatabaseName("./qxBlogRestApi.sqlite");
   pDatabase->setHostName("localhost");
   pDatabase->setUserName("root");
   pDatabase->setPassword("");
}

void connectDatabaseMongoDB()
{
#ifdef _QX_TEST_WITH_MONGODB
   // Parameters to connect to MongoDB database
   qx::QxSqlDatabase * pDatabase = qx::QxSqlDatabase::getSingleton();
   pDatabase->setDriverName("QXMONGODB");
   pDatabase->setDatabaseName("qxBlog");
   pDatabase->setHostName("db_mongodb");
   pDatabase->setPort(27017);
   pDatabase->setUserName("");
   pDatabase->setPassword("");

   // For debug purpose : log all replies from MongoDB database
   qx::dao::mongodb::QxMongoDB_Helper::setLogDatabaseReply(true);

   // Clear previous sample database
   qx_query dropDB("{ \"dropDatabase\" : 1 }");
   QSqlError daoError = qx::dao::call_query(dropDB);
   qAssert(! daoError.isValid());

   // To optimize queries : create automatically indexes based on relationships and properties marked as 'index'
   daoError = qx::dao::mongodb::QxMongoDB_Helper::autoCreateIndexes(true);
   qAssert(! daoError.isValid());
#endif // _QX_TEST_WITH_MONGODB
}

void connectDatabasePostgreSQL()
{
   // Parameters to connect to PostgreSQL database
   qx::QxSqlDatabase * pDatabase = qx::QxSqlDatabase::getSingleton();
   pDatabase->setDriverName("QPSQL");
   pDatabase->setDatabaseName("qxBlog");
   pDatabase->setHostName("db_postgresql");
   pDatabase->setPort(5432);
   pDatabase->setUserName("qxorm");
   pDatabase->setPassword("qxorm");

   // Clear previous sample database
   qx_query query("DROP SCHEMA public CASCADE; CREATE SCHEMA public;");
   QSqlError daoError = qx::dao::call_query_without_prepare(query);
   if (daoError.isValid()) { qAssert(false); }

   // Load database schema generated by QxEntityEditor application
   QString sql = getFileText("./sql/qxBlog_postgresql_db_schema_full.sql");
   qAssert(! sql.isEmpty());
   qx_query schema(sql);
   daoError = qx::dao::call_query_without_prepare(schema);
   if (daoError.isValid()) { qAssert(false); }
}

void connectDatabaseMySQL()
{
   // Parameters to connect to MySQL/MariaDB database
   qx::QxSqlDatabase * pDatabase = qx::QxSqlDatabase::getSingleton();
   QString dbType = qEnvironmentVariable("QX_DB");
   pDatabase->setDriverName("QMYSQL");
   pDatabase->setDatabaseName("qxBlog");
   pDatabase->setHostName((dbType == "mariadb") ? "db_mariadb" : "db_mysql");
   pDatabase->setPort(3306);
   pDatabase->setUserName("qxorm");
   pDatabase->setPassword("qxorm");

   // Clear previous sample database
   qx_query query("DROP DATABASE qxBlog; \nCREATE DATABASE qxBlog; \nUSE qxBlog;");
   QSqlError daoError = qx::dao::call_query_without_prepare(query);
   if (daoError.isValid()) { qAssert(false); }

   // Load database schema generated by QxEntityEditor application
   QString sql = getFileText("./sql/qxBlog_mysql_db_schema_full.sql");
   qAssert(! sql.isEmpty());
   qx_query schema(sql);
   daoError = qx::dao::call_query_without_prepare(schema);
   if (daoError.isValid()) { qAssert(false); }
}

void connectDatabaseMariaDB()
{
   connectDatabaseMySQL();
}

void connectDatabaseOracle()
{
}

void connectDatabaseMSSqlServer()
{
}

void prepareDatabase()
{
   try
   {
      QString dbType = qEnvironmentVariable("QX_DB");
      if ((dbType.isEmpty()) || (dbType == "sqlite")) { prepareDatabaseSQLite(); }
      else if (dbType == "mongodb") { prepareDatabaseMongoDB(); }
      else if (dbType == "postgresql") { prepareDatabasePostgreSQL(); }
      else if (dbType == "mysql") { prepareDatabaseMySQL(); }
      else if (dbType == "mariadb") { prepareDatabaseMariaDB(); }
      else if (dbType == "oracle") { prepareDatabaseOracle(); }
      else if (dbType == "mssqlserver") { prepareDatabaseMSSqlServer(); }
      else { QString msg = "Unknown database type '" + dbType + "'"; qDebug("[QxOrm] %s", qPrintable(msg)); qAssert(false); }
   }
   catch(...)
   {
      QString err = "An error occurred preparing database data";
      qDebug("[QxOrm] %s", qPrintable(err));
   }
}

void prepareDatabaseGeneric(bool createTables)
{
#ifndef _QX_TEST_WITH_MONGODB
   QSqlError daoError;
   if (createTables)
   {
      // Create all tables in database
      daoError = qx::dao::create_table<author>();
      daoError = qx::dao::create_table<comment>();
      daoError = qx::dao::create_table<category>();
      daoError = qx::dao::create_table<blog>();
   }

   // Create a list of 3 author
   author_ptr author_1; author_1.reset(new author());
   author_ptr author_2; author_2.reset(new author());
   author_ptr author_3; author_3.reset(new author());

   author_1->m_id = "author_id_1"; author_1->m_name = "author_1";
   author_1->m_sex = author::male; author_1->m_birthdate = QDate::currentDate();
   author_2->m_id = "author_id_2"; author_2->m_name = "author_2";
   author_2->m_sex = author::female; author_2->m_birthdate = QDate::currentDate();
   author_3->m_id = "author_id_3"; author_3->m_name = "author_3";
   author_3->m_sex = author::female; author_3->m_birthdate = QDate::currentDate();

   list_author authorX;
   authorX.insert(author_1->m_id, author_1);
   authorX.insert(author_2->m_id, author_2);
   authorX.insert(author_3->m_id, author_3);

   // Insert list of 3 author into database
   daoError = qx::dao::insert(authorX);
   qAssert(qx::dao::count<author>() == 3);

   // Clone author 2 : 'author_id_2'
   author_ptr author_clone = qx::clone(* author_2);
   qAssert(author_clone->m_id == "author_id_2");
   qAssert(author_clone->m_sex == author::female);

   // Create a query to fetch only female author : 'author_id_2' and 'author_id_3'
   qx::QxSqlQuery query("WHERE author.sex = :sex");
   query.bind(":sex", author::female);

   list_author list_of_female_author;
   daoError = qx::dao::fetch_by_query(query, list_of_female_author);
   qAssert(list_of_female_author.count() == 2);

   // Dump list of female author (xml serialization)
   qx::dump(list_of_female_author, false);
   qx::dump(list_of_female_author, true);

   // Create 3 categories
   category_ptr category_1 = category_ptr(new category());
   category_ptr category_2 = category_ptr(new category());
   category_ptr category_3 = category_ptr(new category());

   category_1->m_name = "category_1"; category_1->m_desc = "desc_1";
   category_2->m_name = "category_2"; category_2->m_desc = "desc_2";
   category_3->m_name = "category_3"; category_3->m_desc = "desc_3";

   { // Create a scope to destroy temporary connexion to database

      // Open a transaction to database
      QSqlDatabase db = qx::QxSqlDatabase::getDatabase();
      bool bCommit = db.transaction();

      // Insert 3 categories into database, use 'db' parameter for the transaction
      daoError = qx::dao::insert(category_1, (& db));    bCommit = (bCommit && ! daoError.isValid());
      daoError = qx::dao::insert(category_2, (& db));    bCommit = (bCommit && ! daoError.isValid());
      daoError = qx::dao::insert(category_3, (& db));    bCommit = (bCommit && ! daoError.isValid());

      qAssert(bCommit);
      qAssert(category_1->m_id != 0);
      qAssert(category_2->m_id != 0);
      qAssert(category_3->m_id != 0);

      // Terminate transaction => commit or rollback if there is error
      if (bCommit) { db.commit(); }
      else { db.rollback(); }

   } // End of scope : 'db' is destroyed

   // Create a blog with the class name (factory)
   qx::any blog_any = qx::create("blog");
   blog_ptr blog_1;
   try { blog_1 = qx::any_cast<blog_ptr>(blog_any); }
   catch (...) { blog_1.reset(new blog()); }
   blog_1->m_text = "blog_text_1";
   blog_1->m_dt_creation = QDateTime::currentDateTime();
   blog_1->m_author = author_1;

   // Insert 'blog_1' into database with 'save()' method
   daoError = qx::dao::save(blog_1);

   // Modify 'blog_1' properties and save into database
   blog_1->m_text = "update blog_text_1";
   blog_1->m_author = author_2;
   daoError = qx::dao::save(blog_1);

   // Add 2 comments to 'blog_1'
   comment_ptr comment_1; comment_1.reset(new comment());
   comment_ptr comment_2; comment_2.reset(new comment());

   comment_1->m_text = "comment_1 text";
   comment_1->m_dt_create = QDateTime::currentDateTime();
   comment_1->m_blog = blog_1;
   comment_2->m_text = "comment_2 text";
   comment_2->m_dt_create = QDateTime::currentDateTime();
   comment_2->m_blog = blog_1;

   daoError = qx::dao::insert(comment_1);
   daoError = qx::dao::insert(comment_2);
   qAssert(qx::dao::count<comment>() == 2);

   // Add 2 categories to 'blog_1' => must insert into extra-table 'category_blog'
   blog_1->m_categoryX.insert(category_1->m_id, category_1);
   blog_1->m_categoryX.insert(category_3->m_id, category_3);
   daoError = qx::dao::save_with_relation("list_category", blog_1);

   // Fetch blog into a new variable with all relation : 'author', 'comment' and 'category'
   blog_ptr blog_tmp; blog_tmp.reset(new blog());
   blog_tmp->m_id = blog_1->m_id;
   daoError = qx::dao::fetch_by_id_with_all_relation(blog_tmp);

   qAssert(blog_tmp->m_commentX.count() == 2);
   qAssert(blog_tmp->m_categoryX.count() == 2);
   qAssert(blog_tmp->m_text == "update blog_text_1");
   qAssert(blog_tmp->m_author && blog_tmp->m_author->m_id == "author_id_2");

   // Fetch blog into a new variable with many relations using "*->*->*->*" (4 levels of relationships)
   blog_tmp.reset(new blog());
   blog_tmp->m_id = blog_1->m_id;
   daoError = qx::dao::fetch_by_id_with_relation("*->*->*->*", blog_tmp);

   qAssert(blog_tmp->m_commentX.count() == 2);
   qAssert(blog_tmp->m_categoryX.count() == 2);
   qAssert(blog_tmp->m_text == "update blog_text_1");
   qAssert(blog_tmp->m_author && blog_tmp->m_author->m_id == "author_id_2");

   // Dump 'blog_tmp' result from database (xml serialization)
   qx::dump(blog_tmp, false);
   qx::dump(blog_tmp, true);

   // Fetch relations defining columns to fetch with syntax { col_1, col_2, etc... }
   list_blog lstBlogComplexRelation;
   daoError = qx::dao::fetch_all_with_relation(QStringList() << "{ blog_text }" << "author_id { name, birthdate }" << "list_comment { comment_text } -> blog_id -> *", lstBlogComplexRelation);
   qx::dump(lstBlogComplexRelation);
   qAssert(lstBlogComplexRelation.size() > 0);
   qAssert(lstBlogComplexRelation[0]->m_text != ""); // Fetched
   qAssert(lstBlogComplexRelation[0]->m_dt_creation.isNull()); // Not fetched
   qAssert(lstBlogComplexRelation[0]->m_author->m_sex == author::unknown); // Not fetched
   qAssert(lstBlogComplexRelation[0]->m_author->m_name != ""); // Fetched
   qAssert(lstBlogComplexRelation[0]->m_commentX.size() > 0);
   qAssert(lstBlogComplexRelation[0]->m_commentX[0]->m_dt_create.isNull()); // Not fetched
   qAssert(lstBlogComplexRelation[0]->m_commentX[0]->m_text != ""); // Fetched
   qAssert(lstBlogComplexRelation[0]->m_commentX[0]->m_blog);

   // Fetch relations defining columns to remove before fetching with syntax -{ col_1, col_2, etc... }
   list_blog lstBlogComplexRelation2;
   daoError = qx::dao::fetch_all_with_relation(QStringList() << "-{ blog_text }" << "author_id -{ name, birthdate }" << "list_comment -{ comment_text } -> blog_id -> *", lstBlogComplexRelation2);
   qx::dump(lstBlogComplexRelation2);
   qAssert(lstBlogComplexRelation2.size() > 0);
   qAssert(lstBlogComplexRelation2[0]->m_text == ""); // Not fetched
   qAssert(! lstBlogComplexRelation2[0]->m_dt_creation.isNull()); // Fetched
   qAssert(lstBlogComplexRelation2[0]->m_author->m_sex != author::unknown); // Fetched
   qAssert(lstBlogComplexRelation2[0]->m_author->m_name == ""); // Not fetched
   qAssert(lstBlogComplexRelation2[0]->m_commentX.size() > 0);
   qAssert(! lstBlogComplexRelation2[0]->m_commentX[0]->m_dt_create.isNull()); // Fetched
   qAssert(lstBlogComplexRelation2[0]->m_commentX[0]->m_text == ""); // Not fetched
   qAssert(lstBlogComplexRelation2[0]->m_commentX[0]->m_blog);

#ifndef _QX_NO_JSON
   // Custom JSON serialization process
   QString customJsonFull = qx::serialization::json::to_string(blog_tmp, 1);
   QString customJsonFiltered = qx::serialization::json::to_string(blog_tmp, 1, "filter: { blog_text } | author_id { name, birthdate } | list_comment { comment_text } -> blog_id -> *");
   qDebug("[QxOrm] custom JSON serialization process (full) : \n%s", qPrintable(customJsonFull));
   qDebug("[QxOrm] custom JSON serialization process (filtered) : \n%s", qPrintable(customJsonFiltered));

   blog_ptr blogFromJsonFull; blogFromJsonFull.reset(new blog());
   blog_ptr blogFromJsonFiltered; blogFromJsonFiltered.reset(new blog());
   qx::serialization::json::from_string(blogFromJsonFull, customJsonFull, 1);
   qx::serialization::json::from_string(blogFromJsonFiltered, customJsonFull, 1, "filter: { blog_text } | author_id { name, birthdate } | list_comment { comment_text } -> blog_id -> *");

   qx::dump(blogFromJsonFull);
   qAssert(blogFromJsonFull->m_commentX.count() == 2);
   qAssert(blogFromJsonFull->m_categoryX.count() == 2);
   qAssert(blogFromJsonFull->m_text == "update blog_text_1");
   qAssert(blogFromJsonFull->m_author && blogFromJsonFull->m_author->m_id == "author_id_2");

   qx::dump(blogFromJsonFiltered);
   qAssert(blogFromJsonFiltered->m_text != ""); // Fetched
   qAssert(blogFromJsonFiltered->m_dt_creation.isNull()); // Not fetched
   qAssert(blogFromJsonFiltered->m_author->m_sex == author::unknown); // Not fetched
   qAssert(blogFromJsonFiltered->m_author->m_name != ""); // Fetched
   qAssert(blogFromJsonFiltered->m_commentX.size() > 0);
   qAssert(blogFromJsonFiltered->m_commentX[0]->m_dt_create.isNull()); // Not fetched
   qAssert(blogFromJsonFiltered->m_commentX[0]->m_text != ""); // Fetched
   qAssert(blogFromJsonFiltered->m_commentX[0]->m_blog);
#endif // _QX_NO_JSON

   // Fetch relations defining columns to fetch with syntax { col_1, col_2, etc... } + custom table alias using syntax <my_table_alias> + custom table alias suffix using syntax <..._my_alias_suffix>
   list_blog lstBlogComplexRelation3;
   daoError = qx::dao::fetch_all_with_relation(QStringList() << "<blog_alias> { blog_text }" << "author_id <author_alias> { name, birthdate }" << "list_comment <list_comment_alias> { comment_text } -> blog_id <blog_alias_2> -> * <..._my_alias_suffix>", lstBlogComplexRelation3);
   qx::dump(lstBlogComplexRelation3);
   qAssert(lstBlogComplexRelation3.size() > 0);
   qAssert(lstBlogComplexRelation3[0]->m_text != ""); // Fetched
   qAssert(lstBlogComplexRelation3[0]->m_dt_creation.isNull()); // Not fetched
   qAssert(lstBlogComplexRelation3[0]->m_author->m_sex == author::unknown); // Not fetched
   qAssert(lstBlogComplexRelation3[0]->m_author->m_name != ""); // Fetched
   qAssert(lstBlogComplexRelation3[0]->m_commentX.size() > 0);
   qAssert(lstBlogComplexRelation3[0]->m_commentX[0]->m_dt_create.isNull()); // Not fetched
   qAssert(lstBlogComplexRelation3[0]->m_commentX[0]->m_text != ""); // Fetched
   qAssert(lstBlogComplexRelation3[0]->m_commentX[0]->m_blog);

   // Check qx::dao::save_with_relation_recursive() function
   daoError = qx::dao::save_with_relation_recursive(blog_tmp);
   qAssert(! daoError.isValid());
   daoError = qx::dao::save_with_relation_recursive(blog_tmp, qx::dao::save_mode::e_update_only);
   qAssert(! daoError.isValid());

   // Call 'age()' method with class name and method name (reflexion)
   qx_bool bInvokeOk = qx::QxClassX::invoke("author", "age", author_1);
   qAssert(bInvokeOk);

   // Check count with relations and filter
   long lBlogCountWithRelation = 0; qx_query queryBlogCountWithRelation;
   daoError = qx::dao::count_with_relation<blog>(lBlogCountWithRelation, QStringList() << "author_id" << "list_comment -> blog_id -> *", queryBlogCountWithRelation);
   qAssert(! daoError.isValid() && (lBlogCountWithRelation > 0));

   // Test 'isDirty()' method
   qx::dao::ptr<blog> blog_isdirty = qx::dao::ptr<blog>(new blog());
   blog_isdirty->m_id = blog_1->m_id;
   daoError = qx::dao::fetch_by_id(blog_isdirty);
   qAssert(! daoError.isValid() && ! blog_isdirty.isDirty());

   blog_isdirty->m_text = "blog property 'text' modified => blog is dirty !!!";
   QStringList lstDiff; bool bDirty = blog_isdirty.isDirty(lstDiff);
   qAssert(bDirty && (lstDiff.count() == 1) && (lstDiff.at(0) == "blog_text"));
   if (bDirty) { qDebug("[QxOrm] test dirty 1 : blog is dirty => '%s'", qPrintable(lstDiff.join("|"))); }

   // Update only property 'm_text' of 'blog_isdirty'
   daoError = qx::dao::update_optimized(blog_isdirty);
   qAssert(! daoError.isValid() && ! blog_isdirty.isDirty());
   qx::dump(blog_isdirty, false);
   qx::dump(blog_isdirty, true);

   // Test 'isDirty()' method with a container
   typedef qx::dao::ptr< QList<author_ptr> > type_lst_author_test_is_dirty;
   type_lst_author_test_is_dirty container_isdirty = type_lst_author_test_is_dirty(new QList<author_ptr>());
   daoError = qx::dao::fetch_all(container_isdirty);
   qAssert(! daoError.isValid() && ! container_isdirty.isDirty() && (container_isdirty->count() == 3));

   author_ptr author_ptr_dirty;
   if (container_isdirty->count() > 1)
   {
      author_ptr_dirty = container_isdirty->at(1);
      author_ptr_dirty->m_name = "author name modified at index 1 => container is dirty !!!";
      bDirty = container_isdirty.isDirty(lstDiff);
      qAssert(bDirty && (lstDiff.count() == 1));
      if (bDirty) { qDebug("[QxOrm] test dirty 2 : container is dirty => '%s'", qPrintable(lstDiff.join("|"))); }
   }

   if (container_isdirty->count() > 2)
   {
      author_ptr_dirty = container_isdirty->at(2);
      author_ptr_dirty->m_birthdate = QDate(1998, 03, 06);
      bDirty = container_isdirty.isDirty(lstDiff);
      qAssert(bDirty && (lstDiff.count() == 2));
      if (bDirty) { qDebug("[QxOrm] test dirty 3 : container is dirty => '%s'", qPrintable(lstDiff.join("|"))); }
   }

   // Update only property 'm_name' at position 1, only property 'm_birthdate' at position 2 and nothing at position 0
   daoError = qx::dao::update_optimized(container_isdirty);
   qAssert(! daoError.isValid() && ! container_isdirty.isDirty());
   qx::dump(container_isdirty, false);
   qx::dump(container_isdirty, true);

   // Fetch only property 'm_dt_creation' of blog
   QStringList lstColumns = QStringList() << "date_creation";
   list_blog lst_blog_with_only_date_creation;
   daoError = qx::dao::fetch_all(lst_blog_with_only_date_creation, NULL, lstColumns);
   qAssert(! daoError.isValid() && (lst_blog_with_only_date_creation.size() > 0));
   if ((lst_blog_with_only_date_creation.size() > 0) && (lst_blog_with_only_date_creation[0].get() != NULL))
   { qAssert(lst_blog_with_only_date_creation[0]->m_text.isEmpty()); }
   qx::dump(lst_blog_with_only_date_creation, false);
   qx::dump(lst_blog_with_only_date_creation, true);

   // Dump all registered classes into QxOrm context (introspection engine)
   qx::QxClassX::dumpAllClasses();

   // Call a custom SQL query or a stored procedure
   qx_query testStoredProc("SELECT * FROM author");
   daoError = qx::dao::call_query(testStoredProc);
   qAssert(! daoError.isValid());
   testStoredProc.dumpSqlResult();

   // Call a custom SQL query or a stored procedure and fetch automatically properties (with a collection of items)
   qx_query testStoredProcBis("SELECT * FROM author");
   authorX.clear();
   daoError = qx::dao::execute_query(testStoredProcBis, authorX);
   qAssert(! daoError.isValid()); qAssert(authorX.count() > 0);
   qx::dump(authorX, false);
   qx::dump(authorX, true);

   // Call a custom SQL query or a stored procedure and fetch automatically properties
   qx_query testStoredProcThird("SELECT name, category_id FROM category");
   category_ptr category_tmp = category_ptr(new category());
   daoError = qx::dao::execute_query(testStoredProcThird, category_tmp);
   qAssert(! daoError.isValid()); qAssert(category_tmp->m_id != 0);
   qx::dump(category_tmp, false);
   qx::dump(category_tmp, true);

   // Create several blogs
   blog_tmp.reset(new blog());
   blog_tmp->m_id = blog_1->m_id;
   daoError = qx::dao::fetch_by_id_with_relation("*", blog_tmp);
   blog_ptr blog_cloned = qx::clone(* blog_tmp);
   daoError = qx::dao::save_with_relation_recursive(blog_cloned, qx::dao::save_mode::e_insert_only); qAssert(! daoError.isValid());
   blog_cloned = qx::clone(* blog_tmp);
   daoError = qx::dao::save_with_relation_recursive(blog_cloned, qx::dao::save_mode::e_insert_only); qAssert(! daoError.isValid());
   blog_cloned = qx::clone(* blog_tmp);
   daoError = qx::dao::save_with_relation_recursive(blog_cloned, qx::dao::save_mode::e_insert_only); qAssert(! daoError.isValid());
#endif // _QX_TEST_WITH_MONGODB
}

void prepareDatabaseSQLite()
{
   prepareDatabaseGeneric(true);
}

void prepareDatabaseMongoDB()
{
#ifdef _QX_TEST_WITH_MONGODB
   // Basic CRUD operations
   mongoBasicCRUDOnAuthor(true);
   mongoBasicCRUDOnAuthor(false);

   // Populate category collection
   mongoBasicCRUDOnCategory();

   // Populate blog collection
   mongoBasicCRUDOnBlog();

   // Process some complex queries on blog collection (with relationships)
   mongoComplexQueriesOnBlog();

   // Process some others operations on database
   mongoMiscellaneousOperations();
#endif // _QX_TEST_WITH_MONGODB
}

void prepareDatabasePostgreSQL()
{
   prepareDatabaseGeneric(false);
}

void prepareDatabaseMySQL()
{
   prepareDatabaseGeneric(false);
}

void prepareDatabaseMariaDB()
{
   prepareDatabaseMySQL();
}

void prepareDatabaseOracle()
{
   prepareDatabaseGeneric(false);
}

void prepareDatabaseMSSqlServer()
{
   prepareDatabaseGeneric(false);
}

QString pingDatabase()
{
   QString pong;
   try
   {
      QString dbType = qEnvironmentVariable("QX_DB");
      if ((dbType.isEmpty()) || (dbType == "sqlite")) { pong = pingDatabaseSQLite(); }
      else if (dbType == "mongodb") { pong = pingDatabaseMongoDB(); }
      else if (dbType == "postgresql") { pong = pingDatabasePostgreSQL(); }
      else if (dbType == "mysql") { pong = pingDatabaseMySQL(); }
      else if (dbType == "mariadb") { pong = pingDatabaseMariaDB(); }
      else if (dbType == "oracle") { pong = pingDatabaseOracle(); }
      else if (dbType == "mssqlserver") { pong = pingDatabaseMSSqlServer(); }
      else { pong = "Unknown database type '" + dbType + "'"; qDebug("[QxOrm] %s", qPrintable(pong)); qAssert(false); }
   }
   catch(...)
   {
      pong = "An error occurred pinging database";
      qDebug("[QxOrm] %s", qPrintable(pong));
   }
   return pong;
}

QString pingDatabaseSQLite()
{
   qx_query query("select sqlite_version()");
   QSqlError daoError = qx::dao::call_query(query);
   if (daoError.isValid()) { return "ERROR"; }
   return query.getSqlResultAt(0, 0).toString();
}

QString pingDatabaseMongoDB()
{
   qx_query query("{ \"buildInfo\" : 1 }");
   QSqlError daoError = qx::dao::call_query(query);
   if (daoError.isValid()) { return "ERROR"; }
   QVariantMap buildInfo;
   QString response = query.response().toString();
   qx::serialization::json::from_string(buildInfo, response);
   return buildInfo.value("version").toString();
}

QString pingDatabasePostgreSQL()
{
   qx_query query("SELECT version()");
   QSqlError daoError = qx::dao::call_query_without_prepare(query);
   if (daoError.isValid()) { return "ERROR"; }
   return query.getSqlResultAt(0, 0).toString();
}

QString pingDatabaseMySQL()
{
   qx_query query("SELECT VERSION()");
   QSqlError daoError = qx::dao::call_query_without_prepare(query);
   if (daoError.isValid()) { return "ERROR"; }
   return query.getSqlResultAt(0, 0).toString();
}

QString pingDatabaseMariaDB()
{
   return pingDatabaseMySQL();
}

QString pingDatabaseOracle()
{
   return "TODO...";
}

QString pingDatabaseMSSqlServer()
{
   return "TODO...";
}

#ifdef _QX_TEST_WITH_MONGODB
void mongoBasicCRUDOnAuthor(bool withDelete)
{
   // Test delete all author
   QSqlError daoError = qx::dao::delete_all<author>(); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<author>() == 0);

   // Test insert one without id
   author_ptr author_1 = std::make_shared<author>();
   author_1->m_name = "author_1";
   author_1->m_sex = author::male;
   author_1->m_birthdate = QDate(1998, 07, 12);
   daoError = qx::dao::insert(author_1); qAssert(! daoError.isValid());
   qAssert(! author_1->m_id.isEmpty());
   qAssert(qx::dao::count<author>() == 1);

   // Test insert one author with a custom id
   author_ptr author_2 = std::make_shared<author>();
   author_2->m_id = "my_custom_id_author_2";
   author_2->m_name = "author_2";
   author_2->m_sex = author::female;
   author_2->m_birthdate = QDate(2003, 02, 28);
   daoError = qx::dao::insert(author_2); qAssert(! daoError.isValid());
   qAssert(author_2->m_id == "my_custom_id_author_2");
   qAssert(qx::dao::count<author>() == 2);

   // Test insert many author with/without ids
   QList<author> authorX;
   author author_3; author_3.m_name = "author_3"; author_3.m_sex = author::female; author_3.m_birthdate = QDate(1968, 05, 01); authorX.append(author_3);
   author author_4; author_4.m_id = "my_custom_id_author_4"; author_4.m_name = "author_4"; author_4.m_sex = author::male; author_4.m_birthdate = QDate(1980, 12, 19); authorX.append(author_4);
   author author_5; author_5.m_name = "author_5"; author_5.m_sex = author::female; author_5.m_birthdate = QDate(1978, 03, 03); authorX.append(author_5);
   daoError = qx::dao::insert(authorX); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<author>() == 5);
   qAssert(authorX.at(1).m_id == "my_custom_id_author_4");
   QString author_3_id = ((authorX.count() > 0) ? authorX.at(0).m_id : QString()); qAssert(! author_3_id.isEmpty());
   QString author_5_id = ((authorX.count() > 2) ? authorX.at(2).m_id : QString()); qAssert(! author_5_id.isEmpty());

   // Test update one author
   if (authorX.count() > 0)
   {
      author_3 = authorX.at(0);
      author_3.m_name = "author_3_modified";
      daoError = qx::dao::update(author_3); qAssert(! daoError.isValid());
   }

   // Test update many author
   authorX.clear();
   author_3.m_name = "author_3_modified_twice"; authorX.append(author_3);
   author_2->m_name = "author_2_modified"; authorX.append(* author_2);
   author_1->m_name = "author_1_modified"; authorX.append(* author_1);
   daoError = qx::dao::update(authorX); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<author>() == 5);

   // Test fetch all author (inside QList)
   authorX.clear();
   daoError = qx::dao::fetch_all(authorX); qAssert(! daoError.isValid());
   qAssert(authorX.count() == 5);
   qx::dump(authorX);

   // Test fetch all author (inside QHash by id)
   QHash<QString, author_ptr> authorXById;
   daoError = qx::dao::fetch_all(authorXById); qAssert(! daoError.isValid());
   qAssert(authorXById.count() == 5);
   qx::dump(authorXById);

   // Test fetch author by query (only female)
   list_author list_of_female_author;
   qx_query query("{ \"sex\" : " + QString::number(static_cast<int>(author::female)) + " }");
   daoError = qx::dao::fetch_by_query(query, list_of_female_author); qAssert(! daoError.isValid());
   qAssert(list_of_female_author.count() == 3);
   qx::dump(list_of_female_author);

   // Test fetch by query using MongoDB aggregation framework (only female)
   list_author list_of_female_author_other;
   qx_query queryAggregate("aggregate", "[ { \"$match\" : { \"sex\" : " + QString::number(static_cast<int>(author::female)) + " } } ]");
   daoError = qx::dao::fetch_by_query(queryAggregate, list_of_female_author_other); qAssert(! daoError.isValid());
   qAssert(list_of_female_author_other.count() == 3);
   qx::dump(list_of_female_author_other);

   // Test fetch by query (only female) adding 'sort', 'limit', 'skip', etc... commands (see second query QStringList parameter)
   list_of_female_author_other.clear();
   qx_query queryOpts(QStringList() << "{ \"sex\" : " + QString::number(static_cast<int>(author::female)) + " }"
                                    << "{ \"sort\" : { \"sex\" : -1 }, \"limit\" : 2 }");
   daoError = qx::dao::fetch_by_query(queryOpts, list_of_female_author_other); qAssert(! daoError.isValid());
   qAssert(list_of_female_author_other.count() == 2);
   qx::dump(list_of_female_author_other);

   // Test update one author after fetch
   if (authorX.count() > 4)
   {
      author_5 = authorX.at(4);
      author_5.m_name = "author_5_modified_after_fetch";
      daoError = qx::dao::update(author_5); qAssert(! daoError.isValid());
      qAssert(qx::dao::count<author>() == 5);
   }

   // Test update many author after fetch
   author_ptr pAuthor;
   if (list_of_female_author.count() > 2)
   {
      pAuthor = list_of_female_author.getByIndex(0);
      pAuthor->m_name = pAuthor->m_name + "_female_modified_after_fetch";
      pAuthor = list_of_female_author.getByIndex(1);
      pAuthor->m_name = pAuthor->m_name + "_female_modified_after_fetch";
      pAuthor = list_of_female_author.getByIndex(2);
      pAuthor->m_name = pAuthor->m_name + "_female_modified_after_fetch";
      daoError = qx::dao::update(list_of_female_author); qAssert(! daoError.isValid());
      qAssert(qx::dao::count<author>() == 5);
   }

   // Test fetch one author by id
   pAuthor.reset(new author());
   pAuthor->m_id = "my_custom_id_author_2";
   daoError = qx::dao::fetch_by_id(pAuthor); qAssert(! daoError.isValid());
   qAssert(pAuthor->m_id == "my_custom_id_author_2");
   qAssert(! pAuthor->m_birthdate.isNull());

   // Test fetch many author by id
   authorX.clear();
   QHashIterator<QString, author_ptr> itr(authorXById);
   while (itr.hasNext()) { itr.next(); author author_tmp; author_tmp.m_id = itr.key(); authorX.append(author_tmp); }
   daoError = qx::dao::fetch_by_id(authorX); qAssert(! daoError.isValid());
   qAssert(authorX.count() == 5);
   qAssert(! authorX.at(2).m_birthdate.isNull());
   qx::dump(authorX);

   if (! withDelete) { return; }

   // Test delete one author by id
   pAuthor.reset(new author());
   pAuthor->m_id = "my_custom_id_author_4";
   daoError = qx::dao::delete_by_id(pAuthor); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<author>() == 4);

   // Test delete many author by id
   authorX.clear();
   { author author_tmp; author_tmp.m_id = author_3_id; authorX.append(author_tmp); }
   { author author_tmp; author_tmp.m_id = author_5_id; authorX.append(author_tmp); }
   daoError = qx::dao::delete_by_id(authorX); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<author>() == 2);

   // Test delete author by query (all male)
#ifdef Q_COMPILER_INITIALIZER_LISTS
   int iMale = static_cast<int>(author::male);
   query = qx_query{ { "sex", iMale } };
#else // Q_COMPILER_INITIALIZER_LISTS
   query = qx_query("{ \"sex\" : " + QString::number(static_cast<int>(author::male)) + " }");
#endif // Q_COMPILER_INITIALIZER_LISTS
   daoError = qx::dao::delete_by_query<author>(query); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<author>() == 1);

   // Now delete all author
   daoError = qx::dao::delete_all<author>(); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<author>() == 0);
}

void mongoBasicCRUDOnCategory()
{
   // Create 3 categories
   category_ptr category_1 = category_ptr(new category());
   category_ptr category_2 = category_ptr(new category());
   category_ptr category_3 = category_ptr(new category());

   category_1->m_name = "category_1"; category_1->m_desc = "desc_1";
   category_2->m_name = "category_2"; category_2->m_desc = "desc_2";
   category_3->m_name = "category_3"; category_3->m_desc = "desc_3";

   // Insert 3 categories into database, use 'db' parameter for the transaction
   QSqlError daoError = qx::dao::insert(category_1); qAssert(! daoError.isValid());
   daoError = qx::dao::insert(category_2); qAssert(! daoError.isValid());
   daoError = qx::dao::insert(category_3); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<category>() == 3);
}

void mongoBasicCRUDOnBlog()
{
   // Search author_1
   author_ptr author_1 = std::make_shared<author>();
   qx_query query("{ \"name\" : \"author_1_modified\" }");
   QSqlError daoError = qx::dao::fetch_by_query<author>(query, (* author_1)); qAssert(! daoError.isValid());
   qAssert(author_1 && ! author_1->m_id.isEmpty());

   // Search author_2
   author_ptr author_2 = std::make_shared<author>();
   author_2->m_id = "my_custom_id_author_2";
   daoError = qx::dao::fetch_by_id(author_2); qAssert(! daoError.isValid());
   qAssert(author_2 && ! author_2->m_id.isEmpty());

   // Create a blog from class name (factory)
   qx::any blog_any = qx::create("blog");
   blog_ptr blog_1;
   try { blog_1 = qx::any_cast<blog_ptr>(blog_any); }
   catch (...) { blog_1.reset(new blog()); }
   blog_1->m_text = "blog_text_1";
   blog_1->m_dt_creation = QDateTime::currentDateTime();
   blog_1->m_author = author_1;

   // Insert 'blog_1' into database with 'save()' method
   daoError = qx::dao::save(blog_1); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<blog>() == 1);

   // Modify 'blog_1' properties and save into database
   blog_1->m_text = "update blog_text_1";
   blog_1->m_author = author_2;
   daoError = qx::dao::save(blog_1); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<blog>() == 1);

   // Add 2 comments to 'blog_1'
   comment_ptr comment_1; comment_1.reset(new comment());
   comment_ptr comment_2; comment_2.reset(new comment());

   comment_1->m_text = "comment_1 text";
   comment_1->m_dt_create = QDateTime::currentDateTime();
   comment_1->m_blog = blog_1;
   comment_2->m_text = "comment_2 text";
   comment_2->m_dt_create = QDateTime::currentDateTime();
   comment_2->m_blog = blog_1;

   daoError = qx::dao::insert(comment_1); qAssert(! daoError.isValid());
   daoError = qx::dao::insert(comment_2); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<comment>() == 2);

   // Add 2 categories to 'blog_1' => 'list_category' is not defined as relationship in 'blog' class => so all categories are embedded in 'blog' collection (instead of referenced for relationships)
   list_category categories;
   daoError = qx::dao::fetch_all(categories); qAssert(! daoError.isValid());
   qAssert(categories.count() == 3);

   if (categories.count() > 2)
   {
      category_ptr category_1 = categories.getByIndex(0);
      category_ptr category_3 = categories.getByIndex(2);
      blog_1->m_categoryX.insert(category_1->m_id, category_1);
      blog_1->m_categoryX.insert(category_3->m_id, category_3);
      daoError = qx::dao::save(blog_1); qAssert(! daoError.isValid());
      qAssert(qx::dao::count<blog>() == 1);
   }

   // Push a second blog
   blog_ptr blog_2 = std::make_shared<blog>();
   blog_2->m_text = "blog_text_2";
   daoError = qx::dao::save(blog_2); qAssert(! daoError.isValid());
}

void mongoComplexQueriesOnBlog()
{
   // Fetch all blogs (without relation)
   list_blog allBlogs;
   QSqlError daoError = qx::dao::fetch_all(allBlogs); qAssert(! daoError.isValid());
   qx::dump(allBlogs);
   qAssert(allBlogs.size() == 2);
   if (allBlogs.size() != 2) { return; }

   // Fetch blog into a new variable with all relations : 'author', 'comment' and 'category' (MongoDB version 3.6+ is required for relationships)
   blog_ptr blog_tmp = std::make_shared<blog>();
   blog_tmp->m_id = allBlogs[0]->m_id;
   daoError = qx::dao::fetch_by_id_with_all_relation(blog_tmp); qAssert(! daoError.isValid());
   qx::dump(blog_tmp);
   qAssert(blog_tmp->m_commentX.count() == 2);
   qAssert(blog_tmp->m_categoryX.count() == 2);
   qAssert(blog_tmp->m_text == "update blog_text_1");
   qAssert(blog_tmp->m_author && (blog_tmp->m_author->m_id == "my_custom_id_author_2"));

   // Fetch blog into a new variable with many relations using "*->*->*->*" (4 levels of relationships)
   blog_tmp.reset(new blog());
   blog_tmp->m_id = allBlogs[0]->m_id;
   daoError = qx::dao::fetch_by_id_with_relation("*->*->*->*", blog_tmp); qAssert(! daoError.isValid());
   qx::dump(blog_tmp);
   qAssert(blog_tmp->m_commentX.count() == 2);
   qAssert(blog_tmp->m_categoryX.count() == 2);
   qAssert(blog_tmp->m_text == "update blog_text_1");
   qAssert(blog_tmp->m_author && blog_tmp->m_author->m_id == "my_custom_id_author_2");
   qAssert(blog_tmp->m_author->m_blogX[0]->m_commentX.count() > 0);

   // Fetch blog into a new variable with many relations using "*->*" (2 levels of relationships)
   blog_tmp.reset(new blog());
   blog_tmp->m_id = allBlogs[0]->m_id;
   daoError = qx::dao::fetch_all_with_relation("*->*", blog_tmp); qAssert(! daoError.isValid());
   qx::dump(blog_tmp);
   qAssert(blog_tmp->m_commentX.count() == 2);
   qAssert(blog_tmp->m_categoryX.count() == 2);
   qAssert(blog_tmp->m_text == "update blog_text_1");
   qAssert(blog_tmp->m_author && blog_tmp->m_author->m_id == "my_custom_id_author_2");
   qAssert(blog_tmp->m_author->m_blogX[0]->m_commentX.count() == 0);

   // Fetch only property 'm_dt_creation' of blog
   QStringList lstColumns = QStringList() << "date_creation";
   list_blog lst_blog_with_only_date_creation;
   daoError = qx::dao::fetch_all(lst_blog_with_only_date_creation, NULL, lstColumns);
   qAssert(! daoError.isValid() && (lst_blog_with_only_date_creation.size() > 0));
   if ((lst_blog_with_only_date_creation.size() > 0) && (lst_blog_with_only_date_creation[0].get() != NULL))
   { qAssert(lst_blog_with_only_date_creation[0]->m_text.isEmpty()); }
   qx::dump(lst_blog_with_only_date_creation);

   // Fetch relations defining fields to fetch with syntax { col_1, col_2, etc... }
   list_blog lstBlogComplexRelation;
   daoError = qx::dao::fetch_all_with_relation(QStringList() << "{ blog_text }" << "author_id { name, birthdate }" << "list_comment { comment_text } -> blog_id -> *", lstBlogComplexRelation); qAssert(! daoError.isValid());
   qx::dump(lstBlogComplexRelation);
   qAssert(lstBlogComplexRelation.size() > 0);
   qAssert(lstBlogComplexRelation[0]->m_text != ""); // Fetched
   qAssert(lstBlogComplexRelation[0]->m_dt_creation.isNull()); // Not fetched
   qAssert(lstBlogComplexRelation[0]->m_author->m_sex == author::unknown); // Not fetched
   qAssert(lstBlogComplexRelation[0]->m_author->m_name != ""); // Fetched
   qAssert(lstBlogComplexRelation[0]->m_commentX.size() > 0);
   qAssert(lstBlogComplexRelation[0]->m_commentX[0]->m_dt_create.isNull()); // Not fetched
   qAssert(lstBlogComplexRelation[0]->m_commentX[0]->m_text != ""); // Fetched
   qAssert(lstBlogComplexRelation[0]->m_commentX[0]->m_blog);

   // Fetch relations defining columns to remove before fetching with syntax -{ col_1, col_2, etc... }
   list_blog lstBlogComplexRelation2;
   daoError = qx::dao::fetch_all_with_relation(QStringList() << "- { blog_text }" << "author_id -{ name, birthdate }" << "list_comment -{ comment_text } -> blog_id -> *", lstBlogComplexRelation2); qAssert(! daoError.isValid());
   qx::dump(lstBlogComplexRelation2);
   qAssert(lstBlogComplexRelation2.size() > 0);
   qAssert(lstBlogComplexRelation2[0]->m_text == ""); // Not fetched
   qAssert(! lstBlogComplexRelation2[0]->m_dt_creation.isNull()); // Fetched
   qAssert(lstBlogComplexRelation2[0]->m_author->m_sex != author::unknown); // Fetched
   qAssert(lstBlogComplexRelation2[0]->m_author->m_name == ""); // Not fetched
   qAssert(lstBlogComplexRelation2[0]->m_commentX.size() > 0);
   qAssert(! lstBlogComplexRelation2[0]->m_commentX[0]->m_dt_create.isNull()); // Fetched
   qAssert(lstBlogComplexRelation2[0]->m_commentX[0]->m_text == ""); // Not fetched
   qAssert(lstBlogComplexRelation2[0]->m_commentX[0]->m_blog);

   // Check qx::dao::save_with_relation_recursive() function
   daoError = qx::dao::save_with_relation_recursive(blog_tmp); qAssert(! daoError.isValid());
   daoError = qx::dao::save_with_relation_recursive(blog_tmp, qx::dao::save_mode::e_update_only); qAssert(! daoError.isValid());

   // Fetch the second blog stored in database
   blog_tmp = std::make_shared<blog>();
   blog_tmp->m_id = allBlogs[1]->m_id;
   daoError = qx::dao::fetch_by_id_with_all_relation(blog_tmp); qAssert(! daoError.isValid());
   qx::dump(blog_tmp);
   qAssert(blog_tmp->m_text == "blog_text_2");
   qAssert(blog_tmp->m_author == NULL);
   qAssert(blog_tmp->m_categoryX.size() == 0);
   qAssert(blog_tmp->m_commentX.size() == 0);

   // Fetch 2 blogs by id with their relationships
   QList<blog_ptr> lstBlogById;
   blog_tmp = std::make_shared<blog>(); blog_tmp->m_id = allBlogs[1]->m_id; lstBlogById.append(blog_tmp);
   blog_tmp = std::make_shared<blog>(); blog_tmp->m_id = allBlogs[0]->m_id; lstBlogById.append(blog_tmp);
   daoError = qx::dao::fetch_by_id_with_all_relation(lstBlogById); qAssert(! daoError.isValid());
   qx::dump(lstBlogById);
}

void mongoMiscellaneousOperations()
{
   // Dump all registered classes into QxOrm context (introspection engine)
   qx::QxClassX::dumpAllClasses();

   // Call 'age()' method with class name and method name (reflexion)
   author author_1; qx_bool bInvokeOk = qx::QxClassX::invoke("author", "age", author_1); qAssert(bInvokeOk);

   // Fetch all blogs (without relation)
   list_blog allBlogs; QSqlError daoError = qx::dao::fetch_all(allBlogs); qAssert(! daoError.isValid());
   qx::dump(allBlogs); qAssert(allBlogs.size() == 2);
   if (allBlogs.size() != 2) { return; }

   // Test 'isDirty()' method
   qx::dao::ptr<blog> blog_isdirty = qx::dao::ptr<blog>(new blog());
   blog_isdirty->m_id = allBlogs[0]->m_id;
   daoError = qx::dao::fetch_by_id(blog_isdirty);
   qAssert(! daoError.isValid() && ! blog_isdirty.isDirty());

   blog_isdirty->m_text = "blog property 'text' modified => blog is dirty !!!";
   QStringList lstDiff; bool bDirty = blog_isdirty.isDirty(lstDiff);
   qAssert(bDirty && (lstDiff.count() == 1) && (lstDiff.at(0) == "blog_text"));
   if (bDirty) { qDebug("[QxOrm] test dirty 1 : blog is dirty => '%s'", qPrintable(lstDiff.join("|"))); }

   // Update only property 'm_text' of 'blog_isdirty'
   daoError = qx::dao::update_optimized(blog_isdirty);
   qAssert(! daoError.isValid() && ! blog_isdirty.isDirty());
   qx::dump(blog_isdirty);

   // Test 'isDirty()' method with a container
   typedef qx::dao::ptr< QList<author_ptr> > type_lst_author_test_is_dirty;
   type_lst_author_test_is_dirty container_isdirty = type_lst_author_test_is_dirty(new QList<author_ptr>());
   daoError = qx::dao::fetch_all(container_isdirty);
   qAssert(! daoError.isValid() && ! container_isdirty.isDirty() && (container_isdirty->count() == qx::dao::count<author>()));

   author_ptr author_ptr_dirty = container_isdirty->at(1);
   author_ptr_dirty->m_name = "author name modified at index 1 => container is dirty !!!";
   bDirty = container_isdirty.isDirty(lstDiff);
   qAssert(bDirty && (lstDiff.count() == 1));
   if (bDirty) { qDebug("[QxOrm] test dirty 2 : container is dirty => '%s'", qPrintable(lstDiff.join("|"))); }

   author_ptr_dirty = container_isdirty->at(2);
   author_ptr_dirty->m_birthdate = QDate(1998, 03, 06);
   bDirty = container_isdirty.isDirty(lstDiff);
   qAssert(bDirty && (lstDiff.count() == 2));
   if (bDirty) { qDebug("[QxOrm] test dirty 3 : container is dirty => '%s'", qPrintable(lstDiff.join("|"))); }

   // Update only property 'm_name' at position 1, only property 'm_birthdate' at position 2 and nothing at position 0
   daoError = qx::dao::update_optimized(container_isdirty);
   qAssert(! daoError.isValid() && ! container_isdirty.isDirty());
   qx::dump(container_isdirty);

   // Call a custom query and get JSON response as QVariantMap
   qx_query customQuery("{ \"find\": \"author\", \"filter\": { } }");
   daoError = qx::dao::call_query(customQuery); qAssert(! daoError.isValid());
   QString responseCustomQuery = customQuery.response().toString();
   QVariantMap responseCustomQueryAsJson;
   qx::serialization::json::from_string(responseCustomQueryAsJson, responseCustomQuery);
   qx::dump(responseCustomQueryAsJson);

   // Call a custom query with cursor and get JSON response as QList<QVariantMap>
   qx_query customQueryCursor("cursor", "{ \"find\": \"author\", \"filter\": { } }");
   daoError = qx::dao::call_query(customQueryCursor); qAssert(! daoError.isValid());
   QString responseCustomQueryCursor = customQueryCursor.response().toString();
   QList<QVariantMap> responseCustomQueryCursorAsJson;
   qx::serialization::json::from_string(responseCustomQueryCursorAsJson, responseCustomQueryCursor);
   qx::dump(responseCustomQueryCursorAsJson);
   qAssert(responseCustomQueryCursorAsJson.count() == qx::dao::count<author>());

   // Test delete by query using MongoDB aggregation framework (delete all female)
   qx_query queryAggregate("aggregate", "[ { \"$match\" : { \"sex\" : " + QString::number(static_cast<int>(author::female)) + " } } ]");
   daoError = qx::dao::delete_by_query<author>(queryAggregate); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<author>() == 2);
}
#endif // _QX_TEST_WITH_MONGODB
