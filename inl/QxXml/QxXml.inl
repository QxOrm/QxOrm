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
