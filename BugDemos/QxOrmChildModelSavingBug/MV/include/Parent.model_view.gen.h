/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 09:15) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CHILDMODELSAVINGBUG_PARENT_MODEL_VIEW_H_
#define _CHILDMODELSAVINGBUG_PARENT_MODEL_VIEW_H_

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../include/ChildModelSavingBug_precompiled_header.model_view.gen.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include "../../C/include/Parent.gen.h"

namespace model_view {

typedef qx::QxModel<Parent> Parent_model_base_class;

class CHILDMODELSAVINGBUG_MODEL_VIEW_EXPORT Parent_model : public Parent_model_base_class
{

   Q_OBJECT

public:

   Parent_model(QObject * parent = 0);
   Parent_model(qx::IxModel * other, QObject * parent);
   virtual ~Parent_model();

   Q_INVOKABLE QObject * list_of_Child(int row, bool bLoadFromDatabase = false, const QString & sAppendRelations = QString());

   /* List of properties exposed by the model (2) :
      - Parent_id
      - Name
   */

protected:

   virtual void syncNestedModel(int row, const QStringList & relation);
   virtual void syncAllNestedModel(const QStringList & relation);

};

} // namespace model_view

#endif // _CHILDMODELSAVINGBUG_PARENT_MODEL_VIEW_H_
