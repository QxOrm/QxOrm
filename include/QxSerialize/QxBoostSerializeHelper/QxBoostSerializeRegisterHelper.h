/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_BOOST_SERIALIZE_REGISTER_HELPER_H_
#define _QX_BOOST_SERIALIZE_REGISTER_HELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../../include/QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.h"
#include "../../../include/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeHelper.h"

#define QX_BOOST_SERIALIZE_REGISTER_HELPER_IMPLEMENT_VIRTUAL_ARCHIVE(ArchiveIn, ArchiveOut) \
virtual void helper(ArchiveIn & ar) const { private_helper(ar); } \
virtual void helper(ArchiveOut & ar) const { private_helper(ar); }

namespace qx {

template <class T>
class QxBoostSerializeRegisterHelper : public IxBoostSerializeRegisterHelper
{

public:

   QxBoostSerializeRegisterHelper(const QString & sKey) : IxBoostSerializeRegisterHelper(sKey) { ; }
   virtual ~QxBoostSerializeRegisterHelper() { ; }

   virtual void helper() const { private_helper(); }

#if _QX_SERIALIZE_POLYMORPHIC
   QX_BOOST_SERIALIZE_REGISTER_HELPER_IMPLEMENT_VIRTUAL_ARCHIVE(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_BOOST_SERIALIZE_REGISTER_HELPER_IMPLEMENT_VIRTUAL_ARCHIVE(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_BOOST_SERIALIZE_REGISTER_HELPER_IMPLEMENT_VIRTUAL_ARCHIVE(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_BOOST_SERIALIZE_REGISTER_HELPER_IMPLEMENT_VIRTUAL_ARCHIVE(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_BOOST_SERIALIZE_REGISTER_HELPER_IMPLEMENT_VIRTUAL_ARCHIVE(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_BOOST_SERIALIZE_REGISTER_HELPER_IMPLEMENT_VIRTUAL_ARCHIVE(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_BOOST_SERIALIZE_REGISTER_HELPER_IMPLEMENT_VIRTUAL_ARCHIVE(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_BOOST_SERIALIZE_REGISTER_HELPER_IMPLEMENT_VIRTUAL_ARCHIVE(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

private:

   template <class Archive>
   inline void private_helper(Archive & ar) const
   {
      qx::QxBoostSerializeHelper<T>::register_type_helper(ar, static_cast<T *>(NULL));
      qx::QxBoostSerializeHelper<T>::void_cast_register_helper(static_cast<T *>(NULL));
      qx::QxBoostSerializeHelper<T>::init_guid(static_cast<T *>(NULL));
   }

   inline void private_helper() const
   {
      qx::QxBoostSerializeHelper<T>::void_cast_register_helper(static_cast<T *>(NULL));
      qx::QxBoostSerializeHelper<T>::init_guid(static_cast<T *>(NULL));
   }

};

} // namespace qx

#if _QX_USE_BOOST_SERIALIZE_REGISTER_HELPER
#define QX_REGISTER_BOOST_SERIALIZE_HELPER_COMPLEX_CLASS_NAME(className, classNameFormatted) \
extern qx::QxBoostSerializeRegisterHelper< className > G_QX_REGISTER_BOOST_SERIALIZE_HELPER_##classNameFormatted;
#define QX_REGISTER_BOOST_SERIALIZE_HELPER(className) \
QX_REGISTER_BOOST_SERIALIZE_HELPER_COMPLEX_CLASS_NAME(className, className)
#else
#define QX_REGISTER_BOOST_SERIALIZE_HELPER_COMPLEX_CLASS_NAME(className, classNameFormatted) /* Nothing */
#define QX_REGISTER_BOOST_SERIALIZE_HELPER(className) /* Nothing */
#endif // _QX_USE_BOOST_SERIALIZE_REGISTER_HELPER

#if _QX_USE_BOOST_SERIALIZE_REGISTER_HELPER
#define QX_REGISTER_BOOST_SERIALIZE_HELPER_COMPLEX_CLASS_NAME_CPP(className, classNameFormatted) \
qx::QxBoostSerializeRegisterHelper< className > G_QX_REGISTER_BOOST_SERIALIZE_HELPER_##classNameFormatted(QString(#className));
#define QX_REGISTER_BOOST_SERIALIZE_HELPER_CPP(className) \
QX_REGISTER_BOOST_SERIALIZE_HELPER_COMPLEX_CLASS_NAME_CPP(className, className)
#else
#define QX_REGISTER_BOOST_SERIALIZE_HELPER_COMPLEX_CLASS_NAME_CPP(className, classNameFormatted) /* Nothing */
#define QX_REGISTER_BOOST_SERIALIZE_HELPER_CPP(className) /* Nothing */
#endif // _QX_USE_BOOST_SERIALIZE_REGISTER_HELPER

#endif // _QX_BOOST_SERIALIZE_REGISTER_HELPER_H_
