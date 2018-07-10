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

#include "../../../include/QxSerialize/Qt/QxSerialize_QByteArray.h"

#include "../../../include/QxMemLeak.h"

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QByteArray & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   long lCount = t.count();
   std::string data(t.constData(), lCount);
   ar << boost::serialization::make_nvp("size", lCount);
   ar << boost::serialization::make_nvp("data", data);
}

template <class Archive>
inline void qx_load(Archive & ar, QByteArray & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   long lCount = 0; std::string data; t.clear();
   ar >> boost::serialization::make_nvp("size", lCount);
   ar >> boost::serialization::make_nvp("data", data);
   if (lCount > 0) { t = QByteArray(data.c_str(), lCount); }
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QByteArray)
