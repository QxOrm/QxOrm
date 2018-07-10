#ifndef _QX_BLOG_PRECOMPILED_HEADER_H_
#define _QX_BLOG_PRECOMPILED_HEADER_H_

#include <QxOrm.h>

#include "export.h"

// To resolve a problem with MSVC++ 2010 and MSVC++ 2012 (and later ?) :
// These compilers provide a tuple header but BOOST_NO_CXX11_HDR_TUPLE macro is defined !
// This is because these compilers doesn't provide variadic templates
#if (defined(_QX_CPP_11_TUPLE) && !defined(BOOST_NO_CXX11_HDR_TUPLE))
#define QX_TUPLE std::tuple
#define QX_TUPLE_GET std::get
#else // (defined(_QX_CPP_11_TUPLE) && !defined(BOOST_NO_CXX11_HDR_TUPLE))
#define QX_TUPLE boost::tuple
#define QX_TUPLE_GET boost::tuples::get
#endif // (defined(_QX_CPP_11_TUPLE) && !defined(BOOST_NO_CXX11_HDR_TUPLE))

#endif // _QX_BLOG_PRECOMPILED_HEADER_H_
