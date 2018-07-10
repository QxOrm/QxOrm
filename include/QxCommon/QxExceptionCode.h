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

#ifndef _QX_EXCEPTION_CODE_H_
#define _QX_EXCEPTION_CODE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxExceptionCode.h
 * \author Lionel Marty
 * \ingroup QxCommon
 * \brief Some errors codes defined by QxOrm library
 */

#include <QxCommon/QxException.h>

#define QX_ERROR_UNKNOWN                              1
#define QX_ERROR_SERVICE_NOT_SPECIFIED                2
#define QX_ERROR_SERVICE_INVALID                      3
#define QX_ERROR_SERVER_NOT_FOUND                     4
#define QX_ERROR_SERVICE_WRITE_ERROR                  5
#define QX_ERROR_SERVICE_READ_ERROR                   6

#define QX_EXCEPTION_UNKNOWN                          qx::exception(QX_ERROR_UNKNOWN, "unknown error")
#define QX_EXCEPTION_SERVICE_NOT_SPECIFIED            qx::exception(QX_ERROR_SERVICE_NOT_SPECIFIED, "[QxOrm] empty service name")
#define QX_EXCEPTION_SERVICE_INVALID                  qx::exception(QX_ERROR_SERVICE_INVALID, "[QxOrm] invalid service")
#define QX_EXCEPTION_SERVER_NOT_FOUND                 qx::exception(QX_ERROR_SERVER_NOT_FOUND, "[QxOrm] unable to connect to server")
#define QX_EXCEPTION_SERVICE_WRITE_ERROR              qx::exception(QX_ERROR_SERVICE_WRITE_ERROR, "[QxOrm] unable to write request to socket")
#define QX_EXCEPTION_SERVICE_READ_ERROR               qx::exception(QX_ERROR_SERVICE_READ_ERROR, "[QxOrm] unable to read reply from socket")

#endif // _QX_EXCEPTION_CODE_H_
