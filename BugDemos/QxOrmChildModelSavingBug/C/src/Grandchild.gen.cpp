/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 09:33) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ChildModelSavingBug_precompiled_header.gen.h"

#include "../include/Grandchild.gen.h"
#include "../include/Child.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_CHILDMODELSAVINGBUG(Grandchild, Grandchild)

namespace qx {

template <>
void register_class(QxClass<Grandchild> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("t_Grandchild");

   pData = t.id(& Grandchild::m_Grandchild_id, "Grandchild_id", 0);

   pData = t.data(& Grandchild::m_Name, "Name", 0, true, true);

   pRelation = t.relationManyToOne(& Grandchild::m_parent, "parent", 0);

   qx::QxValidatorX<Grandchild> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

Grandchild::Grandchild() : m_Grandchild_id(0) { ; }

Grandchild::Grandchild(const long & id) : m_Grandchild_id(id) { ; }

Grandchild::~Grandchild() { ; }

long Grandchild::getGrandchild_id() const { return m_Grandchild_id; }

QString Grandchild::getName() const { return m_Name; }

Grandchild::type_parent Grandchild::getparent() const { return m_parent; }

void Grandchild::setGrandchild_id(const long & val) { m_Grandchild_id = val; }

void Grandchild::setName(const QString & val) { m_Name = val; }

void Grandchild::setparent(const Grandchild::type_parent & val) { m_parent = val; }

Grandchild::type_parent Grandchild::getparent(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getparent(); }
   QString sRelation = "parent";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Grandchild tmp;
   tmp.m_Grandchild_id = this->m_Grandchild_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_parent = tmp.m_parent; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_parent;
}

