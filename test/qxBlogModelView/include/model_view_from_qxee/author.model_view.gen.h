/************************************************************************************************
** File created by QxEntityEditor 1.1.9 (2016/05/04 10:05) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _QXBLOG_AUTHOR_MODEL_VIEW_H_
#define _QXBLOG_AUTHOR_MODEL_VIEW_H_

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../../include/precompiled.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include "../../include/author.h"

namespace model_view {

typedef qx::QxModel<author> author_model_base_class;

class QX_BLOG_DLL_EXPORT author_model : public author_model_base_class
{

   Q_OBJECT

public:

   author_model(QObject * parent = 0);
   author_model(qx::IxModel * other, QObject * parent);
   virtual ~author_model();

   Q_INVOKABLE QObject * list_of_blog(int row, bool bLoadFromDatabase = false, const QString & sAppendRelations = QString());

   /* List of properties exposed by the model (5) :
      - author_id
      - firstname
      - lastname
      - birthdate
      - sex
   */

protected:

   virtual void syncNestedModel(int row, const QStringList & relation);
   virtual void syncAllNestedModel(const QStringList & relation);

};

} // namespace model_view

#endif // _QXBLOG_AUTHOR_MODEL_VIEW_H_
