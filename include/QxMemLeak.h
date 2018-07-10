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

#ifndef _QX_MEM_LEAK_H_
#define _QX_MEM_LEAK_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxMemLeak.h
 * \author Wu Yongwei
 * \ingroup QxMemLeak
 * \brief QxOrm library memory leak detection (by <a href="http://wyw.dcweb.cn/leakage.htm" target="_blank">Wu Yongwei</a>)
 *
 * QxMemLeak module provides a fast detection of memory leaks in Debug mode once the execution of the program is finished (with indication of the file and the line => MFC-style from Microsoft).<br>
 * This module is developed by Wu Yongwei and has undergone some modifications to be integrated into QxOrm library.<br>
 * If another tool is already used in your projects (Valgrind for example), this functionality should not be activated.<br>
 * To enable/disable QxMemLeak module, all is needed is to modify the constant _QX_USE_MEM_LEAK_DETECTION defined in the QxConfig.h file.<br>
 * A recompilation of QxOrm library is necessary to take into account this modification.
 */

#include <QxMemLeak/mem_leak.h>

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#if _QX_INCLUDE_BOOST_SERIALIZE_EXPORT_HPP_INTO_QX_MEM_LEAK_HPP
#if _QX_USE_MODIFY_BOOST_SERIALIZATION_EXPORT_HPP
#include <QxSerialize/boost/class_export/qx_boost_class_export.h>
#else
#include <boost/serialization/export.hpp>
#endif // _QX_USE_MODIFY_BOOST_SERIALIZATION_EXPORT_HPP
#endif // _QX_INCLUDE_BOOST_SERIALIZE_EXPORT_HPP_INTO_QX_MEM_LEAK_HPP
#endif // _QX_ENABLE_BOOST_SERIALIZATION

#endif // _QX_MEM_LEAK_H_
