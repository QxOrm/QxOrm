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

#ifndef _QX_SERIALIZE_BOOST_SHARED_PTR_H_
#define _QX_SERIALIZE_BOOST_SHARED_PTR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxCommon/QxConfig.h>

#if _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132
#include <boost/serialization/shared_ptr_132.hpp>
#else // _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132
#ifdef BOOST_SERIALIZATION_SHARED_PTR_132_HPP
#undef BOOST_SERIALIZATION_SHARED_PTR_132_HPP
#endif // BOOST_SERIALIZATION_SHARED_PTR_132_HPP
#endif // _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132

#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>

#endif // _QX_SERIALIZE_BOOST_SHARED_PTR_H_
