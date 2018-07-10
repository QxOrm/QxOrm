#ifndef _QX_CLASS_PERSON_H_
#define _QX_CLASS_PERSON_H_

#ifdef _MSC_VER
#pragma once
#endif

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../include/precompiled.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

namespace qx {
namespace test {

class QX_DLL1_EXPORT CPerson : public QObject
{

   Q_OBJECT
   QX_REGISTER_FRIEND_CLASS(qx::test::CPerson)

public:

   enum sex { male, female, unknown };

protected:

   long     m_lPersonId;
   QString  m_sFirstName;
   QString  m_sLastName;
   double   m_dDouble;
   sex      m_eSex;

public:

   CPerson() : QObject(), m_lPersonId(0), m_sFirstName("toto"), m_dDouble(4.5678), m_eSex(unknown) { ; }
   CPerson(long lId) : QObject(), m_lPersonId(lId), m_sFirstName("toto"), m_dDouble(4.5678), m_eSex(unknown) { ; }
   virtual ~CPerson() { ; }

   long getPersonId() const      { return m_lPersonId; }
   QString getFirstName() const  { return m_sFirstName; }
   QString getLastName() const   { return m_sLastName; }
   double getDouble() const      { return m_dDouble; }
   sex getSex() const            { return m_eSex; }

   void setPersonId(long l)               { m_lPersonId = l; }
   void setFirstName(const QString & s)   { m_sFirstName = s; }
   void setLastName(const QString & s)    { m_sLastName = s; }
   void setDouble(double d)               { m_dDouble = d; }
   void setSex(sex e)                     { m_eSex = e; }

   static int testStaticFct(const QString & s);

private:

   void isValid(qx::QxInvalidValueX & invalidValues);

};

} // namespace test
} // namespace qx

QX_REGISTER_COMPLEX_CLASS_NAME_HPP_QX_DLL1(qx::test::CPerson, QObject, 0, qx_test_CPerson)

#endif // _QX_CLASS_PERSON_H_
