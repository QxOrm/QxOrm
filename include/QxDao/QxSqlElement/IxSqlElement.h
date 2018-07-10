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

#ifndef _IX_SQL_ELEMENT_H_
#define _IX_SQL_ELEMENT_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxSqlElement.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Common interface for all SQL elements to build SQL query
 */

#include <QtSql/qsqlquery.h>

#include <QxDao/QxSqlGenerator/IxSqlGenerator.h>

namespace qx {
namespace dao {
namespace detail {

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::IxSqlElement : common interface for all SQL elements to build SQL query
 */
class QX_DLL_EXPORT IxSqlElement
{

protected:

   int               m_iIndex;            //!< Index of SQL element to build unique string
   QStringList       m_lstColumns;        //!< List of columns associated to SQL element
   QStringList       m_lstKeys;           //!< List of keys associated to SQL element
   QVariantList      m_lstValues;         //!< List of values associated to SQL element
   IxSqlGenerator *  m_pSqlGenerator;     //!< SQL generator to build SQL query specific for each database

public:

   IxSqlElement(int index);
   virtual ~IxSqlElement();

   void setColumn(const QString & column);
   void setColumns(const QStringList & columns);
   void setValue(const QVariant & val);
   void setValues(const QVariantList & values);

   virtual QString toString() const = 0;
   virtual void resolve(QSqlQuery & query) const = 0;
   virtual void postProcess(QString & sql) const = 0;

   virtual void clone(IxSqlElement * other);

protected:

   void updateKeys();

};

typedef boost::shared_ptr<IxSqlElement> IxSqlElement_ptr;

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _IX_SQL_ELEMENT_H_
