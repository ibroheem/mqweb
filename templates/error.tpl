<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<head>
 <title>MQWeb - ERROR</title>
 <link href="/static/css/redmond/jquery-ui-1.8.5.custom.css" rel="stylesheet" type="text/css"/>
 <link href="/static/css/mqweb/mqweb.css" rel="stylesheet" type="text/css"/>
 <script src="/static/js/jquery-1.4.2.min.js" type="text/javascript"> </script>
 <script src="/static/js/jquery-ui-1.8.5.custom.min.js" type="text/javascript"> </script>
 <script src="/static/js/jquery.center.js" type="text/javascript"> </script>
 <script type="text/javascript">
  jQuery(document).ready(function()
                         {
                           jQuery("#content").center();
                         });
 </script>
</head>
<body>
 <div style="padding:10px;border:3px solid red;background-color:#FF6666" id="content">
   <img style="float:left;display:block;" src="/static/img/error.png" alt="error" />
   <div style="float:left;padding-left:10px;">
    Object: <?= error.object ?><br />
    Function: <?= error.function ?><br />
    Code: <?= error.code ?><br />
    Reason: <?= error.reason ?>
   </div>
 </div>
</body>
</html>
