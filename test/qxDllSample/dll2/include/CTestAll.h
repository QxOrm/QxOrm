#ifndef _QX_CLASS_TEST_ALL_H_
#define _QX_CLASS_TEST_ALL_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtGui/qcolor.h>
#include <QtGui/qfont.h>
#include <QtGui/qimage.h>
#include <QtGui/qbrush.h>
#include <QtGui/qmatrix.h>
#include <QtGui/qpicture.h>
#include <QtGui/qpixmap.h>
#include <QtGui/qregion.h>

#include "../../dll1/include/CPerson.h"
#include "../../dll2/include/CUser.h"

class QX_DLL2_EXPORT CTestAll
{

   QX_REGISTER_FRIEND_CLASS(CTestAll)

protected:

   long m_lId;
   qx_bool m_oQxBool;

   std::string m_oStdString;
   std::pair<QPoint, QRect> m_oStdPair;
   std::vector< QSharedPointer<qx::test::CPerson> > m_oStdVector;
   std::list<QDateTime> m_oStdList;
   std::map<std::string, QSharedPointer<CUser> > m_oStdMap;

   boost::tuple<QTime, QPoint, QUrl> m_oBoostTuple;
   boost::scoped_ptr<QSize> m_oBoostScopedPtr;
   qx_shared_ptr<QObject> m_oBoostSharedPtr;
   boost::weak_ptr<CTestAll> m_oBoostWeakPtr;
   boost::unordered_map<long, std::string> m_oBoostUnorderedMap;

   QString m_oQString;
   QObject m_oQObject;
   QBrush m_oQBrush;
   QByteArray m_oQByteArray;
   QColor m_oQColor;
   QDate m_oQDate;
   QDateTime m_oQDateTime;
   QTime m_oQTime;
   QFont m_oQFont;
   QMatrix m_oQMatrix;
   QImage m_oQImage;
   QPicture m_oQPicture;
   QPoint m_oQPoint;
   QRect m_oQRect;
   QSize m_oQSize;
   QRegExp m_oQRegExp;
   QRegion m_oQRegion;
   QUrl m_oQUrl;
   QVariant m_oQVariant;
   QStringList m_oQStringList;

   QHash<long, QString> m_oQHash;
   QMultiHash<QString, qx_shared_ptr<qx::test::CPerson> > m_oQMultiHash;
   QMap<double, std::string> m_oQMap;
   QMultiMap<std::string, QSharedPointer<CUser> > m_oQMultiMap;
   qx::QxCollection<QString, boost::tuple<long, qx::test::CPerson *> > m_oQxCollection;

   QList<float> m_oQList;
   QLinkedList<QString> m_oQLinkedList;
   QVector<CUser *> m_oQVector;
   QSharedPointer<boost::tuple<int, std::string, qx_shared_ptr<qx::test::CPerson> > > m_oQSharedPointer;
   QPair<QString, QPoint> m_oQPair;

public:

   CTestAll() { init(); }
   virtual ~CTestAll() { terminate(); }

   static void test();

private:

   void init();
   void terminate();

};

QX_REGISTER_HPP_QX_DLL2(CTestAll, qx::trait::no_base_class_defined, 1)

#endif // _QX_CLASS_TEST_ALL_H_
