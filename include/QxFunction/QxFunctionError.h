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

#ifndef _QX_FUNCTION_ERROR_H_
#define _QX_FUNCTION_ERROR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxFunctionError.h
 * \author Lionel Marty
 * \ingroup QxFunction
 * \brief Define all messages when an error occured using QxFunction module of QxOrm library
 */

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
