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

#ifndef _QX_SQL_QUERY_HELPER_H_
#define _QX_SQL_QUERY_HELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtSql/qsqlquery.h>

#include <QxDao/IxSqlQueryBuilder.h>

#include <QxDataMember/IxDataMember.h>

#include <QxTraits/is_qx_registered.h>

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
