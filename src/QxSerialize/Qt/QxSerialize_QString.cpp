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

#include "../../../include/QxSerialize/Qt/QxSerialize_QString.h"

#include "../../../include/QxTraits/archive_wide_traits.h"
#include "../../../include/QxTraits/archive_printable.h"

#include "../../../include/QxMemLeak.h"

namespace boost {
namespace serialization {

template <bool isPrintable = false>
struct qx_serialize_qstring
{

   template <class Archive>
   static inline void save(Archive & ar, const QString & t, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      char cell, row;
      long lSize = t.size();
      ar << boost::serialization::make_nvp("size", lSize);
      const QChar * qcharPtr = t.constData();
      for (long l = 0; l < lSize; ++l)
      {
         cell = static_cast<char>(qcharPtr[l].cell());
         row = static_cast<char>(qcharPtr[l].row());
         ar << boost::serialization::make_nvp(NULL, cell);
         ar << boost::serialization::make_nvp(NULL, row);
      }
   }

   template <class Archive>
   static inline void load(Archive & ar, QString & t, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      char cell, row;
      long lSize = 0;
      ar >> boost::serialization::make_nvp("size", lSize);
      t.clear();
      t.reserve(lSize);
      for (long l = 0; l < lSize; ++l)
      {
         ar >> boost::serialization::make_nvp(NULL, cell);
         ar >> boost::serialization::make_nvp(NULL, row);
         t.append(QChar(cell, row));
      }
   }

};

template <>
struct qx_serialize_qstring<true>
{

   template <class Archive>
   static inline void save(Archive & ar, const QString & t, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      typedef typename qx::trait::archive_wide_traits<Archive>::type_string qx_type_string_tmp;
      qx_type_string_tmp str = qx::trait::archive_wide_traits<Archive>::fromQString(t);
      ar << boost::serialization::make_nvp(NULL, str);
   }

   template <class Archive>
   static inline void load(Archive & ar, QString & t, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      typedef typename qx::trait::archive_wide_traits<Archive>::type_string qx_type_string_tmp;
      qx_type_string_tmp str;
      ar >> boost::serialization::make_nvp(NULL, str);
      t = qx::trait::archive_wide_traits<Archive>::toQString(str);
   }

};

template <class Archive>
inline void qx_save(Archive & ar, const QString & t, const unsigned int file_version)
{
   qx_serialize_qstring<qx::trait::is_archive_printable<Archive>::value>::save(ar, t, file_version);
}

template <class Archive>
inline void qx_load(Archive & ar, QString & t, const unsigned int file_version)
{
   qx_serialize_qstring<qx::trait::is_archive_printable<Archive>::value>::load(ar, t, file_version);
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QString)
