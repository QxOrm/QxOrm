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

#include <QxPrecompiled.h>

#include <QxModelView/QxModelRowCompare.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace model_view {

bool compareQVariant(const QVariant & v1, const QVariant & v2, bool bAscending)
{
   int type1 = static_cast<int>(v1.type());
   int type2 = static_cast<int>(v2.type());

   if (type1 != type2)
   {
      if (bAscending) { return (v1.toString() < v2.toString()); }
      else { return (v1.toString() > v2.toString()); }
   }

   if (type1 == QVariant::Bool)
   {
      int i1 = (v1.toBool() ? 1 : 0);
      int i2 = (v2.toBool() ? 1 : 0);
      if (bAscending) { return (i1 < i2); }
      else { return (i1 > i2); }
   }
   else if (type1 == QVariant::Int)
   {
      if (bAscending) { return (v1.toInt() < v2.toInt()); }
      else { return (v1.toInt() > v2.toInt()); }
   }
   else if (type1 == QVariant::UInt)
   {
      if (bAscending) { return (v1.toUInt() < v2.toUInt()); }
      else { return (v1.toUInt() > v2.toUInt()); }
   }
   else if (type1 == QVariant::LongLong)
   {
      if (bAscending) { return (v1.toLongLong() < v2.toLongLong()); }
      else { return (v1.toLongLong() > v2.toLongLong()); }
   }
   else if (type1 == QVariant::ULongLong)
   {
      if (bAscending) { return (v1.toULongLong() < v2.toULongLong()); }
      else { return (v1.toULongLong() > v2.toULongLong()); }
   }
   else if (type1 == QVariant::Double)
   {
      if (bAscending) { return (v1.toDouble() < v2.toDouble()); }
      else { return (v1.toDouble() > v2.toDouble()); }
   }
   else if (type1 == QVariant::Date)
   {
      if (bAscending) { return (v1.toDate() < v2.toDate()); }
      else { return (v1.toDate() > v2.toDate()); }
   }
   else if (type1 == QVariant::DateTime)
   {
      if (bAscending) { return (v1.toDateTime() < v2.toDateTime()); }
      else { return (v1.toDateTime() > v2.toDateTime()); }
   }
   else if (type1 == QVariant::Time)
   {
      if (bAscending) { return (v1.toTime() < v2.toTime()); }
      else { return (v1.toTime() > v2.toTime()); }
   }
   else if (type1 == QVariant::ByteArray)
   {
      if (bAscending) { return (v1.toByteArray() < v2.toByteArray()); }
      else { return (v1.toByteArray() > v2.toByteArray()); }
   }

   // Default comparaison converting to string
   if (bAscending) { return (v1.toString() < v2.toString()); }
   return (v1.toString() > v2.toString());
}

} // namespace model_view
} // namespace qx
