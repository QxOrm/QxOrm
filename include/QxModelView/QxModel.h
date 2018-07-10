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

   typedef boost::shared_ptr<T> type_ptr;
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
      beginInsertRows(QModelIndex(), row, (row + count - 1));
      for (int i = 0; i < count; ++i)
      {
         m_lManualInsertIndex--;
         type_primary_key primaryKey;
         QVariant vNewId(static_cast<qlonglong>(m_lManualInsertIndex));
         qx::cvt::from_variant(vNewId, primaryKey);
         type_ptr pItem = type_ptr(new T());
         m_model.insert(row, primaryKey, pItem);
      }
      endInsertRows();
      return true;
   }

public:

   virtual long qxCount(const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL)
   {
      return qx::dao::count<T>(query, database(pDatabase));
   }

   virtual QSqlError qxCount(long & lCount, const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL)
   {
      m_lastError = qx::dao::count<T>(lCount, query, database(pDatabase));
      return m_lastError;
   }

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

   virtual QSqlError qxFetchAll(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      clear();
      type_collection tmp;
      if (relation.count() == 0) { m_lastError = qx::dao::fetch_all(tmp, database(pDatabase), m_lstColumns); }
      else { m_lastError = qx::dao::fetch_all_with_relation(relation, tmp, database(pDatabase)); }

      beginInsertRows(QModelIndex(), 0, (tmp.count() - 1));
      m_model = tmp;
      endInsertRows();
      return m_lastError;
   }

   virtual QSqlError qxFetchByQuery(const qx::QxSqlQuery & query, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      clear();
      type_collection tmp;
      if (relation.count() == 0) { m_lastError = qx::dao::fetch_by_query(query, tmp, database(pDatabase), m_lstColumns); }
      else { m_lastError = qx::dao::fetch_by_query_with_relation(relation, query, tmp, database(pDatabase)); }

      beginInsertRows(QModelIndex(), 0, (tmp.count() - 1));
      m_model = tmp;
      endInsertRows();
      return m_lastError;
   }

   virtual QSqlError qxInsert(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      if (relation.count() == 0) { m_lastError = qx::dao::insert(m_model, database(pDatabase)); }
      else { m_lastError = qx::dao::insert_with_relation(relation, m_model, database(pDatabase)); }
      return m_lastError;
   }

   virtual QSqlError qxUpdate(const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      if (relation.count() == 0) { m_lastError = qx::dao::update_by_query(query, m_model, database(pDatabase), m_lstColumns); }
      else { m_lastError = qx::dao::update_by_query_with_relation(relation, query, m_model, database(pDatabase)); }
      return m_lastError;
   }

   virtual QSqlError qxSave(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      if (relation.count() == 0) { m_lastError = qx::dao::save(m_model, database(pDatabase)); }
      else { m_lastError = qx::dao::save_with_relation(relation, m_model, database(pDatabase)); }
      return m_lastError;
   }

   virtual QSqlError qxSaveRow(int row, const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL)
   {
      if ((row < 0) || (row >= m_model.count())) { return QSqlError(); }
      type_ptr pItem = m_model.getByIndex(row); if (! pItem) { return QSqlError(); }
      if (relation.count() == 0) { m_lastError = qx::dao::save((* pItem), database(pDatabase)); }
      else { m_lastError = qx::dao::save_with_relation(relation, (* pItem), database(pDatabase)); }
      return m_lastError;
   }

   virtual QSqlError qxDeleteById(const QVariant & id, QSqlDatabase * pDatabase = NULL)
   {
      type_ptr pItem = type_ptr(new T());
      if (! m_pDataMemberId) { qDebug("[QxOrm] problem with 'qxDeleteById()' method : '%s'", "data member id not registered"); qAssert(false); }
      if (! m_pDataMemberId) { m_lastError = QSqlError("[QxOrm] problem with 'qxDeleteById()' method : 'data member id not registered'", "", QSqlError::UnknownError); return m_lastError; }
      m_pDataMemberId->fromVariant(pItem.get(), id);
      m_lastError = qx::dao::delete_by_id((* pItem), database(pDatabase));
      return m_lastError;
   }

   virtual QSqlError qxDeleteAll(QSqlDatabase * pDatabase = NULL)
   {
      m_lastError = qx::dao::delete_all<T>(database(pDatabase));
      return m_lastError;
   }

   virtual QSqlError qxDeleteByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   {
      m_lastError = qx::dao::delete_by_query<T>(query, database(pDatabase));
      return m_lastError;
   }

   virtual QSqlError qxDestroyById(const QVariant & id, QSqlDatabase * pDatabase = NULL)
   {
      type_ptr pItem = type_ptr(new T());
      if (! m_pDataMemberId) { qDebug("[QxOrm] problem with 'qxDeleteById()' method : '%s'", "data member id not registered"); qAssert(false); }
      if (! m_pDataMemberId) { m_lastError = QSqlError("[QxOrm] problem with 'qxDeleteById()' method : 'data member id not registered'", "", QSqlError::UnknownError); return m_lastError; }
      m_pDataMemberId->fromVariant(pItem.get(), id);
      m_lastError = qx::dao::destroy_by_id((* pItem), database(pDatabase));
      return m_lastError;
   }

   virtual QSqlError qxDestroyAll(QSqlDatabase * pDatabase = NULL)
   {
      m_lastError = qx::dao::destroy_all<T>(database(pDatabase));
      return m_lastError;
   }

   virtual QSqlError qxDestroyByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   {
      m_lastError = qx::dao::destroy_by_query<T>(query, database(pDatabase));
      return m_lastError;
   }

   virtual QSqlError qxExecuteQuery(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
   {
      clear();
      type_collection tmp;
      m_lastError = qx::dao::execute_query(query, tmp, database(pDatabase));

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

};

} // namespace qx

#endif // _QX_MODEL_H_
