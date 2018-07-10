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

/**
 * @file    debug_new.cpp
 *
 * Implementation of debug versions of new and delete to check leakage.
 *
 * @version 4.14, 2008/10/20
 * @author  Wu Yongwei
 *
 */

#include <QxCommon/QxConfig.h>
#include <QxCommon/QxMacro.h>

#ifndef QT_NO_DEBUG
#ifndef _QX_MODE_RELEASE
#if _QX_USE_MEM_LEAK_DETECTION

#include <new>
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
#include <alloca.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <malloc.h>
#endif

#include <QtCore/qglobal.h>

#include <QxMemLeak/fast_mutex.h>
#include <QxMemLeak/static_assert.h>

#ifndef _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE
#define _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE 0
#endif // _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE

#if !_FAST_MUTEX_CHECK_INITIALIZATION && !defined(_NOTHREADS)
#error "_FAST_MUTEX_CHECK_INITIALIZATION not set: check_leaks may not work"
#endif

/**
 * @def _DEBUG_NEW_ALIGNMENT
 *
 * The alignment requirement of allocated memory blocks.  It must be a
 * power of two.
 */
#ifndef _DEBUG_NEW_ALIGNMENT
#define _DEBUG_NEW_ALIGNMENT 16
#endif

/**
 * @def _DEBUG_NEW_ERROR_ACTION
 *
 * The action to take when an error occurs.  The default behaviour is to
 * call \e abort, unless \c _DEBUG_NEW_ERROR_CRASH is defined, in which
 * case a segmentation fault will be triggered instead (which can be
 * useful on platforms like Windows that do not generate a core dump
 * when \e abort is called).
 */
#ifndef _DEBUG_NEW_ERROR_ACTION
#ifndef _DEBUG_NEW_ERROR_CRASH
#define _DEBUG_NEW_ERROR_ACTION abort()
#else
#define _DEBUG_NEW_ERROR_ACTION do { *((char*)0) = 0; abort(); } while (0)
#endif
#endif

/**
 * @def _DEBUG_NEW_FILENAME_LEN
 *
 * The length of file name stored if greater than zero.  If it is zero,
 * only a const char pointer will be stored.  Currently the default
 * behaviour is to copy the file name, because I found that the exit
 * leakage check cannot access the address of the file name sometimes
 * (in my case, a core dump will occur when trying to access the file
 * name in a shared library after a \c SIGINT).  The current default
 * value makes the size of new_ptr_list_t 64 on 32-bit platforms.
 */
#ifndef _DEBUG_NEW_FILENAME_LEN
#define _DEBUG_NEW_FILENAME_LEN 44
#endif

/**
 * @def _DEBUG_NEW_PROGNAME
 *
 * The program (executable) name to be set at compile time.  It is
 * better to assign the full program path to #new_progname in \e main
 * (at run time) than to use this (compile-time) macro, but this macro
 * serves well as a quick hack.  Note also that double quotation marks
 * need to be used around the program name, i.e., one should specify a
 * command-line option like <code>-D_DEBUG_NEW_PROGNAME=\"a.out\"</code>
 * in \e bash, or <code>-D_DEBUG_NEW_PROGNAME=\"a.exe\"</code> in the
 * Windows command prompt.
 */
#ifndef _DEBUG_NEW_PROGNAME
#define _DEBUG_NEW_PROGNAME NULL
#endif

/**
 * @def _DEBUG_NEW_STD_OPER_NEW
 *
 * Macro to indicate whether the standard-conformant behaviour of
 * <code>operator new</code> is wanted.  It is on by default now, but
 * the user may set it to \c 0 to revert to the old behaviour.
 */
#ifndef _DEBUG_NEW_STD_OPER_NEW
#define _DEBUG_NEW_STD_OPER_NEW 1
#endif

/**
 * @def _DEBUG_NEW_TAILCHECK
 *
 * Macro to indicate whether a writing-past-end check will be performed.
 * Define it to a positive integer as the number of padding bytes at the
 * end of a memory block for checking.
 */
#ifndef _DEBUG_NEW_TAILCHECK
#define _DEBUG_NEW_TAILCHECK 0
#endif

/**
 * @def _DEBUG_NEW_TAILCHECK_CHAR
 *
 * Value of the padding bytes at the end of a memory block.
 */
#ifndef _DEBUG_NEW_TAILCHECK_CHAR
#define _DEBUG_NEW_TAILCHECK_CHAR 0xCC
#endif

/**
 * @def _DEBUG_NEW_USE_ADDR2LINE
 *
 * Whether to use \e addr2line to convert a caller address to file/line
 * information.  Defining it to a non-zero value will enable the
 * conversion (automatically done if GCC is detected).  Defining it to
 * zero will disable the conversion.
 */
#ifndef _DEBUG_NEW_USE_ADDR2LINE
#ifdef __GNUC__
#define _DEBUG_NEW_USE_ADDR2LINE 1
#else
#define _DEBUG_NEW_USE_ADDR2LINE 0
#endif
#endif

#ifdef _MSC_VER
#pragma warning(disable: 4073)  // #pragma init_seg(lib) used
#pragma warning(disable: 4290)  // C++ exception specification ignored
#pragma init_seg(lib)
#endif

#undef  _DEBUG_NEW_EMULATE_MALLOC
#undef  _DEBUG_NEW_REDEFINE_NEW
/**
 * Macro to indicate whether redefinition of \c new is wanted.  Here it
 * is defined to \c 0 to disable the redefinition of \c new.
 */
#define _DEBUG_NEW_REDEFINE_NEW 0
#include <QxMemLeak/debug_new.h>

/**
 * Gets the aligned value of memory block size.
 */
#define align(s) \
        (((s) + _DEBUG_NEW_ALIGNMENT - 1) & ~(_DEBUG_NEW_ALIGNMENT - 1))

namespace qx {
namespace memory {

/**
 * Structure to store the position information where \c new occurs.
 */
struct new_ptr_list_t
{
    new_ptr_list_t*     next;
    new_ptr_list_t*     prev;
    size_t              size;
    union
    {
#if _DEBUG_NEW_FILENAME_LEN == 0
    const char*         file;
#else
    char                file[_DEBUG_NEW_FILENAME_LEN];
#endif
    void*               addr;
    };
    unsigned            line      :31;
    unsigned            is_array  :1;
    unsigned            magic;
};

/**
 * Magic number for error detection.
 */
const unsigned MAGIC = 0x4442474E;

/**
 * The extra memory allocated by <code>operator new</code>.
 */
const int ALIGNED_LIST_ITEM_SIZE = align(sizeof(new_ptr_list_t));

/**
 * List of all new'd pointers.
 */
static new_ptr_list_t new_ptr_list = {
    &new_ptr_list,
    &new_ptr_list,
    0,
    {
#if _DEBUG_NEW_FILENAME_LEN == 0
        NULL
#else
        ""
#endif
    },
    0,
    0,
    MAGIC
};

/**
 * The mutex guard to protect simultaneous access to the pointer list.
 */
static fast_mutex new_ptr_lock;

/**
 * The mutex guard to protect simultaneous output to #new_output_fp.
 */
static fast_mutex new_output_lock;

/**
 * Total memory allocated in bytes.
 */
static size_t total_mem_alloc = 0;

/**
 * Flag to control whether #check_leaks will be automatically called on
 * program exit.
 */
bool new_autocheck_flag = true;

/**
 * Flag to control whether verbose messages are output.
 */
bool new_verbose_flag = false;

/**
 * Pointer to the output stream.  The default output is \e stderr, and
 * one may change it to a user stream if needed (say, #new_verbose_flag
 * is \c true and there are a lot of (de)allocations).
 */
FILE* new_output_fp = stderr;

/**
 * Pointer to the program name.  Its initial value is the macro
 * #_DEBUG_NEW_PROGNAME.  You should try to assign the program path to
 * it early in your application.  Assigning <code>argv[0]</code> to it
 * in \e main is one way.  If you use \e bash or \e ksh (or similar),
 * the following statement is probably what you want:
 * `<code>new_progname = getenv("_");</code>'.
 */
const char* new_progname = _DEBUG_NEW_PROGNAME;

#if _DEBUG_NEW_TAILCHECK
/**
 * Checks whether the padding bytes at the end of a memory block is
 * tampered with.
 *
 * @param ptr   pointer to a new_ptr_list_t struct
 * @return      \c true if the padding bytes are untouched; \c false
 *              otherwise
 */
static bool check_tail(new_ptr_list_t* ptr)
{
    const unsigned char* const pointer = (unsigned char*)ptr +
                            ALIGNED_LIST_ITEM_SIZE + ptr->size;
    for (int i = 0; i < _DEBUG_NEW_TAILCHECK; ++i)
        if (pointer[i] != _DEBUG_NEW_TAILCHECK_CHAR)
            return false;
    return true;
}
#endif

/**
 * Allocates memory and initializes control data.
 *
 * @param size      size of the required memory block
 * @param file      null-terminated string of the file name
 * @param line      line number
 * @param is_array  boolean value whether this is an array operation
 * @return          pointer to the user-requested memory area; \c NULL
 *                  if memory allocation is not successful
 */
static void* alloc_mem(size_t size, const char* file, int line, bool is_array)
{
    assert(line >= 0);
    STATIC_ASSERT((_DEBUG_NEW_ALIGNMENT & (_DEBUG_NEW_ALIGNMENT - 1)) == 0, Alignment_must_be_power_of_two);
    STATIC_ASSERT(_DEBUG_NEW_TAILCHECK >= 0, Invalid_tail_check_length);
    size_t s = size + ALIGNED_LIST_ITEM_SIZE + _DEBUG_NEW_TAILCHECK;
    new_ptr_list_t* ptr = (new_ptr_list_t*)malloc(s);
    if (ptr == NULL)
    {
#if _DEBUG_NEW_STD_OPER_NEW
        return NULL;
#else
        fast_mutex_autolock lock(new_output_lock);
        qDebug("[QxOrm] Out of memory when allocating %u bytes", size);
        fflush(new_output_fp);
        _DEBUG_NEW_ERROR_ACTION;
#endif
    }
    void* pointer = (char*)ptr + ALIGNED_LIST_ITEM_SIZE;
#if _DEBUG_NEW_FILENAME_LEN == 0
    ptr->file = file;
#else
    if (line)
    {
        QX_STRNCPY(ptr->file, file, _DEBUG_NEW_FILENAME_LEN - 1);
        ptr->file[_DEBUG_NEW_FILENAME_LEN - 1] = '\0';
    }
    else
        ptr->addr = (void*)file;
#endif
    ptr->line = line;
    ptr->is_array = is_array;
    ptr->size = size;
    ptr->magic = MAGIC;
    {
        fast_mutex_autolock lock(new_ptr_lock);
        ptr->prev = new_ptr_list.prev;
        ptr->next = &new_ptr_list;
        new_ptr_list.prev->next = ptr;
        new_ptr_list.prev = ptr;
    }
#if _DEBUG_NEW_TAILCHECK
    memset((char*)pointer + size, _DEBUG_NEW_TAILCHECK_CHAR,
                                  _DEBUG_NEW_TAILCHECK);
#endif
    if (new_verbose_flag)
    {
        fast_mutex_autolock lock(new_output_lock);
        const char * msg_out_file = "[QxOrm] new%s: allocated %p (size %u, %s:%d)"; Q_UNUSED(msg_out_file);
        const char * msg_out_no_file = "[QxOrm] new%s: allocated %p (size %u, <Unknown>)"; Q_UNUSED(msg_out_no_file);
        if (line != 0) { qDebug(msg_out_file, (is_array ? "[]" : ""), pointer, size, ptr->file, ptr->line); }
#if (! _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE)
        else { qDebug(msg_out_no_file, (is_array ? "[]" : ""), pointer, size); }
#endif // (! _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE)
    }
    total_mem_alloc += size;
    return pointer;
}

/**
 * Frees memory and adjusts pointers.
 *
 * @param pointer   pointer to delete
 * @param addr      pointer to the caller
 * @param is_array  flag indicating whether it is invoked by a
 *                  <code>delete[]</code> call
 */
void __debug_new_recorder::free_pointer(void* pointer, void* addr, bool is_array)
{
    if (pointer == NULL) { return; }
    new_ptr_list_t* ptr = (new_ptr_list_t*)((char*)pointer - ALIGNED_LIST_ITEM_SIZE);
    if (ptr->magic != MAGIC)
    {
        {
            fast_mutex_autolock lock(new_output_lock);
            const char * msg_out = "[QxOrm] delete%s: invalid pointer %p"; Q_UNUSED(msg_out);
            qDebug(msg_out, (is_array ? "[]" : ""), pointer);
        }
        check_mem_corruption();
        fflush(new_output_fp);
        _DEBUG_NEW_ERROR_ACTION;
    }
    if (is_array != ptr->is_array)
    {
        const char * msg;
        if (is_array) { msg = "[QxOrm] delete[] after new"; }
        else { msg = "[QxOrm] delete after new[]"; }
        fast_mutex_autolock lock(new_output_lock);
        const char * msg_out_file = "[QxOrm] %s: pointer %p (size %u)\n\tat %p\n\toriginally allocated at %s:%d"; Q_UNUSED(msg_out_file);
        const char * msg_out_no_file = "[QxOrm] %s: pointer %p (size %u)\n\tat %p\n\toriginally allocated at <Unknown>"; Q_UNUSED(msg_out_no_file);
        if (ptr->line != 0) { qDebug(msg_out_file, msg, ((char*)ptr + ALIGNED_LIST_ITEM_SIZE), ptr->size, addr, ptr->file, ptr->line); }
#if (! _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE)
        else { qDebug(msg_out_no_file, msg, ((char*)ptr + ALIGNED_LIST_ITEM_SIZE), ptr->size, addr); }
#endif // (! _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE)
        fflush(new_output_fp);
        _DEBUG_NEW_ERROR_ACTION;
    }
#if _DEBUG_NEW_TAILCHECK
    if (!check_tail(ptr))
    {
        check_mem_corruption();
        fflush(new_output_fp);
        _DEBUG_NEW_ERROR_ACTION;
    }
#endif
    {
        fast_mutex_autolock lock(new_ptr_lock);
        total_mem_alloc -= ptr->size;
        ptr->magic = 0;
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
    }
    if (new_verbose_flag)
    {
        fast_mutex_autolock lock(new_output_lock);
        const char * msg_out = "[QxOrm] delete%s: freed %p (size %u, %u bytes still allocated)"; Q_UNUSED(msg_out);
        qDebug(msg_out, (is_array ? "[]" : ""), ((char*)ptr + ALIGNED_LIST_ITEM_SIZE), ptr->size, total_mem_alloc);
    }
    free(ptr);
    return;
}

/**
 * Checks for memory leaks.
 *
 * @return  zero if no leakage is found; the number of leaks otherwise
 */
int check_leaks()
{
    int leak_cnt = 0;
    fast_mutex_autolock lock_ptr(new_ptr_lock);
    fast_mutex_autolock lock_output(new_output_lock);
    new_ptr_list_t* ptr = new_ptr_list.next;
    while (ptr != &new_ptr_list)
    {
        const char* const pointer = (char*)ptr + ALIGNED_LIST_ITEM_SIZE;
        if (ptr->magic != MAGIC)
        {
            const char * msg_out = "[QxOrm] warning: heap data corrupt near %p"; Q_UNUSED(msg_out);
            qDebug(msg_out, pointer);
        }
#if _DEBUG_NEW_TAILCHECK
        if (!check_tail(ptr))
        {
            const char * msg_out = "[QxOrm] warning: overwritten past end of object at %p"; Q_UNUSED(msg_out);
            qDebug(msg_out, pointer);
        }
#endif
        const char * msg_out_file = "[QxOrm] Leaked object at %p (size %u, %s:%d)"; Q_UNUSED(msg_out_file);
        const char * msg_out_no_file = "[QxOrm] Leaked object at %p (size %u, <Unknown>)"; Q_UNUSED(msg_out_no_file);
        if (ptr->line != 0) { qDebug(msg_out_file, pointer, ptr->size, ptr->file, ptr->line); ++leak_cnt; }
#if (! _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE)
        else { qDebug(msg_out_no_file, pointer, ptr->size); ++leak_cnt; }
#endif // (! _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE)
        ptr = ptr->next;
    }
    if (new_verbose_flag || leak_cnt)
    {
        const char * msg_out_leak_cnt = "[QxOrm] **** %d memory leaks found ****"; Q_UNUSED(msg_out_leak_cnt);
        qDebug(msg_out_leak_cnt, leak_cnt);
    }
    return leak_cnt;
}

/**
 * Checks for heap corruption.
 *
 * @return  zero if no problem is found; the number of found memory
 *          corruptions otherwise
 */
int check_mem_corruption()
{
    int corrupt_cnt = 0;
    fast_mutex_autolock lock_ptr(new_ptr_lock);
    fast_mutex_autolock lock_output(new_output_lock);
    const char * msg_out_check_mem_start = "[QxOrm] **** Checking for memory corruption: START ****"; Q_UNUSED(msg_out_check_mem_start);
    qDebug("%s", msg_out_check_mem_start);
    for (new_ptr_list_t* ptr = new_ptr_list.next; ptr != &new_ptr_list; ptr = ptr->next)
    {
        const char* const pointer = (char*)ptr + ALIGNED_LIST_ITEM_SIZE;
        if (ptr->magic == MAGIC
#if _DEBUG_NEW_TAILCHECK
                && check_tail(ptr)
#endif
                )
            continue;
#if _DEBUG_NEW_TAILCHECK
        if (ptr->magic != MAGIC)
        {
#endif
            const char * msg_out_file = "[QxOrm] Heap data corrupt near %p (size %u, %s:%d)"; Q_UNUSED(msg_out_file);
            const char * msg_out_no_file = "[QxOrm] Heap data corrupt near %p (size %u, <Unknown>)"; Q_UNUSED(msg_out_no_file);
            if (ptr->line != 0) { qDebug(msg_out_file, pointer, ptr->size, ptr->file, ptr->line); ++corrupt_cnt; }
#if (! _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE)
            else { qDebug(msg_out_no_file, pointer, ptr->size); ++corrupt_cnt; }
#endif // (! _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE)
#if _DEBUG_NEW_TAILCHECK
        }
        else
        {
            const char * msg_out_file = "[QxOrm] Overwritten past end of object at %p (size %u, %s:%d)"; Q_UNUSED(msg_out_file);
            const char * msg_out_no_file = "[QxOrm] Overwritten past end of object at %p (size %u, <Unknown>)"; Q_UNUSED(msg_out_no_file);
            if (ptr->line != 0) { qDebug(msg_out_file, pointer, ptr->size, ptr->file, ptr->line); ++corrupt_cnt; }
#if (! _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE)
            else { qDebug(msg_out_no_file, pointer, ptr->size); ++corrupt_cnt; }
#endif // (! _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE)
        }
#endif
    }
    const char * msg_out_check_mem_end = "[QxOrm] **** Checking for memory corruption: %d FOUND ****"; Q_UNUSED(msg_out_check_mem_end);
    qDebug(msg_out_check_mem_end, corrupt_cnt);
    return corrupt_cnt;
}

void __debug_new_recorder::_M_process(void* pointer)
{
    if (pointer == NULL) { return; }
    new_ptr_list_t* ptr = (new_ptr_list_t*)((char*)pointer - ALIGNED_LIST_ITEM_SIZE);
    if (ptr->magic != MAGIC || ptr->line != 0)
    {
        fast_mutex_autolock lock(new_output_lock);
        const char * msg_out = "[QxOrm] warning: debug_new used with placement new (%s:%d)"; Q_UNUSED(msg_out);
        qDebug(msg_out, _M_file, _M_line);
        return;
    }
#if _DEBUG_NEW_FILENAME_LEN == 0
    ptr->file = _M_file;
#else
    QX_STRNCPY(ptr->file, _M_file, _DEBUG_NEW_FILENAME_LEN - 1);
    ptr->file[_DEBUG_NEW_FILENAME_LEN - 1] = '\0';
#endif
    ptr->line = _M_line;
}

int __debug_new_counter::_S_count = 0;
__debug_new_counter::__debug_new_counter() { ++_S_count; }
__debug_new_counter::~__debug_new_counter() { if ((--_S_count == 0) && new_autocheck_flag) { check_leaks(); } }

} // namespace memory
} // namespace qx

void* operator new(size_t size, const char* file, int line)
{
    void* ptr = qx::memory::alloc_mem(size, file, line, false);
#if _DEBUG_NEW_STD_OPER_NEW
    if (ptr) { return ptr; }
    else { throw std::bad_alloc(); }
#else
    return ptr;
#endif
}

void* operator new[](size_t size, const char* file, int line)
{
    void* ptr = qx::memory::alloc_mem(size, file, line, true);
#if _DEBUG_NEW_STD_OPER_NEW
    if (ptr) { return ptr; }
    else { throw std::bad_alloc(); }
#else
    return ptr;
#endif
}

#if HAVE_PLACEMENT_DELETE
void operator delete(void* pointer, const char* file, int line) throw()
{
    if (qx::memory::new_verbose_flag)
    {
        qx::memory::fast_mutex_autolock lock(qx::memory::new_output_lock);
        const char * msg_out = "[QxOrm] info: exception thrown on initializing object at %p (%s:%d)"; Q_UNUSED(msg_out);
        qDebug(msg_out, pointer, file, line);
    }
    operator delete(pointer);
}

void operator delete[](void* pointer, const char* file, int line) throw()
{
    if (qx::memory::new_verbose_flag)
    {
        qx::memory::fast_mutex_autolock lock(qx::memory::new_output_lock);
        const char * msg_out = "[QxOrm] info: exception thrown on initializing objects at %p (%s:%d)"; Q_UNUSED(msg_out);
        qDebug(msg_out, pointer, file, line);
    }
    operator delete[](pointer);
}
#endif // HAVE_PLACEMENT_DELETE

#endif // _QX_USE_MEM_LEAK_DETECTION
#endif // _QX_MODE_RELEASE
#endif // QT_NO_DEBUG
