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

#ifndef _QX_VALIDATOR_ERROR_H_
#define _QX_VALIDATOR_ERROR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxValidatorError.h
 * \author Lionel Marty
 * \ingroup QxValidator
 * \brief Define a validator error exception (for example, inserting or updating an element into database) and retrieve list of invalid values
 */

#include <iostream>
#include <exception>

#include <QxValidator/QxInvalidValueX.h>

namespace qx {

/*!
 * \ingroup QxValidator
 * \brief qx::validator_error : define a validator error exception (for example, inserting or updating an element into database) and retrieve list of invalid values
 *
 * For more informations about <b>QxValidator module</b>, <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">goto the FAQ of QxOrm website</a> :
 * <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">http://www.qxorm.com/qxorm_en/faq.html#faq_250</a>
 */
class validator_error : public std::exception
{

private:

   QxInvalidValueX m_lstInvalidValues;

public:

   validator_error(const QxInvalidValueX & err) : std::exception(), m_lstInvalidValues(err) { ; }
   virtual ~validator_error() throw() { ; }

   virtual const char * what() const throw()
   { return qPrintable(m_lstInvalidValues.text()); }

   QxInvalidValueX get() const
   { return m_lstInvalidValues; }

};

} // namespace qx

#endif // _QX_VALIDATOR_ERROR_H_
