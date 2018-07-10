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

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxDao_Trigger
{

private:

   typedef typename qx::trait::get_base_class<T>::type type_base;
   enum { is_valid_base_class = (! std::is_same<type_base, qx::trait::no_base_class_defined>::value) };

public:

   static inline void onBeforeInsert(T * t, qx::dao::detail::IxDao_Helper * dao) { TriggerHelper<is_valid_base_class, 0>::onBeforeInsert(t, dao); }
   static inline void onBeforeUpdate(T * t, qx::dao::detail::IxDao_Helper * dao) { TriggerHelper<is_valid_base_class, 0>::onBeforeUpdate(t, dao); }
   static inline void onBeforeDelete(T * t, qx::dao::detail::IxDao_Helper * dao) { TriggerHelper<is_valid_base_class, 0>::onBeforeDelete(t, dao); }
   static inline void onBeforeFetch(T * t, qx::dao::detail::IxDao_Helper * dao)  { TriggerHelper<is_valid_base_class, 0>::onBeforeFetch(t, dao); }
   static inline void onAfterInsert(T * t, qx::dao::detail::IxDao_Helper * dao)  { TriggerHelper<is_valid_base_class, 0>::onAfterInsert(t, dao); }
   static inline void onAfterUpdate(T * t, qx::dao::detail::IxDao_Helper * dao)  { TriggerHelper<is_valid_base_class, 0>::onAfterUpdate(t, dao); }
   static inline void onAfterDelete(T * t, qx::dao::detail::IxDao_Helper * dao)  { TriggerHelper<is_valid_base_class, 0>::onAfterDelete(t, dao); }
   static inline void onAfterFetch(T * t, qx::dao::detail::IxDao_Helper * dao)   { TriggerHelper<is_valid_base_class, 0>::onAfterFetch(t, dao); }

private:

   template <bool isValidBaseClass /* = false */, int dummy>
   struct TriggerHelper
   {
      static inline void onBeforeInsert(T * t, qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onBeforeUpdate(T * t, qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onBeforeDelete(T * t, qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onBeforeFetch(T * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onAfterInsert(T * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onAfterUpdate(T * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onAfterDelete(T * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onAfterFetch(T * t, qx::dao::detail::IxDao_Helper * dao)   { Q_UNUSED(t); Q_UNUSED(dao); }
   };

   template <int dummy>
   struct TriggerHelper<true, dummy>
   {
      static inline void onBeforeInsert(T * t, qx::dao::detail::IxDao_Helper * dao) { qx::dao::detail::QxDao_Trigger<type_base>::onBeforeInsert(static_cast<type_base *>(t), dao); }
      static inline void onBeforeUpdate(T * t, qx::dao::detail::IxDao_Helper * dao) { qx::dao::detail::QxDao_Trigger<type_base>::onBeforeUpdate(static_cast<type_base *>(t), dao); }
      static inline void onBeforeDelete(T * t, qx::dao::detail::IxDao_Helper * dao) { qx::dao::detail::QxDao_Trigger<type_base>::onBeforeDelete(static_cast<type_base *>(t), dao); }
      static inline void onBeforeFetch(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<type_base>::onBeforeFetch(static_cast<type_base *>(t), dao); }
      static inline void onAfterInsert(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<type_base>::onAfterInsert(static_cast<type_base *>(t), dao); }
      static inline void onAfterUpdate(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<type_base>::onAfterUpdate(static_cast<type_base *>(t), dao); }
      static inline void onAfterDelete(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<type_base>::onAfterDelete(static_cast<type_base *>(t), dao); }
      static inline void onAfterFetch(T * t, qx::dao::detail::IxDao_Helper * dao)   { qx::dao::detail::QxDao_Trigger<type_base>::onAfterFetch(static_cast<type_base *>(t), dao); }
   };

};

} // namespace detail
} // namespace dao
} // namespace qx
