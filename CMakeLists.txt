#############################################################################
##
## http://www.qxorm.com/
## Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
##
## This file is part of the QxOrm library
##
## This software is provided 'as-is', without any express or implied
## warranty. In no event will the authors be held liable for any
## damages arising from the use of this software
##
## Commercial Usage
## Licensees holding valid commercial QxOrm licenses may use this file in
## accordance with the commercial license agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and Lionel Marty
##
## GNU General Public License Usage
## Alternatively, this file may be used under the terms of the GNU
## General Public License version 3.0 as published by the Free Software
## Foundation and appearing in the file 'license.gpl3.txt' included in the
## packaging of this file. Please review the following information to
## ensure the GNU General Public License version 3.0 requirements will be
## met : http://www.gnu.org/copyleft/gpl.html
##
## If you are unsure which license is appropriate for your use, or
## if you have questions regarding the use of this file, please contact :
## contact@qxorm.com
##
#############################################################################

cmake_minimum_required(VERSION 3.1)

project(QxOrm VERSION 1.4.3 LANGUAGES CXX)

# Include QxOrm library configuration file (should be included by all projects which depend on QxOrm)
include(./QxOrm.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_DEBUG_POSTFIX "d")

set(QX_HEADERS
    ./include/QxPrecompiled.h
    ./include/QxMemLeak/bool_array.h
    ./include/QxMemLeak/class_level_lock.h
    ./include/QxMemLeak/cont_ptr_utils.h
    ./include/QxMemLeak/debug_new.h
    ./include/QxMemLeak/fast_mutex.h
    ./include/QxMemLeak/fixed_mem_pool.h
    ./include/QxMemLeak/mem_leak.h
    ./include/QxMemLeak/mem_pool_base.h
    ./include/QxMemLeak/object_level_lock.h
    ./include/QxMemLeak/pctimer.h
    ./include/QxMemLeak/set_assign.h
    ./include/QxMemLeak/static_assert.h
    ./include/QxMemLeak/static_mem_pool.h
    ./include/QxSingleton/IxSingleton.h
    ./include/QxSingleton/QxSingleton.h
    ./include/QxSingleton/QxSingletonX.h
    ./include/QxSingleton/QxSingletonInit.h
    ./include/QxFactory/IxFactory.h
    ./include/QxFactory/QxFactory.h
    ./include/QxFactory/QxFactoryX.h
    ./include/QxCommon/QxConfig.h
    ./include/QxCommon/QxMacro.h
    ./include/QxCommon/QxHashValue.h
    ./include/QxCommon/QxBool.h
    ./include/QxCommon/QxCache.h
    ./include/QxCommon/QxPropertyBag.h
    ./include/QxCommon/QxSimpleCrypt.h
    ./include/QxCommon/QxAnyCastDynamic.h
    ./include/QxCommon/QxException.h
    ./include/QxCommon/QxExceptionCode.h
    ./include/QxConvert/QxConvert.h
    ./include/QxConvert/QxConvert_Impl.h
    ./include/QxConvert/QxConvert_Export.h
    ./include/QxRegister/IxClass.h
    ./include/QxRegister/QxClass.h
    ./include/QxRegister/QxClassX.h
    ./include/QxRegister/QxClassName.h
    ./include/QxRegister/QxRegister.h
    ./include/QxRegister/QxRegisterInternalHelper.h
    ./include/QxRegister/IxTypeInfo.h
    ./include/QxRegister/QxRegisterQtProperty.h
    ./include/QxCollection/IxCollection.h
    ./include/QxCollection/QxCollection.h
    ./include/QxCollection/QxCollectionIterator.h
    ./include/QxCollection/QxForeach.h
    ./include/QxDataMember/IxDataMember.h
    ./include/QxDataMember/IxDataMemberX.h
    ./include/QxDataMember/QxDataMember.h
    ./include/QxDataMember/QxDataMemberX.h
    ./include/QxDataMember/QxDataMember_QObject.h
    ./include/QxDao/IxSqlQueryBuilder.h
    ./include/QxDao/QxSqlQueryBuilder.h
    ./include/QxDao/QxSqlQueryHelper.h
    ./include/QxDao/QxSqlQuery.h
    ./include/QxDao/QxSqlDatabase.h
    ./include/QxDao/IxSqlRelation.h
    ./include/QxDao/QxSqlRelation.h
    ./include/QxDao/QxSqlRelationParams.h
    ./include/QxDao/QxSqlRelation_ManyToMany.h
    ./include/QxDao/QxSqlRelation_ManyToOne.h
    ./include/QxDao/QxSqlRelation_OneToMany.h
    ./include/QxDao/QxSqlRelation_OneToOne.h
    ./include/QxDao/QxSqlRelation_RawData.h
    ./include/QxDao/QxDao.h
    ./include/QxDao/QxDao_Impl.h
    ./include/QxDao/QxDaoStrategy.h
    ./include/QxDao/QxDaoPointer.h
    ./include/QxDao/QxDao_IsDirty.h
    ./include/QxDao/QxSoftDelete.h
    ./include/QxDao/QxSqlError.h
    ./include/QxDao/QxSession.h
    ./include/QxDao/QxDateNeutral.h
    ./include/QxDao/QxTimeNeutral.h
    ./include/QxDao/QxDateTimeNeutral.h
    ./include/QxDao/IxDao_Helper.h
    ./include/QxDao/IxPersistable.h
    ./include/QxDao/QxSqlJoin.h
    ./include/QxDao/QxSqlRelationLinked.h
    ./include/QxDao/QxDaoAsync.h
    ./include/QxDao/QxSqlSaveMode.h
    ./include/QxDao/QxDaoThrowable.h
    ./include/QxDao/QxSqlElement/IxSqlElement.h
    ./include/QxDao/QxSqlElement/QxSqlCompare.h
    ./include/QxDao/QxSqlElement/QxSqlElement.h
    ./include/QxDao/QxSqlElement/QxSqlElementTemp.h
    ./include/QxDao/QxSqlElement/QxSqlExpression.h
    ./include/QxDao/QxSqlElement/QxSqlFreeText.h
    ./include/QxDao/QxSqlElement/QxSqlIn.h
    ./include/QxDao/QxSqlElement/QxSqlIsBetween.h
    ./include/QxDao/QxSqlElement/QxSqlIsNull.h
    ./include/QxDao/QxSqlElement/QxSqlLimit.h
    ./include/QxDao/QxSqlElement/QxSqlSort.h
    ./include/QxDao/QxSqlGenerator/IxSqlGenerator.h
    ./include/QxDao/QxSqlGenerator/QxSqlGenerator.h
    ./include/QxDao/QxSqlGenerator/QxSqlGenerator_MySQL.h
    ./include/QxDao/QxSqlGenerator/QxSqlGenerator_Oracle.h
    ./include/QxDao/QxSqlGenerator/QxSqlGenerator_PostgreSQL.h
    ./include/QxDao/QxSqlGenerator/QxSqlGenerator_SQLite.h
    ./include/QxDao/QxSqlGenerator/QxSqlGenerator_MSSQLServer.h
    ./include/QxDao/QxSqlGenerator/QxSqlGenerator_Standard.h
    ./include/QxDao/QxRepository/IxRepository.h
    ./include/QxDao/QxRepository/QxRepository.h
    ./include/QxDao/QxRepository/QxRepositoryX.h
    ./include/QxSerialize/QxArchive.h
    ./include/QxSerialize/QxClone.h
    ./include/QxSerialize/QxDump.h
    ./include/QxSerialize/QxSerializeFastCompil.h
    ./include/QxSerialize/QxSerializeInvoker.h
    ./include/QxSerialize/QxSerializeMacro.h
    ./include/QxSerialize/QxSerialize.h
    ./include/QxSerialize/QxSerializeQDataStream.h
    ./include/QxSerialize/QxSerializeCheckInstance.h
    ./include/QxSerialize/QxSerializeQJson.h
    ./include/QxSerialize/boost/class_export/qx_boost_class_export.h
    ./include/QxSerialize/boost/portable_binary/portable_archive_exception.hpp
    ./include/QxSerialize/boost/portable_binary/portable_iarchive.hpp
    ./include/QxSerialize/boost/portable_binary/portable_oarchive.hpp
    ./include/QxSerialize/boost/QxSerializeInclude.h
    ./include/QxSerialize/boost/QxSerialize_shared_ptr.h
    ./include/QxSerialize/boost/QxSerialize_tuple.h
    ./include/QxSerialize/boost/QxSerialize_unordered_map.h
    ./include/QxSerialize/boost/QxSerialize_unordered_set.h
    ./include/QxSerialize/boost/QxExportDllMacroHpp.h
    ./include/QxSerialize/boost/QxExportDllMacroCpp.h
    ./include/QxSerialize/boost/QxExportDllBoostArchive.h
    ./include/QxSerialize/boost/QxImportDllBoostArchive.h
    ./include/QxSerialize/Qt/QxSerialize_QBrush.h
    ./include/QxSerialize/Qt/QxSerialize_QByteArray.h
    ./include/QxSerialize/Qt/QxSerialize_QColor.h
    ./include/QxSerialize/Qt/QxSerialize_QDate.h
    ./include/QxSerialize/Qt/QxSerialize_QDateTime.h
    ./include/QxSerialize/Qt/QxSerialize_QFont.h
    ./include/QxSerialize/Qt/QxSerialize_QHash.h
    ./include/QxSerialize/Qt/QxSerialize_QImage.h
    ./include/QxSerialize/Qt/QxSerialize_QFlags.h
    ./include/QxSerialize/Qt/QxSerialize_QLinkedList.h
    ./include/QxSerialize/Qt/QxSerialize_QList.h
    ./include/QxSerialize/Qt/QxSerialize_QMap.h
    ./include/QxSerialize/Qt/QxSerialize_QMatrix.h
    ./include/QxSerialize/Qt/QxSerialize_QObject.h
    ./include/QxSerialize/Qt/QxSerialize_QPair.h
    ./include/QxSerialize/Qt/QxSerialize_QPicture.h
    ./include/QxSerialize/Qt/QxSerialize_QPixmap.h
    ./include/QxSerialize/Qt/QxSerialize_QPoint.h
    ./include/QxSerialize/Qt/QxSerialize_QRect.h
    ./include/QxSerialize/Qt/QxSerialize_QRegExp.h
    ./include/QxSerialize/Qt/QxSerialize_QRegion.h
    ./include/QxSerialize/Qt/QxSerialize_QScopedPointer.h
    ./include/QxSerialize/Qt/QxSerialize_QSharedPointer.h
    ./include/QxSerialize/Qt/QxSerialize_QSize.h
    ./include/QxSerialize/Qt/QxSerialize_QString.h
    ./include/QxSerialize/Qt/QxSerialize_QTime.h
    ./include/QxSerialize/Qt/QxSerialize_QUrl.h
    ./include/QxSerialize/Qt/QxSerialize_QUuid.h
    ./include/QxSerialize/Qt/QxSerialize_QVariant.h
    ./include/QxSerialize/Qt/QxSerialize_QVector.h
    ./include/QxSerialize/Qt/QxSerialize_QWeakPointer.h
    ./include/QxSerialize/Qt/QxSerialize_QMultiHash.h
    ./include/QxSerialize/Qt/QxSerialize_QMultiMap.h
    ./include/QxSerialize/Qt/QxSerialize_QStringList.h
    ./include/QxSerialize/Qt/QxSerialize_QSqlError.h
    ./include/QxSerialize/Qx/QxSerialize_QxCollection.h
    ./include/QxSerialize/Qx/QxSerialize_QxDaoPointer.h
    ./include/QxSerialize/std/QxSerialize_std_tuple.h
    ./include/QxSerialize/std/QxSerialize_std_shared_ptr.h
    ./include/QxSerialize/std/QxSerialize_std_unique_ptr.h
    ./include/QxSerialize/std/QxSerialize_std_unordered_map.h
    ./include/QxSerialize/std/QxSerialize_std_unordered_set.h
    ./include/QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.h
    ./include/QxSerialize/QxBoostSerializeHelper/QxBoostInitGuid.h
    ./include/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeHelper.h
    ./include/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelper.h
    ./include/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_all_include.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_boost_optional.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_boost_scoped_ptr.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_boost_shared_ptr.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_boost_tuple.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_boost_unordered_map.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_boost_unordered_set.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_primitive_type.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_QFlags.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_QObject.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_QScopedPointer.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_QSharedPointer.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_QSqlError.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_QWeakPointer.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_list.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_map.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_pair.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_set.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_shared_ptr.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_string.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_tuple.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_unique_ptr.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_unordered_map.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_unordered_set.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_std_vector.h
    ./include/QxSerialize/QDataStream/QxSerializeQDataStream_qx_registered_class.h
    ./include/QxSerialize/QJson/QxSerializeQJson_all_include.h
    ./include/QxSerialize/QJson/QxSerializeQJson_boost_scoped_ptr.h
    ./include/QxSerialize/QJson/QxSerializeQJson_boost_shared_ptr.h
    ./include/QxSerialize/QJson/QxSerializeQJson_boost_tuple.h
    ./include/QxSerialize/QJson/QxSerializeQJson_boost_unordered_map.h
    ./include/QxSerialize/QJson/QxSerializeQJson_boost_unordered_set.h
    ./include/QxSerialize/QJson/QxSerializeQJson_IxParameter.h
    ./include/QxSerialize/QJson/QxSerializeQJson_IxService.h
    ./include/QxSerialize/QJson/QxSerializeQJson_IxSqlElement.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QBrush.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QColor.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QFlags.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QFont.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QHash.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QImage.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QLinkedList.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QList.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QMap.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QMatrix.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QMultiHash.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QMultiMap.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QObject.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QPair.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QPicture.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QPixmap.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QPoint.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QRect.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QRegExp.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QRegion.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QScopedPointer.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QSharedPointer.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QSize.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QSqlError.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QStringList.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QUrl.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QVector.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QWeakPointer.h
    ./include/QxSerialize/QJson/QxSerializeQJson_qx_registered_class.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QxCollection.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QxDaoPointer.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QxInvalidValue.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QxInvalidValueX.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QxSqlQuery.h
    ./include/QxSerialize/QJson/QxSerializeQJson_QxTransaction.h
    ./include/QxSerialize/QJson/QxSerializeQJson_std_list.h
    ./include/QxSerialize/QJson/QxSerializeQJson_std_map.h
    ./include/QxSerialize/QJson/QxSerializeQJson_std_pair.h
    ./include/QxSerialize/QJson/QxSerializeQJson_std_set.h
    ./include/QxSerialize/QJson/QxSerializeQJson_std_shared_ptr.h
    ./include/QxSerialize/QJson/QxSerializeQJson_std_tuple.h
    ./include/QxSerialize/QJson/QxSerializeQJson_std_unique_ptr.h
    ./include/QxSerialize/QJson/QxSerializeQJson_std_unordered_map.h
    ./include/QxSerialize/QJson/QxSerializeQJson_std_unordered_set.h
    ./include/QxSerialize/QJson/QxSerializeQJson_std_vector.h
    ./include/QxTraits/get_base_class.h
    ./include/QxTraits/get_primary_key.h
    ./include/QxTraits/get_class_name.h
    ./include/QxTraits/get_class_name_primitive.h
    ./include/QxTraits/is_boost_intrusive_ptr.h
    ./include/QxTraits/is_boost_scoped_ptr.h
    ./include/QxTraits/is_boost_shared_ptr.h
    ./include/QxTraits/is_boost_weak_ptr.h
    ./include/QxTraits/is_qt_shared_data_ptr.h
    ./include/QxTraits/is_qt_shared_ptr.h
    ./include/QxTraits/is_qt_scoped_ptr.h
    ./include/QxTraits/is_qt_weak_ptr.h
    ./include/QxTraits/is_smart_ptr.h
    ./include/QxTraits/is_boost_unordered_map.h
    ./include/QxTraits/is_boost_unordered_set.h
    ./include/QxTraits/is_container.h
    ./include/QxTraits/is_qt_hash.h
    ./include/QxTraits/is_qt_linked_list.h
    ./include/QxTraits/is_qt_list.h
    ./include/QxTraits/is_qt_map.h
    ./include/QxTraits/is_qt_multi_hash.h
    ./include/QxTraits/is_qt_multi_map.h
    ./include/QxTraits/is_qt_set.h
    ./include/QxTraits/is_qt_vector.h
    ./include/QxTraits/is_qt_variant_compatible.h
    ./include/QxTraits/is_qx_collection.h
    ./include/QxTraits/is_std_list.h
    ./include/QxTraits/is_std_map.h
    ./include/QxTraits/is_std_set.h
    ./include/QxTraits/is_std_vector.h
    ./include/QxTraits/is_container_base_of.h
    ./include/QxTraits/is_container_key_value.h
    ./include/QxTraits/is_container_to_pod.h
    ./include/QxTraits/is_ptr_base_of.h
    ./include/QxTraits/is_ptr_to_pod.h
    ./include/QxTraits/is_qx_pod.h
    ./include/QxTraits/is_qx_registered.h
    ./include/QxTraits/is_smart_ptr_base_of.h
    ./include/QxTraits/is_smart_ptr_to_pod.h
    ./include/QxTraits/archive_wide_traits.h
    ./include/QxTraits/archive_printable.h
    ./include/QxTraits/remove_attr.h
    ./include/QxTraits/remove_smart_ptr.h
    ./include/QxTraits/construct_ptr.h
    ./include/QxTraits/get_sql_type.h
    ./include/QxTraits/generic_container.h
    ./include/QxTraits/is_valid_primary_key.h
    ./include/QxTraits/is_qx_dao_ptr.h
    ./include/QxTraits/is_equal.h
    ./include/QxTraits/qt_meta_object.h
    ./include/QxTraits/qx_traits.h
    ./include/QxTraits/is_std_shared_ptr.h
    ./include/QxTraits/is_std_unique_ptr.h
    ./include/QxTraits/is_std_unordered_map.h
    ./include/QxTraits/is_std_unordered_set.h
    ./include/QxTraits/is_std_weak_ptr.h
    ./include/QxFunction/IxFunction.h
    ./include/QxFunction/QxFunction_0.h
    ./include/QxFunction/QxFunction_1.h
    ./include/QxFunction/QxFunction_2.h
    ./include/QxFunction/QxFunction_3.h
    ./include/QxFunction/QxFunction_4.h
    ./include/QxFunction/QxFunction_5.h
    ./include/QxFunction/QxFunction_6.h
    ./include/QxFunction/QxFunction_7.h
    ./include/QxFunction/QxFunction_8.h
    ./include/QxFunction/QxFunction_9.h
    ./include/QxFunction/QxFunctionError.h
    ./include/QxFunction/QxFunctionInclude.h
    ./include/QxFunction/QxFunctionMacro.h
    ./include/QxFunction/QxParameters.h
    ./include/QxService/IxParameter.h
    ./include/QxService/IxService.h
    ./include/QxService/QxClientAsync.h
    ./include/QxService/QxConnect.h
    ./include/QxService/QxServer.h
    ./include/QxService/QxService.h
    ./include/QxService/QxThread.h
    ./include/QxService/QxThreadPool.h
    ./include/QxService/QxTools.h
    ./include/QxService/QxTransaction.h
    ./include/QxValidator/IxValidator.h
    ./include/QxValidator/IxValidatorX.h
    ./include/QxValidator/QxInvalidValue.h
    ./include/QxValidator/QxInvalidValueX.h
    ./include/QxValidator/QxValidator.h
    ./include/QxValidator/QxValidatorError.h
    ./include/QxValidator/QxValidatorFct.h
    ./include/QxValidator/QxValidatorX.h
    ./include/QxModelView/IxModel.h
    ./include/QxModelView/QxModel.h
    ./include/QxModelView/QxNestedModel.h
    ./include/QxModelView/QxModelService.h
    ./include/QxOrm.h
    ./include/QxOrm_Impl.h
    ./include/QxMemLeak.h
   )

# To reduce compilation times, it is recommended to define _QX_UNITY_BUILD compilation option
# More details in QxOrm.cmake configuration file, section 'Unity Build'
if(_QX_UNITY_BUILD)

   set(QX_SRCS
       ./src/all.cpp
      )

else() # _QX_UNITY_BUILD

   set(QX_SRCS
       ./src/QxMemLeak/bool_array.cpp
       ./src/QxMemLeak/debug_new.cpp
       ./src/QxMemLeak/mem_pool_base.cpp
       ./src/QxMemLeak/static_mem_pool.cpp
       ./src/QxSingleton/IxSingleton.cpp
       ./src/QxSingleton/QxSingletonX.cpp
       ./src/QxSingleton/QxSingletonInit.cpp
       ./src/QxFactory/IxFactory.cpp
       ./src/QxFactory/QxFactoryX.cpp
       ./src/QxCollection/QxCollection.cpp
       ./src/QxCommon/QxBool.cpp
       ./src/QxCommon/QxCache.cpp
       ./src/QxCommon/QxSimpleCrypt.cpp
       ./src/QxConvert/QxConvert_Export.cpp
       ./src/QxRegister/IxClass.cpp
       ./src/QxRegister/QxClassX.cpp
       ./src/QxDataMember/IxDataMember.cpp
       ./src/QxDataMember/IxDataMemberX.cpp
       ./src/QxDataMember/QxDataMember_QObject.cpp
       ./src/QxTraits/unit_test_is_smart_ptr.cpp
       ./src/QxTraits/unit_test_is_container.cpp
       ./src/QxDao/IxSqlQueryBuilder.cpp
       ./src/QxDao/QxSqlDatabase.cpp
       ./src/QxDao/IxSqlRelation.cpp
       ./src/QxDao/QxSqlQuery.cpp
       ./src/QxDao/QxSession.cpp
       ./src/QxDao/IxDao_Helper.cpp
       ./src/QxDao/IxPersistable.cpp
       ./src/QxDao/QxSqlRelationLinked.cpp
       ./src/QxDao/QxDaoAsync.cpp
       ./src/QxDao/QxSqlRelationParams.cpp
       ./src/QxDao/QxSoftDelete.cpp
       ./src/QxDao/QxDateNeutral.cpp
       ./src/QxDao/QxDateTimeNeutral.cpp
       ./src/QxDao/QxTimeNeutral.cpp
       ./src/QxDao/QxSqlElement/IxSqlElement.cpp
       ./src/QxDao/QxSqlElement/QxSqlCompare.cpp
       ./src/QxDao/QxSqlElement/QxSqlElementTemp.cpp
       ./src/QxDao/QxSqlElement/QxSqlExpression.cpp
       ./src/QxDao/QxSqlElement/QxSqlFreeText.cpp
       ./src/QxDao/QxSqlElement/QxSqlIn.cpp
       ./src/QxDao/QxSqlElement/QxSqlIsBetween.cpp
       ./src/QxDao/QxSqlElement/QxSqlIsNull.cpp
       ./src/QxDao/QxSqlElement/QxSqlLimit.cpp
       ./src/QxDao/QxSqlElement/QxSqlSort.cpp
       ./src/QxDao/QxSqlGenerator/IxSqlGenerator.cpp
       ./src/QxDao/QxSqlGenerator/QxSqlGenerator_MySQL.cpp
       ./src/QxDao/QxSqlGenerator/QxSqlGenerator_Oracle.cpp
       ./src/QxDao/QxSqlGenerator/QxSqlGenerator_PostgreSQL.cpp
       ./src/QxDao/QxSqlGenerator/QxSqlGenerator_SQLite.cpp
       ./src/QxDao/QxSqlGenerator/QxSqlGenerator_MSSQLServer.cpp
       ./src/QxDao/QxSqlGenerator/QxSqlGenerator_Standard.cpp
       ./src/QxDao/QxRepository/IxRepository.cpp
       ./src/QxDao/QxRepository/QxRepositoryX.cpp
       ./src/QxSerialize/QxSerializeCheckInstance.cpp
       ./src/QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.cpp
       ./src/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.cpp
       ./src/QxSerialize/boost/QxExportDllBoostArchive.cpp
       ./src/QxSerialize/Qt/QxSerialize_QBrush.cpp
       ./src/QxSerialize/Qt/QxSerialize_QByteArray.cpp
       ./src/QxSerialize/Qt/QxSerialize_QColor.cpp
       ./src/QxSerialize/Qt/QxSerialize_QDate.cpp
       ./src/QxSerialize/Qt/QxSerialize_QDateTime.cpp
       ./src/QxSerialize/Qt/QxSerialize_QFont.cpp
       ./src/QxSerialize/Qt/QxSerialize_QImage.cpp
       ./src/QxSerialize/Qt/QxSerialize_QMatrix.cpp
       ./src/QxSerialize/Qt/QxSerialize_QObject.cpp
       ./src/QxSerialize/Qt/QxSerialize_QPicture.cpp
       ./src/QxSerialize/Qt/QxSerialize_QPixmap.cpp
       ./src/QxSerialize/Qt/QxSerialize_QPoint.cpp
       ./src/QxSerialize/Qt/QxSerialize_QRect.cpp
       ./src/QxSerialize/Qt/QxSerialize_QRegExp.cpp
       ./src/QxSerialize/Qt/QxSerialize_QRegion.cpp
       ./src/QxSerialize/Qt/QxSerialize_QSize.cpp
       ./src/QxSerialize/Qt/QxSerialize_QString.cpp
       ./src/QxSerialize/Qt/QxSerialize_QStringList.cpp
       ./src/QxSerialize/Qt/QxSerialize_QTime.cpp
       ./src/QxSerialize/Qt/QxSerialize_QUrl.cpp
       ./src/QxSerialize/Qt/QxSerialize_QUuid.cpp
       ./src/QxSerialize/Qt/QxSerialize_QVariant.cpp
       ./src/QxSerialize/Qt/QxSerialize_QSqlError.cpp
       ./src/QxSerialize/QDataStream/QxSerializeQDataStream_primitive_type.cpp
       ./src/QxSerialize/QDataStream/QxSerializeQDataStream_QObject.cpp
       ./src/QxSerialize/QDataStream/QxSerializeQDataStream_QSqlError.cpp
       ./src/QxSerialize/QDataStream/QxSerializeQDataStream_std_string.cpp
       ./src/QxSerialize/QDataStream/QxSerializeQDataStream_qx_registered_class.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_qx_registered_class.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_IxService.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_IxSqlElement.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QBrush.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QColor.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QFont.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QImage.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QMatrix.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QObject.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QPicture.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QPixmap.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QPoint.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QRect.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QRegExp.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QRegion.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QSize.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QSqlError.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QStringList.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QxInvalidValue.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QxInvalidValueX.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QxSqlQuery.cpp
       ./src/QxSerialize/QJson/QxSerializeQJson_QxTransaction.cpp
       ./src/QxService/IxParameter.cpp
       ./src/QxService/IxService.cpp
       ./src/QxService/QxConnect.cpp
       ./src/QxService/QxServer.cpp
       ./src/QxService/QxThread.cpp
       ./src/QxService/QxThreadPool.cpp
       ./src/QxService/QxTools.cpp
       ./src/QxService/QxTransaction.cpp
       ./src/QxValidator/IxValidator.cpp
       ./src/QxValidator/IxValidatorX.cpp
       ./src/QxValidator/QxInvalidValue.cpp
       ./src/QxValidator/QxInvalidValueX.cpp
       ./src/QxModelView/IxModel.cpp
       ./src/QxModelView/QxNestedModel.cpp
       ./src/main.cpp
      )

endif() # _QX_UNITY_BUILD

set(QX_INLS
    ./inl/QxCollection/QxCollection.inl
    ./inl/QxCollection/QxCollectionIterator.inl
    ./inl/QxConvert/QxConvert_FromString.inl
    ./inl/QxConvert/QxConvert_FromVariant.inl
    ./inl/QxConvert/QxConvert_FromJson.inl
    ./inl/QxConvert/QxConvert_Qt.inl
    ./inl/QxConvert/QxConvert_ToString.inl
    ./inl/QxConvert/QxConvert_ToVariant.inl
    ./inl/QxConvert/QxConvert_ToJson.inl
    ./inl/QxConvert/QxConvert_WithIndex.inl
    ./inl/QxDao/QxDao_Count.inl
    ./inl/QxDao/QxDao_CreateTable.inl
    ./inl/QxDao/QxDao_DeleteAll.inl
    ./inl/QxDao/QxDao_DeleteById.inl
    ./inl/QxDao/QxDao_ExecuteQuery.inl
    ./inl/QxDao/QxDao_Exist.inl
    ./inl/QxDao/QxDao_FetchAll.inl
    ./inl/QxDao/QxDao_FetchAll_WithRelation.inl
    ./inl/QxDao/QxDao_FetchById.inl
    ./inl/QxDao/QxDao_FetchById_WithRelation.inl
    ./inl/QxDao/QxDao_Helper.inl
    ./inl/QxDao/QxDao_Helper_Container.inl
    ./inl/QxDao/QxDao_Insert.inl
    ./inl/QxDao/QxDao_Insert_WithRelation.inl
    ./inl/QxDao/QxDao_Save.inl
    ./inl/QxDao/QxDao_Save_WithRelation.inl
    ./inl/QxDao/QxDao_Save_WithRelation_Recursive.inl
    ./inl/QxDao/QxDao_Trigger.inl
    ./inl/QxDao/QxDao_Update.inl
    ./inl/QxDao/QxDao_Update_Optimized.inl
    ./inl/QxDao/QxDao_Update_WithRelation.inl
    ./inl/QxDao/QxSqlQueryHelper_CreateTable.inl
    ./inl/QxDao/QxSqlQueryHelper_DeleteById.inl
    ./inl/QxDao/QxSqlQueryHelper_Exist.inl
    ./inl/QxDao/QxSqlQueryHelper_FetchAll.inl
    ./inl/QxDao/QxSqlQueryHelper_FetchAll_WithRelation.inl
    ./inl/QxDao/QxSqlQueryHelper_FetchById.inl
    ./inl/QxDao/QxSqlQueryHelper_FetchById_WithRelation.inl
    ./inl/QxDao/QxSqlQueryHelper_Insert.inl
    ./inl/QxDao/QxSqlQueryHelper_Update.inl
    ./inl/QxDataMember/QxDataMember.inl
    ./inl/QxDataMember/QxDataMemberX.inl
    ./inl/QxFactory/QxFactory.inl
    ./inl/QxRegister/QxClass.inl
    ./inl/QxSerialize/QxArchive.inl
    ./inl/QxSerialize/QxSerializeInvoker.inl
    ./inl/QxSingleton/QxSingleton.inl
   )

if(_QX_STATIC_BUILD)
   add_library(QxOrm STATIC ${QX_SRCS} ${QX_HEADERS} ${QX_INLS})
else()
   add_library(QxOrm SHARED ${QX_SRCS} ${QX_HEADERS} ${QX_INLS})
endif()

target_compile_definitions(QxOrm PRIVATE -D_QX_BUILDING_QX_ORM)

target_link_libraries(QxOrm ${QX_LIBRARIES})

set_target_properties(QxOrm PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                      RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/lib"
                     )

# To sort all files by folder in MSVC and XCode solution
qx_auto_source_group("${QX_SRCS};${QX_HEADERS};${QX_INLS}")

# Define CMAKE_INSTALL_PREFIX variable to put the location where to copy all files
install(TARGETS QxOrm DESTINATION lib)
install(DIRECTORY ./include/ DESTINATION include)
install(DIRECTORY ./inl/ DESTINATION inl)
