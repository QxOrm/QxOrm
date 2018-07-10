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

#ifndef _QX_BOOL_H_
#define _QX_BOOL_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxBool.h
 * \author Lionel Marty
 * \ingroup QxCommon
 * \brief qx_bool : QxOrm library boolean type with code and description message when an error occured
 */

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

#include <QxSerialize/Qt/QxSerialize_QString.h>

#include <QxTraits/get_class_name.h>

namespace qx {

/*!
 * \ingroup QxCommon
 * \brief qx_bool : boolean type with code and description message when an error occured
 */
class QxBool
{

   friend class boost::serialization::access;

private:

   bool m_bValue;    //!< Data boolean value
   long m_lCode;     //!< Error code when value is false
   QString m_sDesc;  //!< Error description when value is false

public:

   QxBool() : m_bValue(false), m_lCode(0) { ; }
   QxBool(bool b) : m_bValue(b), m_lCode(0) { qAssert(checkInitialized(b)); }
   QxBool(long lCode, const QString & sDesc) : m_bValue(false), m_lCode(lCode), m_sDesc(sDesc) { ; }
   QxBool(bool bValue, long lCode, const QString & sDesc) : m_bValue(bValue), m_lCode(lCode), m_sDesc(sDesc) { qAssert(checkInitialized(bValue)); }
   QxBool(const QxBool & other) : m_bValue(other.getValue()), m_lCode(other.getCode()), m_sDesc(other.getDesc()) { ; }
   ~QxBool() { ; }

   inline bool getValue() const                          { return m_bValue; }
   inline long getCode() const                           { return m_lCode; }
   inline QString getDesc() const                        { return m_sDesc; }

   inline void setValue(bool bValue)                     { m_bValue = bValue; qAssert(checkInitialized(bValue)); }
   inline void setCode(long lCode)                       { m_lCode = lCode; }
   inline void setDesc(const QString & sDesc)            { m_sDesc = sDesc; }

   inline QxBool & operator=(const QxBool & other)       { m_bValue = other.getValue(); m_lCode = other.getCode(); m_sDesc = other.getDesc(); return (* this); }
   inline QxBool & operator=(const bool b)               { m_bValue = b; qAssert(checkInitialized(b)); return (* this); }

   inline operator bool() const                          { return (m_bValue != false); }
   inline bool operator!() const                         { return (m_bValue == false); }

   inline bool operator==(const QxBool & other) const    { return ((m_bValue == other.getValue()) && (m_lCode == other.getCode()) && (m_sDesc == other.getDesc())); }
   inline bool operator==(const bool b) const            { qAssert(checkInitialized(b)); return (m_bValue == b); }
   inline bool operator!=(const QxBool & other) const    { return ((m_bValue != other.getValue()) || (m_lCode != other.getCode()) || (m_sDesc != other.getDesc())); }
   inline bool operator!=(const bool b) const            { qAssert(checkInitialized(b)); return (m_bValue != b); }
   inline bool operator&&(const QxBool & other) const    { return (m_bValue && other.getValue()); }
   inline bool operator&&(const bool b) const            { qAssert(checkInitialized(b)); return (m_bValue && b); }
   inline bool operator||(const QxBool & other) const    { return (m_bValue || other.getValue()); }
   inline bool operator||(const bool b) const            { qAssert(checkInitialized(b)); return (m_bValue || b); }

private:

   template <class Archive>
   void serialize(Archive & ar, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      ar & boost::serialization::make_nvp("value", m_bValue);
      ar & boost::serialization::make_nvp("code", m_lCode);
      ar & boost::serialization::make_nvp("desc", m_sDesc);
   }

   inline bool checkInitialized(const bool b) const { return ((static_cast<int>(b) == 0) || (static_cast<int>(b) == 1)); }

};

} // namespace qx

/*
inline bool operator==(const bool b1, const qx::QxBool & b2) { return (b1 == b2.getValue()); }
inline bool operator!=(const bool b1, const qx::QxBool & b2) { return (b1 != b2.getValue()); }
inline bool operator&&(const bool b1, const qx::QxBool & b2) { return (b1 && b2.getValue()); }
inline bool operator||(const bool b1, const qx::QxBool & b2) { return (b1 || b2.getValue()); }
*/

typedef qx::QxBool qx_bool;
QX_REGISTER_CLASS_NAME(qx_bool)

#endif // _QX_BOOL_H_
