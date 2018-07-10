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

#include <QxPrecompiled.h>

#include <QxDao/QxSqlRelationParams.h>
#include <QxDao/QxSqlRelationLinked.h>
#include <QxDao/IxSqlQueryBuilder.h>
#include <QxDao/IxSqlRelation.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QxSqlRelationParams::QxSqlRelationParams() : m_lIndex(0), m_lIndexOwner(0), m_lOffset(0), m_sql(NULL), m_builder(NULL), m_query(NULL), m_database(NULL), m_pOwner(NULL), m_eJoinType(qx::dao::sql_join::no_join), m_pRelationX(NULL), m_eSaveMode(qx::dao::save_mode::e_check_insert_or_update), m_bRecursiveMode(false), m_pColumns(NULL) { ; }

QxSqlRelationParams::QxSqlRelationParams(long lIndex, long lOffset, QString * sql, IxSqlQueryBuilder * builder, QSqlQuery * query, void * pOwner) : m_lIndex(lIndex), m_lIndexOwner(0), m_lOffset(lOffset), m_sql(sql), m_builder(builder), m_query(query), m_database(NULL), m_pOwner(pOwner), m_eJoinType(qx::dao::sql_join::no_join), m_pRelationX(NULL), m_eSaveMode(qx::dao::save_mode::e_check_insert_or_update), m_bRecursiveMode(false), m_pColumns(NULL) { ; }

QxSqlRelationParams::QxSqlRelationParams(long lIndex, long lOffset, QString * sql, IxSqlQueryBuilder * builder, QSqlQuery * query, void * pOwner, const QVariant & vId) : m_vId(vId), m_lIndex(lIndex), m_lIndexOwner(0), m_lOffset(lOffset), m_sql(sql), m_builder(builder), m_query(query), m_database(NULL), m_pOwner(pOwner), m_eJoinType(qx::dao::sql_join::no_join), m_pRelationX(NULL), m_eSaveMode(qx::dao::save_mode::e_check_insert_or_update), m_bRecursiveMode(false), m_pColumns(NULL) { ; }

QxSqlRelationParams::~QxSqlRelationParams() { ; }

} // namespace qx
