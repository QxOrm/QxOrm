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

#ifndef _QX_FUNCTION_5_H_
#define _QX_FUNCTION_5_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxFunction_5.h
 * \author Lionel Marty
 * \ingroup QxFunction
 * \brief Concrete function class registered into QxOrm context with 5 parameters
 */

#include <QxFunction/IxFunction.h>
#include <QxFunction/QxParameters.h>

namespace qx {

/*!
 * \ingroup QxFunction
 * \brief qx::QxFunction_5<Owner, R, P1, P2, P3, P4, P5> : concrete function registered into QxOrm context defined into class Owner, returning an object of type R and with 5 parameters P1, P2, P3, P4, P5
 */
template <class Owner, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
class QxFunction_5 : public IxFunction
{

public:

   typedef std::function<R (Owner *, P1, P2, P3, P4, P5)> type_fct;
   typedef typename qx::trait::remove_attr<P1, false>::type type_P1;
   typedef typename qx::trait::remove_attr<P2, false>::type type_P2;
   typedef typename qx::trait::remove_attr<P3, false>::type type_P3;
   typedef typename qx::trait::remove_attr<P4, false>::type type_P4;
   typedef typename qx::trait::remove_attr<P5, false>::type type_P5;
   QX_FUNCTION_CLASS_MEMBER_FCT(QxFunction_5);

   virtual int getParamCount() const                                    { return 5; }
   virtual qx_bool isValidParams(const QString & params) const          { Q_UNUSED(params); return true; }
   virtual qx_bool isValidParams(const type_any_params & params) const  { Q_UNUSED(params); return true; }

private:

   template <class T, bool bReturnValue /* = false */>
   struct QxInvokerFct
   {
      static inline qx_bool invoke(void * pOwner, const T & params, qx::any * ret, const QxFunction_5 * pThis)
      {
         QX_FUNCTION_INVOKE_START_WITH_OWNER();
         QX_FUNCTION_FETCH_PARAM(type_P1, p1, get_param_1);
         QX_FUNCTION_FETCH_PARAM(type_P2, p2, get_param_2);
         QX_FUNCTION_FETCH_PARAM(type_P3, p3, get_param_3);
         QX_FUNCTION_FETCH_PARAM(type_P4, p4, get_param_4);
         QX_FUNCTION_FETCH_PARAM(type_P5, p5, get_param_5);
         try { pThis->m_fct(static_cast<Owner *>(pOwner), p1, p2, p3, p4, p5); }
         QX_FUNCTION_CATCH_AND_RETURN_INVOKE();
      }
   };

   template <class T>
   struct QxInvokerFct<T, true>
   {
      static inline qx_bool invoke(void * pOwner, const T & params, qx::any * ret, const QxFunction_5 * pThis)
      {
         QX_FUNCTION_INVOKE_START_WITH_OWNER();
         QX_FUNCTION_FETCH_PARAM(type_P1, p1, get_param_1);
         QX_FUNCTION_FETCH_PARAM(type_P2, p2, get_param_2);
         QX_FUNCTION_FETCH_PARAM(type_P3, p3, get_param_3);
         QX_FUNCTION_FETCH_PARAM(type_P4, p4, get_param_4);
         QX_FUNCTION_FETCH_PARAM(type_P5, p5, get_param_5);
         try { R retTmp = pThis->m_fct(static_cast<Owner *>(pOwner), p1, p2, p3, p4, p5); if (ret) { (* ret) = qx::any(retTmp); } }
         QX_FUNCTION_CATCH_AND_RETURN_INVOKE();
      }
   };

};

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
class QxFunction_5<void, R, P1, P2, P3, P4, P5> : public IxFunction
{

public:

   typedef std::function<R (P1, P2, P3, P4, P5)> type_fct;
   typedef typename qx::trait::remove_attr<P1, false>::type type_P1;
   typedef typename qx::trait::remove_attr<P2, false>::type type_P2;
   typedef typename qx::trait::remove_attr<P3, false>::type type_P3;
   typedef typename qx::trait::remove_attr<P4, false>::type type_P4;
   typedef typename qx::trait::remove_attr<P5, false>::type type_P5;
   QX_FUNCTION_CLASS_FCT(QxFunction_5);

   virtual int getParamCount() const                                    { return 5; }
   virtual qx_bool isValidParams(const QString & params) const          { Q_UNUSED(params); return true; }
   virtual qx_bool isValidParams(const type_any_params & params) const  { Q_UNUSED(params); return true; }

private:

   template <class T, bool bReturnValue /* = false */>
   struct QxInvokerFct
   {
      static inline qx_bool invoke(const T & params, qx::any * ret, const QxFunction_5 * pThis)
      {
         QX_FUNCTION_INVOKE_START_WITHOUT_OWNER();
         QX_FUNCTION_FETCH_PARAM(type_P1, p1, get_param_1);
         QX_FUNCTION_FETCH_PARAM(type_P2, p2, get_param_2);
         QX_FUNCTION_FETCH_PARAM(type_P3, p3, get_param_3);
         QX_FUNCTION_FETCH_PARAM(type_P4, p4, get_param_4);
         QX_FUNCTION_FETCH_PARAM(type_P5, p5, get_param_5);
         try { pThis->m_fct(p1, p2, p3, p4, p5); }
         QX_FUNCTION_CATCH_AND_RETURN_INVOKE();
      }
   };

   template <class T>
   struct QxInvokerFct<T, true>
   {
      static inline qx_bool invoke(const T & params, qx::any * ret, const QxFunction_5 * pThis)
      {
         QX_FUNCTION_INVOKE_START_WITHOUT_OWNER();
         QX_FUNCTION_FETCH_PARAM(type_P1, p1, get_param_1);
         QX_FUNCTION_FETCH_PARAM(type_P2, p2, get_param_2);
         QX_FUNCTION_FETCH_PARAM(type_P3, p3, get_param_3);
         QX_FUNCTION_FETCH_PARAM(type_P4, p4, get_param_4);
         QX_FUNCTION_FETCH_PARAM(type_P5, p5, get_param_5);
         try { R retTmp = pThis->m_fct(p1, p2, p3, p4, p5); if (ret) { (* ret) = qx::any(retTmp); } }
         QX_FUNCTION_CATCH_AND_RETURN_INVOKE();
      }
   };

};

namespace function {

template <class Owner, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
IxFunction_ptr bind_fct_5(const typename QxFunction_5<Owner, R, P1, P2, P3, P4, P5>::type_fct & fct)
{
   typedef std::is_same<Owner, void> qx_verify_owner_tmp;
   static_assert(qx_verify_owner_tmp::value, "qx_verify_owner_tmp::value");
   IxFunction_ptr ptr; ptr.reset(new QxFunction_5<void, R, P1, P2, P3, P4, P5>(fct));
   return ptr;
}

template <class Owner, typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
IxFunction_ptr bind_member_fct_5(const typename QxFunction_5<Owner, R, P1, P2, P3, P4, P5>::type_fct & fct)
{
   typedef std::is_same<Owner, void> qx_verify_owner_tmp;
   static_assert(! qx_verify_owner_tmp::value, "! qx_verify_owner_tmp::value");
   IxFunction_ptr ptr; ptr.reset(new QxFunction_5<Owner, R, P1, P2, P3, P4, P5>(fct));
   return ptr;
}

} // namespace function
} // namespace qx

#endif // _QX_FUNCTION_5_H_
