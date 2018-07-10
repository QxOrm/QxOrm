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

#include <QxDao/QxSqlElement/QxSqlIn.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlIn::QxSqlIn() : IxSqlElement(0), m_type(QxSqlIn::_in) { ; }

QxSqlIn::QxSqlIn(int index, QxSqlIn::type t) : IxSqlElement(index), m_type(t) { ; }

QxSqlIn::~QxSqlIn() { ; }

IxSqlElement::type_class QxSqlIn::getTypeClass() const { return IxSqlElement::_sql_in; }

QString QxSqlIn::toString() const
{
   qAssert((m_lstColumns.count() == 1) && (m_lstKeys.count() == 1) && (m_lstValues.count() >= 1));
   QString sReturn, sColumn(m_lstColumns.at(0)), sKey(m_lstKeys.at(0));
   bool bQuestionMark = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark);
   qAssert(! sColumn.isEmpty() && ! sKey.isEmpty());

   switch (m_type)
   {
      case _in:               sReturn = sColumn + " IN (";        break;
      case _not_in:           sReturn = sColumn + " NOT IN (";    break;
      case _in_select:        sReturn = sColumn + " IN (";        break;
      case _not_in_select:    sReturn = sColumn + " NOT IN (";    break;
      default:                qAssert(false);
   }

   for (int i = 0; i < m_lstValues.count(); i++)
   {
      if ((m_type == _in_select) || (m_type == _not_in_select)) { sReturn += m_lstValues.at(i).toString(); continue; }
      QString sCurrKey = (bQuestionMark ? QString("?") : (sKey + QString("_") + QString::number(i)));
      sReturn += ((i == 0) ? QString("") : QString(", "));
      sReturn += sCurrKey;
   }

   sReturn += QString(")");
   return sReturn;
}

void QxSqlIn::resolve(QSqlQuery & query) const
{
   if ((m_type == _in_select) || (m_type == _not_in_select)) { return; }
   qAssert((m_lstKeys.count() == 1) && (m_lstValues.count() >= 1));
   bool bQuestionMark = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark);
   QString sKey(m_lstKeys.at(0));

   for (int i = 0; i < m_lstValues.count(); i++)
   {
      QString sCurrKey = (bQuestionMark ? QString("?") : (sKey + QString("_") + QString::number(i)));
      QVariant vValue(m_lstValues.at(i));
      if (bQuestionMark) { query.addBindValue(vValue); }
      else { query.bindValue(sCurrKey, vValue); }
   }
}

void QxSqlIn::postProcess(QString & sql) const { Q_UNUSED(sql); }

QString QxSqlIn::getExtraSettings() const { return QString::number(static_cast<int>(m_type)); }

void QxSqlIn::setExtraSettings(const QString & s) { m_type = static_cast<QxSqlIn::type>(s.toInt()); }

} // namespace detail
} // namespace dao
} // namespace qx
