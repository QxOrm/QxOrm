import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

Item {
   width: 1000
   height: 700
   Row {
      anchors.fill: parent
      spacing: 10
      anchors.leftMargin: 5
      anchors.rightMargin: 5
      Column {
         width: ((parent.width - 10) * 0.5)
         height: (parent.height)
         spacing: 10
         Label {
            anchors.left: parent.left
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            text: "JSON Request"
            font.bold: true
            color: "blue"
         }
         TextArea {
            id: txtRequest
            anchors.left: parent.left
            anchors.right: parent.right
            height: (parent.height * 0.4)
            wrapMode: TextEdit.NoWrap
            text: ""
         }
         Button {
            anchors.left: parent.left
            anchors.right: parent.right
            text: "Send JSON request"
            height: 45
            onClicked: onSendRequest()
            style: ButtonStyle {
               label: Text {
                  renderType: Text.NativeRendering
                  verticalAlignment: Text.AlignVCenter
                  horizontalAlignment: Text.AlignHCenter
                  text: control.text
                  font.pointSize: 12
                  font.bold: true
                  color: "blue"
               }
            }
         }
         Label {
            anchors.left: parent.left
            anchors.right: parent.right
            text: "Here are some request examples :"
            font.italic: true
            color: "blue"
         }
         ScrollView {
            width: parent.width
            height: (parent.height * 0.4)
            ListView {
               id: lstRequestExample
               anchors.fill: parent
               flickableDirection: Flickable.VerticalFlick
               boundsBehavior: Flickable.StopAtBounds
               model: ListModel {
                  id: modelRequestExample
                  ListElement { key: "get_meta_data"; txt: " - get project meta-data (all classes)" }
                  ListElement { key: "fetch_all_blogs"; txt: " - fetch all blogs (as list)" }
                  ListElement { key: "fetch_all_blogs_as_collection"; txt: " - fetch all blogs (as collection key/value)" }
                  ListElement { key: "fetch_all_blogs_with_relationships"; txt: " - fetch all blogs with relationships (several levels)" }
                  ListElement { key: "fetch_all_blogs_with_relationships_output_format"; txt: " - fetch all blogs with relationships (several levels) and define output format" }
                  ListElement { key: "fetch_blog_by_id"; txt: " - fetch a single blog by id" }
                  ListElement { key: "fetch_blog_by_id_columns"; txt: " - fetch some columns of a single blog by id" }
                  ListElement { key: "fetch_list_of_blog_by_id"; txt: " - fetch list of blogs by id" }
                  ListElement { key: "fetch_list_of_blog_by_id_output_format"; txt: " - fetch list of blogs by id and define output format" }
                  ListElement { key: "fetch_authors_by_query"; txt: " - fetch authors using a query (only female)" }
                  ListElement { key: "fetch_authors_by_query_with_relationships"; txt: " - fetch authors with relationships using a query" }
                  ListElement { key: "fetch_authors_by_query_with_relationships_output_format"; txt: " - fetch authors with relationships using a query and define output format" }
                  ListElement { key: "insert_blog"; txt: " - insert a blog" }
                  ListElement { key: "insert_list_of_blog"; txt: " - insert list of blogs" }
                  ListElement { key: "insert_author"; txt: " - insert an author" }
                  ListElement { key: "insert_category"; txt: " - insert a category" }
                  ListElement { key: "update_blog"; txt: " - update a blog" }
                  ListElement { key: "update_blog_columns"; txt: " - update some columns of blog" }
                  ListElement { key: "update_author"; txt: " - update an author" }
                  ListElement { key: "update_list_of_author"; txt: " - update list of authors" }
                  ListElement { key: "update_category"; txt: " - update a category" }
                  ListElement { key: "save_blog"; txt: " - save (insert or update) a blog" }
                  ListElement { key: "save_list_of_blog"; txt: " - save (insert or update) list of blogs" }
                  ListElement { key: "save_blog_recursive"; txt: " - save (insert or update) a blog with relationships (recursively)" }
                  ListElement { key: "save_blog_recursive_insert"; txt: " - save (insert optimized) a blog with relationships (recursively)" }
                  ListElement { key: "exist_blog"; txt: " - check if a blog id exist" }
                  ListElement { key: "exist_list_of_blog"; txt: " - check if list of blogs id exist" }
                  ListElement { key: "exist_author"; txt: " - check if an author id exist" }
                  ListElement { key: "validate_blog"; txt: " - validate a blog instance" }
                  ListElement { key: "count_all_blog"; txt: " - count all blogs" }
                  ListElement { key: "count_author_with_query"; txt: " - count authors using a query" }
                  ListElement { key: "count_blog_with_query_and_relationships"; txt: " - count blogs using a query and relationships" }
                  ListElement { key: "delete_blog_by_id"; txt: " - delete a blog by id" }
                  ListElement { key: "delete_list_of_blog_by_id"; txt: " - delete list of blogs by id" }
                  ListElement { key: "delete_author_by_query"; txt: " - delete some authors using a query" }
                  ListElement { key: "delete_all_comment"; txt: " - delete all comments" }
                  ListElement { key: "call_custom_query"; txt: " - call custom database query or stored procedure" }
                  ListElement { key: "call_entity_function"; txt: " - call entity static function with signature : static QJsonValue myEntity::myFct(const QJsonValue & request)" }
                  ListElement { key: "several_requests_in_array"; txt: " - build several requests in array to send only 1 call to server (executed in a transaction commit/rollback)" }
               }
               delegate: Rectangle {
                  width: parent.width
                  height: 20
                  color: ((index == lstRequestExample.currentIndex) ? "lightblue" : (((index % 2) == 0) ? "white" : "papayawhip"))
                  Column { Text { text: txt } }
                  MouseArea {
                     anchors.fill: parent
                     onClicked: lstRequestExample.currentIndex = index
                  }
               }
               highlight: Rectangle { color: "lightblue" }
               onCurrentItemChanged: onRequestExampleSelected(modelRequestExample.get(lstRequestExample.currentIndex))
               Component.onCompleted : currentIndex = -1
               focus: true
            }
         }
      }
      Column {
         width: ((parent.width - 10) * 0.5)
         height: (parent.height)
         spacing: 10
         Label {
            anchors.left: parent.left
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            text: "JSON Response"
            font.bold: true
            color: "blue"
         }
         TextArea {
            id: txtResponse
            anchors.left: parent.left
            anchors.right: parent.right
            height: (parent.height * 0.9)
            wrapMode: TextEdit.NoWrap
            text: ""
         }
      }
   }

   function onSendRequest() {
      try {
         console.log("onSendRequest() called");
         qxRestApi.clearAll();
         var response = qxRestApi.processRequest(txtRequest.text);
         response = JSON.parse(response);
         txtResponse.text = JSON.stringify(response, null, 3);
      }
      catch(exc) {
         txtResponse.text = "An error occurred processing request : " + exc;
      }
   }

   function onRequestExampleSelected(objRequestExample) {
      txtResponse.text = "";
      if (! objRequestExample) { return; }
      console.log("onRequestExampleSelected() : " + objRequestExample.key + " selected");
      var request = buildRequestExample(objRequestExample);
      txtRequest.text = JSON.stringify(request, null, 3);
   }

   function buildRequestExample(objRequestExample) {
      var request = { };
      request.request_id = createGUID();
      if (objRequestExample.key == "get_meta_data") {
         request.action = "get_meta_data";
         request.entity = "*";
      }
      else if (objRequestExample.key == "fetch_all_blogs") {
         request.action = "fetch_all";
         request.entity = "blog";
      }
      else if (objRequestExample.key == "fetch_all_blogs_as_collection") {
         request.action = "fetch_all";
         request.entity = "blog";
         request.data = [ { key: "", value: "" } ]
      }
      else if (objRequestExample.key == "fetch_all_blogs_with_relationships") {
         request.action = "fetch_all";
         request.entity = "blog";
         request.relations = [ "*->*" ];
      }
      else if (objRequestExample.key == "fetch_all_blogs_with_relationships_output_format") {
         request.action = "fetch_all";
         request.entity = "blog";
         request.relations = [ "<blog_alias> { blog_text }", "author_id <author_alias> { name, birthdate }", "list_comment <list_comment_alias> { comment_text } -> blog_id <blog_alias_2> -> * <..._my_alias_suffix>" ];
         request.output_format = [ "{ blog_text }", "author_id { name, birthdate }", "list_comment { comment_text } -> blog_id -> *" ];
      }
      else if (objRequestExample.key == "fetch_blog_by_id") {
         request.action = "fetch_by_id";
         request.entity = "blog";
         request.data = { blog_id: 1 };
      }
      else if (objRequestExample.key == "fetch_blog_by_id_columns") {
         request.action = "fetch_by_id";
         request.entity = "blog";
         request.data = { blog_id: 1 };
         request.columns = [ "blog_text", "date_creation" ];
      }
      else if (objRequestExample.key == "fetch_list_of_blog_by_id") {
         request.action = "fetch_by_id";
         request.entity = "blog";
         request.data = [ { blog_id: 1 }, { blog_id: 2 }, { blog_id: 3 } ];
      }
      else if (objRequestExample.key == "fetch_list_of_blog_by_id_output_format") {
         request.action = "fetch_by_id";
         request.entity = "blog";
         request.data = [ { blog_id: 1 }, { blog_id: 2 } ];
         request.relations = [ "{ blog_text }", "author_id <author_alias> { name, birthdate }", "list_comment <list_comment_alias> { comment_text }" ];
         request.output_format = [ "{ blog_text }", "author_id { name, birthdate }", "list_comment { comment_text }" ];
      }
      else if (objRequestExample.key == "fetch_authors_by_query") {
         request.action = "fetch_by_query";
         request.entity = "author";
         request.query = {
            sql: "WHERE author.sex = :sex", 
            params: [ { key: ":sex", value: 1, type: "in" } ]
         };
      }
      else if (objRequestExample.key == "fetch_authors_by_query_with_relationships") {
         request.action = "fetch_by_query";
         request.entity = "author";
         request.query = {
            sql: "WHERE author.sex = :sex", 
            params: [ { key: ":sex", value: 1, type: "in" } ]
         };
         request.relations = [ "*" ];
      }
      else if (objRequestExample.key == "fetch_authors_by_query_with_relationships_output_format") {
         request.action = "fetch_by_query";
         request.entity = "author";
         request.query = {
            sql: "WHERE author.sex = :sex", 
            params: [ { key: ":sex", value: 1, type: "in" } ]
         };
         request.relations = [ "*" ];
         request.output_format = [ "{ birthdate, name }", "list_blog { blog_text, date_creation }" ];
      }
      else if (objRequestExample.key == "insert_blog") {
         request.action = "insert";
         request.entity = "blog";
         request.data = {
            blog_text: "this is a new blog from QxOrm REST API !", 
            date_creation: "2018-01-30T12:42:01", 
            author_id: "author_id_2"
         };
      }
      else if (objRequestExample.key == "insert_list_of_blog") {
         request.action = "insert";
         request.entity = "blog";
         request.data = [
            {
               blog_text: "new blog from QxOrm REST API !", 
               date_creation: "2018-01-30T12:42:01", 
               author_id: "author_id_2"
            }, 
            {
               blog_text: "another blog from QxOrm REST API !", 
               date_creation: "2016-06-12T08:33:12", 
               author_id: "author_id_1"
            }
         ];
      }
      else if (objRequestExample.key == "insert_author") {
         request.action = "insert";
         request.entity = "author";
         request.data = {
            author_id: "author_id_from_rest_api", 
            birthdate: "1978-05-11", 
            name: "new author created by QxOrm REST API", 
            sex: 1
         };
      }
      else if (objRequestExample.key == "insert_category") {
         request.action = "insert";
         request.entity = "category";
         request.data = {
            description: "category from REST API", 
            name: "new_category"
         };
      }
      else if (objRequestExample.key == "update_blog") {
         request.action = "update";
         request.entity = "blog";
         request.data = {
            blog_id: 1, 
            blog_text: "modify blog from QxOrm REST API", 
            date_creation: "2013-11-25T09:56:33", 
            author_id: "author_id_1"
         };
      }
      else if (objRequestExample.key == "update_blog_columns") {
         request.action = "update";
         request.entity = "blog";
         request.data = {
            blog_id: 2, 
            blog_text: "modify blog from QxOrm REST API", 
            date_creation: "2013-11-25T09:56:33"
         };
         request.columns = [ "blog_text", "date_creation" ];
      }
      else if (objRequestExample.key == "update_author") {
         request.action = "update";
         request.entity = "author";
         request.data = {
            author_id: "author_id_from_rest_api", 
            birthdate: "1992-11-03", 
            name: "modify author from QxOrm REST API", 
            sex: 0
         };
      }
      else if (objRequestExample.key == "update_list_of_author") {
         request.action = "update";
         request.entity = "author";
         request.data = [
            {
               author_id: "author_id_from_rest_api", 
               birthdate: "1992-11-03", 
               name: "modify author from QxOrm REST API", 
               sex: 0
            }, 
            {
               author_id: "author_id_1", 
               birthdate: "1978-12-25", 
               name: "modify another author from QxOrm REST API", 
               sex: 2
            }
         ];
      }
      else if (objRequestExample.key == "update_category") {
         request.action = "update";
         request.entity = "category";
         request.data = {
            category_id: 1, 
            description: "category modified by REST API", 
            name: "modif_category"
         };
      }
      else if (objRequestExample.key == "save_blog") {
         request.action = "save";
         request.entity = "blog";
         request.data = {
            blog_id: 1, 
            blog_text: "modify blog from QxOrm REST API", 
            date_creation: "2013-11-25T09:56:33", 
            author_id: "author_id_1"
         };
      }
      else if (objRequestExample.key == "save_list_of_blog") {
         request.action = "save";
         request.entity = "blog";
         request.data = [
            {
               blog_id: 1, 
               blog_text: "save blog from QxOrm REST API !", 
               date_creation: "2018-01-30T12:42:01", 
               author_id: "author_id_2"
            }, 
            {
               blog_text: "save another blog from QxOrm REST API !", 
               date_creation: "2016-06-12T08:33:12", 
               author_id: "author_id_1"
            }
         ];
      }
      else if (objRequestExample.key == "save_blog_recursive") {
         request.action = "save";
         request.entity = "blog";
         request.data = {
            blog_id: 1, 
            blog_text: "save recursive blog from QxOrm REST API", 
            date_creation: "2013-11-25T09:56:33", 
            author_id: {
               author_id: "author_id_1", 
               birthdate: "1965-07-21", 
               name: "save recursive author from QxOrm REST API", 
               sex: 0
            }
         };
         request.save_mode = "check_insert_or_update";
      }
      else if (objRequestExample.key == "save_blog_recursive_insert") {
         request.action = "save";
         request.entity = "blog";
         request.data = {
            blog_text: "save recursive - new blog from QxOrm REST API", 
            date_creation: "2013-11-25T09:56:33", 
            author_id: {
               author_id: "author_id_save_recursive", 
               birthdate: "1965-07-21", 
               name: "save recursive (insert only) author from QxOrm REST API", 
               sex: 0
            }
         };
         request.save_mode = "insert_only";
      }
      else if (objRequestExample.key == "exist_blog") {
         request.action = "exist";
         request.entity = "blog";
         request.data = { blog_id: 1 };
      }
      else if (objRequestExample.key == "exist_list_of_blog") {
         request.action = "exist";
         request.entity = "blog";
         request.data = [ { blog_id: 1 }, { blog_id: 999 }, { blog_id: 3 } ];
      }
      else if (objRequestExample.key == "exist_author") {
         request.action = "exist";
         request.entity = "author";
         request.data = { author_id: "author_id_2" };
      }
      else if (objRequestExample.key == "validate_blog") {
         request.action = "validate";
         request.entity = "blog";
         request.data = { blog_id: 9999, blog_text: "" };
      }
      else if (objRequestExample.key == "count_all_blog") {
         request.action = "count";
         request.entity = "blog";
      }
      else if (objRequestExample.key == "count_author_with_query") {
         request.action = "count";
         request.entity = "author";
         request.query = {
            sql: "WHERE author.sex = :sex", 
            params: [ { key: ":sex", value: 1 } ]
         };
      }
      else if (objRequestExample.key == "count_blog_with_query_and_relationships") {
         request.action = "count";
         request.entity = "blog";
         request.query = {
            sql: "WHERE author_alias.sex = :sex", 
            params: [ { key: ":sex", value: 1 } ]
         };
         request.relations = [ "author_id <author_alias> { sex }" ];
      }
      else if (objRequestExample.key == "delete_blog_by_id") {
         request.action = "delete_by_id";
         request.entity = "blog";
         request.data = { blog_id: 4 };
      }
      else if (objRequestExample.key == "delete_list_of_blog_by_id") {
         request.action = "delete_by_id";
         request.entity = "blog";
         request.data = [ { blog_id: 3 }, { blog_id: 2 } ];
      }
      else if (objRequestExample.key == "delete_author_by_query") {
         request.action = "delete_by_query";
         request.entity = "author";
         request.query = {
            sql: "WHERE author.sex = :sex", 
            params: [ { key: ":sex", value: 1 } ]
         };
      }
      else if (objRequestExample.key == "delete_all_comment") {
         request.action = "delete_all";
         request.entity = "comment";
      }
      else if (objRequestExample.key == "call_custom_query") {
         request.action = "call_custom_query";
         request.query = {
            sql: "INSERT INTO author (author_id, name, birthdate, sex) VALUES (:author_id, :name, :birthdate, :sex)", 
            params: [
               { key: ":author_id", value: "author_id_custom_query" }, 
               { key: ":name", value: "new author inserted by custom query" }, 
               { key: ":birthdate", value: "20190215" }, 
               { key: ":sex", value: 2 }
            ]
         };
      }
      else if (objRequestExample.key == "call_entity_function") {
         request.action = "call_entity_function";
         request.entity = "blog";
         request.fct = "helloWorld";
         request.data = { param1: "test", param2: "static fct call" };
      }
      else if (objRequestExample.key == "several_requests_in_array") {
         request = [ buildRequestExample(modelRequestExample.get(0)), 
                     buildRequestExample(modelRequestExample.get(1)), 
                     buildRequestExample(modelRequestExample.get(2)), 
                     buildRequestExample(modelRequestExample.get(3)) ];
      }
      else {
         request.error = "<unknown request example : " + objRequestExample.key + ">";
      }
      return request;
   }

   function createGUID() {
      return "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx".replace(/[xy]/g, function(c) {
         var r = Math.random() * 16 | 0, v = c == "x" ? r : (r & 0x3 | 0x8);
         return v.toString(16);
      });
   }
}
