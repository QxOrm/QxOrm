#ifndef _QX_TEST_QT_META_PROPERTY_H_
#define _QX_TEST_QT_META_PROPERTY_H_

#ifdef _MSC_VER
#pragma once
#endif

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include "../include/precompiled.h" // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

class QX_DLL1_EXPORT TestQtProperty : public QObject
{

   Q_OBJECT
   Q_PROPERTY(int id READ id WRITE setId)
   Q_PROPERTY(long number READ number WRITE setNumber)
   Q_PROPERTY(QString desc READ desc WRITE setDesc)
   Q_PROPERTY(QDateTime birthDate READ birthDate WRITE setBirthDate)
   Q_PROPERTY(QVariant photo READ photo WRITE setPhoto)

protected:

   int         m_id;
   long        m_number;
   QString     m_desc;
   QDateTime   m_birthDate;
   QVariant    m_photo;

public:

   TestQtProperty() : QObject(), m_id(0), m_number(0) { ; }
   virtual ~TestQtProperty() { ; }

   int id() const                { return m_id; }
   long number() const           { return m_number; }
   QString desc() const          { return m_desc; }
   QDateTime birthDate() const   { return m_birthDate; }
   QVariant photo() const        { return m_photo; }

   void setId(int i)                         { m_id = i; }
   void setNumber(long l)                    { m_number = l; }
   void setDesc(const QString & s)           { m_desc = s; }
   void setBirthDate(const QDateTime & dt)   { m_birthDate = dt; }
   void setPhoto(const QVariant & v)         { m_photo = v; }

};

QX_REGISTER_HPP_QX_DLL1(TestQtProperty, QObject, 0)

#endif // _QX_TEST_QT_META_PROPERTY_H_
