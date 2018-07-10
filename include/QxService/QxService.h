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

#ifdef _QX_ENABLE_QT_NETWORK
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

   typedef qx_shared_ptr<INPUT> INPUT_ptr;
   typedef qx_shared_ptr<OUTPUT> OUTPUT_ptr;

public:

   QxService(const QString & sServiceName) : IxService(sServiceName) { BOOST_STATIC_ASSERT(is_valid_parameter); }
   virtual ~QxService() { ; }

#if (defined(_QX_CPP_11_SMART_PTR) && !defined(BOOST_NO_CXX11_SMART_PTR))
   INPUT_ptr getInputParameter() const    { return std::static_pointer_cast<INPUT>(m_pInputParameter); }
   OUTPUT_ptr getOutputParameter() const  { return std::static_pointer_cast<OUTPUT>(m_pOutputParameter); }
#else // (defined(_QX_CPP_11_SMART_PTR) && !defined(BOOST_NO_CXX11_SMART_PTR))
   INPUT_ptr getInputParameter() const    { return boost::static_pointer_cast<INPUT>(m_pInputParameter); }
   OUTPUT_ptr getOutputParameter() const  { return boost::static_pointer_cast<OUTPUT>(m_pOutputParameter); }
#endif // (defined(_QX_CPP_11_SMART_PTR) && !defined(BOOST_NO_CXX11_SMART_PTR))

   virtual void registerClass() const { qx::QxClass<INPUT>::getSingleton(); qx::QxClass<OUTPUT>::getSingleton(); }

};

} // namespace service
} // namespace qx

#endif // _QX_SERVICE_H_
#endif // _QX_ENABLE_QT_NETWORK
