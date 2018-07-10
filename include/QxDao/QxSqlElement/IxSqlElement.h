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
