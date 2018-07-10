// -*- Mode: C++; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*-
// vim:tabstop=4:shiftwidth=4:expandtab:

/*
 * Copyright (C) 2004-2008 Wu Yongwei <adah at users dot sourceforge dot net>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must
 *    not claim that you wrote the original software.  If you use this
 *    software in a product, an acknowledgement in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must
 *    not be misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 *
 * This file is part of Stones of Nvwa:
 *      http://sourceforge.net/projects/nvwa
 *
 */

/*!
 * \file    debug_new.h
 * \ingroup QxMemLeak
 *
 * Header file for checking leaks caused by unmatched new/delete.
 *
 * \version 4.4, 2007/12/31
 * \author  Wu Yongwei
 *
 */

#ifndef QT_NO_DEBUG
#ifndef _QX_MODE_RELEASE
#if _QX_USE_MEM_LEAK_DETECTION

#ifndef _DEBUG_NEW_H
#define _DEBUG_NEW_H

#ifdef _MSC_VER
#pragma once
#endif

#include <new>
#include <stdio.h>

#include <QxCommon/QxMacro.h>

/**
 * @def HAVE_PLACEMENT_DELETE
 *
 * Macro to indicate whether placement delete operators are supported on
 * a certain compiler.  Some compilers, like Borland C++ Compiler 5.5.1
 * and Digital Mars Compiler 8.42, do not support them, and the user
 * must define this macro to \c 0 to make the program compile.  Also
 * note that in that case memory leakage will occur if an exception is
 * thrown in the initialization (constructor) of a dynamically created
 * object.
 */
#ifndef HAVE_PLACEMENT_DELETE
#define HAVE_PLACEMENT_DELETE 1
#endif

/**
 * @def _DEBUG_NEW_REDEFINE_NEW
 *
 * Macro to indicate whether redefinition of \c new is wanted.  If one
 * wants to define one's own <code>operator new</code>, to call
 * <code>operator new</code> directly, or to call placement \c new, it
 * should be defined to \c 0 to alter the default behaviour.  Unless, of
 * course, one is willing to take the trouble to write something like:
 * @code
 * # ifdef new
 * #   define _NEW_REDEFINED
 * #   undef new
 * # endif
 *
 * // Code that uses new is here
 *
 * # ifdef _NEW_REDEFINED
 * #   ifdef DEBUG_NEW
 * #     define new DEBUG_NEW
 * #   endif
 * #   undef _NEW_REDEFINED
 * # endif
 * @endcode
 */
#ifndef _DEBUG_NEW_REDEFINE_NEW
#define _DEBUG_NEW_REDEFINE_NEW 1
#endif

/**
 * @def _DEBUG_NEW_CALLER_ADDRESS
 *
 * The expression to return the caller address. print_position will
 * later on use this address to print the position information of memory
 * operation points.
 */
#ifndef _DEBUG_NEW_CALLER_ADDRESS
#ifdef __GNUC__
#define _DEBUG_NEW_CALLER_ADDRESS __builtin_return_address(0)
#else
#define _DEBUG_NEW_CALLER_ADDRESS NULL
#endif
#endif

/**
 * @def DEBUG_NEW
 *
 * Macro to catch file/line information on allocation.  If
 * #_DEBUG_NEW_REDEFINE_NEW is \c 0, one can use this macro directly;
 * otherwise \c new will be defined to it, and one must use \c new
 * instead.
 */
#define DEBUG_NEW qx::memory::__debug_new_recorder(__FILE__, __LINE__, __FUNCTION__) ->* new

#if _DEBUG_NEW_REDEFINE_NEW
#define new DEBUG_NEW
#endif // _DEBUG_NEW_REDEFINE_NEW

#ifdef _DEBUG_NEW_EMULATE_MALLOC
#include <stdlib.h>
#ifdef new
#define malloc(s) ((void*)(new char[s]))
#else // new
#define malloc(s) ((void*)(DEBUG_NEW char[s]))
#endif // new
#define free(p) delete[] (char*)(p)
#endif // _DEBUG_NEW_EMULATE_MALLOC

QX_DLL_EXPORT void * operator new(size_t size, const char * file, int line);
QX_DLL_EXPORT void * operator new[](size_t size, const char * file, int line);

#if HAVE_PLACEMENT_DELETE
QX_DLL_EXPORT void operator delete(void * pointer, const char * file, int line) throw();
QX_DLL_EXPORT void operator delete[](void * pointer, const char * file, int line) throw();
#endif

#if defined(_MSC_VER) && _MSC_VER < 1300
// MSVC 6 requires the following declarations; or the non-placement
// new[]/delete[] will not compile.
QX_DLL_EXPORT void * operator new[](size_t) throw(std::bad_alloc);
QX_DLL_EXPORT void operator delete[](void *) throw();
#endif

namespace qx {
namespace memory {

/* Prototypes */
QX_DLL_EXPORT int check_leaks();
QX_DLL_EXPORT int check_mem_corruption();

/* Control variables */
extern bool new_autocheck_flag; // default to true: call check_leaks() on exit
extern bool new_verbose_flag;   // default to false: no verbose information
extern FILE* new_output_fp;     // default to stderr: output to console
extern const char* new_progname;// default to NULL; should be assigned argv[0]

/**
 * Recorder class to remember the call context.
 *
 * The idea comes from <a href="http://groups.google.com/group/comp.lang.c++.moderated/browse_thread/thread/7089382e3bc1c489/85f9107a1dc79ee9?#85f9107a1dc79ee9">Greg Herlihy's post</a> in comp.lang.c++.moderated.
 */
class QX_DLL_EXPORT __debug_new_recorder
{
    const char* _M_file;
    const int   _M_line;
    const char* _M_fct;
    void _M_process(void* pointer);
public:
    /**
     * Constructor to remember the call context.  The information will
     * be used in __debug_new_recorder::operator->*.
     */
    __debug_new_recorder(const char* file, int line, const char* fct)
        : _M_file(file), _M_line(line), _M_fct(fct) {}
    /**
     * Operator to write the context information to memory.
     * <code>operator->*</code> is chosen because it has the right
     * precedence, it is rarely used, and it looks good: so people can
     * tell the special usage more quickly.
     */
    template <class _Tp> _Tp* operator->*(_Tp* pointer) { _M_process(pointer); return pointer; };
    static void free_pointer(void* pointer, void* addr, bool is_array);
private:
    __debug_new_recorder(const __debug_new_recorder&);
    __debug_new_recorder& operator=(const __debug_new_recorder&);
};

/**
 * Counter class for on-exit leakage check.
 *
 * This technique is learnt from <em>The C++ Programming Language</em> by
 * Bjarne Stroustup.
 */
class QX_DLL_EXPORT __debug_new_counter
{
    static int _S_count;
public:
    __debug_new_counter();
    ~__debug_new_counter();
};

/** Counting object for each file including debug_new.h. */
static __debug_new_counter __debug_new_count;

} // namespace memory
} // namespace qx

#endif // _DEBUG_NEW_H
#endif // _QX_USE_MEM_LEAK_DETECTION
#endif // _QX_MODE_RELEASE
#endif // QT_NO_DEBUG
