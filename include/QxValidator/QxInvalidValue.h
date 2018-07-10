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
