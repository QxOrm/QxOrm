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

#ifndef _QX_GET_CLASS_NAME_H_
#define _QX_GET_CLASS_NAME_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file get_class_name.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::get_class_name<T>::get() : return class name of type T under const char * format, T must be registered with QX_REGISTER_CLASS_NAME(T) macro
 */

#ifndef _QX_NO_RTTI
#include <typeinfo>
#endif // _QX_NO_RTTI

#include <QxTraits/remove_attr.h>

#define QX_REGISTER_CLASS_NAME_SEP_INF "<"
#define QX_REGISTER_CLASS_NAME_SEP_SUP ">"
#define QX_REGISTER_CLASS_NAME_SEP_NXT ", "

#define QX_REGISTER_CLASS_NAME_SEP_INF_XML_TAG "-"
#define QX_REGISTER_CLASS_NAME_SEP_SUP_XML_TAG "-"
#define QX_REGISTER_CLASS_NAME_SEP_NXT_XML_TAG "_"

#define QX_GET_CLASS_NAME(TYPE) \
qx::trait::get_class_name< qx::trait::remove_attr< TYPE >::type >::get()

#define QX_GET_CLASS_NAME_STD_STR(TYPE) \
std::string(qx::trait::get_class_name< qx::trait::remove_attr< TYPE >::type >::get())

#define QX_GET_CLASS_NAME_XML_TAG(TYPE) \
qx::trait::get_class_name< qx::trait::remove_attr< TYPE >::type >::get_xml_tag()

#define QX_GET_CLASS_NAME_XML_TAG_STD_STR(TYPE) \
std::string(qx::trait::get_class_name< qx::trait::remove_attr< TYPE >::type >::get_xml_tag())

#define QX_GET_CLASS_NAME_WITH_TYPENAME(TYPE) \
qx::trait::get_class_name< typename qx::trait::remove_attr< TYPE >::type >::get()

#define QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(TYPE) \
std::string(qx::trait::get_class_name< typename qx::trait::remove_attr< TYPE >::type >::get())

#define QX_GET_CLASS_NAME_XML_TAG_WITH_TYPENAME(TYPE) \
qx::trait::get_class_name< typename qx::trait::remove_attr< TYPE >::type >::get_xml_tag()

#define QX_GET_CLASS_NAME_XML_TAG_STD_STR_WITH_TYPENAME(TYPE) \
std::string(qx::trait::get_class_name< typename qx::trait::remove_attr< TYPE >::type >::get_xml_tag())

#define QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG() \
static inline const char * get_xml_tag() \
{ \
   static std::string result_xml; \
   if (! result_xml.empty()) { return result_xml.c_str(); } \
   QString tmp = get_class_name::get(); \
   tmp.replace(QX_REGISTER_CLASS_NAME_SEP_INF, QX_REGISTER_CLASS_NAME_SEP_INF_XML_TAG); \
   tmp.replace(QX_REGISTER_CLASS_NAME_SEP_SUP, QX_REGISTER_CLASS_NAME_SEP_SUP_XML_TAG); \
   tmp.replace(QX_REGISTER_CLASS_NAME_SEP_NXT, QX_REGISTER_CLASS_NAME_SEP_NXT_XML_TAG); \
   tmp.replace("::", "."); \
   tmp.replace(" ", ""); \
   result_xml = tmp.toLatin1().constData(); \
   return result_xml.c_str(); \
}

#ifdef _QX_NO_RTTI
#define QX_REGISTER_CLASS_NAME_NO_RTTI(className) std::string(#className)
#endif // _QX_NO_RTTI

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::get_class_name<T>::get() : return class name of type T under const char * format, T must be registered with QX_REGISTER_CLASS_NAME(T) macro
 */
template <typename T>
struct get_class_name
{

   static inline const char * get()
   {
      static std::string result;
      if (! result.empty()) { return result.c_str(); }

#ifndef _QX_NO_RTTI
      T * dummy = NULL; Q_UNUSED(dummy);
      result = std::string(typeid(dummy).name());
#else // _QX_NO_RTTI
      result = QX_REGISTER_CLASS_NAME_NO_RTTI(T);
#endif // _QX_NO_RTTI

      qDebug("[QxOrm] Unable to define correct class name : '%s' => use macro 'QX_REGISTER_CLASS_NAME()' or 'QX_REGISTER_CLASS_NAME_TEMPLATE_X()'", result.c_str());
      qAssert(false);
      return result.c_str();
   }

   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG();

};

} // namespace trait
} // namespace qx

#define QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className) \
static std::string result; \
if (! result.empty()) { return result.c_str(); } \
result = std::string(#className);

#define QX_REGISTER_CLASS_NAME(className) \
namespace qx { namespace trait { \
template <> \
struct get_class_name< className > \
{ \
   static inline const char * get() \
   { \
      QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className); \
      return result.c_str(); \
   } \
   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG(); \
}; \
} } // namespace qx::trait

#define QX_REGISTER_CLASS_NAME_TEMPLATE_1(className) \
namespace qx { namespace trait { \
template <typename T> \
struct get_class_name< className<T> > \
{ \
   static inline const char * get() \
   { \
      QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className); \
      result += QX_REGISTER_CLASS_NAME_SEP_INF + QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T) + QX_REGISTER_CLASS_NAME_SEP_SUP; \
      return result.c_str(); \
   } \
   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG(); \
}; \
} } // namespace qx::trait

#define QX_REGISTER_CLASS_NAME_TEMPLATE_2(className) \
namespace qx { namespace trait { \
template <typename T1, typename T2> \
struct get_class_name< className<T1, T2> > \
{ \
   static inline const char * get() \
   { \
      QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className); \
      result += QX_REGISTER_CLASS_NAME_SEP_INF + QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T1) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T2) + QX_REGISTER_CLASS_NAME_SEP_SUP; \
      return result.c_str(); \
   } \
   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG(); \
}; \
} } // namespace qx::trait

#define QX_REGISTER_CLASS_NAME_TEMPLATE_3(className) \
namespace qx { namespace trait { \
template <typename T1, typename T2, typename T3> \
struct get_class_name< className<T1, T2, T3> > \
{ \
   static inline const char * get() \
   { \
      QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className); \
      result += QX_REGISTER_CLASS_NAME_SEP_INF + QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T1) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T2) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T3) + QX_REGISTER_CLASS_NAME_SEP_SUP; \
      return result.c_str(); \
   } \
   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG(); \
}; \
} } // namespace qx::trait

#define QX_REGISTER_CLASS_NAME_TEMPLATE_4(className) \
namespace qx { namespace trait { \
template <typename T1, typename T2, typename T3, typename T4> \
struct get_class_name< className<T1, T2, T3, T4> > \
{ \
   static inline const char * get() \
   { \
      QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className); \
      result += QX_REGISTER_CLASS_NAME_SEP_INF + QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T1) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T2) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T3) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T4) + QX_REGISTER_CLASS_NAME_SEP_SUP; \
      return result.c_str(); \
   } \
   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG(); \
}; \
} } // namespace qx::trait

#define QX_REGISTER_CLASS_NAME_TEMPLATE_5(className) \
namespace qx { namespace trait { \
template <typename T1, typename T2, typename T3, typename T4, typename T5> \
struct get_class_name< className<T1, T2, T3, T4, T5> > \
{ \
   static inline const char * get() \
   { \
      QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className); \
      result += QX_REGISTER_CLASS_NAME_SEP_INF + QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T1) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T2) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T3) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T4) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T5) + QX_REGISTER_CLASS_NAME_SEP_SUP; \
      return result.c_str(); \
   } \
   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG(); \
}; \
} } // namespace qx::trait

#define QX_REGISTER_CLASS_NAME_TEMPLATE_6(className) \
namespace qx { namespace trait { \
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> \
struct get_class_name< className<T1, T2, T3, T4, T5, T6> > \
{ \
   static inline const char * get() \
   { \
      QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className); \
      result += QX_REGISTER_CLASS_NAME_SEP_INF + QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T1) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T2) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T3) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T4) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T5) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T6) + QX_REGISTER_CLASS_NAME_SEP_SUP; \
      return result.c_str(); \
   } \
   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG(); \
}; \
} } // namespace qx::trait

#define QX_REGISTER_CLASS_NAME_TEMPLATE_7(className) \
namespace qx { namespace trait { \
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> \
struct get_class_name< className<T1, T2, T3, T4, T5, T6, T7> > \
{ \
   static inline const char * get() \
   { \
      QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className); \
      result += QX_REGISTER_CLASS_NAME_SEP_INF + QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T1) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T2) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T3) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T4) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T5) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T6) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T7) + QX_REGISTER_CLASS_NAME_SEP_SUP; \
      return result.c_str(); \
   } \
   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG(); \
}; \
} } // namespace qx::trait

#define QX_REGISTER_CLASS_NAME_TEMPLATE_8(className) \
namespace qx { namespace trait { \
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> \
struct get_class_name< className<T1, T2, T3, T4, T5, T6, T7, T8> > \
{ \
   static inline const char * get() \
   { \
      QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className); \
      result += QX_REGISTER_CLASS_NAME_SEP_INF + QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T1) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T2) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T3) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T4) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T5) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T6) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T7) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T8) + QX_REGISTER_CLASS_NAME_SEP_SUP; \
      return result.c_str(); \
   } \
   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG(); \
}; \
} } // namespace qx::trait

#define QX_REGISTER_CLASS_NAME_TEMPLATE_9(className) \
namespace qx { namespace trait { \
template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> \
struct get_class_name< className<T1, T2, T3, T4, T5, T6, T7, T8, T9> > \
{ \
   static inline const char * get() \
   { \
      QX_REGISTER_CLASS_NAME_TEMPLATE_INIT(className); \
      result += QX_REGISTER_CLASS_NAME_SEP_INF + QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T1) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T2) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T3) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T4) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T5) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T6) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T7) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T8) + QX_REGISTER_CLASS_NAME_SEP_NXT; \
      result += QX_GET_CLASS_NAME_STD_STR_WITH_TYPENAME(T9) + QX_REGISTER_CLASS_NAME_SEP_SUP; \
      return result.c_str(); \
   } \
   QX_GET_CLASS_NAME_IMPLEMENT_FCT_GET_XML_TAG(); \
}; \
} } // namespace qx::trait

#endif // _QX_GET_CLASS_NAME_H_
