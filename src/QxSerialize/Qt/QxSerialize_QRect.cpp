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

#include <QxSerialize/Qt/QxSerialize_QRect.h>

#include <QxOrm_Impl.h>

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

#endif // _QX_ENABLE_BOOST_SERIALIZATION
