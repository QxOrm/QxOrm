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

#ifdef _QX_CPP_11_CONTAINER
#ifndef BOOST_NO_CXX11_STD_UNORDERED
#ifndef _QX_IS_STD_UNORDERED_SET_H_
#define _QX_IS_STD_UNORDERED_SET_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_std_unordered_set.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_std_unordered_set<T>::value : return true if T is a std::unordered_set<> or std::unordered_multiset<> container, otherwise return false
 */

#include <unordered_set>

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_std_unordered_set<T>::value : return true if T is a std::unordered_set<> or std::unordered_multiset<> container, otherwise return false
 */
template <typename T>
struct is_std_unordered_set : public boost::mpl::false_ { ; };

template <typename T>
struct is_std_unordered_set< std::unordered_set<T> > : public boost::mpl::true_ { ; };

template <typename T>
struct is_std_unordered_set< std::unordered_set<T> & > : public boost::mpl::true_ { ; };

template <typename T>
struct is_std_unordered_set< const std::unordered_set<T> > : public boost::mpl::true_ { ; };

template <typename T>
struct is_std_unordered_set< const std::unordered_set<T> & > : public boost::mpl::true_ { ; };

template <typename T>
struct is_std_unordered_set< std::unordered_multiset<T> > : public boost::mpl::true_ { ; };

template <typename T>
struct is_std_unordered_set< std::unordered_multiset<T> & > : public boost::mpl::true_ { ; };

template <typename T>
struct is_std_unordered_set< const std::unordered_multiset<T> > : public boost::mpl::true_ { ; };

template <typename T>
struct is_std_unordered_set< const std::unordered_multiset<T> & > : public boost::mpl::true_ { ; };

} // namespace trait
} // namespace qx

#endif // _QX_IS_STD_UNORDERED_SET_H_
#endif // BOOST_NO_CXX11_STD_UNORDERED
#endif // _QX_CPP_11_CONTAINER
