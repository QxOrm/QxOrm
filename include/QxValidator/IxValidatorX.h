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

#ifndef _IX_VALIDATOR_X_H_
#define _IX_VALIDATOR_X_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxValidatorX.h
 * \author Lionel Marty
 * \ingroup QxValidator
 * \brief Common interface for a list of validators
 */

#include <QxCollection/QxCollection.h>

#include <QxValidator/IxValidator.h>

namespace qx {

class IxClass;
class IxDataMember;
class QxInvalidValueX;

/*!
 * \ingroup QxValidator
 * \brief qx::IxValidatorX : common interface for a list of validators
 *
 * For more informations about <b>QxValidator module</b>, <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">goto the FAQ of QxOrm website</a> :
 * <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">http://www.qxorm.com/qxorm_en/faq.html#faq_250</a>
 */
class QX_DLL_EXPORT IxValidatorX
{

   friend class IxClass;

protected:

   typedef QList<IxValidator_ptr> type_lst_validator;
   typedef boost::shared_ptr<type_lst_validator> type_lst_validator_ptr;
   typedef QxCollection<QString, type_lst_validator_ptr> type_lst_validator_ptr_by_group;

   type_lst_validator_ptr_by_group m_lstValidatorByGroup;   //!< List of validator by group
   IxClass * m_pClass;                                      //!< Class registered into QxOrm context

public:

   IxValidatorX();
   virtual ~IxValidatorX() = 0;

   QxInvalidValueX validate(void * pOwner, const QString & sGroup = QString()) const;

   IxValidator * add_NotNull(const QString & sPropertyKey, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_NotEmpty(const QString & sPropertyKey, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_MinValue(const QString & sPropertyKey, long lMinValue, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_MaxValue(const QString & sPropertyKey, long lMaxValue, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_Range(const QString & sPropertyKey, long lMinValue, long lMaxValue, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_MinDecimal(const QString & sPropertyKey, double dMinValue, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_MaxDecimal(const QString & sPropertyKey, double dMaxValue, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_RangeDecimal(const QString & sPropertyKey, double dMinValue, double dMaxValue, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_MinLength(const QString & sPropertyKey, long lMinLength, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_MaxLength(const QString & sPropertyKey, long lMaxLength, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_Size(const QString & sPropertyKey, long lMinLength, long lMaxLength, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_DatePast(const QString & sPropertyKey, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_DateFuture(const QString & sPropertyKey, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_RegExp(const QString & sPropertyKey, const QString & sPattern, const QString & sMessage = QString(), const QString & sGroup = QString());
   IxValidator * add_EMail(const QString & sPropertyKey, const QString & sMessage = QString(), const QString & sGroup = QString());

   QStringList getAllGroup() const;
   QList<IxValidator_ptr> getAllValidatorByGroup(const QString & group) const;

protected:

   void setClass(IxClass * p);
   void insertIntoGroup(IxValidator_ptr pValidator, const QString & sGroup);
   IxValidator_ptr createValidator(IxValidator::validator_type type, const QString & sPropertyKey, const QString & sMessage, const QString & sGroup);
   IxDataMember * getDataMember(const QString & sPropertyKey) const;

};

typedef boost::shared_ptr<IxValidatorX> IxValidatorX_ptr;

} // namespace qx

#endif // _IX_VALIDATOR_X_H_
