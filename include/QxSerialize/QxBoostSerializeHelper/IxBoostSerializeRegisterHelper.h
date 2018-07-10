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

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#ifndef _IX_BOOST_SERIALIZE_REGISTER_HELPER_H_
#define _IX_BOOST_SERIALIZE_REGISTER_HELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxCommon/QxConfig.h>

#include <QxSerialize/boost/QxSerializeInclude.h>

#define QX_IX_BOOST_SERIALIZE_REGISTER_HELPER_PURE_VIRTUAL_ARCHIVE(ArchiveIn, ArchiveOut) \
virtual void helper(ArchiveIn & ar) const = 0; \
virtual void helper(ArchiveOut & ar) const = 0;

namespace qx {

class QX_DLL_EXPORT IxBoostSerializeRegisterHelper
{

private:

   QString m_sKey;   // Register key used by 'QxBoostSerializeRegisterHelperX'

protected:

   IxBoostSerializeRegisterHelper(const QString & sKey);
   virtual ~IxBoostSerializeRegisterHelper() = 0;

public:

   virtual void helper() const = 0;

#if _QX_SERIALIZE_POLYMORPHIC
   QX_IX_BOOST_SERIALIZE_REGISTER_HELPER_PURE_VIRTUAL_ARCHIVE(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_IX_BOOST_SERIALIZE_REGISTER_HELPER_PURE_VIRTUAL_ARCHIVE(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_IX_BOOST_SERIALIZE_REGISTER_HELPER_PURE_VIRTUAL_ARCHIVE(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_IX_BOOST_SERIALIZE_REGISTER_HELPER_PURE_VIRTUAL_ARCHIVE(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_IX_BOOST_SERIALIZE_REGISTER_HELPER_PURE_VIRTUAL_ARCHIVE(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_IX_BOOST_SERIALIZE_REGISTER_HELPER_PURE_VIRTUAL_ARCHIVE(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_IX_BOOST_SERIALIZE_REGISTER_HELPER_PURE_VIRTUAL_ARCHIVE(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_IX_BOOST_SERIALIZE_REGISTER_HELPER_PURE_VIRTUAL_ARCHIVE(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

private:

   IxBoostSerializeRegisterHelper(const IxBoostSerializeRegisterHelper & other) { Q_UNUSED(other); }
   IxBoostSerializeRegisterHelper & operator=(const IxBoostSerializeRegisterHelper & other) { Q_UNUSED(other); return (* this); }

};

} // namespace qx

#endif // _IX_BOOST_SERIALIZE_REGISTER_HELPER_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
