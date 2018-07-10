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

#ifndef _QX_EXCEPTION_H_
#define _QX_EXCEPTION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxException.h
 * \author Lionel Marty
 * \ingroup QxCommon
 * \brief Exception with error code and error description
 */

#include <iostream>
#include <exception>

#include <QxCommon/QxBool.h>

namespace qx {

/*!
 * \ingroup QxCommon
 * \brief qx::exception : exception with error code and error description
 */
class exception : public std::exception
{

private:

   long m_code;      //!< Error code
   QString m_desc;   //!< Error description
   QString m_what;   //!< Formatted error : code + "^" + description

public:

   exception(const QString & desc) : std::exception(), m_code(0), m_desc(desc) { updateWhat(); }
   exception(long code, const QString & desc) : std::exception(), m_code(code), m_desc(desc) { updateWhat(); }
   virtual ~exception() throw() { ; }

   virtual const char * what() const throw() { return qPrintable(m_what); }

   long getCode() const             { return m_code; }
   QString getDescription() const   { return m_desc; }
   qx_bool toQxBool() const         { return qx_bool(m_code, m_desc); }

private:

   void updateWhat() { m_what = (QString::number(m_code) + QString("^") + m_desc); }

};

} // namespace qx

#endif // _QX_EXCEPTION_H_
