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

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxDao_Trigger
{

private:

   typedef typename qx::trait::get_base_class<T>::type type_base;
   enum { is_valid_base_class = (! boost::is_same<type_base, qx::trait::no_base_class_defined>::value) };

public:

   static inline void onBeforeInsert(T * t, qx::dao::detail::IxDao_Helper * dao) { qx::dao::detail::QxDao_Trigger<T>::TriggerHelper<is_valid_base_class, 0>::onBeforeInsert(t, dao); }
   static inline void onBeforeUpdate(T * t, qx::dao::detail::IxDao_Helper * dao) { qx::dao::detail::QxDao_Trigger<T>::TriggerHelper<is_valid_base_class, 0>::onBeforeUpdate(t, dao); }
   static inline void onBeforeDelete(T * t, qx::dao::detail::IxDao_Helper * dao) { qx::dao::detail::QxDao_Trigger<T>::TriggerHelper<is_valid_base_class, 0>::onBeforeDelete(t, dao); }
   static inline void onAfterInsert(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<T>::TriggerHelper<is_valid_base_class, 0>::onAfterInsert(t, dao); }
   static inline void onAfterUpdate(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<T>::TriggerHelper<is_valid_base_class, 0>::onAfterUpdate(t, dao); }
   static inline void onAfterDelete(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<T>::TriggerHelper<is_valid_base_class, 0>::onAfterDelete(t, dao); }

private:

   template <bool isValidBaseClass /* = false */, int dummy>
   struct TriggerHelper
   {
      static inline void onBeforeInsert(T * t, qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onBeforeUpdate(T * t, qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onBeforeDelete(T * t, qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onAfterInsert(T * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onAfterUpdate(T * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
      static inline void onAfterDelete(T * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
   };

   template <int dummy>
   struct TriggerHelper<true, dummy>
   {
      static inline void onBeforeInsert(T * t, qx::dao::detail::IxDao_Helper * dao) { qx::dao::detail::QxDao_Trigger<type_base>::onBeforeInsert(static_cast<type_base *>(t), dao); }
      static inline void onBeforeUpdate(T * t, qx::dao::detail::IxDao_Helper * dao) { qx::dao::detail::QxDao_Trigger<type_base>::onBeforeUpdate(static_cast<type_base *>(t), dao); }
      static inline void onBeforeDelete(T * t, qx::dao::detail::IxDao_Helper * dao) { qx::dao::detail::QxDao_Trigger<type_base>::onBeforeDelete(static_cast<type_base *>(t), dao); }
      static inline void onAfterInsert(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<type_base>::onAfterInsert(static_cast<type_base *>(t), dao); }
      static inline void onAfterUpdate(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<type_base>::onAfterUpdate(static_cast<type_base *>(t), dao); }
      static inline void onAfterDelete(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<type_base>::onAfterDelete(static_cast<type_base *>(t), dao); }
   };

};

} // namespace detail
} // namespace dao
} // namespace qx
