/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 12:31) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CHILDMODELSAVINGBUG_CHILD_H_
#define _CHILDMODELSAVINGBUG_CHILD_H_

class Grandchild;
class Parent;

class CHILDMODELSAVINGBUG_EXPORT Child
{

   QX_REGISTER_FRIEND_CLASS(Child)

public:

   typedef qx::QxCollection<long, std::shared_ptr<Grandchild> > type_list_of_Grandchild;
   typedef std::shared_ptr<Parent> type_parent;

protected:

   long m_Child_id;
   QString m_Name;
   type_list_of_Grandchild m_list_of_Grandchild;
   type_parent m_parent;

public:

   Child();
   Child(const long & id);
   virtual ~Child();

   long getChild_id() const;
   QString getName() const;
   type_list_of_Grandchild getlist_of_Grandchild() const;
   type_list_of_Grandchild & list_of_Grandchild();
   const type_list_of_Grandchild & list_of_Grandchild() const;
   type_parent getparent() const;

   void setChild_id(const long & val);
   void setName(const QString & val);
   void setlist_of_Grandchild(const type_list_of_Grandchild & val);
   void setparent(const type_parent & val);

   type_list_of_Grandchild getlist_of_Grandchild(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_list_of_Grandchild & list_of_Grandchild(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_parent getparent(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);

public:

   static QString relation_list_of_Grandchild(bool key = false) { Q_UNUSED(key); return "list_of_Grandchild"; }
   static QString relation_parent(bool key = false) { Q_UNUSED(key); return "parent"; }

public:

   static QString column_Child_id(bool key = false) { Q_UNUSED(key); return "Child_id"; }
   static QString column_Name(bool key = false) { Q_UNUSED(key); return "Name"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("Child") : QString("t_Child")); }

};

typedef std::shared_ptr<Child> Child_ptr;
typedef qx::QxCollection<long, Child_ptr> list_of_Child;
typedef std::shared_ptr<list_of_Child> list_of_Child_ptr;

QX_REGISTER_COMPLEX_CLASS_NAME_HPP_CHILDMODELSAVINGBUG(Child, qx::trait::no_base_class_defined, 0, Child)

#include "../include/Grandchild.gen.h"
#include "../include/Parent.gen.h"

#include "../custom/include/Child.h"

#endif // _CHILDMODELSAVINGBUG_CHILD_H_
