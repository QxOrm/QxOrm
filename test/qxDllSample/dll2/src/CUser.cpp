#include "../include/precompiled.h"

#include "../include/CUser.h"

#include <QxMemLeak.h>

void CUser::test()
{
   boost::shared_ptr<QObject> ptrTmp;
   ptrTmp.reset(new CUser());
   qx::clone(ptrTmp);

#if _QX_SERIALIZE_POLYMORPHIC
   qx::serialization::polymorphic_xml::to_file(ptrTmp, "pointer_from_CUser.xml");
   qx::serialization::polymorphic_xml::from_file(ptrTmp, "pointer_from_CUser.xml");
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_XML
   qx::serialization::xml::to_file(ptrTmp, "pointer_from_CUser.xml");
   qx::serialization::xml::from_file(ptrTmp, "pointer_from_CUser.xml");
#endif // _QX_SERIALIZE_XML

   qx::test::CPerson person;
   qx::clone(person);
   qx::create("qx::test::CPerson");

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
   qx::clone(user);
   qx::create("CUser");

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

   qx::test::CPerson * pPerson = new qx::test::CPerson(); // You find a memory leak !!!
   Q_UNUSED(pPerson);
}
