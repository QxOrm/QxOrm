/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 09:15) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ChildModelSavingBug_precompiled_header.model_view.gen.h"

#include "../include/Parent.model_view.gen.h"
#include "../include/Child.model_view.gen.h"

#include <QxOrm_Impl.h>

namespace model_view {

Parent_model::Parent_model(QObject * parent /* = 0 */) : Parent_model_base_class(parent) { ; }

Parent_model::Parent_model(qx::IxModel * other, QObject * parent) : Parent_model_base_class(other, parent) { ; }

Parent_model::~Parent_model() { ; }

QObject * Parent_model::list_of_Child(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "list_of_Child";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->m_model.count())) { qAssert(false); return NULL; }
   Parent_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { qAssert(false); return NULL; }
   long id = ptr->getParent_id();
   Parent::type_list_of_Child value = ptr->getlist_of_Child();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      Parent tmp;
      tmp.setParent_id(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getlist_of_Child();
      ptr->setlist_of_Child(value);
   }

   model_view::Child_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "list_of_Child", pChild); }
   return static_cast<QObject *>(pChild);
}

void Parent_model::syncNestedModel(int row, const QStringList & relation)
{
   Q_UNUSED(relation);
   qx::IxModel * pNestedModel = NULL;
   if ((row < 0) || (row >= this->m_model.count())) { return; }
   Parent_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { return; }

   pNestedModel = this->getChild(row, "list_of_Child");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      Parent::type_list_of_Child value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setlist_of_Child(value);
   }
}

void Parent_model::syncAllNestedModel(const QStringList & relation)
{
   if (this->m_lstChild.count() <= 0) { return; }
   for (long l = 0; l < this->m_model.count(); l++)
   { this->syncNestedModel(static_cast<int>(l), relation); }
}

} // namespace model_view
