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

#ifndef _QX_FACTORY_X_H_
#define _QX_FACTORY_X_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/shared_ptr.hpp>

#include <QtCore/qhash.h>
#include <QtCore/qmutex.h>

#include <QxFactory/IxFactory.h>

#include <QxSingleton/QxSingleton.h>

namespace qx {

class QX_DLL_EXPORT QxFactoryX : public QxSingleton<QxFactoryX>
{

   friend class QxSingleton<QxFactoryX>;
   friend class IxFactory;

protected:

   QHash<QString, IxFactory *> m_mapFactoryX;   // Collection of all 'IxFactory' pointer
   QMutex m_oMutexFactoryX;                     // Mutex -> 'QxFactoryX' is thread-safe

private:

   QxFactoryX() : QxSingleton<QxFactoryX>("qx::QxFactoryX") { ; }
   virtual ~QxFactoryX() { ; }

   void registerFactory(const QString & sKey, IxFactory * pFactory);
   void unregisterFactory(const QString & sKey);

public:

   boost::any createObject(const QString & sKey) const;

   static inline boost::any createInstance(const QString & sKey) { return QxFactoryX::getSingleton()->createObject(sKey); }

};

inline boost::any create(const QString & sKey) { return qx::QxFactoryX::createInstance(sKey); }

} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::QxFactoryX)

#endif // _QX_FACTORY_X_H_
