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
   QFile::remove("./qxBlogPImpl.sqlite");

   // Parameters to connect to database
   qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
   qx::QxSqlDatabase::getSingleton()->setDatabaseName("./qxBlogPImpl.sqlite");
   qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
   qx::QxSqlDatabase::getSingleton()->setUserName("root");
   qx::QxSqlDatabase::getSingleton()->setPassword("");
   qx::QxSqlDatabase::getSingleton()->setFormatSqlQueryBeforeLogging(true);
   qx::QxSqlDatabase::getSingleton()->setDisplayTimerDetails(true);

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

   author_1->setId("author_id_1"); author_1->setName("author_1");
   author_1->setSex(author::male); author_1->setBirthdate(QDate::currentDate());
   author_2->setId("author_id_2"); author_2->setName("author_2");
   author_2->setSex(author::female); author_2->setBirthdate(QDate::currentDate());
   author_3->setId("author_id_3"); author_3->setName("author_3");
   author_3->setSex(author::female); author_3->setBirthdate(QDate::currentDate());

   list_author authorX;
   authorX.insert(author_1->id(), author_1);
   authorX.insert(author_2->id(), author_2);
   authorX.insert(author_3->id(), author_3);

   // Insert list of 3 author into database
   daoError = qx::dao::insert(authorX);
   qAssert(qx::dao::count<author>() == 3);

   // Clone author 2 : 'author_id_2'
   author_ptr author_clone = qx::clone(* author_2);
   qAssert(author_clone->id() == "author_id_2");
   qAssert(author_clone->sex() == author::female);

   // Create a query to fetch only female author : 'author_id_2' and 'author_id_3'
   qx::QxSqlQuery query("WHERE author.sex = :sex");
   query.bind(":sex", author::female);

   list_author list_of_female_author;
   daoError = qx::dao::fetch_by_query(query, list_of_female_author);
   qAssert(list_of_female_author.count() == 2);

   // Dump list of female author (xml serialization)
   qx::dump(list_of_female_author, false);
   qx::dump(list_of_female_author, true);

   // Test qx::QxSqlQuery::freeText() with/without placeholders
   query = qx_query(); query.freeText("WHERE author.sex = " + QString::number(static_cast<int>(author::female)));
   daoError = qx::dao::fetch_by_query(query, list_of_female_author);
   qAssert(list_of_female_author.count() == 2);
   query = qx_query(); query.freeText("WHERE author.sex = :sex", QVariantList() << author::female);
   daoError = qx::dao::fetch_by_query(query, list_of_female_author);
   qAssert(list_of_female_author.count() == 2);
   query = qx_query(); query.freeText("WHERE author.sex=:sex AND author.author_id=:author_id", QVariantList() << author::female << "author_id_2");
   daoError = qx::dao::fetch_by_query(query, list_of_female_author);
   qAssert(list_of_female_author.count() == 1);
   query = qx_query(); query.freeText("WHERE (author.sex = :sex) AND (author.author_id = :author_id)", QVariantList() << author::female << "author_id_2");
   daoError = qx::dao::fetch_by_query(query, list_of_female_author);
   qAssert(list_of_female_author.count() == 1);

   // Create 3 categories
   category_ptr category_1 = category_ptr(new category());
   category_ptr category_2 = category_ptr(new category());
   category_ptr category_3 = category_ptr(new category());

   category_1->setName("category_1"); category_1->setDesc("desc_1");
   category_2->setName("category_2"); category_2->setDesc("desc_2");
   category_3->setName("category_3"); category_3->setDesc("desc_3");

   { // Create a scope to destroy temporary connexion to database

   // Open a transaction to database
   QSqlDatabase db = qx::QxSqlDatabase::getDatabase();
   bool bCommit = db.transaction();

   // Insert 3 categories into database, use 'db' parameter for the transaction
   daoError = qx::dao::insert(category_1, (& db));    bCommit = (bCommit && ! daoError.isValid());
   daoError = qx::dao::insert(category_2, (& db));    bCommit = (bCommit && ! daoError.isValid());
   daoError = qx::dao::insert(category_3, (& db));    bCommit = (bCommit && ! daoError.isValid());

   qAssert(bCommit);
   qAssert(category_1->id() != 0);
   qAssert(category_2->id() != 0);
   qAssert(category_3->id() != 0);

   // Terminate transaction => commit or rollback if there is error
   if (bCommit) { db.commit(); }
   else { db.rollback(); }

   } // End of scope : 'db' is destroyed

   // Create a blog with the class name (factory)
   qx::any blog_any = qx::create("blog");
   blog_ptr blog_1;
   try { blog_1 = qx::any_cast<blog_ptr>(blog_any); }
   catch (...) { blog_1.reset(new blog()); }
   blog_1->setText("blog_text_1");
   blog_1->setDateCreation(QDateTime::currentDateTime());
   blog_1->getAuthor() = author_1;

   // Insert 'blog_1' into database with 'save()' method
   daoError = qx::dao::save(blog_1);

   // Modify 'blog_1' properties and save into database
   blog_1->setText("update blog_text_1");
   blog_1->getAuthor() = author_2;
   daoError = qx::dao::save(blog_1);

   // Add 2 comments to 'blog_1'
   comment_ptr comment_1; comment_1.reset(new comment());
   comment_ptr comment_2; comment_2.reset(new comment());

   comment_1->setText("comment_1 text");
   comment_1->setDateCreation(QDateTime::currentDateTime());
   comment_1->getBlog() = blog_1;
   comment_2->setText("comment_2 text");
   comment_2->setDateCreation(QDateTime::currentDateTime());
   comment_2->getBlog() = blog_1;

   daoError = qx::dao::insert(comment_1);
   daoError = qx::dao::insert(comment_2);
   qAssert(qx::dao::count<comment>() == 2);

   // Add 2 categories to 'blog_1' => must insert into extra-table 'category_blog'
   blog_1->listOfCategories().insert(category_1->id(), category_1);
   blog_1->listOfCategories().insert(category_3->id(), category_3);
   daoError = qx::dao::save_with_relation("list_category", blog_1);

   // Fetch blog into a new variable with all relation : 'author', 'comment' and 'category'
   blog_ptr blog_tmp; blog_tmp.reset(new blog());
   blog_tmp->setId(blog_1->id());
   daoError = qx::dao::fetch_by_id_with_all_relation(blog_tmp);

   qAssert(blog_tmp->listOfComments().count() == 2);
   qAssert(blog_tmp->listOfCategories().count() == 2);
   qAssert(blog_tmp->text() == "update blog_text_1");
   qAssert(blog_tmp->getAuthor() && blog_tmp->getAuthor()->id() == "author_id_2");

   // Fetch blog into a new variable with many relations using "*->*->*->*" (4 levels of relationships)
   blog_tmp.reset(new blog());
   blog_tmp->setId(blog_1->id());
   daoError = qx::dao::fetch_by_id_with_relation("*->*->*->*", blog_tmp);

   qAssert(blog_tmp->listOfComments().count() == 2);
   qAssert(blog_tmp->listOfCategories().count() == 2);
   qAssert(blog_tmp->text() == "update blog_text_1");
   qAssert(blog_tmp->getAuthor() && blog_tmp->getAuthor()->id() == "author_id_2");

   // Dump 'blog_tmp' result from database (xml serialization)
   qx::dump(blog_tmp, false);
   qx::dump(blog_tmp, true);

   // Fetch relations defining columns to fetch with syntax { col_1, col_2, etc... }
   list_blog lstBlogComplexRelation;
   daoError = qx::dao::fetch_all_with_relation(QStringList() << "{ blog_text }" << "author_id { name, birthdate }" << "list_comment { comment_text } -> blog_id -> *", lstBlogComplexRelation);
   qx::dump(lstBlogComplexRelation);
   qAssert(lstBlogComplexRelation.size() > 0);
   qAssert(lstBlogComplexRelation[0]->text() != ""); // Fetched
   qAssert(lstBlogComplexRelation[0]->dateCreation().isNull()); // Not fetched
   qAssert(lstBlogComplexRelation[0]->getAuthor()->sex() == author::unknown); // Not fetched
   qAssert(lstBlogComplexRelation[0]->getAuthor()->name() != ""); // Fetched
   qAssert(lstBlogComplexRelation[0]->listOfComments().size() > 0);
   qAssert(lstBlogComplexRelation[0]->listOfComments()[0]->dateCreation().isNull()); // Not fetched
   qAssert(lstBlogComplexRelation[0]->listOfComments()[0]->text() != ""); // Fetched
   qAssert(lstBlogComplexRelation[0]->listOfComments()[0]->getBlog());

   // Fetch relations defining columns to remove before fetching with syntax -{ col_1, col_2, etc... }
   list_blog lstBlogComplexRelation2;
   daoError = qx::dao::fetch_all_with_relation(QStringList() << "-{ blog_text }" << "author_id -{ name, birthdate }" << "list_comment -{ comment_text } -> blog_id -> *", lstBlogComplexRelation2);
   qx::dump(lstBlogComplexRelation2);
   qAssert(lstBlogComplexRelation2.size() > 0);
   qAssert(lstBlogComplexRelation2[0]->text() == ""); // Not fetched
   qAssert(! lstBlogComplexRelation2[0]->dateCreation().isNull()); // Fetched
   qAssert(lstBlogComplexRelation2[0]->getAuthor()->sex() != author::unknown); // Fetched
   qAssert(lstBlogComplexRelation2[0]->getAuthor()->name() == ""); // Not fetched
   qAssert(lstBlogComplexRelation2[0]->listOfComments().size() > 0);
   qAssert(! lstBlogComplexRelation2[0]->listOfComments()[0]->dateCreation().isNull()); // Fetched
   qAssert(lstBlogComplexRelation2[0]->listOfComments()[0]->text() == ""); // Not fetched
   qAssert(lstBlogComplexRelation2[0]->listOfComments()[0]->getBlog());

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
   qAssert(blogFromJsonFull->listOfComments().count() == 2);
   qAssert(blogFromJsonFull->listOfCategories().count() == 2);
   qAssert(blogFromJsonFull->text() == "update blog_text_1");
   qAssert(blogFromJsonFull->getAuthor() && blogFromJsonFull->getAuthor()->id() == "author_id_2");

   qx::dump(blogFromJsonFiltered);
   qAssert(blogFromJsonFiltered->text() != ""); // Fetched
   qAssert(blogFromJsonFiltered->dateCreation().isNull()); // Not fetched
   qAssert(blogFromJsonFiltered->getAuthor()->sex() == author::unknown); // Not fetched
   qAssert(blogFromJsonFiltered->getAuthor()->name() != ""); // Fetched
   qAssert(blogFromJsonFiltered->listOfComments().size() > 0);
   qAssert(blogFromJsonFiltered->listOfComments()[0]->dateCreation().isNull()); // Not fetched
   qAssert(blogFromJsonFiltered->listOfComments()[0]->text() != ""); // Fetched
   qAssert(blogFromJsonFiltered->listOfComments()[0]->getBlog());
#endif // _QX_NO_JSON

   // Fetch relations defining columns to fetch with syntax { col_1, col_2, etc... } + custom table alias using syntax <my_table_alias> + custom table alias suffix using syntax <..._my_alias_suffix>
   list_blog lstBlogComplexRelation3;
   daoError = qx::dao::fetch_all_with_relation(QStringList() << "<blog_alias> { blog_text }" << "author_id <author_alias> { name, birthdate }" << "list_comment <list_comment_alias> { comment_text } -> blog_id <blog_alias_2> -> * <..._my_alias_suffix>", lstBlogComplexRelation3);
   qx::dump(lstBlogComplexRelation3);
   qAssert(lstBlogComplexRelation3.size() > 0);
   qAssert(lstBlogComplexRelation3[0]->text() != ""); // Fetched
   qAssert(lstBlogComplexRelation3[0]->dateCreation().isNull()); // Not fetched
   qAssert(lstBlogComplexRelation3[0]->getAuthor()->sex() == author::unknown); // Not fetched
   qAssert(lstBlogComplexRelation3[0]->getAuthor()->name() != ""); // Fetched
   qAssert(lstBlogComplexRelation3[0]->listOfComments().size() > 0);
   qAssert(lstBlogComplexRelation3[0]->listOfComments()[0]->dateCreation().isNull()); // Not fetched
   qAssert(lstBlogComplexRelation3[0]->listOfComments()[0]->text() != ""); // Fetched
   qAssert(lstBlogComplexRelation3[0]->listOfComments()[0]->getBlog());

   // Test to add join SQL sub-queries (inside LEFT OUTER JOIN or INNER JOIN)
   list_blog lstBlogWithJoinQueries;
   query = qx_query().where("blog_alias.blog_text").isEqualTo("update blog_text_1");
   query.addJoinQuery("list_comment_alias", "AND list_comment_alias.comment_text IS NOT NULL");
   query.addJoinQuery("author_alias", qx_query().freeText("AND author_alias.sex = :sex", QVariantList() << author::female));
   daoError = qx::dao::fetch_by_query_with_relation(QStringList() << "<blog_alias> { blog_text }" << "author_id <author_alias> { name, birthdate, sex }" << "list_comment <list_comment_alias> { comment_text }", query, lstBlogWithJoinQueries);
   qx::dump(lstBlogWithJoinQueries);
   qAssert(lstBlogWithJoinQueries.size() > 0);
   qAssert(lstBlogWithJoinQueries[0]->text() == "update blog_text_1");
   qAssert(lstBlogWithJoinQueries[0]->getAuthor()->sex() == author::female);

   // When join SQL sub-queries are used, then relationships should keep user defined order (in this example : 'list_comment' before 'author')
   lstBlogWithJoinQueries.clear();
   query = qx_query().where("blog_alias.blog_text").isEqualTo("update blog_text_1");
   query.addJoinQuery("list_comment_alias", "AND list_comment_alias.comment_text IS NOT NULL");
   query.addJoinQuery("author_alias", qx_query("AND author_alias.sex = :sex", QVariantList() << author::female));
   daoError = qx::dao::fetch_by_query_with_relation(QStringList() << "<blog_alias> { blog_text }" << "list_comment <list_comment_alias> { comment_text }" << "author_id <author_alias> { name, birthdate, sex }", query, lstBlogWithJoinQueries);
   qx::dump(lstBlogWithJoinQueries);
   qAssert(lstBlogWithJoinQueries.size() > 0);
   qAssert(lstBlogWithJoinQueries[0]->text() == "update blog_text_1");
   qAssert(lstBlogWithJoinQueries[0]->getAuthor()->sex() == author::female);

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
   blog_isdirty->setId(blog_1->id());
   daoError = qx::dao::fetch_by_id(blog_isdirty);
   qAssert(! daoError.isValid() && ! blog_isdirty.isDirty());

   blog_isdirty->setText("blog property 'text' modified => blog is dirty !!!");
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
   author_ptr_dirty->setName("author name modified at index 1 => container is dirty !!!");
   bDirty = container_isdirty.isDirty(lstDiff);
   qAssert(bDirty && (lstDiff.count() == 1));
   if (bDirty) { qDebug("[QxOrm] test dirty 2 : container is dirty => '%s'", qPrintable(lstDiff.join("|"))); }

   author_ptr_dirty = container_isdirty->at(2);
   author_ptr_dirty->setBirthdate(QDate(1998, 03, 06));
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
   { qAssert(lst_blog_with_only_date_creation[0]->text().isEmpty()); }
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
   qAssert(! daoError.isValid()); qAssert(category_tmp->id() != 0);
   qx::dump(category_tmp, false);
   qx::dump(category_tmp, true);

   // Test SQL DISTINCT keyword
   QList<blog> listOfBlogDistinct;
   qx_query queryDistinct; queryDistinct.distinct().limit(10);
   daoError = qx::dao::fetch_by_query(queryDistinct, listOfBlogDistinct, NULL, QStringList() << "blog_text");
   qAssert(! daoError.isValid()); qAssert((listOfBlogDistinct.count() > 0) && (listOfBlogDistinct.at(0).id() == 0) && (! listOfBlogDistinct.at(0).text().isEmpty()));
   qx::dump(listOfBlogDistinct);

   return 0;
}
