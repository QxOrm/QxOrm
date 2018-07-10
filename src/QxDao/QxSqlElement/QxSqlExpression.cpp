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

#include <QxDao/QxSqlElement/QxSqlExpression.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlExpression::QxSqlExpression() : IxSqlElement(0), m_type(QxSqlExpression::_where) { ; }

QxSqlExpression::QxSqlExpression(int index, QxSqlExpression::type t) : IxSqlElement(index), m_type(t) { ; }

QxSqlExpression::~QxSqlExpression() { ; }

IxSqlElement::type_class QxSqlExpression::getTypeClass() const { return IxSqlElement::_sql_expression; }

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

QString QxSqlExpression::getExtraSettings() const { return QString::number(static_cast<int>(m_type)); }

void QxSqlExpression::setExtraSettings(const QString & s) { m_type = static_cast<QxSqlExpression::type>(s.toInt()); }

} // namespace detail
} // namespace dao
} // namespace qx
