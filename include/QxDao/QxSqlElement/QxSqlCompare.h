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

#ifndef _QX_SQL_COMPARE_H_
#define _QX_SQL_COMPARE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlCompare.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief SQL element to compare value (==, <, >, <=, >=, LIKE, NOT LIKE, etc.)
 */

#include <QxDao/QxSqlElement/IxSqlElement.h>

namespace qx {
namespace dao {
namespace detail {

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::QxSqlCompare : SQL element to compare value (==, <, >, <=, >=, LIKE, NOT LIKE, etc.)
 */
class QX_DLL_EXPORT QxSqlCompare : public IxSqlElement
{

public:

   enum type { _is_equal_to, _is_not_equal_to, _is_greater_than, 
               _is_greater_than_or_equal_to, _is_less_than, _is_less_than_or_equal_to, 
               _like, _not_like, _starts_with, _ends_with, _contains_string, _custom_operator };

protected:

   QxSqlCompare::type m_type;    //!< Compare type
   QString m_sCustomOperator;    //!< Possibility to define a custom operator with enum _custom_operator (for example <@ for PostgreSQL ltree type)

public:

   QxSqlCompare();
   QxSqlCompare(int index, QxSqlCompare::type t, const QString & sCustomOperator = QString());
   virtual ~QxSqlCompare();

   virtual QString toString() const;
   virtual void resolve(QSqlQuery & query) const;
   virtual void postProcess(QString & sql) const;

   virtual IxSqlElement::type_class getTypeClass() const;

protected:

   virtual QString getExtraSettings() const;
   virtual void setExtraSettings(const QString & s);

};

typedef qx_shared_ptr<QxSqlCompare> QxSqlCompare_ptr;

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _QX_SQL_COMPARE_H_
