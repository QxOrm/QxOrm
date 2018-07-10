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

#include <QxSerialize/Qt/QxSerialize_QBrush.h>

#include <QxOrm_Impl.h>

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

#endif // _QX_ENABLE_QT_GUI
#endif // _QX_ENABLE_BOOST_SERIALIZATION
