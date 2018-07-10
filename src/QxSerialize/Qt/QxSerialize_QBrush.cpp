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

#include "../../../include/QxSerialize/Qt/QxSerialize_QBrush.h"

#include "../../../include/QxMemLeak.h"

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QBrush & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   int iStyle = static_cast<int>(t.style());
   QColor color(t.color());
   QPixmap texture(t.texture());

   ar << boost::serialization::make_nvp("style", iStyle);
   ar << boost::serialization::make_nvp("color", color);
   ar << boost::serialization::make_nvp("texture", texture);
}

template <class Archive>
inline void qx_load(Archive & ar, QBrush & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   int iStyle = 0; QColor color; QPixmap texture;

   ar >> boost::serialization::make_nvp("style", iStyle);
   ar >> boost::serialization::make_nvp("color", color);
   ar >> boost::serialization::make_nvp("texture", texture);

   t.setStyle(static_cast<Qt::BrushStyle>(iStyle));
   ((iStyle == Qt::TexturePattern) ? t.setTexture(texture) : t.setColor(color));
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QBrush)
