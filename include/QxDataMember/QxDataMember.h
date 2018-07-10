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

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#endif // _QX_ENABLE_BOOST_SERIALIZATION

#include <QxDataMember/IxDataMember.h>

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

   QxDataMember(type_data_member_ptr pData, const QString & sKey) : IxDataMember(sKey), m_pData(pData) { this->setAccessDataPointer(true); }
   QxDataMember(type_data_member_ptr pData, const QString & sKey, long lVersion, bool bSerialize, bool bDao) : IxDataMember(sKey, lVersion, bSerialize, bDao), m_pData(pData) { this->setAccessDataPointer(true); }
   virtual ~QxDataMember() { ; }

   inline DataType * getData(void * pOwner) const              { return (pOwner ? (& ((static_cast<Owner *>(pOwner))->*m_pData)) : NULL); }
   inline const DataType * getData(const void * pOwner) const  { return (pOwner ? (& ((static_cast<const Owner *>(pOwner))->*m_pData)) : NULL); }

   virtual QVariant toVariant(const void * pOwner, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) const          { return qx::cvt::to_variant((* getData(pOwner)), sFormat, iIndexName, ctx); }
   virtual qx_bool fromVariant(void * pOwner, const QVariant & v, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) { return qx::cvt::from_variant(v, (* getData(pOwner)), sFormat, iIndexName, ctx); }

#ifndef _QX_NO_JSON
   virtual QJsonValue toJson(const void * pOwner, const QString & sFormat) const             { return qx::cvt::to_json((* getData(pOwner)), sFormat); }
   virtual qx_bool fromJson(void * pOwner, const QJsonValue & j, const QString & sFormat)    { return qx::cvt::from_json(j, (* getData(pOwner)), sFormat); }
#endif // _QX_NO_JSON

   virtual bool isEqual(const void * pOwner1, const void * pOwner2) const
   {
      if ((pOwner1 == NULL) || (pOwner2 == NULL)) { return false; }
      if (pOwner1 == pOwner2) { return true; }
      return qxCompareDataMember<qx::trait::has_operator_equal_equal<DataType>::value, 0>::isEqual((* this), pOwner1, pOwner2);
   }

protected:

   virtual qx::any getDataPtr(const void * pOwner) const       { return qx::any(getData(pOwner)); }
   virtual qx::any getDataPtr(void * pOwner)                   { return qx::any(getData(pOwner)); }
   virtual void * getDataVoidPtr(const void * pOwner) const    { return static_cast<void *>(const_cast<DataType *>(getData(pOwner))); }
   virtual void * getDataVoidPtr(void * pOwner)                { return static_cast<void *>(getData(pOwner)); }

public:

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

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

#endif // _QX_ENABLE_BOOST_SERIALIZATION

private:

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

   template <class Archive>
   static inline void toArchive(Archive & ar, const char * sName, const DataType * pData)
   { ar << boost::serialization::make_nvp(sName, (* pData)); }

   template <class Archive>
   static inline void fromArchive(Archive & ar, const char * sName, DataType * pData)
   { ar >> boost::serialization::make_nvp(sName, (* pData)); }

#endif // _QX_ENABLE_BOOST_SERIALIZATION

private:

   template <bool bCanCompare /* = false */, int dummy>
   struct qxCompareDataMember
   {
      static inline bool isEqual(const QxDataMember<DataType, Owner> & dataMember, const void * pOwner1, const void * pOwner2)
      { return (dataMember.toVariant(pOwner1, "") == dataMember.toVariant(pOwner2, "")); }
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
