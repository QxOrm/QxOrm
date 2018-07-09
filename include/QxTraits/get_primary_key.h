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

#ifndef _QX_GET_PRIMARY_KEY_H_
#define _QX_GET_PRIMARY_KEY_H_

#ifdef _MSC_VER
#pragma once
#endif

namespace qx {
namespace trait {

template <class T>
class get_primary_key
{ public: typedef long type; };

} // namespace trait
} // namespace qx

#define QX_REGISTER_PRIMARY_KEY(daoClass, primaryKey) \
namespace qx { namespace trait { \
template <> \
class get_primary_key< daoClass > \
{ public: typedef primaryKey type; }; \
} } // namespace qx::trait

#endif // _QX_GET_PRIMARY_KEY_H_
