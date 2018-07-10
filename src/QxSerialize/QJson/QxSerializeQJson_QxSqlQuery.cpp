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

#ifndef _QX_NO_JSON

#include <QxSerialize/QJson/QxSerializeQJson_QxSqlQuery.h>
#include <QxSerialize/QJson/QxSerializeQJson_boost_tuple.h>
#include <QxSerialize/QJson/QxSerializeQJson_QHash.h>
#include <QxSerialize/QJson/QxSerializeQJson_QVector.h>
#include <QxSerialize/QJson/QxSerializeQJson_QFlags.h>
#include <QxSerialize/QJson/QxSerializeQJson_IxSqlElement.h>
#include <QxSerialize/QJson/QxSerializeQJson_QxCollection.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

QJsonValue QxConvert_ToJson_Helper(const qx::QxSqlQuery & t, const QString & format)
{
   QJsonObject obj; QJsonArray arr;
   QHash<QString, int> lstResultPosByKey;
   QVector< QVector<QVariant> > lstResultValues;
   qx::dao::detail::IxSqlElement::type_class eNoSqlType = qx::dao::detail::IxSqlElement::_no_type;

   if (t.m_pSqlResult)
   {
      lstResultPosByKey = t.m_pSqlResult->positionByKey;
      lstResultValues = t.m_pSqlResult->values;
   }

   obj.insert("query", QJsonValue(t.m_sQuery));
   obj.insert("list_values", qx::cvt::to_json(t.m_lstValue, format));
   obj.insert("sql_element_index", QJsonValue(t.m_iSqlElementIndex));
   obj.insert("parenthesis_count", QJsonValue(t.m_iParenthesisCount));
   obj.insert("distinct", QJsonValue(t.m_bDistinct));
   obj.insert("result_position_by_key", qx::cvt::to_json(lstResultPosByKey, format));
   obj.insert("result_values", qx::cvt::to_json(lstResultValues, format));

   if (! t.m_pSqlElementTemp)
   {
      obj.insert("sql_element_temp_type", QJsonValue(static_cast<int>(eNoSqlType)));
   }
   else
   {
      qx::dao::detail::IxSqlElement::type_class eTypeSqlElement = t.m_pSqlElementTemp->getTypeClass();
      obj.insert("sql_element_temp_type", QJsonValue(static_cast<int>(eTypeSqlElement)));
      obj.insert("sql_element_temp", qx::cvt::to_json((* t.m_pSqlElementTemp), format));
   }

   Q_FOREACH(qx::dao::detail::IxSqlElement_ptr pSqlElement, t.m_lstSqlElement)
   {
      QJsonObject item;
      if (! pSqlElement) { item.insert("sql_element_type", QJsonValue(static_cast<int>(eNoSqlType))); arr.append(QJsonValue(item)); continue; }
      qx::dao::detail::IxSqlElement::type_class eTypeSqlElement = pSqlElement->getTypeClass();
      item.insert("sql_element_type", QJsonValue(static_cast<int>(eTypeSqlElement)));
      item.insert("sql_element", qx::cvt::to_json((* pSqlElement), format));
      arr.append(QJsonValue(item));
   }
   obj.insert("sql_element_list", QJsonValue(arr));

   return QJsonValue(obj);
}

qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, qx::QxSqlQuery & t, const QString & format)
{
   t = qx::QxSqlQuery();
   if (! j.isObject()) { return qx_bool(true); }
   QJsonObject obj = j.toObject();
   QHash<QString, int> lstResultPosByKey;
   QVector< QVector<QVariant> > lstResultValues;

   t.m_sQuery = obj.value("query").toString();
   qx::cvt::from_json(obj.value("list_values"), t.m_lstValue, format);
   t.m_iSqlElementIndex = qRound(obj.value("sql_element_index").toDouble());
   t.m_iParenthesisCount = qRound(obj.value("parenthesis_count").toDouble());
   t.m_bDistinct = obj.value("distinct").toBool();
   qx::cvt::from_json(obj.value("result_position_by_key"), lstResultPosByKey, format);
   qx::cvt::from_json(obj.value("result_values"), lstResultValues, format);

   t.m_pSqlResult.reset();
   if ((lstResultPosByKey.count() > 0) || (lstResultValues.count() > 0))
   {
      t.m_pSqlResult = qx_shared_ptr<qx::QxSqlQuery::QxSqlResult>(new qx::QxSqlQuery::QxSqlResult());
      t.m_pSqlResult->positionByKey = lstResultPosByKey;
      t.m_pSqlResult->values = lstResultValues;
   }

   t.m_pSqlElementTemp.reset();
   qx::dao::detail::IxSqlElement::type_class eTypeSqlElement = qx::dao::detail::IxSqlElement::_no_type;
   eTypeSqlElement = static_cast<qx::dao::detail::IxSqlElement::type_class>(qRound(obj.value("sql_element_temp_type").toDouble()));
   if (eTypeSqlElement != qx::dao::detail::IxSqlElement::_no_type)
   {
      t.m_pSqlElementTemp = qx::dao::detail::create_sql_element(eTypeSqlElement); qAssert(t.m_pSqlElementTemp);
      if (t.m_pSqlElementTemp) { qx::cvt::from_json(obj.value("sql_element_temp"), (* t.m_pSqlElementTemp), format); }
   }

   t.m_lstSqlElement.clear();
   QJsonArray arr = obj.value("sql_element_list").toArray();
   for (int i = 0; i < arr.count(); i++)
   {
      QJsonValue val = arr.at(i); if (! val.isObject()) { continue; }
      QJsonObject item = val.toObject();
      qx::dao::detail::IxSqlElement_ptr pSqlElement;
      eTypeSqlElement = qx::dao::detail::IxSqlElement::_no_type;
      eTypeSqlElement = static_cast<qx::dao::detail::IxSqlElement::type_class>(qRound(item.value("sql_element_type").toDouble()));
      if (eTypeSqlElement != qx::dao::detail::IxSqlElement::_no_type)
      {
         pSqlElement = qx::dao::detail::create_sql_element(eTypeSqlElement); qAssert(pSqlElement);
         if (pSqlElement) { qx::cvt::from_json(item.value("sql_element"), (* pSqlElement), format); }
      }
      t.m_lstSqlElement.append(pSqlElement);
   }

   return qx_bool(true);
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_NO_JSON
