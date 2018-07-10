function showHideElementById(id, show)
{
   var obj = document.getElementById(id);
   var objParent = (obj ? obj.parentNode : null);
   if (obj && ! show) { obj.style.display = 'none'; }
   else if (obj) { obj.style.display = 'block'; }
   if (objParent && ! show) { objParent.style.display = 'none'; }
   else if (objParent) { objParent.style.display = 'block'; }
}
