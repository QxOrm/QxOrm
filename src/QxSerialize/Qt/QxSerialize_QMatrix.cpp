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

#include "../../../include/QxSerialize/Qt/QxSerialize_QMatrix.h"

#include "../../../include/QxMemLeak.h"

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
