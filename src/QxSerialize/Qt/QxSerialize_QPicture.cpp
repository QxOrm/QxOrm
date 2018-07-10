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

#include <QxPrecompiled.h>

#ifdef _QX_ENABLE_QT_GUI

#include <QxSerialize/Qt/QxSerialize_QPicture.h>

#include <QxOrm_Impl.h>

QX_BOOST_EXPORT_SERIALIZATION_FAST_COMPIL_CPP(QPicture)

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QPicture & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   bool bIsNull = t.isNull();
   ar << boost::serialization::make_nvp("null", bIsNull);
   if (bIsNull) { return; }

   QByteArray bytes;
   QBuffer buffer(& bytes);
   QPicture * pTmp = const_cast<QPicture *>(& t);
   buffer.open(QIODevice::ReadWrite);
   pTmp->save(& buffer, "PNG");
   ar << boost::serialization::make_nvp("bytes", bytes);
}

template <class Archive>
inline void qx_load(Archive & ar, QPicture & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   t = QPicture();
   bool bIsNull(false);
   ar >> boost::serialization::make_nvp("null", bIsNull);
   if (bIsNull) { return; }

   QByteArray bytes;
   QBuffer buffer(& bytes);
   buffer.open(QIODevice::ReadWrite);
   ar >> boost::serialization::make_nvp("bytes", bytes);
   t.load(& buffer, "PNG");
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QPicture)

#endif // _QX_ENABLE_QT_GUI
#endif // _QX_ENABLE_BOOST_SERIALIZATION
