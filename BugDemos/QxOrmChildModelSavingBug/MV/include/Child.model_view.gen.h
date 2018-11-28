/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 09:33) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CHILDMODELSAVINGBUG_CHILD_MODEL_VIEW_H_
#define _CHILDMODELSAVINGBUG_CHILD_MODEL_VIEW_H_

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../include/ChildModelSavingBug_precompiled_header.model_view.gen.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include "../../C/include/Child.gen.h"

namespace model_view {

typedef qx::QxModel<Child> Child_model_base_class;

class CHILDMODELSAVINGBUG_MODEL_VIEW_EXPORT Child_model : public Child_model_base_class
{

   Q_OBJECT

public:

   Child_model(QObject * parent = 0);
   Child_model(qx::IxModel * other, QObject * parent);
   virtual ~Child_model();

   Q_INVOKABLE QObject * list_of_Grandchild(int row, bool bLoadFromDatabase = false, const QString & sAppendRelations = QString());
   Q_INVOKABLE QObject * parent(int row, bool bLoadFromDatabase = false, const QString & sAppendRelations = QString());

   /* List of properties exposed by the model (2) :
      - Child_id
      - Name
   */

protected:

   virtual void syncNestedModel(int row, const QStringList & relation);
   virtual void syncAllNestedModel(const QStringList & relation);

};

} // namespace model_view

#endif // _CHILDMODELSAVINGBUG_CHILD_MODEL_VIEW_H_
