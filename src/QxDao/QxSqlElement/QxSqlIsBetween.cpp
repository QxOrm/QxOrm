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

#include <QxDao/QxSqlElement/QxSqlIsBetween.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlIsBetween::QxSqlIsBetween() : IxSqlElement(0), m_type(QxSqlIsBetween::_is_between) { ; }

QxSqlIsBetween::QxSqlIsBetween(int index, QxSqlIsBetween::type t) : IxSqlElement(index), m_type(t) { ; }

QxSqlIsBetween::~QxSqlIsBetween() { ; }

IxSqlElement::type_class QxSqlIsBetween::getTypeClass() const { return IxSqlElement::_sql_is_between; }

QString QxSqlIsBetween::toString() const
{
   qAssert((m_lstColumns.count() == 1) && (m_lstKeys.count() == 1));
   QString sReturn, sColumn(m_lstColumns.at(0)), sKey(m_lstKeys.at(0));
   qAssert(! sColumn.isEmpty() && ! sKey.isEmpty());
   bool bQuestionMark = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark);
   QString sKey1(bQuestionMark ? QString("?") : (sKey + "_1")), sKey2(bQuestionMark ? QString("?") : (sKey + "_2"));

   switch (m_type)
   {
      case _is_between:       sReturn = sColumn + " BETWEEN " + sKey1 + " AND " + sKey2;        break;
      case _is_not_between:   sReturn = sColumn + " NOT BETWEEN " + sKey1 + " AND " + sKey2;    break;
      default:                qAssert(false);
   }

   return sReturn;
}

void QxSqlIsBetween::resolve(QSqlQuery & query) const
{
   qAssert((m_lstKeys.count() == 1) && (m_lstValues.count() == 2));
   bool bQuestionMark = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark);
   QString sKey1(bQuestionMark ? QString("?") : (m_lstKeys.at(0) + "_1")), sKey2(bQuestionMark ? QString("?") : (m_lstKeys.at(0) + "_2"));
   QVariant vValue1(m_lstValues.at(0)), vValue2(m_lstValues.at(1));

   if (bQuestionMark) { query.addBindValue(vValue1); query.addBindValue(vValue2); }
   else { query.bindValue(sKey1, vValue1); query.bindValue(sKey2, vValue2); }
}

void QxSqlIsBetween::postProcess(QString & sql) const { Q_UNUSED(sql); }

QString QxSqlIsBetween::getExtraSettings() const { return QString::number(static_cast<int>(m_type)); }

void QxSqlIsBetween::setExtraSettings(const QString & s) { m_type = static_cast<QxSqlIsBetween::type>(s.toInt()); }

} // namespace detail
} // namespace dao
} // namespace qx
