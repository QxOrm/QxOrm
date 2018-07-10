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

#ifndef _QX_XML_H_
#define _QX_XML_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../include/QxXml/QxXmlReader.h"
#include "../../include/QxXml/QxXmlWriter.h"

#include "../../include/QxDataMember/QxDataMemberX.h"

namespace qx {

template <class T>
class QxXml
{

private:

   QxXml() { ; }
   virtual ~QxXml() { ; }

public:

   static QString toXml(T * pOwner);
   static bool fromXml(T * pOwner, const QString & sXml);

   static boost::shared_ptr<QxXmlWriter> toXmlWriter(T * pOwner);
   static bool fromXmlReader(T * pOwner, QxXmlReader * pXmlReader);

};

#include "../../inl/QxXml/QxXml.inl"

} // namespace qx

#endif // _QX_XML_H_
