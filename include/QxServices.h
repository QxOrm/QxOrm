/****************************************************************************
**
** https://www.qxorm.com/
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

#ifndef _QX_SERVICES_H_
#define _QX_SERVICES_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxServices.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Include all headers required to use QxService module : https://www.qxorm.com/qxorm_en/manual.html#manual_80
 */

#include <QxOrm.h>

#ifdef _QX_ENABLE_QT_NETWORK

#include <QxService/IxParameter.h>
#include <QxService/IxService.h>
#include <QxService/QxClientAsync.h>
#include <QxService/QxConnect.h>
#include <QxService/QxServer.h>
#include <QxService/QxService.h>
#include <QxService/QxThread.h>
#include <QxService/QxThreadPool.h>
#include <QxService/QxTools.h>
#include <QxService/QxTransaction.h>

#endif // _QX_ENABLE_QT_NETWORK

#endif // _QX_SERVICES_H_
