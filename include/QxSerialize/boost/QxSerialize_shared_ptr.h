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

#ifndef _QX_SERIALIZE_BOOST_SHARED_PTR_H_
#define _QX_SERIALIZE_BOOST_SHARED_PTR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../../include/QxCommon/QxConfig.h"

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
