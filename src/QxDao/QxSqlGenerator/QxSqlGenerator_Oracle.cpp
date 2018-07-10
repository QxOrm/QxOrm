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

#include <QxDao/QxSqlGenerator/QxSqlGenerator_Oracle.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlGenerator_Oracle::QxSqlGenerator_Oracle() : QxSqlGenerator_Standard() { ; }

QxSqlGenerator_Oracle::~QxSqlGenerator_Oracle() { ; }

QString QxSqlGenerator_Oracle::getLimit(const QxSqlLimit * pLimit) const { Q_UNUSED(pLimit); return ""; }

void QxSqlGenerator_Oracle::resolveLimit(QSqlQuery & query, const QxSqlLimit * pLimit) const
{
   if (! pLimit) { qAssert(false); return; }
   QString sMinRow = pLimit->getStartRow_ParamKey();
   QString sMaxRow = pLimit->getMaxRow_ParamKey();
   int iMinRow(pLimit->getStartRow()), iMaxRow(pLimit->getMaxRow());
   bool bQuestionMark = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark);
   if (bQuestionMark) { query.addBindValue(iMaxRow); query.addBindValue(iMinRow); }
   else { query.bindValue(sMaxRow, iMaxRow); query.bindValue(sMinRow, iMinRow); }
}

void QxSqlGenerator_Oracle::postProcess(QString & sql, const QxSqlLimit * pLimit) const
{
   if (! pLimit) { qAssert(false); return; }
   QString sMinRow = pLimit->getStartRow_ParamKey();
   QString sMaxRow = pLimit->getMaxRow_ParamKey();
   QString sReplace = "%SQL_QUERY%";

   QString sqlPaging;
   sqlPaging += "SELECT * FROM ";
   sqlPaging += "   ( SELECT a.*, ROWNUM rnum FROM ";
   sqlPaging += "      ( " + sReplace + " ) a ";
   sqlPaging += "     WHERE ROWNUM <= " + sMaxRow + " ) ";
   sqlPaging += "WHERE rnum >= " + sMinRow;
   sqlPaging.replace(sReplace, sql);
   sql = sqlPaging;
}

} // namespace detail
} // namespace dao
} // namespace qx
