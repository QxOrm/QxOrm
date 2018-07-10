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

#ifndef _QX_SERIALIZE_CHECK_INSTANCE_H_
#define _QX_SERIALIZE_CHECK_INSTANCE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeCheckInstance.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Check instance during serialization process to avoid infinite loop with circular references (using RAII)
 */

#include <QtCore/qset.h>
#include <QtCore/qpair.h>
#include <QtCore/qthread.h>

namespace qx {
namespace serialization {
namespace helper {

/*!
 * \ingroup QxSerialize
 * \brief qx::serialization::helper::QxSerializeCheckInstance : check instance during serialization process to avoid infinite loop with circular references (using RAII)
 */
class QX_DLL_EXPORT QxSerializeCheckInstance
{

protected:

   static QSet< QPair<Qt::HANDLE, qptrdiff> > m_lstInstanceByThread;    //!< List of all instances currently used by a serialization process

   qptrdiff m_pInstance;      //!< Instance associated to this helper class
   Qt::HANDLE m_lThreadId;    //!< Thread id associated to this helper class

public:

   QxSerializeCheckInstance(const void * pInstance);
   virtual ~QxSerializeCheckInstance();

   static bool contains(const void * pInstance);

};

} // namespace helper
} // namespace serialization
} // namespace qx

#endif // _QX_SERIALIZE_CHECK_INSTANCE_H_
