/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#include "../../include/QxPrecompiled.h"

#include "../../include/QxDao/QxSqlQuery.h"
#include "../../include/QxDao/QxSqlDatabase.h"

#include "../../include/QxCollection/QxCollectionIterator.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {

QxSqlQuery & QxSqlQuery::query(const QString & sQuery)
{
   m_sQuery = sQuery;
   m_lstValue.clear();

   return (* this);
}

QxSqlQuery & QxSqlQuery::bind(const QVariant & vValue)
{
   qAssert(! m_sQuery.isEmpty() && (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark));
   QString sKey = QString::number(m_lstValue.count() + 1);
   m_lstValue.insert(sKey, vValue);

   return (* this);
}

QxSqlQuery & QxSqlQuery::bind(const QString & sKey, const QVariant & vValue)
{
   qAssert(! m_sQuery.isEmpty() && (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() != qx::QxSqlDatabase::ph_style_question_mark));
   if (sKey.isEmpty() || m_lstValue.exist(sKey)) { qAssert(false); return (* this); }
   if (! m_sQuery.contains(sKey)) { qAssert(false); return (* this); }
   m_lstValue.insert(sKey, vValue);

   return (* this);
}

void QxSqlQuery::resolve(QSqlQuery & query) const
{
   bool bKey = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() != qx::QxSqlDatabase::ph_style_question_mark);
   QxCollectionIterator<QString, QVariant> itr(m_lstValue);

   while (itr.next())
   {
      if (bKey) { query.bindValue(itr.key(), itr.value()); }
      else { query.addBindValue(itr.value()); }
   }
}

} // namespace qx
