/************************************************************************************************
** File created by QxEntityEditor 1.1.9 (2016/05/04 10:05) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../../include/precompiled.h"

#include "../../include/model_view_from_qxee/comment.model_view.gen.h"
#include "../../include/model_view_from_qxee/blog.model_view.gen.h"

#include <QxMemLeak.h>

namespace model_view {

comment_model::comment_model(QObject * parent /* = 0 */) : comment_model_base_class(parent) { ; }

comment_model::comment_model(qx::IxModel * other, QObject * parent) : comment_model_base_class(other, parent) { ; }

comment_model::~comment_model() { ; }

QObject * comment_model::blog_id(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "blog_id";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->m_model.count())) { qAssert(false); return NULL; }
   comment_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { qAssert(false); return NULL; }
   long id = ptr->getcomment_id();
   comment::type_blog_id value = ptr->getblog_id();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      comment tmp;
      tmp.setcomment_id(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getblog_id();
      ptr->setblog_id(value);
   }

   model_view::blog_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "blog_id", pChild); }
   return static_cast<QObject *>(pChild);
}

void comment_model::syncNestedModel(int row, const QStringList & relation)
{
   Q_UNUSED(relation);
   qx::IxModel * pNestedModel = NULL;
   if ((row < 0) || (row >= this->m_model.count())) { return; }
   comment_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { return; }

   pNestedModel = this->getChild(row, "blog_id");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      comment::type_blog_id value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setblog_id(value);
   }
}

void comment_model::syncAllNestedModel(const QStringList & relation)
{
   if (this->m_lstChild.count() <= 0) { return; }
   for (long l = 0; l < this->m_model.count(); l++)
   { this->syncNestedModel(static_cast<int>(l), relation); }
}

} // namespace model_view
