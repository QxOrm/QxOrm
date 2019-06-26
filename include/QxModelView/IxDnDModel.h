/****************************************************************************
**
** http://www.qxorm.com/
** Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software
**
** Commercial Usage
** Licensees holding valid commercial QxOrm licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Lionel Marty
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met : http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, or
** if you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifdef QT_WIDGETS_LIB
#ifndef _IX_DND_MODEL_H_
#define _IX_DND_MODEL_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxDnDModel.h
 * \author The Jimmytaker
 * \ingroup QxModelView
 * \brief Plug-in class to use as a base class for QxModel.
 */

#include <QxModelView/IxModel.h>
#include <QtWidgets/QUndoStack>
#include <QMimeData>
#include <QxModelView/QxModelRowCompare.h>

namespace qx {

class QX_DLL_EXPORT IxDnDModel : public IxModel
{

   Q_OBJECT

public:

    enum e_drag_drop { e_no_drag_drop = 0, e_drag_drop_relations, e_drag_drop_all };
    enum e_undo { uNone, uChangeRel, uAddRel };

signals:
    void relationsAboutToBeUpdated();               //!< Emitted when executing DragNDrop
    void relationsUpdated();                        //!< Emitted when executing DragNDrop

public:

    IxDnDModel(QObject * parent = 0);
    virtual ~IxDnDModel();

   Q_INVOKABLE bool getOnlyDelRelations() const;
   Q_INVOKABLE void setOnlyDelRelations(bool bEnable);
   Q_INVOKABLE virtual bool qxDeleteRow_(int row) Q_DECL_OVERRIDE;

   e_drag_drop getDragDropMode() const;
   void setDragDropMode(e_drag_drop e, QUndoStack* undo);

   virtual Qt::ItemFlags flags(const QModelIndex & index) const Q_DECL_OVERRIDE;
   virtual Qt::DropActions supportedDropActions() const Q_DECL_OVERRIDE;
   virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                                int column, const QModelIndex &parent) const;
   virtual bool dropMimeData(const QMimeData * data, Qt::DropAction action, int row,
                             int column, const QModelIndex & parent) Q_DECL_OVERRIDE;
   virtual QStringList mimeTypes() const Q_DECL_OVERRIDE;
   virtual QMimeData *mimeData(const QModelIndexList & indexes) const Q_DECL_OVERRIDE;
   virtual bool removeRowsGeneric(int row, int count) Q_DECL_OVERRIDE;

   template <class K, class T>
   static void Sort(qx::QxCollection<K, std::shared_ptr<T> >& c, const QString& sColumn)
   {
       if (qx::QxClass<T>::getSingleton()->getDataMemberX())
       {
           long lCount = qx::QxClass<T>::getSingleton()->getDataMemberX()->count();
           for (long l = 0; l < lCount; l++)
           {
               qx::IxDataMember * p = qx::QxClass<T>::getSingleton()->getDataMemberX()->get(l);
               if (!p || p->getName() != sColumn) { continue; }
               c.sort(qx::model_view::QxModelRowCompare<QPair<K, std::shared_ptr<T> > >(true, p));
               break;
           }
       }
   }

   friend class UndoCommand;
   class UndoCommand : public QUndoCommand
   {
   public:
       UndoCommand(e_undo uCommand, int row, const QByteArray& baDrop, IxDnDModel* model,
                   QUndoCommand *parent = Q_NULLPTR);

       virtual void undo() Q_DECL_OVERRIDE
       {
           //TODO
       }

       //! Executes the action
       virtual void redo() Q_DECL_OVERRIDE;

   private:
      e_undo m_uCommand;
      IxDnDModel* m_ix;
      int m_nRow;
      QByteArray m_baDrop;
   };

protected:
   QUndoStack* getUndo() { return (QUndoStack*) m_hCustomProperties["undo"].toLongLong(); }
   QString commandText(e_undo uCommand);
};

} // namespace qx

#endif // _IX_DND_MODEL_H_
#endif //QT_WIDGETS_LIB
