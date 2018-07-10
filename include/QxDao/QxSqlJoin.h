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
