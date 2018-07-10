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

namespace qx {

template <class T>
IxDataMember * QxDataMemberX<T>::initId(IxDataMember * pId, long lVersion)
{
   if (! pId) { qAssert(false); return NULL; }
   qAssert(lVersion <= getVersion());
   QString sKey = pId->getKey();

   pId->setSqlType(qx::trait::get_sql_type<typename QxDataMemberX<T>::type_primary_key>::get());
   pId->setAutoIncrement(std::is_integral<typename QxDataMemberX<T>::type_primary_key>::value);
   pId->setNameParent(getName());
   pId->setIsPrimaryKey(true);
   pId->setNotNull(true);
   pId->setVersion(lVersion);
   pId->setParent(this);
   this->setId(pId);
   this->getListDataMemberRef().insert(sKey, pId);

   return pId;
}

template <class T>
IxDataMember * QxDataMemberX<T>::initData(IxDataMember * pData, long lVersion)
{
   if (! pData) { qAssert(false); return NULL; }
   qAssert(lVersion <= getVersion());
   QString sKey = pData->getKey();

   pData->setVersion(lVersion);
   pData->setNameParent(getName());
   pData->setParent(this);
   this->getListDataMemberRef().insert(sKey, pData);

   return pData;
}

template <class T>
template <typename V, typename U>
IxDataMember * QxDataMemberX<T>::add(V U::* pData, const QString & sKey, long lVersion /* = 0 */, bool bSerialize /* = true */, bool bDao /* = true */)
{
   typedef std::is_base_of<U, T> is_valid_class_tmp;
   static_assert(is_valid_class_tmp::value, "is_valid_class_tmp::value");
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }

   IxDataMember * pNewDataMember = new QxDataMember<V, T>(pData, sKey, lVersion, bSerialize, bDao);
   pNewDataMember->setSqlType(qx::trait::get_sql_type<V>::get());
   return this->initData(pNewDataMember, lVersion);
}

template <class T>
IxDataMember * QxDataMemberX<T>::add(const QString & sKey, long lVersion)
{
   if (! qx::trait::qt_meta_object<T>::is_valid) { qDebug("[QxOrm] qx::QxDataMemberX<T>::add() : '%s'", "Qt introspection engine works only with QObject class"); qAssert(false); return NULL; }
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }
   return this->initData(new QxDataMember_QObject(qx::trait::qt_meta_object<T>::get(), sKey), lVersion);
}

template <class T>
IxDataMember * QxDataMemberX<T>::id(typename QxDataMemberX<T>::type_primary_key T::* pDataMemberId, const QString & sKey, long lVersion /* = 0 */)
{
   if (getId_WithDaoStrategy()) { qDebug("[QxOrm] qx::QxDataMemberX<T> id (primary key) already defined '%s'", qPrintable(getId_WithDaoStrategy()->getName())); }
   if (exist_WithDaoStrategy(sKey) || getId_WithDaoStrategy()) { qAssert(false); return getId_WithDaoStrategy(); }
   return this->initId(new QxDataMember<typename QxDataMemberX<T>::type_primary_key, T>(pDataMemberId, sKey), lVersion);
}

template <class T>
IxDataMember * QxDataMemberX<T>::id(const QString & sKey, long lVersion)
{
   if (! qx::trait::qt_meta_object<T>::is_valid) { qDebug("[QxOrm] qx::QxDataMemberX<T>::id() : '%s'", "Qt introspection engine works only with QObject class"); qAssert(false); return NULL; }
   if (getId_WithDaoStrategy()) { qDebug("[QxOrm] qx::QxDataMemberX<T> id (primary key) already defined '%s'", qPrintable(getId_WithDaoStrategy()->getName())); }
   if (exist_WithDaoStrategy(sKey) || getId_WithDaoStrategy()) { qAssert(false); return getId_WithDaoStrategy(); }
   return this->initId(new QxDataMember_QObject(qx::trait::qt_meta_object<T>::get(), sKey), lVersion);
}

template <class T>
template <typename V, typename U>
IxSqlRelation * QxDataMemberX<T>::relationOneToOne(V U::* pData, const QString & sKey, long lVersion /* = 0 */)
{
   typedef std::is_base_of<U, T> is_valid_class_tmp;
   static_assert(is_valid_class_tmp::value, "is_valid_class_tmp::value");
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }

   IxDataMember * pDataMember = this->add(pData, sKey, lVersion);
   IxSqlRelation * pSqlRelation = new QxSqlRelation_OneToOne<V, T>(pDataMember);
   pDataMember->setSqlRelation(pSqlRelation);

   return pSqlRelation;
}

template <class T>
template <typename V, typename U>
IxSqlRelation * QxDataMemberX<T>::relationManyToOne(V U::* pData, const QString & sKey, long lVersion /* = 0 */)
{
   typedef std::is_base_of<U, T> is_valid_class_tmp;
   static_assert(is_valid_class_tmp::value, "is_valid_class_tmp::value");
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }

   IxDataMember * pDataMember = this->add(pData, sKey, lVersion);
   IxSqlRelation * pSqlRelation = new QxSqlRelation_ManyToOne<V, T>(pDataMember);
   pDataMember->setSqlRelation(pSqlRelation);

   return pSqlRelation;
}

template <class T>
template <typename V, typename U>
IxSqlRelation * QxDataMemberX<T>::relationOneToMany(V U::* pData, const QString & sKey, const QString & sForeignKey, long lVersion /* = 0 */)
{
   typedef std::is_base_of<U, T> is_valid_class_tmp;
   static_assert(is_valid_class_tmp::value, "is_valid_class_tmp::value");
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }

   IxDataMember * pDataMember = this->add(pData, sKey, lVersion);
   IxSqlRelation * pSqlRelation = new QxSqlRelation_OneToMany<V, T>(pDataMember, sForeignKey);
   pDataMember->setSqlRelation(pSqlRelation);

   return pSqlRelation;
}

template <class T>
template <typename V, typename U>
IxSqlRelation * QxDataMemberX<T>::relationManyToMany(V U::* pData, const QString & sKey, const QString & sExtraTable, const QString & sForeignKeyOwner, const QString & sForeignKeyDataType, long lVersion /* = 0 */)
{
   typedef std::is_base_of<U, T> is_valid_class_tmp;
   static_assert(is_valid_class_tmp::value, "is_valid_class_tmp::value");
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }

   IxDataMember * pDataMember = this->add(pData, sKey, lVersion);
   IxSqlRelation * pSqlRelation = new QxSqlRelation_ManyToMany<V, T>(pDataMember, sExtraTable, sForeignKeyOwner, sForeignKeyDataType);
   pDataMember->setSqlRelation(pSqlRelation);

   return pSqlRelation;
}

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

template <class T>
template <class Archive>
inline void QxDataMemberX<T>::toArchive(const T * pOwner, Archive & ar, const unsigned int file_version) const
{
   Q_UNUSED(file_version);
   const QxCollection<QString, IxDataMember *> & lstDataMember = this->getListDataMemberRef();
   _foreach_if(IxDataMember * pDataMember, lstDataMember, (pDataMember->getSerialize()))
      pDataMember->toArchive(pOwner, ar);
}

template <class T>
template <class Archive>
inline void QxDataMemberX<T>::fromArchive(T * pOwner, Archive & ar, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QxCollection<QString, IxDataMember *> & lstDataMember = this->getListDataMemberRef();
   _foreach_if(IxDataMember * pDataMember, lstDataMember, (pDataMember->getSerialize() && (pDataMember->getVersion() <= static_cast<long>(file_version))))
      pDataMember->fromArchive(pOwner, ar);
}

#endif // _QX_ENABLE_BOOST_SERIALIZATION

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
QxDataMemberX<qx::trait::no_base_class_defined>::QxDataMemberX() : IxDataMemberX(), QxSingleton< QxDataMemberX<qx::trait::no_base_class_defined> >("qx::QxDataMemberX_no_base_class_defined") { ; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
QxDataMemberX<QObject>::QxDataMemberX() : IxDataMemberX(), QxSingleton< QxDataMemberX<QObject> >("qx::QxDataMemberX_QObject") { ; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
long QxDataMemberX<qx::trait::no_base_class_defined>::count_WithDaoStrategy_Helper() const { return 0; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
bool QxDataMemberX<qx::trait::no_base_class_defined>::exist_WithDaoStrategy_Helper(const QString & sKey) const { Q_UNUSED(sKey); return false; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
IxDataMember * QxDataMemberX<qx::trait::no_base_class_defined>::get_WithDaoStrategy_Helper(long lIndex) const { Q_UNUSED(lIndex); return NULL; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
IxDataMember * QxDataMemberX<qx::trait::no_base_class_defined>::get_WithDaoStrategy_Helper(const QString & sKey) const { Q_UNUSED(sKey); return NULL; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
IxDataMember * QxDataMemberX<qx::trait::no_base_class_defined>::getId_WithDaoStrategy_Helper() const { return NULL; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
long QxDataMemberX<QObject>::count_WithDaoStrategy_Helper() const { return 0; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
bool QxDataMemberX<QObject>::exist_WithDaoStrategy_Helper(const QString & sKey) const { Q_UNUSED(sKey); return false; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
IxDataMember * QxDataMemberX<QObject>::get_WithDaoStrategy_Helper(long lIndex) const { Q_UNUSED(lIndex); return NULL; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
IxDataMember * QxDataMemberX<QObject>::get_WithDaoStrategy_Helper(const QString & sKey) const { Q_UNUSED(sKey); return NULL; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
IxDataMember * QxDataMemberX<QObject>::getId_WithDaoStrategy_Helper() const { return NULL; }

} // namespace qx
