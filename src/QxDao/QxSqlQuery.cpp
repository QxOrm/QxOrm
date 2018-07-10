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

#include <QxDao/QxSqlQuery.h>
#include <QxDao/QxSqlDatabase.h>

#include <QxCollection/QxCollectionIterator.h>

#include <QxMemLeak/mem_leak.h>

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
