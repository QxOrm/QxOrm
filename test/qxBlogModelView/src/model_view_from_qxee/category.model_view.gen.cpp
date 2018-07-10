/************************************************************************************************
** File created by QxEntityEditor 1.1.9 (2016/05/04 10:05) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../../include/precompiled.h"

#include "../../include/model_view_from_qxee/category.model_view.gen.h"
#include "../../include/model_view_from_qxee/blog.model_view.gen.h"

#include <QxMemLeak.h>

namespace model_view {

category_model::category_model(QObject * parent /* = 0 */) : category_model_base_class(parent) { ; }

category_model::category_model(qx::IxModel * other, QObject * parent) : category_model_base_class(other, parent) { ; }

category_model::~category_model() { ; }

QObject * category_model::list_of_blog(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "list_blog";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->m_model.count())) { qAssert(false); return NULL; }
   category_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { qAssert(false); return NULL; }
   long id = ptr->getcategory_id();
   category::type_list_of_blog value = ptr->getlist_of_blog();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      category tmp;
      tmp.setcategory_id(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getlist_of_blog();
      ptr->setlist_of_blog(value);
   }

   model_view::blog_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "list_blog", pChild); }
   return static_cast<QObject *>(pChild);
}

void category_model::syncNestedModel(int row, const QStringList & relation)
{
   Q_UNUSED(relation);
   qx::IxModel * pNestedModel = NULL;
   if ((row < 0) || (row >= this->m_model.count())) { return; }
   category_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { return; }

   pNestedModel = this->getChild(row, "list_blog");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      category::type_list_of_blog value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setlist_of_blog(value);
   }
}

void category_model::syncAllNestedModel(const QStringList & relation)
{
   if (this->m_lstChild.count() <= 0) { return; }
   for (long l = 0; l < this->m_model.count(); l++)
   { this->syncNestedModel(static_cast<int>(l), relation); }
}

} // namespace model_view
