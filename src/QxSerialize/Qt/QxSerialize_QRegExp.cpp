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

#include "../../../include/QxPrecompiled.h"

#include "../../../include/QxSerialize/Qt/QxSerialize_QRegExp.h"

#include "../../../include/QxMemLeak.h"

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const QRegExp & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QString sPattern = t.pattern();
   int iCaseSensitivity = static_cast<int>(t.caseSensitivity());
   int iPatternSyntax = static_cast<int>(t.patternSyntax());
   bool bMinimal = t.isMinimal();

   ar << boost::serialization::make_nvp("pattern", sPattern);
   ar << boost::serialization::make_nvp("caseSensitivity", iCaseSensitivity);
   ar << boost::serialization::make_nvp("patternSyntax", iPatternSyntax);
   ar << boost::serialization::make_nvp("minimal", bMinimal);
}

template <class Archive>
inline void qx_load(Archive & ar, QRegExp & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QString sPattern; bool bMinimal(false);
   int iCaseSensitivity(0), iPatternSyntax(0);

   ar >> boost::serialization::make_nvp("pattern", sPattern);
   ar >> boost::serialization::make_nvp("caseSensitivity", iCaseSensitivity);
   ar >> boost::serialization::make_nvp("patternSyntax", iPatternSyntax);
   ar >> boost::serialization::make_nvp("minimal", bMinimal);

   t.setPattern(sPattern);
   t.setCaseSensitivity(static_cast<Qt::CaseSensitivity>(iCaseSensitivity));
   t.setPatternSyntax(static_cast<QRegExp::PatternSyntax>(iPatternSyntax));
   t.setMinimal(bMinimal);
}

} // namespace boost
} // namespace serialization

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QRegExp)
