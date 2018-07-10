/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_PROPERTY_BAG_H_
#define _QX_PROPERTY_BAG_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxPropertyBag.h
 * \author Lionel Marty
 * \ingroup QxCommon
 * \brief Used by introspection engine (IxClass, IxDataMember, IxFunction, etc.) to add meta-data (property bag)
 */

#include <boost/shared_ptr.hpp>

#include <QtCore/qhash.h>
#include <QtCore/qstring.h>
#include <QtCore/qvariant.h>

namespace qx {

/*!
 * \ingroup QxCommon
 * \brief qx::QxPropertyBag : used by introspection engine (IxClass, IxDataMember, IxFunction, etc.) to add meta-data (property bag)
 */
class QxPropertyBag
{

protected:

   typedef QHash<QString, QVariant> type_hash_prop_bag;
   typedef boost::shared_ptr<type_hash_prop_bag> type_hash_prop_bag_ptr;

   type_hash_prop_bag_ptr m_lstPropertyBag;  //!< List of all properties in the bag (meta-data)

public:

   QxPropertyBag() { ; }
   virtual ~QxPropertyBag() { ; }

   void setPropertyBag(const QString & key, const QVariant & value)  { initPropertyBag(); m_lstPropertyBag->insert(key, value); }
   QVariant getPropertyBag(const QString & key) const                { return ((m_lstPropertyBag && m_lstPropertyBag->contains(key)) ? m_lstPropertyBag->value(key) : QVariant()); }
   void removePropertyBag(const QString & key)                       { if (m_lstPropertyBag) { m_lstPropertyBag->remove(key); } }
   void clearPropertyBag()                                           { if (m_lstPropertyBag) { m_lstPropertyBag->clear(); } }
   long countPropertyBag() const                                     { return (m_lstPropertyBag ? m_lstPropertyBag->count() : 0); }
   QList<QString> getAllPropertyBagKeys() const                      { return (m_lstPropertyBag ? m_lstPropertyBag->keys() : QList<QString>()); }

private:

   inline void initPropertyBag()
   { if (! m_lstPropertyBag) { m_lstPropertyBag.reset(new type_hash_prop_bag()); } }

};

} // namespace qx

#endif // _QX_PROPERTY_BAG_H_
