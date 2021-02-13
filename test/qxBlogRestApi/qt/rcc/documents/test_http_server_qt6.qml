import QtQuick
import QtQuick.Controls

Item {
   width: 500
   height: 130
   Column {
      anchors.fill: parent
      spacing: 10
      anchors.leftMargin: 5
      anchors.rightMargin: 5
      Label {
         anchors.left: parent.left
         anchors.right: parent.right
         horizontalAlignment: Text.AlignHCenter
         text: "  "
      }
      Label {
         anchors.left: parent.left
         anchors.right: parent.right
         horizontalAlignment: Text.AlignHCenter
         text: "!!! Test QxOrm QxRestApi module from a web page using QxHttpServer module !!!"
         font.bold: true
         color: "blue"
      }
      Label {
         anchors.left: parent.left
         anchors.right: parent.right
         horizontalAlignment: Text.AlignHCenter
         text: "Please open your web browser to this URL : http://localhost:9642/files/test_http_server.html"
      }
      Label {
         anchors.left: parent.left
         anchors.right: parent.right
         horizontalAlignment: Text.AlignHCenter
         text: "Note : closing this QML window means stopping QxOrm HTTP server too."
      }
   }
}
