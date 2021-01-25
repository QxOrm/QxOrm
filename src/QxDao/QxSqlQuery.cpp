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

#include <QtCore/qelapsedtimer.h>

#include <QtSql/qsqlrecord.h>

#include <QxDao/QxSqlQuery.h>
#include <QxDao/QxSqlDatabase.h>
#include <QxDao/QxMongoDB/QxMongoDB_Helper.h>

#include <QxCollection/QxCollectionIterator.h>

#include <QxSerialize/std/QxSerialize_std_tuple.h>

#include <QxSerialize/Qt/QxSerialize_QString.h>
#include <QxSerialize/Qt/QxSerialize_QVariant.h>
#include <QxSerialize/Qt/QxSerialize_QHash.h>
#include <QxSerialize/Qt/QxSerialize_QVector.h>
#include <QxSerialize/Qt/QxSerialize_QFlags.h>

#include <QxSerialize/Qx/QxSerialize_QxCollection.h>

#include <QxSerialize/QDataStream/QxSerializeQDataStream_all_include.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QxSqlQuery::QxSqlQuery() : m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false) { m_sQuery << QString(); }

QxSqlQuery::QxSqlQuery(const char * query, const QVariantList & values /* = QVariantList() */) : m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false)
{
   if (values.count() <= 0) { m_sQuery << QString(query); }
   else { addFreeText(query, values); }
}

QxSqlQuery::QxSqlQuery(const QString & query, const QVariantList & values /* = QVariantList() */) : m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false)
{
   if (values.count() <= 0) { m_sQuery << query; }
   else { addFreeText(query, values); }
}

QxSqlQuery::QxSqlQuery(const QStringList & query) : m_sQuery(query), m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false) { ; }

QxSqlQuery::QxSqlQuery(const QString & type, const QString & query) : m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false), m_sType(type) { m_sQuery << query; }

QxSqlQuery::QxSqlQuery(const QString & type, const QStringList & query) : m_sQuery(query), m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false), m_sType(type) { ; }

#ifndef _QX_NO_JSON
#ifdef Q_COMPILER_INITIALIZER_LISTS

QxSqlQuery::QxSqlQuery(std::initializer_list<QPair<QString, QJsonValue> > json) : m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false)
{
   QJsonObject obj; for (std::initializer_list<QPair<QString, QJsonValue> >::const_iterator itr = json.begin(); itr != json.end(); ++itr) { obj.insert(itr->first, itr->second); }
   QJsonDocument doc(obj); m_sQuery << QString::fromUtf8(doc.toJson());
}

QxSqlQuery::QxSqlQuery(std::initializer_list<QPair<QString, QJsonValue> > json, std::initializer_list<QPair<QString, QJsonValue> > opts) : m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false)
{
   QJsonObject obj1; for (std::initializer_list<QPair<QString, QJsonValue> >::const_iterator itr = json.begin(); itr != json.end(); ++itr) { obj1.insert(itr->first, itr->second); }
   QJsonObject obj2; for (std::initializer_list<QPair<QString, QJsonValue> >::const_iterator itr = opts.begin(); itr != opts.end(); ++itr) { obj2.insert(itr->first, itr->second); }
   QJsonDocument doc1(obj1); QJsonDocument doc2(obj2); m_sQuery << QString::fromUtf8(doc1.toJson()) << QString::fromUtf8(doc2.toJson());
}

QxSqlQuery::QxSqlQuery(const QString & type, std::initializer_list<QPair<QString, QJsonValue> > json) : m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false), m_sType(type)
{
   QJsonObject obj; for (std::initializer_list<QPair<QString, QJsonValue> >::const_iterator itr = json.begin(); itr != json.end(); ++itr) { obj.insert(itr->first, itr->second); }
   QJsonDocument doc(obj); m_sQuery << QString::fromUtf8(doc.toJson());
}

QxSqlQuery::QxSqlQuery(const QString & type, std::initializer_list<QPair<QString, QJsonValue> > json, std::initializer_list<QPair<QString, QJsonValue> > opts) : m_iSqlElementIndex(0), m_iParenthesisCount(0), m_bDistinct(false), m_sType(type)
{
   QJsonObject obj1; for (std::initializer_list<QPair<QString, QJsonValue> >::const_iterator itr = json.begin(); itr != json.end(); ++itr) { obj1.insert(itr->first, itr->second); }
   QJsonObject obj2; for (std::initializer_list<QPair<QString, QJsonValue> >::const_iterator itr = opts.begin(); itr != opts.end(); ++itr) { obj2.insert(itr->first, itr->second); }
   QJsonDocument doc1(obj1); QJsonDocument doc2(obj2); m_sQuery << QString::fromUtf8(doc1.toJson()) << QString::fromUtf8(doc2.toJson());
}

#endif // Q_COMPILER_INITIALIZER_LISTS
#endif // _QX_NO_JSON

QxSqlQuery::~QxSqlQuery() { ; }

void QxSqlQuery::verifyQuery() const
{
#ifdef _QX_MODE_DEBUG
   if (queryAt(0).isEmpty() || (m_lstSqlElement.count() <= 0)) { return; }
   qDebug("[QxOrm] qx::QxSqlQuery::verifyQuery() : '%s'", "invalid SQL query, you cannot mix classic SQL and C++ syntax");
   qAssert(false);
#endif // _QX_MODE_DEBUG
}

QString QxSqlQuery::query()
{
   verifyQuery();
   if (m_lstSqlElement.count() <= 0) { return queryAt(0); }
   while (m_iParenthesisCount > 0) { closeParenthesis(); }

   QString sQuery;
   for (int i = 0; i < m_lstSqlElement.count(); i++)
   { sQuery += m_lstSqlElement.at(i)->toString() + " "; }
   return sQuery;
}

QString QxSqlQuery::queryAt(int idx) const
{
   if ((idx < 0) || (idx >= m_sQuery.count())) { return QString(); }
   return m_sQuery.at(idx);
}

void QxSqlQuery::queryAt(int idx, const QString & query)
{
   while ((m_sQuery.count() - 1) < idx) { m_sQuery << QString(); }
   m_sQuery.replace(idx, query); qAssert(m_sQuery.at(idx) == query);
}

QVariant QxSqlQuery::response() const
{
   return m_vResponse;
}

void QxSqlQuery::setResponse(const QVariant & v)
{
   m_vResponse = v;
}

QString QxSqlQuery::type() const
{
   return m_sType;
}

void QxSqlQuery::setType(const QString & s)
{
   m_sType = s;
}

bool QxSqlQuery::isEmpty() const
{
   return (queryAt(0).isEmpty() && (m_lstSqlElement.count() <= 0) && (m_lstJoinQueryUser.count() <= 0));
}

bool QxSqlQuery::isDistinct() const
{
   return m_bDistinct;
}

void QxSqlQuery::clear()
{
   m_sQuery.clear();
   m_lstValue.clear();
   m_pSqlElementTemp.reset();
   m_lstSqlElement.clear();
   m_iSqlElementIndex = 0;
   m_iParenthesisCount = 0;
   m_vResponse = QVariant();
   m_sType = "";
   m_lstJoinQueryUser.clear();
   m_lstJoinQueryToResolve.clear();
}

QxSqlQuery & QxSqlQuery::query(const QString & sQuery)
{
   if (! sQuery.isEmpty())
   { qAssert(m_lstSqlElement.count() <= 0); }

   clear();
   m_sQuery << sQuery;
   return (* this);
}

QxSqlQuery & QxSqlQuery::bind(const QVariant & vValue, QSql::ParamType paramType /* = QSql::In */)
{
   verifyQuery();
   qAssert(m_lstSqlElement.count() <= 0);
   qAssert(! queryAt(0).isEmpty() && (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark));

   QString sKey = QString::number(m_lstValue.count() + 1);
   m_lstValue.insert(sKey, type_bind_value(vValue, paramType));
   return (* this);
}

QxSqlQuery & QxSqlQuery::bind(const QString & sKey, const QVariant & vValue, QSql::ParamType paramType /* = QSql::In */)
{
   verifyQuery();
   qAssert(m_lstSqlElement.count() <= 0);
   qAssert(! queryAt(0).isEmpty() && (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() != qx::QxSqlDatabase::ph_style_question_mark));

   if (sKey.isEmpty() || m_lstValue.exist(sKey)) { qAssert(false); return (* this); }
   if (! queryAt(0).contains(sKey)) { qAssert(false); return (* this); }
   m_lstValue.insert(sKey, type_bind_value(vValue, paramType));
   return (* this);
}

QVariant QxSqlQuery::boundValue(const QString & sKey) const
{
   if (sKey.isEmpty() || ! m_lstValue.exist(sKey)) { qAssert(false); return QVariant(); }
   return std::get<0>(m_lstValue.getByKey(sKey));
}

QVariant QxSqlQuery::boundValue(int iPosition) const
{
   if ((iPosition < 0) || (iPosition >= m_lstValue.count())) { qAssert(false); return QVariant(); }
   return std::get<0>(m_lstValue.getByIndex(iPosition));
}

void QxSqlQuery::resolve(QSqlQuery & query) const
{
   verifyQuery();

   for (int i = 0; i < m_lstJoinQueryToResolve.count(); i++)
   {
      std::shared_ptr<QxSqlQuery> joinQuery = m_lstJoinQueryToResolve.at(i);
      joinQuery->resolve(query);
   }

   if (m_lstSqlElement.count() > 0)
   {
      for (int i = 0; i < m_lstSqlElement.count(); i++)
      { m_lstSqlElement.at(i)->resolve(query); }
      return;
   }

   bool bKey = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() != qx::QxSqlDatabase::ph_style_question_mark);
   QxCollectionIterator<QString, type_bind_value> itr(m_lstValue);
   while (itr.next())
   {
      if (bKey) { query.bindValue(itr.key(), std::get<0>(itr.value()), std::get<1>(itr.value())); }
      else { query.addBindValue(std::get<0>(itr.value()), std::get<1>(itr.value())); }
   }
}

void QxSqlQuery::resolveOutput(QSqlQuery & query, bool bFetchSqlResult)
{
   QxCollection<QString, type_bind_value> lst; lst.reserve(m_lstValue.count());
   bool bKey = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() != qx::QxSqlDatabase::ph_style_question_mark);
   for (long l = 0; l < m_lstValue.count(); l++)
   {
      QVariant outputValue;
      QString key = m_lstValue.getKeyByIndex(l);
      type_bind_value val = m_lstValue.getByIndex(l);
      QSql::ParamType paramType = std::get<1>(val);
      if (paramType == QSql::In) { lst.insert(key, val); continue; }
      if (bKey) { outputValue = query.boundValue(key); }
      else { outputValue = query.boundValue(l); }
      lst.insert(key, type_bind_value(outputValue, paramType));
   }
   if (bFetchSqlResult) { fetchSqlResult(query); }
   m_lstValue = lst;
}

QString QxSqlQuery::getJoinQuery(const QString & relationKey, const QString & relationAlias)
{
   if (m_lstJoinQueryUser.contains(relationKey))
   {
      std::shared_ptr<QxSqlQuery> query = m_lstJoinQueryUser.value(relationKey);
      m_lstJoinQueryToResolve.append(query);
      return query->query().trimmed();
   }
   else if (m_lstJoinQueryUser.contains(relationAlias))
   {
      std::shared_ptr<QxSqlQuery> query = m_lstJoinQueryUser.value(relationAlias);
      m_lstJoinQueryToResolve.append(query);
      return query->query().trimmed();
   }
   return QString();
}

QString QxSqlQuery::getJoinQueryHash()
{
   QString hash;
   QHashIterator<QString, std::shared_ptr<QxSqlQuery> > itr(m_lstJoinQueryUser);
   while (itr.hasNext())
   {
      itr.next();
      std::shared_ptr<QxSqlQuery> tmp = itr.value();
      hash += "|" + itr.key() + "|" + tmp->query();
   }
   return hash;
}

void QxSqlQuery::dumpBoundValues(const QSqlQuery & query)
{
   QString sBoundValues = "";
#if (QT_VERSION >= 0x060000)
   QVariantList lstBoundValues = query.boundValues();
#else // (QT_VERSION >= 0x060000)
   QMap<QString, QVariant> lstBoundValues = query.boundValues();
#endif // (QT_VERSION >= 0x060000)
   if (lstBoundValues.count() <= 0) { return; }

#if (QT_VERSION >= 0x060000)
   for (int i = 0; i < lstBoundValues.size(); ++i)
   { sBoundValues += "\n  - position '" + QString::number(i) + "' : " + lstBoundValues.at(i).toString(); }
#else // (QT_VERSION >= 0x060000)
   if (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark)
   {
      QList<QVariant> lst = lstBoundValues.values();
      for (int i = 0; i < lst.size(); ++i)
      { sBoundValues += "\n  - position '" + QString::number(i) + "' : " + lst.at(i).toString(); }
   }
   else
   {
      QMapIterator<QString, QVariant> itr(lstBoundValues);
      while (itr.hasNext()) { itr.next(); sBoundValues += "\n  - " + itr.key() + " : " + itr.value().toString(); }
   }
#endif // (QT_VERSION >= 0x060000)

   if (! sBoundValues.isEmpty())
   { qDebug("[QxOrm] dump sql query bound values : %s", qPrintable(sBoundValues)); }
}

void QxSqlQuery::fetchSqlResult(QSqlQuery & query)
{
   bool bCheckRecord = true;
   m_pSqlResult = std::make_shared<QxSqlResult>();
   if (query.size() > 0) { m_pSqlResult->values.reserve(query.size()); }
   while (query.next())
   {
      if (bCheckRecord)
      {
         bCheckRecord = false;
         QSqlRecord record = query.record();
         m_pSqlResult->positionByKey.reserve(record.count());
         for (int i = 0; i < record.count(); i++)
         { m_pSqlResult->positionByKey.insert(record.fieldName(i), i); }
         qAssert(record.count() == m_pSqlResult->positionByKey.count());
      }
      QVector<QVariant> lst;
      lst.reserve(m_pSqlResult->positionByKey.count());
      for (long j = 0; j < m_pSqlResult->positionByKey.count(); j++)
      { lst.append(query.value(j)); }
      qAssert(lst.count() == m_pSqlResult->positionByKey.count());
      m_pSqlResult->values.append(lst);
   }
}

long QxSqlQuery::getSqlResultRowCount() const
{
   if (! m_pSqlResult) { return 0; }
   return m_pSqlResult->values.count();
}

long QxSqlQuery::getSqlResultColumnCount() const
{
   if (! m_pSqlResult) { return 0; }
   return m_pSqlResult->positionByKey.count();
}

QVariant QxSqlQuery::getSqlResultAt(long row, long column) const
{
   if (! m_pSqlResult) { return QVariant(); }
   if ((row < 0) || (row >= m_pSqlResult->values.count())) { return QVariant(); }
   if ((column < 0) || (column >= m_pSqlResult->positionByKey.count())) { return QVariant(); }
   return m_pSqlResult->values.at(row).at(column);
}

QVariant QxSqlQuery::getSqlResultAt(long row, const QString & column) const
{
   if (! m_pSqlResult) { return QVariant(); }
   if ((row < 0) || (row >= m_pSqlResult->values.count())) { return QVariant(); }
   int i(-1); int col = m_pSqlResult->positionByKey.value(column, i);
   return ((col >= 0) ? m_pSqlResult->values.at(row).at(col) : QVariant());
}

QVector<QVariant> QxSqlQuery::getSqlResultAt(long row) const
{
   if (! m_pSqlResult) { return QVector<QVariant>(); }
   if ((row < 0) || (row >= m_pSqlResult->values.count())) { return QVector<QVariant>(); }
   return m_pSqlResult->values.at(row);
}

QVector<QString> QxSqlQuery::getSqlResultAllColumns() const
{
   if (! m_pSqlResult) { return QVector<QString>(); }
   QVector<QString> lstAllColumns(m_pSqlResult->positionByKey.count());
   QHashIterator<QString, int> itr(m_pSqlResult->positionByKey);
   while (itr.hasNext()) { itr.next(); lstAllColumns[itr.value()] = itr.key(); }
   return lstAllColumns;
}

void QxSqlQuery::dumpSqlResult()
{
   if (! m_pSqlResult) { return; }
   QString sql(this->query()), sColumns("#"), sOutput;
   qDebug("[QxOrm] start dump sql result : '%s'", qPrintable(sql));
   QVector<QString> lstColumns = this->getSqlResultAllColumns();
   for (long i = 0; i < lstColumns.count(); i++) { sColumns += "|" + lstColumns.at(i); }
   qDebug("%s", qPrintable(sColumns));
   for (long j = 0; j < m_pSqlResult->values.count(); j++)
   {
      sOutput = QString::number(j);
      for (long k = 0; k < m_pSqlResult->positionByKey.count(); k++)
      { sOutput += "|" + m_pSqlResult->values.at(j).at(k).toString(); }
      qDebug("%s", qPrintable(sOutput));
   }
   qDebug("[QxOrm] end dump sql result : '%s'", qPrintable(sql));
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
   p = std::make_shared<qx::dao::detail::QxSqlExpression>(m_iSqlElementIndex++, qx::dao::detail::QxSqlExpression::_open_parenthesis);
   m_lstSqlElement.append(p);
   m_iParenthesisCount++;
   return (* this);
}

QxSqlQuery & QxSqlQuery::closeParenthesis()
{
   if (m_iParenthesisCount <= 0) { return (* this); }
   qx::dao::detail::QxSqlExpression_ptr p;
   p = std::make_shared<qx::dao::detail::QxSqlExpression>(m_iSqlElementIndex++, qx::dao::detail::QxSqlExpression::_close_parenthesis);
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

QxSqlQuery & QxSqlQuery::limit(int rowsCount, int startRow /* = 0 */, bool withTies /* = false */)
{
   qx::dao::detail::QxSqlLimit_ptr p;
   p = std::make_shared<qx::dao::detail::QxSqlLimit>(m_iSqlElementIndex++);
   p->setValues(QVariantList() << QVariant(startRow) << QVariant(rowsCount) << QVariant(withTies));
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

QxSqlQuery & QxSqlQuery::customOperator(const QString & sCustomOperator, const QVariant & val)
{
   return addSqlCompare(val, qx::dao::detail::QxSqlCompare::_custom_operator, sCustomOperator);
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

QxSqlQuery & QxSqlQuery::in_Select(const QxSqlQuery & query)
{
   if (query.m_lstSqlElement.count() <= 0) { addSqlIn(QVariantList() << QVariant(query.queryAt(0)), qx::dao::detail::QxSqlIn::_in_select); }
   else { addEmbedQuery(query, qx::dao::detail::QxSqlEmbedQuery::_in, true); }
   return (* this);
}

QxSqlQuery & QxSqlQuery::notIn_Select(const QxSqlQuery & query)
{
   if (query.m_lstSqlElement.count() <= 0) { addSqlIn(QVariantList() << QVariant(query.queryAt(0)), qx::dao::detail::QxSqlIn::_not_in_select); }
   else { addEmbedQuery(query, qx::dao::detail::QxSqlEmbedQuery::_not_in, true); }
   return (* this);
}

QxSqlQuery & QxSqlQuery::isEqualTo_Select(const QxSqlQuery & query)
{
   if (query.m_lstSqlElement.count() <= 0) { addSqlCompare(query.queryAt(0), qx::dao::detail::QxSqlCompare::_is_equal_to_select); }
   else { addEmbedQuery(query, qx::dao::detail::QxSqlEmbedQuery::_is_equal_to, true); }
   return (* this);
}

QxSqlQuery & QxSqlQuery::isNotEqualTo_Select(const QxSqlQuery & query)
{
   if (query.m_lstSqlElement.count() <= 0) { addSqlCompare(query.queryAt(0), qx::dao::detail::QxSqlCompare::_is_not_equal_to_select); }
   else { addEmbedQuery(query, qx::dao::detail::QxSqlEmbedQuery::_is_not_equal_to, true); }
   return (* this);
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

QxSqlQuery & QxSqlQuery::freeText(const QString & text, const QVariantList & values /* = QVariantList() */)
{
   if (text.isEmpty()) { return (* this); }
   return addFreeText(text, values);
}

QxSqlQuery & QxSqlQuery::addJoinQuery(const QString & relationKeyOrAlias, const QxSqlQuery & joinQuery)
{
   std::shared_ptr<QxSqlQuery> pQuery = std::make_shared<QxSqlQuery>(joinQuery);
   m_lstJoinQueryUser.insert(relationKeyOrAlias, pQuery);
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlExpression(const QString & column, qx::dao::detail::QxSqlExpression::type type)
{
   qx::dao::detail::QxSqlExpression_ptr p;
   p = std::make_shared<qx::dao::detail::QxSqlExpression>(m_iSqlElementIndex++, type);
   m_lstSqlElement.append(p);

   m_pSqlElementTemp = std::make_shared<qx::dao::detail::QxSqlElementTemp>();
   m_pSqlElementTemp->setColumn(column);
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlCompare(const QVariant & val, qx::dao::detail::QxSqlCompare::type type, const QString & sCustomOperator /* = QString() */)
{
   if (! m_pSqlElementTemp)
   { qDebug("[QxOrm] qx::QxSqlQuery::addSqlCompare : '%s'", "invalid SQL query, need a column name"); qAssert(false); return (* this); }

   qx::dao::detail::QxSqlCompare_ptr p;
   p = std::make_shared<qx::dao::detail::QxSqlCompare>(m_iSqlElementIndex++, type, sCustomOperator);
   p->clone(m_pSqlElementTemp.get());
   p->setValue(val);

   m_lstSqlElement.append(p);
   m_pSqlElementTemp.reset();
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlSort(const QStringList & columns, qx::dao::detail::QxSqlSort::type type)
{
   qx::dao::detail::QxSqlSort_ptr p;
   p = std::make_shared<qx::dao::detail::QxSqlSort>(m_iSqlElementIndex++, type);
   p->setColumns(columns);
   m_lstSqlElement.append(p);
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlIn(const QVariantList & values, qx::dao::detail::QxSqlIn::type type)
{
   if (! m_pSqlElementTemp)
   { qDebug("[QxOrm] qx::QxSqlQuery::addSqlIn : '%s'", "invalid SQL query, need a column name"); qAssert(false); return (* this); }

   qx::dao::detail::QxSqlIn_ptr p;
   p = std::make_shared<qx::dao::detail::QxSqlIn>(m_iSqlElementIndex++, type);
   p->clone(m_pSqlElementTemp.get());
   p->setValues(values);

   m_lstSqlElement.append(p);
   m_pSqlElementTemp.reset();
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlIsNull(qx::dao::detail::QxSqlIsNull::type type)
{
   if (! m_pSqlElementTemp)
   { qDebug("[QxOrm] qx::QxSqlQuery::addSqlIsNull : '%s'", "invalid SQL query, need a column name"); qAssert(false); return (* this); }

   qx::dao::detail::QxSqlIsNull_ptr p;
   p = std::make_shared<qx::dao::detail::QxSqlIsNull>(m_iSqlElementIndex++, type);
   p->clone(m_pSqlElementTemp.get());

   m_lstSqlElement.append(p);
   m_pSqlElementTemp.reset();
   return (* this);
}

QxSqlQuery & QxSqlQuery::addSqlIsBetween(const QVariant & val1, const QVariant & val2, qx::dao::detail::QxSqlIsBetween::type type)
{
   if (! m_pSqlElementTemp)
   { qDebug("[QxOrm] qx::QxSqlQuery::addSqlIsBetween : '%s'", "invalid SQL query, need a column name"); qAssert(false); return (* this); }

   qx::dao::detail::QxSqlIsBetween_ptr p;
   p = std::make_shared<qx::dao::detail::QxSqlIsBetween>(m_iSqlElementIndex++, type);
   p->clone(m_pSqlElementTemp.get());
   p->setValues(QVariantList() << val1 << val2);

   m_lstSqlElement.append(p);
   m_pSqlElementTemp.reset();
   return (* this);
}

QxSqlQuery & QxSqlQuery::addFreeText(const QString & text, const QVariantList & values)
{
   qx::dao::detail::QxSqlFreeText_ptr p;
   p = std::make_shared<qx::dao::detail::QxSqlFreeText>(m_iSqlElementIndex++);
   p->setText(text);
   p->setValues(values);
   m_lstSqlElement.append(p);
   return (* this);
}

QxSqlQuery & QxSqlQuery::addEmbedQuery(const QxSqlQuery & query, qx::dao::detail::QxSqlEmbedQuery::type type, bool requirePreviousElement)
{
   if ((requirePreviousElement) && (! m_pSqlElementTemp))
   { qDebug("[QxOrm] qx::QxSqlQuery::addEmbedQuery : '%s'", "invalid SQL query, need a column name"); qAssert(false); return (* this); }

   qx::dao::detail::QxSqlEmbedQuery_ptr p;
   p = std::make_shared<qx::dao::detail::QxSqlEmbedQuery>(m_iSqlElementIndex++, type);
   if (requirePreviousElement) { p->clone(m_pSqlElementTemp.get()); }
   p->setQuery(query);

   m_lstSqlElement.append(p);
   m_pSqlElementTemp.reset();
   return (* this);
}

} // namespace qx

namespace qx {
namespace dao {

QSqlError call_query(qx::QxSqlQuery & query, QSqlDatabase * pDatabase /* = NULL */) { return qx::dao::helper::call_query_helper(query, pDatabase, true); }

QSqlError call_query_without_prepare(qx::QxSqlQuery & query, QSqlDatabase * pDatabase /* = NULL */) { return qx::dao::helper::call_query_helper(query, pDatabase, false); }

namespace helper {

QSqlError call_query_helper(qx::QxSqlQuery & query, QSqlDatabase * pDatabase, bool bPrepare)
{
#ifdef _QX_ENABLE_MONGODB
   if (qx::QxSqlDatabase::getSingleton()->getDriverName() == "QXMONGODB")
   { return qx::dao::mongodb::QxMongoDB_Helper::executeCommand(NULL, NULL, (& query)); }
#endif // _QX_ENABLE_MONGODB

   QSqlError dbError;
   QSqlDatabase d = (pDatabase ? (* pDatabase) : qx::QxSqlDatabase::getDatabase(dbError));
   if (dbError.isValid()) { return dbError; }
   bool bBoundValues = qx::QxSqlDatabase::getSingleton()->getTraceSqlBoundValues();
   bool bBoundValuesOnError = qx::QxSqlDatabase::getSingleton()->getTraceSqlBoundValuesOnError();
   QElapsedTimer timer; timer.start();
   QString sql = query.query();
   QSqlQuery q = QSqlQuery(d);
   q.setForwardOnly(true);

   do {
      if (bPrepare && ! q.prepare(sql)) { dbError = q.lastError(); break; }
      query.resolve(q);
      if (bPrepare) { if (! q.exec()) { dbError = q.lastError(); break; } }
      else { if (! q.exec(sql)) { dbError = q.lastError(); break; } }
      query.resolveOutput(q, true);
   }
   while (0);

   qlonglong ms = static_cast<qlonglong>(timer.elapsed());
   if (dbError.isValid())
   {
      QString log = "custom sql query failed (" + QString::number(ms) + " ms) : " + sql;
      qDebug("[QxOrm] %s", qPrintable(log));
#if (QT_VERSION >= 0x050300)
      QString serr = dbError.nativeErrorCode();
#else // (QT_VERSION >= 0x050300)
      int ierr = dbError.number();
      QString serr = QString::number(ierr);
#endif // (QT_VERSION >= 0x050300)
      QString tmp = dbError.driverText();
      qDebug("Database error number '%s' : %s", qPrintable(serr), qPrintable(tmp));
      tmp = dbError.databaseText(); qDebug("%s", qPrintable(tmp));
   }
   else if (qx::QxSqlDatabase::getSingleton()->getTraceSqlQuery())
   {
      qlonglong iTraceSqlOnlySlowQueriesDatabase = static_cast<qlonglong>(qx::QxSqlDatabase::getSingleton()->getTraceSqlOnlySlowQueriesDatabase());
      qlonglong iTraceSqlOnlySlowQueriesTotal = static_cast<qlonglong>(qx::QxSqlDatabase::getSingleton()->getTraceSqlOnlySlowQueriesTotal());
      if ((iTraceSqlOnlySlowQueriesDatabase > 0) && (iTraceSqlOnlySlowQueriesTotal < 0)) { iTraceSqlOnlySlowQueriesTotal = 999999999; }
      else if ((iTraceSqlOnlySlowQueriesTotal > 0) && (iTraceSqlOnlySlowQueriesDatabase < 0)) { iTraceSqlOnlySlowQueriesDatabase = 999999999; }
      if ((ms >= iTraceSqlOnlySlowQueriesTotal) || (ms >= iTraceSqlOnlySlowQueriesDatabase))
      {
         QString log = "custom sql query (" + QString::number(ms) + " ms) : " + sql;
         qDebug("[QxOrm] %s", qPrintable(log));
      }
   }

   if ((dbError.isValid() && bBoundValuesOnError) || (bBoundValues)) { qx::QxSqlQuery::dumpBoundValues(q); }
   return dbError;
}

} // namespace helper
} // namespace dao
} // namespace qx

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const qx::QxSqlQuery & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QHash<QString, int> lstResultPosByKey;
   QVector< QVector<QVariant> > lstResultValues;
   qx::dao::detail::IxSqlElement::type_class eNoSqlType = qx::dao::detail::IxSqlElement::_no_type;

   if (t.m_pSqlResult)
   {
      lstResultPosByKey = t.m_pSqlResult->positionByKey;
      lstResultValues = t.m_pSqlResult->values;
   }

   ar << boost::serialization::make_nvp("query", t.m_sQuery);
   ar << boost::serialization::make_nvp("list_values", t.m_lstValue);
   ar << boost::serialization::make_nvp("sql_element_index", t.m_iSqlElementIndex);
   ar << boost::serialization::make_nvp("parenthesis_count", t.m_iParenthesisCount);
   ar << boost::serialization::make_nvp("distinct", t.m_bDistinct);
   ar << boost::serialization::make_nvp("result_position_by_key", lstResultPosByKey);
   ar << boost::serialization::make_nvp("result_values", lstResultValues);
   ar << boost::serialization::make_nvp("response", t.m_vResponse);
   ar << boost::serialization::make_nvp("type", t.m_sType);
   ar << boost::serialization::make_nvp("list_join_query_user", t.m_lstJoinQueryUser);
   ar << boost::serialization::make_nvp("list_join_query_resolve", t.m_lstJoinQueryToResolve);

   if (! t.m_pSqlElementTemp)
   {
      ar << boost::serialization::make_nvp("sql_element_temp_type", eNoSqlType);
   }
   else
   {
      qx::dao::detail::IxSqlElement::type_class eTypeSqlElement = t.m_pSqlElementTemp->getTypeClass();
      ar << boost::serialization::make_nvp("sql_element_temp_type", eTypeSqlElement);
      t.m_pSqlElementTemp->qxSave(ar);
   }

   long lSqlElementCount = t.m_lstSqlElement.count();
   ar << boost::serialization::make_nvp("sql_element_count", lSqlElementCount);
   Q_FOREACH(qx::dao::detail::IxSqlElement_ptr pSqlElement, t.m_lstSqlElement)
   {
      if (! pSqlElement) { ar << boost::serialization::make_nvp("sql_element_type", eNoSqlType); continue; }
      qx::dao::detail::IxSqlElement::type_class eTypeSqlElement = pSqlElement->getTypeClass();
      ar << boost::serialization::make_nvp("sql_element_type", eTypeSqlElement);
      pSqlElement->qxSave(ar);
   }
}

template <class Archive>
inline void qx_load(Archive & ar, qx::QxSqlQuery & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QHash<QString, int> lstResultPosByKey;
   QVector< QVector<QVariant> > lstResultValues;

   ar >> boost::serialization::make_nvp("query", t.m_sQuery);
   ar >> boost::serialization::make_nvp("list_values", t.m_lstValue);
   ar >> boost::serialization::make_nvp("sql_element_index", t.m_iSqlElementIndex);
   ar >> boost::serialization::make_nvp("parenthesis_count", t.m_iParenthesisCount);
   ar >> boost::serialization::make_nvp("distinct", t.m_bDistinct);
   ar >> boost::serialization::make_nvp("result_position_by_key", lstResultPosByKey);
   ar >> boost::serialization::make_nvp("result_values", lstResultValues);
   ar >> boost::serialization::make_nvp("response", t.m_vResponse);
   ar >> boost::serialization::make_nvp("type", t.m_sType);
   ar >> boost::serialization::make_nvp("list_join_query_user", t.m_lstJoinQueryUser);
   ar >> boost::serialization::make_nvp("list_join_query_resolve", t.m_lstJoinQueryToResolve);

   t.m_pSqlResult.reset();
   if ((lstResultPosByKey.count() > 0) || (lstResultValues.count() > 0))
   {
      t.m_pSqlResult = std::shared_ptr<qx::QxSqlQuery::QxSqlResult>(new qx::QxSqlQuery::QxSqlResult());
      t.m_pSqlResult->positionByKey = lstResultPosByKey;
      t.m_pSqlResult->values = lstResultValues;
   }

   t.m_pSqlElementTemp.reset();
   qx::dao::detail::IxSqlElement::type_class eTypeSqlElement = qx::dao::detail::IxSqlElement::_no_type;
   ar >> boost::serialization::make_nvp("sql_element_temp_type", eTypeSqlElement);
   if (eTypeSqlElement != qx::dao::detail::IxSqlElement::_no_type)
   {
      t.m_pSqlElementTemp = qx::dao::detail::create_sql_element(eTypeSqlElement); qAssert(t.m_pSqlElementTemp);
      if (t.m_pSqlElementTemp) { t.m_pSqlElementTemp->qxLoad(ar); }
   }

   t.m_lstSqlElement.clear(); long lSqlElementCount = 0;
   ar >> boost::serialization::make_nvp("sql_element_count", lSqlElementCount);
   t.m_lstSqlElement.reserve(lSqlElementCount);
   for (long l = 0; l < lSqlElementCount; l++)
   {
      qx::dao::detail::IxSqlElement_ptr pSqlElement;
      eTypeSqlElement = qx::dao::detail::IxSqlElement::_no_type;
      ar >> boost::serialization::make_nvp("sql_element_type", eTypeSqlElement);
      if (eTypeSqlElement != qx::dao::detail::IxSqlElement::_no_type)
      {
         pSqlElement = qx::dao::detail::create_sql_element(eTypeSqlElement); qAssert(pSqlElement);
         if (pSqlElement) { pSqlElement->qxLoad(ar); }
      }
      t.m_lstSqlElement.append(pSqlElement);
   }
}

} // namespace serialization
} // namespace boost

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(qx::QxSqlQuery)

#endif // _QX_ENABLE_BOOST_SERIALIZATION

QDataStream & operator<< (QDataStream & stream, const qx::QxSqlQuery & t)
{
   QHash<QString, int> lstResultPosByKey;
   QVector< QVector<QVariant> > lstResultValues;
   qx::dao::detail::IxSqlElement::type_class eNoSqlType = qx::dao::detail::IxSqlElement::_no_type;

   if (t.m_pSqlResult)
   {
      lstResultPosByKey = t.m_pSqlResult->positionByKey;
      lstResultValues = t.m_pSqlResult->values;
   }

   stream << t.m_sQuery;
   stream << t.m_lstValue;
   stream << t.m_iSqlElementIndex;
   stream << t.m_iParenthesisCount;
   stream << t.m_bDistinct;
   stream << lstResultPosByKey;
   stream << lstResultValues;
   stream << t.m_vResponse;
   stream << t.m_sType;
   stream << t.m_lstJoinQueryUser;
   stream << t.m_lstJoinQueryToResolve;

   if (! t.m_pSqlElementTemp)
   {
      stream << (qint32)(eNoSqlType);
   }
   else
   {
      qx::dao::detail::IxSqlElement::type_class eTypeSqlElement = t.m_pSqlElementTemp->getTypeClass();
      stream << (qint32)(eTypeSqlElement);
      stream << (* t.m_pSqlElementTemp);
   }

   long lSqlElementCount = t.m_lstSqlElement.count();
   stream << (qint64)(lSqlElementCount);
   Q_FOREACH(qx::dao::detail::IxSqlElement_ptr pSqlElement, t.m_lstSqlElement)
   {
      if (! pSqlElement) { stream << (qint32)(eNoSqlType); continue; }
      qx::dao::detail::IxSqlElement::type_class eTypeSqlElement = pSqlElement->getTypeClass();
      stream << (qint32)(eTypeSqlElement);
      stream << (* pSqlElement);
   }

   return stream;
}

QDataStream & operator>> (QDataStream & stream, qx::QxSqlQuery & t)
{
   QHash<QString, int> lstResultPosByKey;
   QVector< QVector<QVariant> > lstResultValues;
   qint32 i32Temp = 0;

   stream >> t.m_sQuery;
   stream >> t.m_lstValue;
   stream >> t.m_iSqlElementIndex;
   stream >> t.m_iParenthesisCount;
   stream >> t.m_bDistinct;
   stream >> lstResultPosByKey;
   stream >> lstResultValues;
   stream >> t.m_vResponse;
   stream >> t.m_sType;
   stream >> t.m_lstJoinQueryUser;
   stream >> t.m_lstJoinQueryToResolve;

   t.m_pSqlResult.reset();
   if ((lstResultPosByKey.count() > 0) || (lstResultValues.count() > 0))
   {
      t.m_pSqlResult = std::shared_ptr<qx::QxSqlQuery::QxSqlResult>(new qx::QxSqlQuery::QxSqlResult());
      t.m_pSqlResult->positionByKey = lstResultPosByKey;
      t.m_pSqlResult->values = lstResultValues;
   }

   t.m_pSqlElementTemp.reset();
   qx::dao::detail::IxSqlElement::type_class eTypeSqlElement = qx::dao::detail::IxSqlElement::_no_type;
   stream >> i32Temp; eTypeSqlElement = static_cast<qx::dao::detail::IxSqlElement::type_class>(i32Temp);
   if (eTypeSqlElement != qx::dao::detail::IxSqlElement::_no_type)
   {
      t.m_pSqlElementTemp = qx::dao::detail::create_sql_element(eTypeSqlElement); qAssert(t.m_pSqlElementTemp);
      if (t.m_pSqlElementTemp) { stream >> (* t.m_pSqlElementTemp); }
   }

   t.m_lstSqlElement.clear();
   qint64 lSqlElementCount = 0;
   stream >> lSqlElementCount;
   t.m_lstSqlElement.reserve(static_cast<long>(lSqlElementCount));
   for (long l = 0; l < static_cast<long>(lSqlElementCount); l++)
   {
      qx::dao::detail::IxSqlElement_ptr pSqlElement;
      eTypeSqlElement = qx::dao::detail::IxSqlElement::_no_type;
      stream >> i32Temp; eTypeSqlElement = static_cast<qx::dao::detail::IxSqlElement::type_class>(i32Temp);
      if (eTypeSqlElement != qx::dao::detail::IxSqlElement::_no_type)
      {
         pSqlElement = qx::dao::detail::create_sql_element(eTypeSqlElement); qAssert(pSqlElement);
         if (pSqlElement) { stream >> (* pSqlElement); }
      }
      t.m_lstSqlElement.append(pSqlElement);
   }

   return stream;
}
