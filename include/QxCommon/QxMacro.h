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

#ifndef _QX_MACRO_H_
#define _QX_MACRO_H_

#ifdef _MSC_VER
#pragma once
#endif

#ifndef qAssert
#define qAssert Q_ASSERT
#endif // qAssert

#ifndef QX_DLL_EXPORT
#ifdef Q_OS_WIN
#define QX_DLL_EXPORT __declspec(dllexport)
#else
#define QX_DLL_EXPORT
#endif
#endif // QX_DLL_EXPORT

#ifndef QX_DLL_IMPORT
#ifdef Q_OS_WIN
#define QX_DLL_IMPORT __declspec(dllimport)
#else
#define QX_DLL_IMPORT
#endif
#endif // QX_DLL_IMPORT

#ifdef Q_OS_WIN
#ifndef _QX_BUILDING_QX_ORM
#ifdef QX_DLL_EXPORT
#undef QX_DLL_EXPORT
#endif
#define QX_DLL_EXPORT QX_DLL_IMPORT
#endif
#endif // Q_OS_WIN

#ifdef _MSC_VER
#define QX_DLL_EXPORT_TEMPLATE_HPP(CL, T) extern template CL __declspec(dllimport) T;
#define QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(CL, T, P1) extern template CL __declspec(dllimport) T< P1 >;
#define QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(CL, T, U, P1) extern template CL __declspec(dllimport) T< U< P1 > >;
#define QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(CL, T, P1, P2) extern template CL __declspec(dllimport) T< P1, P2 >;
#define QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(CL, T, U, P1, P2) extern template CL __declspec(dllimport) T< U< P1, P2 > >;
// ---
#define QX_DLL_EXPORT_TEMPLATE_CPP(CL, T) template CL __declspec(dllexport) T;
#define QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(CL, T, P1) template CL __declspec(dllexport) T< P1 >;
#define QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(CL, T, U, P1) template CL __declspec(dllexport) T< U< P1 > >;
#define QX_DLL_EXPORT_TEMPLATE_T_P1_P2_CPP(CL, T, P1, P2) template CL __declspec(dllexport) T< P1, P2 >;
#define QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_CPP(CL, T, U, P1, P2) template CL __declspec(dllexport) T< U< P1, P2 > >;
#else // _MSC_VER
#define QX_DLL_EXPORT_TEMPLATE_HPP(CL, T) extern template CL T;
#define QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(CL, T, P1) extern template CL T< P1 >;
#define QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(CL, T, U, P1) extern template CL T< U< P1 > >;
#define QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(CL, T, P1, P2) extern template CL T< P1, P2 >;
#define QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(CL, T, U, P1, P2) extern template CL T< U< P1, P2 > >;
// ---
#define QX_DLL_EXPORT_TEMPLATE_CPP(CL, T) template CL T;
#define QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(CL, T, P1) template CL T< P1 >;
#define QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(CL, T, U, P1) template CL T< U< P1 > >;
#define QX_DLL_EXPORT_TEMPLATE_T_P1_P2_CPP(CL, T, P1, P2) template CL T< P1, P2 >;
#define QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_CPP(CL, T, U, P1, P2) template CL T< U< P1, P2 > >;
#endif // _MSC_VER

#define QX_TEMPLATE_T(T) T<>
#define QX_TEMPLATE_T_P1(T, P1) T< P1 >
#define QX_TEMPLATE_T_P1_P2(T, P1, P2) T< P1, P2 >
#define QX_TEMPLATE_T_P1_P2_P3(T, P1, P2, P3) T< P1, P2, P3 >
#define QX_TEMPLATE_T_U_P1(T, U, P1) T< U< P1 > >
#define QX_TEMPLATE_T_U_P1_P2(T, U, P1, P2) T< U< P1, P2 > >
#define QX_TEMPLATE_T_U_P1_P2_P3(T, U, P1, P2, P3) T< U< P1, P2, P3 > >

/* -- Create your macro (in your precompiled header) replacing "QX_ORM" -- */
#ifdef _QX_BUILDING_QX_ORM
#define QX_REGISTER_HPP_QX_ORM QX_REGISTER_HPP_EXPORT_DLL
#define QX_REGISTER_CPP_QX_ORM QX_REGISTER_CPP_EXPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_HPP_QX_ORM QX_REGISTER_COMPLEX_CLASS_NAME_HPP_EXPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_CPP_QX_ORM QX_REGISTER_COMPLEX_CLASS_NAME_CPP_EXPORT_DLL
#else
#define QX_REGISTER_HPP_QX_ORM QX_REGISTER_HPP_IMPORT_DLL
#define QX_REGISTER_CPP_QX_ORM QX_REGISTER_CPP_IMPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_HPP_QX_ORM QX_REGISTER_COMPLEX_CLASS_NAME_HPP_IMPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_CPP_QX_ORM QX_REGISTER_COMPLEX_CLASS_NAME_CPP_IMPORT_DLL
#endif // _QX_BUILDING_QX_ORM

#ifdef __GNUC__
#define QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE inline
#else
#define QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE /* nothing */
#endif // __GNUC__

#ifdef _MSC_VER
#define QX_STRNCPY strncpy_s
#define QX_VSPRINTF vsprintf_s
#else
#define QX_STRNCPY strncpy
#define QX_VSPRINTF vsprintf
#endif // _MSC_VER

#endif // _QX_MACRO_H_
