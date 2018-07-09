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

#ifndef _QX_ORM_H_
#define _QX_ORM_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../include/QxPrecompiled.h"

#include "../include/QxCommon/QxConfig.h"
#include "../include/QxCommon/QxMacro.h"
#include "../include/QxCommon/QxHashValue.h"
#include "../include/QxCommon/QxBool.h"
#include "../include/QxCommon/QxCache.h"

#include "../include/QxMemLeak/bool_array.h"
#include "../include/QxMemLeak/class_level_lock.h"
#include "../include/QxMemLeak/cont_ptr_utils.h"
#include "../include/QxMemLeak/fast_mutex.h"
#include "../include/QxMemLeak/fixed_mem_pool.h"
#include "../include/QxMemLeak/mem_pool_base.h"
#include "../include/QxMemLeak/object_level_lock.h"
#include "../include/QxMemLeak/pctimer.h"
#include "../include/QxMemLeak/set_assign.h"
#include "../include/QxMemLeak/static_assert.h"
#include "../include/QxMemLeak/static_mem_pool.h"

#include "../include/QxCollection/IxCollection.h"
#include "../include/QxCollection/QxCollection.h"
#include "../include/QxCollection/QxCollectionIterator.h"
#include "../include/QxCollection/QxForeach.h"

#include "../include/QxSingleton/IxSingleton.h"
#include "../include/QxSingleton/QxSingleton.h"
#include "../include/QxSingleton/QxSingletonX.h"

#include "../include/QxFactory/IxFactory.h"
#include "../include/QxFactory/QxFactory.h"
#include "../include/QxFactory/QxFactoryX.h"

#include "../include/QxTraits/qx_traits.h"

#include "../include/QxDataMember/IxDataMember.h"
#include "../include/QxDataMember/IxDataMemberX.h"
#include "../include/QxDataMember/QxDataMember.h"
#include "../include/QxDataMember/QxDataMemberX.h"

#include "../include/QxFunction/QxFunctionInclude.h"

#include "../include/QxXml/QxXmlReader.h"
#include "../include/QxXml/QxXmlWriter.h"
#include "../include/QxXml/QxXml.h"

#include "../include/QxDao/IxSqlQueryBuilder.h"
#include "../include/QxDao/QxSqlQueryBuilder.h"
#include "../include/QxDao/QxSqlQueryHelper.h"
#include "../include/QxDao/QxSqlQuery.h"
#include "../include/QxDao/QxSqlDatabase.h"
#include "../include/QxDao/IxSqlRelation.h"
#include "../include/QxDao/QxSqlRelation.h"
#include "../include/QxDao/QxSqlRelationParams.h"
#include "../include/QxDao/QxSqlRelation_ManyToMany.h"
#include "../include/QxDao/QxSqlRelation_ManyToOne.h"
#include "../include/QxDao/QxSqlRelation_OneToMany.h"
#include "../include/QxDao/QxSqlRelation_OneToOne.h"
#include "../include/QxDao/QxSqlRelation_RawData.h"
#include "../include/QxDao/QxDao.h"
#include "../include/QxDao/QxDao_Impl.h"

#include "../include/QxSerialize/QxSerialize.h"

#include "../include/QxCommon/QxStringCvt.h"
#include "../include/QxCommon/QxStringCvt_Impl.h"

#include "../include/QxRegister/IxClass.h"
#include "../include/QxRegister/QxClass.h"
#include "../include/QxRegister/QxClassX.h"
#include "../include/QxRegister/QxClassName.h"
#include "../include/QxRegister/QxRegister.h"

#endif // _QX_ORM_H_
