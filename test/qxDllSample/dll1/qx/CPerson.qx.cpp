#include "../include/precompiled.h"

#include "../include/CPerson.h"

#include <QxMemLeak.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_QX_DLL1(qx::test::CPerson, qx_test_CPerson)

namespace qx {
template <> void register_class(QxClass<qx::test::CPerson> & t)
{
   IxDataMember * pData = NULL;
   IxFunction * pFct = NULL;

   t.setName("CPerson");

   pData = t.id(& qx::test::CPerson::m_lPersonId, "idPerson", 0);

   pData = t.data(& qx::test::CPerson::m_sFirstName, "firstName", 0);
   pData = t.data(& qx::test::CPerson::m_sLastName, "lastName", 0);
   pData = t.data(& qx::test::CPerson::m_dDouble, "double", 0);
   pData = t.data(& qx::test::CPerson::m_eSex, "sex", 0);

   pFct = t.fct_0<long>(& qx::test::CPerson::getPersonId, "fct_getPersonId");
   pFct = t.fct_0<QString>(& qx::test::CPerson::getFirstName, "fct_getFirstName");
   pFct = t.fct_1<void, long>(& qx::test::CPerson::setPersonId, "fct_setPersonId");
}}
