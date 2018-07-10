/************************************************************************************************
** File created by QxEntityEditor 1.1.9 (2016/05/04 10:05) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../../include/precompiled.h"

#include "../../include/model_view_from_qxee/author.model_view.gen.h"
#include "../../include/model_view_from_qxee/blog.model_view.gen.h"

#include <QxMemLeak.h>

namespace model_view {

author_model::author_model(QObject * parent /* = 0 */) : author_model_base_class(parent) { ; }

author_model::author_model(qx::IxModel * other, QObject * parent) : author_model_base_class(other, parent) { ; }

author_model::~author_model() { ; }

QObject * author_model::list_of_blog(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "list_blog";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->m_model.count())) { qAssert(false); return NULL; }
   author_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { qAssert(false); return NULL; }
   QString id = ptr->getauthor_id();
   author::type_list_of_blog value = ptr->getlist_of_blog();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      author tmp;
      tmp.setauthor_id(id);
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

void author_model::syncNestedModel(int row, const QStringList & relation)
{
   Q_UNUSED(relation);
   qx::IxModel * pNestedModel = NULL;
   if ((row < 0) || (row >= this->m_model.count())) { return; }
   author_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { return; }

   pNestedModel = this->getChild(row, "list_blog");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      author::type_list_of_blog value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setlist_of_blog(value);
   }
}

void author_model::syncAllNestedModel(const QStringList & relation)
{
   if (this->m_lstChild.count() <= 0) { return; }
   for (long l = 0; l < this->m_model.count(); l++)
   { this->syncNestedModel(static_cast<int>(l), relation); }
}

} // namespace model_view
