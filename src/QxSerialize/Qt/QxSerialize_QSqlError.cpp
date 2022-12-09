/****************************************************************************
**
** https://www.qxorm.com/
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

#include <QxSerialize/Qt/QxSerialize_QSqlError.h>

#include <QxOrm_Impl.h>

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QSqlError & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QString sDatabaseText = t.databaseText();
   QString sDriverText = t.driverText();
#if (QT_VERSION >= 0x050300)
   int iNumber = t.nativeErrorCode().toInt();
   QString sNativeErrorCode = t.nativeErrorCode();
#else // (QT_VERSION >= 0x050300)
   int iNumber = t.number();
   QString sNativeErrorCode = "";
#endif // (QT_VERSION >= 0x050300)
   int iType = static_cast<int>(t.type());

   ar << boost::serialization::make_nvp("database_text", sDatabaseText);
   ar << boost::serialization::make_nvp("driver_text", sDriverText);
   ar << boost::serialization::make_nvp("number", iNumber);
   ar << boost::serialization::make_nvp("type", iType);
   ar << boost::serialization::make_nvp("native_error_code", sNativeErrorCode);
}

template <class Archive>
inline void qx_load(Archive & ar, QSqlError & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QString sDatabaseText; QString sDriverText;
   int iNumber(0); int iType(0);
   QString sNativeErrorCode;

   ar >> boost::serialization::make_nvp("database_text", sDatabaseText);
   ar >> boost::serialization::make_nvp("driver_text", sDriverText);
   ar >> boost::serialization::make_nvp("number", iNumber);
   ar >> boost::serialization::make_nvp("type", iType);
   ar >> boost::serialization::make_nvp("native_error_code", sNativeErrorCode);

#if (QT_VERSION >= 0x050300)
   t = QSqlError(sDriverText, sDatabaseText, static_cast<QSqlError::ErrorType>(iType), sNativeErrorCode);
#else // (QT_VERSION >= 0x050300)
   t.setDatabaseText(sDatabaseText);
   t.setDriverText(sDriverText);
   t.setNumber(iNumber);
   t.setType(static_cast<QSqlError::ErrorType>(iType));
#endif // (QT_VERSION >= 0x050300)
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QSqlError)

#endif // _QX_ENABLE_BOOST_SERIALIZATION
