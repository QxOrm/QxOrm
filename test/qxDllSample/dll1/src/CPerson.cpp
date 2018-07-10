#include "../include/precompiled.h"

#include "../include/CPerson.h"

#include <QxOrm_Impl.h>

namespace qx {
namespace test {

void CPerson::isValid(qx::QxInvalidValueX & invalidValues)
{
   // This method is called automatically by 'QxValidator' module (validator engine of QxOrm library) :
   // - when you try to insert or update using 'qx::dao::xxx' functions
   // - when you call 'qx::validate()' function

   // For registration, see 'pAllValidator->add_CustomValidator(& qx::test::CPerson::isValid);' into 'qx::register_class<T>()' function

   // Here, you can verify some values of your instance
   // If a value is not valid, you must add an invalid value into the collection 'invalidValues'

   if ((m_sFirstName == "admin") || (m_sLastName == "admin"))
   { invalidValues.insert("you cannot set 'admin' for the name of a person"); }
}

int CPerson::testStaticFct(const QString & s)
{
   return s.toInt();
}

} // namespace test
} // namespace qx
