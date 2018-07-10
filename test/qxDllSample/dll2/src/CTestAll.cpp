#include "../include/precompiled.h"

#include "../include/CTestAll.h"

#include <QxOrm_Impl.h>

void CTestAll::init()
{
   m_lId = 56;
   m_oQxBool = qx_bool(true, "qx_bool description");
   m_oStdString = "std::string text";

   m_oQString = "QString text\nwith a new line";
   m_oQDate = QDate::currentDate();
   m_oQDateTime = QDateTime::currentDateTime();
   m_oQTime = QTime::currentTime();
   m_oQColor = QColor(255, 200, 200);
   m_oQFont.setBold(true);
   m_oQFont.setFamily("font family from qx test");
   m_oQPoint = QPoint(8, 11);
   m_oQRect = QRect(QPoint(52, 3), QPoint(574, 1112));
   m_oQSize = QSize(1024, 768);
   m_oQRegExp = QRegExp("qt reg exp");
   m_oQUrl = QUrl("www.qxorm.com");
   m_oQStringList << "str1" << "str2" << "str3" << "str4";
   m_oQByteArray = QByteArray("QByteArray t\0ext\nwith a new line\0and null multi\0ple null char\0", 55);
   m_oQVariant = QVariant(0.437);
   m_oQObject.setProperty("prop_1", 1);
   m_oQObject.setProperty("prop_2", 2);

   QSharedPointer<CUser> u1(new CUser());
   QSharedPointer<CUser> u2(new CUser());

   m_oStdPair = std::make_pair(QPoint(2, 6), QRect(99, 55, 44, 22));
   m_oStdList.push_back(QDateTime());
   m_oStdList.push_back(QDateTime::currentDateTime());
   m_oStdList.push_back(QDateTime());
   m_oStdMap.insert(std::make_pair("1", u1));
   m_oStdMap.insert(std::make_pair("2", u2));

   m_oStdVector.push_back(QSharedPointer<qx::test::CPerson>(new qx::test::CPerson()));
   m_oStdVector.push_back(QSharedPointer<qx::test::CPerson>(new CUser()));
}

void CTestAll::terminate()
{
   typedef boost::tuple<long, qx::test::CPerson *> qx_elt_tmp;

   _foreach(CUser * p2, m_oQVector) { if (p2) { delete p2; } }
   _foreach(qx_elt_tmp p3, m_oQxCollection) { if (p3.get<1>()) { delete p3.get<1>(); } }
}

void CTestAll::test()
{
   qx_shared_ptr<CTestAll> o1; o1.reset(new CTestAll());
   qx_shared_ptr<CTestAll> o2; o2.reset(new CTestAll());

   qx::QxCollection<long, qx_shared_ptr<CTestAll> > coll;
   coll.insert(0, o1);
   coll.insert(1, o2);

#if _QX_SERIALIZE_POLYMORPHIC
   qx::serialization::polymorphic_xml::to_file(coll, "test_all.xml");
   qx::serialization::polymorphic_xml::from_file(coll, "test_all.xml");
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   qx::serialization::binary::to_file(coll, "test_all.bin");
   qx::serialization::binary::from_file(coll, "test_all.bin");
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_XML
   qx::serialization::xml::to_file(coll, "test_all.xml");
   qx::serialization::xml::from_file(coll, "test_all.xml");
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   qx::serialization::portable_binary::to_file(coll, "test_all.bin2", 0);
   qx::serialization::portable_binary::from_file(coll, "test_all.bin2", 0);
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#ifndef _QX_NO_JSON
   qx::serialization::json::to_file(coll, "test_all.json");
   qx::serialization::json::from_file(coll, "test_all.json");
#endif // _QX_NO_JSON

   qx::clone(coll);
   qx::create("CTestAll");
}
