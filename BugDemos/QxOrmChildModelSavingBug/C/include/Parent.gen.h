/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 12:31) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CHILDMODELSAVINGBUG_PARENT_H_
#define _CHILDMODELSAVINGBUG_PARENT_H_

class Child;

class CHILDMODELSAVINGBUG_EXPORT Parent
{

   QX_REGISTER_FRIEND_CLASS(Parent)

public:

   typedef qx::QxCollection<long, std::shared_ptr<Child> > type_list_of_Child;

protected:

   long m_Parent_id;
   QString m_Name;
   type_list_of_Child m_list_of_Child;

public:

   Parent();
   Parent(const long & id);
   virtual ~Parent();

   long getParent_id() const;
   QString getName() const;
   type_list_of_Child getlist_of_Child() const;
   type_list_of_Child & list_of_Child();
   const type_list_of_Child & list_of_Child() const;

   void setParent_id(const long & val);
   void setName(const QString & val);
   void setlist_of_Child(const type_list_of_Child & val);

   type_list_of_Child getlist_of_Child(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_list_of_Child & list_of_Child(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);

public:

   static QString relation_list_of_Child(bool key = false) { Q_UNUSED(key); return "list_of_Child"; }

public:

   static QString column_Parent_id(bool key = false) { Q_UNUSED(key); return "Parent_id"; }
   static QString column_Name(bool key = false) { Q_UNUSED(key); return "Name"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("Parent") : QString("t_Parent")); }

};

typedef std::shared_ptr<Parent> Parent_ptr;
typedef qx::QxCollection<long, Parent_ptr> list_of_Parent;
typedef std::shared_ptr<list_of_Parent> list_of_Parent_ptr;

QX_REGISTER_COMPLEX_CLASS_NAME_HPP_CHILDMODELSAVINGBUG(Parent, qx::trait::no_base_class_defined, 0, Parent)

#include "../include/Child.gen.h"

#include "../custom/include/Parent.h"

#endif // _CHILDMODELSAVINGBUG_PARENT_H_
