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

#ifndef _IX_REPOSITORY_H_
#define _IX_REPOSITORY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxRepository.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Common interface for all repositories to provide access to database by introspection using QObject class or qx::IxCollection class
 */

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqldriver.h>

#include <QxCommon/QxBool.h>

#include <QxDao/QxSqlQuery.h>

#include <QxCollection/IxCollection.h>

namespace qx {

class IxClass;
class QxSession;

/*!
 * \ingroup QxDao
 * \brief qx::IxRepository : common interface for all repositories to provide access to database by introspection using QObject class or qx::IxCollection class
 *
 * There is a type verification at runtime using <i>dynamic_cast</i> function.
 * For example, if you are working with a class named <i>MyType</i>, you can call all methods of <i>qx::IxRepository</i> interface using :
 * - <i>MyType *</i> for a single object, if <i>MyType</i> inherits from <i>QObject</i> ;
 * - <i>qx::QxCollection< Key, QSharedPointer<MyType> > *</i> for a list of objects, where <i>Key</i> is the primary key type defined for <i>MyType</i> class (<i>long</i> by default).
 *
 * Note : if a bad type is detected at runtime, an exception of type <i>qx::dao::sql_error</i> is thrown.
 */
class QX_DLL_EXPORT IxRepository
{

protected:

   bool m_bRegister;             //!< Register repository into QxRepositoryX collection
   QString m_sKeyRepository;     //!< Repository key used by QxRepositoryX collection
   QSqlDatabase m_database;      //!< Database connection associated to the repository
   QxSession * m_pSession;       //!< Session associated to the repository

public:

   IxRepository(bool bRegister, const QString & sKey);
   IxRepository(bool bRegister, const QString & sKey, const QSqlDatabase & database);
   IxRepository(bool bRegister, const QString & sKey, QxSession * pSession);
   virtual ~IxRepository();

   QSqlDatabase * database();
   QxSession * session() const;

   virtual long _count(const qx::QxSqlQuery & query = qx::QxSqlQuery()) = 0;
   virtual void * _fetchById(const QVariant & id, const QStringList & columns = QStringList(), const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _fetchById(QObject * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _fetchById(qx::IxCollection * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _fetchAll(QObject * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _fetchAll(qx::IxCollection * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _fetchByQuery(const qx::QxSqlQuery & query, QObject * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _fetchByQuery(const qx::QxSqlQuery & query, qx::IxCollection * p, const QStringList & columns = QStringList(), const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _insert(QObject * p, const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _insert(qx::IxCollection * p, const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _update(QObject * p, const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _update(qx::IxCollection * p, const qx::QxSqlQuery & query = qx::QxSqlQuery(), const QStringList & columns = QStringList(), const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _save(QObject * p, const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _save(qx::IxCollection * p, const QStringList & relation = QStringList()) = 0;
   virtual QSqlError _deleteById(const QVariant & id) = 0;
   virtual QSqlError _deleteById(QObject * p) = 0;
   virtual QSqlError _deleteById(qx::IxCollection * p) = 0;
   virtual QSqlError _deleteAll() = 0;
   virtual QSqlError _deleteByQuery(const qx::QxSqlQuery & query) = 0;
   virtual QSqlError _destroyById(const QVariant & id) = 0;
   virtual QSqlError _destroyById(QObject * p) = 0;
   virtual QSqlError _destroyById(qx::IxCollection * p) = 0;
   virtual QSqlError _destroyAll() = 0;
   virtual QSqlError _destroyByQuery(const qx::QxSqlQuery & query) = 0;
   virtual qx_bool _exist(QObject * p) = 0;
   virtual qx_bool _exist(qx::IxCollection * p) = 0;
   virtual qx::IxCollection_ptr _newCollection() const = 0;
   virtual qx::IxClass * _getClass() const = 0;

public:

   static qx::IxCollection_ptr _fetchAll(const QString & repositoryKey, const QStringList & columns = QStringList(), const QStringList & relation = QStringList());
   static qx::IxCollection_ptr _fetchByQuery(const QString & repositoryKey, const qx::QxSqlQuery & query, const QStringList & columns = QStringList(), const QStringList & relation = QStringList());

};

} // namespace qx

#endif // _IX_REPOSITORY_H_
