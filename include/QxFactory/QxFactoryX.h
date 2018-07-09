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

#ifndef _QX_FACTORY_X_H_
#define _QX_FACTORY_X_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/shared_ptr.hpp>

#include <QtCore/qhash.h>
#include <QtCore/qmutex.h>

#include "../../include/QxFactory/IxFactory.h"

#include "../../include/QxSingleton/QxSingleton.h"

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

#endif // _QX_FACTORY_X_H_
