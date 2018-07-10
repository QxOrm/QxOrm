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

#include <QxDao/QxSqlElement/QxSqlExpression.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlExpression::QxSqlExpression(int index, QxSqlExpression::type t) : IxSqlElement(index), m_type(t) { ; }

QxSqlExpression::~QxSqlExpression() { ; }

QString QxSqlExpression::toString() const
{
   QString sReturn;

   switch (m_type)
   {
      case _where:               sReturn = "WHERE";   break;
      case _and:                 sReturn = "AND";     break;
      case _or:                  sReturn = "OR";      break;
      case _open_parenthesis:    sReturn = "(";       break;
      case _close_parenthesis:   sReturn = ")";       break;
      default:                   qAssert(false);
   }

   return sReturn;
}

void QxSqlExpression::resolve(QSqlQuery & query) const { Q_UNUSED(query); }

void QxSqlExpression::postProcess(QString & sql) const { Q_UNUSED(sql); }

} // namespace detail
} // namespace dao
} // namespace qx
