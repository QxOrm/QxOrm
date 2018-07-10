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

#include <QxDao/QxSqlElement/QxSqlIsNull.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlIsNull::QxSqlIsNull() : IxSqlElement(0), m_type(QxSqlIsNull::_is_null) { ; }

QxSqlIsNull::QxSqlIsNull(int index, QxSqlIsNull::type t) : IxSqlElement(index), m_type(t) { ; }

QxSqlIsNull::~QxSqlIsNull() { ; }

IxSqlElement::type_class QxSqlIsNull::getTypeClass() const { return IxSqlElement::_sql_is_null; }

QString QxSqlIsNull::toString() const
{
   qAssert(m_lstColumns.count() == 1);
   QString sReturn, sColumn(m_lstColumns.at(0));
   qAssert(! sColumn.isEmpty());

   switch (m_type)
   {
      case _is_null:       sReturn = sColumn + " IS NULL";        break;
      case _is_not_null:   sReturn = sColumn + " IS NOT NULL";    break;
      default:             qAssert(false);
   }

   return sReturn;
}

void QxSqlIsNull::resolve(QSqlQuery & query) const { Q_UNUSED(query); }

void QxSqlIsNull::postProcess(QString & sql) const { Q_UNUSED(sql); }

QString QxSqlIsNull::getExtraSettings() const { return QString::number(static_cast<int>(m_type)); }

void QxSqlIsNull::setExtraSettings(const QString & s) { m_type = static_cast<QxSqlIsNull::type>(s.toInt()); }

} // namespace detail
} // namespace dao
} // namespace qx
