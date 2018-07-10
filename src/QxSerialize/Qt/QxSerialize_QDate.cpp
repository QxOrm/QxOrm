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

#include <QxSerialize/Qt/QxSerialize_QDate.h>

#include <QxMemLeak.h>

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QDate & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QString sDate = t.toString(QX_SERIALIZE_QDATE_FORMAT);
   ar << boost::serialization::make_nvp(NULL, sDate);
}

template <class Archive>
inline void qx_load(Archive & ar, QDate & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QString sDate;
   ar >> boost::serialization::make_nvp(NULL, sDate);
   t = QDate::fromString(sDate, QX_SERIALIZE_QDATE_FORMAT);
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QDate)
