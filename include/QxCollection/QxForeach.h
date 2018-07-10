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

#ifdef _QX_ENABLE_BOOST
#ifndef _QX_FOREACH_H_
#define _QX_FOREACH_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxForeach.h
 * \author Lionel Marty
 * \ingroup QxCollection
 * \brief foreach-style (based on BOOST_FOREACH macro) to iterate over all stl, boost and Qt containers + qx::QxCollection<Key, Value> QxOrm library container
 *
 * Quick sample using QX_FOREACH (or _foreach) macro :
 * \code
// iterate over drugs container using QxOrm '_foreach' keyword
_foreach(drug_ptr p, lstDrugs)
{ qDebug() << qPrintable(p->name) << " " << qPrintable(p->desc); }
 * \endcode
 *
 * \note QxOrm library provides also other macros to iterator over all containers : _foreach_reverse, _foreach_if, _foreach_reverse_if
 */

#include <boost/foreach.hpp>

#ifndef BOOST_FOREACH_ID
#define BOOST_FOREACH_ID(x) x
#endif

#include <QxTraits/is_qx_collection.h>

namespace qx {

namespace foreach {

template<typename T, typename C, bool is_qx_collection = false>
struct qx_deref_boost_or_qx
{
   typedef typename boost::foreach_detail_::foreach_reference<T, C>::type type;
};

template<typename T, typename C>
struct qx_deref_boost_or_qx<T, C, true>
{
   typedef typename T::type_pair_key_value::second_type type;
};

template<typename T, typename C, bool is_qx_collection = false>
struct qx_deref_deduce
{
   static inline typename qx::foreach::qx_deref_boost_or_qx<T, C, false>::type
   deref(boost::foreach_detail_::auto_any_t cur, boost::foreach_detail_::type2type<T, C> * ptmp)
   { return boost::foreach_detail_::deref(cur, ptmp); }

   static inline typename qx::foreach::qx_deref_boost_or_qx<T, C, false>::type
   rderef(boost::foreach_detail_::auto_any_t cur, boost::foreach_detail_::type2type<T, C> * ptmp)
   { return boost::foreach_detail_::rderef(cur, ptmp); }
};

template<typename T, typename C>
struct qx_deref_deduce<T, C, true>
{
   static inline typename qx::foreach::qx_deref_boost_or_qx<T, C, true>::type
   deref(boost::foreach_detail_::auto_any_t cur, boost::foreach_detail_::type2type<T, C> * ptmp)
   { return boost::foreach_detail_::deref(cur, ptmp).second; }

   static inline typename qx::foreach::qx_deref_boost_or_qx<T, C, true>::type
   rderef(boost::foreach_detail_::auto_any_t cur, boost::foreach_detail_::type2type<T, C> * ptmp)
   { return boost::foreach_detail_::rderef(cur, ptmp).second; }
};

struct qx_deref
{
   template<typename T, typename C>
   static inline typename qx::foreach::qx_deref_boost_or_qx<T, C, qx::trait::is_qx_collection<T>::value>::type
   deref(boost::foreach_detail_::auto_any_t cur, boost::foreach_detail_::type2type<T, C> * ptmp)
   { return qx::foreach::qx_deref_deduce<T, C, qx::trait::is_qx_collection<T>::value>::deref(cur, ptmp); }

   template<typename T, typename C>
   static inline typename qx::foreach::qx_deref_boost_or_qx<T, C, qx::trait::is_qx_collection<T>::value>::type
   deref_reverse(boost::foreach_detail_::auto_any_t cur, boost::foreach_detail_::type2type<T, C> * ptmp)
   { return qx::foreach::qx_deref_deduce<T, C, qx::trait::is_qx_collection<T>::value>::rderef(cur, ptmp); }
};

} // namespace foreach

} // namespace qx

#define QX_FOREACH_DEREF(COL) \
   qx::foreach::qx_deref::deref(BOOST_FOREACH_ID(_foreach_cur), BOOST_FOREACH_TYPEOF(COL))

#define QX_FOREACH_DEREF_REVERSE(COL) \
   qx::foreach::qx_deref::deref_reverse(BOOST_FOREACH_ID(_foreach_cur), BOOST_FOREACH_TYPEOF(COL))

#define QX_FOREACH(VAR, COL)                                                                    \
   BOOST_FOREACH_PREAMBLE()                                                                     \
   if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_col) = BOOST_FOREACH_CONTAIN(COL)) {} else    \
   if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_cur) = BOOST_FOREACH_BEGIN(COL)) {} else      \
   if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_end) = BOOST_FOREACH_END(COL)) {} else        \
   for (bool BOOST_FOREACH_ID(_foreach_continue) = true;                                                          \
         BOOST_FOREACH_ID(_foreach_continue) && !BOOST_FOREACH_DONE(COL);                                         \
         BOOST_FOREACH_ID(_foreach_continue) ? BOOST_FOREACH_NEXT(COL) : (void)0)                                 \
      if  (boost::foreach_detail_::set_false(BOOST_FOREACH_ID(_foreach_continue))) {} else                        \
      for (VAR = QX_FOREACH_DEREF(COL); !BOOST_FOREACH_ID(_foreach_continue); BOOST_FOREACH_ID(_foreach_continue) = true)

#define QX_FOREACH_REVERSE(VAR, COL)                                                            \
   BOOST_FOREACH_PREAMBLE()                                                                     \
   if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_col) = BOOST_FOREACH_CONTAIN(COL)) {} else    \
   if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_cur) = BOOST_FOREACH_RBEGIN(COL)) {} else     \
   if (boost::foreach_detail_::auto_any_t BOOST_FOREACH_ID(_foreach_end) = BOOST_FOREACH_REND(COL)) {} else       \
   for (bool BOOST_FOREACH_ID(_foreach_continue) = true;                                                          \
         BOOST_FOREACH_ID(_foreach_continue) && !BOOST_FOREACH_RDONE(COL);                                        \
         BOOST_FOREACH_ID(_foreach_continue) ? BOOST_FOREACH_RNEXT(COL) : (void)0)                                \
      if  (boost::foreach_detail_::set_false(BOOST_FOREACH_ID(_foreach_continue))) {} else                        \
      for (VAR = QX_FOREACH_DEREF_REVERSE(COL); !BOOST_FOREACH_ID(_foreach_continue); BOOST_FOREACH_ID(_foreach_continue) = true)

#ifdef _foreach
#undef _foreach
#endif // _foreach

#ifdef _foreach_reverse
#undef _foreach_reverse
#endif // _foreach_reverse

#ifdef _foreach_if
#undef _foreach_if
#endif // _foreach_if

#ifdef _foreach_reverse_if
#undef _foreach_reverse_if
#endif // _foreach_reverse_if

#define _foreach QX_FOREACH
#define _foreach_reverse QX_FOREACH_REVERSE

#define _foreach_if(VAR, COL, COND) _foreach(VAR, COL) if (COND)
#define _foreach_reverse_if(VAR, COL, COND) _foreach_reverse(VAR, COL) if (COND)

#endif // _QX_FOREACH_H_
#endif // _QX_ENABLE_BOOST
