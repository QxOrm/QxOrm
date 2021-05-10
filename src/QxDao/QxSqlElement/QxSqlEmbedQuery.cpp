/****************************************************************************
**
** https://www.qxorm.com/
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

#include <QxDao/QxSqlElement/QxSqlEmbedQuery.h>

#include <QxDao/QxSqlQuery.h>

#ifndef _QX_NO_JSON
#include <QxSerialize/QJson/QxSerializeQJson_QxSqlQuery.h>
#endif // _QX_NO_JSON

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

struct Q_DECL_HIDDEN QxSqlEmbedQuery::QxSqlEmbedQueryImpl
{

   qx::QxSqlQuery m_query;          //!< SQL sub-query to embed inside a parent SQL query
   QxSqlEmbedQuery::type m_type;    //!< Embed query type

   QxSqlEmbedQueryImpl(QxSqlEmbedQuery::type type) : m_type(type) { ; }
   ~QxSqlEmbedQueryImpl() { ; }

};

QxSqlEmbedQuery::QxSqlEmbedQuery(QxSqlEmbedQuery::type type /* = QxSqlEmbedQuery::_none */) : IxSqlElement(0), m_pImpl(new QxSqlEmbedQueryImpl(type)) { ; }

QxSqlEmbedQuery::QxSqlEmbedQuery(int index, QxSqlEmbedQuery::type type /* = QxSqlEmbedQuery::_none */) : IxSqlElement(index), m_pImpl(new QxSqlEmbedQueryImpl(type)) { ; }

QxSqlEmbedQuery::~QxSqlEmbedQuery() { ; }

IxSqlElement::type_class QxSqlEmbedQuery::getTypeClass() const { return IxSqlElement::_sql_embed_query; }

void QxSqlEmbedQuery::setQuery(const qx::QxSqlQuery & query) { m_pImpl->m_query = query; }

QString QxSqlEmbedQuery::toString() const
{
   QString result;
   QString column = m_lstColumns.at(0);
   QString sql = m_pImpl->m_query.query();
   switch (m_pImpl->m_type)
   {
      case _none:                result = sql;                                         break;
      case _in:                  result = column + " IN (" + sql + ")";                break;
      case _not_in:              result = column + " NOT IN (" + sql + ")";            break;
      case _is_equal_to:         result = column + " = (" + sql + ")";                 break;
      case _is_not_equal_to:     result = column + " <> (" + sql + ")";                break;
      default:                   qAssert(false);
   }
   return result;
}

void QxSqlEmbedQuery::resolve(QSqlQuery & query, qx::QxCollection<QString, QVariantList> * pLstExecBatch /* = NULL */) const { m_pImpl->m_query.resolve(query, pLstExecBatch); }

void QxSqlEmbedQuery::postProcess(QString & sql) const { Q_UNUSED(sql); }

QString QxSqlEmbedQuery::getExtraSettings() const
{
#ifndef _QX_NO_JSON
   return (QString::number(static_cast<int>(m_pImpl->m_type)) + "|" + qx::serialization::json::to_string(m_pImpl->m_query));
#else // _QX_NO_JSON
   return QString();
#endif // _QX_NO_JSON
}

void QxSqlEmbedQuery::setExtraSettings(const QString & s)
{
#ifndef _QX_NO_JSON
   int pos = s.indexOf("|");
   if (pos == -1) { m_pImpl->m_type = static_cast<QxSqlEmbedQuery::type>(s.toInt()); return; }
   m_pImpl->m_type = static_cast<QxSqlEmbedQuery::type>(s.left(pos).toInt());
   QString json = s.right(s.size() - (pos + 1));
   qx::serialization::json::from_string(m_pImpl->m_query, json);
#else // _QX_NO_JSON
   Q_UNUSED(s);
#endif // _QX_NO_JSON
}

} // namespace detail
} // namespace dao
} // namespace qx
