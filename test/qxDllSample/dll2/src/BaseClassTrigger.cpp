#include "../include/precompiled.h"

#include "../include/BaseClassTrigger.h"

#include <QxOrm_Impl.h>

void BaseClassTrigger::onBeforeInsert(qx::dao::detail::IxDao_Helper * dao)
{
   Q_UNUSED(dao);
   m_dateCreation = QDateTime::currentDateTime();
   m_dateModification = QDateTime::currentDateTime();
   m_userCreation = "current_user_1";
   m_userModification = "current_user_1";
}

void BaseClassTrigger::onBeforeUpdate(qx::dao::detail::IxDao_Helper * dao)
{
   Q_UNUSED(dao);
   m_dateModification = QDateTime::currentDateTime();
   m_userModification = "current_user_2";
}
