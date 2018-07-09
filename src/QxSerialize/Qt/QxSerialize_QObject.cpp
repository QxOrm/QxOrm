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

#include "../../../include/QxPrecompiled.h"

#include "../../../include/QxSerialize/Qt/QxSerialize_QObject.h"

#include "../../../include/QxMemLeak.h"

QX_BOOST_EXPORT_SERIALIZATION_FAST_COMPIL_CPP(QObject)

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QObject & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QList<QByteArray> propertyKeyList = t.dynamicPropertyNames();
   int iPropertyCount = propertyKeyList.count();
   std::pair<std::string, QVariant> pair_string_variant;
   ar << boost::serialization::make_nvp("propertyCount", iPropertyCount);

   for (long l = 0; l < iPropertyCount; l++)
   {
      pair_string_variant.first = propertyKeyList.at(l).constData();
      pair_string_variant.second = t.property(pair_string_variant.first.c_str());
      ar << boost::serialization::make_nvp("property", pair_string_variant);
   }
}

template <class Archive>
inline void qx_load(Archive & ar, QObject & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   int iPropertyCount = 0;
   std::pair<std::string, QVariant> pair_string_variant;
   ar >> boost::serialization::make_nvp("propertyCount", iPropertyCount);

   for (long l = 0; l < iPropertyCount; l++)
   {
      ar >> boost::serialization::make_nvp("property", pair_string_variant);
      t.setProperty(pair_string_variant.first.c_str(), pair_string_variant.second);
   }
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QObject)
QX_REGISTER_BOOST_SERIALIZE_HELPER_CPP(QObject)
