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

#ifndef _QX_MODEL_H_
#define _QX_MODEL_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxModel.h
 * \author Lionel Marty
 * \ingroup QxModelView
 * \brief All classes registered into QxOrm context can be used with Qt model/view architecture (Qt widgets and/or QML views)
 */

#include <QxModelView/IxModel.h>
#include <QxModelView/QxModelRowCompare.h>

#include <QxCollection/QxCollection.h>

#include <QxRegister/QxClass.h>

#include <QxTraits/get_primary_key.h>
#include <QxTraits/is_qx_registered.h>
#include <QxTraits/is_valid_primary_key.h>

#include <QxSerialize/QxDump.h>
#include <QxSerialize/QxClone.h>

#ifndef _QX_NO_JSON
#include <QxSerialize/QJson/QxSerializeQJson_QxCollection.h>
#include <QxSerialize/QxSerializeQJson.h>
#endif // _QX_NO_JSON

namespace qx {
namespace model_view {
namespace detail {

template <class T, class M> struct QxNestedModel;
template <class T, class M> struct QxNestedModel_Generic;
template <class T, class M> struct QxNestedModel_Container;

} // namespace detail
} // namespace model_view
} // namespace qx

namespace qx {

/*!
 * \ingroup QxModelView
 * \brief qx::QxModel<T, B> : all classes registered into QxOrm context can be used with Qt model/view architecture (Qt widgets and/or QML views)
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
template <class T, class B = qx::IxModel>
class QxModel : public B // B type must inherit from qx::IxModel and must not define new data-members (use 'm_hCustomProperties' or QObject dynamic properties if you need new properties in your derived class)
{

   template <typename U, typename V> friend struct qx::model_view::detail::QxNestedModel;
   template <typename U, typename V> friend struct qx::model_view::detail::QxNestedModel_Generic;
   template <typename U, typename V> friend struct qx::model_view::detail::QxNestedModel_Container;

public:

   typedef std::shared_ptr<T> type_ptr;
   typedef typename qx::trait::get_primary_key<T>::type type_primary_key;
   typedef qx::QxCollection<type_primary_key, type_ptr> type_collection;
   typedef B type_base_class;

   enum { qx_is_valid = (qx::trait::is_qx_registered<T>::value && std::is_base_of<qx::IxModel, B>::value) };

protected:

   type_collection m_model;                           //!< Model associated to a class registered into QxOrm context
   std::shared_ptr<QPair<int, type_ptr> > m_pDirtyRow;  //!< When displayed in a QTableView, this will cause an empty line awaiting user input to be displayed at the bottom (enabled with setShowEmptyLine() method)

public:

   QxModel(QObject * parent = 0) : B(parent) { qx::QxModel<T, B>::init(); }
   QxModel(qx::IxModel * other, QObject * parent) : B(parent) { qx::QxModel<T, B>::initFrom(other); }
   virtual ~QxModel() { ; }

protected:

   void init()
   {
      static_assert(qx_is_valid, "qx_is_valid");
      this->m_pClass = qx::QxClass<T>::getSingleton(); qAssert(this->m_pClass != NULL);
      this->m_pDataMemberX = (this->m_pClass ? this->m_pClass->getDataMemberX() : NULL); qAssert(this->m_pDataMemberX != NULL);
      this->m_pDataMemberId = (this->m_pDataMemberX ? this->m_pDataMemberX->getId_WithDaoStrategy() : NULL);
      this->m_pCollection = (& m_model);
      this->generateRoleNames();
   }

   void initFrom(qx::IxModel * pOther)
   {
      init();
      qx::QxModel<T, B> * pOtherWrk = static_cast<qx::QxModel<T, B> *>(pOther);
      m_model = pOtherWrk->m_model;
      this->m_lManualInsertIndex = pOtherWrk->m_lManualInsertIndex;
      this->setParentModel(pOtherWrk->m_pParent);
      if (this->m_pParent) { this->m_eAutoUpdateDatabase = this->m_pParent->getAutoUpdateDatabase(); }
      this->m_hCustomProperties = pOtherWrk->m_hCustomProperties;
   }

public:

   virtual bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex())
   {
      if (parent.isValid()) { return false; }
      if ((row < 0) || (count <= 0)) { return false; }
      this->beginInsertRows(QModelIndex(), row, (row + count - 1));
      for (int i = 0; i < count; ++i)
      {
         type_ptr pItem = type_ptr(new T());
         insertItem(row, pItem);
      }
      this->endInsertRows();
      return true;
   }

   virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder)
   {
      IxDataMember * pDataMember = this->getDataMember(column); if (! pDataMember) { return; }
      m_model.sort(qx::model_view::QxModelRowCompare<typename type_collection::type_pair_key_value>((order == Qt::AscendingOrder), pDataMember));
      this->raiseEvent_layoutChanged();
   }

   virtual bool getShowEmptyLine() const { return m_pDirtyRow.get(); }

   virtual void setShowEmptyLine(bool b)
   {
      if (b == getShowEmptyLine()) { return; }
      if (b) { addDirtyRow(); return; }
      this->beginRemoveRows(QModelIndex(), this->rowCount(), this->rowCount());
      m_pDirtyRow.reset();
      this->endRemoveRows();
   }

public:

   /*!
    * \brief Return the number of lines in the table (database) mapped to the C++ class T (registered into QxOrm context) and filtered by a user SQL query
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library (optional parameter)
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    */
   virtual long qxCount(const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL)
   {
      return qx::dao::count<T>(query, this->database(pDatabase));
   }

   /*!
    * \brief Return the number of lines in the table (database) mapped to the C++ class T (registered into QxOrm context) and filtered by a user SQL query
    * \param lCount Output parameter with the number of lines in the table associated to the SQL query
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library (optional parameter)
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    */
   virtual QSqlError qxCount(long & lCount, const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL)
   {
      this->m_lastError = qx::dao::count<T>(lCount, query, this->database(pDatabase));
      return this->m_lastError;
   }

   /*!
    * \brief Clear the model and fetch an object (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database
    * \param id Row id to be fetched (retrieve all properties from database)
    * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxFetchById(const QVariant & id, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      this->clear();
      type_ptr pItem = type_ptr(new T());
      if (! this->m_pDataMemberId) { qDebug("[QxOrm] problem with 'qxFetchById()' method : '%s'", "data member id not registered"); qAssert(false); }
      if (! this->m_pDataMemberId) { this->m_lastError = QSqlError("[QxOrm] problem with 'qxFetchById()' method : 'data member id not registered'", "", QSqlError::UnknownError); return this->m_lastError; }
      this->m_pDataMemberId->fromVariant(pItem.get(), id);

      type_primary_key primaryKey;
      qx::cvt::from_variant(id, primaryKey);
      this->beginInsertRows(QModelIndex(), 0, 0);
      m_model.insert(primaryKey, pItem);

      if (relation.count() == 0) { this->m_lastError = qx::dao::fetch_by_id((* pItem), this->database(pDatabase), this->m_lstColumns); }
      else { this->m_lastError = qx::dao::fetch_by_id_with_relation(relation, (* pItem), this->database(pDatabase)); }
      this->updateShowEmptyLine();
      this->endInsertRows();
      return this->m_lastError;
   }

   /*!
    * \brief Clear the model and fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
    * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxFetchAll(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      this->clear();
      type_collection tmp;
      if (relation.count() == 0) { this->m_lastError = qx::dao::fetch_all(tmp, this->database(pDatabase), this->m_lstColumns); }
      else { this->m_lastError = qx::dao::fetch_all_with_relation(relation, tmp, this->database(pDatabase)); }

      if (tmp.count() <= 0) { return this->m_lastError; }
      this->beginResetModel();
      m_model = tmp;
      this->updateShowEmptyLine();
      this->endResetModel();
      return this->m_lastError;
   }

   /*!
    * \brief Clear the model and fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxFetchByQuery(const qx::QxSqlQuery & query, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      this->clear();
      type_collection tmp;
      if (relation.count() == 0) { this->m_lastError = qx::dao::fetch_by_query(query, tmp, this->database(pDatabase), this->m_lstColumns); }
      else { this->m_lastError = qx::dao::fetch_by_query_with_relation(relation, query, tmp, this->database(pDatabase)); }

      if (tmp.count() <= 0) { return this->m_lastError; }
      this->beginResetModel();
      m_model = tmp;
      this->updateShowEmptyLine();
      this->endResetModel();
      return this->m_lastError;
   }

   /*!
    * \brief Get an item in the model at line row and fetch all its properties mapped to a table in the database, then all views attached to this model are automatically updated
    * \param row Get an item in the model at line row
    * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxFetchRow(int row, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      type_ptr pItem = getRowItemAt(row); if (! pItem) { return QSqlError(); }
      if (relation.count() == 0) { this->m_lastError = qx::dao::fetch_by_id((* pItem), this->database(pDatabase), this->m_lstColumns); }
      else { this->m_lastError = qx::dao::fetch_by_id_with_relation(relation, (* pItem), this->database(pDatabase)); }
      if (this->m_lastError.isValid()) { return this->m_lastError; }

      QModelIndex idxTopLeft = this->index(row, 0);
      QModelIndex idxBottomRight = this->index(row, (this->m_lstDataMember.count() - 1));
      this->raiseEvent_dataChanged(idxTopLeft, idxBottomRight);
      updateKey(row);
      return this->m_lastError;
   }

   /*!
    * \brief Insert all items in the model into database
    * \param relation List of relationships keys to be inserted in others tables of database : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxInsert(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      if (relation.count() > 0) { this->syncAllNestedModel(relation); }
      if (relation.count() == 0) { this->m_lastError = qx::dao::insert(m_model, this->database(pDatabase)); }
      else { this->m_lastError = qx::dao::insert_with_relation(relation, m_model, this->database(pDatabase)); }
      if (! this->m_lastError.isValid()) { this->updateAllKeys(); }
      return this->m_lastError;
   }

   /*!
    * \brief Insert an item of the model at line row into database
    * \param row Insert an item in the model at line row
    * \param relation List of relationships keys to be inserted in others tables of database : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxInsertRow(int row, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      type_ptr pItem = getRowItemAt(row); if (! pItem) { return QSqlError(); }
      if (relation.count() > 0) { this->syncNestedModel(row, relation); }
      if (relation.count() == 0) { this->m_lastError = qx::dao::insert((* pItem), this->database(pDatabase)); }
      else { this->m_lastError = qx::dao::insert_with_relation(relation, (* pItem), this->database(pDatabase)); }
      if (! this->m_lastError.isValid()) { updateKey(row); }
      return this->m_lastError;
   }

   /*!
    * \brief Update all items in the model into database
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param relation List of relationships keys to be inserted in others tables of database : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxUpdate(const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      if (relation.count() > 0) { this->syncAllNestedModel(relation); }
      if (relation.count() == 0) { this->m_lastError = qx::dao::update_by_query(query, m_model, this->database(pDatabase), this->m_lstColumns); }
      else { this->m_lastError = qx::dao::update_by_query_with_relation(relation, query, m_model, this->database(pDatabase)); }
      if (! this->m_lastError.isValid()) { this->updateAllKeys(); }
      return this->m_lastError;
   }

   /*!
    * \brief Update an item of the model at line row into database
    * \param row Update an item in the model at line row
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param relation List of relationships keys to be inserted in others tables of database : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxUpdateRow(int row, const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      if ((row < 0) || (row >= m_model.count())) { return QSqlError(); }
      if (relation.count() > 0) { this->syncNestedModel(row, relation); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return QSqlError(); }
      if (relation.count() == 0) { this->m_lastError = qx::dao::update_by_query(query, (* pItem), this->database(pDatabase), this->m_lstColumns); }
      else { this->m_lastError = qx::dao::update_by_query_with_relation(relation, query, (* pItem), this->database(pDatabase)); }
      if (! this->m_lastError.isValid()) { updateKey(row); }
      return this->m_lastError;
   }

   /*!
    * \brief Save all items (insert or update) in the model into database
    * \param relation List of relationships keys to be inserted in others tables of database : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxSave(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      if (relation.count() > 0) { this->syncAllNestedModel(relation); }
      if (relation.count() == 0) { this->m_lastError = qx::dao::save(m_model, this->database(pDatabase)); }
      else { this->m_lastError = qx::dao::save_with_relation(relation, m_model, this->database(pDatabase)); }
      if (! this->m_lastError.isValid()) { this->updateAllKeys(); }
      return this->m_lastError;
   }

   /*!
    * \brief Save an item of the model at line row into database
    * \param row Save an item (insert or update) in the model at line row
    * \param relation List of relationships keys to be inserted in others tables of database : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxSaveRow(int row, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      if ((row < 0) || (row >= m_model.count())) { return QSqlError(); }
      if (relation.count() > 0) { this->syncNestedModel(row, relation); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return QSqlError(); }
      if (relation.count() == 0) { this->m_lastError = qx::dao::save((* pItem), this->database(pDatabase)); }
      else { this->m_lastError = qx::dao::save_with_relation(relation, (* pItem), this->database(pDatabase)); }
      if (! this->m_lastError.isValid()) { updateKey(row); }
      return this->m_lastError;
   }

   /*!
    * \brief Used internally by qx::IxModel::setData() method with e_auto_update_on_field_change option, save an item (even if it is the dirty row item) of the model at line row into database
    * \param row Save an item (insert or update) in the model at line row
    * \param column List of columns of model to save in database
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxSaveRowData(int row, const QStringList & column = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      if (! this->m_pDataMemberId) { this->m_lastError = QSqlError("[QxOrm] problem with 'qxSaveRowData()' method : 'data member id not registered'", "", QSqlError::UnknownError); return this->m_lastError; }
      type_ptr pItem = getRowItemAt(row); if (! pItem) { return QSqlError(); }
      QVariant id = this->m_pDataMemberId->toVariant(pItem.get());
      bool bExist = qx::trait::is_valid_primary_key(id);
      if (bExist) { bExist = qx::dao::exist((* pItem), this->database(pDatabase)); }
      if (bExist) { this->m_lastError = qx::dao::update((* pItem), this->database(pDatabase), column); }
      else { this->m_lastError = qx::dao::insert((* pItem), this->database(pDatabase)); }
      return this->m_lastError;
   }

   /*!
    * \brief Delete a line of a table (database) mapped to a C++ object of type T (registered into QxOrm context), if no error occurred then you should remove row from the model
    * \param id Row id to be deleted from database
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDeleteById(const QVariant & id, QSqlDatabase * pDatabase = NULL)
   {
      type_ptr pItem = type_ptr(new T());
      if (! this->m_pDataMemberId) { qDebug("[QxOrm] problem with 'qxDeleteById()' method : '%s'", "data member id not registered"); qAssert(false); }
      if (! this->m_pDataMemberId) { this->m_lastError = QSqlError("[QxOrm] problem with 'qxDeleteById()' method : 'data member id not registered'", "", QSqlError::UnknownError); return this->m_lastError; }
      this->m_pDataMemberId->fromVariant(pItem.get(), id);
      this->m_lastError = qx::dao::delete_by_id((* pItem), this->database(pDatabase));
      return this->m_lastError;
   }

   /*!
    * \brief Delete all lines of a table (database) mapped to a C++ class T (registered into QxOrm context), if no error occurred then you should clear the model
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDeleteAll(QSqlDatabase * pDatabase = NULL)
   {
      this->m_lastError = qx::dao::delete_all<T>(this->database(pDatabase));
      return this->m_lastError;
   }

   /*!
    * \brief Delete all lines of a table (database) mapped to a C++ class T (registered into QxOrm context) and filtered by a user SQL query, if no error occurred then you should refresh the model
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDeleteByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   {
      this->m_lastError = qx::dao::delete_by_query<T>(query, this->database(pDatabase));
      return this->m_lastError;
   }

   /*!
    * \brief Delete in database the item at line row in the model, if no error occurred then you should remove row from the model
    * \param row Delete in database the item in the model at line row
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDeleteRow(int row, QSqlDatabase * pDatabase = NULL)
   {
      if ((row < 0) || (row >= m_model.count())) { return QSqlError(); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return QSqlError(); }
      this->m_lastError = qx::dao::delete_by_id((* pItem), this->database(pDatabase));
      return this->m_lastError;
   }

   /*!
    * \brief Delete a line of a table (even if a logical delete is defined) mapped to a C++ object of type T (registered into QxOrm context), if no error occurred then you should remove row from the model
    * \param id Row id to be deleted from database
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDestroyById(const QVariant & id, QSqlDatabase * pDatabase = NULL)
   {
      type_ptr pItem = type_ptr(new T());
      if (! this->m_pDataMemberId) { qDebug("[QxOrm] problem with 'qxDeleteById()' method : '%s'", "data member id not registered"); qAssert(false); }
      if (! this->m_pDataMemberId) { this->m_lastError = QSqlError("[QxOrm] problem with 'qxDeleteById()' method : 'data member id not registered'", "", QSqlError::UnknownError); return this->m_lastError; }
      this->m_pDataMemberId->fromVariant(pItem.get(), id);
      this->m_lastError = qx::dao::destroy_by_id((* pItem), this->database(pDatabase));
      return this->m_lastError;
   }

   /*!
    * \brief Delete all lines of a table (even if a logical delete is defined) mapped to a C++ class T (registered into QxOrm context), if no error occurred then you should clear the model
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDestroyAll(QSqlDatabase * pDatabase = NULL)
   {
      this->m_lastError = qx::dao::destroy_all<T>(this->database(pDatabase));
      return this->m_lastError;
   }

   /*!
    * \brief Delete all lines of a table (even if a logical delete is defined) mapped to a C++ class T (registered into QxOrm context) and filtered by a user SQL query, if no error occurred then you should refresh the model
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDestroyByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   {
      this->m_lastError = qx::dao::destroy_by_query<T>(query, this->database(pDatabase));
      return this->m_lastError;
   }

   /*!
    * \brief Delete in database (even if a logical delete is defined) the item at line row in the model, if no error occurred then you should remove row from the model
    * \param row Delete in database the item in the model at line row
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDestroyRow(int row, QSqlDatabase * pDatabase = NULL)
   {
      if ((row < 0) || (row >= m_model.count())) { return QSqlError(); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return QSqlError(); }
      this->m_lastError = qx::dao::destroy_by_id((* pItem), this->database(pDatabase));
      return this->m_lastError;
   }

   virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   {
      this->clear();
      type_collection tmp;
      this->m_lastError = qx::dao::execute_query(query, tmp, this->database(pDatabase));

      if (tmp.count() <= 0) { return this->m_lastError; }
      this->beginResetModel();
      m_model = tmp;
      this->updateShowEmptyLine();
      this->endResetModel();
      return this->m_lastError;
   }

   virtual qx_bool qxExist(const QVariant & id, QSqlDatabase * pDatabase = NULL)
   {
      type_ptr pItem = type_ptr(new T());
      if (! this->m_pDataMemberId) { qDebug("[QxOrm] problem with 'qxExist()' method : '%s'", "data member id not registered"); qAssert(false); }
      if (! this->m_pDataMemberId) { return qx_bool(false); }
      this->m_pDataMemberId->fromVariant(pItem.get(), id);
      return qx::dao::exist((* pItem), this->database(pDatabase));
   }

   virtual qx::QxInvalidValueX qxValidate(const QStringList & groups = QStringList())
   {
      return qx::validate(m_model, groups);
   }

   virtual qx::QxInvalidValueX qxValidateRow(int row, const QStringList & groups = QStringList())
   {
      type_ptr pItem = getRowItemAt(row); if (! pItem) { return qx::QxInvalidValueX(); }
      return qx::validate((* pItem), groups);
   }

protected:

   type_ptr getRowItemAt(int row) const
   {
      if ((row >= 0) && (row < m_model.count())) { return m_model.getByIndex(row); }
      if (m_pDirtyRow && (m_pDirtyRow->first == row)) { return m_pDirtyRow->second; }
      return type_ptr();
   }

   virtual void * getRowItemAsVoidPtr(int row) const { return getRowItemAt(row).get(); }

   virtual void dumpModelImpl(bool bJsonFormat) const { qx::dump(m_model, bJsonFormat); }

   virtual QObject * cloneModelImpl()
   {
      qx::QxModel<T, B> * pClone = new qx::QxModel<T, B>(this, NULL);
      std::shared_ptr<type_collection> pModel = qx::clone(pClone->m_model);
      if (pModel) { pClone->m_model = (* pModel); }
      return static_cast<QObject *>(pClone);
   }

   virtual void updateShowEmptyLine() { if (m_pDirtyRow) { m_pDirtyRow->first = m_model.count(); } }

   virtual bool isDirtyRow(int row) const { return (m_pDirtyRow && (m_pDirtyRow->first == row)); }

   virtual void insertDirtyRowToModel()
   {
      if (! m_pDirtyRow) { return; }
      int row = m_pDirtyRow->first;
      insertItem(row, m_pDirtyRow->second);
      if (this->m_pParent) { this->m_pParent->saveChildRelations(this); }
      updateKey(row);
      addDirtyRow();
   }

   void addDirtyRow()
   {
      this->beginInsertRows(QModelIndex(), m_model.count(), m_model.count());
      m_pDirtyRow.reset(new QPair<int, type_ptr>(m_model.count(), type_ptr(new T())));
      IxSqlRelation * pRelationParent = (this->m_pDataMemberRelationToParent ? this->m_pDataMemberRelationToParent->getSqlRelation() : NULL);
      IxSqlRelation::relation_type eRelationParentType = (pRelationParent ? pRelationParent->getRelationType() : IxSqlRelation::no_relation);
      if (this->m_pParent && ((eRelationParentType == IxSqlRelation::many_to_many) || (eRelationParentType == IxSqlRelation::many_to_one)))
      { this->m_pDataMemberRelationToParent->fromVariant(m_pDirtyRow->second.get(), this->m_pParent->getIdFromChild(this)); }
      this->endInsertRows();
   }

   void insertItem(int row, const type_ptr & pItem)
   {
      if (! pItem) { return; }
      type_primary_key primaryKey;
      this->m_lManualInsertIndex = (this->m_lManualInsertIndex - 1);
      QVariant vNewId(static_cast<qlonglong>(this->m_lManualInsertIndex));
      qx::cvt::from_variant(vNewId, primaryKey);
      m_model.insert(row, primaryKey, pItem);
      this->updateShowEmptyLine();
   }

   void updateKey(int row)
   {
      if ((row < 0) || (row >= m_model.count())) { return; }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem || ! this->m_pDataMemberId) { return; }
      type_primary_key currPrimaryKey = m_model.getKeyByIndex(row);
      QVariant vCurrPrimaryKey = qx::cvt::to_variant(currPrimaryKey);
      QVariant vNextPrimaryKey = this->m_pDataMemberId->toVariant(pItem.get());
      if ((vCurrPrimaryKey == vNextPrimaryKey) || (! vNextPrimaryKey.isValid())) { return; }
      if (! qx::trait::is_valid_primary_key(vNextPrimaryKey)) { return; }
      type_primary_key updatedPrimaryKey;
      qx::cvt::from_variant(vNextPrimaryKey, updatedPrimaryKey);
      if (m_model.exist(updatedPrimaryKey)) { return; }
      m_model.removeByIndex(row);
      m_model.insert(row, updatedPrimaryKey, pItem);
   }

   void updateAllKeys()
   {
      for (long l = 0; l < m_model.count(); l++)
      { updateKey(l); }
   }

protected:

#ifndef _QX_NO_JSON

   virtual QString toJson_Helper(int row) const
   {
      if (row == -1) { return qx::serialization::json::to_string(m_model); }
      type_ptr pItem = getRowItemAt(row); if (! pItem) { return QString(); }
      return qx::serialization::json::to_string(* pItem);
   }

   virtual bool fromJson_Helper(const QString & json, int row)
   {
      if (row == -1)
      {
         this->clear();
         type_collection tmp;
         if (! qx::serialization::json::from_string(tmp, json)) { return false; }
         this->beginResetModel();
         m_model = tmp;
         this->updateShowEmptyLine();
         this->endResetModel();
         return true;
      }

      type_ptr pItem = getRowItemAt(row); if (! pItem) { return false; }
      if (! qx::serialization::json::from_string((* pItem), json)) { return false; }

      QModelIndex idxTopLeft = this->index(row, 0);
      QModelIndex idxBottomRight = this->index(row, (this->m_lstDataMember.count() - 1));
      this->raiseEvent_dataChanged(idxTopLeft, idxBottomRight);
      updateKey(row);
      return true;
   }

   virtual QVariant getRelationshipValues_Helper(int row, const QString & relation, bool bLoadFromDatabase, const QString & sAppendRelations)
   {
      if ((row < 0) || (row >= m_model.count())) { return QVariant(); }
      if (! this->m_pDataMemberId || ! this->m_pDataMemberX || ! this->m_pDataMemberX->exist(relation)) { return QVariant(); }
      IxDataMember * pDataMember = this->m_pDataMemberX->get_WithDaoStrategy(relation); if (! pDataMember) { return QVariant(); }
      IxSqlRelation * pRelation = (pDataMember->hasSqlRelation() ? pDataMember->getSqlRelation() : NULL); if (! pRelation) { return QVariant(); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return QVariant(); }
      type_ptr pItemTemp = pItem;

      if (bLoadFromDatabase)
      {
         QString sRelation = relation;
         if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
         else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
         pItemTemp = type_ptr(new T());
         QVariant id = this->m_pDataMemberId->toVariant(pItem.get());
         this->m_pDataMemberId->fromVariant(pItemTemp.get(), id);
         QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, (* pItemTemp));
         if (daoError.isValid()) { return QVariant(); }
      }

      QJsonValue json = pDataMember->toJson(pItemTemp.get()); if (json.isNull()) { return QVariant(); }
      if (json.isArray()) { return json.toArray().toVariantList(); }
      return json.toObject().toVariantMap();
   }

   virtual bool setRelationshipValues_Helper(int row, const QString & relation, const QVariant & values)
   {
      if ((row < 0) || (row >= m_model.count())) { return false; }
      if ((values.type() != QVariant::List) && (values.type() != QVariant::Map)) { return false; }
      if (! this->m_pDataMemberId || ! this->m_pDataMemberX || ! this->m_pDataMemberX->exist(relation)) { return false; }
      IxDataMember * pDataMember = this->m_pDataMemberX->get_WithDaoStrategy(relation); if (! pDataMember) { return false; }
      IxSqlRelation * pRelation = (pDataMember->hasSqlRelation() ? pDataMember->getSqlRelation() : NULL); if (! pRelation) { return false; }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return false; }

      QJsonValue json;
      if (values.type() == QVariant::List) { json = QJsonArray::fromVariantList(values.toList()); }
      else if (values.type() == QVariant::Map) { json = QJsonObject::fromVariantMap(values.toMap()); }
      if (! pDataMember->fromJson(pItem.get(), json)) { return false; }

      QModelIndex idxTopLeft = this->index(row, 0);
      QModelIndex idxBottomRight = this->index(row, (this->m_lstDataMember.count() - 1));
      this->raiseEvent_dataChanged(idxTopLeft, idxBottomRight);
      return true;
   }

#endif // _QX_NO_JSON

};

} // namespace qx

#endif // _QX_MODEL_H_
