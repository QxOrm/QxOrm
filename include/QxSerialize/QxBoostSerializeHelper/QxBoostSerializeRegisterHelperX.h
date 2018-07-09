/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#ifndef _QX_BOOST_SERIALIZE_REGISTER_HELPER_X_H_
#define _QX_BOOST_SERIALIZE_REGISTER_HELPER_X_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtCore/qmutex.h>

#include "../../../include/QxCommon/QxConfig.h"

#include "../../../include/QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.h"

#include "../../../include/QxSingleton/QxSingleton.h"

#include "../../../include/QxCollection/QxCollection.h"
#include "../../../include/QxCollection/QxForeach.h"

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

#endif // _QX_BOOST_SERIALIZE_REGISTER_HELPER_X_H_
