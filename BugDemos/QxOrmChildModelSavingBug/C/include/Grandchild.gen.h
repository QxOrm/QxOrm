/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 12:31) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CHILDMODELSAVINGBUG_GRANDCHILD_H_
#define _CHILDMODELSAVINGBUG_GRANDCHILD_H_

class Child;

class CHILDMODELSAVINGBUG_EXPORT Grandchild
{

   QX_REGISTER_FRIEND_CLASS(Grandchild)

public:

   typedef std::shared_ptr<Child> type_parent;

protected:

   long m_Grandchild_id;
   QString m_Name;
   type_parent m_parent;

public:

   Grandchild();
   Grandchild(const long & id);
   virtual ~Grandchild();

   long getGrandchild_id() const;
   QString getName() const;
   type_parent getparent() const;

   void setGrandchild_id(const long & val);
   void setName(const QString & val);
   void setparent(const type_parent & val);

   type_parent getparent(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);

public:

   static QString relation_parent(bool key = false) { Q_UNUSED(key); return "parent"; }

public:

   static QString column_Grandchild_id(bool key = false) { Q_UNUSED(key); return "Grandchild_id"; }
   static QString column_Name(bool key = false) { Q_UNUSED(key); return "Name"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("Grandchild") : QString("t_Grandchild")); }

};

typedef std::shared_ptr<Grandchild> Grandchild_ptr;
typedef qx::QxCollection<long, Grandchild_ptr> list_of_Grandchild;
typedef std::shared_ptr<list_of_Grandchild> list_of_Grandchild_ptr;

QX_REGISTER_COMPLEX_CLASS_NAME_HPP_CHILDMODELSAVINGBUG(Grandchild, qx::trait::no_base_class_defined, 0, Grandchild)

#include "../include/Child.gen.h"

#include "../custom/include/Grandchild.h"

#endif // _CHILDMODELSAVINGBUG_GRANDCHILD_H_
