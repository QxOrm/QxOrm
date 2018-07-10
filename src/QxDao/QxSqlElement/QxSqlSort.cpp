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

#include <QxDao/QxSqlElement/QxSqlSort.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlSort::QxSqlSort(int index, QxSqlSort::type t) : IxSqlElement(index), m_type(t) { ; }

QxSqlSort::~QxSqlSort() { ; }

QString QxSqlSort::toString() const
{
   qAssert(m_lstColumns.count() >= 1);
   QString sReturn;

   switch (m_type)
   {
      case _order_asc:     sReturn = "ORDER BY ";     break;
      case _order_desc:    sReturn = "ORDER BY ";     break;
      case _group_by:      sReturn = "GROUP BY ";     break;
      default:             qAssert(false);
   }

   for (int i = 0; i < m_lstColumns.count(); i++)
   {
      sReturn += ((i == 0) ? QString("") : QString(", "));
      QString sColumn = m_lstColumns.at(i);
      qAssert(! sColumn.isEmpty());

      switch (m_type)
      {
         case _order_asc:     sReturn += sColumn + " ASC";     break;
         case _order_desc:    sReturn += sColumn + " DESC";    break;
         case _group_by:      sReturn += sColumn;              break;
      }
   }

   return sReturn;
}

void QxSqlSort::resolve(QSqlQuery & query) const { Q_UNUSED(query); }

void QxSqlSort::postProcess(QString & sql) const { Q_UNUSED(sql); }

} // namespace detail
} // namespace dao
} // namespace qx
