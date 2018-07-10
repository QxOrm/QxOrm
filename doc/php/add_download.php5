<html>
<body>
   <?php
      $file_to_download = '../version/' . $_GET["file_path"];
      $file_description = $_GET["file_desc"];
      $is_valid = ((substr($_GET["file_path"], 0, 2) === 'Qx') && (substr($_GET["file_desc"], 0, 2) === 'Qx'));
      if (($is_valid) && (file_exists($file_to_download)))
      {
         try
         {
            settype($try_count, "integer");
            $file_log = "./download_log/" . $file_description . ".php";
            $text_log = "<h3>**** " . date(d."/".m."/"."Y") . " " . date(H.":".i) . " ****</h3>";
            while ((file_exists($file_log)) && (! is_writable($file_log)) && ($try_count < 200))
            { usleep(100000); $try_count++; }
            $fp = fopen($file_log, "a");
            fputs($fp, "\n");
            fputs($fp, $text_log);
            fclose($fp);
         }
         catch (Exception $exc) { echo '<p>' . $exc->getMessage() . '</p>'; }

         echo '<p>If your download does not start automatically within 5 seconds, <a href="' . $file_to_download . '">please click here to manually download the file</a>.</p>';
         echo '<br/>';
         echo '<p><a href="../qxorm_en/home.html"><img alt="QxOrm and QxEntityEditor home page" src="../qxorm_en/resource/logo_qxorm_and_qxee.png" align="left" border="0"></a></p>';

         echo '<script type="text/javascript">';
         echo 'document.location.href = "' . $file_to_download . '";';
         echo '</script>';
      }
      else if ($is_valid)
      {
         echo '<p>File to download <b>' . $file_to_download . '</b> does not exist !</p>';
         echo '<br/>';
         echo '<p><a href="../qxorm_en/home.html"><img alt="QxOrm and QxEntityEditor home page" src="../qxorm_en/resource/logo_qxorm_and_qxee.png" align="left" border="0"></a></p>';
      }
   ?>
</body>
</html>
