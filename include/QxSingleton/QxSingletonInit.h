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

#ifndef _QX_SINGLETON_INIT_H_
#define _QX_SINGLETON_INIT_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSingletonInit.h
 * \author Lionel Marty
 * \ingroup QxSingleton
 * \brief Initialize some singletons hosted by QxOrm shared library
 */

#include <QxSingleton/QxSingleton.h>

#include <QxRegister/QxClass.h>

#include <QxDataMember/QxDataMemberX.h>

#include <QxService/IxParameter.h>
#include <QxService/IxService.h>
#include <QxService/QxTransaction.h>

#include <QxTraits/get_base_class.h>

QX_DLL_EXPORT_QX_SINGLETON_HPP( qx::QxClass< qx::trait::no_base_class_defined > )
QX_DLL_EXPORT_QX_SINGLETON_HPP( qx::QxDataMemberX< qx::trait::no_base_class_defined > )

QX_DLL_EXPORT_QX_SINGLETON_HPP( qx::QxClass< QObject > )
QX_DLL_EXPORT_QX_SINGLETON_HPP( qx::QxDataMemberX< QObject > )

#ifdef _QX_ENABLE_QT_NETWORK

QX_DLL_EXPORT_QX_SINGLETON_HPP( qx::QxClass< qx::service::IxParameter > )
QX_DLL_EXPORT_QX_SINGLETON_HPP( qx::QxDataMemberX< qx::service::IxParameter > )

QX_DLL_EXPORT_QX_SINGLETON_HPP( qx::QxClass< qx::service::IxService > )
QX_DLL_EXPORT_QX_SINGLETON_HPP( qx::QxDataMemberX< qx::service::IxService > )

QX_DLL_EXPORT_QX_SINGLETON_HPP( qx::QxClass< qx::service::QxTransaction > )
QX_DLL_EXPORT_QX_SINGLETON_HPP( qx::QxDataMemberX< qx::service::QxTransaction > )

#endif // _QX_ENABLE_QT_NETWORK

#endif // _QX_SINGLETON_INIT_H_
