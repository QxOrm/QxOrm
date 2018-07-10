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

namespace qx {

template <class T> T * QxSingleton<T>::m_pSingleton = NULL;
template <class T> QMutex QxSingleton<T>::m_oMutexSingleton;

template <class T>
T * QxSingleton<T>::getSingleton()
{
   if (m_pSingleton)
      return m_pSingleton;

   IxSingleton::initQxSingletonX();
   QMutexLocker locker(QCoreApplication::instance() ? (& m_oMutexSingleton) : NULL);
   if (! m_pSingleton) { m_pSingleton = new T(); }

   return m_pSingleton;
}

template <class T>
void QxSingleton<T>::deleteSingleton()
{
   QMutexLocker locker(QCoreApplication::instance() ? (& m_oMutexSingleton) : NULL);
   if (! m_pSingleton) { return; }

   delete m_pSingleton;
   m_pSingleton = NULL;
}

} // namespace qx
