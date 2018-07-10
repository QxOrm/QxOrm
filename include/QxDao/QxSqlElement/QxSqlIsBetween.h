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

#ifndef _QX_SQL_IS_BETWEEN_H_
#define _QX_SQL_IS_BETWEEN_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlIsBetween.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief SQL element to verify if a value is included into 2 other values
 */

#include <QxDao/QxSqlElement/IxSqlElement.h>

namespace qx {
namespace dao {
namespace detail {

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::QxSqlIsBetween : SQL element to verify if a value is included into 2 other values
 */
class QX_DLL_EXPORT QxSqlIsBetween : public IxSqlElement
{

public:

   enum type { _is_between, _is_not_between };

protected:

   QxSqlIsBetween::type m_type;

public:

   QxSqlIsBetween(int index, QxSqlIsBetween::type t);
   virtual ~QxSqlIsBetween();

   virtual QString toString() const;
   virtual void resolve(QSqlQuery & query) const;
   virtual void postProcess(QString & sql) const;

};

typedef boost::shared_ptr<QxSqlIsBetween> QxSqlIsBetween_ptr;

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _QX_SQL_IS_BETWEEN_H_
