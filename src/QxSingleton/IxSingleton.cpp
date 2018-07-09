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

#include "../../include/QxPrecompiled.h"

#include <QtCore/qcoreapplication.h>

#include "../../include/QxSingleton/IxSingleton.h"
#include "../../include/QxSingleton/QxSingletonX.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {

IxSingleton::IxSingleton(const QString & sKey) : boost::noncopyable(), m_sKeySingleton(sKey)
{
#if _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::IxSingleton constructor '%s'", qPrintable(m_sKeySingleton));
#endif // _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR

   QxSingletonX::addSingleton(m_sKeySingleton, this);
}

IxSingleton::~IxSingleton()
{
#if _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::IxSingleton destructor '%s'", qPrintable(m_sKeySingleton));
#endif // _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR

   QxSingletonX::removeSingleton(m_sKeySingleton);
}

void IxSingleton::initQxSingletonX()
{
   static bool bDone = false;
   if (! bDone && QCoreApplication::instance()) { bDone = true; QxSingletonX::getSingleton(); }
}

} // namespace qx
