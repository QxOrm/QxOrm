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

#include <QxPrecompiled.h>

#include <QtCore/qcoreapplication.h>

#include <QxSingleton/IxSingleton.h>
#include <QxSingleton/QxSingletonX.h>

#include <QxMemLeak/mem_leak.h>

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
