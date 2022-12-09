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

#include <QxSerialize/QDataStream/QxSerializeQDataStream_QSqlError.h>

#include <QxMemLeak/mem_leak.h>

QDataStream & operator<< (QDataStream & stream, const QSqlError & t)
{
   QString sDatabaseText = t.databaseText();
   QString sDriverText = t.driverText();
#if (QT_VERSION >= 0x050300)
   qint32 iNumber = static_cast<qint32>(t.nativeErrorCode().toInt());
   QString sNativeErrorCode = t.nativeErrorCode();
#else // (QT_VERSION >= 0x050300)
   qint32 iNumber = static_cast<qint32>(t.number());
   QString sNativeErrorCode = "";
#endif // (QT_VERSION >= 0x050300)
   qint32 iType = static_cast<qint32>(t.type());

   stream << sDatabaseText;
   stream << sDriverText;
   stream << iNumber;
   stream << iType;
   stream << sNativeErrorCode;

   return stream;
}

QDataStream & operator>> (QDataStream & stream, QSqlError & t)
{
   QString sDatabaseText; QString sDriverText;
   qint32 iNumber(0); qint32 iType(0);
   QString sNativeErrorCode;

   stream >> sDatabaseText;
   stream >> sDriverText;
   stream >> iNumber;
   stream >> iType;
   stream >> sNativeErrorCode;

#if (QT_VERSION >= 0x050300)
   t = QSqlError(sDriverText, sDatabaseText, static_cast<QSqlError::ErrorType>(iType), sNativeErrorCode);
#else // (QT_VERSION >= 0x050300)
   t.setDatabaseText(sDatabaseText);
   t.setDriverText(sDriverText);
   t.setNumber(static_cast<int>(iNumber));
   t.setType(static_cast<QSqlError::ErrorType>(iType));
#endif // (QT_VERSION >= 0x050300)

   return stream;
}
