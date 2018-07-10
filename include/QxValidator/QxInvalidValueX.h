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

#ifndef _QX_VALIDATOR_INVALID_VALUE_X_H_
#define _QX_VALIDATOR_INVALID_VALUE_X_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxInvalidValueX.h
 * \author Lionel Marty
 * \ingroup QxValidator
 * \brief List of invalid values
 */

#include <QxValidator/QxInvalidValue.h>

namespace qx {

/*!
 * \ingroup QxValidator
 * \brief qx::QxInvalidValueX : list of invalid values
 *
 * For more informations about <b>QxValidator module</b>, <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">goto the FAQ of QxOrm website</a> :
 * <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">http://www.qxorm.com/qxorm_en/faq.html#faq_250</a>
 */
class QX_DLL_EXPORT QxInvalidValueX
{

protected:

   QList<QxInvalidValue> m_lstInvalidValues;    //!< List of invalid values
   QString m_sCurrentPath;                      //!< Current path of validation process

public:

   QxInvalidValueX();
   virtual ~QxInvalidValueX();

   QString getCurrentPath() const;
   void setCurrentPath(const QString & s);

   long count() const;
   QxInvalidValue at(long l) const;
   void insert(const IxValidator * pValidator);
   void insert(const QString & sMessage);
   void insert(const QxInvalidValue & invalidValue);
   void insert(const QxInvalidValueX & other);

   QString text() const;
   void dump() const;

   inline operator bool() const
   { return (m_lstInvalidValues.count() == 0); }

};

} // namespace qx

#endif // _QX_VALIDATOR_INVALID_VALUE_X_H_
