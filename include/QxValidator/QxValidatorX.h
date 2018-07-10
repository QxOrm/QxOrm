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

#ifndef _QX_VALIDATOR_X_H_
#define _QX_VALIDATOR_X_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxValidatorX.h
 * \author Lionel Marty
 * \ingroup QxValidator
 * \brief Concrete class for a list of validators associated to a type registered into QxOrm context
 */

#include <QxValidator/IxValidatorX.h>
#include <QxValidator/QxValidator.h>

#include <QxRegister/QxClassX.h>

namespace qx {

/*!
 * \ingroup QxValidator
 * \brief qx::QxValidatorX<T> : concrete class for a list of validators associated to a type registered into QxOrm context
 *
 * For more informations about <b>QxValidator module</b>, <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">goto the FAQ of QxOrm website</a> :
 * <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">http://www.qxorm.com/qxorm_en/faq.html#faq_250</a>
 */
template <class T>
class QxValidatorX : public IxValidatorX
{

public:

   QxValidatorX() : IxValidatorX() { ; }
   virtual ~QxValidatorX() { ; }

   template <class DataType>
   IxValidator * add_RecursiveValidator(const QString & sPropertyKey, const QString & sGroup = QString())
   {
      IxValidator_ptr pValidator;
      pValidator.reset(new QxValidator_Recursive<DataType, T>());
      pValidator->setGroup(sGroup);
      pValidator->setDataMember(getDataMember(sPropertyKey));
      insertIntoGroup(pValidator, sGroup);
      return pValidator.get();
   }

   IxValidator * add_CustomValidator(typename QxValidator<T>::type_fct_custom_validator_member fct, const QString & sGroup = QString())
   { return add_CustomValidator_Helper(new QxValidator<T>(), fct, "", sGroup); }

   IxValidator * add_CustomValidator_QVariant(typename QxValidator<T>::type_fct_custom_validator_variant_validator fct, const QString & sPropertyKey, const QString & sGroup = QString())
   { return add_CustomValidator_Helper(new QxValidator<T>(), fct, sPropertyKey, sGroup); }

   template <class DataType>
   IxValidator * add_CustomValidator_DataType(typename QxValidator_WithDataType<DataType, T>::type_fct_custom_validator_data_type_validator fct, const QString & sPropertyKey, const QString & sGroup = QString())
   { return add_CustomValidator_Helper(new QxValidator_WithDataType<DataType, T>(), fct, sPropertyKey, sGroup); }

private:

   template <class Validator, class FunctionType>
   IxValidator * add_CustomValidator_Helper(Validator * validator, FunctionType fct, const QString & sPropertyKey, const QString & sGroup)
   {
      if (! validator) { qAssert(false); return NULL; }
      IxValidator_ptr pValidator;
      pValidator.reset(validator);
      validator->setGroup(sGroup);
      validator->setFunction(fct);
      validator->setDataMember(getDataMember(sPropertyKey));
      insertIntoGroup(pValidator, sGroup);
      return pValidator.get();
   }

};

} // namespace qx

#endif // _QX_VALIDATOR_X_H_
