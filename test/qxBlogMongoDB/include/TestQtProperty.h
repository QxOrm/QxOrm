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

class QX_BLOG_DLL_EXPORT TestQtProperty : public QObject, public qx::IxPersistable
{

   Q_OBJECT
   QX_PERSISTABLE_HPP(TestQtProperty)
   Q_PROPERTY(QString id READ id WRITE setId)
   Q_PROPERTY(long number READ number WRITE setNumber)
   Q_PROPERTY(QString desc READ desc WRITE setDesc)
   Q_PROPERTY(QDateTime birthDate READ birthDate WRITE setBirthDate)
   Q_PROPERTY(QVariant photo READ photo WRITE setPhoto)

protected:

   QString     m_id;
   long        m_number;
   QString     m_desc;
   QDateTime   m_birthDate;
   QVariant    m_photo;

public:

   TestQtProperty() : QObject(), m_number(0) { ; }
   virtual ~TestQtProperty() { ; }

   QString id() const            { return m_id; }
   long number() const           { return m_number; }
   QString desc() const          { return m_desc; }
   QDateTime birthDate() const   { return m_birthDate; }
   QVariant photo() const        { return m_photo; }

   void setId(const QString & id)            { m_id = id; }
   void setNumber(long l)                    { m_number = l; }
   void setDesc(const QString & s)           { m_desc = s; }
   void setBirthDate(const QDateTime & dt)   { m_birthDate = dt; }
   void setPhoto(const QVariant & v)         { m_photo = v; }

};

QX_REGISTER_PRIMARY_KEY(TestQtProperty, QString)
QX_REGISTER_HPP_QX_BLOG(TestQtProperty, QObject, 0)

#endif // _QX_TEST_QT_META_PROPERTY_H_
