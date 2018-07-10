#include "../include/precompiled.h"

#include "../include/TestQtProperty.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_DLL1(TestQtProperty)
QX_REGISTER_ALL_QT_PROPERTIES(TestQtProperty, "id")

/*
   Instead of using 'QX_REGISTER_ALL_QT_PROPERTIES(...)' macro, it's also
   possible to write classic 'void qx::register_class<T>(...)' function, like this :

   namespace qx {
   template <> void register_class(QxClass<MyQObject> & t)
   { qx::register_all_qt_properties<MyQObject>(t, "my_id"); }
   } // namespace qx

   So, you can mix Qt meta-properties and classic registration data-member.
   All is stored using the same interface : 'qx::IxDataMember *'.
   To more details about advantages and disadvantages of using Qt meta-property,
   go to the FAQ of QxOrm library :
   - How to register automatically Qt meta-properties to QxOrm context ?
*/
