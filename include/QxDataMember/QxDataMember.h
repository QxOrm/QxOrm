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

#ifndef _QX_DATA_MEMBER_H_
#define _QX_DATA_MEMBER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

#include "../../include/QxDataMember/IxDataMember.h"

#include "../../include/QxCommon/QxStringCvt.h"

#define QX_DATA_MEMBER_IMPL_VIRTUAL_ARCHIVE(ArchiveInput, ArchiveOutput) \
virtual void toArchive(const void * pOwner, ArchiveOutput & ar) const   { QxDataMember::toArchive(ar, getNamePtr(), getData(pOwner)); } \
virtual void fromArchive(void * pOwner, ArchiveInput & ar)              { QxDataMember::fromArchive(ar, getNamePtr(), getData(pOwner)); }

namespace qx {

template <typename DataType, class Owner>
class QxDataMember : public IxDataMember
{

protected:

   typedef DataType Owner::* type_data_member_ptr;

   type_data_member_ptr m_pData; // Data member under format "& Owner::DataMember"

public:

   QxDataMember(type_data_member_ptr pData, const QString & sKey) : IxDataMember(sKey), m_pData(pData) { ; }
   QxDataMember(type_data_member_ptr pData, const QString & sKey, long lVersion, bool bSerialize, bool bDao) : IxDataMember(sKey, lVersion, bSerialize, bDao), m_pData(pData) { ; }
   virtual ~QxDataMember() { ; }

   inline DataType * getData(void * pOwner) const              { return (pOwner ? (& ((static_cast<Owner *>(pOwner))->*m_pData)) : NULL); }
   inline const DataType * getData(const void * pOwner) const  { return (pOwner ? (& ((static_cast<const Owner *>(pOwner))->*m_pData)) : NULL); }

   virtual boost::any getDataPtr(const void * pOwner) const    { return boost::any(getData(pOwner)); }
   virtual boost::any getDataPtr(void * pOwner)                { return boost::any(getData(pOwner)); }
   virtual void * getDataVoidPtr(const void * pOwner) const    { return static_cast<void *>(const_cast<DataType *>(getData(pOwner))); }
   virtual void * getDataVoidPtr(void * pOwner)                { return static_cast<void *>(getData(pOwner)); }
   virtual qx_bool isValid(const void * pOwner) const          { Q_UNUSED(pOwner); return true; }
   virtual qx_bool isValid(void * pOwner)                      { Q_UNUSED(pOwner); return true; }

   virtual QString toString(const void * pOwner, const QString & sFormat) const              { return qx::cvt::to_string((* getData(pOwner)), sFormat); }
   virtual qx_bool fromString(void * pOwner, const QString & s, const QString & sFormat)     { return qx::cvt::from_string(s, (* getData(pOwner)), sFormat); }
   virtual QVariant toVariant(const void * pOwner, const QString & sFormat) const            { return qx::cvt::to_variant((* getData(pOwner)), sFormat); }
   virtual qx_bool fromVariant(void * pOwner, const QVariant & v, const QString & sFormat)   { return qx::cvt::from_variant(v, (* getData(pOwner)), sFormat); }

#if _QX_SERIALIZE_POLYMORPHIC
   QX_DATA_MEMBER_IMPL_VIRTUAL_ARCHIVE(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_DATA_MEMBER_IMPL_VIRTUAL_ARCHIVE(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_DATA_MEMBER_IMPL_VIRTUAL_ARCHIVE(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_DATA_MEMBER_IMPL_VIRTUAL_ARCHIVE(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_DATA_MEMBER_IMPL_VIRTUAL_ARCHIVE(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_DATA_MEMBER_IMPL_VIRTUAL_ARCHIVE(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_DATA_MEMBER_IMPL_VIRTUAL_ARCHIVE(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_DATA_MEMBER_IMPL_VIRTUAL_ARCHIVE(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

private:

   template <class Archive>
   static inline void toArchive(Archive & ar, const char * sName, const DataType * pData)
   { ar << boost::serialization::make_nvp(sName, (* pData)); }

   template <class Archive>
   static inline void fromArchive(Archive & ar, const char * sName, DataType * pData)
   { ar >> boost::serialization::make_nvp(sName, (* pData)); }

};

} // namespace qx

#include "../../inl/QxDataMember/QxDataMember.inl"

#endif // _QX_DATA_MEMBER_H_
