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
#include <QxPrecompiled.h>

#include <QxModelView/IxDnDModel.h>

namespace qx {

IxDnDModel::IxDnDModel(QObject * parent /* = 0 */) : IxModel(parent)
{
    //!< Must be provided my the application
    m_hCustomProperties["undo"] = 0;

    //!< Drag and drop mode
    m_hCustomProperties["eDragDrop"] = (int) e_no_drag_drop;

    //!< When removing an element from a nested model, will only remote the relation,
    //! but not the element itself
    m_hCustomProperties["bOnlyDelRelations"] = false;
}

IxDnDModel::~IxDnDModel() { ; }

void IxDnDModel::setOnlyDelRelations(bool bEnable)
{
    m_hCustomProperties["bOnlyDelRelations"] = bEnable;
}

bool IxDnDModel::getOnlyDelRelations() const{
    return m_hCustomProperties["bOnlyDelRelations"].toBool();
}

bool IxDnDModel::qxDeleteRow_(int row)
{
    return m_pParent && getOnlyDelRelations() || IxModel::qxDeleteRow_(row);
}

bool IxDnDModel::removeRowsGeneric(int row, int count)
{
    if (! m_pCollection) { qAssert(false); return false; }
   beginRemoveRows(QModelIndex(), row, (row + count - 1));
   for (int i = 0; i < count; ++i)
   { m_pCollection->_remove(row); removeListOfChild(row); }
   if (m_pParent && getOnlyDelRelations()) m_pParent->saveChildRelations(this);
   updateShowEmptyLine();
   endRemoveRows();
   if (m_pParent && getOnlyDelRelations()) emit relationsUpdated();
   return true;
}

Qt::ItemFlags IxDnDModel::flags(const QModelIndex & index) const
{
    Qt::ItemFlags defaultFlags = Qt::ItemIsEditable;
   if (index.isValid()) defaultFlags |= QAbstractItemModel::flags(index);
   return getDragDropMode() ? Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags :
        defaultFlags;
}

void IxDnDModel::setDragDropMode(e_drag_drop e, QUndoStack* undo)
{
    m_hCustomProperties["eDragDrop"] = int(undo ? e : e_no_drag_drop);
    m_hCustomProperties["undo"] = (qint64) undo;
}

IxDnDModel::e_drag_drop IxDnDModel::getDragDropMode() const
{
    return (e_drag_drop) m_hCustomProperties["eDragDrop"].toInt();
}

Qt::DropActions IxDnDModel::supportedDropActions() const
{
    if (getDragDropMode() == e_drag_drop_all)
        return Qt::CopyAction | Qt::MoveAction;
    if (getDragDropMode() == e_drag_drop_relations) {
        Qt::DropActions r = Qt::IgnoreAction;
        if (getClass()->getDataMemberX())
        {
            long lCount = getClass()->getDataMemberX()->count();
            for (long l = 0; l < lCount; l++)
            {
                IxDataMember * p = getClass()->getDataMemberX()->get(l); if (!p) { continue; }
                IxSqlRelation * pRelation = p->getSqlRelation();
                if (pRelation) {
                    if (pRelation->getRelationType() == IxSqlRelation::one_to_many ||
                            pRelation->getRelationType() == IxSqlRelation::many_to_one)
                        r |= Qt::MoveAction;
                    else if (pRelation->getRelationType() == IxSqlRelation::many_to_many)
                        return Qt::MoveAction | Qt::CopyAction;
                }
            }
        }
        return r;
    }
   return IxModel::supportedDropActions();
}

IxDnDModel::UndoCommand::UndoCommand(e_undo uCommand, int row, const QByteArray& baDrop,
                                     IxDnDModel* model, QUndoCommand *parent/* = Q_NULLPTR*/)
    : QUndoCommand(parent), m_uCommand(uCommand), m_ix(model), m_nRow(row), m_baDrop(baDrop)
{ //save state
    qAssert(m_ix && !m_baDrop.isEmpty());
    setText(model->commandText(uCommand));
}

void IxDnDModel::UndoCommand::redo()
{
    if (!(m_ix && !m_baDrop.isEmpty())) return;
    switch (m_uCommand)
    {
    case uChangeRel:
    case uAddRel: {
        QDataStream in(&m_baDrop, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_4_5);
        qint64 nFrom; in >> nFrom;
        auto from = (IxDnDModel*) nFrom;
        int n, row; in >> n;
        QVector<int> vFromRows;
        for (int i = 0; i < n; ++i) { in >> row; vFromRows.append(row); }
        if (m_ix->getClass() == from->getClass()) {
            if (m_ix == from) return;
            emit m_ix->relationsAboutToBeUpdated();
            foreach (int i, vFromRows)
                m_ix->insertItemFrom(from, i,
                                 m_uCommand == uChangeRel && from->getParentModel()
                                 && m_ix->getParentModel());
            if (m_ix->m_pParent) m_ix->m_pParent->saveChildRelations(m_ix);
            return emit m_ix->relationsUpdated();
        }
        IxSqlRelation * rel = Q_NULLPTR; //figure out the relation
        if (m_ix->getClass()->getDataMemberX())
        {
            long lCount = m_ix->getClass()->getDataMemberX()->count();
            for (long l = 0; l < lCount; l++)
            {
                IxDataMember * p = m_ix->getClass()->getDataMemberX()->get(l);
                if (!p) { continue; }
                IxSqlRelation * pRelation = p->getSqlRelation();
                if (pRelation && pRelation->getClass() == from->getClass()) {
                    rel = pRelation;
                    break;
                }
            }
        }
        qAssert(rel); if (!rel) return;
        IxDnDModel* to = m_ix->m_lstChild.size() > m_nRow ?
             qobject_cast<IxDnDModel*>(m_ix->m_lstChild.at(m_nRow).value(rel->getKey())) :
                    Q_NULLPTR;
        if (!to) { //only create a child if it does not exist already
            QxClassX::type_any_params v(3, true);
            QString sRel;
            v[0] = m_nRow;
            v[2] = (const QString&)sRel;
            qx::any r;
            qx_bool bInvokeOk = QxClassX::invoke(m_ix->getModelClass()->getKey(),
                                                 rel->getKey(), m_ix, v, &r);
            qAssert(bInvokeOk);
            to = qobject_cast<IxDnDModel*>(qx::any_cast<QObject*>(r));
        }
        qAssert(to);
        std::sort(vFromRows.rbegin(), vFromRows.rend());
        emit m_ix->relationsAboutToBeUpdated();
        foreach (int i, vFromRows)
            to->insertItemFrom(from, i, m_uCommand == uChangeRel && from->getParentModel());
        m_ix->saveChildRelations(from);
        m_ix->saveChildRelations(to);
        emit m_ix->relationsUpdated();
    } break;
    default:
        break;
    }
}

QString IxDnDModel::commandText(e_undo uCommand)
{
    switch (uCommand)
    {
    case uChangeRel: return tr("Change");
    case uAddRel: return tr("Add");
    }
    return QString();
}

bool IxDnDModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                             int column, const QModelIndex &parent) const
{
   if (!getDragDropMode()) return false;
   if (!data->formats().last().startsWith(QLatin1String("application/IxDnDModel")) ||
           !mimeTypes().contains(data->formats().last())) return false;
   QByteArray ba = data->data(data->formats().last());
   QDataStream in(&ba, QIODevice::ReadOnly);
   in.setVersion(QDataStream::Qt_4_5);
   qint64 nFrom; in >> nFrom;
   auto from = (IxDnDModel*) nFrom;
   if (this == from) return false;
   //allow inwindow/not on item drops only for same class items
   if (m_pParent && getClass() == from->getClass())
       return from->getParentModel() || action != Qt::MoveAction;
   //do not allow drop from a child model, if dropping on its index in parent
    return getChildPosition(from).first != parent.row() &&
            (getParentModel() || from->getParentModel() || action != Qt::MoveAction) &&
            parent.isValid() && parent.row() < m_pCollection->_count() &&
          IxModel::canDropMimeData(data, action, row, column, parent);
}

bool IxDnDModel::dropMimeData(const QMimeData * data, Qt::DropAction action, int,
                          int, const QModelIndex & parent)
{
    if (action == Qt::IgnoreAction) return true;
    if (getDragDropMode()) {
        getUndo()->push(new UndoCommand(action == Qt::MoveAction ? uChangeRel : uAddRel,
                 parent.row(), data->data(data->formats().last()), this));
        return true;
    }
    return false;
}

QStringList IxDnDModel::mimeTypes() const
{
   QStringList types = IxModel::mimeTypes();
    if (getDragDropMode() && getClass()->getDataMemberX()) { //Only direct relations allowed
        long lCount = getClass()->getDataMemberX()->count();
        for (long l = 0; l < lCount; l++)
        {
            IxDataMember * p = getClass()->getDataMemberX()->get(l);
            if (!p) { continue; }
            if (p->getSqlRelation())
                types << "application/IxDnDModel" + p->getSqlRelation()->getClass()->getKey();
        }
        if (m_pParent) //can accept same items, if this has a parent (would be like dropping on the parent)
            types << "application/IxDnDModel" + getClass()->getKey();
    }
    return types;
}

QMimeData *IxDnDModel::mimeData(const QModelIndexList & indexes) const
{
    if (!getDragDropMode()) return Q_NULLPTR;
    auto data = IxModel::mimeData(indexes); //InternalMove will not work without this
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);
    out << (qint64) this;
    QVector<int> vFromRows; //remove possible duplicates, preserve order
    foreach(const QModelIndex& i, indexes)
        if (!vFromRows.contains(i.row()) && !isDirtyRow(i.row())) vFromRows << i.row();
    if (vFromRows.isEmpty()) return Q_NULLPTR;
    out << vFromRows.size();
    foreach(int i, vFromRows) out << i;
    data->setData("application/IxDnDModel" + getClass()->getKey(), ba);
    return data;
}

} // namespace qx
#endif //QT_WIDGETS_LIB
