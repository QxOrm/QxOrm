#include "../include/precompiled.h"

#include "../include/CPerson.h"

#include <QxOrm_Impl.h>

void myGlobalValidator_1(const QVariant & value, const qx::IxValidator * validator, qx::QxInvalidValueX & invalidValues);
void myGlobalValidator_2(const QString & value, const qx::IxValidator * validator, qx::QxInvalidValueX & invalidValues);

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_QX_DLL1(qx::test::CPerson, qx_test_CPerson)

namespace qx {
template <> void register_class(QxClass<qx::test::CPerson> & t)
{
   IxDataMember * pData = NULL;
   IxFunction * pFct = NULL;
   IxValidator * pValidator = NULL;

   t.setName("CPerson");

   pData = t.id(& qx::test::CPerson::m_lPersonId, "idPerson", 0);

   pData = t.data(& qx::test::CPerson::m_sFirstName, "firstName", 0);
   pData = t.data(& qx::test::CPerson::m_sLastName, "lastName", 0);
   pData = t.data(& qx::test::CPerson::m_dDouble, "double", 0);
   pData = t.data(& qx::test::CPerson::m_eSex, "sex", 0);

   pFct = t.fct_0<long>(& qx::test::CPerson::getPersonId, "fct_getPersonId");
   pFct = t.fct_0<QString>(& qx::test::CPerson::getFirstName, "fct_getFirstName");
   pFct = t.fct_1<void, long>(& qx::test::CPerson::setPersonId, "fct_setPersonId");

   pFct = t.fctStatic_1<int, const QString &>(& qx::test::CPerson::testStaticFct, "fct_testStaticFct");

   QxValidatorX<qx::test::CPerson> * pAllValidator = t.getAllValidator();
   if (! pAllValidator) { qAssert(false); return; }
   pValidator = pAllValidator->add_NotEmpty("firstName", "a person must have a firstname");
   pValidator = pAllValidator->add_NotEmpty("lastName");
   pValidator = pAllValidator->add_MinDecimal("double", 0.5, "'double' field must be greater than or equal to '0.5'");
   pValidator = pAllValidator->add_MaxDecimal("double", 103.19);
   pValidator = pAllValidator->add_CustomValidator(& qx::test::CPerson::isValid);
   pValidator = pAllValidator->add_CustomValidator_QVariant(& myGlobalValidator_1, "firstName");
   pValidator = pAllValidator->add_CustomValidator_DataType<QString>(& myGlobalValidator_2, "lastName");
}}

// ********************************************************************************************************
// ********************************************************************************************************

// Example of global functions 'myGlobalValidator_1' and 'myGlobalValidator_2' used by 'QxValidator' module
// Those functions will be called automatically by validator engine of QxOrm library :
// - when you try to insert or update using 'qx::dao::xxx' functions
// - when you call 'qx::validate()' function

void myGlobalValidator_1(const QVariant & value, const qx::IxValidator * validator, qx::QxInvalidValueX & invalidValues)
{
   // Here you can test the value (converted to QVariant type)
   // If an invalid value is detected, just add a message into 'invalidValues' collection

   Q_UNUSED(value); Q_UNUSED(validator); Q_UNUSED(invalidValues);
}

void myGlobalValidator_2(const QString & value, const qx::IxValidator * validator, qx::QxInvalidValueX & invalidValues)
{
   // Here you can test the value (with its real type, in this example, the data-member is a 'QString' type)
   // If an invalid value is detected, just add a message into 'invalidValues' collection

   Q_UNUSED(value); Q_UNUSED(validator); Q_UNUSED(invalidValues);
}

// ********************************************************************************************************
// ********************************************************************************************************
