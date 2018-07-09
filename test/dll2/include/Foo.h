#ifndef _QX_FOO_H_
#define _QX_FOO_H_

#include "../include/Bar.h"

class QX_DLL2_EXPORT Foo
{

   QX_REGISTER_FRIEND_CLASS(Foo)

protected:

   long     m_lId;
   QString  m_sName;
   QString  m_sDesc;
   BarX *   m_pBarX;

public:

   Foo() : m_lId(0), m_pBarX(NULL) { ; }
   virtual ~Foo() { reset(); }

   long getId() const         { return m_lId; }
   QString getName() const    { return m_sName; }
   QString getDesc() const    { return m_sDesc; }
   BarX * getBarX() const     { return m_pBarX; }

   void setId(long l)               { m_lId = l; }
   void setName(const QString & s)  { m_sName = s; }
   void setDesc(const QString & s)  { m_sDesc = s; }
   void setBarX(BarX * p)           { reset(); m_pBarX = p; }

private:

   void reset() { if (m_pBarX) { delete m_pBarX; m_pBarX = NULL; } }

};

QX_REGISTER_HPP_QX_DLL2(Foo, qx::trait::no_base_class_defined, 0)

typedef boost::shared_ptr<Foo> Foo_ptr;
typedef qx::QxCollection<long, Foo_ptr> FooX;
typedef boost::shared_ptr<FooX> FooX_ptr;

#endif // _QX_FOO_H_
