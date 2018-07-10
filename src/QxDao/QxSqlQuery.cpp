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

#include <QxPrecompiled.h>

#include <QxDao/QxSqlQuery.h>
#include <QxDao/QxSqlDatabase.h>

#include <QxCollection/QxCollectionIterator.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

#ifndef NDEBUG
void QxSqlQuery::verifyQuery() const
{
   if (m_sQuery.isEmpty() || (m_lstSqlElement.count() <= 0)) { return; }
   qDebug("[QxOrm] qx::QxSqlQuery::verifyQuery() : '%s'", "invalid SQL query, you cannot mix classic SQL and C++ syntax");
   qAssert(false);
}
#endif // NDEBUG

QString QxSqlQuery::query()
{
   verifyQuery();
   if (m_lstSqlElement.count() <= 0) { return m_sQuery; }
   while (m_iParenthesisCount > 0) { closeParenthesis(); }

   QString sQuery;
   for (int i = 0; i < m_lstSqlElement.count(); i++)
   { sQuery += m_lstSqlElement.at(i)->toString() + " "; }
   return sQuery;
}

bool QxSqlQuery::isEmpty() const
{
   return (m_sQuery.isEmpty() && (m_lstSqlElement.count() <= 0));
}

bool QxSqlQuery::isDistinct() const
{
   return m_bDistinct;
}

void QxSqlQuery::clear()
{
   m_sQuery = "";
   m_lstValue.clear();
   m_pSqlElementTemp.reset();
   m_lstSqlElement.clear();
   m_iSqlElementIndex = 0;
   m_iParenthesisCount = 0;
}

QxSqlQuery & QxSqlQuery::query(const QString & sQuery)
{
   if (! sQuery.isEmpty())
   { qAssert(m_lstSqlElement.count() <= 0); }

   clear();
   m_sQuery = sQuery;
   return (* this);
}

QxSqlQuery & QxSqlQuery::bind(const QVariant & vValue)
{
   verifyQuery();
   qAssert(m_lstSqlElement.count() <= 0);
   qAssert(! m_sQuery.isEmpty() && (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark));

   QString sKey = QString::number(m_lstValue.count() + 1);
   m_lstValue.insert(sKey, vValue);
   return (* this);
}

QxSqlQuery & QxSqlQuery::bind(const QString & sKey, const QVariant & vValue)
{
   verifyQuery();
   qAssert(m_lstSqlElement.count() <= 0);
   qAssert(! m_sQuery.isEmpty() && (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() != qx::QxSqlDatabase::ph_style_question_mark));

   if (sKey.isEmpty() || m_lstValue.exist(sKey)) { qAssert(false); return (* this); }
   if (! m_sQuery.contains(sKey)) { qAssert(false); return (* this); }
   m_lstValue.insert(sKey, vValue);
   return (* this);
}

void QxSqlQuery::resolve(QSqlQuery & query) const
{
   verifyQuery();
   if (m_lstSqlElement.count() > 0)
   {
      for (int i = 0; i < m_lstSqlElement.count(); i++)
      { m_lstSqlElement.at(i)->resolve(query); }
      return;
   }

   bool bKey = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() != qx::QxSqlDatabase::ph_style_question_mark);
   QxCollectionIterator<QString, QVariant> itr(m_lstValue);

   while (itr.next())
   {
      if (bKey) { query.bindValue(itr.key(), itr.value()); }
      else { query.addBindValue(itr.value()); }
   }
}

void QxSqlQuery::postProcess(QString & sql) const
{
   verifyQuery();
   for (int i = 0; i < m_lstSqlElement.count(); i++)
   { m_lstSqlElement.at(i)->postProcess(sql); }
}

QxSqlQuery & QxSqlQuery::distinct()
{
   m_bDistinct = true;
   return (* this);
}

QxSqlQuery & QxSqlQuery::where(const QString & column)
{
   return addSqlExpression(column, qx::dao::detail::QxSqlExpression::_where);
}

QxSqlQuery & QxSqlQuery::where_OpenParenthesis(const QString & column)
{
   where(column);
   return openParenthesis();
}

QxSqlQuery & QxSqlQuery::and_(const QString & column)
{
   return addSqlExpression(column, qx::dao::detail::QxSqlExpression::_and);
}

QxSqlQuery & QxSqlQuery::and_OpenParenthesis(const QString & column)
{
   and_(column);
   return openParenthesis();
}

QxSqlQuery & QxSqlQuery::or_(const QString & column)
{
   return addSqlExpression(column, qx::dao::detail::QxSqlExpression::_or);
}

QxSqlQuery & QxSqlQuery::or_OpenParenthesis(const QString & column)
{
   or_(column);
   return openParenthesis();
}

QxSqlQuery & QxSqlQuery::openParenthesis()
{
   qx::dao::detail::QxSqlExpression_ptr p;
   p.reset(new qx::dao::detail::QxSqlExpression(m_iSqlElementIndex++, qx::dao::detail::QxSqlExpression::_open_parenthesis));
   m_lstSqlElement.append(p);
   m_iParenthesisCount++;
   return (* this);
}

QxSqlQuery & QxSqlQuery::closeParenthesis()
{
   if (m_iParenthesisCount <= 0) { return (* this); }
   qx::dao::detail::QxSqlExpression_ptr p;
   p.reset(new qx::dao::detail::QxSqlExpression(m_iSqlElementIndex++, qx::dao::detail::QxSqlExpression::_close_parenthesis));
   m_lstSqlElement.append(p);
   m_iParenthesisCount--;
   m_pSqlElementTemp.reset();
   return (* this);
}

QxSqlQuery & QxSqlQuery::orderAsc(const QStringList & columns)
{
   return addSqlSort(columns, qx::dao::detail::QxSqlSort::_order_asc);
}

QxSqlQuery & QxSqlQuery::orderAsc(const QString & col1)
{
   return orderAsc(QStringList() << col1);
}

QxSqlQuery & QxSqlQuery::orderAsc(const QString & col1, const QString & col2)
{
   return orderAsc(QStringList() << col1 << col2);
}

QxSqlQuery & QxSqlQuery::orderAsc(const QString & col1, const QString & col2, const QString & col3)
{
   return orderAsc(QStringList() << col1 << col2 << col3);
}

QxSqlQuery & QxSqlQuery::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4)
{
   return orderAsc(QStringList() << col1 << col2 << col3 << col4);
}

QxSqlQuery & QxSqlQuery::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5)
{
   return orderAsc(QStringList() << col1 << col2 << col3 << col4 << col5);
}

QxSqlQuery & QxSqlQuery::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6)
{
   return orderAsc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6);
}

QxSqlQuery & QxSqlQuery::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7)
{
   return orderAsc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7);
}

QxSqlQuery & QxSqlQuery::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8)
{
   return orderAsc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8);
}

QxSqlQuery & QxSqlQuery::orderAsc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9)
{
   return orderAsc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8 << col9);
}

QxSqlQuery & QxSqlQuery::orderDesc(const QStringList & columns)
{
   return addSqlSort(columns, qx::dao::detail::QxSqlSort::_order_desc);
}

QxSqlQuery & QxSqlQuery::orderDesc(const QString & col1)
{
   return orderDesc(QStringList() << col1);
}

QxSqlQuery & QxSqlQuery::orderDesc(const QString & col1, const QString & col2)
{
   return orderDesc(QStringList() << col1 << col2);
}

QxSqlQuery & QxSqlQuery::orderDesc(const QString & col1, const QString & col2, const QString & col3)
{
   return orderDesc(QStringList() << col1 << col2 << col3);
}

QxSqlQuery & QxSqlQuery::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4)
{
   return orderDesc(QStringList() << col1 << col2 << col3 << col4);
}

QxSqlQuery & QxSqlQuery::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5)
{
   return orderDesc(QStringList() << col1 << col2 << col3 << col4 << col5);
}

QxSqlQuery & QxSqlQuery::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6)
{
   return orderDesc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6);
}

QxSqlQuery & QxSqlQuery::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7)
{
   return orderDesc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7);
}

QxSqlQuery & QxSqlQuery::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8)
{
   return orderDesc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8);
}

QxSqlQuery & QxSqlQuery::orderDesc(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9)
{
   return orderDesc(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8 << col9);
}

QxSqlQuery & QxSqlQuery::groupBy(const QStringList & columns)
{
   return addSqlSort(columns, qx::dao::detail::QxSqlSort::_group_by);
}

QxSqlQuery & QxSqlQuery::groupBy(const QString & col1)
{
   return groupBy(QStringList() << col1);
}

QxSqlQuery & QxSqlQuery::groupBy(const QString & col1, const QString & col2)
{
   return groupBy(QStringList() << col1 << col2);
}

QxSqlQuery & QxSqlQuery::groupBy(const QString & col1, const QString & col2, const QString & col3)
{
   return groupBy(QStringList() << col1 << col2 << col3);
}

QxSqlQuery & QxSqlQuery::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4)
{
   return groupBy(QStringList() << col1 << col2 << col3 << col4);
}

QxSqlQuery & QxSqlQuery::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5)
{
   return groupBy(QStringList() << col1 << col2 << col3 << col4 << col5);
}

QxSqlQuery & QxSqlQuery::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6)
{
   return groupBy(QStringList() << col1 << col2 << col3 << col4 << col5 << col6);
}

QxSqlQuery & QxSqlQuery::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7)
{
   return groupBy(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7);
}

QxSqlQuery & QxSqlQuery::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8)
{
   return groupBy(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8);
}

QxSqlQuery & QxSqlQuery::groupBy(const QString & col1, const QString & col2, const QString & col3, const QString & col4, const QString & col5, const QString & col6, const QString & col7, const QString & col8, const QString & col9)
{
   return groupBy(QStringList() << col1 << col2 << col3 << col4 << col5 << col6 << col7 << col8 << col9);
}

QxSqlQuery & QxSqlQuery::limit(int rowsCount, int startRow /* = 0 */)
{
   qx::dao::detail::QxSqlLimit_ptr p;
   p.reset(new qx::dao::detail::QxSqlLimit(m_iSqlElementIndex++));
   p->setValues(QVariantList() << QVariant(startRow) << QVariant(rowsCount));
   m_lstSqlElement.append(p);
   return (* this);
}

QxSqlQuery & QxSqlQuery::like(const QString & val)
{
   return addSqlCompare(QVariant(val), qx::dao::detail::QxSqlCompare::_like);
}

QxSqlQuery & QxSqlQuery::notLike(const QString & val)
{
   return addSqlCompare(QVariant(val), qx::dao::detail::QxSqlCompare::_not_like);
}

QxSqlQuery & QxSqlQuery::startsWith(const QString & val)
{
   return addSqlCompare(QVariant(val), qx::dao::detail::QxSqlCompare::_starts_with);
}

QxSqlQuery & QxSqlQuery::endsWith(const QString & val)
{
   return addSqlCompare(QVariant(val), qx::dao::detail::QxSqlCompare::_ends_with);
}

QxSqlQuery & QxSqlQuery::containsString(const QString & val)
{
   return addSqlCompare(QVariant(val), qx::dao::detail::QxSqlCompare::_contains_string);
}

QxSqlQuery & QxSqlQuery::isEqualTo(const QVariant & val)
{
   return addSqlCompare(val, qx::dao::detail::QxSqlCompare::_is_equal_to);
}

QxSqlQuery & QxSqlQuery::isNotEqualTo(const QVariant & val)
{
   return addSqlCompare(val, qx::dao::detail::QxSqlCompare::_is_not_equal_to);
}

QxSqlQuery & QxSqlQuery::isGreaterThan(const QVariant & val)
{
   return addSqlCompare(val, qx::dao::detail::QxSqlCompare::_is_greater_than);
}

QxSqlQuery & QxSqlQuery::isGreaterThanOrEqualTo(const QVariant & val)
{
   return addSqlCompare(val, qx::dao::detail::QxSqlCompare::_is_greater_than_or_equal_to);
}

QxSqlQuery & QxSqlQuery::isLessThan(const QVariant & val)
{
   return addSqlCompare(val, qx::dao::detail::QxSqlCompare::_is_less_than);
}

QxSqlQuery & QxSqlQuery::isLessThanOrEqualTo(const QVariant & val)
{
   return addSqlCompare(val, qx::dao::detail::QxSqlCompare::_is_less_than_or_equal_to);
}

QxSqlQuery & QxSqlQuery::in(const QVariantList & values)
{
   return addSqlIn(values, qx::dao::detail::QxSqlIn::_in);
}

QxSqlQuery & QxSqlQuery::in(const QVariant & val1)
{
   return in(QVariantList() << val1);
}

QxSqlQuery & QxSqlQuery::in(const QVariant & val1, const QVariant & val2)
{
   return in(QVariantList() << val1 << val2);
}

QxSqlQuery & QxSqlQuery::in(const QVariant & val1, const QVariant & val2, const QVariant & val3)
{
   return in(QVariantList() << val1 << val2 << val3);
}

QxSqlQuery & QxSqlQuery::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4)
{
   return in(QVariantList() << val1 << val2 << val3 << val4);
}

QxSqlQuery & QxSqlQuery::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5)
{
   return in(QVariantList() << val1 << val2 << val3 << val4 << val5);
}

QxSqlQuery & QxSqlQuery::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6)
{
   return in(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6);
}

QxSqlQuery & QxSqlQuery::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7)
{
   return in(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7);
}

QxSqlQuery & QxSqlQuery::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8)
{
   return in(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7 << val8);
}

QxSqlQuery & QxSqlQuery::in(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9)
{
   return in(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7 << val8 << val9);
}

QxSqlQuery & QxSqlQuery::notIn(const QVariantList & values)
{
   return addSqlIn(values, qx::dao::detail::QxSqlIn::_not_in);
}

QxSqlQuery & QxSqlQuery::notIn(const QVariant & val1)
{
   return notIn(QVariantList() << val1);
}

QxSqlQuery & QxSqlQuery::notIn(const QVariant & val1, const QVariant & val2)
{
   return notIn(QVariantList() << val1 << val2);
}

QxSqlQuery & QxSqlQuery::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3)
{
   return notIn(QVariantList() << val1 << val2 << val3);
}

QxSqlQuery & QxSqlQuery::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4)
{
   return notIn(QVariantList() << val1 << val2 << val3 << val4);
}

QxSqlQuery & QxSqlQuery::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5)
{
   return notIn(QVariantList() << val1 << val2 << val3 << val4 << val5);
}

QxSqlQuery & QxSqlQuery::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6)
{
   return notIn(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6);
}

QxSqlQuery & QxSqlQuery::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7)
{
   return notIn(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7);
}

QxSqlQuery & QxSqlQuery::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8)
{
   return notIn(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7 << val8);
}

QxSqlQuery & QxSqlQuery::notIn(const QVariant & val1, const QVariant & val2, const QVariant & val3, const QVariant & val4, const QVariant & val5, const QVariant & val6, const QVariant & val7, const QVariant & val8, const QVariant & val9)
{
   return notIn(QVariantList() << val1 << val2 << val3 << val4 << val5 << val6 << val7 << val8 << val9);
}

QxSqlQuery & QxSqlQuery::in_Select(const QString & sql)
{
   return addSqlIn(QVariantList() << QVariant(sql), qx::dao::detail::QxSqlIn::_in_select);
}

QxSqlQuery & QxSqlQuery::notIn_Select(const QString & sql)
{
   return addSqlIn(QVariantList() << QVariant(sql), qx::dao::detail::QxSqlIn::_not_in_select);
}

QxSqlQuery & QxSqlQuery::isNull()
{
   return addSqlIsNull(qx::dao::detail::QxSqlIsNull::_is_null);
}

QxSqlQuery & QxSqlQuery::isNotNull()
{
   return addSqlIsNull(qx::dao::detail::QxSqlIsNull::_is_not_null);
}

QxSqlQuery & QxSqlQuery::isBetween(const QVariant & val1, const QVariant & val2)
{
   return addSqlIsBetween(val1, val2, qx::dao::detail::QxSqlIsBetween::_is_between);
}

QxSqlQuery & QxSqlQuery::isNotBetween(const QVariant & val1, const QVariant & val2)
{
   return addSqlIsBetween(val1, val2, qx::dao::detail::QxSqlIsBetween::_is_not_between);
}

QxSqlQuery & QxSqlQuery::freeText(const QString & text)
{
   if (text.isEmpty()) { return (* this); }
   qx::dao::detail::QxSqlFreeText_ptr p;
   p.reset(new qx::dao::detail::QxSqlFreeText(m_iSqlElementIndex++));
   p->setValue(QVariant(text));
   m_lstSqlElement.append(p);
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlExpression(const QString & column, qx::dao::detail::QxSqlExpression::type type)
{
   qx::dao::detail::QxSqlExpression_ptr p;
   p.reset(new qx::dao::detail::QxSqlExpression(m_iSqlElementIndex++, type));
   m_lstSqlElement.append(p);

   m_pSqlElementTemp.reset(new qx::dao::detail::QxSqlElementTemp());
   m_pSqlElementTemp->setColumn(column);
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlCompare(const QVariant & val, qx::dao::detail::QxSqlCompare::type type)
{
   if (! m_pSqlElementTemp)
   { qDebug("[QxOrm] qx::QxSqlQuery : '%s'", "invalid SQL query, need a column name"); qAssert(false); return (* this); }

   qx::dao::detail::QxSqlCompare_ptr p;
   p.reset(new qx::dao::detail::QxSqlCompare(m_iSqlElementIndex++, type));
   p->clone(m_pSqlElementTemp.get());
   p->setValue(val);

   m_lstSqlElement.append(p);
   m_pSqlElementTemp.reset();
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlSort(const QStringList & columns, qx::dao::detail::QxSqlSort::type type)
{
   qx::dao::detail::QxSqlSort_ptr p;
   p.reset(new qx::dao::detail::QxSqlSort(m_iSqlElementIndex++, type));
   p->setColumns(columns);
   m_lstSqlElement.append(p);
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlIn(const QVariantList & values, qx::dao::detail::QxSqlIn::type type)
{
   if (! m_pSqlElementTemp)
   { qDebug("[QxOrm] qx::QxSqlQuery : '%s'", "invalid SQL query, need a column name"); qAssert(false); return (* this); }

   qx::dao::detail::QxSqlIn_ptr p;
   p.reset(new qx::dao::detail::QxSqlIn(m_iSqlElementIndex++, type));
   p->clone(m_pSqlElementTemp.get());
   p->setValues(values);

   m_lstSqlElement.append(p);
   m_pSqlElementTemp.reset();
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlIsNull(qx::dao::detail::QxSqlIsNull::type type)
{
   if (! m_pSqlElementTemp)
   { qDebug("[QxOrm] qx::QxSqlQuery : '%s'", "invalid SQL query, need a column name"); qAssert(false); return (* this); }

   qx::dao::detail::QxSqlIsNull_ptr p;
   p.reset(new qx::dao::detail::QxSqlIsNull(m_iSqlElementIndex++, type));
   p->clone(m_pSqlElementTemp.get());

   m_lstSqlElement.append(p);
   m_pSqlElementTemp.reset();
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlIsBetween(const QVariant & val1, const QVariant & val2, qx::dao::detail::QxSqlIsBetween::type type)
{
   if (! m_pSqlElementTemp)
   { qDebug("[QxOrm] qx::QxSqlQuery : '%s'", "invalid SQL query, need a column name"); qAssert(false); return (* this); }

   qx::dao::detail::QxSqlIsBetween_ptr p;
   p.reset(new qx::dao::detail::QxSqlIsBetween(m_iSqlElementIndex++, type));
   p->clone(m_pSqlElementTemp.get());
   p->setValues(QVariantList() << val1 << val2);

   m_lstSqlElement.append(p);
   m_pSqlElementTemp.reset();
   return (* this);
}

} // namespace qx
