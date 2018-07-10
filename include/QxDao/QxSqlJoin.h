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

#ifndef _QX_SQL_JOIN_H_
#define _QX_SQL_JOIN_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlJoin.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Define how to join 2 tables into SQL query (LEFT OUTER JOIN, INNER JOIN, etc...)
 */

#define QX_LEFT_OUTER_JOIN    QString("->")
#define QX_INNER_JOIN         QString(">>")

namespace qx {
namespace dao {

/*!
 * \ingroup QxDao
 * \brief qx::dao::sql_join : define how to join 2 tables into SQL query (LEFT OUTER JOIN, INNER JOIN, etc...)
 */
struct sql_join
{

   enum join_type
   {
      no_join,
      left_outer_join,
      inner_join
   };

};

} // namespace dao
} // namespace qx

#endif // _QX_SQL_JOIN_H_
