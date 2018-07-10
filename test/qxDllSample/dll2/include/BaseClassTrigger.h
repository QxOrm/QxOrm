#ifndef _QX_BASE_CLASS_TRIGGER_H_
#define _QX_BASE_CLASS_TRIGGER_H_

class QX_DLL2_EXPORT BaseClassTrigger
{

   QX_REGISTER_FRIEND_CLASS(BaseClassTrigger)

protected:

   long        m_id;
   QDateTime   m_dateCreation;
   QDateTime   m_dateModification;
   QString     m_userCreation;
   QString     m_userModification;

public:

   BaseClassTrigger() : m_id(0)  { ; }
   virtual ~BaseClassTrigger()   { ; }

   virtual void makeAbstractClass() = 0;

   long getId() const                     { return m_id; }
   QDateTime getDateCreation() const      { return m_dateCreation; }
   QDateTime getDateModification() const  { return m_dateModification; }
   QString getUserCreation() const        { return m_userCreation; }
   QString getUserModification() const    { return m_userModification; }

   void setId(long l)                              { m_id = l; }
   void setDateCreation(const QDateTime & dt)      { m_dateCreation = dt; }
   void setDateModification(const QDateTime & dt)  { m_dateModification = dt; }
   void setUserCreation(const QString & s)         { m_userCreation = s; }
   void setUserModification(const QString & s)     { m_userModification = s; }

   void onBeforeInsert(qx::dao::detail::IxDao_Helper * dao);
   void onBeforeUpdate(qx::dao::detail::IxDao_Helper * dao);

};

QX_REGISTER_ABSTRACT_CLASS(BaseClassTrigger)
QX_REGISTER_HPP_QX_DLL2(BaseClassTrigger, qx::trait::no_base_class_defined, 0)

namespace qx {
namespace dao {
namespace detail {

template <>
struct QxDao_Trigger<BaseClassTrigger>
{

   static inline void onBeforeInsert(BaseClassTrigger * t, qx::dao::detail::IxDao_Helper * dao) { if (t) { t->onBeforeInsert(dao); } }
   static inline void onBeforeUpdate(BaseClassTrigger * t, qx::dao::detail::IxDao_Helper * dao) { if (t) { t->onBeforeUpdate(dao); } }
   static inline void onBeforeDelete(BaseClassTrigger * t, qx::dao::detail::IxDao_Helper * dao) { Q_UNUSED(t); Q_UNUSED(dao); }
   static inline void onBeforeFetch(BaseClassTrigger * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
   static inline void onAfterInsert(BaseClassTrigger * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
   static inline void onAfterUpdate(BaseClassTrigger * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
   static inline void onAfterDelete(BaseClassTrigger * t, qx::dao::detail::IxDao_Helper * dao)  { Q_UNUSED(t); Q_UNUSED(dao); }
   static inline void onAfterFetch(BaseClassTrigger * t, qx::dao::detail::IxDao_Helper * dao)   { Q_UNUSED(t); Q_UNUSED(dao); }

};

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _QX_BASE_CLASS_TRIGGER_H_
