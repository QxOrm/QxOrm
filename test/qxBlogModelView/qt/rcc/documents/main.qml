import QtQuick 2.1
import QtQuick.Controls 1.0

Item {
   width: 400
   height: 300
   Row {
      height: 20
      spacing: 20
      Button {
         text: "Clear"
         onClicked: myModel.clear()
      }
      Button {
         text: "Fetch All"
         onClicked: myModel.qxFetchAll_()
      }
      Button {
         text: "Save"
         onClicked: myModel.qxSave_()
      }
   }
   ListView {
      y: 30
      height: 270
      model: myModel
      delegate: Row {
         height: 20
         spacing: 10
         Text { text: "id: " + author_id }
         TextField {
            text: name
            onTextChanged: name = text
         }
      }
   }
}
