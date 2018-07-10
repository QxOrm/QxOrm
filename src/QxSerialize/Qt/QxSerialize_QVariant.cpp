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

#include <QxSerialize/Qt/QxSerialize_QVariant.h>

#include <QxRegister/QxClassX.h>

#include <QxOrm_Impl.h>

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QVariant & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   int iType = static_cast<int>(t.type());
   ar << boost::serialization::make_nvp("type", iType);
   const char * sTag = "value";

   if (iType == QVariant::Bool)
   { bool b(false); b = t.toBool(); ar << boost::serialization::make_nvp(sTag, b); }
   else if (iType == QVariant::Int)
   { int i(0); i = t.toInt(); ar << boost::serialization::make_nvp(sTag, i); }
   else if (iType == QVariant::UInt)
   { uint ui(0); ui = t.toUInt(); ar << boost::serialization::make_nvp(sTag, ui); }
   else if (iType == QVariant::LongLong)
   { long l(0); l = static_cast<long>(t.toLongLong()); ar << boost::serialization::make_nvp(sTag, l); }
   else if (iType == QVariant::ULongLong)
   { unsigned long ul(0); ul = static_cast<unsigned long>(t.toULongLong()); ar << boost::serialization::make_nvp(sTag, ul); }
   else if (iType == QVariant::Double)
   { double d(0.0); d = t.toDouble(); ar << boost::serialization::make_nvp(sTag, d); }
   else if (iType == QVariant::String)
   { QString s; s = t.toString(); ar << boost::serialization::make_nvp(sTag, s); }
   else if (iType == QVariant::Date)
   { QDate qdate; qdate = t.toDate(); ar << boost::serialization::make_nvp(sTag, qdate); }
   else if (iType == QVariant::DateTime)
   { QDateTime qdatetime; qdatetime = t.toDateTime(); ar << boost::serialization::make_nvp(sTag, qdatetime); }
   else if (iType == QVariant::Time)
   { QTime qtime; qtime = t.toTime(); ar << boost::serialization::make_nvp(sTag, qtime); }
   else if (iType == QVariant::ByteArray)
   { QByteArray qbytearray; qbytearray = t.toByteArray(); ar << boost::serialization::make_nvp(sTag, qbytearray); }
   else if (iType == QVariant::Point)
   { QPoint qpoint; qpoint = t.toPoint(); ar << boost::serialization::make_nvp(sTag, qpoint); }
   else if (iType == QVariant::Rect)
   { QRect qrect; qrect = t.toRect(); ar << boost::serialization::make_nvp(sTag, qrect); }
   else if (iType == QVariant::Size)
   { QSize qsize; qsize = t.toSize(); ar << boost::serialization::make_nvp(sTag, qsize); }
   else if (iType == QVariant::RegExp)
   { QRegExp qregexp; qregexp = t.toRegExp(); ar << boost::serialization::make_nvp(sTag, qregexp); }
   else if (iType == QVariant::Url)
   { QUrl qurl; qurl = t.toUrl(); ar << boost::serialization::make_nvp(sTag, qurl); }
#ifdef _QX_ENABLE_QT_GUI
   else if (iType == QVariant::Brush)
   { QBrush qbrush; qbrush = t.value<QBrush>(); ar << boost::serialization::make_nvp(sTag, qbrush); } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
   else if (iType == QVariant::Color)
   { QColor qcolor; qcolor = t.value<QColor>(); ar << boost::serialization::make_nvp(sTag, qcolor); } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
   else if (iType == QVariant::Font)
   { QFont qfont; qfont = t.value<QFont>(); ar << boost::serialization::make_nvp(sTag, qfont); } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
   else if (iType == QVariant::Image)
   { QImage qimage; qimage = t.value<QImage>(); ar << boost::serialization::make_nvp(sTag, qimage); } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
   else if (iType == QVariant::Pixmap)
   { QPixmap qpixmap; qpixmap = t.value<QPixmap>(); ar << boost::serialization::make_nvp(sTag, qpixmap); } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
   else if (iType == QVariant::Region)
   { QRegion qregion; qregion = t.value<QRegion>(); ar << boost::serialization::make_nvp(sTag, qregion); } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
#endif // _QX_ENABLE_QT_GUI
   else if (iType == QVariant::Invalid)
   { QString sInvalid; ar << boost::serialization::make_nvp(sTag, sInvalid); }
   else if (iType == QMetaType::Long)
   { long l(0); l = static_cast<long>(t.toLongLong()); ar << boost::serialization::make_nvp(sTag, l); }
   else if (iType == QMetaType::Short)
   { int i(0); i = t.toInt(); ar << boost::serialization::make_nvp(sTag, i); }
   else if (iType == QMetaType::Char)
   { int i(0); i = t.toInt(); ar << boost::serialization::make_nvp(sTag, i); }
   else if (iType == QMetaType::ULong)
   { unsigned long ul(0); ul = static_cast<unsigned long>(t.toULongLong()); ar << boost::serialization::make_nvp(sTag, ul); }
   else if (iType == QMetaType::UShort)
   { uint ui(0); ui = t.toUInt(); ar << boost::serialization::make_nvp(sTag, ui); }
   else if (iType == QMetaType::UChar)
   { uint ui(0); ui = t.toUInt(); ar << boost::serialization::make_nvp(sTag, ui); }
   else if (iType == QMetaType::Float)
   { double d(0.0); d = t.toDouble(); ar << boost::serialization::make_nvp(sTag, d); }
   else
   {
      QString sUserType("unknown variant serialize type");
      qx::QxClassX::type_fct_save_qvariant_usertype fct;
      fct = qx::QxClassX::getFctSaveQVariantUserType();
      if (fct) { sUserType = fct(t, iType, file_version); }
      ar << boost::serialization::make_nvp(sTag, sUserType);
   }
}

template <class Archive>
inline void qx_load(Archive & ar, QVariant & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   int iType = 0;
   ar >> boost::serialization::make_nvp("type", iType);
   const char * sTag = "value";

   if (iType == QVariant::Bool)
   { bool b(false); ar >> boost::serialization::make_nvp(sTag, b); t = QVariant(b); }
   else if (iType == QVariant::Int)
   { int i(0); ar >> boost::serialization::make_nvp(sTag, i); t = QVariant(i); }
   else if (iType == QVariant::UInt)
   { uint ui(0); ar >> boost::serialization::make_nvp(sTag, ui); t = QVariant(ui); }
   else if (iType == QVariant::LongLong)
   { long l(0); ar >> boost::serialization::make_nvp(sTag, l); t = QVariant(static_cast<qlonglong>(l)); }
   else if (iType == QVariant::ULongLong)
   { unsigned long ul(0); ar >> boost::serialization::make_nvp(sTag, ul); t = QVariant(static_cast<qulonglong>(ul)); }
   else if (iType == QVariant::Double)
   { double d(0.0); ar >> boost::serialization::make_nvp(sTag, d); t = QVariant(d); }
   else if (iType == QVariant::String)
   { QString s; ar >> boost::serialization::make_nvp(sTag, s); t = QVariant(s); }
   else if (iType == QVariant::Date)
   { QDate qdate; ar >> boost::serialization::make_nvp(sTag, qdate); t = QVariant(qdate); }
   else if (iType == QVariant::DateTime)
   { QDateTime qdatetime; ar >> boost::serialization::make_nvp(sTag, qdatetime); t = QVariant(qdatetime); }
   else if (iType == QVariant::Time)
   { QTime qtime; ar >> boost::serialization::make_nvp(sTag, qtime); t = QVariant(qtime); }
   else if (iType == QVariant::ByteArray)
   { QByteArray qbytearray; ar >> boost::serialization::make_nvp(sTag, qbytearray); t = QVariant(qbytearray); }
   else if (iType == QVariant::Point)
   { QPoint qpoint; ar >> boost::serialization::make_nvp(sTag, qpoint); t = QVariant(qpoint); }
   else if (iType == QVariant::Rect)
   { QRect qrect; ar >> boost::serialization::make_nvp(sTag, qrect); t = QVariant(qrect); }
   else if (iType == QVariant::Size)
   { QSize qsize; ar >> boost::serialization::make_nvp(sTag, qsize); t = QVariant(qsize); }
   else if (iType == QVariant::RegExp)
   { QRegExp qregexp; ar >> boost::serialization::make_nvp(sTag, qregexp); t = QVariant(qregexp); }
   else if (iType == QVariant::Url)
   { QUrl qurl; ar >> boost::serialization::make_nvp(sTag, qurl); t = QVariant(qurl); }
#ifdef _QX_ENABLE_QT_GUI
   else if (iType == QVariant::Brush)
   { QBrush qbrush; ar >> boost::serialization::make_nvp(sTag, qbrush); t = qbrush; } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
   else if (iType == QVariant::Color)
   { QColor qcolor; ar >> boost::serialization::make_nvp(sTag, qcolor); t = qcolor; } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
   else if (iType == QVariant::Font)
   { QFont qfont; ar >> boost::serialization::make_nvp(sTag, qfont); t = qfont; } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
   else if (iType == QVariant::Image)
   { QImage qimage; ar >> boost::serialization::make_nvp(sTag, qimage); t = qimage; } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
   else if (iType == QVariant::Pixmap)
   { QPixmap qpixmap; ar >> boost::serialization::make_nvp(sTag, qpixmap); t = qpixmap; } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
   else if (iType == QVariant::Region)
   { QRegion qregion; ar >> boost::serialization::make_nvp(sTag, qregion); t = qregion; } /* if you crash on this line, please check in your main() function if you have created a QApplication and not a QCoreApplication ! */
#endif // _QX_ENABLE_QT_GUI
   else if (iType == QVariant::Invalid)
   { QString sInvalid; ar >> boost::serialization::make_nvp(sTag, sInvalid); t = QVariant(); }
   else if (iType == QMetaType::Long)
   { long l(0); ar >> boost::serialization::make_nvp(sTag, l); t = QVariant(static_cast<qlonglong>(l)); }
   else if (iType == QMetaType::Short)
   { int i(0); ar >> boost::serialization::make_nvp(sTag, i); t = QVariant(i); }
   else if (iType == QMetaType::Char)
   { int i(0); ar >> boost::serialization::make_nvp(sTag, i); t = QVariant(i); }
   else if (iType == QMetaType::ULong)
   { unsigned long ul(0); ar >> boost::serialization::make_nvp(sTag, ul); t = QVariant(static_cast<qulonglong>(ul)); }
   else if (iType == QMetaType::UShort)
   { uint ui(0); ar >> boost::serialization::make_nvp(sTag, ui); t = QVariant(ui); }
   else if (iType == QMetaType::UChar)
   { uint ui(0); ar >> boost::serialization::make_nvp(sTag, ui); t = QVariant(ui); }
   else if (iType == QMetaType::Float)
   { double d(0.0); ar >> boost::serialization::make_nvp(sTag, d); t = QVariant(d); }
   else
   {
      QString sUserType;
      qx::QxClassX::type_fct_load_qvariant_usertype fct;
      ar >> boost::serialization::make_nvp(sTag, sUserType);
      fct = qx::QxClassX::getFctLoadQVariantUserType();
      if (fct) { t = fct(sUserType, iType, file_version); }
      else { t = QVariant(); }
   }
}

} // namespace serialization
} // namespace boost

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QVariant)

#endif // _QX_ENABLE_BOOST_SERIALIZATION
