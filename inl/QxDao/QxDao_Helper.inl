/****************************************************************************
**
** http://www.qxorm.com/
** Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software
**
** Commercial Usage
** Licensees holding valid commercial QxOrm licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Lionel Marty
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met : http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, or
** if you have questions regarding the use of this file, please contact :
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

   QxDao_Helper(T & t, QSqlDatabase * pDatabase, const QString & sContext, qx::IxSqlQueryBuilder * pBuilder) : IxDao_Helper(pBuilder) { Q_UNUSED(t); init(pDatabase, sContext); }
   virtual ~QxDao_Helper() { static_assert(qx::trait::is_qx_registered<typename qx::QxSqlQueryBuilder<T>::type_sql>::value, "qx::trait::is_qx_registered<typename qx::QxSqlQueryBuilder<T>::type_sql>::value"); }

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
