/****************************************************************************
**
** https://www.qxorm.com/
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

#include <QxPrecompiled.h>

#include <QxModelView/IxModel.h>

#include <QxMemLeak/mem_leak.h>

#define QX_CONSTRUCT_IX_MODEL() \
m_pClass(NULL), m_pModelClass(NULL), m_pDataMemberX(NULL), m_pDataMemberId(NULL), m_pCollection(NULL), \
m_pParent(NULL), m_eAutoUpdateDatabase(IxModel::e_no_auto_update), m_pDataMemberRelationToParent(NULL), m_lManualInsertIndex(0)

namespace qx {

IxModel::IxModel(QObject * parent /* = 0 */) : QAbstractItemModel(parent), QX_CONSTRUCT_IX_MODEL() { ; }

IxModel::~IxModel() { ; }

IxClass * IxModel::getClass() const { return m_pClass; }

IxClass * IxModel::getModelClass() const { return m_pModelClass; }

IxCollection * IxModel::getCollection() const { return m_pCollection; }

QSqlDatabase IxModel::getDatabase() const { return m_database; }

QSqlError IxModel::getLastError() const { return m_lastError; }

QString IxModel::getLastErrorAsString() const { return (m_lastError.isValid() ? m_lastError.text() : QString()); }

QStringList IxModel::getListOfColumns() const { return m_lstColumns; }

int IxModel::getRowCount() const { return rowCount(); }

QHash<QString, QString> IxModel::getListOfHeaders() const
{
   QHash<QString, QString> lst;
   QHashIterator<QString, QVariant> itr(m_lstHeadersData);
   QString sStart = (QString::number(Qt::DisplayRole) + "|");
   while (itr.hasNext()) { itr.next(); if (itr.key().startsWith(sStart)) { QString sKey = itr.key(); sKey.replace(sStart, ""); lst.insert(sKey, itr.value().toString()); } }
   return lst;
}

IxDataMember * IxModel::getDataMember(int column) const { return (((column < 0) || (column >= m_lstDataMember.count())) ? NULL : m_lstDataMember.at(column)); }

QString IxModel::getDataMemberKey(int column) const { IxDataMember * p = getDataMember(column); return (p ? p->getKey() : QString()); }

QVariant IxModel::getModelValue(int row, const QString & column) const
{
   if (! m_lstDataMemberByKey.contains(column)) { return QVariant(); }
   int iColumnIndex = m_lstDataMemberByKey.value(column);
   QModelIndex idx = index(row, iColumnIndex, QModelIndex());
   return data(idx, Qt::DisplayRole);
}

int IxModel::getColumnIndex(const QString & sColumnName) const
{
   if (! m_lstDataMemberByKey.contains(sColumnName)) { qAssert(false); return -1; }
   return m_lstDataMemberByKey.value(sColumnName);
}

int IxModel::getAutoUpdateDatabase_() const { return static_cast<int>(m_eAutoUpdateDatabase); }

IxModel::e_auto_update_database IxModel::getAutoUpdateDatabase() const { return m_eAutoUpdateDatabase; }

QVariant IxModel::getCustomProperty(const QString & key) const { return (m_hCustomProperties.contains(key) ? m_hCustomProperties.value(key) : QVariant()); }

QObject * IxModel::getParentModel() const { return static_cast<QObject *>(m_pParent); }

void IxModel::dumpModel(bool bJsonFormat /* = true */) const { dumpModelImpl(bJsonFormat); }

QObject * IxModel::cloneModel() { return cloneModelImpl(); }

void IxModel::setDatabase(const QSqlDatabase & db) { m_database = db; }

void IxModel::setListOfColumns(const QStringList & lst) { m_lstColumns = lst; clear(true); }

void IxModel::setListOfHeaders(const QHash<QString, QString> & lst)
{
   QHashIterator<QString, QString> itr(lst);
   while (itr.hasNext())
   {
      itr.next();
      QString sHeaderDataKey = (QString::number(Qt::DisplayRole) + "|" + itr.key());
      QVariant vHeaderDataValue = QVariant(itr.value());
      m_lstHeadersData.insert(sHeaderDataKey, vHeaderDataValue);
   }
   Q_EMIT headerDataChanged(Qt::Horizontal, 0, (m_lstDataMember.count() - 1));
}

bool IxModel::setModelValue(int row, const QString & column, const QVariant & value)
{
   if (! m_lstDataMemberByKey.contains(column)) { return false; }
   int iColumnIndex = m_lstDataMemberByKey.value(column);
   QModelIndex idx = index(row, iColumnIndex, QModelIndex());
   return setData(idx, value, Qt::EditRole);
}

void IxModel::setParentModel(IxModel * pParent)
{
   m_pParent = pParent;
   m_pDataMemberRelationToParent = NULL;
   if (! pParent || ! m_pDataMemberX) { return; }
   long lCount = m_pDataMemberX->count_WithDaoStrategy();
   for (long l = 0; l < lCount; l++)
   {
      IxDataMember * p = m_pDataMemberX->get_WithDaoStrategy(l); if (! p) { continue; }
      IxSqlRelation * pRelation = p->getSqlRelation(); if (! pRelation) { continue; }
      pRelation->init();
      if (pRelation->getDataId() == pParent->m_pDataMemberId)
      { m_pDataMemberRelationToParent = p; break; }
   }
}

void IxModel::setAutoUpdateDatabase_(int i) { m_eAutoUpdateDatabase = static_cast<IxModel::e_auto_update_database>(i); }

void IxModel::setAutoUpdateDatabase(IxModel::e_auto_update_database e) { m_eAutoUpdateDatabase = e; }

void IxModel::setCustomProperty(const QString & key, const QVariant & val) { m_hCustomProperties.insert(key, val); }

int IxModel::qxCount_(const QString & sQuery) { qx_query query(sQuery); return static_cast<int>(qxCount(query, database(NULL))); }

bool IxModel::qxFetchById_(const QVariant & id, const QStringList & relation /* = QStringList() */) { return (! qxFetchById(id, relation, database(NULL)).isValid()); }

bool IxModel::qxFetchAll_(const QStringList & relation /* = QStringList() */) { return (! qxFetchAll(relation, database(NULL)).isValid()); }

bool IxModel::qxFetchByQuery_(const QString & sQuery, const QStringList & relation /* = QStringList() */) { qx_query query(sQuery); return (! qxFetchByQuery(query, relation, database(NULL)).isValid()); }

bool IxModel::qxFetchRow_(int row, const QStringList & relation /* = QStringList() */) { return (! qxFetchRow(row, relation, database(NULL)).isValid()); }

bool IxModel::qxInsert_(const QStringList & relation /* = QStringList() */, bool bUseExecBatch /* = false */) { return (! qxInsert(relation, database(NULL), bUseExecBatch).isValid()); }

bool IxModel::qxInsertRow_(int row, const QStringList & relation /* = QStringList() */) { return (! qxInsertRow(row, relation, database(NULL)).isValid()); }

bool IxModel::qxUpdate_(const QString & sQuery, const QStringList & relation /* = QStringList() */, bool bUseExecBatch /* = false */) { qx_query query(sQuery); return (! qxUpdate(query, relation, database(NULL), bUseExecBatch).isValid()); }

bool IxModel::qxUpdateRow_(int row, const QString & sQuery, const QStringList & relation /* = QStringList() */) { qx_query query(sQuery); return (! qxUpdateRow(row, query, relation, database(NULL)).isValid()); }

bool IxModel::qxSave_(const QStringList & relation /* = QStringList() */) { return (! qxSave(relation, database(NULL)).isValid()); }

bool IxModel::qxSaveRow_(int row, const QStringList & relation /* = QStringList() */) { return (! qxSaveRow(row, relation, database(NULL)).isValid()); }

bool IxModel::qxDeleteById_(const QVariant & id) { return (! qxDeleteById(id, database(NULL)).isValid()); }

bool IxModel::qxDeleteAll_() { return (! qxDeleteAll(database(NULL)).isValid()); }

bool IxModel::qxDeleteByQuery_(const QString & sQuery) { qx_query query(sQuery); return (! qxDeleteByQuery(query, database(NULL)).isValid()); }

bool IxModel::qxDeleteRow_(int row) { return (! qxDeleteRow(row, database(NULL)).isValid()); }

bool IxModel::qxDestroyById_(const QVariant & id) { return (! qxDestroyById(id, database(NULL)).isValid()); }

bool IxModel::qxDestroyAll_() { return (! qxDestroyAll(database(NULL)).isValid()); }

bool IxModel::qxDestroyByQuery_(const QString & sQuery) { qx_query query(sQuery); return (! qxDestroyByQuery(query, database(NULL)).isValid()); }

bool IxModel::qxDestroyRow_(int row) { return (! qxDestroyRow(row, database(NULL)).isValid()); }

bool IxModel::qxExecuteQuery_(const QString & sQuery) { qx_query query(sQuery); return (! qxExecuteQuery(query, database(NULL)).isValid()); }

bool IxModel::qxExist_(const QVariant & id) { return qxExist(id, database(NULL)).getValue(); }

QString IxModel::qxValidate_(const QStringList & groups /* = QStringList() */) { qx::QxInvalidValueX invalidValueX = qxValidate(groups); return (invalidValueX ? QString() : invalidValueX.text()); }

QString IxModel::qxValidateRow_(int row, const QStringList & groups /* = QStringList() */) { qx::QxInvalidValueX invalidValueX = qxValidateRow(row, groups); return (invalidValueX ? QString() : invalidValueX.text()); }

void IxModel::raiseEvent_headerDataChanged(Qt::Orientation orientation, int first, int last) { Q_EMIT headerDataChanged(orientation, first, last); }

#if (QT_VERSION >= 0x050000)

void IxModel::raiseEvent_dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight, const QVector<int> & roles /* = QVector<int>() */) { Q_EMIT dataChanged(topLeft, bottomRight, roles); }

void IxModel::raiseEvent_layoutAboutToBeChanged(const QList<QPersistentModelIndex> & parents /* = QList<QPersistentModelIndex>() */, QAbstractItemModel::LayoutChangeHint hint /* = QAbstractItemModel::NoLayoutChangeHint */) { Q_EMIT layoutAboutToBeChanged(parents, hint); }

void IxModel::raiseEvent_layoutChanged(const QList<QPersistentModelIndex> & parents /* = QList<QPersistentModelIndex>() */, QAbstractItemModel::LayoutChangeHint hint /* = QAbstractItemModel::NoLayoutChangeHint */) { Q_EMIT layoutChanged(parents, hint); }

#else // (QT_VERSION >= 0x050000)

void IxModel::raiseEvent_dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight) { Q_EMIT dataChanged(topLeft, bottomRight); }

void IxModel::raiseEvent_layoutAboutToBeChanged() { Q_EMIT layoutAboutToBeChanged(); }

void IxModel::raiseEvent_layoutChanged() { Q_EMIT layoutChanged(); }

#endif // (QT_VERSION >= 0x050000)

void IxModel::clear(bool bUpdateColumns /* = false */)
{
   if (! m_pCollection) { qAssert(false); return; }
   if (! bUpdateColumns && (m_pCollection->_count() <= 0)) { return; }
   beginResetModel();
   m_pCollection->_clear();
   for (long l = (m_lstChild.count() - 1); l >= 0; l--)
   { removeListOfChild(l); }
   m_lstChild.clear();
   m_hChild.clear();
   if (bUpdateColumns) { generateRoleNames(); }
   endResetModel();

   if (getShowEmptyLine())
   {
      setShowEmptyLine(false);
      setShowEmptyLine(true);
   }
}

IxModel * IxModel::getChild(long row, const QString & relation)
{
   if ((row < 0) || (row >= m_lstChild.count())) { return NULL; }
   IxModel::type_relation_by_name child = m_lstChild.at(row);
   if (! child.contains(relation)) { return NULL; }
   return child.value(relation);
}

void IxModel::insertChild(long row, const QString & relation, IxModel * pChild)
{
   if ((row < 0) || (! pChild)) { return; }
   if (relation.isEmpty()) { return; }
   while (row > (m_lstChild.count() - 1))
   { IxModel::type_relation_by_name tmp; m_lstChild.append(tmp); }
   m_lstChild[row].insert(relation, pChild);
   QPair<int, QString> pairRowRelation(static_cast<int>(row), relation);
   m_hChild.insert(pChild, pairRowRelation);
}

void IxModel::removeListOfChild(long row)
{
   if ((row < 0) || (row >= m_lstChild.count())) { return; }
   IxModel::type_relation_by_name lst = m_lstChild.at(row);
   Q_FOREACH(IxModel * p, lst) { if (p) { m_hChild.remove(p); delete p; } }
   m_lstChild.removeAt(row);
}

QSqlError IxModel::saveChildRelations(IxModel * pChild)
{
   if (! m_hChild.contains(pChild)) { return QSqlError(); }
   QPair<int, QString> pairRowRelation = m_hChild.value(pChild);
   return qxSaveRow(pairRowRelation.first, (QStringList() << pairRowRelation.second));
}

QVariant IxModel::getIdFromChild(IxModel * pChild) const
{
   if (! m_hChild.contains(pChild)) { return QVariant(); }
   if (! m_pCollection || ! m_pDataMemberId) { qAssert(false); return QVariant(); }
   int row = m_hChild.value(pChild).first;
   if ((row < 0) || (row >= m_pCollection->_count())) { return QVariant(); }
   void * pItem = getRowItemAsVoidPtr(row);
   return (pItem ? m_pDataMemberId->toVariant(pItem) : QVariant());
}

QPair<int, QString> IxModel::getChildPosition(IxModel * pChild) const
{
   if (! m_hChild.contains(pChild)) { return QPair<int, QString>(-1, ""); }
   return m_hChild.value(pChild);
}

QVariant IxModel::data(const QModelIndex & index, int role /* = Qt::DisplayRole */) const
{
   if (! index.isValid()) { return QVariant(); }
   if ((role == Qt::DisplayRole) || (role == Qt::EditRole))
   {
      if ((index.column() < 0) || (index.column() >= m_lstDataMember.count())) { return QVariant(); }
      else if ((index.row() < 0) || (index.row() >= rowCount())) { return QVariant(); }
      IxDataMember * pDataMember = m_lstDataMember.at(index.column());
      void * pItem = getRowItemAsVoidPtr(index.row());
      if (! pDataMember || ! pItem) { return QVariant(); }
      return pDataMember->toVariant(pItem);
   }
   else if (role >= (Qt::UserRole + 1))
   {
      QModelIndex idx = this->index(index.row(), (role - Qt::UserRole - 1), QModelIndex());
      return data(idx, Qt::DisplayRole);
   }
   return QVariant();
}

bool IxModel::setData(const QModelIndex & index, const QVariant & value, int role /* = Qt::EditRole */)
{
   if (! index.isValid()) { return false; }
   if (role == Qt::EditRole)
   {
      if ((index.column() < 0) || (index.column() >= m_lstDataMember.count())) { return false; }
      else if ((index.row() < 0) || (index.row() >= rowCount())) { return false; }
      IxDataMember * pDataMember = m_lstDataMember.at(index.column());
      bool bDirtyRow = isDirtyRow(index.row());
      void * pItem = getRowItemAsVoidPtr(index.row());
      if (! pDataMember || ! pItem) { return false; }
      QVariant vCurrentValue = pDataMember->toVariant(pItem);
      if (vCurrentValue == value) { return true; }
      qx_bool bSetData = pDataMember->fromVariant(pItem, value);
      if (bSetData && (m_eAutoUpdateDatabase == qx::IxModel::e_auto_update_on_field_change))
      {
         qxSaveRowData(index.row(), (QStringList() << pDataMember->getKey()));
         if (! m_lastError.isValid() && bDirtyRow) { insertDirtyRowToModel(); }
         if (m_lastError.isValid())
         {
            if (! bDirtyRow)
            {
               qDebug("[QxOrm] qx::IxModel::setData() : %s", "an error occurred saving value in database (more details with 'getLastError()' method), so previous value has been restored");
               pDataMember->fromVariant(pItem, vCurrentValue);
               return false;
            }
         }
         else if (pDataMember->hasSqlRelation())
         { qxFetchRow(index.row(), (QStringList() << pDataMember->getSqlRelation()->getKey())); }
      }
      if (bSetData) { raiseEvent_dataChanged(index, index); }
      return bSetData;
   }
   else if (role >= (Qt::UserRole + 1))
   {
      QModelIndex idx = this->index(index.row(), (role - Qt::UserRole - 1), QModelIndex());
      return setData(idx, value, Qt::EditRole);
   }
   return false;
}

int IxModel::rowCount(const QModelIndex & parent /* = QModelIndex() */) const
{
   if (parent.isValid() || ! m_pCollection) { return 0; }
   return (static_cast<int>(m_pCollection->_count()) + (getShowEmptyLine() ? 1 : 0));
}

int IxModel::columnCount(const QModelIndex & parent /* = QModelIndex() */) const
{
   if (parent.isValid()) { return 0; }
   qAssert(m_lstRoleNames.count() == m_lstDataMember.count());
   return static_cast<int>(m_lstRoleNames.count());
}

QModelIndex IxModel::index(int row, int column, const QModelIndex & parent /* = QModelIndex() */) const
{
   if (! hasIndex(row, column, parent)) { return QModelIndex(); }
   if ((column < 0) || (column >= m_lstDataMember.count())) { return QModelIndex(); }
   IxDataMember * pDataMember = m_lstDataMember.at(column);
   if (pDataMember) { return createIndex(row, column, static_cast<void *>(pDataMember)); }
   else { return QModelIndex(); }
}

QModelIndex IxModel::parent(const QModelIndex & index) const
{
   Q_UNUSED(index);
   return QModelIndex();
}

bool IxModel::hasChildren(const QModelIndex & parent /* = QModelIndex() */) const
{
   Q_UNUSED(parent);
   return false;
}

QVariant IxModel::headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const
{
   if (role == Qt::TextAlignmentRole) { return Qt::AlignCenter; }
   if ((orientation == Qt::Vertical) && (role == Qt::DisplayRole) && (isDirtyRow(section))) { return QVariant(QString("*")); }
   if (orientation != Qt::Horizontal) { return QAbstractItemModel::headerData(section, orientation, role); }
   if ((section < 0) || (section >= m_lstDataMember.count()))
   { return QAbstractItemModel::headerData(section, orientation, role); }
   IxDataMember * pDataMember = m_lstDataMember.at(section);
   if (! pDataMember) { return QAbstractItemModel::headerData(section, orientation, role); }
   QString sHeaderDataKey = (QString::number(role) + "|" + pDataMember->getKey());
   if (m_lstHeadersData.contains(sHeaderDataKey)) { return m_lstHeadersData.value(sHeaderDataKey); }
   if ((role == Qt::DisplayRole) || (role == Qt::EditRole))
   {
      if (! pDataMember->getDescription().isEmpty()) { return pDataMember->getDescription(); }
      return pDataMember->getKey();
   }
   return QVariant();
}

Qt::ItemFlags IxModel::flags(const QModelIndex & index) const
{
   if (! index.isValid()) { return Qt::ItemIsEnabled; }
   return (Qt::ItemIsEditable | QAbstractItemModel::flags(index));
}

#if (QT_VERSION >= 0x050000)
QHash<int, QByteArray> IxModel::roleNames() const
{
   return m_lstRoleNames;
}
#endif // (QT_VERSION >= 0x050000)

#if (QT_VERSION >= 0x050000)
Qt::DropActions IxModel::supportedDragActions() const
{
   return QAbstractItemModel::supportedDragActions();
}
#endif // (QT_VERSION >= 0x050000)

Qt::DropActions IxModel::supportedDropActions() const
{
   return QAbstractItemModel::supportedDropActions();
}

bool IxModel::removeRows(int row, int count, const QModelIndex & parent /* = QModelIndex() */)
{
   if (parent.isValid()) { return false; }
   if (m_eAutoUpdateDatabase == IxModel::e_auto_update_on_field_change) { return removeRowsAutoUpdateOnFieldChange(row, count); }
   return removeRowsGeneric(row, count);
}

bool IxModel::removeRowsGeneric(int row, int count)
{
   if (! m_pCollection) { qAssert(false); return false; }
   beginRemoveRows(QModelIndex(), row, (row + count - 1));
   for (int i = 0; i < count; ++i)
   { m_pCollection->_remove(row); removeListOfChild(row); }
   updateShowEmptyLine();
   endRemoveRows();
   return true;
}

bool IxModel::removeRowsAutoUpdateOnFieldChange(int row, int count)
{
   if (! m_pCollection) { qAssert(false); return false; }
   for (int i = 0; i < count; ++i)
   {
      if ((row >= 0) && (row < m_pCollection->_count()))
      {
         if (qxDeleteRow_(row)) { removeRowsGeneric(row, 1); }
         else { qDebug("[QxOrm] qx::IxModel::removeRowsAutoUpdateOnFieldChange() : %s", "an error occurred deleting row from database (more details with 'getLastError()' method), so row is not removed from model"); return false; }
      }
      else if (isDirtyRow(row)) { setShowEmptyLine(false); setShowEmptyLine(true); }
      else { return true; }
   }
   return true;
}

bool IxModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant & value, int role /* = Qt::EditRole */)
{
   if (orientation != Qt::Horizontal) { return QAbstractItemModel::setHeaderData(section, orientation, value, role); }
   if ((section < 0) || (section >= m_lstDataMember.count())) { return false; }
   IxDataMember * pDataMember = m_lstDataMember.at(section); if (! pDataMember) { return false; }

   if ((role == Qt::EditRole) || (role == Qt::DisplayRole))
   {
      QString sHeaderDataKey = (QString::number(Qt::EditRole) + "|" + pDataMember->getKey());
      m_lstHeadersData.insert(sHeaderDataKey, value);
      sHeaderDataKey = (QString::number(Qt::DisplayRole) + "|" + pDataMember->getKey());
      m_lstHeadersData.insert(sHeaderDataKey, value);
   }
   else
   {
      QString sHeaderDataKey = (QString::number(role) + "|" + pDataMember->getKey());
      m_lstHeadersData.insert(sHeaderDataKey, value);
   }

   Q_EMIT headerDataChanged(orientation, section, section);
   return true;
}

bool IxModel::setHeaderData(const QString & sColumnName, const QVariant & value, int role /* = Qt::EditRole */)
{
   int section = getColumnIndex(sColumnName);
   return ((section == -1) ? false : setHeaderData(section, Qt::Horizontal, value, role));
}

void IxModel::syncNestedModel(int row, const QStringList & relation) { Q_UNUSED(row); Q_UNUSED(relation); }

void IxModel::syncAllNestedModel(const QStringList & relation) { Q_UNUSED(relation); }

void IxModel::syncNestedModelRecursive(IxModel * pNestedModel, const QStringList & relation) { if (pNestedModel) { pNestedModel->syncAllNestedModel(relation); } }

void IxModel::generateRoleNames()
{
   int iRoleCount = 0;
   m_lstRoleNames.clear();
   m_lstDataMember.clear();
   m_lstDataMemberByKey.clear();

   for (long l = 0; l < (m_pDataMemberX ? m_pDataMemberX->count_WithDaoStrategy() : 0); ++l)
   {
      IxDataMember * pDataMember = m_pDataMemberX->get_WithDaoStrategy(l); if (! pDataMember) { continue; }
      IxSqlRelation * pRelation = (pDataMember->hasSqlRelation() ? pDataMember->getSqlRelation() : NULL);
      IxSqlRelation::relation_type eRelationType = (pRelation ? pRelation->getRelationType() : IxSqlRelation::no_relation);
      if (pRelation && ((eRelationType == IxSqlRelation::one_to_many) || (eRelationType == IxSqlRelation::many_to_many))) { continue; }
      if ((m_lstColumns.count() > 0) && (! m_lstColumns.contains(pDataMember->getKey()))) { continue; }
      m_lstRoleNames.insert(static_cast<int>(Qt::UserRole + 1 + iRoleCount), pDataMember->getKey().toLatin1());
      m_lstDataMemberByKey.insert(pDataMember->getKey(), static_cast<int>(m_lstDataMember.count()));
      m_lstDataMember.append(pDataMember);
      iRoleCount++;
   }

#if (QT_VERSION < 0x050000)
   setRoleNames(m_lstRoleNames);
#endif // (QT_VERSION < 0x050000)
}

QSqlDatabase * IxModel::database(QSqlDatabase * other)
{
   return (other ? other : (m_database.isValid() ? (& m_database) : NULL));
}

#ifndef _QX_NO_JSON

QString IxModel::toJson(int row /* = -1 */) const { return toJson_Helper(row); }

bool IxModel::fromJson(const QString & json, int row /* = -1 */) { return fromJson_Helper(json, row); }

QVariant IxModel::getRelationshipValues(int row, const QString & relation, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */) { return getRelationshipValues_Helper(row, relation, bLoadFromDatabase, sAppendRelations); }

bool IxModel::setRelationshipValues(int row, const QString & relation, const QVariant & values) { return setRelationshipValues_Helper(row, relation, values); }

#else // _QX_NO_JSON

QString IxModel::toJson(int row /* = -1 */) const { qDebug("[QxOrm] qx::IxModel::toJson() : %s", "not implemented when _QX_NO_JSON compilation option is defined"); Q_UNUSED(row); return QString(); }

bool IxModel::fromJson(const QString & json, int row /* = -1 */) { qDebug("[QxOrm] qx::IxModel::fromJson() : %s", "not implemented when _QX_NO_JSON compilation option is defined"); Q_UNUSED(json); Q_UNUSED(row); return false; }

QVariant IxModel::getRelationshipValues(int row, const QString & relation, bool bLoadFromDatabase /* = false */, const QString & sAppendRelations /* = QString() */) { qDebug("[QxOrm] qx::IxModel::getRelationshipValues() : %s", "not implemented when _QX_NO_JSON compilation option is defined"); Q_UNUSED(row); Q_UNUSED(relation); Q_UNUSED(bLoadFromDatabase); Q_UNUSED(sAppendRelations); return QVariant(); }

bool IxModel::setRelationshipValues(int row, const QString & relation, const QVariant & values) { qDebug("[QxOrm] qx::IxModel::setRelationshipValues() : %s", "not implemented when _QX_NO_JSON compilation option is defined"); Q_UNUSED(row); Q_UNUSED(relation); Q_UNUSED(values); return false; }

#endif // _QX_NO_JSON

} // namespace qx
