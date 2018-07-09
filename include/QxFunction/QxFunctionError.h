/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
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
