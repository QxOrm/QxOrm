/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 09:33) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/ChildModelSavingBug_precompiled_header.model_view.gen.h"

#include "../include/Grandchild.model_view.gen.h"
#include "../include/Child.model_view.gen.h"

#include <QxOrm_Impl.h>

namespace model_view {

Grandchild_model::Grandchild_model(QObject * parent /* = 0 */) : Grandchild_model_base_class(parent) { ; }

Grandchild_model::Grandchild_model(qx::IxModel * other, QObject * parent) : Grandchild_model_base_class(other, parent) { ; }

Grandchild_model::~Grandchild_model() { ; }

QObject * Grandchild_model::parent(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "parent";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->m_model.count())) { qAssert(false); return NULL; }
   Grandchild_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { qAssert(false); return NULL; }
   long id = ptr->getGrandchild_id();
   Grandchild::type_parent value = ptr->getparent();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      Grandchild tmp;
      tmp.setGrandchild_id(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getparent();
      ptr->setparent(value);
   }

   model_view::Child_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "parent", pChild); }
   return static_cast<QObject *>(pChild);
}

void Grandchild_model::syncNestedModel(int row, const QStringList & relation)
{
   Q_UNUSED(relation);
   qx::IxModel * pNestedModel = NULL;
   if ((row < 0) || (row >= this->m_model.count())) { return; }
   Grandchild_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { return; }

   pNestedModel = this->getChild(row, "parent");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      Grandchild::type_parent value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setparent(value);
   }
}

void Grandchild_model::syncAllNestedModel(const QStringList & relation)
{
   if (this->m_lstChild.count() <= 0) { return; }
   for (long l = 0; l < this->m_model.count(); l++)
   { this->syncNestedModel(static_cast<int>(l), relation); }
}

} // namespace model_view
