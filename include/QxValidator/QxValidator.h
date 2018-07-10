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

#ifndef _QX_VALIDATOR_H_
#define _QX_VALIDATOR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxValidator.h
 * \author Lionel Marty
 * \ingroup QxValidator
 * \brief Concrete class for a custom or recursive validator
 */

#include <boost/function.hpp>

#include <QxValidator/IxValidator.h>
#include <QxValidator/QxInvalidValueX.h>

#include <QxDataMember/IxDataMember.h>

namespace qx {

template <class T>
QxInvalidValueX validate(T & t, const QString & group);

/*!
 * \ingroup QxValidator
 * \brief qx::QxValidator<Owner> : concrete class for a custom validator
 *
 * For more informations about <b>QxValidator module</b>, <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">goto the FAQ of QxOrm website</a> :
 * <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">http://www.qxorm.com/qxorm_en/faq.html#faq_250</a>
 */
template <class Owner>
class QxValidator : public IxValidator
{

public:

   typedef boost::function<void (Owner *, QxInvalidValueX &)> type_fct_custom_validator_member;
   typedef boost::function<void (const QVariant &, QxInvalidValueX &)> type_fct_custom_validator_variant;
   typedef boost::function<void (const QVariant &, const IxValidator *, QxInvalidValueX &)> type_fct_custom_validator_variant_validator;

protected:

   type_fct_custom_validator_member             m_fctCustomValidator_Member;              //!< Custom validator function : class method
   type_fct_custom_validator_variant            m_fctCustomValidator_Variant;             //!< Custom validator function : global function with value converted to QVariant type
   type_fct_custom_validator_variant_validator  m_fctCustomValidator_VariantValidator;    //!< Custom validator function : global function with value converted to QVariant type and a IxValidator pointer containing all parameters

public:

   QxValidator() : IxValidator(IxValidator::custom_validator) { ; }
   virtual ~QxValidator() { ; }

   void setFunction(type_fct_custom_validator_member fct)               { m_fctCustomValidator_Member = fct; }
   void setFunction(type_fct_custom_validator_variant fct)              { m_fctCustomValidator_Variant = fct; }
   void setFunction(type_fct_custom_validator_variant_validator fct)    { m_fctCustomValidator_VariantValidator = fct; }

   virtual void validate(void * pOwner, QxInvalidValueX & lstInvalidValues) const
   {
      if (! m_fctCustomValidator_Member.empty())
      { m_fctCustomValidator_Member(static_cast<Owner *>(pOwner), lstInvalidValues); }
      else if (! m_fctCustomValidator_Variant.empty() && m_pDataMember)
      { m_fctCustomValidator_Variant(m_pDataMember->toVariant(pOwner), lstInvalidValues); }
      else if (! m_fctCustomValidator_VariantValidator.empty() && m_pDataMember)
      { m_fctCustomValidator_VariantValidator(m_pDataMember->toVariant(pOwner), this, lstInvalidValues); }
   }

};

/*!
 * \ingroup QxValidator
 * \brief qx::QxValidator_WithDataType<DataType, Owner> : concrete class for a custom validator with data type
 *
 * For more informations about <b>QxValidator module</b>, <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">goto the FAQ of QxOrm website</a> :
 * <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">http://www.qxorm.com/qxorm_en/faq.html#faq_250</a>
 */
template <typename DataType, class Owner>
class QxValidator_WithDataType : public IxValidator
{

public:

   typedef boost::function<void (const DataType &, QxInvalidValueX &)> type_fct_custom_validator_data_type;
   typedef boost::function<void (const DataType &, const IxValidator *, QxInvalidValueX &)> type_fct_custom_validator_data_type_validator;

protected:

   type_fct_custom_validator_data_type             m_fctCustomValidator_DataType;            //!< Custom validator function : global function with value
   type_fct_custom_validator_data_type_validator   m_fctCustomValidator_DataTypeValidator;   //!< Custom validator function : global function with value and a IxValidator pointer containing all parameters

public:

   QxValidator_WithDataType() : IxValidator(IxValidator::custom_validator) { ; }
   virtual ~QxValidator_WithDataType() { ; }

   void setFunction(type_fct_custom_validator_data_type fct)            { m_fctCustomValidator_DataType = fct; }
   void setFunction(type_fct_custom_validator_data_type_validator fct)  { m_fctCustomValidator_DataTypeValidator = fct; }

   virtual void validate(void * pOwner, QxInvalidValueX & lstInvalidValues) const
   {
      if (! m_pDataMember) { return; }
      IxDataMember * pDataMember = const_cast<IxDataMember *>(m_pDataMember);
      DataType * val = pDataMember->getValuePtr<DataType>(pOwner);
      if (! m_fctCustomValidator_DataType.empty() && val)
      { m_fctCustomValidator_DataType((* val), lstInvalidValues); }
      else if (! m_fctCustomValidator_DataTypeValidator.empty() && val)
      { m_fctCustomValidator_DataTypeValidator((* val), this, lstInvalidValues); }
   }

};

/*!
 * \ingroup QxValidator
 * \brief qx::QxValidator_Recursive<DataType, Owner> : concrete class for a recursive validator
 *
 * For more informations about <b>QxValidator module</b>, <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">goto the FAQ of QxOrm website</a> :
 * <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">http://www.qxorm.com/qxorm_en/faq.html#faq_250</a>
 */
template <typename DataType, class Owner>
class QxValidator_Recursive : public IxValidator
{

public:

   QxValidator_Recursive() : IxValidator(IxValidator::recursive_validator) { ; }
   virtual ~QxValidator_Recursive() { ; }

   virtual void validate(void * pOwner, QxInvalidValueX & lstInvalidValues) const
   {
      if (! m_pDataMember) { qAssert(false); return; }
      IxDataMember * pDataMember = const_cast<IxDataMember *>(m_pDataMember);
      DataType * val = pDataMember->getValuePtr<DataType>(pOwner);
      if (! val) { qAssert(false); return; }
      QxInvalidValueX invalidValues;
      invalidValues.setCurrentPath(m_pDataMember->getName());
      invalidValues.insert(qx::validate((* val), m_group));
      lstInvalidValues.insert(invalidValues);
   }

};

} // namespace qx

#endif // _QX_VALIDATOR_H_
