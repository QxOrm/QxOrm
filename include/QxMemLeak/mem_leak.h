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

/*** http://wyw.dcweb.cn/leakage.htm ***/

#ifndef QT_NO_DEBUG
#ifndef _QX_MODE_RELEASE
#if _QX_USE_MEM_LEAK_DETECTION

#define _DEBUG_NEW_REDEFINE_NEW 0
#include "debug_new.h"

#ifdef _MSC_VER
#pragma warning(disable: 4290) // C++ exception specification ignored
#endif // _MSC_VER

#ifndef QX_MEM_LEAK_STATIC_OR_INLINE
#ifdef _MSC_VER
#define QX_MEM_LEAK_STATIC_OR_INLINE static
#else
#define QX_MEM_LEAK_STATIC_OR_INLINE inline
#endif // _MSC_VER
#endif // QX_MEM_LEAK_STATIC_OR_INLINE

QX_MEM_LEAK_STATIC_OR_INLINE void * operator new(size_t size) throw(std::bad_alloc)    { return operator new(size, (char *)_DEBUG_NEW_CALLER_ADDRESS, 0); };
QX_MEM_LEAK_STATIC_OR_INLINE void * operator new[](size_t size) throw(std::bad_alloc)  { return operator new[](size, (char *)_DEBUG_NEW_CALLER_ADDRESS, 0); };
QX_MEM_LEAK_STATIC_OR_INLINE void operator delete(void * pointer) throw()              { qx::memory::__debug_new_recorder::free_pointer(pointer, _DEBUG_NEW_CALLER_ADDRESS, false); };
QX_MEM_LEAK_STATIC_OR_INLINE void operator delete[](void * pointer) throw()            { qx::memory::__debug_new_recorder::free_pointer(pointer, _DEBUG_NEW_CALLER_ADDRESS, true); };

#if HAVE_PLACEMENT_DELETE
QX_MEM_LEAK_STATIC_OR_INLINE void operator delete(void * pointer, const std::nothrow_t &) throw()     { operator delete(pointer, (char *)_DEBUG_NEW_CALLER_ADDRESS, 0); };
QX_MEM_LEAK_STATIC_OR_INLINE void operator delete[](void * pointer, const std::nothrow_t &) throw()   { operator delete[](pointer, (char *)_DEBUG_NEW_CALLER_ADDRESS, 0); };
#endif // HAVE_PLACEMENT_DELETE

#ifdef new
#undef new
#endif // new
#define new DEBUG_NEW

#endif // _QX_USE_MEM_LEAK_DETECTION
#endif // _QX_MODE_RELEASE
#endif // QT_NO_DEBUG

#if (! _QX_USE_MEM_LEAK_DETECTION)
#ifndef DEBUG_NEW
#define DEBUG_NEW new
#endif // DEBUG_NEW
#endif // (! _QX_USE_MEM_LEAK_DETECTION)

#ifdef _QX_MODE_RELEASE
#ifndef DEBUG_NEW
#define DEBUG_NEW new
#endif // DEBUG_NEW
#endif // _QX_MODE_RELEASE
