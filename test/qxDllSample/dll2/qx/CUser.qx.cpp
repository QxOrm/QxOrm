#include "../include/precompiled.h"

#include "../include/CUser.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_DLL2(CUser)

namespace qx {
template <> void register_class(QxClass<CUser> & t)
{
   IxDataMember * pData = NULL;
   IxSqlRelation * pRelation = NULL;
   IxValidator * pValidator = NULL;

   pData = t.data(& CUser::m_lUserId, "idUser", 0);
   pData = t.data(& CUser::m_sProfil, "profil", 0);    pData->setSqlAlias("profil");
   pData = t.data(& CUser::m_bIsAdmin, "isAdmin", 1);
   pData = t.data(& CUser::m_dtModif, "dtModif", 1);

   pRelation = t.relationManyToOne(& CUser::m_pBrother, "brother", 2);

   QxValidatorX<CUser> * pAllValidator = t.getAllValidator();
   if (! pAllValidator) { qAssert(false); return; }
   pValidator = pAllValidator->add_RecursiveValidator<qx::test::CPerson *>("brother");
}}
