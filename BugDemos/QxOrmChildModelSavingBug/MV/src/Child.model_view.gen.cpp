/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 09:33) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ChildModelSavingBug_precompiled_header.model_view.gen.h"

#include "../include/Child.model_view.gen.h"
#include "../include/Grandchild.model_view.gen.h"
#include "../include/Parent.model_view.gen.h"

#include <QxOrm_Impl.h>

namespace model_view {

Child_model::Child_model(QObject * parent /* = 0 */) : Child_model_base_class(parent) { ; }

Child_model::Child_model(qx::IxModel * other, QObject * parent) : Child_model_base_class(other, parent) { ; }

Child_model::~Child_model() { ; }

QObject * Child_model::list_of_Grandchild(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "list_of_Grandchild";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->m_model.count())) { qAssert(false); return NULL; }
   Child_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { qAssert(false); return NULL; }
   long id = ptr->getChild_id();
   Child::type_list_of_Grandchild value = ptr->getlist_of_Grandchild();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      Child tmp;
      tmp.setChild_id(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getlist_of_Grandchild();
      ptr->setlist_of_Grandchild(value);
   }

   model_view::Grandchild_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "list_of_Grandchild", pChild); }
   return static_cast<QObject *>(pChild);
}

QObject * Child_model::parent(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "parent";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->m_model.count())) { qAssert(false); return NULL; }
   Child_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { qAssert(false); return NULL; }
   long id = ptr->getChild_id();
   Child::type_parent value = ptr->getparent();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      Child tmp;
      tmp.setChild_id(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getparent();
      ptr->setparent(value);
   }

   model_view::Parent_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "parent", pChild); }
   return static_cast<QObject *>(pChild);
}

void Child_model::syncNestedModel(int row, const QStringList & relation)
{
   Q_UNUSED(relation);
   qx::IxModel * pNestedModel = NULL;
   if ((row < 0) || (row >= this->m_model.count())) { return; }
   Child_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { return; }

   pNestedModel = this->getChild(row, "list_of_Grandchild");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      Child::type_list_of_Grandchild value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setlist_of_Grandchild(value);
   }

   pNestedModel = this->getChild(row, "parent");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      Child::type_parent value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setparent(value);
   }
}

void Child_model::syncAllNestedModel(const QStringList & relation)
{
   if (this->m_lstChild.count() <= 0) { return; }
   for (long l = 0; l < this->m_model.count(); l++)
   { this->syncNestedModel(static_cast<int>(l), relation); }
}

} // namespace model_view
