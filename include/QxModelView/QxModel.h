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

template <class T> struct QxNestedModel;
template <class T> struct QxNestedModel_Generic;
template <class T> struct QxNestedModel_Container;

} // namespace detail
} // namespace model_view
} // namespace qx

namespace qx {

/*!
 * \ingroup QxModelView
 * \brief qx::QxModel<T> : all classes registered into QxOrm context can be used with Qt model/view architecture (Qt widgets and/or QML views)
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
template <class T>
class QxModel : public qx::IxModel
{

   friend struct qx::model_view::detail::QxNestedModel<T>;
   friend struct qx::model_view::detail::QxNestedModel_Generic<T>;
   template <typename U> friend struct qx::model_view::detail::QxNestedModel_Container;

public:

   typedef qx_shared_ptr<T> type_ptr;
   typedef typename qx::trait::get_primary_key<T>::type type_primary_key;
   typedef qx::QxCollection<type_primary_key, type_ptr> type_collection;

   enum { qx_is_valid = qx::trait::is_qx_registered<T>::value };

protected:

   type_collection m_model;      //!< Model associated to a class registered into QxOrm context
   long m_lManualInsertIndex;    //!< Index to insert manually items to the collection

public:

   QxModel(QObject * parent = 0) : qx::IxModel(parent), m_lManualInsertIndex(0) { qx::QxModel<T>::init(); }
   QxModel(qx::IxModel * other, QObject * parent) : qx::IxModel(parent), m_lManualInsertIndex(0) { qx::QxModel<T>::initFrom(other); }
   virtual ~QxModel() { ; }

protected:

   void init()
   {
      BOOST_STATIC_ASSERT(qx_is_valid);
      m_pClass = qx::QxClass<T>::getSingleton(); qAssert(m_pClass != NULL);
      m_pDataMemberX = (m_pClass ? m_pClass->getDataMemberX() : NULL); qAssert(m_pDataMemberX != NULL);
      m_pDataMemberId = (m_pDataMemberX ? m_pDataMemberX->getId_WithDaoStrategy() : NULL);
      m_pCollection = (& m_model);
      generateRoleNames();
   }

   void initFrom(qx::IxModel * pOther)
   {
      init();
      qx::QxModel<T> * pOtherWrk = static_cast<qx::QxModel<T> *>(pOther);
      this->m_model = pOtherWrk->m_model;
      this->m_lManualInsertIndex = pOtherWrk->m_lManualInsertIndex;
      this->m_pParent = pOtherWrk->m_pParent;
      if (this->m_pParent) { this->m_eAutoUpdateDatabase = this->m_pParent->getAutoUpdateDatabase(); }
   }

public:

   virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const
   {
      if (! index.isValid()) { return QVariant(); }
      if ((role == Qt::DisplayRole) || (role == Qt::EditRole))
      {
         if ((index.column() < 0) || (index.column() >= m_lstDataMember.count())) { return QVariant(); }
         else if ((index.row() < 0) || (index.row() >= m_model.count())) { return QVariant(); }
         IxDataMember * pDataMember = m_lstDataMember.at(index.column());
         type_ptr pItem = m_model.getByIndex(index.row());
         if (! pDataMember || ! pItem) { return QVariant(); }
         return pDataMember->toVariant(pItem.get());
      }
      else if (role >= (Qt::UserRole + 1))
      {
         QModelIndex idx = this->index(index.row(), (role - Qt::UserRole - 1), QModelIndex());
         return data(idx, Qt::DisplayRole);
      }
      return QVariant();
   }

   virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole)
   {
      if (! index.isValid()) { return false; }
      if (role == Qt::EditRole)
      {
         if ((index.column() < 0) || (index.column() >= m_lstDataMember.count())) { return false; }
         else if ((index.row() < 0) || (index.row() >= m_model.count())) { return false; }
         IxDataMember * pDataMember = m_lstDataMember.at(index.column());
         type_ptr pItem = m_model.getByIndex(index.row());
         if (! pDataMember || ! pItem) { return false; }
         QVariant vCurrentValue = pDataMember->toVariant(pItem.get());
         if (vCurrentValue == value) { return true; }
         qx_bool bSetData = pDataMember->fromVariant(pItem.get(), value);
         if (bSetData) { raiseEvent_dataChanged(index, index); }
         if (bSetData && (m_eAutoUpdateDatabase == qx::IxModel::e_auto_update_on_field_change) && m_pDataMemberId)
         {
            QVariant vId = m_pDataMemberId->toVariant(pItem.get());
            bool bExist = qx::trait::is_valid_primary_key(vId);
            if (bExist) { bExist = qx::dao::exist((* pItem), database(NULL)); }
            if (bExist) { m_lastError = qx::dao::update((* pItem), database(NULL), (QStringList() << pDataMember->getKey())); }
            else { m_lastError = qx::dao::insert((* pItem), database(NULL)); }
         }
         return bSetData;
      }
      else if (role >= (Qt::UserRole + 1))
      {
         QModelIndex idx = this->index(index.row(), (role - Qt::UserRole - 1), QModelIndex());
         return setData(idx, value, Qt::EditRole);
      }
      return false;
   }

   virtual bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex())
   {
      if (parent.isValid()) { return false; }
      if ((row < 0) || (count <= 0)) { return false; }
      beginInsertRows(QModelIndex(), row, (row + count - 1));
      for (int i = 0; i < count; ++i)
      {
         type_primary_key primaryKey;
         m_lManualInsertIndex = (m_lManualInsertIndex - 1);
         QVariant vNewId(static_cast<qlonglong>(m_lManualInsertIndex));
         qx::cvt::from_variant(vNewId, primaryKey);
         type_ptr pItem = type_ptr(new T());
         m_model.insert(row, primaryKey, pItem);
      }
      endInsertRows();
      return true;
   }

public:

   /*!
    * \brief Return the number of lines in the table (database) mapped to the C++ class T (registered into QxOrm context) and filtered by a user SQL query
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library (optional parameter)
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    */
   virtual long qxCount(const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL)
   {
      return qx::dao::count<T>(query, database(pDatabase));
   }

   /*!
    * \brief Return the number of lines in the table (database) mapped to the C++ class T (registered into QxOrm context) and filtered by a user SQL query
    * \param lCount Output parameter with the number of lines in the table associated to the SQL query
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library (optional parameter)
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    */
   virtual QSqlError qxCount(long & lCount, const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL)
   {
      m_lastError = qx::dao::count<T>(lCount, query, database(pDatabase));
      return m_lastError;
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
      clear();
      type_ptr pItem = type_ptr(new T());
      if (! m_pDataMemberId) { qDebug("[QxOrm] problem with 'qxFetchById()' method : '%s'", "data member id not registered"); qAssert(false); }
      if (! m_pDataMemberId) { m_lastError = QSqlError("[QxOrm] problem with 'qxFetchById()' method : 'data member id not registered'", "", QSqlError::UnknownError); return m_lastError; }
      m_pDataMemberId->fromVariant(pItem.get(), id);

      type_primary_key primaryKey;
      qx::cvt::from_variant(id, primaryKey);
      beginInsertRows(QModelIndex(), 0, 0);
      m_model.insert(primaryKey, pItem);

      if (relation.count() == 0) { m_lastError = qx::dao::fetch_by_id((* pItem), database(pDatabase), m_lstColumns); }
      else { m_lastError = qx::dao::fetch_by_id_with_relation(relation, (* pItem), database(pDatabase)); }
      endInsertRows();
      return m_lastError;
   }

   /*!
    * \brief Clear the model and fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
    * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxFetchAll(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      clear();
      type_collection tmp;
      if (relation.count() == 0) { m_lastError = qx::dao::fetch_all(tmp, database(pDatabase), m_lstColumns); }
      else { m_lastError = qx::dao::fetch_all_with_relation(relation, tmp, database(pDatabase)); }

      if (tmp.count() <= 0) { return m_lastError; }
      beginInsertRows(QModelIndex(), 0, (tmp.count() - 1));
      m_model = tmp;
      endInsertRows();
      return m_lastError;
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
      clear();
      type_collection tmp;
      if (relation.count() == 0) { m_lastError = qx::dao::fetch_by_query(query, tmp, database(pDatabase), m_lstColumns); }
      else { m_lastError = qx::dao::fetch_by_query_with_relation(relation, query, tmp, database(pDatabase)); }

      if (tmp.count() <= 0) { return m_lastError; }
      beginInsertRows(QModelIndex(), 0, (tmp.count() - 1));
      m_model = tmp;
      endInsertRows();
      return m_lastError;
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
      if ((row < 0) || (row >= m_model.count())) { return QSqlError(); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return QSqlError(); }
      if (relation.count() == 0) { m_lastError = qx::dao::fetch_by_id((* pItem), database(pDatabase), m_lstColumns); }
      else { m_lastError = qx::dao::fetch_by_id_with_relation(relation, (* pItem), database(pDatabase)); }
      if (m_lastError.isValid()) { return m_lastError; }

      QModelIndex idxTopLeft = this->index(row, 0);
      QModelIndex idxBottomRight = this->index(row, (m_lstDataMember.count() - 1));
      this->raiseEvent_dataChanged(idxTopLeft, idxBottomRight);
      this->updateKey(row);
      return m_lastError;
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
      if (relation.count() == 0) { m_lastError = qx::dao::insert(m_model, database(pDatabase)); }
      else { m_lastError = qx::dao::insert_with_relation(relation, m_model, database(pDatabase)); }
      if (! m_lastError.isValid()) { this->updateAllKeys(); }
      return m_lastError;
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
      if ((row < 0) || (row >= m_model.count())) { return QSqlError(); }
      if (relation.count() > 0) { this->syncNestedModel(row, relation); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return QSqlError(); }
      if (relation.count() == 0) { m_lastError = qx::dao::insert((* pItem), database(pDatabase)); }
      else { m_lastError = qx::dao::insert_with_relation(relation, (* pItem), database(pDatabase)); }
      if (! m_lastError.isValid()) { this->updateKey(row); }
      return m_lastError;
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
      if (relation.count() == 0) { m_lastError = qx::dao::update_by_query(query, m_model, database(pDatabase), m_lstColumns); }
      else { m_lastError = qx::dao::update_by_query_with_relation(relation, query, m_model, database(pDatabase)); }
      if (! m_lastError.isValid()) { this->updateAllKeys(); }
      return m_lastError;
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
      if (relation.count() == 0) { m_lastError = qx::dao::update_by_query(query, (* pItem), database(pDatabase), m_lstColumns); }
      else { m_lastError = qx::dao::update_by_query_with_relation(relation, query, (* pItem), database(pDatabase)); }
      if (! m_lastError.isValid()) { this->updateKey(row); }
      return m_lastError;
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
      if (relation.count() == 0) { m_lastError = qx::dao::save(m_model, database(pDatabase)); }
      else { m_lastError = qx::dao::save_with_relation(relation, m_model, database(pDatabase)); }
      if (! m_lastError.isValid()) { this->updateAllKeys(); }
      return m_lastError;
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
      if (relation.count() == 0) { m_lastError = qx::dao::save((* pItem), database(pDatabase)); }
      else { m_lastError = qx::dao::save_with_relation(relation, (* pItem), database(pDatabase)); }
      if (! m_lastError.isValid()) { this->updateKey(row); }
      return m_lastError;
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
      if (! m_pDataMemberId) { qDebug("[QxOrm] problem with 'qxDeleteById()' method : '%s'", "data member id not registered"); qAssert(false); }
      if (! m_pDataMemberId) { m_lastError = QSqlError("[QxOrm] problem with 'qxDeleteById()' method : 'data member id not registered'", "", QSqlError::UnknownError); return m_lastError; }
      m_pDataMemberId->fromVariant(pItem.get(), id);
      m_lastError = qx::dao::delete_by_id((* pItem), database(pDatabase));
      return m_lastError;
   }

   /*!
    * \brief Delete all lines of a table (database) mapped to a C++ class T (registered into QxOrm context), if no error occurred then you should clear the model
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDeleteAll(QSqlDatabase * pDatabase = NULL)
   {
      m_lastError = qx::dao::delete_all<T>(database(pDatabase));
      return m_lastError;
   }

   /*!
    * \brief Delete all lines of a table (database) mapped to a C++ class T (registered into QxOrm context) and filtered by a user SQL query, if no error occurred then you should refresh the model
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDeleteByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   {
      m_lastError = qx::dao::delete_by_query<T>(query, database(pDatabase));
      return m_lastError;
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
      m_lastError = qx::dao::delete_by_id((* pItem), database(pDatabase));
      return m_lastError;
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
      if (! m_pDataMemberId) { qDebug("[QxOrm] problem with 'qxDeleteById()' method : '%s'", "data member id not registered"); qAssert(false); }
      if (! m_pDataMemberId) { m_lastError = QSqlError("[QxOrm] problem with 'qxDeleteById()' method : 'data member id not registered'", "", QSqlError::UnknownError); return m_lastError; }
      m_pDataMemberId->fromVariant(pItem.get(), id);
      m_lastError = qx::dao::destroy_by_id((* pItem), database(pDatabase));
      return m_lastError;
   }

   /*!
    * \brief Delete all lines of a table (even if a logical delete is defined) mapped to a C++ class T (registered into QxOrm context), if no error occurred then you should clear the model
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDestroyAll(QSqlDatabase * pDatabase = NULL)
   {
      m_lastError = qx::dao::destroy_all<T>(database(pDatabase));
      return m_lastError;
   }

   /*!
    * \brief Delete all lines of a table (even if a logical delete is defined) mapped to a C++ class T (registered into QxOrm context) and filtered by a user SQL query, if no error occurred then you should refresh the model
    * \param query Define a user SQL query added to default SQL query builded by QxOrm library
    * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
    * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
    */
   virtual QSqlError qxDestroyByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   {
      m_lastError = qx::dao::destroy_by_query<T>(query, database(pDatabase));
      return m_lastError;
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
      m_lastError = qx::dao::destroy_by_id((* pItem), database(pDatabase));
      return m_lastError;
   }

   virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   {
      clear();
      type_collection tmp;
      m_lastError = qx::dao::execute_query(query, tmp, database(pDatabase));

      if (tmp.count() <= 0) { return m_lastError; }
      beginInsertRows(QModelIndex(), 0, (tmp.count() - 1));
      m_model = tmp;
      endInsertRows();
      return m_lastError;
   }

   virtual qx_bool qxExist(const QVariant & id, QSqlDatabase * pDatabase = NULL)
   {
      type_ptr pItem = type_ptr(new T());
      if (! m_pDataMemberId) { qDebug("[QxOrm] problem with 'qxExist()' method : '%s'", "data member id not registered"); qAssert(false); }
      if (! m_pDataMemberId) { return qx_bool(false); }
      m_pDataMemberId->fromVariant(pItem.get(), id);
      return qx::dao::exist((* pItem), database(pDatabase));
   }

   virtual qx::QxInvalidValueX qxValidate(const QStringList & groups = QStringList())
   {
      return qx::validate(m_model, groups);
   }

   virtual qx::QxInvalidValueX qxValidateRow(int row, const QStringList & groups = QStringList())
   {
      if ((row < 0) || (row >= m_model.count())) { return qx::QxInvalidValueX(); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return qx::QxInvalidValueX(); }
      return qx::validate((* pItem), groups);
   }

protected:

   virtual void dumpModelImpl(bool bJsonFormat) const { qx::dump(m_model, bJsonFormat); }

   virtual QObject * cloneModelImpl()
   {
      qx::QxModel<T> * pClone = new qx::QxModel<T>(this, NULL);
      qx_shared_ptr<type_collection> pModel = qx::clone(pClone->m_model);
      if (pModel) { pClone->m_model = (* pModel); }
      return static_cast<QObject *>(pClone);
   }

   void updateKey(int row)
   {
      if ((row < 0) || (row >= m_model.count())) { return; }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem || ! m_pDataMemberId) { return; }
      type_primary_key currPrimaryKey = m_model.getKeyByIndex(row);
      QVariant vCurrPrimaryKey = qx::cvt::to_variant(currPrimaryKey);
      QVariant vNextPrimaryKey = m_pDataMemberId->toVariant(pItem.get());
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
      { this->updateKey(l); }
   }

protected:

#ifndef _QX_NO_JSON

   virtual QString toJson_Helper(int row) const
   {
      if (row == -1) { return qx::serialization::json::to_string(m_model); }
      if ((row < 0) || (row >= m_model.count())) { return QString(); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return QString(); }
      return qx::serialization::json::to_string(* pItem);
   }

   virtual bool fromJson_Helper(const QString & json, int row)
   {
      if (row == -1)
      {
         clear();
         type_collection tmp;
         if (! qx::serialization::json::from_string(tmp, json)) { return false; }
         beginInsertRows(QModelIndex(), 0, (tmp.count() - 1));
         m_model = tmp;
         endInsertRows();
         return true;
      }

      if ((row < 0) || (row >= m_model.count())) { return false; }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return false; }
      if (! qx::serialization::json::from_string((* pItem), json)) { return false; }

      QModelIndex idxTopLeft = this->index(row, 0);
      QModelIndex idxBottomRight = this->index(row, (m_lstDataMember.count() - 1));
      this->raiseEvent_dataChanged(idxTopLeft, idxBottomRight);
      this->updateKey(row);
      return true;
   }

   virtual QVariant getRelationshipValues_Helper(int row, const QString & relation, bool bLoadFromDatabase, const QString & sAppendRelations)
   {
      if ((row < 0) || (row >= m_model.count())) { return QVariant(); }
      if (! m_pDataMemberId || ! m_pDataMemberX || ! m_pDataMemberX->exist(relation)) { return QVariant(); }
      IxDataMember * pDataMember = m_pDataMemberX->get_WithDaoStrategy(relation); if (! pDataMember) { return QVariant(); }
      IxSqlRelation * pRelation = (pDataMember->hasSqlRelation() ? pDataMember->getSqlRelation() : NULL); if (! pRelation) { return QVariant(); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return QVariant(); }
      type_ptr pItemTemp = pItem;

      if (bLoadFromDatabase)
      {
         QString sRelation = relation;
         if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
         else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
         pItemTemp = type_ptr(new T());
         QVariant id = m_pDataMemberId->toVariant(pItem.get());
         m_pDataMemberId->fromVariant(pItemTemp.get(), id);
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
      if (! m_pDataMemberId || ! m_pDataMemberX || ! m_pDataMemberX->exist(relation)) { return false; }
      IxDataMember * pDataMember = m_pDataMemberX->get_WithDaoStrategy(relation); if (! pDataMember) { return false; }
      IxSqlRelation * pRelation = (pDataMember->hasSqlRelation() ? pDataMember->getSqlRelation() : NULL); if (! pRelation) { return false; }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return false; }

      QJsonValue json;
      if (values.type() == QVariant::List) { json = QJsonArray::fromVariantList(values.toList()); }
      else if (values.type() == QVariant::Map) { json = QJsonObject::fromVariantMap(values.toMap()); }
      if (! pDataMember->fromJson(pItem.get(), json)) { return false; }

      QModelIndex idxTopLeft = this->index(row, 0);
      QModelIndex idxBottomRight = this->index(row, (m_lstDataMember.count() - 1));
      this->raiseEvent_dataChanged(idxTopLeft, idxBottomRight);
      return true;
   }

#endif // _QX_NO_JSON

};

} // namespace qx

#endif // _QX_MODEL_H_
