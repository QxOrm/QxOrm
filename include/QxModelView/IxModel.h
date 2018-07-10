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

#ifndef _IX_MODEL_H_
#define _IX_MODEL_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxModel.h
 * \author Lionel Marty
 * \ingroup QxModelView
 * \brief Interface to manage Qt model/view architecture with classes registered into QxOrm context (Qt widgets and/or QML views)
 */

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include <QxPrecompiled.h> // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include <QtCore/qabstractitemmodel.h>

#ifndef Q_MOC_RUN
#include <QxRegister/IxClass.h>
#include <QxDataMember/IxDataMemberX.h>
#include <QxCollection/QxCollection.h>
#include <QxDao/IxSqlRelation.h>
#include <QxDao/QxSqlQuery.h>
#include <QxDao/QxDao.h>
#include <QxValidator/QxInvalidValueX.h>
#include <QxValidator/QxValidatorFct.h>
#endif // Q_MOC_RUN

namespace qx {

/*!
 * \ingroup QxModelView
 * \brief qx::IxModel : interface to manage Qt model/view architecture with classes registered into QxOrm context (Qt widgets and/or QML views)
 *
 * <b>QxModelView</b> module provides an easy way to work with Qt model/view engine with all classes registered into QxOrm context :
 * - Qt widgets : QTableView or QListView for example to display/modify a database table content ;
 * - QML : each property defined in QxOrm context is exposed to QML engine : QxModelView module makes easier integration between QML and databases.
 *
 * qx::IxModel interface provides a generic way for all models linked to persistents classes registered into QxOrm context. All methods of this class prefixed by <i>qx</i> call functions from qx::dao namespace and then communicate with database.
 *
 * The <i>qxBlogModelView</i> sample project in <i>./test/</i> directory of QxOrm package shows how to create quickly a model and associate it to the Qt model/view engine (first with a Qt widget, then with a QML view).
 *
 * 1- Here is an example to display/modify data from 'author' table (go to qxBlog tutorial for 'author' class definition) in a QTableView :
 * \code
// Create a model and fetch all data from database
qx::IxModel * pModel = new qx::QxModel<author>();
pModel->qxFetchAll();

// Associate the model to a QTableView and display it
QTableView tableView;
tableView.setModel(pModel);
tableView.show();
 * \endcode
 *
 * 2- Here is another example in QML (with Qt5, QxModelView module works fine with Qt4 too) :
 * \code
// Create a model and fetch all data from database
qx::IxModel * pModel = new qx::QxModel<author>();
pModel->qxFetchAll();

// Associate the model to a QML view and display it
QQuickView qmlView;
qmlView.rootContext()->setContextProperty("myModel", pModel);
qmlView.setSource(QUrl("qrc:/documents/main.qml"));
qmlView.show();
 * \endcode
 *
 * And here is the 'main.qml' file content :
 * \code
import QtQuick 2.1
import QtQuick.Controls 1.0

Item {
   width: 400
   height: 300
   Row {
      height: 20
      spacing: 20
      Button {
         text: "Clear"
         onClicked: myModel.clear()
      }
      Button {
         text: "Fetch All"
         onClicked: myModel.qxFetchAll_()
      }
      Button {
         text: "Save"
         onClicked: myModel.qxSave_()
      }
   }
   ListView {
      y: 30
      height: 270
      model: myModel
      delegate: Row {
         height: 20
         spacing: 10
         Text { text: "id: " + author_id }
         TextField {
            text: name
            onTextChanged: name = text
         }
      }
   }
}
 * \endcode
 *
 * As you can see in the 'main.qml' file, 'author_id' and 'name' properties of 'author' model ('myModel' variable) can be automatically read and write (because they are registered into QxOrm context).
 * Moreover, qx::IxModel interface provides a list of methods for QML side (Q_INVOKABLE) to communicate with database : for example, the 'Save' button will save the model in database without having to write a C++ function.
 *
 * <b>Note :</b> a <b>QxEntityEditor</b> plugin generates automatically the code to manage models with relationships. Then it is possible to work with nested C++ models.
 */
class QX_DLL_EXPORT IxModel : public QAbstractItemModel
{

   Q_OBJECT

public:

   enum e_auto_update_database { e_no_auto_update, e_auto_update_on_field_change };

   typedef QHash<QString, IxModel *> type_relation_by_name;
   typedef QList<type_relation_by_name> type_lst_relation_by_name;

protected:

   IxClass * m_pClass;                             //!< Class introspection registered into QxOrm context associated to the model
   IxDataMemberX * m_pDataMemberX;                 //!< List of properties defined into QxOrm context
   IxDataMember * m_pDataMemberId;                 //!< Primary key (property id) defined into QxOrm context
   IxCollection * m_pCollection;                   //!< Interface to store a list of items
   QHash<int, QByteArray> m_lstRoleNames;          //!< List of model's role names to expose data to QML
   QList<IxDataMember *> m_lstDataMember;          //!< List of data member exposed by the model
   QHash<QString, int> m_lstDataMemberByKey;       //!< List of data member key to get column index in model
   QHash<QString, QVariant> m_lstHeadersData;      //!< List of headers data by role and data member key
   QStringList m_lstColumns;                       //!< List of columns exposed by the model (if empty, all columns)
   QSqlDatabase m_database;                        //!< Database connexion to execute SQL queries (if empty, default database connexion)
   QSqlError m_lastError;                          //!< Last SQL error
   IxModel * m_pParent;                            //!< Parent model, NULL if current model is the root model
   type_lst_relation_by_name m_lstChild;           //!< List of child model : QxEntityEditor uses this property to manage relationships and create complex data structure
   e_auto_update_database m_eAutoUpdateDatabase;   //!< Auto-update database on field change (detected by the setData() method)

public:

   IxModel(QObject * parent = 0);
   virtual ~IxModel();

   IxClass * getClass() const;
   IxCollection * getCollection() const;
   QSqlDatabase getDatabase() const;
   QSqlError getLastError() const;
   Q_INVOKABLE QString getLastErrorAsString() const;
   Q_INVOKABLE QStringList getListOfColumns() const;
   QHash<QString, QString> getListOfHeaders() const; //!< Obsolete : use headerData() instead
   IxDataMember * getDataMember(int column) const;
   Q_INVOKABLE QString getDataMemberKey(int column) const;
   Q_INVOKABLE int getRowCount() const;
   Q_INVOKABLE QVariant getModelValue(int row, const QString & column) const;
   Q_INVOKABLE int getColumnIndex(const QString & sColumnName) const;
   Q_INVOKABLE int getAutoUpdateDatabase_() const;
   e_auto_update_database getAutoUpdateDatabase() const;
   Q_INVOKABLE void dumpModel(bool bJsonFormat = true) const;
   Q_INVOKABLE QObject * cloneModel();

   void setDatabase(const QSqlDatabase & db);
   Q_INVOKABLE void setListOfColumns(const QStringList & lst);
   void setListOfHeaders(const QHash<QString, QString> & lst); //!< Obsolete : use setHeaderData() instead
   Q_INVOKABLE bool setModelValue(int row, const QString & column, const QVariant & value);
   void setParentModel(IxModel * pParent);
   Q_INVOKABLE void setAutoUpdateDatabase_(int i);
   void setAutoUpdateDatabase(e_auto_update_database e);

   Q_INVOKABLE QString toJson(int row = -1) const;                   //!< On QML side, use JSON.parse() to create a javascript object after calling this qx::IxModel::toJson() method
   Q_INVOKABLE bool fromJson(const QString & json, int row = -1);    //!< On QML side, use JSON.stringify() on a javascript object before calling this qx::IxModel::fromJson() method

   Q_INVOKABLE QVariant getRelationshipValues(int row, const QString & relation, bool bLoadFromDatabase = false, const QString & sAppendRelations = QString()); //!< Depending on relationship type (1-1, 1-n, n-1, n-n) : can return a QVariantMap type or a QVariantList type
   Q_INVOKABLE bool setRelationshipValues(int row, const QString & relation, const QVariant & values); //!< Depending on relationship type (1-1, 1-n, n-1, n-n) : values parameter can be a QVariantMap type or a QVariantList type

   virtual long qxCount(const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxCount(long & lCount, const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxFetchById(const QVariant & id, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxFetchAll(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxFetchByQuery(const qx::QxSqlQuery & query, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxFetchRow(int row, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxInsert(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxInsertRow(int row, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxUpdate(const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxUpdateRow(int row, const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxSave(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxSaveRow(int row, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxDeleteById(const QVariant & id, QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxDeleteAll(QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxDeleteByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxDeleteRow(int row, QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxDestroyById(const QVariant & id, QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxDestroyAll(QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxDestroyByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxDestroyRow(int row, QSqlDatabase * pDatabase = NULL) = 0;
   virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL) = 0;
   virtual qx_bool qxExist(const QVariant & id, QSqlDatabase * pDatabase = NULL) = 0;
   virtual qx::QxInvalidValueX qxValidate(const QStringList & groups = QStringList()) = 0;
   virtual qx::QxInvalidValueX qxValidateRow(int row, const QStringList & groups = QStringList()) = 0;

   Q_INVOKABLE int qxCount_(const QString & sQuery);
   Q_INVOKABLE bool qxFetchById_(const QVariant & id, const QStringList & relation = QStringList());
   Q_INVOKABLE bool qxFetchAll_(const QStringList & relation = QStringList());
   Q_INVOKABLE bool qxFetchByQuery_(const QString & sQuery, const QStringList & relation = QStringList());
   Q_INVOKABLE bool qxFetchRow_(int row, const QStringList & relation = QStringList());
   Q_INVOKABLE bool qxInsert_(const QStringList & relation = QStringList());
   Q_INVOKABLE bool qxInsertRow_(int row, const QStringList & relation = QStringList());
   Q_INVOKABLE bool qxUpdate_(const QString & sQuery, const QStringList & relation = QStringList());
   Q_INVOKABLE bool qxUpdateRow_(int row, const QString & sQuery, const QStringList & relation = QStringList());
   Q_INVOKABLE bool qxSave_(const QStringList & relation = QStringList());
   Q_INVOKABLE bool qxSaveRow_(int row, const QStringList & relation = QStringList());
   Q_INVOKABLE bool qxDeleteById_(const QVariant & id);
   Q_INVOKABLE bool qxDeleteAll_();
   Q_INVOKABLE bool qxDeleteByQuery_(const QString & sQuery);
   Q_INVOKABLE bool qxDeleteRow_(int row);
   Q_INVOKABLE bool qxDestroyById_(const QVariant & id);
   Q_INVOKABLE bool qxDestroyAll_();
   Q_INVOKABLE bool qxDestroyByQuery_(const QString & sQuery);
   Q_INVOKABLE bool qxDestroyRow_(int row);
   Q_INVOKABLE bool qxExecuteQuery_(const QString & sQuery);
   Q_INVOKABLE bool qxExist_(const QVariant & id);
   Q_INVOKABLE QString qxValidate_(const QStringList & groups = QStringList());
   Q_INVOKABLE QString qxValidateRow_(int row, const QStringList & groups = QStringList());

protected:

   void raiseEvent_headerDataChanged(Qt::Orientation orientation, int first, int last);
#if (QT_VERSION >= 0x050000)
   void raiseEvent_dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight, const QVector<int> & roles = QVector<int>());
   void raiseEvent_layoutAboutToBeChanged(const QList<QPersistentModelIndex> & parents = QList<QPersistentModelIndex>(), QAbstractItemModel::LayoutChangeHint hint = QAbstractItemModel::NoLayoutChangeHint);
   void raiseEvent_layoutChanged(const QList<QPersistentModelIndex> & parents = QList<QPersistentModelIndex>(), QAbstractItemModel::LayoutChangeHint hint = QAbstractItemModel::NoLayoutChangeHint);
#else // (QT_VERSION >= 0x050000)
   void raiseEvent_dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight);
   void raiseEvent_layoutAboutToBeChanged();
   void raiseEvent_layoutChanged();
#endif // (QT_VERSION >= 0x050000)

public:

   Q_INVOKABLE void clear(bool bUpdateColumns = false);

   virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
   virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
   virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
   virtual QModelIndex parent(const QModelIndex & index) const;
   virtual bool hasChildren(const QModelIndex & parent = QModelIndex()) const;
   virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
   virtual Qt::ItemFlags flags(const QModelIndex & index) const;
   virtual Qt::DropActions supportedDropActions() const;
   virtual bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
   virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole);
   bool setHeaderData(const QString & sColumnName, const QVariant & value, int role = Qt::EditRole);

#if (QT_VERSION >= 0x050000)
   virtual QHash<int, QByteArray> roleNames() const;
   virtual Qt::DropActions supportedDragActions() const;
#endif // (QT_VERSION >= 0x050000)

protected:

   virtual QObject * cloneModelImpl() = 0;
   virtual void dumpModelImpl(bool bJsonFormat) const = 0;
   virtual void syncNestedModel(int row, const QStringList & relation);
   virtual void syncAllNestedModel(const QStringList & relation);
   void syncNestedModelRecursive(IxModel * pNestedModel, const QStringList & relation);

   void generateRoleNames();
   QSqlDatabase * database(QSqlDatabase * other);
   IxModel * getChild(long row, const QString & relation);
   void insertChild(long row, const QString & relation, IxModel * pChild);
   void removeListOfChild(long row);

#ifndef _QX_NO_JSON

   virtual QString toJson_Helper(int row) const = 0;
   virtual bool fromJson_Helper(const QString & json, int row) = 0;

   virtual QVariant getRelationshipValues_Helper(int row, const QString & relation, bool bLoadFromDatabase, const QString & sAppendRelations) = 0;
   virtual bool setRelationshipValues_Helper(int row, const QString & relation, const QVariant & values) = 0;

#endif // _QX_NO_JSON

};

} // namespace qx

#endif // _IX_MODEL_H_
