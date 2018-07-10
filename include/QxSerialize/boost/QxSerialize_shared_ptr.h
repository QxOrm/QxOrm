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

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#ifndef _QX_SERIALIZE_BOOST_SHARED_PTR_H_
#define _QX_SERIALIZE_BOOST_SHARED_PTR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxCommon/QxConfig.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4100)
#endif // _MSC_VER

#if _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132
#include <boost/serialization/shared_ptr_132.hpp>
#else // _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132
#ifdef BOOST_SERIALIZATION_SHARED_PTR_132_HPP
#undef BOOST_SERIALIZATION_SHARED_PTR_132_HPP
#endif // BOOST_SERIALIZATION_SHARED_PTR_132_HPP
#endif // _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132

#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif // _QX_SERIALIZE_BOOST_SHARED_PTR_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
