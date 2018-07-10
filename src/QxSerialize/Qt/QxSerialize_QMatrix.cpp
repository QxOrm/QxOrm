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

#include <QxPrecompiled.h>

#include <QxSerialize/Qt/QxSerialize_QMatrix.h>

#include <QxMemLeak.h>

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QMatrix & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   double m11(t.m11()), m12(t.m12()), m21(t.m21()), m22(t.m22()), dx(t.dx()), dy(t.dy());

   ar << boost::serialization::make_nvp("m11", m11);
   ar << boost::serialization::make_nvp("m12", m12);
   ar << boost::serialization::make_nvp("m21", m21);
   ar << boost::serialization::make_nvp("m22", m22);
   ar << boost::serialization::make_nvp("dx", dx);
   ar << boost::serialization::make_nvp("dy", dy);
}

template <class Archive>
inline void qx_load(Archive & ar, QMatrix & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   double m11(0.0), m12(0.0), m21(0.0), m22(0.0), dx(0.0), dy(0.0);

   ar >> boost::serialization::make_nvp("m11", m11);
   ar >> boost::serialization::make_nvp("m12", m12);
   ar >> boost::serialization::make_nvp("m21", m21);
   ar >> boost::serialization::make_nvp("m22", m22);
   ar >> boost::serialization::make_nvp("dx", dx);
   ar >> boost::serialization::make_nvp("dy", dy);

   t.setMatrix(m11, m12, m21, m22, dx, dy);
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QMatrix)
