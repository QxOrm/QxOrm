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

#ifndef _QX_FUNCTION_MACRO_H_
#define _QX_FUNCTION_MACRO_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/utility/value_init.hpp>

#define QX_FUNCTION_CLASS_FCT(className) \
public: \
type_fct m_fct; \
className(type_fct fct) : IxFunction(), m_fct(fct) { ; }; \
virtual ~className() { ; }; \
virtual qx_bool invoke(const QString & params = QString(), boost::any * ret = NULL) const \
{ return QxInvokerFct<QString, ! boost::is_same<R, void>::value>::invoke(params, ret, this); } \
virtual qx_bool invoke(const type_any_params & params, boost::any * ret = NULL) const \
{ return QxInvokerFct<type_any_params, ! boost::is_same<R, void>::value>::invoke(params, ret, this); } \
virtual qx_bool invoke(void * pOwner, const QString & params = QString(), boost::any * ret = NULL) const \
{ Q_UNUSED(pOwner); Q_UNUSED(params); Q_UNUSED(ret); qAssert(false); return qx_bool(false, 0, QX_FUNCTION_ERR_INVALID_INVOKE_CALL); } \
virtual qx_bool invoke(void * pOwner, const type_any_params & params, boost::any * ret = NULL) const \
{ Q_UNUSED(pOwner); Q_UNUSED(params); Q_UNUSED(ret); qAssert(false); return qx_bool(false, 0, QX_FUNCTION_ERR_INVALID_INVOKE_CALL); } \
virtual qx_bool isValidFct() const \
{ return (m_fct.empty() ? qx_bool(false, 0, QX_FUNCTION_ERR_EMPTY_FCT) : qx_bool(true)); }

#define QX_FUNCTION_CLASS_MEMBER_FCT(className) \
public: \
type_fct m_fct; \
className(type_fct fct) : IxFunction(), m_fct(fct) { ; }; \
virtual ~className() { ; }; \
virtual qx_bool invoke(void * pOwner, const QString & params = QString(), boost::any * ret = NULL) const \
{ return QxInvokerFct<QString, ! boost::is_same<R, void>::value>::invoke(pOwner, params, ret, this); } \
virtual qx_bool invoke(void * pOwner, const type_any_params & params, boost::any * ret = NULL) const \
{ return QxInvokerFct<type_any_params, ! boost::is_same<R, void>::value>::invoke(pOwner, params, ret, this); } \
virtual qx_bool invoke(const QString & params = QString(), boost::any * ret = NULL) const \
{ Q_UNUSED(params); Q_UNUSED(ret); qAssert(false); return qx_bool(false, 0, QX_FUNCTION_ERR_INVALID_INVOKE_CALL); } \
virtual qx_bool invoke(const type_any_params & params, boost::any * ret = NULL) const \
{ Q_UNUSED(params); Q_UNUSED(ret); qAssert(false); return qx_bool(false, 0, QX_FUNCTION_ERR_INVALID_INVOKE_CALL); } \
virtual qx_bool isValidFct() const \
{ return (m_fct.empty() ? qx_bool(false, 0, QX_FUNCTION_ERR_EMPTY_MEMBER_FCT) : qx_bool(true)); }

#define QX_FUNCTION_CATCH_AND_RETURN_INVOKE() \
catch (const std::exception & e) { bValid = qx_bool(false, 0, e.what()); } \
catch (...) { bValid = qx_bool(false, 0, QX_FUNCTION_ERR_UNKNOWN_ERROR); } \
if (! bValid) { qDebug("[QxOrm] %s", qPrintable(bValid.getDesc())); qAssert(false); } \
return bValid;

#define QX_FUNCTION_INVOKE_START_WITH_OWNER() \
if (ret) { (* ret) = boost::any(); } \
qx_bool bValid = pThis->isValid<T, Owner>(pOwner, params, NULL); \
if (! bValid) { qDebug("[QxOrm] %s", qPrintable(bValid.getDesc())); qAssert(false); return bValid; }

#define QX_FUNCTION_INVOKE_START_WITHOUT_OWNER() \
if (ret) { (* ret) = boost::any(); } \
qx_bool bValid = pThis->isValid(params); \
if (! bValid) { qDebug("[QxOrm] %s", qPrintable(bValid.getDesc())); qAssert(false); return bValid; }

#define QX_FUNCTION_FETCH_PARAM(TYPE, VALUE, FCT) \
boost::value_initialized< TYPE > VALUE; \
{ qx_bool bTmp = qx::function::detail::FCT(params, VALUE, pThis); \
if (! bTmp) { qDebug("[QxOrm] %s", qPrintable(bTmp.getDesc())); qAssert(false); return bTmp; } }

#define QX_FUNCTION_GET_PARAM_TYPE_ANY(PARAMCOUNT) \
Q_UNUSED(qx_fct); \
if (params.size() < PARAMCOUNT) { return qx_bool(false, 0, QX_FUNCTION_ERR_NUMBER_PARAMS); } \
qx_bool bValid = true; \
try { p = boost::any_cast<P>(params[PARAMCOUNT - 1]); } \
catch (...) { bValid = qx_bool(false, 0, QString(QX_FUNCTION_ERR_INVALID_PARAM).replace("XXX", QString::number(PARAMCOUNT))); } \
return bValid;

#define QX_FUNCTION_GET_PARAM_TYPE_STRING(PARAMCOUNT) \
if (! qx_fct) { return qx_bool(false, 0, QX_FUNCTION_ERR_UNKNOWN_ERROR); } \
QStringList lst = params.split(qx_fct->getSeparator()); \
if (lst.size() < PARAMCOUNT) { return qx_bool(false, 0, QX_FUNCTION_ERR_NUMBER_PARAMS); } \
qx_bool bValid = true; \
try { p = boost::lexical_cast<P>(lst.at(PARAMCOUNT - 1).toStdString()); } \
catch (...) { bValid = qx_bool(false, 0, QString(QX_FUNCTION_ERR_INVALID_PARAM).replace("XXX", QString::number(PARAMCOUNT))); } \
return bValid;

#define QX_FUNCTION_GET_PARAM_TYPE_STRING_TO_QSTRING(PARAMCOUNT) \
if (! qx_fct) { return qx_bool(false, 0, QX_FUNCTION_ERR_UNKNOWN_ERROR); } \
QStringList lst = params.split(qx_fct->getSeparator()); \
if (lst.size() < PARAMCOUNT) { return qx_bool(false, 0, QX_FUNCTION_ERR_NUMBER_PARAMS); } \
p = lst.at(PARAMCOUNT - 1); \
return true;

#endif // _QX_FUNCTION_MACRO_H_
