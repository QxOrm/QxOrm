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

template <class T>
template <typename V>
IxDataMember * QxDataMemberX<T>::add(V T::* pData, const QString & sKey, long lVersion, bool bSerialize, bool bDao)
{
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }

   qAssert(lVersion <= getVersion());
   IxDataMember * pNewDataMember = new QxDataMember<V, T>(pData, sKey, lVersion, bSerialize, bDao);
   pNewDataMember->setSqlType(qx::trait::get_sql_type<V>::get());
   pNewDataMember->setNameParent(getName());
   pNewDataMember->setParent(this);
   m_lstDataMember.insert(sKey, pNewDataMember);

   return pNewDataMember;
}

template <class T>
template <typename V>
IxDataMember * QxDataMemberX<T>::add(V T::* pData, const QString & sKey, long lVersion, bool bSerialize)
{ return add(pData, sKey, lVersion, bSerialize, true); }

template <class T>
template <typename V>
IxDataMember * QxDataMemberX<T>::add(V T::* pData, const QString & sKey, long lVersion)
{ return add(pData, sKey, lVersion, true, true); }

template <class T>
template <typename V>
IxDataMember * QxDataMemberX<T>::add(V T::* pData, const QString & sKey)
{ return add(pData, sKey, 0, true, true); }

template <class T>
IxDataMember * QxDataMemberX<T>::id(typename QxDataMemberX<T>::type_primary_key T::* pDataMemberId, const QString & sKey)
{ return id(pDataMemberId, sKey, 0); }

template <class T>
IxDataMember * QxDataMemberX<T>::id(typename QxDataMemberX<T>::type_primary_key T::* pDataMemberId, const QString & sKey, long lVersion)
{
   if (exist_WithDaoStrategy(sKey) || getId_WithDaoStrategy()) { qAssert(false); return getId_WithDaoStrategy(); }

   qAssert(lVersion <= getVersion());
   m_pDataMemberId = new QxDataMember<typename QxDataMemberX<T>::type_primary_key, T>(pDataMemberId, sKey);
   m_pDataMemberId->setSqlType(qx::trait::get_sql_type<typename QxDataMemberX<T>::type_primary_key>::get());
   m_pDataMemberId->setAutoIncrement(boost::is_integral<typename QxDataMemberX<T>::type_primary_key>::value);
   m_pDataMemberId->setNameParent(getName());
   m_pDataMemberId->setIsPrimaryKey(true);
   m_pDataMemberId->setNotNull(true);
   m_pDataMemberId->setVersion(lVersion);
   m_pDataMemberId->setParent(this);
   m_lstDataMember.insert(sKey, m_pDataMemberId);

   return m_pDataMemberId;
}

template <class T>
template <typename V>
IxSqlRelation * QxDataMemberX<T>::relationOneToOne(V T::* pData, const QString & sKey)
{ return this->relationOneToOne(pData, sKey, 0); }

template <class T>
template <typename V>
IxSqlRelation * QxDataMemberX<T>::relationManyToOne(V T::* pData, const QString & sKey)
{ return this->relationManyToOne(pData, sKey, 0); }

template <class T>
template <typename V>
IxSqlRelation * QxDataMemberX<T>::relationOneToMany(V T::* pData, const QString & sKey, const QString & sForeignKey)
{ return this->relationOneToMany(pData, sKey, sForeignKey, 0); }

template <class T>
template <typename V>
IxSqlRelation * QxDataMemberX<T>::relationManyToMany(V T::* pData, const QString & sKey, const QString & sExtraTable, const QString & sForeignKeyOwner, const QString & sForeignKeyDataType)
{ return this->relationManyToMany(pData, sKey, sExtraTable, sForeignKeyOwner, sForeignKeyDataType, 0); }

template <class T>
template <typename V>
IxSqlRelation * QxDataMemberX<T>::relationOneToOne(V T::* pData, const QString & sKey, long lVersion)
{
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }
   IxDataMember * pDataMember = this->add(pData, sKey, lVersion);
   IxSqlRelation * pSqlRelation = new QxSqlRelation_OneToOne<V, T>(pDataMember);
   pDataMember->setSqlRelation(pSqlRelation);

   return pSqlRelation;
}

template <class T>
template <typename V>
IxSqlRelation * QxDataMemberX<T>::relationManyToOne(V T::* pData, const QString & sKey, long lVersion)
{
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }
   IxDataMember * pDataMember = this->add(pData, sKey, lVersion);
   IxSqlRelation * pSqlRelation = new QxSqlRelation_ManyToOne<V, T>(pDataMember);
   pDataMember->setSqlRelation(pSqlRelation);

   return pSqlRelation;
}

template <class T>
template <typename V>
IxSqlRelation * QxDataMemberX<T>::relationOneToMany(V T::* pData, const QString & sKey, const QString & sForeignKey, long lVersion)
{
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }
   IxDataMember * pDataMember = this->add(pData, sKey, lVersion);
   IxSqlRelation * pSqlRelation = new QxSqlRelation_OneToMany<V, T>(pDataMember, sForeignKey);
   pDataMember->setSqlRelation(pSqlRelation);

   return pSqlRelation;
}

template <class T>
template <typename V>
IxSqlRelation * QxDataMemberX<T>::relationManyToMany(V T::* pData, const QString & sKey, const QString & sExtraTable, const QString & sForeignKeyOwner, const QString & sForeignKeyDataType, long lVersion)
{
   if (exist_WithDaoStrategy(sKey)) { qAssert(false); return NULL; }
   IxDataMember * pDataMember = this->add(pData, sKey, lVersion);
   IxSqlRelation * pSqlRelation = new QxSqlRelation_ManyToMany<V, T>(pDataMember, sExtraTable, sForeignKeyOwner, sForeignKeyDataType);
   pDataMember->setSqlRelation(pSqlRelation);

   return pSqlRelation;
}

template <class T>
template <class Archive>
inline void QxDataMemberX<T>::toArchive(const T * pOwner, Archive & ar, const unsigned int file_version) const
{
   Q_UNUSED(file_version);
   _foreach_if(IxDataMember * pDataMember, m_lstDataMember, (pDataMember->getSerialize()))
      pDataMember->toArchive(pOwner, ar);
}

template <class T>
template <class Archive>
inline void QxDataMemberX<T>::fromArchive(T * pOwner, Archive & ar, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   _foreach_if(IxDataMember * pDataMember, m_lstDataMember, (pDataMember->getSerialize() && (pDataMember->getVersion() <= static_cast<long>(file_version))))
      pDataMember->fromArchive(pOwner, ar);
}

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
QxDataMemberX<qx::trait::no_base_class_defined>::QxDataMemberX() : IxDataMemberX(), QxSingleton< QxDataMemberX<qx::trait::no_base_class_defined> >("qx::QxDataMemberX_no_base_class_defined"), m_pDataMemberId(NULL) { ; }

template <> QX_GCC_WORKAROUND_TEMPLATE_SPEC_INLINE
QxDataMemberX<QObject>::QxDataMemberX() : IxDataMemberX(), QxSingleton< QxDataMemberX<QObject> >("qx::QxDataMemberX_QObject"), m_pDataMemberId(NULL) { ; }

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
