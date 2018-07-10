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

#include <QxRegister/QxVersion.h>

namespace qx {

template <class T>
void QxClass<T>::init()
{
   this->setDataMemberX(QxDataMemberX<T>::getSingleton());
   this->getDataMemberX()->setClass(this);
   this->setFctMemberX(new IxFunctionX());
   this->setFctStaticX(new IxFunctionX());

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
   this->setVersion(boost::serialization::version<T>::value);
#else // _QX_ENABLE_BOOST_SERIALIZATION
   this->setVersion(qx::version<T>::value);
#endif // _QX_ENABLE_BOOST_SERIALIZATION

   this->setKey(qx::trait::get_class_name<T>::get());
   this->setDaoStrategy(QxClass<typename QxClass<T>::type_base_class>::getSingleton()->getDaoStrategy());
   this->setName(qx::trait::get_class_name<T>::get_xml_tag());
   this->updateClassX();
   beforeRegisterClass();
}

template <class T>
IxDataMember * QxClass<T>::data(const QString & sKey, long lVersion)
{ return this->dataMemberX()->add(sKey, lVersion); }

template <class T>
template <typename V, typename U>
IxDataMember * QxClass<T>::data(V U::* pData, const QString & sKey, long lVersion /* = 0 */, bool bSerialize /* = true */, bool bDao /* = true */)
{ return this->dataMemberX()->add(pData, sKey, lVersion, bSerialize, bDao); }

template <class T>
IxDataMember * QxClass<T>::id(const QString & sKey, long lVersion)
{ return this->dataMemberX()->id(sKey, lVersion); }

template <class T>
IxDataMember * QxClass<T>::id(typename QxClass<T>::type_primary_key T::* pDataMemberId, const QString & sKey, long lVersion /* = 0 */)
{ return this->dataMemberX()->id(pDataMemberId, sKey, lVersion); }

template <class T>
template <typename V, typename U>
IxSqlRelation * QxClass<T>::relationOneToOne(V U::* pData, const QString & sKey, long lVersion /* = 0 */)
{ return this->dataMemberX()->relationOneToOne(pData, sKey, lVersion); }

template <class T>
template <typename V, typename U>
IxSqlRelation * QxClass<T>::relationManyToOne(V U::* pData, const QString & sKey, long lVersion /* = 0 */)
{ return this->dataMemberX()->relationManyToOne(pData, sKey, lVersion); }

template <class T>
template <typename V, typename U>
IxSqlRelation * QxClass<T>::relationOneToMany(V U::* pData, const QString & sKey, const QString & sForeignKey, long lVersion /* = 0 */)
{ return this->dataMemberX()->relationOneToMany(pData, sKey, sForeignKey, lVersion); }

template <class T>
template <typename V, typename U>
IxSqlRelation * QxClass<T>::relationManyToMany(V U::* pData, const QString & sKey, const QString & sExtraTable, const QString & sForeignKeyOwner, const QString & sForeignKeyDataType, long lVersion /* = 0 */)
{ return this->dataMemberX()->relationManyToMany(pData, sKey, sExtraTable, sForeignKeyOwner, sForeignKeyDataType, lVersion); }

template <class T>
IxFunction * QxClass<T>::insertFct(IxFunction_ptr pFct, const QString & sKey)
{
   if (! this->getFctMemberX() || sKey.isEmpty() || this->getFctMemberX()->exist(sKey)) { qAssert(false); return NULL; }
   bool bInsertOk = this->getFctMemberX()->insert(sKey, pFct);
   if (bInsertOk) { pFct->setKey(sKey); }
   return (bInsertOk ? pFct.get() : NULL);
}

template <class T>
IxFunction * QxClass<T>::insertFctStatic(IxFunction_ptr pFct, const QString & sKey)
{
   if (! this->getFctStaticX() || sKey.isEmpty() || this->getFctStaticX()->exist(sKey)) { qAssert(false); return NULL; }
   bool bInsertOk = this->getFctStaticX()->insert(sKey, pFct);
   if (bInsertOk) { pFct->setKey(sKey); }
   return (bInsertOk ? pFct.get() : NULL);
}

template <class T>
template <typename R>
IxFunction * QxClass<T>::fct_0(const typename QxFunction_0<T, R>::type_fct & fct, const QString & sKey)
{ return this->insertFct(qx::function::bind_member_fct_0<T, R>(fct), sKey); }

template <class T>
template <typename R, typename P1>
IxFunction * QxClass<T>::fct_1(const typename QxFunction_1<T, R, P1>::type_fct & fct, const QString & sKey)
{ return this->insertFct(qx::function::bind_member_fct_1<T, R, P1>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2>
IxFunction * QxClass<T>::fct_2(const typename QxFunction_2<T, R, P1, P2>::type_fct & fct, const QString & sKey)
{ return this->insertFct(qx::function::bind_member_fct_2<T, R, P1, P2>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3>
IxFunction * QxClass<T>::fct_3(const typename QxFunction_3<T, R, P1, P2, P3>::type_fct & fct, const QString & sKey)
{ return this->insertFct(qx::function::bind_member_fct_3<T, R, P1, P2, P3>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4>
IxFunction * QxClass<T>::fct_4(const typename QxFunction_4<T, R, P1, P2, P3, P4>::type_fct & fct, const QString & sKey)
{ return this->insertFct(qx::function::bind_member_fct_4<T, R, P1, P2, P3, P4>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
IxFunction * QxClass<T>::fct_5(const typename QxFunction_5<T, R, P1, P2, P3, P4, P5>::type_fct & fct, const QString & sKey)
{ return this->insertFct(qx::function::bind_member_fct_5<T, R, P1, P2, P3, P4, P5>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
IxFunction * QxClass<T>::fct_6(const typename QxFunction_6<T, R, P1, P2, P3, P4, P5, P6>::type_fct & fct, const QString & sKey)
{ return this->insertFct(qx::function::bind_member_fct_6<T, R, P1, P2, P3, P4, P5, P6>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
IxFunction * QxClass<T>::fct_7(const typename QxFunction_7<T, R, P1, P2, P3, P4, P5, P6, P7>::type_fct & fct, const QString & sKey)
{ return this->insertFct(qx::function::bind_member_fct_7<T, R, P1, P2, P3, P4, P5, P6, P7>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
IxFunction * QxClass<T>::fct_8(const typename QxFunction_8<T, R, P1, P2, P3, P4, P5, P6, P7, P8>::type_fct & fct, const QString & sKey)
{ return this->insertFct(qx::function::bind_member_fct_8<T, R, P1, P2, P3, P4, P5, P6, P7, P8>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
IxFunction * QxClass<T>::fct_9(const typename QxFunction_9<T, R, P1, P2, P3, P4, P5, P6, P7, P8, P9>::type_fct & fct, const QString & sKey)
{ return this->insertFct(qx::function::bind_member_fct_9<T, R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(fct), sKey); }

template <class T>
template <typename R>
IxFunction * QxClass<T>::fctStatic_0(const typename QxFunction_0<void, R>::type_fct & fct, const QString & sKey)
{ return this->insertFctStatic(qx::function::bind_fct_0<void, R>(fct), sKey); }

template <class T>
template <typename R, typename P1>
IxFunction * QxClass<T>::fctStatic_1(const typename QxFunction_1<void, R, P1>::type_fct & fct, const QString & sKey)
{ return this->insertFctStatic(qx::function::bind_fct_1<void, R, P1>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2>
IxFunction * QxClass<T>::fctStatic_2(const typename QxFunction_2<void, R, P1, P2>::type_fct & fct, const QString & sKey)
{ return this->insertFctStatic(qx::function::bind_fct_2<void, R, P1, P2>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3>
IxFunction * QxClass<T>::fctStatic_3(const typename QxFunction_3<void, R, P1, P2, P3>::type_fct & fct, const QString & sKey)
{ return this->insertFctStatic(qx::function::bind_fct_3<void, R, P1, P2, P3>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4>
IxFunction * QxClass<T>::fctStatic_4(const typename QxFunction_4<void, R, P1, P2, P3, P4>::type_fct & fct, const QString & sKey)
{ return this->insertFctStatic(qx::function::bind_fct_4<void, R, P1, P2, P3, P4>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5>
IxFunction * QxClass<T>::fctStatic_5(const typename QxFunction_5<void, R, P1, P2, P3, P4, P5>::type_fct & fct, const QString & sKey)
{ return this->insertFctStatic(qx::function::bind_fct_5<void, R, P1, P2, P3, P4, P5>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
IxFunction * QxClass<T>::fctStatic_6(const typename QxFunction_6<void, R, P1, P2, P3, P4, P5, P6>::type_fct & fct, const QString & sKey)
{ return this->insertFctStatic(qx::function::bind_fct_6<void, R, P1, P2, P3, P4, P5, P6>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
IxFunction * QxClass<T>::fctStatic_7(const typename QxFunction_7<void, R, P1, P2, P3, P4, P5, P6, P7>::type_fct & fct, const QString & sKey)
{ return this->insertFctStatic(qx::function::bind_fct_7<void, R, P1, P2, P3, P4, P5, P6, P7>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
IxFunction * QxClass<T>::fctStatic_8(const typename QxFunction_8<void, R, P1, P2, P3, P4, P5, P6, P7, P8>::type_fct & fct, const QString & sKey)
{ return this->insertFctStatic(qx::function::bind_fct_8<void, R, P1, P2, P3, P4, P5, P6, P7, P8>(fct), sKey); }

template <class T>
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
IxFunction * QxClass<T>::fctStatic_9(const typename QxFunction_9<void, R, P1, P2, P3, P4, P5, P6, P7, P8, P9>::type_fct & fct, const QString & sKey)
{ return this->insertFctStatic(qx::function::bind_fct_9<void, R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(fct), sKey); }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
QxClass<qx::trait::no_base_class_defined>::QxClass() : IxClass(), QxSingleton< QxClass<qx::trait::no_base_class_defined> >("qx::QxClass_no_base_class_defined") { setName("qx::trait::no_base_class_defined"); setFinalClass(true); }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
QxClass<QObject>::QxClass() : IxClass(), QxSingleton< QxClass<QObject> >("qx::QxClass_QObject") { setKey("QObject"); setName("QObject"); setFinalClass(true); }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
void QxClass<qx::trait::no_base_class_defined>::registerClass() { ; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
void QxClass<QObject>::registerClass() { ; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
void QxClass<qx::trait::no_base_class_defined>::beforeRegisterClass() { ; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
void QxClass<QObject>::beforeRegisterClass() { ; }

} // namespace qx
