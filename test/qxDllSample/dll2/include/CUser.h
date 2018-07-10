#ifndef _QX_CLASS_USER_H_
#define _QX_CLASS_USER_H_

#ifdef _MSC_VER
#pragma once
#endif

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../include/precompiled.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include "../../dll1/include/CPerson.h"

class QX_DLL2_EXPORT CUser : public qx::test::CPerson
{

   Q_OBJECT
   QX_REGISTER_FRIEND_CLASS(CUser)

protected:

   long                 m_lUserId;
   QString              m_sProfil;
   qx_bool              m_bIsAdmin;
   QDateTime            m_dtModif;
   qx::test::CPerson *  m_pBrother;

public:

   CUser() : qx::test::CPerson(), m_lUserId(0), m_pBrother(NULL) { ; }
   CUser(long lId) : qx::test::CPerson(), m_lUserId(lId), m_pBrother(NULL) { ; }
   virtual ~CUser() { if (m_pBrother) { delete m_pBrother; m_pBrother = NULL; } }

   void test();

   long getUserId() const                    { return m_lUserId; }
   QString getProfil() const                 { return m_sProfil; }
   qx_bool getIsAdmin() const                { return m_bIsAdmin; }
   QDateTime getDateModif() const            { return m_dtModif; }
   qx::test::CPerson * getBrother() const    { return m_pBrother; }

   void setUserId(long l)                    { m_lUserId = l; }
   void setProfil(const QString & s)         { m_sProfil = s; }
   void setIsAdmin(qx_bool b)                { m_bIsAdmin = b; }
   void setDateModif(const QDateTime & dt)   { m_dtModif = dt; }
   void setBrother(qx::test::CPerson * p)    { if (m_pBrother) { delete m_pBrother; } m_pBrother = p; }

};

QX_REGISTER_HPP_QX_DLL2(CUser, qx::test::CPerson, 2)

#endif // _QX_CLASS_USER_H_
