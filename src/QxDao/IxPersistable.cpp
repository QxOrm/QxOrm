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

#include <QxPrecompiled.h>

#include <QxDao/IxPersistable.h>
#include <QxDao/QxSqlError.h>

#include <QxFactory/QxFactoryX.h>

#include <QxRegister/QxClassX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxPersistable::IxPersistable() { ; }

IxPersistable::~IxPersistable() { ; }

qx::IxCollection_ptr IxPersistable::qxFetchAll(const QString & className, const QStringList & columns /* = QStringList() */, const QStringList & relation /* = QStringList() */, QSqlDatabase * pDatabase /* = NULL */)
{
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return qx::IxCollection_ptr(); }
   qx::IxPersistable_ptr ptr = qx::IxPersistable_ptr(static_cast<qx::IxPersistable *>(qx::create_void_ptr(className)));
   if (! ptr) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxPersistable::qxFetchAll() : 'invalid classname, unable to create a new instance'", "", QSqlError::UnknownError)); }
   qx::IxCollection_ptr lst = ptr->qxNewPersistableCollection();
   if (! lst) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxPersistable::qxFetchAll() : 'unable to create a new persistable collection'", "", QSqlError::UnknownError)); }
   QSqlError daoError = ptr->qxFetchAll((* lst), columns, relation, pDatabase);
   if (daoError.isValid()) { throw qx::dao::sql_error(daoError); }
   return lst;
}

qx::IxCollection_ptr IxPersistable::qxFetchByQuery(const QString & className, const qx::QxSqlQuery & query, const QStringList & columns /* = QStringList() */, const QStringList & relation /* = QStringList() */, QSqlDatabase * pDatabase /* = NULL */)
{
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return qx::IxCollection_ptr(); }
   qx::IxPersistable_ptr ptr = qx::IxPersistable_ptr(static_cast<qx::IxPersistable *>(qx::create_void_ptr(className)));
   if (! ptr) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxPersistable::qxFetchByQuery() : 'invalid classname, unable to create a new instance'", "", QSqlError::UnknownError)); }
   qx::IxCollection_ptr lst = ptr->qxNewPersistableCollection();
   if (! lst) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxPersistable::qxFetchByQuery() : 'unable to create a new persistable collection'", "", QSqlError::UnknownError)); }
   QSqlError daoError = ptr->qxFetchByQuery(query, (* lst), columns, relation, pDatabase);
   if (daoError.isValid()) { throw qx::dao::sql_error(daoError); }
   return lst;
}

qx::IxCollection_ptr IxPersistable::qxExecuteQuery(const QString & className, qx::QxSqlQuery & query, QSqlDatabase * pDatabase /* = NULL */)
{
   if (! QxClassX::implementIxPersistable(className)) { qAssert(false); return qx::IxCollection_ptr(); }
   qx::IxPersistable_ptr ptr = qx::IxPersistable_ptr(static_cast<qx::IxPersistable *>(qx::create_void_ptr(className)));
   if (! ptr) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxPersistable::qxExecuteQuery() : 'invalid classname, unable to create a new instance'", "", QSqlError::UnknownError)); }
   qx::IxCollection_ptr lst = ptr->qxNewPersistableCollection();
   if (! lst) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxPersistable::qxExecuteQuery() : 'unable to create a new persistable collection'", "", QSqlError::UnknownError)); }
   QSqlError daoError = ptr->qxExecuteQuery(query, (* lst), pDatabase);
   if (daoError.isValid()) { throw qx::dao::sql_error(daoError); }
   return lst;
}

} // namespace qx
