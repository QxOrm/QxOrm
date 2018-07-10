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

#include <QxDao/IxDao_Helper.h>

namespace qx {
namespace dao {
namespace detail {

template <class T>
class QxDao_Helper : public IxDao_Helper
{

public:

   QxDao_Helper(T & t, QSqlDatabase * pDatabase, const QString & sContext) : IxDao_Helper() { Q_UNUSED(t); init(pDatabase, sContext); }
   virtual ~QxDao_Helper() { BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<typename qx::QxSqlQueryBuilder<T>::type_sql>::value); }

protected:

   virtual void updateQueryBuilder() { m_pQueryBuilder.reset(new qx::QxSqlQueryBuilder<T>()); }

};

template <class T>
struct QxDao_Keep_Original
{ static inline void backup(T & t) { Q_UNUSED(t); } };

template <typename T>
struct QxDao_Keep_Original< qx::dao::ptr<T> >
{ static inline void backup(qx::dao::ptr<T> & t) { if (t) { t.resetOriginal(qx::clone_to_qt_shared_ptr(* t)); } } };

} // namespace detail
} // namespace dao
} // namespace qx

#include "../../inl/QxDao/QxDao_Helper_Container.inl"
