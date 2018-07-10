/************************************************************************************************
** File created by QxEntityEditor 1.1.9 (2016/05/04 10:05) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../../include/precompiled.h"

#include "../../include/model_view_from_qxee/blog.model_view.gen.h"
#include "../../include/model_view_from_qxee/author.model_view.gen.h"
#include "../../include/model_view_from_qxee/comment.model_view.gen.h"
#include "../../include/model_view_from_qxee/category.model_view.gen.h"

#include <QxMemLeak.h>

namespace model_view {

blog_model::blog_model(QObject * parent /* = 0 */) : blog_model_base_class(parent) { ; }

blog_model::blog_model(qx::IxModel * other, QObject * parent) : blog_model_base_class(other, parent) { ; }

blog_model::~blog_model() { ; }

QObject * blog_model::author_id(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "author_id";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->m_model.count())) { qAssert(false); return NULL; }
   blog_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { qAssert(false); return NULL; }
   long id = ptr->getblog_id();
   blog::type_author value = ptr->getauthor();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      blog tmp;
      tmp.setblog_id(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getauthor();
      ptr->setauthor(value);
   }

   model_view::author_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "author_id", pChild); }
   return static_cast<QObject *>(pChild);
}

QObject * blog_model::list_of_comment(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "list_comment";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->m_model.count())) { qAssert(false); return NULL; }
   blog_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { qAssert(false); return NULL; }
   long id = ptr->getblog_id();
   blog::type_list_of_comment value = ptr->getlist_of_comment();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      blog tmp;
      tmp.setblog_id(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getlist_of_comment();
      ptr->setlist_of_comment(value);
   }

   model_view::comment_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "list_comment", pChild); }
   return static_cast<QObject *>(pChild);
}

QObject * blog_model::list_of_category(int row, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */)
{
   QString sRelation = "list_category";
   qx::IxModel * pChild = (bLoadFromDatabase ? NULL : this->getChild(row, sRelation));
   if (pChild) { return static_cast<QObject *>(pChild); }

   if ((row < 0) || (row >= this->m_model.count())) { qAssert(false); return NULL; }
   blog_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { qAssert(false); return NULL; }
   long id = ptr->getblog_id();
   blog::type_list_of_category value = ptr->getlist_of_category();

   if (bLoadFromDatabase)
   {
      if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
      else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
      blog tmp;
      tmp.setblog_id(id);
      this->m_lastError = qx::dao::fetch_by_id_with_relation(sRelation, tmp);
      if (this->m_lastError.isValid()) { return NULL; }
      value = tmp.getlist_of_category();
      ptr->setlist_of_category(value);
   }

   model_view::category_model * pNewChild = NULL;
   pChild = qx::model_view::create_nested_model_with_type(this, QModelIndex(), value, pNewChild);
   if (pChild) { this->insertChild(row, "list_category", pChild); }
   return static_cast<QObject *>(pChild);
}

void blog_model::syncNestedModel(int row, const QStringList & relation)
{
   Q_UNUSED(relation);
   qx::IxModel * pNestedModel = NULL;
   if ((row < 0) || (row >= this->m_model.count())) { return; }
   blog_model_base_class::type_ptr ptr = this->m_model.getByIndex(row);
   if (! ptr) { return; }

   pNestedModel = this->getChild(row, "author_id");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      blog::type_author value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setauthor(value);
   }

   pNestedModel = this->getChild(row, "list_comment");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      blog::type_list_of_comment value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setlist_of_comment(value);
   }

   pNestedModel = this->getChild(row, "list_category");
   if (pNestedModel)
   {
      this->syncNestedModelRecursive(pNestedModel, relation);
      blog::type_list_of_category value;
      qx::model_view::sync_nested_model(pNestedModel, value);
      ptr->setlist_of_category(value);
   }
}

void blog_model::syncAllNestedModel(const QStringList & relation)
{
   if (this->m_lstChild.count() <= 0) { return; }
   for (long l = 0; l < this->m_model.count(); l++)
   { this->syncNestedModel(static_cast<int>(l), relation); }
}

} // namespace model_view
