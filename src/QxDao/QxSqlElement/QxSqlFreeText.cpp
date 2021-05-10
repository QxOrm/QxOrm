/****************************************************************************
**
** https://www.qxorm.com/
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

#include <QxDao/QxSqlElement/QxSqlFreeText.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlFreeText::QxSqlFreeText() : IxSqlElement(0) { ; }

QxSqlFreeText::QxSqlFreeText(int index) : IxSqlElement(index) { ; }

QxSqlFreeText::~QxSqlFreeText() { ; }

IxSqlElement::type_class QxSqlFreeText::getTypeClass() const { return IxSqlElement::_sql_free_text; }

QString QxSqlFreeText::toString() const { return m_sText; }

void QxSqlFreeText::resolve(QSqlQuery & query, qx::QxCollection<QString, QVariantList> * pLstExecBatch /* = NULL */) const
{
   if (m_lstValues.count() <= 0) { return; }
   qx::QxSqlDatabase::ph_style phStyle = qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle();
   bool bQuestionMark = (phStyle == qx::QxSqlDatabase::ph_style_question_mark);
   QString toFind = ((phStyle == qx::QxSqlDatabase::ph_style_2_point_name) ? QString(":") : QString("@"));
   QString txt = m_sText.trimmed();
   int posBegin = -1;
   int posEnd = -1;

   for (int i = 0; i < m_lstValues.count(); i++)
   {
      QString key = (QString("sql_free_text_") + QString::number(i));
      QVariant val(m_lstValues.at(i));
      if (! bQuestionMark)
      {
         posBegin = txt.indexOf(toFind);
         posEnd = txt.indexOf(" ", (posBegin + 1));
         if ((posEnd == -1) && (i == (m_lstValues.count() - 1))) { posEnd = txt.size(); }
         if ((posBegin == -1) || (posEnd == -1) || (posEnd <= posBegin)) { qAssert(false); break; }
         key = txt.mid(posBegin, (posEnd - posBegin)).replace(")", "");
         txt = txt.right(txt.size() - posEnd).trimmed();
      }

      if (pLstExecBatch)
      {
         if (! pLstExecBatch->exist(key)) { QVariantList empty; pLstExecBatch->insert(key, empty); }
         QVariantList & values = const_cast<QVariantList &>(pLstExecBatch->getByKey(key));
         values.append(val);
      }
      else
      {
         if (bQuestionMark) { query.addBindValue(val); }
         else { query.bindValue(key, val); }
      }
   }
}

void QxSqlFreeText::postProcess(QString & sql) const { Q_UNUSED(sql); }

QString QxSqlFreeText::getExtraSettings() const { return m_sText; }

void QxSqlFreeText::setExtraSettings(const QString & s) { m_sText = s; }

void QxSqlFreeText::setText(const QString & txt) { m_sText = txt; }

} // namespace detail
} // namespace dao
} // namespace qx
