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

#include <QxCommon/QxAny.h>
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

   QString m_sKey;            //!< Function key
   QString m_sSeparator;      //!< Separator character(s) for 'QString' parameters type
   QString m_sDescription;    //!< Function description

public:

   typedef std::vector<qx::any> type_any_params;

   IxFunction() : qx::QxPropertyBag(), m_sSeparator("|") { ; }
   virtual ~IxFunction() { ; }

   QString getKey() const                 { return m_sKey; }
   QString getSeparator() const           { return m_sSeparator; }
   QString getDescription() const         { return m_sDescription; }

   void setKey(const QString & s)         { m_sKey = s; }
   void setSeparator(const QString & s)   { m_sSeparator = s; }
   void setDescription(const QString & s) { m_sDescription = s; }

   virtual int getParamCount() const = 0;

   virtual qx_bool invoke(const QString & params = QString(), qx::any * ret = NULL) const = 0;
   virtual qx_bool invoke(const type_any_params & params, qx::any * ret = NULL) const = 0;
   virtual qx_bool invoke(void * pOwner, const QString & params = QString(), qx::any * ret = NULL) const = 0;
   virtual qx_bool invoke(void * pOwner, const type_any_params & params, qx::any * ret = NULL) const = 0;

   virtual qx_bool isValidFct() const = 0;
   virtual qx_bool isValidParams(const QString & params) const = 0;
   virtual qx_bool isValidParams(const type_any_params & params) const = 0;

   template <class T>
   qx_bool isValidOwner(void * pOwner, T * dummy) const
   {
      Q_UNUSED(dummy);
      typedef std::is_same<T, void> qx_verify_owner_tmp;
      static_assert(! qx_verify_owner_tmp::value, "! qx_verify_owner_tmp::value");
      if (! pOwner) { return qx_bool(false, 0, QX_FUNCTION_ERR_NULL_OWNER); }
#ifndef _QX_NO_RTTI
      if (! dynamic_cast<T *>(static_cast<T *>(pOwner))) { return qx_bool(false, 0, QX_FUNCTION_ERR_INVALID_OWNER); }
#endif // _QX_NO_RTTI
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

typedef std::shared_ptr<IxFunction> IxFunction_ptr;
typedef QxCollection<QString, IxFunction_ptr> IxFunctionX;
typedef std::shared_ptr<IxFunctionX> IxFunctionX_ptr;

} // namespace qx

#endif // _IX_FUNCTION_H_
