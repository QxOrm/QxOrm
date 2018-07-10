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

#include <QxDao/QxSqlElement/QxSqlSort.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlSort::QxSqlSort() : IxSqlElement(0), m_type(QxSqlSort::_order_asc) { ; }

QxSqlSort::QxSqlSort(int index, QxSqlSort::type t) : IxSqlElement(index), m_type(t) { ; }

QxSqlSort::~QxSqlSort() { ; }

IxSqlElement::type_class QxSqlSort::getTypeClass() const { return IxSqlElement::_sql_sort; }

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

QString QxSqlSort::getExtraSettings() const { return QString::number(static_cast<int>(m_type)); }

void QxSqlSort::setExtraSettings(const QString & s) { m_type = static_cast<QxSqlSort::type>(s.toInt()); }

} // namespace detail
} // namespace dao
} // namespace qx
