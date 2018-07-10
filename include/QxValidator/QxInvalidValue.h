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

#ifndef _QX_VALIDATOR_INVALID_VALUE_H_
#define _QX_VALIDATOR_INVALID_VALUE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxInvalidValue.h
 * \author Lionel Marty
 * \ingroup QxValidator
 * \brief Invalid value when a property fails to pass a constraint
 */

#include <QxCommon/QxPropertyBag.h>

namespace qx {

class IxValidator;

/*!
 * \ingroup QxValidator
 * \brief qx::QxInvalidValue : invalid value when a property fails to pass a constraint
 *
 * For more informations about <b>QxValidator module</b>, <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">goto the FAQ of QxOrm website</a> :
 * <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">http://www.qxorm.com/qxorm_en/faq.html#faq_250</a>
 */
class QX_DLL_EXPORT QxInvalidValue : public QxPropertyBag
{

protected:

   QString m_sMessage;                    //!< Message associated to the invalid value
   QString m_sPropertyName;               //!< Property name failing to pass the constraint
   QString m_sPath;                       //!< Path of property failing to pass the constraint
   const IxValidator * m_pValidator;      //!< IxValidator class associated to the invalid value

public:

   QxInvalidValue();
   virtual ~QxInvalidValue();

   QString getMessage() const                   { return m_sMessage; }
   QString getPropertyName() const              { return m_sPropertyName; }
   QString getPath() const                      { return m_sPath; }
   QString getFullName() const;
   const IxValidator * getValidator() const;

   void setMessage(const QString & s)           { m_sMessage = s; }
   void setPropertyName(const QString & s)      { m_sPropertyName = s; }
   void setPath(const QString & s)              { m_sPath = s; }
   void setValidator(const IxValidator * p);

};

} // namespace qx

#endif // _QX_VALIDATOR_INVALID_VALUE_H_
