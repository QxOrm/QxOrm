import QtQuick 1.0

Item {
   width: 400
   height: 300
   ListView {
      anchors.fill: parent
      model: myModel
      delegate: Row {
         height: 20
         spacing: 10
         Text { text: "id: " + author_id }
         Text { text: "name: " + name }
      }
   }
}
