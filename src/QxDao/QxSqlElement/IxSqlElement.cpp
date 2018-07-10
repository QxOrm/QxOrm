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

#include <QxDao/QxSqlElement/IxSqlElement.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

IxSqlElement::IxSqlElement(int index) : m_iIndex(index), m_pSqlGenerator(NULL)
{
   m_pSqlGenerator = qx::QxSqlDatabase::getSingleton()->getSqlGenerator();
   qAssert((m_iIndex >= 0) && (m_pSqlGenerator != NULL));
}

IxSqlElement::~IxSqlElement() { ; }

void IxSqlElement::setColumn(const QString & column)
{
   m_lstColumns.clear();
   m_lstColumns.append(column);
   updateKeys();
}

void IxSqlElement::setColumns(const QStringList & columns)
{
   m_lstColumns.clear();
   m_lstColumns = columns;
   updateKeys();
}

void IxSqlElement::setValue(const QVariant & val)
{
   m_lstValues.clear();
   m_lstValues.append(val);
}

void IxSqlElement::setValues(const QVariantList & values)
{
   m_lstValues.clear();
   m_lstValues = values;
}

void IxSqlElement::clone(IxSqlElement * other)
{
   if (! other) { return; }
   m_lstColumns = other->m_lstColumns;
   m_lstValues = other->m_lstValues;
   updateKeys();
}

void IxSqlElement::updateKeys()
{
   m_lstKeys.clear();
   for (int i = 0; i < m_lstColumns.count(); i++)
   {
      QString sColumn = m_lstColumns.at(i);
      QString sKey = sColumn.replace(".", "_") + "_" + QString::number(m_iIndex) + "_" + QString::number(i);
      if (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark) { sKey = "?"; }
      else if (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_at_name) { sKey = QString("@") + sKey; }
      else { sKey = QString(":") + sKey; }
      m_lstKeys.append(sKey);
   }
}

} // namespace detail
} // namespace dao
} // namespace qx
