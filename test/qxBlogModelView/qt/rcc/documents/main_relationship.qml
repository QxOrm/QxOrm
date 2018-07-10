import QtQuick 2.1
import QtQuick.Controls 1.0

Item {
   width: 500
   height: 300

   /*
      1- How to display a relationship value :
         * root model : blog
         * child model : author
         * display author name using getModelValue() method of qx::IxModel base class
   */
   Text {
      y: 30
      color: "blue"
      text: "--- 1. display relationship author name using getModelValue() method of qx::IxModel base class ---"
   }
   ListView {
      y: 50
      height: 270
      model: myModel
      delegate: Row {
         height: 20
         spacing: 10
         Text { text: "blog id : " + blog_id }
         TextField {
            text: blog_text
            onTextChanged: blog_text = text
         }
         Text { text: "author name : " + myModel.author_id(0).getModelValue(0, "name") } // display author name using getModelValue() method of qx::IxModel base class
      }
   }

   /*
      2- How to display a relationship value :
         * root model : blog
         * child model : author
         * display author name passing the author child model to another QML component, then using the role value
   */
   Text {
      y: 80
      color: "blue"
      text: "--- 2. display relationship author name passing the author child model to another QML component, then using the author 'name' role value ---"
   }
   ListView {
      y: 100
      height: 270
      model: myModel
      delegate: Row {
         height: 20
         spacing: 10
         Text { text: "blog id : " + blog_id }
         TextField {
            text: blog_text
            onTextChanged: blog_text = text
         }
         ListView {
            x: 200
            height: 270
            model: myModel.author_id(0) // pass the author child model to another QML component
            delegate: Row {
               Text { text: "author name : " + name } // use role 'name' defined in author class to display the author name
            }
         }
      }
   }

   /*
      3- Display the author row id in database using the 'author_id' role defined in blog class
   */
   Text {
      y: 130
      color: "blue"
      text: "--- 3. display the author row id in database using the 'author_id' role defined in blog class ---"
   }
   ListView {
      y: 150
      height: 270
      model: myModel
      delegate: Row {
         height: 20
         spacing: 10
         Text { text: "blog id : " + blog_id }
         TextField {
            text: blog_text
            onTextChanged: blog_text = text
         }
         Text { text: "author id : " + author_id }
      }
   }

}
