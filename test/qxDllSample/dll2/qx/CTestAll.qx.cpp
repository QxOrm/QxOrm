#include "../include/precompiled.h"

#include "../include/CTestAll.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_DLL2(CTestAll)

namespace qx {
template <> void register_class(QxClass<CTestAll> & t)
{
   IxDataMember * pData = NULL;

   pData = t.id(& CTestAll::m_lId, "m_lId");

   pData = t.data(& CTestAll::m_oQxBool, "m_oQxBool");
   pData = t.data(& CTestAll::m_oStdString, "m_oStdString");
   pData = t.data(& CTestAll::m_oStdPair, "m_oStdPair");
   pData = t.data(& CTestAll::m_oStdVector, "m_oStdVector");
   pData = t.data(& CTestAll::m_oStdList, "m_oStdList");
   pData = t.data(& CTestAll::m_oStdMap, "m_oStdMap");
   pData = t.data(& CTestAll::m_oBoostTuple, "m_oBoostTuple");
   pData = t.data(& CTestAll::m_oQString, "m_oQString");
   pData = t.data(& CTestAll::m_oQObject, "m_oQObject");
   pData = t.data(& CTestAll::m_oQByteArray, "m_oQByteArray");
   pData = t.data(& CTestAll::m_oQDate, "m_oQDate");
   pData = t.data(& CTestAll::m_oQDateTime, "m_oQDateTime");
   pData = t.data(& CTestAll::m_oQTime, "m_oQTime");

#ifdef _QX_ENABLE_QT_GUI
   pData = t.data(& CTestAll::m_oQBrush, "m_oQBrush");
   pData = t.data(& CTestAll::m_oQColor, "m_oQColor");
   pData = t.data(& CTestAll::m_oQFont, "m_oQFont", 0);
   pData = t.data(& CTestAll::m_oQImage, "m_oQImage", 0);
   pData = t.data(& CTestAll::m_oQPicture, "m_oQPicture", 0);
   pData = t.data(& CTestAll::m_oQRegion, "m_oQRegion", 0);
   pData = t.data(& CTestAll::m_oQMatrix, "m_oQMatrix", 1);
#endif // _QX_ENABLE_QT_GUI

#if (0) /* ((! defined(Q_OS_WIN)) || (! defined(__GNUC__))) // MinGW memory bug ? */
   pData = t.data(& CTestAll::m_oQPoint, "m_oQPoint", 0);
   pData = t.data(& CTestAll::m_oQRect, "m_oQRect", 0);
   pData = t.data(& CTestAll::m_oQRegExp, "m_oQRegExp", 0);
   pData = t.data(& CTestAll::m_oQUrl, "m_oQUrl", 0);
   pData = t.data(& CTestAll::m_oQVariant, "m_oQVariant", 0);
   pData = t.data(& CTestAll::m_oQStringList, "m_oQStringList", 0);
   pData = t.data(& CTestAll::m_oQHash, "m_oQHash", 0);
   pData = t.data(& CTestAll::m_oQMultiHash, "m_oQMultiHash", 0);

   pData = t.data(& CTestAll::m_oQMap, "m_oQMap", 1);
   pData = t.data(& CTestAll::m_oQMultiMap, "m_oQMultiMap", 1);
   pData = t.data(& CTestAll::m_oQxCollection, "m_oQxCollection", 1);
   pData = t.data(& CTestAll::m_oQList, "m_oQList", 1);
   pData = t.data(& CTestAll::m_oQLinkedList, "m_oQLinkedList", 1);
   pData = t.data(& CTestAll::m_oQVector, "m_oQVector", 1);
   pData = t.data(& CTestAll::m_oQPair, "m_oQPair", 1);
   pData = t.data(& CTestAll::m_oBoostScopedPtr, "m_oBoostScopedPtr", 1);
   pData = t.data(& CTestAll::m_oBoostSharedPtr, "m_oBoostSharedPtr", 1);
   pData = t.data(& CTestAll::m_oBoostUnorderedMap, "m_oBoostUnorderedMap", 1);
   pData = t.data(& CTestAll::m_oQSharedPointer, "m_oQSharedPointer", 1);
   pData = t.data(& CTestAll::m_oQSize, "m_oQSize", 1);
#endif // ((! defined(Q_OS_WIN)) || (! defined(__GNUC__)))
}}
