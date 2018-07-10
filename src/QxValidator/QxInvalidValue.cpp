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

#include <QxValidator/QxInvalidValue.h>
#include <QxValidator/QxInvalidValueX.h>
#include <QxValidator/IxValidator.h>

#include <QxDataMember/IxDataMember.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QxInvalidValue::QxInvalidValue() : QxPropertyBag(), m_pValidator(NULL) { ; }

QxInvalidValue::~QxInvalidValue() { ; }

const IxValidator * QxInvalidValue::getValidator() const { return m_pValidator; }

void QxInvalidValue::setValidator(const IxValidator * p) { m_pValidator = p; }

QString QxInvalidValue::getFullName() const
{
   QString sResult = m_sPath;
   sResult += ((! m_sPath.isEmpty() && ! m_sPropertyName.isEmpty()) ? QString(".") : QString(""));
   sResult += m_sPropertyName;
   return sResult;
}

} // namespace qx
