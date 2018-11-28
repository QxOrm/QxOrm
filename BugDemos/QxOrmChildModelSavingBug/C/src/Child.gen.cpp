/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 11:12) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ChildModelSavingBug_precompiled_header.gen.h"

#include "../include/Child.gen.h"
#include "../include/Grandchild.gen.h"
#include "../include/Parent.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_CHILDMODELSAVINGBUG(Child, Child)

namespace qx {

template <>
void register_class(QxClass<Child> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("t_Child");

   pData = t.id(& Child::m_Child_id, "Child_id", 0);

   pData = t.data(& Child::m_Name, "Name", 0, true, true);

   pRelation = t.relationOneToMany(& Child::m_list_of_Grandchild, "list_of_Grandchild", "parent", 0);
   pRelation = t.relationManyToOne(& Child::m_parent, "parent", 0);

   qx::QxValidatorX<Child> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

Child::Child() : m_Child_id(0) { ; }

Child::Child(const long & id) : m_Child_id(id) { ; }

Child::~Child() { ; }

long Child::getChild_id() const { return m_Child_id; }

QString Child::getName() const { return m_Name; }

Child::type_list_of_Grandchild Child::getlist_of_Grandchild() const { return m_list_of_Grandchild; }

Child::type_list_of_Grandchild & Child::list_of_Grandchild() { return m_list_of_Grandchild; }

const Child::type_list_of_Grandchild & Child::list_of_Grandchild() const { return m_list_of_Grandchild; }

Child::type_parent Child::getparent() const { return m_parent; }

void Child::setChild_id(const long & val) { m_Child_id = val; }

void Child::setName(const QString & val) { m_Name = val; }

void Child::setlist_of_Grandchild(const Child::type_list_of_Grandchild & val) { m_list_of_Grandchild = val; }

void Child::setparent(const Child::type_parent & val) { m_parent = val; }

Child::type_list_of_Grandchild Child::getlist_of_Grandchild(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_Grandchild(); }
   QString sRelation = "list_of_Grandchild";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Child tmp;
   tmp.m_Child_id = this->m_Child_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_Grandchild = tmp.m_list_of_Grandchild; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_Grandchild;
}

Child::type_list_of_Grandchild & Child::list_of_Grandchild(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_Grandchild(); }
   QString sRelation = "list_of_Grandchild";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Child tmp;
   tmp.m_Child_id = this->m_Child_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_Grandchild = tmp.m_list_of_Grandchild; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_Grandchild;
}

Child::type_parent Child::getparent(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getparent(); }
   QString sRelation = "parent";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   Child tmp;
   tmp.m_Child_id = this->m_Child_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_parent = tmp.m_parent; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_parent;
}

