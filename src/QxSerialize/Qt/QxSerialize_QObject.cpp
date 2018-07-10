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
