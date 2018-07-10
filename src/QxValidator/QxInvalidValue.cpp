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

#include <QxValidator/QxInvalidValue.h>
#include <QxValidator/QxInvalidValueX.h>
#include <QxValidator/IxValidator.h>

#include <QxDataMember/IxDataMember.h>

#include <QxSerialize/QDataStream/QxSerializeQDataStream_boost_shared_ptr.h>
#include <QxSerialize/QDataStream/QxSerializeQDataStream_std_shared_ptr.h>

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

QDataStream & operator<< (QDataStream & stream, const qx::QxInvalidValue & t)
{
   stream << t.m_sMessage;
   stream << t.m_sPropertyName;
   stream << t.m_sPath;
   stream << t.m_lstPropertyBag;
   return stream;
}

QDataStream & operator>> (QDataStream & stream, qx::QxInvalidValue & t)
{
   stream >> t.m_sMessage;
   stream >> t.m_sPropertyName;
   stream >> t.m_sPath;
   stream >> t.m_lstPropertyBag;
   return stream;
}
