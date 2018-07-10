#############################################################################
##
## http://www.qxorm.com/
## http://sourceforge.net/projects/qxorm/
## Original file by Lionel Marty
##
## This file is part of the QxOrm library
##
## This software is provided 'as-is', without any express or implied
## warranty. In no event will the authors be held liable for any
## damages arising from the use of this software.
##
## GNU Lesser General Public License Usage
## This file must be used under the terms of the GNU Lesser
## General Public License version 2.1 as published by the Free Software
## Foundation and appearing in the file 'license.lgpl.txt' included in the
## packaging of this file.  Please review the following information to
## ensure the GNU Lesser General Public License version 2.1 requirements
## will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## If you have questions regarding the use of this file, please contact :
## contact@qxorm.com
##
#############################################################################

include(./QxOrm.pri)

######################
# Globals Parameters #
######################

TEMPLATE = lib
CONFIG += dll
DEFINES += _QX_BUILDING_QX_ORM
PRECOMPILED_HEADER = ./include/QxPrecompiled.h

unix { VERSION = 1.2.3 }

contains(DEFINES, _QX_STATIC_BUILD) {
CONFIG -= dll
CONFIG += staticlib
}

#############################
# Compiler / Linker Options #
#############################

CONFIG(debug, debug|release) {
TARGET = QxOrmd
} else {
TARGET = QxOrm
} # CONFIG(debug, debug|release)

unix {
DESTDIR = ./lib/
target.path = /usr/local/lib/
headers.path = /usr/local/include/
headers.files = ./include/*
INSTALLS = target headers
} # unix

#################
# Headers Files #
#################

HEADERS += ./include/QxPrecompiled.h

HEADERS += ./include/QxMemLeak/bool_array.h
HEADERS += ./include/QxMemLeak/class_level_lock.h
HEADERS += ./include/QxMemLeak/cont_ptr_utils.h
HEADERS += ./include/QxMemLeak/debug_new.h
HEADERS += ./include/QxMemLeak/fast_mutex.h
HEADERS += ./include/QxMemLeak/fixed_mem_pool.h
HEADERS += ./include/QxMemLeak/mem_leak.h
HEADERS += ./include/QxMemLeak/mem_pool_base.h
HEADERS += ./include/QxMemLeak/object_level_lock.h
HEADERS += ./include/QxMemLeak/pctimer.h
HEADERS += ./include/QxMemLeak/set_assign.h
HEADERS += ./include/QxMemLeak/static_assert.h
HEADERS += ./include/QxMemLeak/static_mem_pool.h

HEADERS += ./include/QxSingleton/IxSingleton.h
HEADERS += ./include/QxSingleton/QxSingleton.h
HEADERS += ./include/QxSingleton/QxSingletonX.h

HEADERS += ./include/QxFactory/IxFactory.h
HEADERS += ./include/QxFactory/QxFactory.h
HEADERS += ./include/QxFactory/QxFactoryX.h

HEADERS += ./include/QxCommon/QxConfig.h
HEADERS += ./include/QxCommon/QxMacro.h
HEADERS += ./include/QxCommon/QxHashValue.h
HEADERS += ./include/QxCommon/QxBool.h
HEADERS += ./include/QxCommon/QxCache.h
HEADERS += ./include/QxCommon/QxStringCvt.h
HEADERS += ./include/QxCommon/QxStringCvt_Impl.h
HEADERS += ./include/QxCommon/QxStringCvt_Export.h
HEADERS += ./include/QxCommon/QxPropertyBag.h
HEADERS += ./include/QxCommon/QxSimpleCrypt.h
HEADERS += ./include/QxCommon/QxAnyCastDynamic.h

HEADERS += ./include/QxRegister/IxClass.h
HEADERS += ./include/QxRegister/QxClass.h
HEADERS += ./include/QxRegister/QxClassX.h
HEADERS += ./include/QxRegister/QxClassName.h
HEADERS += ./include/QxRegister/QxRegister.h
HEADERS += ./include/QxRegister/QxRegisterInternalHelper.h
HEADERS += ./include/QxRegister/IxTypeInfo.h
HEADERS += ./include/QxRegister/QxRegisterQtProperty.h

HEADERS += ./include/QxCollection/IxCollection.h
HEADERS += ./include/QxCollection/QxCollection.h
HEADERS += ./include/QxCollection/QxCollectionIterator.h
HEADERS += ./include/QxCollection/QxForeach.h

HEADERS += ./include/QxDataMember/IxDataMember.h
HEADERS += ./include/QxDataMember/IxDataMemberX.h
HEADERS += ./include/QxDataMember/QxDataMember.h
HEADERS += ./include/QxDataMember/QxDataMemberX.h
HEADERS += ./include/QxDataMember/QxDataMember_QObject.h

HEADERS += ./include/QxDao/IxSqlQueryBuilder.h
HEADERS += ./include/QxDao/QxSqlQueryBuilder.h
HEADERS += ./include/QxDao/QxSqlQueryHelper.h
HEADERS += ./include/QxDao/QxSqlQuery.h
HEADERS += ./include/QxDao/QxSqlDatabase.h
HEADERS += ./include/QxDao/IxSqlRelation.h
HEADERS += ./include/QxDao/QxSqlRelation.h
HEADERS += ./include/QxDao/QxSqlRelationParams.h
HEADERS += ./include/QxDao/QxSqlRelation_ManyToMany.h
HEADERS += ./include/QxDao/QxSqlRelation_ManyToOne.h
HEADERS += ./include/QxDao/QxSqlRelation_OneToMany.h
HEADERS += ./include/QxDao/QxSqlRelation_OneToOne.h
HEADERS += ./include/QxDao/QxSqlRelation_RawData.h
HEADERS += ./include/QxDao/QxDao.h
HEADERS += ./include/QxDao/QxDao_Impl.h
HEADERS += ./include/QxDao/QxDaoStrategy.h
HEADERS += ./include/QxDao/QxDaoPointer.h
HEADERS += ./include/QxDao/QxDao_IsDirty.h
HEADERS += ./include/QxDao/QxSoftDelete.h
HEADERS += ./include/QxDao/QxSqlError.h
HEADERS += ./include/QxDao/QxSession.h
HEADERS += ./include/QxDao/QxDateNeutral.h
HEADERS += ./include/QxDao/QxTimeNeutral.h
HEADERS += ./include/QxDao/QxDateTimeNeutral.h
HEADERS += ./include/QxDao/IxDao_Helper.h
HEADERS += ./include/QxDao/IxPersistable.h

HEADERS += ./include/QxDao/QxSqlElement/IxSqlElement.h
HEADERS += ./include/QxDao/QxSqlElement/QxSqlCompare.h
HEADERS += ./include/QxDao/QxSqlElement/QxSqlElement.h
HEADERS += ./include/QxDao/QxSqlElement/QxSqlElementTemp.h
HEADERS += ./include/QxDao/QxSqlElement/QxSqlExpression.h
HEADERS += ./include/QxDao/QxSqlElement/QxSqlFreeText.h
HEADERS += ./include/QxDao/QxSqlElement/QxSqlIn.h
HEADERS += ./include/QxDao/QxSqlElement/QxSqlIsBetween.h
HEADERS += ./include/QxDao/QxSqlElement/QxSqlIsNull.h
HEADERS += ./include/QxDao/QxSqlElement/QxSqlLimit.h
HEADERS += ./include/QxDao/QxSqlElement/QxSqlSort.h

HEADERS += ./include/QxDao/QxSqlGenerator/IxSqlGenerator.h
HEADERS += ./include/QxDao/QxSqlGenerator/QxSqlGenerator.h
HEADERS += ./include/QxDao/QxSqlGenerator/QxSqlGenerator_MySQL.h
HEADERS += ./include/QxDao/QxSqlGenerator/QxSqlGenerator_Oracle.h
HEADERS += ./include/QxDao/QxSqlGenerator/QxSqlGenerator_PostgreSQL.h
HEADERS += ./include/QxDao/QxSqlGenerator/QxSqlGenerator_SQLite.h
HEADERS += ./include/QxDao/QxSqlGenerator/QxSqlGenerator_MSSQLServer.h
HEADERS += ./include/QxDao/QxSqlGenerator/QxSqlGenerator_Standard.h

HEADERS += ./include/QxDao/QxRepository/IxRepository.h
HEADERS += ./include/QxDao/QxRepository/QxRepository.h
HEADERS += ./include/QxDao/QxRepository/QxRepositoryX.h

HEADERS += ./include/QxSerialize/QxArchive.h
HEADERS += ./include/QxSerialize/QxClone.h
HEADERS += ./include/QxSerialize/QxDump.h
HEADERS += ./include/QxSerialize/QxSerializeFastCompil.h
HEADERS += ./include/QxSerialize/QxSerializeInvoker.h
HEADERS += ./include/QxSerialize/QxSerializeMacro.h
HEADERS += ./include/QxSerialize/QxSerialize.h

HEADERS += ./include/QxSerialize/boost/class_export/qx_boost_class_export.h
HEADERS += ./include/QxSerialize/boost/portable_binary/portable_archive_exception.hpp
HEADERS += ./include/QxSerialize/boost/portable_binary/portable_iarchive.hpp
HEADERS += ./include/QxSerialize/boost/portable_binary/portable_oarchive.hpp
HEADERS += ./include/QxSerialize/boost/QxSerializeInclude.h
HEADERS += ./include/QxSerialize/boost/QxSerialize_shared_ptr.h
HEADERS += ./include/QxSerialize/boost/QxSerialize_tuple.h
HEADERS += ./include/QxSerialize/boost/QxSerialize_unordered_map.h
HEADERS += ./include/QxSerialize/boost/QxSerialize_unordered_set.h
HEADERS += ./include/QxSerialize/boost/QxExportDllMacroHpp.h
HEADERS += ./include/QxSerialize/boost/QxExportDllMacroCpp.h
HEADERS += ./include/QxSerialize/boost/QxExportDllBoostArchive.h
HEADERS += ./include/QxSerialize/boost/QxImportDllBoostArchive.h

HEADERS += ./include/QxSerialize/Qt/QxSerialize_QBrush.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QByteArray.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QColor.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QDate.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QDateTime.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QFont.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QHash.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QImage.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QLinkedList.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QList.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QMap.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QMatrix.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QObject.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QPair.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QPicture.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QPixmap.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QPoint.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QRect.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QRegExp.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QRegion.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QScopedPointer.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QSharedPointer.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QSize.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QString.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QTime.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QUrl.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QUuid.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QVariant.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QVector.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QWeakPointer.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QMultiHash.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QMultiMap.h
HEADERS += ./include/QxSerialize/Qt/QxSerialize_QStringList.h

HEADERS += ./include/QxSerialize/Qx/QxSerialize_QxCollection.h
HEADERS += ./include/QxSerialize/Qx/QxSerialize_QxXmlReader.h
HEADERS += ./include/QxSerialize/Qx/QxSerialize_QxXmlWriter.h
HEADERS += ./include/QxSerialize/Qx/QxSerialize_QxDaoPointer.h

HEADERS += ./include/QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.h
HEADERS += ./include/QxSerialize/QxBoostSerializeHelper/QxBoostInitGuid.h
HEADERS += ./include/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeHelper.h
HEADERS += ./include/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelper.h
HEADERS += ./include/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.h

HEADERS += ./include/QxTraits/get_base_class.h
HEADERS += ./include/QxTraits/get_primary_key.h
HEADERS += ./include/QxTraits/get_class_name.h
HEADERS += ./include/QxTraits/get_class_name_primitive.h
HEADERS += ./include/QxTraits/is_boost_intrusive_ptr.h
HEADERS += ./include/QxTraits/is_boost_scoped_ptr.h
HEADERS += ./include/QxTraits/is_boost_shared_ptr.h
HEADERS += ./include/QxTraits/is_boost_weak_ptr.h
HEADERS += ./include/QxTraits/is_qt_shared_data_ptr.h
HEADERS += ./include/QxTraits/is_qt_shared_ptr.h
HEADERS += ./include/QxTraits/is_qt_scoped_ptr.h
HEADERS += ./include/QxTraits/is_qt_weak_ptr.h
HEADERS += ./include/QxTraits/is_smart_ptr.h
HEADERS += ./include/QxTraits/is_boost_unordered_map.h
HEADERS += ./include/QxTraits/is_boost_unordered_set.h
HEADERS += ./include/QxTraits/is_container.h
HEADERS += ./include/QxTraits/is_qt_hash.h
HEADERS += ./include/QxTraits/is_qt_linked_list.h
HEADERS += ./include/QxTraits/is_qt_list.h
HEADERS += ./include/QxTraits/is_qt_map.h
HEADERS += ./include/QxTraits/is_qt_multi_hash.h
HEADERS += ./include/QxTraits/is_qt_multi_map.h
HEADERS += ./include/QxTraits/is_qt_set.h
HEADERS += ./include/QxTraits/is_qt_vector.h
HEADERS += ./include/QxTraits/is_qt_variant_compatible.h
HEADERS += ./include/QxTraits/is_qx_collection.h
HEADERS += ./include/QxTraits/is_std_list.h
HEADERS += ./include/QxTraits/is_std_map.h
HEADERS += ./include/QxTraits/is_std_set.h
HEADERS += ./include/QxTraits/is_std_vector.h
HEADERS += ./include/QxTraits/is_container_base_of.h
HEADERS += ./include/QxTraits/is_container_key_value.h
HEADERS += ./include/QxTraits/is_container_to_pod.h
HEADERS += ./include/QxTraits/is_ptr_base_of.h
HEADERS += ./include/QxTraits/is_ptr_to_pod.h
HEADERS += ./include/QxTraits/is_qx_pod.h
HEADERS += ./include/QxTraits/is_qx_registered.h
HEADERS += ./include/QxTraits/is_smart_ptr_base_of.h
HEADERS += ./include/QxTraits/is_smart_ptr_to_pod.h
HEADERS += ./include/QxTraits/archive_wide_traits.h
HEADERS += ./include/QxTraits/archive_printable.h
HEADERS += ./include/QxTraits/remove_attr.h
HEADERS += ./include/QxTraits/remove_smart_ptr.h
HEADERS += ./include/QxTraits/construct_ptr.h
HEADERS += ./include/QxTraits/get_sql_type.h
HEADERS += ./include/QxTraits/generic_container.h
HEADERS += ./include/QxTraits/is_valid_primary_key.h
HEADERS += ./include/QxTraits/is_qx_dao_ptr.h
HEADERS += ./include/QxTraits/is_equal.h
HEADERS += ./include/QxTraits/qt_meta_object.h
HEADERS += ./include/QxTraits/qx_traits.h

HEADERS += ./include/QxFunction/IxFunction.h
HEADERS += ./include/QxFunction/QxFunction_0.h
HEADERS += ./include/QxFunction/QxFunction_1.h
HEADERS += ./include/QxFunction/QxFunction_2.h
HEADERS += ./include/QxFunction/QxFunction_3.h
HEADERS += ./include/QxFunction/QxFunction_4.h
HEADERS += ./include/QxFunction/QxFunction_5.h
HEADERS += ./include/QxFunction/QxFunction_6.h
HEADERS += ./include/QxFunction/QxFunction_7.h
HEADERS += ./include/QxFunction/QxFunction_8.h
HEADERS += ./include/QxFunction/QxFunction_9.h
HEADERS += ./include/QxFunction/QxFunctionError.h
HEADERS += ./include/QxFunction/QxFunctionInclude.h
HEADERS += ./include/QxFunction/QxFunctionMacro.h
HEADERS += ./include/QxFunction/QxParameters.h

HEADERS += ./include/QxService/IxParameter.h
HEADERS += ./include/QxService/IxService.h
HEADERS += ./include/QxService/QxClientAsync.h
HEADERS += ./include/QxService/QxConnect.h
HEADERS += ./include/QxService/QxServer.h
HEADERS += ./include/QxService/QxService.h
HEADERS += ./include/QxService/QxThread.h
HEADERS += ./include/QxService/QxThreadPool.h
HEADERS += ./include/QxService/QxTools.h
HEADERS += ./include/QxService/QxTransaction.h

HEADERS += ./include/QxXml/QxXmlReader.h
HEADERS += ./include/QxXml/QxXmlWriter.h
HEADERS += ./include/QxXml/QxXml.h

HEADERS += ./include/QxValidator/IxValidator.h
HEADERS += ./include/QxValidator/IxValidatorX.h
HEADERS += ./include/QxValidator/QxInvalidValue.h
HEADERS += ./include/QxValidator/QxInvalidValueX.h
HEADERS += ./include/QxValidator/QxValidator.h
HEADERS += ./include/QxValidator/QxValidatorError.h
HEADERS += ./include/QxValidator/QxValidatorFct.h
HEADERS += ./include/QxValidator/QxValidatorX.h

HEADERS += ./include/QxOrm.h
HEADERS += ./include/QxMemLeak.h

#################
# Sources Files #
#################

SOURCES += ./src/QxMemLeak/bool_array.cpp
SOURCES += ./src/QxMemLeak/debug_new.cpp
SOURCES += ./src/QxMemLeak/mem_pool_base.cpp
SOURCES += ./src/QxMemLeak/static_mem_pool.cpp

SOURCES += ./src/QxSingleton/IxSingleton.cpp
SOURCES += ./src/QxSingleton/QxSingletonX.cpp

SOURCES += ./src/QxFactory/IxFactory.cpp
SOURCES += ./src/QxFactory/QxFactoryX.cpp

SOURCES += ./src/QxCollection/QxCollection.cpp

SOURCES += ./src/QxCommon/QxCache.cpp
SOURCES += ./src/QxCommon/QxStringCvt_Export.cpp
SOURCES += ./src/QxCommon/QxSimpleCrypt.cpp

SOURCES += ./src/QxRegister/IxClass.cpp
SOURCES += ./src/QxRegister/QxClassX.cpp

SOURCES += ./src/QxDataMember/IxDataMember.cpp
SOURCES += ./src/QxDataMember/IxDataMemberX.cpp
SOURCES += ./src/QxDataMember/QxDataMember_QObject.cpp

SOURCES += ./src/QxTraits/unit_test_is_smart_ptr.cpp
SOURCES += ./src/QxTraits/unit_test_is_container.cpp

SOURCES += ./src/QxXml/QxXmlReader.cpp
SOURCES += ./src/QxXml/QxXmlWriter.cpp

SOURCES += ./src/QxDao/IxSqlQueryBuilder.cpp
SOURCES += ./src/QxDao/QxSqlDatabase.cpp
SOURCES += ./src/QxDao/IxSqlRelation.cpp
SOURCES += ./src/QxDao/QxSqlQuery.cpp
SOURCES += ./src/QxDao/QxSession.cpp
SOURCES += ./src/QxDao/IxDao_Helper.cpp
SOURCES += ./src/QxDao/IxPersistable.cpp

SOURCES += ./src/QxDao/QxSqlElement/IxSqlElement.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlCompare.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlElementTemp.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlExpression.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlFreeText.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlIn.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlIsBetween.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlIsNull.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlLimit.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlSort.cpp

SOURCES += ./src/QxDao/QxSqlGenerator/IxSqlGenerator.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_MySQL.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_Oracle.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_PostgreSQL.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_SQLite.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_MSSQLServer.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_Standard.cpp

SOURCES += ./src/QxDao/QxRepository/IxRepository.cpp
SOURCES += ./src/QxDao/QxRepository/QxRepositoryX.cpp

SOURCES += ./src/QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.cpp
SOURCES += ./src/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.cpp

SOURCES += ./src/QxSerialize/boost/QxExportDllBoostArchive.cpp

SOURCES += ./src/QxSerialize/Qt/QxSerialize_QBrush.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QByteArray.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QColor.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QDate.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QDateTime.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QFont.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QImage.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QMatrix.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QObject.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QPicture.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QPixmap.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QPoint.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QRect.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QRegExp.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QRegion.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QSize.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QString.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QStringList.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QTime.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QUrl.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QUuid.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QVariant.cpp

SOURCES += ./src/QxService/IxParameter.cpp
SOURCES += ./src/QxService/IxService.cpp
SOURCES += ./src/QxService/QxConnect.cpp
SOURCES += ./src/QxService/QxServer.cpp
SOURCES += ./src/QxService/QxThread.cpp
SOURCES += ./src/QxService/QxThreadPool.cpp
SOURCES += ./src/QxService/QxTools.cpp
SOURCES += ./src/QxService/QxTransaction.cpp

SOURCES += ./src/QxValidator/IxValidator.cpp
SOURCES += ./src/QxValidator/IxValidatorX.cpp
SOURCES += ./src/QxValidator/QxInvalidValue.cpp
SOURCES += ./src/QxValidator/QxInvalidValueX.cpp

SOURCES += ./src/main.cpp
