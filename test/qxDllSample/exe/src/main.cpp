#include <QtCore/qglobal.h>

#if (QT_VERSION >= 0x050000)
#include <QtWidgets/qapplication.h>
#else // (QT_VERSION >= 0x050000)
#include <QtGui/qapplication.h>
#endif // (QT_VERSION >= 0x050000)

#include "../include/precompiled.h"

#include "../../dll1/include/CPerson.h"
#include "../../dll1/include/TestQtProperty.h"

#include "../../dll2/include/CUser.h"
#include "../../dll2/include/CTestAll.h"
#include "../../dll2/include/Bar.h"
#include "../../dll2/include/Foo.h"

#include <QxMemLeak.h>

void test_fct() { qDebug("[QxOrm] %s", "'test_fct()' called by 'qx::IxFunction()'"); }
struct test_class_fct { int class_fct() { qDebug("[QxOrm] %s", "'test_class_fct::class_fct()' called by 'qx::IxFunction()'"); return 123; }; };

int main(int argc, char * argv[])
{
   QApplication app(argc, argv);

   //--------------------------------

   boost::shared_ptr<QObject> ptrTmp;
   ptrTmp.reset(new CUser());
   qx::clone(ptrTmp);

#if _QX_SERIALIZE_POLYMORPHIC
   qx::serialization::polymorphic_xml::to_file(ptrTmp, "pointer_from_main.xml");
   qx::serialization::polymorphic_xml::from_file(ptrTmp, "pointer_from_main.xml");
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_XML
   qx::serialization::xml::to_file(ptrTmp, "pointer_from_main.xml");
   qx::serialization::xml::from_file(ptrTmp, "pointer_from_main.xml");
#endif // _QX_SERIALIZE_XML

   //--------------------------------

   qx::test::CPerson person;
   boost::shared_ptr<qx::test::CPerson> personClone = qx::clone(person);
   boost::any a = qx::create("qx::test::CPerson");

#if _QX_SERIALIZE_POLYMORPHIC
   qx::serialization::polymorphic_binary::to_file(person, "person.bin");
   qx::serialization::polymorphic_binary::from_file(person, "person.bin");
   qx::serialization::polymorphic_xml::to_file(person, "person.xml");
   qx::serialization::polymorphic_xml::from_file(person, "person.xml");
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   qx::serialization::binary::to_file(person, "person.bin");
   qx::serialization::binary::from_file(person, "person.bin");
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   qx::serialization::text::to_file(person, "person.txt");
   qx::serialization::text::from_file(person, "person.txt");
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   qx::serialization::xml::to_file(person, "person.xml");
   qx::serialization::xml::from_file(person, "person.xml");
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   qx::serialization::portable_binary::to_file(person, "person.bin2", 0);
   qx::serialization::portable_binary::from_file(person, "person.bin2", 0);
#endif // _QX_SERIALIZE_PORTABLE_BINARY

   qx::serialization::to_string(person);
   qx::serialization::to_file_compressed(person, "person.zip");
   qx::serialization::from_file_compressed(person, "person.zip");

   //--------------------------------

   CUser user;
   boost::shared_ptr<CUser> userClone = qx::clone(user);
   qx::create("CUserXXX");

   qx::cache::max_cost(2);
   qx::cache::set("user", userClone);
   qx::cache::set("object", ptrTmp);
   qx::cache::set("person", personClone);
   qAssert(qx::cache::count() == 2);
   ptrTmp = qx::cache::get< boost::shared_ptr<QObject> >("object");
   qx_bool bCacheOk = qx::cache::get("user", userClone);
   qAssert(! bCacheOk && (ptrTmp.get() != NULL));

   boost::shared_ptr<qx::test::CPerson> personValidate = qx::clone(person);
   if (! personValidate) { personValidate.reset(new qx::test::CPerson()); }
   personValidate->setLastName("admin");
   personValidate->setDouble(305.86);
   qx::QxInvalidValueX invalidValues = qx::validate(personValidate);
   QString sInvalidValues = invalidValues.text();
   qDebug("[QxOrm] test 'QxValidator' module :\n%s", qPrintable(sInvalidValues));

#if _QX_SERIALIZE_POLYMORPHIC
   qx::serialization::polymorphic_binary::to_file(user, "user.bin");
   qx::serialization::polymorphic_binary::from_file(user, "user.bin");
   qx::serialization::polymorphic_xml::to_file(user, "user.xml");
   qx::serialization::polymorphic_xml::from_file(user, "user.xml");
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   qx::serialization::binary::to_file(user, "user.bin");
   qx::serialization::binary::from_file(user, "user.bin");
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   qx::serialization::text::to_file(user, "user.txt");
   qx::serialization::text::from_file(user, "user.txt");
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   qx::serialization::xml::to_file(user, "user.xml");
   qx::serialization::xml::from_file(user, "user.xml");
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   qx::serialization::portable_binary::to_file(user, "user.bin2", 0);
   qx::serialization::portable_binary::from_file(user, "user.bin2", 0);
#endif // _QX_SERIALIZE_PORTABLE_BINARY

   qx::serialization::to_string(user);
   qx::serialization::to_file_compressed(user, "user.zip");
   qx::serialization::from_file_compressed(user, "user.zip");

   //--------------------------------

   boost::any resultInvoke;
   CUser * pUser = new CUser(); // You find a memory leak !!!
   pUser->test();
   qx_bool bInvokeOk = qx::QxClass<CUser>::invoke("fct_getPersonId", pUser);                          qAssert(bInvokeOk);
   bInvokeOk = qx::QxClassX::invoke("CUser", "fct_getPersonId", pUser);                               qAssert(bInvokeOk);
   bInvokeOk = qx::QxClassX::invokeStatic("CUser", "fct_testStaticFct", "182", (& resultInvoke));     qAssert(bInvokeOk.getValue() && (boost::any_cast<int>(resultInvoke) == 182));

   //--------------------------------

   typedef QSharedPointer<CUser> CUser_ptr;
   qx::QxCollection<long, CUser_ptr> coll;
   CUser_ptr p1(new CUser());
   CUser_ptr p2(new CUser());
   coll.insert(0, p1);
   coll.insert(1, p2);

   {
      // Test qx::IxCollection interface using a smart-pointer (test also qx::any_cast_dynamic<T>::get(...) function)
      QSharedPointer<QObject> pTestIxCollection = coll._get< QSharedPointer<QObject> >(1);
      Q_UNUSED(pTestIxCollection);
   }

#if _QX_SERIALIZE_POLYMORPHIC
   qx::serialization::polymorphic_xml::to_file(coll, "collection.xml");
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_XML
   qx::serialization::xml::to_file(coll, "collection.xml");
#endif // _QX_SERIALIZE_XML

   //--------------------------------

   boost::any any_ret;
   qx::IxFunction_ptr pFct1 = qx::function::bind_fct_0<void, void>(& test_fct);
   qx_bool bInvoke = pFct1->invoke();

   qx::IxFunction_ptr pFct2 = qx::function::bind_member_fct_0<test_class_fct, int>(& test_class_fct::class_fct);
   test_class_fct o_test_class_fct;
   bInvoke = pFct2->invoke(& o_test_class_fct, "", (& any_ret));
   int iReturnByInvoke = boost::any_cast<int>(any_ret);
   Q_UNUSED(iReturnByInvoke);

   //--------------------------------

   CTestAll::test();

   //--------------------------------

   QString sTestCvt = qx::cvt::to_string(18, "%03d");
   sTestCvt = qx::cvt::to_string(int(4));
   sTestCvt = qx::cvt::to_string(QDateTime::currentDateTime());
   sTestCvt = qx::cvt::to_string(pUser);
   sTestCvt = qx::cvt::to_string(p1, "%08d");
   QObject dummy_01; sTestCvt = qx::cvt::to_string(dummy_01);
   CTestAll dummy_02; sTestCvt = qx::cvt::to_string(dummy_02);

   qx_bool bCvtOk = qx::cvt::from_string("34", pUser);
   sTestCvt = qx::cvt::to_string(pUser);

   QVariant sTestCvtVar = qx::cvt::to_variant(QTime::currentTime());
   QVariant dummy_03; bCvtOk = qx::cvt::from_variant(dummy_03, p1);

   QVector< boost::shared_ptr<CUser> > lstCvtTest;
   boost::shared_ptr<CUser> pp1; pp1.reset(new CUser()); lstCvtTest.push_back(pp1);
   boost::shared_ptr<CUser> pp2; lstCvtTest.push_back(pp2);
   boost::shared_ptr<CUser> pp3; pp3.reset(new CUser()); lstCvtTest.push_back(pp3);
   sTestCvt = qx::cvt::to_string(lstCvtTest);
   lstCvtTest.remove(1);
   bCvtOk = qx::cvt::from_string(sTestCvt, lstCvtTest);
   qAssert(lstCvtTest.size() == 3);

   //--------------------------------

   QFile::remove("./database.db");

   qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
   qx::QxSqlDatabase::getSingleton()->setDatabaseName("database.db");
   qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
   qx::QxSqlDatabase::getSingleton()->setUserName("root");
   qx::QxSqlDatabase::getSingleton()->setPassword("");
   qx::QxSqlDatabase::getSingleton()->setSqlPlaceHolderStyle(qx::QxSqlDatabase::ph_style_2_point_name);
   qx::QxSqlDatabase::getSingleton()->setTraceSqlQuery(true);
   qx::QxSqlDatabase::getSingleton()->setTraceSqlRecord(false);

   // Only for debug purpose : assert if invalid offset detected fetching a relation
   qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);

   qx::test::CPerson * pBrother = new qx::test::CPerson();
   pBrother->setFirstName("brother firstname");
   pBrother->setLastName("brother lastname");
   pUser->setBrother(pBrother);
   pUser->setLastName("user lastname");

   QSqlError daoError = qx::dao::create_table<CUser>();
   daoError = qx::dao::create_table<qx::test::CPerson>();
   daoError = qx::dao::insert(pBrother);
   long lBrotherId = pBrother->getPersonId();
   daoError = qx::dao::insert(pUser);
   long lDaoCount = qx::dao::count<CUser>();                            qAssert(lDaoCount == 1);
   pUser->setBrother(NULL);
   daoError = qx::dao::fetch_by_id(pUser);                              qAssert(pUser->getBrother() && (pUser->getBrother()->getPersonId() == lBrotherId));
   pUser->setBrother(NULL);
   daoError = qx::dao::fetch_by_id_with_relation("brother", pUser);     qAssert(pUser->getBrother() && (pUser->getBrother()->getFirstName() == "brother firstname"));
   qx_bool bDaoExist = qx::dao::exist(pUser);                           qAssert(bDaoExist);
   daoError = qx::dao::update(pUser);
   daoError = qx::dao::delete_by_id(pUser);
   lDaoCount = qx::dao::count<CUser>();                                 qAssert(lDaoCount == 0);
   daoError = qx::dao::save(pUser);
   daoError = qx::dao::save(pUser);
   lDaoCount = qx::dao::count<CUser>();                                 qAssert(lDaoCount == 1);
   daoError = qx::dao::delete_all<CUser>();
   bDaoExist = qx::dao::exist(pUser);                                   qAssert(! bDaoExist);
   pUser->setBrother(NULL);

   typedef qx::QxCollection< long, boost::shared_ptr<CUser> > type_lstUser;
   boost::shared_ptr<CUser> ppp1; ppp1.reset(new CUser(53));
   ppp1->setProfil("profil n°10");
   ppp1->setLastName("ppp1 lastname");
   boost::shared_ptr<CUser> ppp2; ppp2.reset(new CUser(108));
   ppp2->setDateModif(QDateTime::currentDateTime());
   ppp2->setLastName("ppp1 lastname");
   type_lstUser lstUser;
   lstUser.insert(ppp1->getUserId(), ppp1);
   lstUser.insert(ppp2->getUserId(), ppp2);

   QString sQuery1 = "WHERE profil LIKE '%pro%'";
   QString sQuery2 = "LIMIT 1";
   qx::QxSqlQuery qxQuery1("WHERE profil LIKE :profil");
   qxQuery1.bind(":profil", "%pro%");

   daoError = qx::dao::insert(lstUser);
   lDaoCount = qx::dao::count<CUser>();                        qAssert(lDaoCount == 2);
   lDaoCount = qx::dao::count<CUser>(sQuery1);                 qAssert(lDaoCount == 1);
   lDaoCount = qx::dao::count<CUser>(qxQuery1);                qAssert(lDaoCount == 1);
   daoError = qx::dao::fetch_by_id(lstUser);
   bDaoExist = qx::dao::exist(lstUser);                        qAssert(bDaoExist);
   daoError = qx::dao::update(lstUser);
   daoError = qx::dao::delete_by_id(lstUser);
   lDaoCount = qx::dao::count<CUser>();                        qAssert(lDaoCount == 0);
   daoError = qx::dao::save(lstUser);

   pBrother = new qx::test::CPerson();
   pBrother->setFirstName("brother firstname from collection");
   pBrother->setLastName("brother lastname from collection");
   lstUser.getByIndex(0)->setBrother(pBrother);

   daoError = qx::dao::insert(pBrother);
   lBrotherId = pBrother->getPersonId();
   daoError = qx::dao::save(lstUser);
   daoError = qx::dao::fetch_by_query(sQuery2, lstUser);       qAssert(lstUser.size() == 1);
   daoError = qx::dao::fetch_all_with_all_relation(lstUser);   qAssert((lstUser.size() == 2) && lstUser.getByIndex(0)->getBrother() && (lstUser.getByIndex(0)->getBrother()->getLastName() == "brother lastname from collection"));
   lDaoCount = qx::dao::count<CUser>();                        qAssert(lDaoCount == 2);
   daoError = qx::dao::fetch_all(lstUser);                     qAssert(lstUser.size() == 2);
   daoError = qx::dao::delete_by_query<CUser>(sQuery1);
   lDaoCount = qx::dao::count<CUser>();                        qAssert(lDaoCount == 1);
   daoError = qx::dao::delete_all<CUser>();
   bDaoExist = qx::dao::exist(lstUser);                        qAssert(! bDaoExist);
   daoError = qx::dao::fetch_all(lstUser);                     qAssert(lstUser.size() == 0);

   //--------------------------------

   daoError = qx::dao::create_table<Bar>();
   daoError = qx::dao::create_table<Foo>();

   Foo_ptr pFoo;
   pFoo.reset(new Foo()); pFoo->setName("name1"); pFoo->setDesc("desc1"); daoError = qx::dao::save(pFoo); qAssert(pFoo->getId() == 1);
   pFoo.reset(new Foo()); pFoo->setName("name2"); pFoo->setDesc("desc2"); daoError = qx::dao::save(pFoo); qAssert(pFoo->getId() == 2);
   pFoo.reset(new Foo()); pFoo->setName("name3"); pFoo->setDesc("desc3"); daoError = qx::dao::save(pFoo); qAssert(pFoo->getId() == 3);
   pFoo.reset(new Foo()); pFoo->setName("name4"); pFoo->setDesc("desc4"); daoError = qx::dao::save(pFoo); qAssert(pFoo->getId() == 4);
   pFoo.reset(new Foo()); pFoo->setName("name5"); pFoo->setDesc("desc5"); daoError = qx::dao::save(pFoo); qAssert(pFoo->getId() == 5);
   pFoo.reset(new Foo()); pFoo->setName("name6"); pFoo->setDesc("desc6"); daoError = qx::dao::save(pFoo); qAssert(pFoo->getId() == 6);
   pFoo.reset(new Foo()); pFoo->setName("name7"); pFoo->setDesc("desc7"); daoError = qx::dao::save(pFoo); qAssert(pFoo->getId() == 7);

   // Test qx::IxPersistable interface
   daoError = pFoo->qxFetchById();        qAssert(! daoError.isValid());
   daoError = pFoo->qxUpdate();           qAssert(! daoError.isValid());
   lDaoCount = pFoo->qxCount();           qAssert(lDaoCount == 7);
   invalidValues = pFoo->qxValidate();    qAssert(invalidValues.count() == 0);

   Bar_ptr pBar;
   pBar.reset(new Bar()); pBar->setCode("code1"); pBar->setValue("value1"); pBar->setFoo(3); daoError = qx::dao::save(pBar); qAssert(pBar->getId() == 1);
   pBar.reset(new Bar()); pBar->setCode("code2"); pBar->setValue("value2"); pBar->setFoo(3); daoError = qx::dao::save(pBar); qAssert(pBar->getId() == 2);
   pBar.reset(new Bar()); pBar->setCode("code3"); pBar->setValue("value3"); pBar->setFoo(2); daoError = qx::dao::save(pBar); qAssert(pBar->getId() == 3);
   pBar.reset(new Bar()); pBar->setCode("code4"); pBar->setValue("value4"); pBar->setFoo(3); daoError = qx::dao::save(pBar); qAssert(pBar->getId() == 4);
   pBar.reset(new Bar()); pBar->setCode("code5"); pBar->setValue("value5"); pBar->setFoo(2); daoError = qx::dao::save(pBar); qAssert(pBar->getId() == 5);
   pBar.reset(new Bar()); pBar->setCode("code6"); pBar->setValue("value6"); pBar->setFoo(6); daoError = qx::dao::save(pBar); qAssert(pBar->getId() == 6);
   pBar.reset(new Bar()); pBar->setCode("code7"); pBar->setValue("value7"); pBar->setFoo(3); daoError = qx::dao::save(pBar); qAssert(pBar->getId() == 7);

   pFoo.reset(new Foo()); pFoo->setId(3);
   daoError = qx::dao::fetch_by_id_with_relation("lstBar", pFoo);    qAssert(pFoo->getBarX() && (pFoo->getBarX()->size() == 4));
   pFoo.reset(new Foo()); pFoo->setId(4);
   daoError = qx::dao::fetch_by_id_with_relation("lstBar", pFoo);    qAssert(! pFoo->getBarX() || (pFoo->getBarX()->size() == 0));
   pFoo.reset(new Foo()); pFoo->setId(2);
   daoError = qx::dao::fetch_by_id_with_relation("lstBar", pFoo);    qAssert(pFoo->getBarX() && (pFoo->getBarX()->size() == 2));

   FooX_ptr pFooX; pFooX.reset(new FooX());
   daoError = qx::dao::fetch_all_with_all_relation(pFooX);           qAssert(pFooX->size() == 7);
   pFoo = pFooX->getByKey(3);                                        qAssert(pFoo->getBarX() && (pFoo->getBarX()->size() == 4));
   pFoo = pFooX->getByKey(4);                                        qAssert(! pFoo->getBarX() || (pFoo->getBarX()->size() == 0));
   pFoo = pFooX->getByKey(2);                                        qAssert(pFoo->getBarX() && (pFoo->getBarX()->size() == 2));

   pBar.reset(new Bar()); pBar->setId(7);
   daoError = qx::dao::fetch_by_id_with_relation("foo_id", pBar);    qAssert(pBar->getFoo() && (pBar->getFoo()->getName() == "name3"));
   pFoo = pBar->getFoo(); if (pFoo) { pFoo->setDate(QDate::currentDate()); pFoo->setTime(QTime::currentTime()); pFoo->setDateTime(QDateTime::currentDateTime()); }
   qx::dump(pBar);

   // Test soft delete behavior
   pBar.reset(new Bar());
   pBar->setId(5);
   daoError = qx::dao::delete_by_id(pBar);      qAssert(! daoError.isValid());
   bDaoExist = qx::dao::exist(pBar);            qAssert(! bDaoExist);
   daoError = qx::dao::delete_all<Bar>();       qAssert(! daoError.isValid());
   long lBarCount = qx::dao::count<Bar>();      qAssert(lBarCount == 0);            Q_UNUSED(lBarCount);
   daoError = qx::dao::destroy_all<Bar>();      qAssert(! daoError.isValid());

   {
      pFoo.reset(new Foo()); pFoo->setName("name10"); pFoo->setDesc("desc10");
      pFoo->setDate(QDate::currentDate()); pFoo->setTime(QTime::currentTime()); pFoo->setDateTime(QDateTime::currentDateTime());
      boost::optional<QString> optionalString("test boost optional"); pFoo->setOptString(optionalString);

      // Test session to manage automatically database transactions (using C++ RAII)
      qx::QxSession session;
      session += qx::dao::insert(pFoo, session.database());
      session += qx::dao::update(pFoo, session.database());
      session += qx::dao::fetch_by_id(pFoo, session.database());
      session += qx::dao::delete_by_id(pFoo, session.database());
      qAssert(session.isValid());
   }

   //--------------------------------

   // Dump all registered classes into QxOrm context (introspection engine)
   qx::QxClassX::dumpAllClasses();

   pBar.reset(new Bar());
   qx::IxDataMember * pDataMember = qx::QxClassX::getDataMember("Bar", "code"); qAssert(pDataMember != NULL);
   bool bIntrospectionOk = pDataMember->setValue<QString>(pBar.get(), QString("test introspection engine")); qAssert(bIntrospectionOk);
   QString sIntrospectionTest = pDataMember->getValue<QString>(pBar.get(), (& bIntrospectionOk));
   qAssert(bIntrospectionOk && (sIntrospectionTest == "test introspection engine"));
   qAssert(pBar->getCode() == "test introspection engine");

   //--------------------------------

   daoError = qx::dao::create_table<TestQtProperty>();
   TestQtProperty testQtMetaProperty;
   QString sQtPropertyDesc = "test Qt introspection engine : meta-property using Q_PROPERTY() macro";
   testQtMetaProperty.setDesc(sQtPropertyDesc);
   testQtMetaProperty.setBirthDate(QDateTime::currentDateTime());
   daoError = qx::dao::insert(testQtMetaProperty);       qAssert(! daoError.isValid());
   daoError = qx::dao::fetch_by_id(testQtMetaProperty);  qAssert(! daoError.isValid());
   qx::IxDataMember * pQtMetaProperty = qx::QxClassX::getDataMember("TestQtProperty", "desc"); Q_UNUSED(pQtMetaProperty);
   qAssert(pQtMetaProperty && pQtMetaProperty->getValue<QString>(& testQtMetaProperty) == sQtPropertyDesc);
   qx::dump(testQtMetaProperty);

   //--------------------------------

   QDateTime queryDT1, queryDT2;
   qx_query queryToTest;
   queryToTest.where("sex").isEqualTo("female")
              .and_("age").isGreaterThan(38)
              .or_("last_name").isNotEqualTo("Dupont")
              .or_("first_name").like("Alfred")
              .and_OpenParenthesis("id").isLessThanOrEqualTo(999)
              .and_("birth_date").isBetween(queryDT1, queryDT2)
              .closeParenthesis()
              .or_("id").in(50, 999, 11, 23, 78945)
              .and_("is_deleted").isNotNull()
              .orderAsc("last_name", "first_name", "sex")
              .limit(50, 150);

   QString sQueryToTest = queryToTest.query();
   qDebug("[QxOrm] test SQL query using C++ syntax : '%s'", qPrintable(sQueryToTest));

   //--------------------------------

   qx::QxRepository<Foo> repositoryFoo;
   pFooX.reset(new FooX());
   daoError = repositoryFoo.fetchAll(pFooX);
   qAssert(! daoError.isValid());
   Foo_ptr pFooTmp;
   pFooTmp.reset(repositoryFoo.fetchById(3));
   if (pFooTmp)
   {
      pFooTmp->setDesc("desc_modified");
      daoError = repositoryFoo.save(pFooTmp);
      qAssert(! daoError.isValid());
   }

   //--------------------------------

   qAssert(qx::QxClassX::implementIxPersistable("qx::QxPersistable"));
   qAssert(! qx::QxClassX::implementIxPersistable("Bar"));

   qx::cache::clear();

   return 0;
}
