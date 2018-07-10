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

#ifndef _QX_SINGLETON_X_H_
#define _QX_SINGLETON_X_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSingletonX.h
 * \author Lionel Marty
 * \ingroup QxSingleton
 * \brief List of all singleton defined by QxOrm library
 */

#include <QtCore/qhash.h>

#include <QxSingleton/QxSingleton.h>

#include <QxCollection/QxForeach.h>

namespace qx {

/*!
 * \ingroup QxSingleton
 * \brief qx::QxSingletonX : list of all singleton defined by QxOrm library (this container is also a singleton)
 */
class QX_DLL_EXPORT QxSingletonX : public QxSingleton<QxSingletonX>
{

   friend class QxSingleton<QxSingletonX>;
   friend class IxSingleton;

private:

   static QHash<QString, IxSingleton *> & getMapSingletonX();     //!< Collection of all 'IxSingleton' pointer
   static QMutex * getMutexSingletonX();                          //!< Mutex -> 'QxSingletonX' is thread-safe
   static bool & getOnClearSingletonX();                          //!< Clear collection of 'IxSingleton' in event

private:

   QxSingletonX();
   virtual ~QxSingletonX() { ; }

   static bool addSingleton(const QString & sKey, IxSingleton * pSingleton);
   static bool removeSingleton(const QString & sKey);
   static void deleteAllSingleton();

};

} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::QxSingletonX)

#endif // _QX_SINGLETON_X_H_
