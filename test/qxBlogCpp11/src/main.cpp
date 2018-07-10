#include "../include/precompiled.h"

#include <QtCore/qcoreapplication.h>

#include "../include/blog.h"
#include "../include/author.h"
#include "../include/comment.h"
#include "../include/category.h"

#include <QxOrm_Impl.h>

int main(int argc, char * argv[])
{
   // Qt application
   QCoreApplication app(argc, argv);
   QFile::remove("./qxBlogCpp11.sqlite");

   // Parameters to connect to database
   qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
   qx::QxSqlDatabase::getSingleton()->setDatabaseName("./qxBlogCpp11.sqlite");
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

   author_1->setId_0("_111_"); author_1->setId_1(100); author_1->setId_2("1_1");
   author_1->m_name = "author_1"; author_1->m_sex = author::male; author_1->m_birthdate = QDate::currentDate();
   author_2->setId_0("_222_"); author_2->setId_1(200); author_2->setId_2("2_2");
   author_2->m_name = "author_2"; author_2->m_sex = author::female; author_2->m_birthdate = QDate::currentDate();
   author_3->setId_0("_333_"); author_3->setId_1(300); author_3->setId_2("3_3");
   author_3->m_name = "author_3"; author_3->m_sex = author::female; author_3->m_birthdate = QDate::currentDate();

   list_author authorX;
   authorX.insert(author_1->getId(), author_1);
   authorX.insert(author_2->getId(), author_2);
   authorX.insert(author_3->getId(), author_3);

   // Insert list of 3 author into database
   daoError = qx::dao::insert(authorX);
   qAssert(qx::dao::count<author>() == 3);

   // Clone author n°2 : 'author_id_2'
   author_ptr author_clone = qx::clone_to_std_shared_ptr(* author_2);
   qAssert(author_clone->getId() == author::type_composite_key("_222_", 200, "2_2"));
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

   category_1->setId_0("101"); category_1->setId_1(10);
   category_1->setId_2("__11_XX"); category_1->setId_3(10010);
   category_1->m_name = "category_1"; category_1->m_desc = "desc_1";
   category_2->setId_0("202"); category_2->setId_1(20);
   category_2->setId_2("__22_XX"); category_2->setId_3(20020);
   category_2->m_name = "category_2"; category_2->m_desc = "desc_2";
   category_3->setId_0("303"); category_3->setId_1(30);
   category_3->setId_2("__33_XX"); category_3->setId_3(30030);
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
   qAssert(category_1->getId() == category::type_composite_key("101", 10, "__11_XX", 10010));
   qAssert(category_2->getId() == category::type_composite_key("202", 20, "__22_XX", 20020));
   qAssert(category_3->getId() == category::type_composite_key("303", 30, "__33_XX", 30030));

   // Terminate transaction => commit or rollback if there is error
   if (bCommit) { db.commit(); }
   else { db.rollback(); }

   } // End of scope : 'db' is destroyed

   // Create a blog with the class name (factory)
   boost::any blog_any = qx::create("blog");
   blog_ptr blog_1;
   try { blog_1 = boost::any_cast<blog_ptr>(blog_any); }
   catch (...) { blog_1.reset(new blog()); }
   blog_1->setId_0(1);
   blog_1->setId_1("blog n°1");
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

   comment_1->setId_0(1);
   comment_1->setId_1("comment n°1");
   comment_1->m_text = "comment_1 text";
   comment_1->m_dt_create = QDateTime::currentDateTime();
   comment_1->m_blog = blog_1;
   comment_2->setId_0(2);
   comment_2->setId_1("comment n°2");
   comment_2->m_text = "comment_2 text";
   comment_2->m_dt_create = QDateTime::currentDateTime();
   comment_2->m_blog = blog_1;

   daoError = qx::dao::insert(comment_1);
   daoError = qx::dao::insert(comment_2);
   qAssert(! daoError.isValid() && (qx::dao::count<comment>() == 2));

   // Add 2 categories to 'blog_1' => must insert into extra-table 'category_blog'
   blog_1->m_categoryX.insert(category_1->getId(), category_1);
   blog_1->m_categoryX.insert(category_3->getId(), category_3);
   daoError = qx::dao::save_with_relation("list_category", blog_1);

   // Fetch blog into a new variable with all relation : 'author', 'comment' and 'category'
   blog_ptr blog_tmp; blog_tmp.reset(new blog());
   blog_tmp->setId_0(blog_1->getId_0());
   blog_tmp->setId_1(blog_1->getId_1());
   daoError = qx::dao::fetch_by_id_with_all_relation(blog_tmp);

   qAssert(! daoError.isValid());
   qAssert(blog_tmp->m_commentX.count() == 2);
   qAssert(blog_tmp->m_categoryX.count() == 2);
   qAssert(blog_tmp->m_text == "update blog_text_1");
   qAssert(blog_tmp->m_author && blog_tmp->m_author->getId() == author::type_composite_key("_222_", 200, "2_2"));

   // Dump 'blog_tmp' result from database (xml serialization)
   qx::dump(blog_tmp);

   // Call 'age()' method with class name and method name (reflexion)
   qx_bool bInvokeOk = qx::QxClassX::invoke("author", "age", author_1);
   qAssert(bInvokeOk);

   // Test 'isDirty()' method
   qx::dao::ptr<blog> blog_isdirty = qx::dao::ptr<blog>(new blog());
   blog_isdirty->setId_0(blog_1->getId_0());
   blog_isdirty->setId_1(blog_1->getId_1());
   daoError = qx::dao::fetch_by_id(blog_isdirty);
   qAssert(! daoError.isValid() && ! blog_isdirty.isDirty());

   blog_isdirty->m_text = "blog property 'text' modified => blog is dirty !!!";
   QStringList lstDiff; bool bDirty = blog_isdirty.isDirty(lstDiff);
   qAssert(bDirty && (lstDiff.count() == 1) && (lstDiff.at(0) == "blog_text"));
   if (bDirty) { qDebug("[QxOrm] test dirty 1 : blog is dirty => '%s'", qPrintable(lstDiff.join("|"))); }

   daoError = qx::dao::update(blog_isdirty);
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

   daoError = qx::dao::save(container_isdirty);
   qAssert(! daoError.isValid() && ! container_isdirty.isDirty());
   qx::dump(container_isdirty);

   return 0;
}
