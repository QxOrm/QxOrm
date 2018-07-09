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

#ifndef _QX_MEM_LEAK_H_
#define _QX_MEM_LEAK_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../include/QxMemLeak/mem_leak.h"

#if _QX_INCLUDE_BOOST_SERIALIZE_EXPORT_HPP_INTO_QX_MEM_LEAK_HPP
#if _QX_USE_MODIFY_BOOST_SERIALIZATION_EXPORT_HPP
#include "../include/QxSerialize/boost/class_export/qx_boost_class_export.h"
#else
#include <boost/serialization/export.hpp>
#endif // _QX_USE_MODIFY_BOOST_SERIALIZATION_EXPORT_HPP
#endif // _QX_INCLUDE_BOOST_SERIALIZE_EXPORT_HPP_INTO_QX_MEM_LEAK_HPP

#endif // _QX_MEM_LEAK_H_
