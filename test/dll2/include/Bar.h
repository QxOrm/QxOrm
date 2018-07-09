#ifndef _QX_BAR_H_
#define _QX_BAR_H_

class Foo;

class QX_DLL2_EXPORT Bar
{

   QX_REGISTER_FRIEND_CLASS(Bar)

public:

   typedef boost::shared_ptr<Foo> Foo_ptr;

protected:

   long     m_lId;
   QString  m_sCode;
   QString  m_sValue;
   Foo_ptr  m_pFoo;

public:

   Bar() : m_lId(0)  { ; }
   virtual ~Bar()    { ; }

   long getId() const         { return m_lId; }
   QString getCode() const    { return m_sCode; }
   QString getValue() const   { return m_sValue; }
   Foo_ptr getFoo() const     { return m_pFoo; }

   void setId(long l)                  { m_lId = l; }
   void setCode(const QString & s)     { m_sCode = s; }
   void setValue(const QString & s)    { m_sValue = s; }
   void setFoo(Foo_ptr p)              { m_pFoo = p; }
   void setFoo(long l);

};

QX_REGISTER_HPP_QX_DLL2(Bar, qx::trait::no_base_class_defined, 0)

typedef boost::shared_ptr<Bar> Bar_ptr;
typedef std::vector<Bar_ptr> BarX;
typedef boost::shared_ptr<BarX> BarX_ptr;

#endif // _QX_BAR_H_
