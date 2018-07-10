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

#ifndef _QX_REPOSITORY_X_H_
#define _QX_REPOSITORY_X_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxRepositoryX.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief List of all repositories registered using qx::register_repository<T> function
 */

#include <QtCore/qhash.h>
#include <QtCore/qmutex.h>

#include <QxDao/QxRepository/IxRepository.h>

#include <QxSingleton/QxSingleton.h>

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxRepositoryX : list of all repositories registered using qx::register_repository<T> function
 *
 * Note : you can register automatically all repositories using the macro <i>_QX_AUTO_REGISTER_REPOSITORY</i> into <i>QxConfig.h</i> file.
 */
class QX_DLL_EXPORT QxRepositoryX : public QxSingleton<QxRepositoryX>
{

   friend class IxRepository;
   friend class QxSingleton<QxRepositoryX>;

protected:

   QHash<QString, IxRepository *> m_mapRepositoryX;   //!< Collection of all 'IxRepository' pointer
   QMutex m_oMutexRepositoryX;                        //!< Mutex -> 'QxRepositoryX' is thread-safe
   bool m_bUnregisterAllRepository;                   //!< Flag to know if collection is clearing

private:

   QxRepositoryX() : QxSingleton<QxRepositoryX>("qx::QxRepositoryX"), m_bUnregisterAllRepository(false) { ; }
   virtual ~QxRepositoryX() { unregisterAllRepository(); }

   void registerRepository(const QString & sKey, IxRepository * pRepository);
   void unregisterRepository(const QString & sKey);
   void unregisterAllRepository();

public:

   static IxRepository * get(const QString & sKey);

};

} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::QxRepositoryX)

#endif // _QX_REPOSITORY_X_H_
