/****************************************************************************
**
** https://www.qxorm.com/
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

#ifndef _QX_DATA_MEMBER_PIMPL_H_
#define _QX_DATA_MEMBER_PIMPL_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxDataMember_PImpl.h
 * \author Lionel Marty
 * \ingroup QxDataMember
 * \brief Concrete class property registered into QxOrm context (using private implementation idiom)
 */

#include <QxDataMember/IxDataMember.h>

#define QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(ArchiveInput, ArchiveOutput) \
virtual void toArchive(const void * pOwner, ArchiveOutput & ar) const Q_DECL_OVERRIDE { Q_UNUSED(pOwner); Q_UNUSED(ar); } \
virtual void fromArchive(void * pOwner, ArchiveInput & ar) Q_DECL_OVERRIDE { Q_UNUSED(pOwner); Q_UNUSED(ar); }

namespace qx {

/*!
 * \ingroup QxDataMember
 * \brief qx::QxDataMember_PImpl<DataType, Owner> : concrete property of type DataType registered into QxOrm context for the class Owner (using private implementation idiom)
 */
template <typename DataType, class Owner>
class QxDataMember_PImpl : public IxDataMember
{

protected:

   typedef DataType Owner::* type_data_member_ptr;

   type_data_member_ptr m_pData; //!< Data member under format "& Owner::DataMember"

public:

   QxDataMember_PImpl(type_data_member_ptr pData, const QString & sKey) : IxDataMember(sKey, 0, false, false, NULL), m_pData(pData) { static_assert(std::is_pointer<DataType>::value, "std::is_pointer<DataType>::value"); this->setAccessDataPointer(true); }
   virtual ~QxDataMember_PImpl() { ; }

   virtual bool isEqual(const void * pOwner1, const void * pOwner2) const Q_DECL_OVERRIDE { Q_UNUSED(pOwner1); Q_UNUSED(pOwner2); return false; }
   virtual QVariant toVariant(const void * pOwner, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) const Q_DECL_OVERRIDE          { Q_UNUSED(pOwner); Q_UNUSED(sFormat); Q_UNUSED(iIndexName); Q_UNUSED(ctx); return QVariant(); }
   virtual qx_bool fromVariant(void * pOwner, const QVariant & v, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) Q_DECL_OVERRIDE { Q_UNUSED(pOwner); Q_UNUSED(v); Q_UNUSED(sFormat); Q_UNUSED(iIndexName); Q_UNUSED(ctx); return qx_bool(true); }
   virtual QString getType() const Q_DECL_OVERRIDE { return QString(); }

#ifndef _QX_NO_JSON
   virtual QJsonValue toJson(const void * pOwner, const QString & sFormat) const Q_DECL_OVERRIDE             { Q_UNUSED(pOwner); Q_UNUSED(sFormat); return QJsonValue(); }
   virtual qx_bool fromJson(void * pOwner, const QJsonValue & j, const QString & sFormat) Q_DECL_OVERRIDE    { Q_UNUSED(pOwner); Q_UNUSED(j); Q_UNUSED(sFormat); return qx_bool(true); }
#endif // _QX_NO_JSON

protected:

   inline DataType * getData(void * pOwner) const              { return (& ((static_cast<Owner *>(pOwner))->*m_pData)); }
   inline const DataType * getData(const void * pOwner) const  { return (& ((static_cast<const Owner *>(pOwner))->*m_pData)); }

   virtual qx::any getDataPtr(const void * pOwner) const Q_DECL_FINAL       { return (pOwner ? qx::any(* getData(pOwner)) : qx::any()); }
   virtual qx::any getDataPtr(void * pOwner) Q_DECL_FINAL                   { return (pOwner ? qx::any(* getData(pOwner)) : qx::any()); }
   virtual void * getDataVoidPtr(const void * pOwner) const Q_DECL_FINAL    { return (pOwner ? static_cast<void *>(const_cast<DataType>(* getData(pOwner))) : NULL); }
   virtual void * getDataVoidPtr(void * pOwner) Q_DECL_FINAL                { return (pOwner ? static_cast<void *>(* getData(pOwner)) : NULL); }

public:

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

#if _QX_SERIALIZE_POLYMORPHIC
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

#endif // _QX_ENABLE_BOOST_SERIALIZATION

};

template <typename DataType, class Owner>
class QxDataMember_PImpl<std::unique_ptr<DataType>, Owner> : public IxDataMember
{

protected:

   typedef std::unique_ptr<DataType> Owner::* type_data_member_ptr;

   type_data_member_ptr m_pData; //!< Data member under format "& Owner::DataMember"

public:

   QxDataMember_PImpl(type_data_member_ptr pData, const QString & sKey) : IxDataMember(sKey, 0, false, false, NULL), m_pData(pData) { this->setAccessDataPointer(true); }
   virtual ~QxDataMember_PImpl() { ; }

   virtual bool isEqual(const void * pOwner1, const void * pOwner2) const Q_DECL_OVERRIDE { Q_UNUSED(pOwner1); Q_UNUSED(pOwner2); return false; }
   virtual QVariant toVariant(const void * pOwner, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) const Q_DECL_OVERRIDE          { Q_UNUSED(pOwner); Q_UNUSED(sFormat); Q_UNUSED(iIndexName); Q_UNUSED(ctx); return QVariant(); }
   virtual qx_bool fromVariant(void * pOwner, const QVariant & v, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) Q_DECL_OVERRIDE { Q_UNUSED(pOwner); Q_UNUSED(v); Q_UNUSED(sFormat); Q_UNUSED(iIndexName); Q_UNUSED(ctx); return qx_bool(true); }
   virtual QString getType() const Q_DECL_OVERRIDE { return QString(); }

#ifndef _QX_NO_JSON
   virtual QJsonValue toJson(const void * pOwner, const QString & sFormat) const Q_DECL_OVERRIDE             { Q_UNUSED(pOwner); Q_UNUSED(sFormat); return QJsonValue(); }
   virtual qx_bool fromJson(void * pOwner, const QJsonValue & j, const QString & sFormat) Q_DECL_OVERRIDE    { Q_UNUSED(pOwner); Q_UNUSED(j); Q_UNUSED(sFormat); return qx_bool(true); }
#endif // _QX_NO_JSON

protected:

   inline std::unique_ptr<DataType> * getData(void * pOwner) const              { return (& ((static_cast<Owner *>(pOwner))->*m_pData)); }
   inline const std::unique_ptr<DataType> * getData(const void * pOwner) const  { return (& ((static_cast<const Owner *>(pOwner))->*m_pData)); }

   virtual qx::any getDataPtr(const void * pOwner) const Q_DECL_FINAL       { return (pOwner ? qx::any(getData(pOwner)->get()) : qx::any()); }
   virtual qx::any getDataPtr(void * pOwner) Q_DECL_FINAL                   { return (pOwner ? qx::any(getData(pOwner)->get()) : qx::any()); }
   virtual void * getDataVoidPtr(const void * pOwner) const Q_DECL_FINAL    { return (pOwner ? static_cast<void *>(const_cast<DataType *>(getData(pOwner)->get())) : NULL); }
   virtual void * getDataVoidPtr(void * pOwner) Q_DECL_FINAL                { return (pOwner ? static_cast<void *>(getData(pOwner)->get()) : NULL); }

public:

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

#if _QX_SERIALIZE_POLYMORPHIC
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

#endif // _QX_ENABLE_BOOST_SERIALIZATION

};

template <typename DataType, class Owner>
class QxDataMember_PImpl<std::shared_ptr<DataType>, Owner> : public IxDataMember
{

protected:

   typedef std::shared_ptr<DataType> Owner::* type_data_member_ptr;

   type_data_member_ptr m_pData; //!< Data member under format "& Owner::DataMember"

public:

   QxDataMember_PImpl(type_data_member_ptr pData, const QString & sKey) : IxDataMember(sKey, 0, false, false, NULL), m_pData(pData) { this->setAccessDataPointer(true); }
   virtual ~QxDataMember_PImpl() { ; }

   virtual bool isEqual(const void * pOwner1, const void * pOwner2) const Q_DECL_OVERRIDE { Q_UNUSED(pOwner1); Q_UNUSED(pOwner2); return false; }
   virtual QVariant toVariant(const void * pOwner, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) const Q_DECL_OVERRIDE          { Q_UNUSED(pOwner); Q_UNUSED(sFormat); Q_UNUSED(iIndexName); Q_UNUSED(ctx); return QVariant(); }
   virtual qx_bool fromVariant(void * pOwner, const QVariant & v, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) Q_DECL_OVERRIDE { Q_UNUSED(pOwner); Q_UNUSED(v); Q_UNUSED(sFormat); Q_UNUSED(iIndexName); Q_UNUSED(ctx); return qx_bool(true); }
   virtual QString getType() const Q_DECL_OVERRIDE { return QString(); }

#ifndef _QX_NO_JSON
   virtual QJsonValue toJson(const void * pOwner, const QString & sFormat) const Q_DECL_OVERRIDE             { Q_UNUSED(pOwner); Q_UNUSED(sFormat); return QJsonValue(); }
   virtual qx_bool fromJson(void * pOwner, const QJsonValue & j, const QString & sFormat) Q_DECL_OVERRIDE    { Q_UNUSED(pOwner); Q_UNUSED(j); Q_UNUSED(sFormat); return qx_bool(true); }
#endif // _QX_NO_JSON

protected:

   inline std::shared_ptr<DataType> * getData(void * pOwner) const              { return (& ((static_cast<Owner *>(pOwner))->*m_pData)); }
   inline const std::shared_ptr<DataType> * getData(const void * pOwner) const  { return (& ((static_cast<const Owner *>(pOwner))->*m_pData)); }

   virtual qx::any getDataPtr(const void * pOwner) const Q_DECL_FINAL       { return (pOwner ? qx::any(getData(pOwner)->get()) : qx::any()); }
   virtual qx::any getDataPtr(void * pOwner) Q_DECL_FINAL                   { return (pOwner ? qx::any(getData(pOwner)->get()) : qx::any()); }
   virtual void * getDataVoidPtr(const void * pOwner) const Q_DECL_FINAL    { return (pOwner ? static_cast<void *>(const_cast<DataType *>(getData(pOwner)->get())) : NULL); }
   virtual void * getDataVoidPtr(void * pOwner) Q_DECL_FINAL                { return (pOwner ? static_cast<void *>(getData(pOwner)->get()) : NULL); }

public:

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

#if _QX_SERIALIZE_POLYMORPHIC
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_DATA_MEMBER_PIMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

#endif // _QX_ENABLE_BOOST_SERIALIZATION

};

} // namespace qx

#endif // _QX_DATA_MEMBER_PIMPL_H_
