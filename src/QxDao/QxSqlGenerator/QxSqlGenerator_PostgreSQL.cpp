/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#include <QxPrecompiled.h>

#include <QxDao/QxSqlGenerator/QxSqlGenerator_PostgreSQL.h>

#include <QxDao/QxSqlDatabase.h>
#include <QxDao/IxDao_Helper.h>

#include <QxRegister/QxClassX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlGenerator_PostgreSQL::QxSqlGenerator_PostgreSQL() : QxSqlGenerator_Standard() { this->initSqlTypeByClassName(); }

QxSqlGenerator_PostgreSQL::~QxSqlGenerator_PostgreSQL() { ; }

void QxSqlGenerator_PostgreSQL::onBeforeInsert(IxDao_Helper * pDaoHelper, void * pOwner) const
{
   if (! pDaoHelper || ! pOwner) { qAssert(false); return; }
   if (! pDaoHelper->getDataId()) { return; }
   qx::IxDataMember * pId = pDaoHelper->getDataId();
   if (! pId->getAutoIncrement()) { return; }
   if (pId->getNameCount() > 1) { qAssert(false); return; }
   QString sql = pDaoHelper->sql();
   QString sqlToAdd = " RETURNING " + pId->getName();
   if (sql.right(sqlToAdd.size()) == sqlToAdd) { return; }
   sql += sqlToAdd;
   pDaoHelper->builder().setSqlQuery(sql);
   pDaoHelper->query().prepare(sql);
}

void QxSqlGenerator_PostgreSQL::onAfterInsert(IxDao_Helper * pDaoHelper, void * pOwner) const
{
   if (! pDaoHelper || ! pOwner) { qAssert(false); return; }
   if (! pDaoHelper->getDataId()) { return; }
   qx::IxDataMember * pId = pDaoHelper->getDataId();
   if (! pId->getAutoIncrement()) { return; }
   if (pId->getNameCount() > 1) { qAssert(false); return; }
   if (! pDaoHelper->nextRecord()) { qAssert(false); return; }
   QVariant vId = pDaoHelper->query().value(0);
   pId->fromVariant(pOwner, vId);
}

void QxSqlGenerator_PostgreSQL::initSqlTypeByClassName() const
{
   QHash<QString, QString> * lstSqlType = qx::QxClassX::getAllSqlTypeByClassName();
   if (! lstSqlType) { qAssert(false); return; }

   lstSqlType->insert("bool", "BOOLEAN");
   lstSqlType->insert("qx_bool", "BOOLEAN");
   lstSqlType->insert("short", "SMALLINT");
   lstSqlType->insert("int", "INTEGER");
   lstSqlType->insert("long", "INTEGER");
   lstSqlType->insert("long long", "BIGINT");
   lstSqlType->insert("float", "FLOAT");
   lstSqlType->insert("double", "FLOAT");
   lstSqlType->insert("long double", "FLOAT");
   lstSqlType->insert("unsigned short", "SMALLINT");
   lstSqlType->insert("unsigned int", "INTEGER");
   lstSqlType->insert("unsigned long", "INTEGER");
   lstSqlType->insert("unsigned long long", "BIGINT");
   lstSqlType->insert("std::string", "TEXT");
   lstSqlType->insert("std::wstring", "TEXT");
   lstSqlType->insert("QString", "TEXT");
   lstSqlType->insert("QVariant", "TEXT");
   lstSqlType->insert("QUuid", "TEXT");
   lstSqlType->insert("QDate", "DATE");
   lstSqlType->insert("QTime", "TIME");
   lstSqlType->insert("QDateTime", "TIMESTAMP");
   lstSqlType->insert("QByteArray", "BYTEA");
   lstSqlType->insert("qx::QxDateNeutral", "TEXT");
   lstSqlType->insert("qx::QxTimeNeutral", "TEXT");
   lstSqlType->insert("qx::QxDateTimeNeutral", "TEXT");
}

} // namespace detail
} // namespace dao
} // namespace qx
