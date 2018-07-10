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

#include "../../../include/QxSerialize/Qt/QxSerialize_QRect.h"

#include "../../../include/QxMemLeak.h"

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QRect & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   int iLeft(t.left()), iRight(t.right()), iTop(t.top()), iBottom(t.bottom());

   ar << boost::serialization::make_nvp("left", iLeft);
   ar << boost::serialization::make_nvp("right", iRight);
   ar << boost::serialization::make_nvp("top", iTop);
   ar << boost::serialization::make_nvp("bottom", iBottom);
}

template <class Archive>
inline void qx_load(Archive & ar, QRect & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   int iLeft(0), iRight(0), iTop(0), iBottom(0);

   ar >> boost::serialization::make_nvp("left", iLeft);
   ar >> boost::serialization::make_nvp("right", iRight);
   ar >> boost::serialization::make_nvp("top", iTop);
   ar >> boost::serialization::make_nvp("bottom", iBottom);

   t.setTop(iTop);
   t.setBottom(iBottom);
   t.setLeft(iLeft);
   t.setRight(iRight);
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QRect)
