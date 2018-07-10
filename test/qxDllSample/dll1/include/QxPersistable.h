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

#ifndef _QX_PERSISTABLE_H_
#define _QX_PERSISTABLE_H_

#ifdef _MSC_VER
#pragma once
#endif

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../include/precompiled.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

namespace qx {

class QxPersistable;

namespace dao {
namespace detail {

template <>
struct QxDao_Trigger<qx::QxPersistable>;

} // namespace detail
} // namespace dao

/*!
 * \brief qx::QxPersistable : super base class for persistent classes with many features and methods to override (be careful, don't forget to use QX_PERSISTABLE_HPP() and QX_PERSISTABLE_CPP() macros for each derived class)
 */
class QX_DLL1_EXPORT QxPersistable : public QObject, public qx::IxPersistable
{

   Q_OBJECT
   QX_REGISTER_FRIEND_CLASS(qx::QxPersistable)
   QX_PERSISTABLE_HPP(qx::QxPersistable)

   Q_PROPERTY( long qxId READ qxGetId WRITE qxSetId )
   Q_PROPERTY( QDateTime qxDateCreation READ qxGetDateCreation WRITE qxSetDateCreation )
   Q_PROPERTY( QDateTime qxDateModification READ qxGetDateModification WRITE qxSetDateModification )

   friend struct qx::dao::detail::QxDao_Trigger<qx::QxPersistable>;

protected:

   long                    m_qxId;                 //!< Id of current instance stored into database
   qx::QxDateTimeNeutral   m_qxDateCreation;       //!< Creation date-time automatically calculated before INSERT query
   qx::QxDateTimeNeutral   m_qxDateModification;   //!< Modification date-time automatically calculated before INSERT and UPDATE queries

public:

   QxPersistable();
   virtual ~QxPersistable();

   long qxGetId() const;
   QDateTime qxGetDateCreation() const;
   QDateTime qxGetDateModification() const;

   void qxSetId(long l);
   void qxSetDateCreation(const QDateTime & dt);
   void qxSetDateModification(const QDateTime & dt);

protected:

   // -- List of useful protected methods to override into derived class -- //

   virtual void qxIsValid(qx::QxInvalidValueX & invalidValues);

   virtual void qxOnBeforeInsert(qx::dao::detail::IxDao_Helper * dao);
   virtual void qxOnBeforeUpdate(qx::dao::detail::IxDao_Helper * dao);
   virtual void qxOnBeforeDelete(qx::dao::detail::IxDao_Helper * dao);
   virtual void qxOnBeforeFetch(qx::dao::detail::IxDao_Helper * dao);
   virtual void qxOnAfterInsert(qx::dao::detail::IxDao_Helper * dao);
   virtual void qxOnAfterUpdate(qx::dao::detail::IxDao_Helper * dao);
   virtual void qxOnAfterDelete(qx::dao::detail::IxDao_Helper * dao);
   virtual void qxOnAfterFetch(qx::dao::detail::IxDao_Helper * dao);

private:

   void qxIsValidInternal(qx::QxInvalidValueX & invalidValues);

Q_SIGNALS:

   void qxOnBeforeInsert(qx::QxPersistable * p);
   void qxOnBeforeUpdate(qx::QxPersistable * p);
   void qxOnBeforeDelete(qx::QxPersistable * p);
   void qxOnBeforeFetch(qx::QxPersistable * p);
   void qxOnAfterInsert(qx::QxPersistable * p);
   void qxOnAfterUpdate(qx::QxPersistable * p);
   void qxOnAfterDelete(qx::QxPersistable * p);
   void qxOnAfterFetch(qx::QxPersistable * p);

public:

   // -- List of useful public methods available from 'qx::IxPersistable' interface (using QX_PERSISTABLE_HPP() and QX_PERSISTABLE_CPP() macros) -- //

/*
   virtual long qxCount(const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxFetchById(const QVariant & id = QVariant(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxFetchAll(qx::IxCollection & list, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxFetchByQuery(const qx::QxSqlQuery & query, qx::IxCollection & list, const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxInsert(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxUpdate(const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxSave(const QStringList & relation = QStringList(), QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxDeleteById(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxDeleteAll(QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxDeleteByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxDestroyById(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxDestroyAll(QSqlDatabase * pDatabase = NULL);
   virtual QSqlError qxDestroyByQuery(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL);
   virtual qx_bool qxExist(const QVariant & id = QVariant(), QSqlDatabase * pDatabase = NULL);
   virtual qx::QxInvalidValueX qxValidate(const QStringList & groups = QStringList());
   virtual qx::IxCollection_ptr qxNewPersistableCollection() const;
   virtual qx::IxClass * qxClass() const;
*/

};

typedef qx_shared_ptr<qx::QxPersistable> QxPersistable_ptr;

} // namespace qx

QX_REGISTER_COMPLEX_CLASS_NAME_HPP_QX_DLL1(qx::QxPersistable, QObject, 0, qx_QxPersistable)

namespace qx {
namespace dao {
namespace detail {

template <>
struct QxDao_Trigger<qx::QxPersistable>
{

   static inline void onBeforeInsert(qx::QxPersistable * t, qx::dao::detail::IxDao_Helper * dao)   { if (t) { t->qxOnBeforeInsert(dao); } }
   static inline void onBeforeUpdate(qx::QxPersistable * t, qx::dao::detail::IxDao_Helper * dao)   { if (t) { t->qxOnBeforeUpdate(dao); } }
   static inline void onBeforeDelete(qx::QxPersistable * t, qx::dao::detail::IxDao_Helper * dao)   { if (t) { t->qxOnBeforeDelete(dao); } }
   static inline void onBeforeFetch(qx::QxPersistable * t, qx::dao::detail::IxDao_Helper * dao)    { if (t) { t->qxOnBeforeFetch(dao); } }
   static inline void onAfterInsert(qx::QxPersistable * t, qx::dao::detail::IxDao_Helper * dao)    { if (t) { t->qxOnAfterInsert(dao); } }
   static inline void onAfterUpdate(qx::QxPersistable * t, qx::dao::detail::IxDao_Helper * dao)    { if (t) { t->qxOnAfterUpdate(dao); } }
   static inline void onAfterDelete(qx::QxPersistable * t, qx::dao::detail::IxDao_Helper * dao)    { if (t) { t->qxOnAfterDelete(dao); } }
   static inline void onAfterFetch(qx::QxPersistable * t, qx::dao::detail::IxDao_Helper * dao)     { if (t) { t->qxOnAfterFetch(dao); } }

};

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _QX_PERSISTABLE_H_
