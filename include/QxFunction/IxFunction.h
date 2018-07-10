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

#ifndef _IX_FUNCTION_H_
#define _IX_FUNCTION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxFunction.h
 * \author Lionel Marty
 * \ingroup QxFunction
 * \brief Common interface for all functions registered into QxOrm context (used by introspection engine)
 */

#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <QxCommon/QxBool.h>
#include <QxCommon/QxPropertyBag.h>

#include <QxCollection/QxCollection.h>

#include <QxFunction/QxFunctionError.h>
#include <QxFunction/QxFunctionMacro.h>

#include <QxTraits/remove_attr.h>

namespace qx {

/*!
 * \ingroup QxFunction
 * \brief qx::IxFunction : common interface for all functions registered into QxOrm context (used by introspection engine)
 */
class IxFunction : public qx::QxPropertyBag
{

protected:

   QString m_sKey;         //!< Function key
   QString m_sSeparator;   //!< Separator character(s) for 'QString' parameters type

public:

   typedef std::vector<boost::any> type_any_params;

   IxFunction() : qx::QxPropertyBag(), m_sSeparator("|") { ; }
   virtual ~IxFunction() { ; }

   QString getKey() const                 { return m_sKey; }
   QString getSeparator() const           { return m_sSeparator; }

   void setKey(const QString & s)         { m_sKey = s; }
   void setSeparator(const QString & s)   { m_sSeparator = s; }

   virtual qx_bool invoke(const QString & params = QString(), boost::any * ret = NULL) const = 0;
   virtual qx_bool invoke(const type_any_params & params, boost::any * ret = NULL) const = 0;
   virtual qx_bool invoke(void * pOwner, const QString & params = QString(), boost::any * ret = NULL) const = 0;
   virtual qx_bool invoke(void * pOwner, const type_any_params & params, boost::any * ret = NULL) const = 0;

   virtual qx_bool isValidFct() const = 0;
   virtual qx_bool isValidParams(const QString & params) const = 0;
   virtual qx_bool isValidParams(const type_any_params & params) const = 0;

   template <class T>
   qx_bool isValidOwner(void * pOwner, T * dummy) const
   {
      Q_UNUSED(dummy);
      typedef boost::is_same<T, void> qx_verify_owner_tmp;
      BOOST_STATIC_ASSERT(! qx_verify_owner_tmp::value);
      if (! pOwner) { return qx_bool(false, 0, QX_FUNCTION_ERR_NULL_OWNER); }
      if (! dynamic_cast<T *>(static_cast<T *>(pOwner))) { return qx_bool(false, 0, QX_FUNCTION_ERR_INVALID_OWNER); }
      return true;
   }

   template <class T>
   qx_bool isValid(const T & params) const
   {
      qx_bool bValid = isValidFct(); if (! bValid) { return bValid; };
      bValid = isValidParams(params); if (! bValid) { return bValid; };
      return true;
   }

   template <class T, class U>
   qx_bool isValid(void * pOwner, const T & params, U * dummy) const
   {
      Q_UNUSED(dummy);
      qx_bool bValid = isValidFct(); if (! bValid) { return bValid; };
      bValid = isValidParams(params); if (! bValid) { return bValid; };
      bValid = isValidOwner<U>(pOwner, NULL); if (! bValid) { return bValid; };
      return true;
   }

};

typedef boost::shared_ptr<IxFunction> IxFunction_ptr;
typedef QxCollection<QString, IxFunction_ptr> IxFunctionX;
typedef boost::shared_ptr<IxFunctionX> IxFunctionX_ptr;

} // namespace qx

#endif // _IX_FUNCTION_H_
