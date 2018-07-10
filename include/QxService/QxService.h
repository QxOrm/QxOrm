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

#if _QX_ENABLE_QT_NETWORK_DEPENDENCY
#ifndef _QX_SERVICE_H_
#define _QX_SERVICE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxService.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Concrete service class defined with QxService module of QxOrm library
 */

#include <QxRegister/QxClass.h>

#include <QxService/IxService.h>

namespace qx {
namespace service {

/*!
 * \ingroup QxService
 * \brief qx::service::QxService<INPUT, OUTPUT> : concrete service class with INPUT parameters and OUTPUT parameters
 *
 * <a href="http://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
template <class INPUT, class OUTPUT>
class QxService : public IxService
{

protected:

   enum { is_input_parameter = boost::is_base_of<IxParameter, INPUT>::value };
   enum { is_output_parameter = boost::is_base_of<IxParameter, OUTPUT>::value };
   enum { is_input_registered = qx::trait::is_qx_registered<INPUT>::value };
   enum { is_output_registered = qx::trait::is_qx_registered<OUTPUT>::value };
   enum { is_valid_parameter = (is_input_parameter && is_output_parameter && is_input_registered && is_output_registered) };

   typedef boost::shared_ptr<INPUT> INPUT_ptr;
   typedef boost::shared_ptr<OUTPUT> OUTPUT_ptr;

public:

   QxService(const QString & sServiceName) : IxService(sServiceName) { BOOST_STATIC_ASSERT(is_valid_parameter); }
   virtual ~QxService() { ; }

   INPUT_ptr getInputParameter() const    { return boost::static_pointer_cast<INPUT>(m_pInputParameter); }
   OUTPUT_ptr getOutputParameter() const  { return boost::static_pointer_cast<OUTPUT>(m_pOutputParameter); }

   virtual void registerClass() const { qx::QxClass<INPUT>::getSingleton(); qx::QxClass<OUTPUT>::getSingleton(); }

};

} // namespace service
} // namespace qx

#endif // _QX_SERVICE_H_
#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
