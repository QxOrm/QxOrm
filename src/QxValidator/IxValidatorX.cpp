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

#include <QxValidator/IxValidatorX.h>
#include <QxValidator/QxInvalidValueX.h>

#include <QxDataMember/IxDataMember.h>

#include <QxRegister/IxClass.h>
#include <QxRegister/QxClassX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxValidatorX::IxValidatorX() : m_pClass(NULL) { ; }

IxValidatorX::~IxValidatorX() { ; }

void IxValidatorX::setClass(IxClass * p) { m_pClass = p; }

IxDataMember * IxValidatorX::getDataMember(const QString & sPropertyKey) const
{
   if (sPropertyKey.isEmpty() || ! m_pClass) { return NULL; }
   IxDataMember * pDataMember = QxClassX::getDataMember(m_pClass->getKey(), sPropertyKey, true);
   if (! pDataMember) { qDebug("[QxOrm] qx::IxValidatorX::getDataMember() : '%s'", "property key not found"); qAssert(false); return NULL; }
   return pDataMember;
}

QStringList IxValidatorX::getAllGroup() const
{
   QStringList lstGroup;
   for (long l = 0; l < m_lstValidatorByGroup.count(); l++)
   { QString sGroup = m_lstValidatorByGroup.getKeyByIndex(l); lstGroup.append(sGroup); }
   return lstGroup;
}

QList<IxValidator_ptr> IxValidatorX::getAllValidatorByGroup(const QString & group) const
{
   if (! m_lstValidatorByGroup.exist(group)) { return QList<IxValidator_ptr>(); }
   type_lst_validator_ptr lst = m_lstValidatorByGroup.getByKey(group);
   return (* lst);
}

QxInvalidValueX IxValidatorX::validate(void * pOwner, const QString & sGroup /* = QString() */) const
{
   QxInvalidValueX invalidValues;
   if (! m_pClass) { qAssert(false); return invalidValues; }

   if (m_pClass->getBaseClass())
   {
      IxValidatorX * pAllValidator = m_pClass->getBaseClass()->getAllValidator();
      if (pAllValidator) { invalidValues.insert(pAllValidator->validate(pOwner, sGroup)); }
   }

   if (! m_lstValidatorByGroup.exist(sGroup)) { return invalidValues; }
   type_lst_validator_ptr lstValidator = m_lstValidatorByGroup.getByKey(sGroup);
   if (! lstValidator) { return invalidValues; }

   for (long l = 0; l < lstValidator->count(); l++)
   {
      IxValidator_ptr validator = lstValidator->at(l);
      if (validator) { validator->validate(pOwner, invalidValues); }
   }

   return invalidValues;
}

void IxValidatorX::insertIntoGroup(IxValidator_ptr pValidator, const QString & sGroup)
{
   if (! pValidator) { qAssert(false); return; }

   if (! m_lstValidatorByGroup.exist(sGroup))
   {
      type_lst_validator_ptr newLstValidator;
      newLstValidator.reset(new type_lst_validator());
      m_lstValidatorByGroup.insert(sGroup, newLstValidator);
   }

   type_lst_validator_ptr lstValidator = m_lstValidatorByGroup.getByKey(sGroup);
   lstValidator->append(pValidator);
}

IxValidator_ptr IxValidatorX::createValidator(IxValidator::validator_type type, const QString & sPropertyKey, const QString & sMessage, const QString & sGroup)
{
   IxValidator_ptr pValidator;
   pValidator.reset(new IxValidator(type));
   if (! sMessage.isEmpty()) { pValidator->setMessage(sMessage); }
   if (! sGroup.isEmpty()) { pValidator->setGroup(sGroup); }
   pValidator->setDataMember(getDataMember(sPropertyKey));
   return pValidator;
}

IxValidator * IxValidatorX::add_NotNull(const QString & sPropertyKey, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::not_null, sPropertyKey, sMessage, sGroup);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_NotEmpty(const QString & sPropertyKey, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::not_empty, sPropertyKey, sMessage, sGroup);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_MinValue(const QString & sPropertyKey, long lMinValue, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::min_value, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint((qlonglong)lMinValue);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_MaxValue(const QString & sPropertyKey, long lMaxValue, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::max_value, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint((qlonglong)lMaxValue);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_Range(const QString & sPropertyKey, long lMinValue, long lMaxValue, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::min_value, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint((qlonglong)lMinValue);
   insertIntoGroup(pValidator, sGroup);

   pValidator = createValidator(IxValidator::max_value, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint((qlonglong)lMaxValue);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_MinDecimal(const QString & sPropertyKey, double dMinValue, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::min_decimal, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint(dMinValue);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_MaxDecimal(const QString & sPropertyKey, double dMaxValue, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::max_decimal, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint(dMaxValue);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_RangeDecimal(const QString & sPropertyKey, double dMinValue, double dMaxValue, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::min_decimal, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint(dMinValue);
   insertIntoGroup(pValidator, sGroup);

   pValidator = createValidator(IxValidator::max_decimal, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint(dMaxValue);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_MinLength(const QString & sPropertyKey, long lMinLength, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::min_length, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint((qlonglong)lMinLength);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_MaxLength(const QString & sPropertyKey, long lMaxLength, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::max_length, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint((qlonglong)lMaxLength);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_Size(const QString & sPropertyKey, long lMinLength, long lMaxLength, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::min_length, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint((qlonglong)lMinLength);
   insertIntoGroup(pValidator, sGroup);

   pValidator = createValidator(IxValidator::max_length, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint((qlonglong)lMaxLength);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_DatePast(const QString & sPropertyKey, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::date_past, sPropertyKey, sMessage, sGroup);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_DateFuture(const QString & sPropertyKey, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::date_future, sPropertyKey, sMessage, sGroup);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_RegExp(const QString & sPropertyKey, const QString & sPattern, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::regular_expression, sPropertyKey, sMessage, sGroup);
   pValidator->setConstraint(sPattern);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

IxValidator * IxValidatorX::add_EMail(const QString & sPropertyKey, const QString & sMessage /* = QString() */, const QString & sGroup /* = QString() */)
{
   IxValidator_ptr pValidator = createValidator(IxValidator::e_mail, sPropertyKey, sMessage, sGroup);
   insertIntoGroup(pValidator, sGroup);
   return pValidator.get();
}

} // namespace qx
