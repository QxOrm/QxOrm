<html>
<head>
<meta http-equiv="refresh" content="0; url=../version/QxOrm_1.4.3.zip">
<?php
   settype($nb_errors, "integer");
   settype($try_count, "integer");
   /*
   if ($_POST['created_by'] == "") { $errors = $errors . "\nYou must write your name or compagny name."; $nb_errors++; }
   */
   if ($nb_errors != 0) { echo "<script type='text/javascript'>alert('" . $errors . "');</script>"; }
   if ($nb_errors == 0)
   {
      $_POST['created_by'] = nl2br(htmlentities(stripslashes($_POST['created_by'])));
      $_POST['message_text'] = nl2br(htmlentities(stripslashes($_POST['message_text'])));
      $createdby = "<h3>**** Downloaded by " . $_POST['created_by'] . " (" . date(d."/".m."/"."Y") . " " . date(H.":".i) . ")</h3>";
      $msg = "<p>" . $_POST['message_text'] . "</p>";
      $filename = "./version_1.4.3.php";
      while ((file_exists($filename)) && (! is_writable($filename)) && ($try_count < 200)) { usleep(100000); $try_count++; }
      $fp = fopen($filename, "a");
      fputs($fp, "\n");
      fputs($fp, $createdby);
      fputs($fp, "\n");
      fputs($fp, $msg);
      fclose($fp);
   }
   echo "<script type='text/javascript'>document.location.href='../version/QxOrm_1.4.3.zip';</script>";
?>
</head>
<body>
</body>
</html>
