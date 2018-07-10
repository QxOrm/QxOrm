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
 * \file    mem_pool_base.h
 * \ingroup QxMemLeak
 *
 * Header file for the memory pool base.
 *
 * \version 1.1, 2004/07/26
 * \author  Wu Yongwei
 *
 */

#ifndef QT_NO_DEBUG
#ifndef _QX_MODE_RELEASE
#if _QX_USE_MEM_LEAK_DETECTION

#ifndef _MEM_POOL_BASE_H
#define _MEM_POOL_BASE_H

#ifdef _MSC_VER
#pragma once
#endif

#include <stddef.h>

namespace qx {
namespace memory {

/**
 * Base class for memory pools.
 */
class QX_DLL_EXPORT mem_pool_base
{
public:
    virtual ~mem_pool_base();
    virtual void recycle() = 0;
    static void* alloc_sys(size_t __size);
    static void dealloc_sys(void* __ptr);

    /** Structure to store the next available memory block. */
    struct _Block_list { _Block_list* _M_next; };
};

} // namespace memory
} // namespace qx

#endif // _MEM_POOL_BASE_H
#endif // _QX_USE_MEM_LEAK_DETECTION
#endif // _QX_MODE_RELEASE
#endif // QT_NO_DEBUG
