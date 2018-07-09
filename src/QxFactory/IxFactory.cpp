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

#include "../../include/QxFactory/IxFactory.h"
#include "../../include/QxFactory/QxFactoryX.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {

IxFactory::IxFactory(const QString & sKey) : boost::noncopyable(), m_sKeyFactory(sKey)
{
#if _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::IxFactory constructor '%s'", qPrintable(m_sKeyFactory));
#endif // _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR

   QxFactoryX::getSingleton()->registerFactory(m_sKeyFactory, this);
}

IxFactory::~IxFactory()
{
#if _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::IxFactory destructor '%s'", qPrintable(m_sKeyFactory));
#endif // _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR

   if (! QxFactoryX::isSingletonNull()) { QxFactoryX::getSingleton()->unregisterFactory(m_sKeyFactory); }
}

} // namespace qx
