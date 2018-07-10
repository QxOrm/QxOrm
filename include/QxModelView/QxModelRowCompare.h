/****************************************************************************
**
** https://www.qxorm.com/
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

#ifndef _QX_MODEL_ROW_COMPARE_H_
#define _QX_MODEL_ROW_COMPARE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxModelRowCompare.h
 * \author Lionel Marty
 * \ingroup QxModelView
 * \brief Functor used to provide sort feature for all models based on qx::IxModel interface (please note that you can also use QSortFilterProxyModel Qt class to sort your model)
 */

#include <QxDataMember/IxDataMember.h>

namespace qx {
namespace model_view {

QX_DLL_EXPORT bool compareQVariant(const QVariant & v1, const QVariant & v2, bool bAscending) QX_USED;

/*!
 * \ingroup QxModelView
 * \brief qx::QxModelRowCompare : functor used to provide sort feature for all models based on qx::IxModel interface (please note that you can also use QSortFilterProxyModel Qt class to sort your model)
 */
template <typename T>
struct QxModelRowCompare
{

   bool m_bAscendingOrder;             //!< Sort your model using ascending or descending order
   qx::IxDataMember * m_pDataMember;   //!< Data member associated to the model column to sort

   QxModelRowCompare(bool bAscendingOrder, qx::IxDataMember * pDataMember) : m_bAscendingOrder(bAscendingOrder), m_pDataMember(pDataMember) { qAssert(m_pDataMember != NULL); }

   bool operator()(const T & t1, const T & t2) const
   {
      if (! m_pDataMember || ! t1.second || ! t2.second) { return false; }
      QVariant v1 = m_pDataMember->toVariant(& (* t1.second));
      QVariant v2 = m_pDataMember->toVariant(& (* t2.second));
      return qx::model_view::compareQVariant(v1, v2, m_bAscendingOrder);
   }

};

} // namespace model_view
} // namespace qx

#endif // _QX_MODEL_ROW_COMPARE_H_
