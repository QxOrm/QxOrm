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

template <class T>
QString QxXml<T>::toXml(T * pOwner)
{
   if (! pOwner) { return ""; }

   QxXmlWriter xmlWriter;
   QxDataMemberX<T>::toXml(pOwner, & xmlWriter);

   return xmlWriter.getXml();
}

template <class T>
bool QxXml<T>::fromXml(T * pOwner, const QString & sXml)
{
   if (! pOwner || sXml.isEmpty()) { return false; }

   QxXmlReader xmlReader(sXml);
   QxDataMemberX<T>::fromXml(pOwner, & xmlReader);

   return true;
}

template <class T>
boost::shared_ptr<QxXmlWriter> QxXml<T>::toXmlWriter(T * pOwner)
{
   if (! pOwner) { return boost::shared_ptr<QxXmlWriter>(); }

   boost::shared_ptr<QxXmlWriter> pXmlWriter;
   pXmlWriter.reset(new QxXmlWriter());
   QxDataMemberX<T>::toXml(pOwner, pXmlWriter.get());

   return pXmlWriter;
}

template <class T>
bool QxXml<T>::fromXmlReader(T * pOwner, QxXmlReader * pXmlReader)
{
   if (! pOwner || ! pXmlReader) { return false; }
   QxDataMemberX<T>::fromXml(pOwner, pXmlReader);

   return true;
}
