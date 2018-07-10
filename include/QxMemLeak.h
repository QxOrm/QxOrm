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

#if _QX_INCLUDE_BOOST_SERIALIZE_EXPORT_HPP_INTO_QX_MEM_LEAK_HPP
#if _QX_USE_MODIFY_BOOST_SERIALIZATION_EXPORT_HPP
#include <QxSerialize/boost/class_export/qx_boost_class_export.h>
#else
#include <boost/serialization/export.hpp>
#endif // _QX_USE_MODIFY_BOOST_SERIALIZATION_EXPORT_HPP
#endif // _QX_INCLUDE_BOOST_SERIALIZE_EXPORT_HPP_INTO_QX_MEM_LEAK_HPP

#endif // _QX_MEM_LEAK_H_
