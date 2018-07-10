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
               _like, _not_like, _starts_with, _ends_with, _contains_string };

protected:

   QxSqlCompare::type m_type;

public:

   QxSqlCompare(int index, QxSqlCompare::type t);
   virtual ~QxSqlCompare();

   virtual QString toString() const;
   virtual void resolve(QSqlQuery & query) const;
   virtual void postProcess(QString & sql) const;

};

typedef boost::shared_ptr<QxSqlCompare> QxSqlCompare_ptr;

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _QX_SQL_COMPARE_H_
