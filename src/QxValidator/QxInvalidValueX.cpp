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

#include <QxValidator/QxInvalidValueX.h>
#include <QxValidator/IxValidator.h>

#include <QxDataMember/IxDataMember.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QxInvalidValueX::QxInvalidValueX() { ; }

QxInvalidValueX::~QxInvalidValueX() { ; }

QString QxInvalidValueX::getCurrentPath() const { return m_sCurrentPath; }

void QxInvalidValueX::setCurrentPath(const QString & s) { m_sCurrentPath = s; }

long QxInvalidValueX::count() const { return m_lstInvalidValues.count(); }

void QxInvalidValueX::dump() const { QString s = text(); qDebug("[QxOrm] %s", qPrintable(s)); }

QxInvalidValue QxInvalidValueX::at(long l) const { return (((l < 0) || (l >= m_lstInvalidValues.count())) ? QxInvalidValue() : m_lstInvalidValues.at(l)); }

QString QxInvalidValueX::text() const
{
   if (m_lstInvalidValues.count() <= 0) { return "There is no invalid value"; }
   QString sResult = "List of invalid values (" + QString::number(m_lstInvalidValues.count()) + ") :";

   for (long l = 0; l < m_lstInvalidValues.count(); l++)
   {
      QxInvalidValue invalidValue = m_lstInvalidValues.at(l);
      sResult += "\n\t- " + invalidValue.getMessage();
      sResult += " (" + invalidValue.getFullName() + ")";
   }

   return sResult;
}

void QxInvalidValueX::insert(const IxValidator * pValidator)
{
   if (! pValidator) { return; }
   IxDataMember * pDataMember = pValidator->getDataMember();
   QString sMessage = pValidator->getMessage();
   sMessage.replace("%NAME%", (pDataMember ? pDataMember->getName() : QString()));
   sMessage.replace("%CONSTRAINT%", pValidator->getConstraint().toString());
   QVariantList lstConstraints = pValidator->getConstraints();
   for (long l = 0; l < lstConstraints.count(); l++)
   { sMessage.replace("%CONSTRAINT_" + QString::number(l) + "%", lstConstraints.at(l).toString()); }
   if (sMessage.isEmpty()) { qAssert(false); return; }

   QxInvalidValue invalidValue;
   invalidValue.setValidator(pValidator);
   invalidValue.setMessage(sMessage);
   invalidValue.setPropertyName(pDataMember ? pDataMember->getName() : QString());
   invalidValue.setPath(m_sCurrentPath);
   m_lstInvalidValues.append(invalidValue);
}

void QxInvalidValueX::insert(const QString & sMessage)
{
   if (sMessage.isEmpty()) { qAssert(false); return; }
   QxInvalidValue invalidValue;
   invalidValue.setMessage(sMessage);
   invalidValue.setPath(m_sCurrentPath);
   m_lstInvalidValues.append(invalidValue);
}

void QxInvalidValueX::insert(const QxInvalidValue & invalidValue)
{
   if (invalidValue.getMessage().isEmpty()) { qAssert(false); return; }
   QxInvalidValue clone = invalidValue;
   clone.setPath(m_sCurrentPath);
   m_lstInvalidValues.append(clone);
}

void QxInvalidValueX::insert(const QxInvalidValueX & other)
{
   for (long l = 0; l < other.count(); l++)
   {
      QxInvalidValue invalidValue = other.at(l);
      if (invalidValue.getMessage().isEmpty()) { qAssert(false); continue; }
      QString sOtherPath = invalidValue.getPath();
      QString sCurrPath = m_sCurrentPath;
      sCurrPath += ((! m_sCurrentPath.isEmpty() && ! sOtherPath.isEmpty()) ? QString(".") : QString(""));
      sCurrPath += sOtherPath;
      invalidValue.setPath(sCurrPath);
      m_lstInvalidValues.append(invalidValue);
   }
}

} // namespace qx

QDataStream & operator<< (QDataStream & stream, const qx::QxInvalidValueX & t)
{
   stream << t.m_lstInvalidValues;
   stream << t.m_sCurrentPath;
   return stream;
}

QDataStream & operator>> (QDataStream & stream, qx::QxInvalidValueX & t)
{
   stream >> t.m_lstInvalidValues;
   stream >> t.m_sCurrentPath;
   return stream;
}
