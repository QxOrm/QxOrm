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

#include <QxDao/QxSqlElement/QxSqlCompare.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlCompare::QxSqlCompare(int index, QxSqlCompare::type t) : IxSqlElement(index), m_type(t) { ; }

QxSqlCompare::~QxSqlCompare() { ; }

QString QxSqlCompare::toString() const
{
   qAssert((m_lstColumns.count() == 1) && (m_lstKeys.count() == 1));
   QString sReturn, sColumn(m_lstColumns.at(0)), sKey(m_lstKeys.at(0));
   qAssert(! sColumn.isEmpty() && ! sKey.isEmpty());

   switch (m_type)
   {
      case _is_equal_to:                     sReturn = sColumn + " = " + sKey;            break;
      case _is_not_equal_to:                 sReturn = sColumn + " <> " + sKey;           break;
      case _is_greater_than:                 sReturn = sColumn + " > " + sKey;            break;
      case _is_greater_than_or_equal_to:     sReturn = sColumn + " >= " + sKey;           break;
      case _is_less_than:                    sReturn = sColumn + " < " + sKey;            break;
      case _is_less_than_or_equal_to:        sReturn = sColumn + " <= " + sKey;           break;
      case _like:                            sReturn = sColumn + " LIKE " + sKey;         break;
      case _not_like:                        sReturn = sColumn + " NOT LIKE " + sKey;     break;
      case _starts_with:                     sReturn = sColumn + " LIKE " + sKey;         break;
      case _ends_with:                       sReturn = sColumn + " LIKE " + sKey;         break;
      case _contains_string:                 sReturn = sColumn + " LIKE " + sKey;         break;
      default:                               qAssert(false);
   }

   return sReturn;
}

void QxSqlCompare::resolve(QSqlQuery & query) const
{
   qAssert((m_lstKeys.count() == 1) && (m_lstValues.count() == 1));
   QString sKey(m_lstKeys.at(0));
   QVariant vValue(m_lstValues.at(0));

   QString sWildCard = m_pSqlGenerator->getWildCard();
   if (m_type == _starts_with) { vValue = QVariant(vValue.toString() + sWildCard); }
   else if (m_type == _ends_with) { vValue = QVariant(sWildCard + vValue.toString()); }
   else if (m_type == _contains_string) { vValue = QVariant(sWildCard + vValue.toString() + sWildCard); }

   bool bQuestionMark = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark);
   if (bQuestionMark) { query.addBindValue(vValue); }
   else { query.bindValue(sKey, vValue); }
}

void QxSqlCompare::postProcess(QString & sql) const { Q_UNUSED(sql); }

} // namespace detail
} // namespace dao
} // namespace qx
