/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#ifndef _IX_FUNCTION_H_
#define _IX_FUNCTION_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include "../../include/QxCommon/QxBool.h"

#include "../../include/QxCollection/QxCollection.h"

#include "../../include/QxFunction/QxFunctionError.h"
#include "../../include/QxFunction/QxFunctionMacro.h"

#include "../../include/QxTraits/remove_attr.h"

namespace qx {

class IxFunction
{

protected:

   QString m_sSeparator;   // Separator character(s) for 'QString' parameters type

public:

   typedef std::vector<boost::any> type_any_params;

   IxFunction() : m_sSeparator("|") { ; }
   virtual ~IxFunction() { ; }

   QString getSeparator() const           { return m_sSeparator; }
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
