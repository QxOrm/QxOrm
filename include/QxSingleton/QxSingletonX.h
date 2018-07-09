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

#ifndef _QX_SINGLETON_X_H_
#define _QX_SINGLETON_X_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtCore/qhash.h>

#include "../../include/QxSingleton/QxSingleton.h"

#include "../../include/QxCollection/QxForeach.h"

namespace qx {

class QX_DLL_EXPORT QxSingletonX : public QxSingleton<QxSingletonX>
{

   friend class QxSingleton<QxSingletonX>;
   friend class IxSingleton;

private:

   static QHash<QString, IxSingleton *> m_mapSingletonX; // Collection of all 'IxSingleton' pointer
   static QMutex m_oMutexSingletonX;                     // Mutex -> 'QxSingletonX' is thread-safe
   static bool m_bOnClearSingletonX;                     // Clear collection of 'IxSingleton' in event

private:

   QxSingletonX();
   virtual ~QxSingletonX() { ; }

   static bool addSingleton(const QString & sKey, IxSingleton * pSingleton);
   static bool removeSingleton(const QString & sKey);
   static void deleteAllSingleton();

};

} // namespace qx

#endif // _QX_SINGLETON_X_H_
