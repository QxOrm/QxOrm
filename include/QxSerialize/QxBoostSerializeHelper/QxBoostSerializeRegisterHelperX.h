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

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#ifndef _QX_BOOST_SERIALIZE_REGISTER_HELPER_X_H_
#define _QX_BOOST_SERIALIZE_REGISTER_HELPER_X_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtCore/qmutex.h>

#include <QxCommon/QxConfig.h>

#include <QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.h>

#include <QxSingleton/QxSingleton.h>

#include <QxCollection/QxCollection.h>
#include <QxCollection/QxForeach.h>

namespace qx {

class QX_DLL_EXPORT QxBoostSerializeRegisterHelperX : public QxSingleton<QxBoostSerializeRegisterHelperX>
{

   friend class QxSingleton<QxBoostSerializeRegisterHelperX>;
   friend class IxBoostSerializeRegisterHelper;

private:

   QxCollection<QString, IxBoostSerializeRegisterHelper *> m_colHelperX;   // Collection of all 'IxBoostSerializeRegisterHelper' pointer
   QMutex m_oMutexHelperX;                                                 // Mutex -> 'QxBoostSerializeRegisterHelperX' is thread-safe

   QxBoostSerializeRegisterHelperX() : QxSingleton<QxBoostSerializeRegisterHelperX>("qx::QxBoostSerializeRegisterHelperX") { ; }
   virtual ~QxBoostSerializeRegisterHelperX() { ; }

public:

   void add(const QString & sKey, IxBoostSerializeRegisterHelper * p);
   void remove(const QString & sKey);

   template <class Archive>
   static inline void helper(Archive & ar)
#if _QX_USE_BOOST_SERIALIZE_REGISTER_HELPER
   { QxBoostSerializeRegisterHelperX::getSingleton()->private_helper(ar); }
#else
   { Q_UNUSED(ar); }
#endif // _QX_USE_BOOST_SERIALIZE_REGISTER_HELPER

   static inline void helper()
#if _QX_USE_BOOST_SERIALIZE_REGISTER_HELPER
   { QxBoostSerializeRegisterHelperX::getSingleton()->private_helper(); }
#else
   { ; }
#endif // _QX_USE_BOOST_SERIALIZE_REGISTER_HELPER

private:

   template <class Archive>
   inline void private_helper(Archive & ar) const
   {
      static bool bDone = false;
      if (bDone) { return; }
      QMutexLocker locker(const_cast<QMutex *>(& m_oMutexHelperX));
      if (bDone) { return; }
      _foreach(IxBoostSerializeRegisterHelper * p, m_colHelperX) { p->helper(ar); }
      bDone = true;
   }

   inline void private_helper() const
   {
      static bool bDone = false;
      if (bDone) { return; }
      QMutexLocker locker(const_cast<QMutex *>(& m_oMutexHelperX));
      if (bDone) { return; }
      _foreach(IxBoostSerializeRegisterHelper * p, m_colHelperX) { p->helper(); }
      bDone = true;
   }

};

} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::QxBoostSerializeRegisterHelperX)

#endif // _QX_BOOST_SERIALIZE_REGISTER_HELPER_X_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
