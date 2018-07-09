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
