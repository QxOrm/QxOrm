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

#include <QxPrecompiled.h>

#include <QtCore/qcoreapplication.h>

#include <QxSingleton/IxSingleton.h>
#include <QxSingleton/QxSingletonX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxSingleton::IxSingleton(const QString & sKey) : m_sKeySingleton(sKey)
{
#ifdef _QX_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::IxSingleton constructor '%s'", qPrintable(m_sKeySingleton));
#endif // _QX_TRACE_CONSTRUCTOR_DESTRUCTOR

   QxSingletonX::addSingleton(m_sKeySingleton, this);
}

IxSingleton::~IxSingleton()
{
#ifdef _QX_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::IxSingleton destructor '%s'", qPrintable(m_sKeySingleton));
#endif // _QX_TRACE_CONSTRUCTOR_DESTRUCTOR

   QxSingletonX::removeSingleton(m_sKeySingleton);
}

void IxSingleton::initQxSingletonX()
{
   static bool bDone = false;
   if (! bDone && QCoreApplication::instance()) { bDone = true; QxSingletonX::getSingleton(); }
}

} // namespace qx
