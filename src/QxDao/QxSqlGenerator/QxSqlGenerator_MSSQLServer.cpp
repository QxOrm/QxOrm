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

#include <QxDao/QxSqlGenerator/QxSqlGenerator_MSSQLServer.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlGenerator_MSSQLServer::QxSqlGenerator_MSSQLServer() : QxSqlGenerator_Standard() { ; }

QxSqlGenerator_MSSQLServer::~QxSqlGenerator_MSSQLServer() { ; }

QString QxSqlGenerator_MSSQLServer::getLimit(const QxSqlLimit * pLimit) const { Q_UNUSED(pLimit); return ""; }

void QxSqlGenerator_MSSQLServer::resolveLimit(QSqlQuery & query, const QxSqlLimit * pLimit) const
{
   if (! pLimit) { qAssert(false); return; }
   QString sRowsCount = pLimit->getRowsCount_ParamKey();
   int iRowsCount(pLimit->getRowsCount());
   bool bQuestionMark = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark);
   if (bQuestionMark) { query.addBindValue(iRowsCount); }
   else { query.bindValue(sRowsCount, iRowsCount); }
}

void QxSqlGenerator_MSSQLServer::postProcess(QString & sql, const QxSqlLimit * pLimit) const
{
   if (! pLimit) { qAssert(false); return; }
   if (! sql.left(7).contains("SELECT ", Qt::CaseInsensitive)) { qAssert(false); return; }
   QString sRowsCount = pLimit->getRowsCount_ParamKey();
   sql = sql.right(sql.size() - 7);
   sql = "SELECT TOP " + sRowsCount + " " + sql;
}

} // namespace detail
} // namespace dao
} // namespace qx
