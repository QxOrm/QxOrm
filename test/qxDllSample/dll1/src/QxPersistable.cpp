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

#include "../include/precompiled.h"

#include "../include/QxPersistable.h"

#include <QxMemLeak.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_QX_DLL1(qx::QxPersistable, qx_QxPersistable)

namespace qx {

template <>
void register_class(QxClass<qx::QxPersistable> & t)
{
   t.setPropertyBag("QX_NOT_PERSISTABLE", "1");

   t.setSoftDelete(qx::QxSoftDelete("qx_deleted_at"));

   t.id(& qx::QxPersistable::m_qxId, "qx_id");

   t.data(& qx::QxPersistable::m_qxDateCreation, "qx_date_creation");
   t.data(& qx::QxPersistable::m_qxDateModification, "qx_date_modification");

   QxValidatorX<qx::QxPersistable> * pAllValidator = t.getAllValidator();
   pAllValidator->add_CustomValidator(& qx::QxPersistable::qxIsValidInternal);
}

QX_PERSISTABLE_CPP(QxPersistable)

QxPersistable::QxPersistable() : QObject(), qx::IxPersistable(), m_qxId(0) { ; }

QxPersistable::~QxPersistable() { ; }

long QxPersistable::qxGetId() const { return m_qxId; }

QDateTime QxPersistable::qxGetDateCreation() const { return m_qxDateCreation.toDateTime(); }

QDateTime QxPersistable::qxGetDateModification() const { return m_qxDateModification.toDateTime(); }

void QxPersistable::qxSetId(long l) { m_qxId = l; }

void QxPersistable::qxSetDateCreation(const QDateTime & dt) { m_qxDateCreation.fromDateTime(dt); }

void QxPersistable::qxSetDateModification(const QDateTime & dt) { m_qxDateModification.fromDateTime(dt); }

void QxPersistable::qxIsValidInternal(qx::QxInvalidValueX & invalidValues) { this->qxIsValid(invalidValues); }

void QxPersistable::qxIsValid(qx::QxInvalidValueX & invalidValues) { Q_UNUSED(invalidValues); }

void QxPersistable::qxOnBeforeInsert(qx::dao::detail::IxDao_Helper * dao)
{
   Q_UNUSED(dao);
   m_qxDateCreation.fromDateTime(QDateTime::currentDateTime());
   m_qxDateModification = m_qxDateCreation;
   Q_EMIT qxOnBeforeInsert(this);
}

void QxPersistable::qxOnBeforeUpdate(qx::dao::detail::IxDao_Helper * dao)
{
   Q_UNUSED(dao);
   m_qxDateModification.fromDateTime(QDateTime::currentDateTime());
   Q_EMIT qxOnBeforeUpdate(this);
}

void QxPersistable::qxOnBeforeDelete(qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(dao); Q_EMIT qxOnBeforeDelete(this); }

void QxPersistable::qxOnBeforeFetch(qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(dao); Q_EMIT qxOnBeforeFetch(this); }

void QxPersistable::qxOnAfterInsert(qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(dao); Q_EMIT qxOnAfterInsert(this); }

void QxPersistable::qxOnAfterUpdate(qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(dao); Q_EMIT qxOnAfterUpdate(this); }

void QxPersistable::qxOnAfterDelete(qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(dao); Q_EMIT qxOnAfterDelete(this); }

void QxPersistable::qxOnAfterFetch(qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(dao); Q_EMIT qxOnAfterFetch(this); }

} // namespace qx
