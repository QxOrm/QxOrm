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

#ifndef _QX_FUNCTION_ERROR_H_
#define _QX_FUNCTION_ERROR_H_

#ifdef _MSC_VER
#pragma once
#endif

#define QX_FUNCTION_ERR_NUMBER_PARAMS              "Incorrect parameters count"
#define QX_FUNCTION_ERR_INVALID_PARAM              "Invalid parameter at position 'XXX'"
#define QX_FUNCTION_ERR_INVALID_FCT                "Invalid function"
#define QX_FUNCTION_ERR_EMPTY_FCT                  "Empty function"
#define QX_FUNCTION_ERR_INVALID_MEMBER_FCT         "Invalid member function"
#define QX_FUNCTION_ERR_EMPTY_MEMBER_FCT           "Empty member function"
#define QX_FUNCTION_ERR_INVALID_OWNER              "Invalid owner"
#define QX_FUNCTION_ERR_NULL_OWNER                 "NULL owner"
#define QX_FUNCTION_ERR_INVALID_INVOKE_CALL        "Invalid 'invoke()' call"
#define QX_FUNCTION_ERR_UNKNOWN_ERROR              "Unknown error calling function"

#endif // _QX_FUNCTION_ERROR_H_
