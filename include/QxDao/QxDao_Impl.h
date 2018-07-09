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

#ifndef _QX_DAO_IMPL_H_
#define _QX_DAO_IMPL_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include "../../include/QxDao/QxDao.h"
#include "../../include/QxDao/QxSqlDatabase.h"
#include "../../include/QxDao/QxSqlQueryBuilder.h"
#include "../../include/QxDao/QxSqlQueryHelper.h"

#include "../../include/QxCollection/QxCollection.h"

#include "../../include/QxRegister/QxClass.h"

#include "../../include/QxTraits/is_qx_registered.h"
#include "../../include/QxTraits/is_container.h"
#include "../../include/QxTraits/is_smart_ptr.h"
#include "../../include/QxTraits/get_base_class.h"
#include "../../include/QxTraits/get_class_name_primitive.h"
#include "../../include/QxTraits/construct_ptr.h"
#include "../../include/QxTraits/generic_container.h"
#include "../../include/QxTraits/is_valid_primary_key.h"

#include "../../inl/QxDao/QxDao_Helper.inl"
#include "../../inl/QxDao/QxDao_Count.inl"
#include "../../inl/QxDao/QxDao_FetchById.inl"
#include "../../inl/QxDao/QxDao_FetchById_WithRelation.inl"
#include "../../inl/QxDao/QxDao_FetchAll.inl"
#include "../../inl/QxDao/QxDao_FetchAll_WithRelation.inl"
#include "../../inl/QxDao/QxDao_Insert.inl"
#include "../../inl/QxDao/QxDao_Insert_WithRelation.inl"
#include "../../inl/QxDao/QxDao_Update.inl"
#include "../../inl/QxDao/QxDao_Update_WithRelation.inl"
#include "../../inl/QxDao/QxDao_Save.inl"
#include "../../inl/QxDao/QxDao_Save_WithRelation.inl"
#include "../../inl/QxDao/QxDao_DeleteById.inl"
#include "../../inl/QxDao/QxDao_DeleteAll.inl"
#include "../../inl/QxDao/QxDao_Exist.inl"
#include "../../inl/QxDao/QxDao_CreateTable.inl"
#include "../../inl/QxDao/QxDao_Trigger.inl"

#endif // _QX_DAO_IMPL_H_
