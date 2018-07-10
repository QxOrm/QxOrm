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

#include "../include/blog.h"
#include "../include/author.h"
#include "../include/comment.h"
#include "../include/category.h"

#include "../include/model_view_from_qxee/blog.model_view.gen.h"

#include <QxOrm_Impl.h>

void init_data();
void test_qt_widget();
void test_qml_view();
void test_qml_view_with_relationship();

int main(int argc, char * argv[])
{
   QApplication app(argc, argv);
   init_data();
   test_qt_widget();
   test_qml_view();
   test_qml_view_with_relationship();
   return 0;
}

void init_data()
{
   QFile::remove("./qxBlog.sqlite");

   // Parameters to connect to database
   qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
   qx::QxSqlDatabase::getSingleton()->setDatabaseName("./qxBlog.sqlite");
   qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
   qx::QxSqlDatabase::getSingleton()->setUserName("root");
   qx::QxSqlDatabase::getSingleton()->setPassword("");

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

   // Clone author n°2 : 'author_id_2'
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
   qx::dump(list_of_female_author);

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
   boost::any blog_any = qx::create("blog");
   blog_ptr blog_1;
   try { blog_1 = boost::any_cast<blog_ptr>(blog_any); }
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
   qx::dump(blog_tmp);

   // Check qx::dao::save_with_relation_recursive() function
   daoError = qx::dao::save_with_relation_recursive(blog_tmp);
   qAssert(! daoError.isValid());
   daoError = qx::dao::save_with_relation_recursive(blog_tmp, qx::dao::save_mode::e_update_only);
   qAssert(! daoError.isValid());

   // Call 'age()' method with class name and method name (reflexion)
   qx_bool bInvokeOk = qx::QxClassX::invoke("author", "age", author_1);
   qAssert(bInvokeOk);

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
   qx::dump(blog_isdirty);

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
   qx::dump(container_isdirty);

   // Fetch only property 'm_dt_creation' of blog
   QStringList lstColumns = QStringList() << "date_creation";
   list_blog lst_blog_with_only_date_creation;
   daoError = qx::dao::fetch_all(lst_blog_with_only_date_creation, NULL, lstColumns);
   qAssert(! daoError.isValid() && (lst_blog_with_only_date_creation.size() > 0));
   if ((lst_blog_with_only_date_creation.size() > 0) && (lst_blog_with_only_date_creation[0].get() != NULL))
   { qAssert(lst_blog_with_only_date_creation[0]->m_text.isEmpty()); }
   qx::dump(lst_blog_with_only_date_creation);

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
   qx::dump(authorX);

   // Call a custom SQL query or a stored procedure and fetch automatically properties
   qx_query testStoredProcThird("SELECT name, category_id FROM category");
   category_ptr category_tmp = category_ptr(new category());
   daoError = qx::dao::execute_query(testStoredProcThird, category_tmp);
   qAssert(! daoError.isValid()); qAssert(category_tmp->m_id != 0);
   qx::dump(category_tmp);

   // Just to test compilation of nested models
   qx::IxModel * pNestedModel1 = qx::model_view::create_nested_model(NULL, QModelIndex(), category_tmp);    Q_UNUSED(pNestedModel1);
   qx::IxModel * pNestedModel2 = qx::model_view::create_nested_model(NULL, QModelIndex(), authorX);         Q_UNUSED(pNestedModel2);
}

void test_qt_widget()
{
   qx::IxModel * pModel = new qx::QxModel<author>();
   pModel->qxFetchAll();

   QTableView tableView;
   tableView.setModel(pModel);
   tableView.show();
   qApp->exec();
}

void test_qml_view()
{
   qx::IxModel * pModel = new qx::QxModel<author>();
   pModel->qxFetchAll();

#if (QT_VERSION >= 0x050000)
   QQuickView qmlView;
   QString sQmlFile = "qrc:/documents/main.qml";
#else // (QT_VERSION >= 0x050000)
   QDeclarativeView qmlView;
   QString sQmlFile = "qrc:/documents/main_qt4.qml";
#endif // (QT_VERSION >= 0x050000)

   qmlView.rootContext()->setContextProperty("myModel", pModel);
   qmlView.setSource(QUrl(sQmlFile));
   qmlView.show();
   qApp->exec();
}

void test_qml_view_with_relationship()
{
#if (QT_VERSION >= 0x050000)
   qx::IxModel * pModel = new model_view::blog_model();
   pModel->qxFetchAll(QStringList() << "*");

   QQuickView qmlView;
   QString sQmlFile = "qrc:/documents/main_relationship.qml";

   qmlView.rootContext()->setContextProperty("myModel", pModel);
   qmlView.setSource(QUrl(sQmlFile));
   qmlView.show();
   qApp->exec();
#endif // (QT_VERSION >= 0x050000)
}
