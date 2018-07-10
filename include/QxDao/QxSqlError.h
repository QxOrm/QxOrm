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

#ifndef _QX_SQL_ERROR_H_
#define _QX_SQL_ERROR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlError.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Define a SQL error exception and retrieve QSqlError type of Qt library
 */

#include <iostream>
#include <exception>

#include <QtSql/qsqlerror.h>

namespace qx {
namespace dao {

/*!
 * \ingroup QxDao
 * \brief qx::dao::sql_error : define a SQL error exception and retrieve QSqlError type of Qt library
 */
class sql_error : public std::exception
{

private:

   QSqlError m_error;

public:

   sql_error(const QSqlError & err) : std::exception(), m_error(err) { if (! m_error.text().isEmpty() && (m_error.type() == QSqlError::NoError)) { m_error.setType(QSqlError::UnknownError); } }
   virtual ~sql_error() throw() { ; }

   virtual const char * what() const throw()
   { return (m_error.isValid() ? qPrintable(m_error.text()) : ""); }

   QSqlError get() const { return m_error; }

};

} // namespace dao
} // namespace qx

#endif // _QX_SQL_ERROR_H_
