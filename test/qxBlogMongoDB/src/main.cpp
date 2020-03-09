#include "../include/precompiled.h"

#include <QtCore/qcoreapplication.h>

#include "../include/blog.h"
#include "../include/author.h"
#include "../include/comment.h"
#include "../include/category.h"
#include "../include/TestQtProperty.h"

#include <QxOrm_Impl.h>

void basicCRUDOnAuthor(bool withDelete);
void basicCRUDOnCategory();
void basicCRUDOnBlog();
void complexQueriesOnBlog();
void miscellaneousOperations();
void testQtProperty();

int main(int argc, char * argv[])
{
   // Qt application
   QCoreApplication app(argc, argv);

   // Following command is recommanded to initialize QxOrm introspection engine
   qx::QxClassX::registerAllClasses(true);

   // Parameters to connect to MongoDB database
   qx::QxSqlDatabase * pDatabase = qx::QxSqlDatabase::getSingleton();
   pDatabase->setDriverName("QXMONGODB");
   pDatabase->setDatabaseName("qxBlog");
   pDatabase->setHostName("localhost");
   pDatabase->setPort(27017);
   pDatabase->setUserName("");
   pDatabase->setPassword("");

   // For debug purpose : log all replies from MongoDB database
   qx::dao::mongodb::QxMongoDB_Helper::setLogDatabaseReply(true);

   // Clear previous sample database
   qx_query dropDB("{ \"dropDatabase\" : 1 }");
   QSqlError daoError = qx::dao::call_query(dropDB); qAssert(! daoError.isValid());

   // To optimize queries : create automatically indexes based on relationships and properties marked as 'index'
   daoError = qx::dao::mongodb::QxMongoDB_Helper::autoCreateIndexes(true); qAssert(! daoError.isValid());

   // Basic CRUD operations
   basicCRUDOnAuthor(true);
   basicCRUDOnAuthor(false);

   // Populate category collection
   basicCRUDOnCategory();

   // Populate blog collection
   basicCRUDOnBlog();

   // Process some complex queries on blog collection (with relationships)
   complexQueriesOnBlog();

   // Process some others operations on database
   miscellaneousOperations();

   // Test Qt properties registered via QX_REGISTER_ALL_QT_PROPERTIES() macro (https://www.qxorm.com/qxorm_en/manual.html#manual_520)
   testQtProperty();

   return 0;
}

void basicCRUDOnAuthor(bool withDelete)
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
   QString author_3_id = authorX.at(0).m_id; qAssert(! author_3_id.isEmpty());
   QString author_5_id = authorX.at(2).m_id; qAssert(! author_5_id.isEmpty());

   // Test update one author
   author_3 = authorX.at(0);
   author_3.m_name = "author_3_modified";
   daoError = qx::dao::update(author_3); qAssert(! daoError.isValid());

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
   author_5 = authorX.at(4);
   author_5.m_name = "author_5_modified_after_fetch";
   daoError = qx::dao::update(author_5); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<author>() == 5);

   // Test update many author after fetch
   author_ptr pAuthor = list_of_female_author.getByIndex(0);
   pAuthor->m_name = pAuthor->m_name + "_female_modified_after_fetch";
   pAuthor = list_of_female_author.getByIndex(1);
   pAuthor->m_name = pAuthor->m_name + "_female_modified_after_fetch";
   pAuthor = list_of_female_author.getByIndex(2);
   pAuthor->m_name = pAuthor->m_name + "_female_modified_after_fetch";
   daoError = qx::dao::update(list_of_female_author); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<author>() == 5);

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

void basicCRUDOnCategory()
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

void basicCRUDOnBlog()
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

   category_ptr category_1 = categories.getByIndex(0);
   category_ptr category_3 = categories.getByIndex(2);
   blog_1->m_categoryX.insert(category_1->m_id, category_1);
   blog_1->m_categoryX.insert(category_3->m_id, category_3);
   daoError = qx::dao::save(blog_1); qAssert(! daoError.isValid());
   qAssert(qx::dao::count<blog>() == 1);

   // Push a second blog
   blog_ptr blog_2 = std::make_shared<blog>();
   blog_2->m_text = "blog_text_2";
   daoError = qx::dao::save(blog_2); qAssert(! daoError.isValid());
}

void complexQueriesOnBlog()
{
   // Fetch all blogs (without relation)
   list_blog allBlogs;
   QSqlError daoError = qx::dao::fetch_all(allBlogs); qAssert(! daoError.isValid());
   qx::dump(allBlogs);
   qAssert(allBlogs.size() == 2);

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

void miscellaneousOperations()
{
   // Dump all registered classes into QxOrm context (introspection engine)
   qx::QxClassX::dumpAllClasses();

   // Call 'age()' method with class name and method name (reflexion)
   author author_1; qx_bool bInvokeOk = qx::QxClassX::invoke("author", "age", author_1); qAssert(bInvokeOk);

   // Fetch all blogs (without relation)
   list_blog allBlogs; QSqlError daoError = qx::dao::fetch_all(allBlogs); qAssert(! daoError.isValid());
   qx::dump(allBlogs); qAssert(allBlogs.size() == 2);

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

void testQtProperty()
{
   TestQtProperty tst;
   tst.setDesc("tst");
   QSqlError daoError = qx::dao::insert(tst); qAssert(! daoError.isValid());
   tst.setDesc("tst update");
   daoError = qx::dao::update(tst); qAssert(! daoError.isValid());
   daoError = qx::dao::fetch_by_id(tst); qAssert(! daoError.isValid());
   std::shared_ptr<qx::IxPersistableCollection> lst = qx::IxPersistable::qxFetchAll("TestQtProperty"); qAssert(lst->__count() == 1);
}
