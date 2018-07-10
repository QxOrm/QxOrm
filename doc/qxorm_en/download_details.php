<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
  <meta http-equiv="content-type" content="text/html; charset=iso-8859-1">
  <title>QxOrm : C++ Qt ORM Object Relational Mapping database library - QxEntityEditor : C++ Qt entities graphic editor (data model designer and source code generator)</title>
  <link rel='stylesheet' type='text/css' href='./resource/qxorm_style.css'>
  <script type="text/javascript" src="./resource/jquery.min.js"></script>
  <script type="text/javascript" src="./resource/qxorm_script.js"></script>
</head>
<body>
<table border="0" style="width: 80%" align="center">
  <col><col><col><col><col>
  <tbody>
    <tr>
      <td><a href="./home.html"><img alt="QxOrm" src="./resource/logo_qxorm_and_qxee.png"align="left" border="0"></a></td>
      <td align="right" style="vertical-align:bottom"><div id="qx_search"><gcse:search></gcse:search></div></td>
      <td width="15"></td>
      <td align="right" style="vertical-align:bottom">
        <img alt="Windows" src="./resource/logo_windows.gif" width="35" height="35">
        <img alt="Linux" src="./resource/logo_linux.gif" width="35" height="35">
        <img alt="Macintosh" src="./resource/logo_mac.gif" width="35" height="35">
      </td>
      <td width="70"><img alt="C++" src="./resource/logo_cpp.gif" width="50" height="50" align="right"></td>
    </tr>
  </tbody>
</table>
<hr style="width: 80%" align="center" size="1" color="#100D5A">
<table border="0" style="width: 80%" align="center">
  <col><col><col><col><col><col>
  <tbody>
    <tr>
      <td align="center"><a href="./home.html" class="btn_nav">Home</a></td>
      <td align="center"><a href="./download.html" class="btn_nav">Download</a></td>
      <td align="center"><a href="./quick_sample.html" class="btn_nav">Quick sample</a></td>
      <td align="center" onmouseover="showHideElementById('menu_tuto', true);" onmouseout="showHideElementById('menu_tuto', false);">
         <a href="./tutorial.html" class="btn_nav">Tutorial (4)</a>
         <table class="table_menu_tuto"><tbody><tr><td>
            <div id="menu_tuto" class="div_menu_tuto">
               <a href="./tutorial_3.html" class="btn_sub_menu">install QxOrm</a><br/>
               <a href="./tutorial.html" class="btn_sub_menu">qxBlog</a><br/>
               <a href="./tutorial_2.html" class="btn_sub_menu">qxClientServer</a><br/>
               <a href="./tutorial_4.html" class="btn_sub_menu">QxEntityEditor videos</a>
            </div>
         </td></tr></tbody></table>
      </td>
      <td align="center" onmouseover="showHideElementById('menu_manual', true);" onmouseout="showHideElementById('menu_manual', false);">
         <a href="./manual.html" class="btn_nav">Manual (2)</a>
         <table class="table_menu_manual"><tbody><tr><td>
            <div id="menu_manual" class="div_menu_manual">
               <a href="./manual.html" class="btn_sub_menu">QxOrm manual</a><br/>
               <a href="./manual_qxee.html" class="btn_sub_menu">QxEntityEditor manual</a><br/>
            </div>
         </td></tr></tbody></table>
      </td>
      <td align="center"><a href="./link.html" class="btn_nav">Forum</a></td>
      <td align="center"><a href="./customer.html" class="btn_nav">Our customers</a></td>
    </tr>
  </tbody>
</table>
<hr style="width: 80%" align="center" size="1" color="#100D5A">
<table border="0" style="width: 80%" align="center">
  <col><col><col><col><col><col>
  <tbody><tr>
  <td align="left" valign="top"><font size="2" class="txt_with_shadow">QxOrm  &gt;&gt;  Download details</font></td>
  <td align="right" valign="top">
    <table cellspacing="0" cellpadding="1"><col><col><tbody>
      <tr>
         <td align="right" valign="top"><font size="2" class="txt_with_shadow">Current version :&nbsp;</font></td>
         <td align="left" valign="top"><font size="2" class="txt_with_shadow">QxOrm 1.4.3 - <a href="../doxygen/index.html" target="_blank">QxOrm library online class documentation</a></font></td>
      </tr>
      <tr>
         <td align="right" valign="top"><font size="2" class="txt_with_shadow"></font></td>
         <td align="left" valign="top"><font size="2" class="txt_with_shadow">QxEntityEditor 1.2.1</font></td>
      </tr>
    </tbody></table>
  </td>
  <td width="10px"></td>
  <td width="40px" height="30px"><a href="../qxorm_fr/download_details.php"><img alt="Version française du site" src="./resource/FR.png" width="40" height="30" border="0"></a></td>
  <td width="40px" height="30px"><a href="../qxorm_en/download_details.php"><img alt="Web site english version" src="./resource/GB.png" width="40" height="30" border="0"></a></td>
  <td width="40px" height="30px"><a href="http://sites.google.com/site/qxormpostgres/" target="_blank"><img alt="" src="./resource/ES.png" width="40" height="30" border="0"></a></td>
  </tr></tbody>
</table>
<table border="1" frame="vsides" rules="cols" style="width: 80%" align="center" cellpadding="6" bgcolor="#F2F2F4">
  <col>
  <tbody>
    <tr>
      <td align="justify">
         <table border="0" style="width: 100%" align="center">
           <col><col>
           <tbody>
             <tr>
               <td>QxOrm library is available with full source code and can be used free of charge under the terms of the <a href="./resource/license.gpl3.txt" target="_blank">GNU General Public License (GPL) version 3</a>.
               <br><br>
               <a href="http://en.wikipedia.org/wiki/GNU_General_Public_License" target="_blank">From Wikipedia</a> : <i>The GNU General Public License (GNU GPL or GPL) is the most widely used free software license, which guarantees end users (individuals, organizations, companies) the freedoms to use, study, share (copy), and modify the software. Software that ensures that these rights are retained is called free software. The GPL grants the recipients of a computer program the rights of the Free Software Definition and uses copyleft to ensure the freedoms are preserved whenever the work is distributed, even when the work is changed or added to. The GPL is a copyleft license, which means that derived works can only be distributed under the same license terms.</i>
               <br><br>
               If the GPLv3 license is too restrictive for your project, you can purchase the <b>QxOrm Proprietary License</b> (<b>QXPL</b>). Additional benefits of the QxOrm Proprietary License include :
               <ul>
                  <li>Application source code stays private ;</li>
                  <li>High compatibility with different commercial and open-source licenses ;</li>
                  <li>Possibility to use QxOrm without delivering the full source of the library code to end users ;</li>
                  <li>Possibility to keep own modifications to QxOrm private ;</li>
                  <li>Possibility to create products without mentioning QxOrm to the end users ;</li>
                  <li>Protection against reverse engineering of the product.</li>
               </ul>
               </td>
               <td width="200" align="center" valign="top"><a href="./resource/qt_ambassador_logo.png" target="_blank"><img alt="qt_ambassador" src="./resource/qt_ambassador_logo_150x150.png" width="150" height="150" border="0"></a><br>
                 <b><font size="2">QxOrm library has been accepted into the <a href="http://forum.qt.io/category/24/qt-ambassador-program" target="_blank">Qt Ambassador Program</a></font></b>
               </td>
             </tr>
           </tbody>
         </table>
         The price of the <b>QxOrm Proprietary License</b> depends on the number of C++ classes registered in QxOrm context (<i>void qx::register_class&lt;my_class&gt;()</i> functions count per application) :
         <ul>
            <li>From 1 to 10 C++ classes registered in QxOrm context per application : <i>100&euro;</i> ;</li>
            <li>From 11 to 20 C++ classes registered in QxOrm context per application : <i>180&euro;</i> ;</li>
            <li>From 21 to 30 C++ classes registered in QxOrm context per application : <i>250&euro;</i> ;</li>
            <li>From 31 to unlimited C++ classes registered in QxOrm context per application : <i>300&euro;</i>.</li>
         </ul>
         The QxOrm QXPL license is a per project (or per application) license, no matter developers count working on the project, and no matter deployed instances count of your software (royalty-free).
         For example, if you develop 3 differents applications based on QxOrm library, then you have to purchase 3 differents QXPL licenses (one per project).<br/>
         <br/>
         If you have any questions, or if you want to purchase the <b>QXPL</b> license, please contact us using this e-mail : <a href="mailto:contact@qxorm.com">contact@qxorm.com</a>.<br/>
         <br/>
         <a href="../php/add_download.php5?file_path=QxOrm_1.4.3.zip&file_desc=QxOrm_1.4.3" class="btn_tuto" target="_blank">Download QxOrm 1.4.3</a>
         <br/>
         <!--
         <script type="text/javascript">
function checkForm(f) { f.submit(); return true; }
         </script>
         <form action="../php/add_download.php" method="POST" onSubmit="return checkForm(this);">
            Your name or compagny name (optional) :<br/>
            <input type="text" id="created_by" name="created_by" size="50" maxlength="200" /><br/>
            Help us to improve QxOrm library adding a comment (optional) :<br/>
            <textarea id="message_text" name="message_text" rows="3" cols="50"></textarea><br/>
            <input type="submit" value="            Download QxOrm 1.4.3            " />
         </form>
         -->
         <br>
      </td>
    </tr>
  </tbody>
</table>
<br><hr style="width: 80%" align="center" size="1" color="#100D5A">
<table border="0" style="width: 80%" align="center">
  <col><col><col>
  <tbody>
    <tr>
      <td align="left" valign="middle">
        <img alt="QxOrm" src="./resource/logo_qxorm_small.png" width="168" height="40">
      </td>
      <td align="center" valign="middle">
        <font size="2">© 2017 Lionel Marty - <a href="mailto:contact@qxorm.com">contact@qxorm.com</a></font>
      </td>
      <td align="right" valign="middle">
        <form action="https://www.paypal.com/cgi-bin/webscr" method="post">
           <input type="hidden" name="cmd" value="_s-xclick">
           <input type="hidden" name="hosted_button_id" value="2K4Z58ZYAYJ6S">
           <input type="image" src="./resource/paypal_support_qxorm_library.gif" border="0" name="submit" alt="Support QxOrm library - PayPal">
           <img alt="" border="0" src="https://www.paypalobjects.com/fr_FR/i/scr/pixel.gif" width="1" height="1">
        </form>
      </td>
    </tr>
  </tbody>
</table>
</body>
</html>
