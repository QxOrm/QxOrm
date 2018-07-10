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

#ifndef _QX_SQL_QUERY_HELPER_H_
#define _QX_SQL_QUERY_HELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/static_assert.hpp>

#include <QtSql/qsqlquery.h>

#include "../../include/QxDao/IxSqlQueryBuilder.h"

#include "../../include/QxDataMember/IxDataMember.h"

#include "../../include/QxTraits/is_qx_registered.h"

namespace qx {
namespace dao {
namespace detail {

template <class T> struct QxSqlQueryHelper_CreateTable;
template <class T> struct QxSqlQueryHelper_DeleteById;
template <class T> struct QxSqlQueryHelper_Exist;
template <class T> struct QxSqlQueryHelper_FetchAll;
template <class T> struct QxSqlQueryHelper_FetchAll_WithRelation;
template <class T> struct QxSqlQueryHelper_FetchById;
template <class T> struct QxSqlQueryHelper_FetchById_WithRelation;
template <class T> struct QxSqlQueryHelper_Insert;
template <class T> struct QxSqlQueryHelper_Update;

} // namespace detail
} // namespace dao
} // namespace qx

#include "../../inl/QxDao/QxSqlQueryHelper_CreateTable.inl"
#include "../../inl/QxDao/QxSqlQueryHelper_DeleteById.inl"
#include "../../inl/QxDao/QxSqlQueryHelper_Exist.inl"
#include "../../inl/QxDao/QxSqlQueryHelper_FetchAll.inl"
#include "../../inl/QxDao/QxSqlQueryHelper_FetchAll_WithRelation.inl"
#include "../../inl/QxDao/QxSqlQueryHelper_FetchById.inl"
#include "../../inl/QxDao/QxSqlQueryHelper_FetchById_WithRelation.inl"
#include "../../inl/QxDao/QxSqlQueryHelper_Insert.inl"
#include "../../inl/QxDao/QxSqlQueryHelper_Update.inl"

#endif // _QX_SQL_QUERY_HELPER_H_
