function showHideElementById(id, show) {
   var obj = document.getElementById(id);
   var objParent = (obj ? obj.parentNode : null);
   if (obj && ! show) { obj.style.display = 'none'; }
   else if (obj) { obj.style.display = 'block'; }
   if (objParent && ! show) { objParent.style.display = 'none'; }
   else if (objParent) { objParent.style.display = 'block'; }
}

(function() {
   var cx = '017860332352182638653:t-roc8qak5q';
   var gcse = document.createElement('script');
   gcse.type = 'text/javascript';
   gcse.async = true;
   gcse.src = ((document.location.protocol == 'https:') ? 'https:' : 'http:') + '//cse.google.com/cse.js?cx=' + cx;
   var s = document.getElementsByTagName('script')[0];
   s.parentNode.insertBefore(gcse, s);
})();

function initQxOrmManualWebPage() {
   // Put an index on each item of table of contents
   var currLevel1 = 0; var currLevel2 = 0; var currLevel3 = 0;
   $('#manual_table_of_contents .manual_li_title_1 a').each(function(index, value) {
      if ($(this).parent().hasClass('manual_li_title_1')) {
         currLevel1 = (currLevel1 + 1); currLevel2 = 0; currLevel3 = 0;
         $(this).text(currLevel1 + '. ' + $(this).text());
      }
      else if ($(this).parent().hasClass('manual_li_title_2')) {
         currLevel2 = (currLevel2 + 1); currLevel3 = 0;
         $(this).text(currLevel1 + '.' + currLevel2 + '. ' + $(this).text());
      }
      else if ($(this).parent().hasClass('manual_li_title_3')) {
         currLevel3 = (currLevel3 + 1);
         $(this).text(currLevel1 + '.' + currLevel2 + '.' + currLevel3 + '. ' + $(this).text());
      }
      else {
         alert('QxOrm - Manual - Table of contents - level not implemented !');
      }
   });

   // Remove default ol/li style
   $('.manual_li_title_1').css('list-style-type', 'none');
   $('.manual_li_title_2').css('list-style-type', 'none');
   $('.manual_li_title_3').css('list-style-type', 'none');

   // Put an index on each paragraph associated to table of contents
   var currLevel1 = 0; var currLevel2 = 0; var currLevel3 = 0;
   $('#manual_content a').each(function(index, value) {
      if ($(this).hasClass('manual_a_title_1')) {
         currLevel1 = (currLevel1 + 1); currLevel2 = 0; currLevel3 = 0;
         $(this).text(currLevel1 + '. ' + $(this).text());
      }
      else if ($(this).hasClass('manual_a_title_2')) {
         currLevel2 = (currLevel2 + 1); currLevel3 = 0;
         $(this).text(currLevel1 + '.' + currLevel2 + '. ' + $(this).text());
      }
      else if ($(this).hasClass('manual_a_title_3')) {
         currLevel3 = (currLevel3 + 1);
         $(this).text(currLevel1 + '.' + currLevel2 + '.' + currLevel3 + '. ' + $(this).text());
      }
   });

   // Iterate over all 'json_pretty' div
   $('#manual_content .json_pretty').each(function(index, value) {
      try {
         var jsonObj = JSON.parse($(this).text());
         var jsonPretty = JSON.stringify(jsonObj, null, 2);
         var jsonHighlighted = jsonSyntaxHighlight(jsonPretty);
         $(this).html(""); $(this).get(0).appendChild(document.createElement('pre')).innerHTML = jsonHighlighted;
      }
      catch(exc) { ; }
   });
}

function jsonSyntaxHighlight(json) {
   json = json.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
   return json.replace(/("(\\u[a-zA-Z0-9]{4}|\\[^u]|[^\\"])*"(\s*:)?|\b(true|false|null)\b|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?)/g, function (match) {
      var cls = 'number';
      if (/^"/.test(match)) {
         if (/:$/.test(match)) {
            cls = 'key';
         } else {
            cls = 'string';
         }
      } else if (/true|false/.test(match)) {
         cls = 'boolean';
      } else if (/null/.test(match)) {
         cls = 'null';
      }
      return '<span class="' + cls + '">' + match + '</span>';
   });
}
