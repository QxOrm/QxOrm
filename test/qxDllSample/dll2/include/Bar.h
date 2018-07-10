#ifndef _QX_BAR_H_
#define _QX_BAR_H_

#include "../include/BaseClassTrigger.h"

class Foo;

class QX_DLL2_EXPORT Bar : public BaseClassTrigger
{

   QX_REGISTER_FRIEND_CLASS(Bar)

public:

   typedef qx_shared_ptr<Foo> Foo_ptr;

protected:

   QString  m_sCode;
   QString  m_sValue;
   Foo_ptr  m_pFoo;

public:

   Bar() : BaseClassTrigger() { ; }
   virtual ~Bar()             { ; }

   virtual void makeAbstractClass() { ; }

   QString getCode() const    { return m_sCode; }
   QString getValue() const   { return m_sValue; }
   Foo_ptr getFoo() const     { return m_pFoo; }

   void setCode(const QString & s)     { m_sCode = s; }
   void setValue(const QString & s)    { m_sValue = s; }
   void setFoo(Foo_ptr p)              { m_pFoo = p; }
   void setFoo(long l);

};

QX_REGISTER_HPP_QX_DLL2(Bar, BaseClassTrigger, 0)

typedef qx_shared_ptr<Bar> Bar_ptr;
typedef std::vector<Bar_ptr> BarX;
typedef qx_shared_ptr<BarX> BarX_ptr;

#endif // _QX_BAR_H_
