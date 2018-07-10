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

#include <QxValidator/IxValidator.h>
#include <QxValidator/QxInvalidValueX.h>

#include <QxDataMember/IxDataMember.h>

#include <QxRegister/QxClassX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxValidator::IxValidator(IxValidator::validator_type type) : QxPropertyBag(), m_type(type), m_pDataMember(NULL) { initDefaultMessage(); }

IxValidator::~IxValidator() { ; }

IxValidator::validator_type IxValidator::getType() const { return m_type; }

QString IxValidator::getMessage() const { return m_message; }

QString IxValidator::getGroup() const { return m_group; }

QVariant IxValidator::getConstraint() const { return ((m_Constraints.count() > 0) ? m_Constraints.at(0) : QVariant()); }

QVariantList IxValidator::getConstraints() const { return m_Constraints; }

IxDataMember * IxValidator::getDataMember() const { return m_pDataMember; }

void IxValidator::setMessage(const QString & s) { m_message = s; }

void IxValidator::setGroup(const QString & s) { m_group = s; }

void IxValidator::setConstraint(const QVariant & v) { m_Constraints.clear(); m_Constraints.append(v); }

void IxValidator::setConstraints(const QVariantList & lst) { m_Constraints = lst; }

void IxValidator::setDataMember(IxDataMember * p) { m_pDataMember = p; }

void IxValidator::validate(void * pOwner, QxInvalidValueX & lstInvalidValues) const
{
   if (! pOwner) { qAssert(false); return; }
   if (! m_pDataMember) { return; }
   QVariant val = m_pDataMember->toVariant(pOwner);

   switch (m_type)
   {
      case not_null:             validateNotNull(val, lstInvalidValues);               break;
      case not_empty:            validateNotEmpty(val, lstInvalidValues);              break;
      case min_value:            validateMinValue(val, lstInvalidValues);              break;
      case max_value:            validateMaxValue(val, lstInvalidValues);              break;
      case min_length:           validateMinLength(val, lstInvalidValues);             break;
      case max_length:           validateMaxLength(val, lstInvalidValues);             break;
      case date_past:            validateDatePast(val, lstInvalidValues);              break;
      case date_future:          validateDateFuture(val, lstInvalidValues);            break;
      case min_decimal:          validateMinDecimal(val, lstInvalidValues);            break;
      case max_decimal:          validateMaxDecimal(val, lstInvalidValues);            break;
      case regular_expression:   validateRegularExpression(val, lstInvalidValues);     break;
      case e_mail:               validateEMail(val, lstInvalidValues);                 break;
      default:                   break;
   }
}

void IxValidator::initDefaultMessage()
{
   QHash<QString, QString> * lstMessage = QxClassX::getAllValidatorMessage();
   if (! lstMessage) { qAssert(false); return; }

   switch (m_type)
   {
      case not_null:             m_message = lstMessage->value("not_null");               break;
      case not_empty:            m_message = lstMessage->value("not_empty");              break;
      case min_value:            m_message = lstMessage->value("min_value");              break;
      case max_value:            m_message = lstMessage->value("max_value");              break;
      case min_length:           m_message = lstMessage->value("min_length");             break;
      case max_length:           m_message = lstMessage->value("max_length");             break;
      case date_past:            m_message = lstMessage->value("date_past");              break;
      case date_future:          m_message = lstMessage->value("date_future");            break;
      case min_decimal:          m_message = lstMessage->value("min_decimal");            break;
      case max_decimal:          m_message = lstMessage->value("max_decimal");            break;
      case regular_expression:   m_message = lstMessage->value("regular_expression");     break;
      case e_mail:               m_message = lstMessage->value("e_mail");                 break;
      default:                   m_message = "";                                          break;
   }
}

void IxValidator::validateNotNull(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   if (v.isNull()) { lstInvalidValues.insert(this); }
}

void IxValidator::validateNotEmpty(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   QString s = v.toString();
   if (s.size() <= 0) { lstInvalidValues.insert(this); }
}

void IxValidator::validateMinValue(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   long d = (long)v.toLongLong();
   long constraint = (long)getConstraint().toLongLong();
   if (d < constraint) { lstInvalidValues.insert(this); }
}

void IxValidator::validateMaxValue(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   long d = (long)v.toLongLong();
   long constraint = (long)getConstraint().toLongLong();
   if (d > constraint) { lstInvalidValues.insert(this); }
}

void IxValidator::validateMinDecimal(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   double d = v.toDouble();
   double constraint = getConstraint().toDouble();
   if (d < constraint) { lstInvalidValues.insert(this); }
}

void IxValidator::validateMaxDecimal(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   double d = v.toDouble();
   double constraint = getConstraint().toDouble();
   if (d > constraint) { lstInvalidValues.insert(this); }
}

void IxValidator::validateMinLength(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   QString s = v.toString();
   long constraint = (long)getConstraint().toLongLong();
   if (s.size() < constraint) { lstInvalidValues.insert(this); }
}

void IxValidator::validateMaxLength(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   QString s = v.toString();
   long constraint = (long)getConstraint().toLongLong();
   if (s.size() > constraint) { lstInvalidValues.insert(this); }
}

void IxValidator::validateDatePast(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   QDateTime dt = v.toDateTime();
   if (! dt.isValid() || (dt > QDateTime::currentDateTime())) { lstInvalidValues.insert(this); }
}

void IxValidator::validateDateFuture(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   QDateTime dt = v.toDateTime();
   if (! dt.isValid() || (dt < QDateTime::currentDateTime())) { lstInvalidValues.insert(this); }
}

void IxValidator::validateRegularExpression(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   QString s = v.toString();
   QRegExp constraint(getConstraint().toString());
   if (! constraint.exactMatch(s)) { lstInvalidValues.insert(this); }
}

void IxValidator::validateEMail(const QVariant & v, QxInvalidValueX & lstInvalidValues) const
{
   QString s = v.toString();
   QString pattern = "\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b";
   QRegExp constraint(pattern, Qt::CaseInsensitive);
   if (! constraint.exactMatch(s)) { lstInvalidValues.insert(this); }
}

} // namespace qx
