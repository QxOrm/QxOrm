/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 11:12) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ChildModelSavingBug_precompiled_header.gen.h"

#include "../include/Parent.gen.h"
#include "../include/Child.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_CHILDMODELSAVINGBUG(Parent, Parent)

namespace qx {

template <>
void register_class(QxClass<Parent> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("t_Parent");

   pData = t.id(& Parent::m_Parent_id, "Parent_id", 0);

   pData = t.data(& Parent::m_Name, "Name", 0, true, true);

   pRelation = t.relationOneToMany(& Parent::m_list_of_Child, "list_of_Child", "parent", 0);

   qx::QxValidatorX<Parent> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

Parent::Parent() : m_Parent_id(0) { ; }

Parent::Parent(const long & id) : m_Parent_id(id) { ; }

Parent::~Parent() { ; }

long Parent::getParent_id() const { return m_Parent_id; }

QString Parent::getName() const { return m_Name; }

Parent::type_list_of_Child Parent::getlist_of_Child() const { return m_list_of_Child; }

Parent::type_list_of_Child & Parent::list_of_Child() { return m_list_of_Child; }

const Parent::type_list_of_Child & Parent::list_of_Child() const { return m_list_of_Child; }

void Parent::setParent_id(const long & val) { m_Parent_id = val; }

void Parent::setName(const QString & val) { m_Name = val; }

void Parent::setlist_of_Child(const Parent::type_list_of_Child & val) { m_list_of_Child = val; }

Parent::type_list_of_Child Parent::getlist_of_Child(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_Child(); }
   QString sRelation = "list_of_Child";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Parent tmp;
   tmp.m_Parent_id = this->m_Parent_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_Child = tmp.m_list_of_Child; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_Child;
}

Parent::type_list_of_Child & Parent::list_of_Child(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_Child(); }
   QString sRelation = "list_of_Child";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Parent tmp;
   tmp.m_Parent_id = this->m_Parent_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_Child = tmp.m_list_of_Child; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_Child;
}

