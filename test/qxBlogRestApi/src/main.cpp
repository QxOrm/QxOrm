#include "../include/precompiled.h"

#if (QT_VERSION >= 0x050000)
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qtableview.h>
#include <QtQuick/qquickview.h>
#include <QtQml/qqmlcontext.h>
#else // (QT_VERSION >= 0x050000)
#include <QtGui/qapplication.h>
#include <QtGui/qtableview.h>
#include <QtDeclarative/qdeclarativeview.h>
#include <QtDeclarative/qdeclarativecontext.h>
#endif // (QT_VERSION >= 0x050000)

#include <QtGui/qdesktopservices.h>

#include "../include/blog.h"
#include "../include/author.h"
#include "../include/comment.h"
#include "../include/category.h"

#include <QxOrm_Impl.h>

int main(int argc, char * argv[])
{
   // Qt application
   QApplication app(argc, argv);
   QFile::remove("./qxBlogRestApi.sqlite");

   // Parameters to connect to database
   qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
   qx::QxSqlDatabase::getSingleton()->setDatabaseName("./qxBlogRestApi.sqlite");
   qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
   qx::QxSqlDatabase::getSingleton()->setUserName("root");
   qx::QxSqlDatabase::getSingleton()->setPassword("");
   qx::QxSqlDatabase::getSingleton()->setFormatSqlQueryBeforeLogging(true);

   // Only for debug purpose : assert if invalid offset detected fetching a relation
   qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);

   // Create all tables in database
   QSqlError daoError = qx::dao::create_table<author>();
   daoError = qx::dao::create_table<comment>();
   daoError = qx::dao::create_table<category>();
   daoError = qx::dao::create_table<blog>();

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

#if (QT_VERSION >= 0x050000)

   {
      qx::QxRestApi api;

      QQuickView qmlView;
#if (QT_VERSION >= 0x060000)
      QString sQmlFile = "qrc:/documents/test_rest_api_qt6.qml";
#else // (QT_VERSION >= 0x060000)
      QString sQmlFile = "qrc:/documents/test_rest_api.qml";
#endif // (QT_VERSION >= 0x060000)

      qmlView.rootContext()->setContextProperty("qxRestApi", (& api));
      qmlView.setResizeMode(QQuickView::SizeRootObjectToView);
      qmlView.setSource(QUrl(sQmlFile));
      qmlView.show();
      qApp->exec();
   }

#ifdef _QX_ENABLE_QT_NETWORK

   {
      // Just to be sure to have static files on the system
      QDir appPath(QDir::currentPath()); appPath.mkdir("files");
      QFile::copy(":/documents/test_http_server.html", appPath.filePath("files/test_http_server.html"));
      QFile::copy(":/documents/logo_qxorm_and_qxee.png", appPath.filePath("files/logo_qxorm_and_qxee.png"));
      QFile::copy(":/documents/jquery.js", appPath.filePath("files/jquery.js"));

      // HTTP server settings
      qx::service::QxConnect * serverSettings = qx::service::QxConnect::getSingleton();
      serverSettings->setKeepAlive(5000);
      serverSettings->setCompressData(true);
      serverSettings->setThreadCount(50);
      serverSettings->setPort(9642);

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

      // Start HTTP server
      httpServer.startServer();

      // Open default web browser to connect to QxOrm HTTP server instance
#ifndef QT_NO_SSL
      if (serverSettings->getSSLEnabled()) { QDesktopServices::openUrl(QUrl("https://localhost:9642/files/test_http_server.html")); }
      else { QDesktopServices::openUrl(QUrl("http://localhost:9642/files/test_http_server.html")); }
#else // QT_NO_SSL
      QDesktopServices::openUrl(QUrl("http://localhost:9642/files/test_http_server.html"));
#endif // QT_NO_SSL

      QQuickView qmlView;
#if (QT_VERSION >= 0x060000)
      QString sQmlFile = "qrc:/documents/test_http_server_qt6.qml";
#else // (QT_VERSION >= 0x060000)
      QString sQmlFile = "qrc:/documents/test_http_server.qml";
#endif // (QT_VERSION >= 0x060000)

      qmlView.rootContext()->setContextProperty("qxHttpServer", (& httpServer));
      qmlView.setResizeMode(QQuickView::SizeRootObjectToView);
      qmlView.setSource(QUrl(sQmlFile));
      qmlView.show();
      qApp->exec();
   }

#else // _QX_ENABLE_QT_NETWORK

   qDebug("[QxOrm] qxBlogRestApi example project : %s", "cannot start QxOrm HTTP server because _QX_ENABLE_QT_NETWORK compilation option is not defined");

#endif // _QX_ENABLE_QT_NETWORK

#else // (QT_VERSION >= 0x050000)

   qDebug("[QxOrm] %s", "qxBlogRestApi example project only works with Qt5 or +");

#endif // (QT_VERSION >= 0x050000)

   return 0;
}
