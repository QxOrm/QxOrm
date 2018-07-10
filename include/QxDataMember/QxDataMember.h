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

#ifndef _QX_DATA_MEMBER_H_
#define _QX_DATA_MEMBER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxDataMember.h
 * \author Lionel Marty
 * \ingroup QxDataMember
 * \brief Concrete class property registered into QxOrm context
 */

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

#include <QxDataMember/IxDataMember.h>

#include <QxCommon/QxStringCvt.h>

#include <QxTraits/is_equal.h>

#define QX_DATA_MEMBER_IMPL_VIRTUAL_ARCHIVE(ArchiveInput, ArchiveOutput) \
virtual void toArchive(const void * pOwner, ArchiveOutput & ar) const   { QxDataMember::toArchive(ar, getNamePtr(), getData(pOwner)); } \
virtual void fromArchive(void * pOwner, ArchiveInput & ar)              { QxDataMember::fromArchive(ar, getNamePtr(), getData(pOwner)); }

namespace qx {

/*!
 * \ingroup QxDataMember
 * \brief qx::QxDataMember<DataType, Owner> : concrete property of type DataType registered into QxOrm context for the class Owner
 */
template <typename DataType, class Owner>
class QxDataMember : public IxDataMember
{

protected:

   typedef DataType Owner::* type_data_member_ptr;

   type_data_member_ptr m_pData; //!< Data member under format "& Owner::DataMember"

public:

   QxDataMember(type_data_member_ptr pData, const QString & sKey) : IxDataMember(sKey), m_pData(pData) { m_bAccessDataPointer = true; }
   QxDataMember(type_data_member_ptr pData, const QString & sKey, long lVersion, bool bSerialize, bool bDao) : IxDataMember(sKey, lVersion, bSerialize, bDao), m_pData(pData) { m_bAccessDataPointer = true; }
   virtual ~QxDataMember() { ; }

   inline DataType * getData(void * pOwner) const              { return (pOwner ? (& ((static_cast<Owner *>(pOwner))->*m_pData)) : NULL); }
   inline const DataType * getData(const void * pOwner) const  { return (pOwner ? (& ((static_cast<const Owner *>(pOwner))->*m_pData)) : NULL); }

   virtual QString toString(const void * pOwner, const QString & sFormat, int iIndexName = -1) const              { return qx::cvt::to_string((* getData(pOwner)), sFormat, iIndexName); }
   virtual qx_bool fromString(void * pOwner, const QString & s, const QString & sFormat, int iIndexName = -1)     { return qx::cvt::from_string(s, (* getData(pOwner)), sFormat, iIndexName); }
   virtual QVariant toVariant(const void * pOwner, const QString & sFormat, int iIndexName = -1) const            { return qx::cvt::to_variant((* getData(pOwner)), sFormat, iIndexName); }
   virtual qx_bool fromVariant(void * pOwner, const QVariant & v, const QString & sFormat, int iIndexName = -1)   { return qx::cvt::from_variant(v, (* getData(pOwner)), sFormat, iIndexName); }

   virtual bool isEqual(const void * pOwner1, const void * pOwner2) const
   {
      if ((pOwner1 == NULL) || (pOwner2 == NULL)) { return false; }
      if (pOwner1 == pOwner2) { return true; }
      return qxCompareDataMember<qx::trait::has_operator_equal_equal<DataType>::value, 0>::isEqual((* this), pOwner1, pOwner2);
   }

protected:

   virtual boost::any getDataPtr(const void * pOwner) const    { return boost::any(getData(pOwner)); }
   virtual boost::any getDataPtr(void * pOwner)                { return boost::any(getData(pOwner)); }
   virtual void * getDataVoidPtr(const void * pOwner) const    { return static_cast<void *>(const_cast<DataType *>(getData(pOwner))); }
   virtual void * getDataVoidPtr(void * pOwner)                { return static_cast<void *>(getData(pOwner)); }

public:

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

private:

   template <bool bCanCompare /* = false */, int dummy>
   struct qxCompareDataMember
   {
      static inline bool isEqual(const QxDataMember<DataType, Owner> & dataMember, const void * pOwner1, const void * pOwner2)
      { return (dataMember.toString(pOwner1, "") == dataMember.toString(pOwner2, "")); }
   };

   template <int dummy>
   struct qxCompareDataMember<true, dummy>
   {
      static inline bool isEqual(const QxDataMember<DataType, Owner> & dataMember, const void * pOwner1, const void * pOwner2)
      { return ((* dataMember.getData(pOwner1)) == (* dataMember.getData(pOwner2))); }
   };

};

} // namespace qx

#include "../../inl/QxDataMember/QxDataMember.inl"

#endif // _QX_DATA_MEMBER_H_
