/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxDao_Update_Optimized_Generic
{

   static inline QSqlError update_optimized(const qx::QxSqlQuery & query, qx::dao::ptr<T> & ptr, QSqlDatabase * pDatabase)
   {
      QStringList lstDiff;
      if (ptr.isNull() || ! ptr.isDirty(lstDiff)) { return QSqlError(); }
      return qx::dao::update_by_query(query, (* ptr), pDatabase, lstDiff);
   }

};

template <class T>
struct QxDao_Update_Optimized_Container
{

   static inline QSqlError update_optimized(const qx::QxSqlQuery & query, qx::dao::ptr<T> & ptr, QSqlDatabase * pDatabase)
   {
      if (ptr.isNull() || (qx::trait::generic_container<T>::size(* ptr) <= 0)) { return QSqlError(); }
      if (! ptr.getOriginal() || (qx::trait::generic_container<T>::size(* ptr) != qx::trait::generic_container<T>::size(* ptr.getOriginal())))
      { return qx::dao::update_by_query(query, (* ptr), pDatabase); }

      QStringList lstDiffItem; QSqlError errorItem;
      QSqlDatabase db = (pDatabase ? (* pDatabase) : qx::QxSqlDatabase::getDatabase(errorItem));
      if (errorItem.isValid()) { return errorItem; }
      if (! pDatabase) { db.transaction(); }

      typename T::const_iterator it2 = ptr.getOriginal()->begin();
      for (typename T::const_iterator it1 = ptr->begin(); it1 != ptr->end(); ++it1)
      {
         lstDiffItem.clear();
         qx::dao::detail::is_dirty((* it1), (* it2), lstDiffItem);
         if (lstDiffItem.count() > 0) { errorItem = qx::dao::update_by_query(query, (* it1), (& db), lstDiffItem); }
         if (errorItem.isValid()) { break; }
         else { ++it2; }
      }

      if (! pDatabase && ! errorItem.isValid()) { db.commit(); }
      else if (! pDatabase) { db.rollback(); }
      return errorItem;
   }

};

template <class T>
struct QxDao_Update_Optimized
{

   static inline QSqlError update_optimized(const qx::QxSqlQuery & query, qx::dao::ptr<T> & ptr, QSqlDatabase * pDatabase)
   {
      typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_Update_Optimized_Container<T>, qx::dao::detail::QxDao_Update_Optimized_Generic<T> >::type type_dao_1;

      QSqlError error = type_dao_1::update_optimized(query, ptr, pDatabase);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original< qx::dao::ptr<T> >::backup(ptr); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
