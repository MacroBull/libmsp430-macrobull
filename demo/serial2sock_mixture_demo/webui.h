
#include <stdint.h>

const char header_200[]="HTTP/1.1 200 OK\nContent-Type: text/html; charset=UTF-8\nAccess-Control-Allow-Origin null";
const char header_404[]="HTTP/1.1 404 Not Found\nContent-Type: text/html; charset=UTF-8\nAccess-Control-Allow-Origin null";


//for (i=0;i<2000;i+=10) {console.log(i);$.post("write", '{"setPWM": '+i+'}\n');}


const char _html_404[]="<html class=\"js no-touch history rgba boxshadow csstransforms csstransforms3d csstransitions localstorage fancytransitions wf-adobecaslonpro-i4-active wf-adobecaslonpro-n4-active wf-active js no-touch history rgba boxshadow csstransforms csstransforms3d csstransitions localstorage fancytransitions js no-touch history rgba boxshadow csstransforms csstransforms3d csstransitions localstorage fancytransitions js no-touch history rgba boxshadow csstransforms csstransforms3d csstransitions localstorage fancytransitions\"><head> <title>404</title> <link rel=\"icon\" type=\"image/png\" href=\"http://storage.knormal.com/static/img/favicon.png?v=2\"> <link rel=\"stylesheet\" href=\"http://storage.knormal.com/static/CACHE/css/46f00ec9bc77.css\" type=\"text/css\"> <script type=\"text/javascript\">try{Typekit.load();}catch(e){}</script> <script type=\"text/javascript\" charset=\"utf-8\" src=\"http://storage.knormal.com/static/js/libs/modernizr.js\"></script> <script type=\"text/javascript\" charset=\"utf-8\"> Modernizr.addTest('fancytransitions', function () { return ( Modernizr.csstransitions && Modernizr.csstransforms ); }); </script> <script type=\"text/javascript\">var NREUMQ=NREUMQ||[];NREUMQ.push([\"mark\",\"firstbyte\",new Date().getTime()]);</script></head> <body class=\"\"> <div id=\"wrapper\"> <div id=\"main\" style=\"min-height: 258px;\"> <!-- Content --> <div id=\"content_error\" class=\"content content-in\"> <div id=\"error_table\"> <div id=\"error_cell\"> <div class=\"container-wrapper\"> <div class=\"container\"> <h1 id=\"error_message\">WTF... <span>Page not found.</span></h1> <p>We don't know how you ended up here, but you should just <a href=\"/\">go home now</a>.</p> </div> </div> </div> </div> </div> </div> <div id=\"footer_push\"></div> </div> <script type=\"text/javascript\">if(!NREUMQ.f){NREUMQ.f=function(){NREUMQ.push([\"load\",new Date().getTime()]);var e=document.createElement(\"script\");e.type=\"text/javascript\";e.src=((\"http:\"===document.location.protocol)?\"http:\":\"https:\")+\"//\"+\"js-agent.newrelic.com/nr-100.js\";document.body.appendChild(e);if(NREUMQ.a)NREUMQ.a();};NREUMQ.a=window.onload;window.onload=NREUMQ.f;};NREUMQ.push([\"nrfj\",\"beacon-2.newrelic.com\",\"89086e09bd\",\"3098520\",\"YlYGZEEEVhZWAkZcDlscIkVdBkwMWA8dUQtUXQNfHRNRAEASHFEEU1IRXEcWAhVWBldqD1pHO1ZcEFYB\",0,47,new Date().getTime(),\"\",\"\",\"\",\"\",\"\"]);</script><script type=\"text/javascript\" src=\"https://js-agent.newrelic.com/nr-100.js\"></script><script type=\"text/javascript\" src=\"https://beacon-2.newrelic.com/1/89086e09bd?a=3098520&amp;be=79&amp;qt=0&amp;ap=47&amp;dc=58&amp;fe=1026&amp;to=YlYGZEEEVhZWAkZcDlscIkVdBkwMWA8dUQtUXQNfHRNRAEASHFEEU1IRXEcWAhVWBldqD1pHO1ZcEFYB&amp;v=42&amp;jsonp=NREUM.setToken&amp;perf=%7B%22timing%22%3A%7B%22of%22%3A1402048474526%2C%20%22n%22%3A0%2C%20%22u%22%3A1%2C%20%22ue%22%3A1%2C%20%22dl%22%3A7%2C%20%22di%22%3A137%2C%20%22ds%22%3A137%2C%20%22de%22%3A852%2C%20%22dc%22%3A1105%2C%20%22l%22%3A1105%2C%20%22le%22%3A1106%2C%20%22f%22%3A0%2C%20%22dn%22%3A0%2C%20%22dne%22%3A0%2C%20%22c%22%3A0%2C%20%22ce%22%3A0%2C%20%22rq%22%3A0%2C%20%22rp%22%3A0%2C%20%22rpe%22%3A1%7D%2C%20%22navigation%22%3A%7B%7D%7D\"></script><script type=\"text/javascript\" src=\"https://js-agent.newrelic.com/nr-100.js\"></script><script type=\"text/javascript\" src=\"https://beacon-2.newrelic.com/1/89086e09bd?a=3098520&amp;be=3214&amp;qt=0&amp;ap=47&amp;dc=39&amp;fe=1063&amp;to=YlYGZEEEVhZWAkZcDlscIkVdBkwMWA8dUQtUXQNfHRNRAEASHFEEU1IRXEcWAhVWBldqD1pHO1ZcEFYB&amp;v=42&amp;jsonp=NREUM.setToken&amp;perf=%7B%22timing%22%3A%7B%22of%22%3A1402048511361%2C%20%22n%22%3A0%2C%20%22u%22%3A2%2C%20%22ue%22%3A2%2C%20%22dl%22%3A12%2C%20%22di%22%3A3255%2C%20%22ds%22%3A3255%2C%20%22de%22%3A3324%2C%20%22dc%22%3A4277%2C%20%22l%22%3A4277%2C%20%22f%22%3A0%2C%20%22dn%22%3A0%2C%20%22dne%22%3A0%2C%20%22c%22%3A0%2C%20%22ce%22%3A0%2C%20%22rq%22%3A0%2C%20%22rp%22%3A0%2C%20%22rpe%22%3A1%7D%2C%20%22navigation%22%3A%7B%22ty%22%3A1%7D%7D\"></script>\
<script type=\"text/javascript\" src=\"https://beacon-2.newrelic.com/1/89086e09bd?a=3098520&amp;be=3214&amp;qt=0&amp;ap=47&amp;dc=39&amp;fe=1063&amp;to=YlYGZEEEVhZWAkZcDlscIkVdBkwMWA8dUQtUXQNfHRNRAEASHFEEU1IRXEcWAhVWBldqD1pHO1ZcEFYB&amp;v=42&amp;jsonp=NREUM.setToken&amp;perf=%7B%22timing%22%3A%7B%22of%22%3A1402048511361%2C%20%22n%22%3A0%2C%20%22u%22%3A2%2C%20%22ue%22%3A2%2C%20%22dl%22%3A12%2C%20%22di%22%3A3255%2C%20%22ds%22%3A3255%2C%20%22de%22%3A3324%2C%20%22dc%22%3A4277%2C%20%22l%22%3A4277%2C%20%22le%22%3A4287%2C%20%22f%22%3A0%2C%20%22dn%22%3A0%2C%20%22dne%22%3A0%2C%20%22c%22%3A0%2C%20%22ce%22%3A0%2C%20%22rq%22%3A0%2C%20%22rp%22%3A0%2C%20%22rpe%22%3A1%7D%2C%20%22navigation%22%3A%7B%22ty%22%3A1%7D%7D\"></script><script type=\"text/javascript\" src=\"https://js-agent.newrelic.com/nr-100.js\"></script><script type=\"text/javascript\" src=\"https://beacon-2.newrelic.com/1/89086e09bd?a=3098520&amp;be=1666&amp;qt=0&amp;ap=47&amp;dc=1549&amp;fe=1606&amp;to=YlYGZEEEVhZWAkZcDlscIkVdBkwMWA8dUQtUXQNfHRNRAEASHFEEU1IRXEcWAhVWBldqD1pHO1ZcEFYB&amp;v=42&amp;jsonp=NREUM.setToken&amp;perf=%7B%22timing%22%3A%7B%22of%22%3A1402048647164%2C%20%22n%22%3A0%2C%20%22u%22%3A1%2C%20%22ue%22%3A1%2C%20%22dl%22%3A11%2C%20%22di%22%3A3224%2C%20%22ds%22%3A3224%2C%20%22de%22%3A3239%2C%20%22dc%22%3A3271%2C%20%22l%22%3A3271%2C%20%22f%22%3A0%2C%20%22dn%22%3A0%2C%20%22dne%22%3A0%2C%20%22c%22%3A0%2C%20%22ce%22%3A0%2C%20%22rq%22%3A0%2C%20%22rp%22%3A0%2C%20%22rpe%22%3A1%7D%2C%20%22navigation%22%3A%7B%22ty%22%3A1%7D%7D\"></script><script type=\"text/javascript\" src=\"https://beacon-2.newrelic.com/1/89086e09bd?a=3098520&amp;be=1666&amp;qt=0&amp;ap=47&amp;dc=1549&amp;fe=1606&amp;to=YlYGZEEEVhZWAkZcDlscIkVdBkwMWA8dUQtUXQNfHRNRAEASHFEEU1IRXEcWAhVWBldqD1pHO1ZcEFYB&amp;v=42&amp;jsonp=NREUM.setToken&amp;perf=%7B%22timing%22%3A%7B%22of%22%3A1402048647164%2C%20%22n%22%3A0%2C%20%22u%22%3A1%2C%20%22ue%22%3A1%2C%20%22dl%22%3A11%2C%20%22di%22%3A3224%2C%20%22ds%22%3A3224%2C%20%22de%22%3A3239%2C%20%22dc%22%3A3271%2C%20%22l%22%3A3271%2C%20%22le%22%3A3282%2C%20%22f%22%3A0%2C%20%22dn%22%3A0%2C%20%22dne%22%3A0%2C%20%22c%22%3A0%2C%20%22ce%22%3A0%2C%20%22rq%22%3A0%2C%20%22rp%22%3A0%2C%20%22rpe%22%3A1%7D%2C%20%22navigation%22%3A%7B%22ty%22%3A1%7D%7D\"></script><script type=\"text/javascript\" src=\"https://js-agent.newrelic.com/nr-100.js\"></script><script type=\"text/javascript\" src=\"https://beacon-2.newrelic.com/1/89086e09bd?a=3098520&amp;be=646&amp;qt=0&amp;ap=47&amp;dc=1&amp;fe=3589&amp;to=YlYGZEEEVhZWAkZcDlscIkVdBkwMWA8dUQtUXQNfHRNRAEASHFEEU1IRXEcWAhVWBldqD1pHO1ZcEFYB&amp;v=42&amp;jsonp=NREUM.setToken&amp;perf=%7B%22timing%22%3A%7B%22of%22%3A1402048745583%2C%20%22n%22%3A0%2C%20%22u%22%3A1%2C%20%22ue%22%3A1%2C%20%22dl%22%3A10%2C%20%22di%22%3A4234%2C%20%22ds%22%3A4234%2C%20%22de%22%3A4234%2C%20%22dc%22%3A4235%2C%20%22l%22%3A4235%2C%20%22f%22%3A0%2C%20%22dn%22%3A0%2C%20%22dne%22%3A0%2C%20%22c%22%3A0%2C%20%22ce%22%3A0%2C%20%22rq%22%3A0%2C%20%22rp%22%3A0%2C%20%22rpe%22%3A1%7D%2C%20%22navigation%22%3A%7B%22ty%22%3A1%7D%7D\"></script><script type=\"text/javascript\" src=\"https://beacon-2.newrelic.com/1/89086e09bd?a=3098520&amp;be=646&amp;qt=0&amp;ap=47&amp;dc=1&amp;fe=3589&amp;to=YlYGZEEEVhZWAkZcDlscIkVdBkwMWA8dUQtUXQNfHRNRAEASHFEEU1IRXEcWAhVWBldqD1pHO1ZcEFYB&amp;v=42&amp;jsonp=NREUM.setToken&amp;perf=%7B%22timing%22%3A%7B%22of%22%3A1402048745583%2C%20%22n%22%3A0%2C%20%22u%22%3A1%2C%20%22ue%22%3A1%2C%20%22dl%22%3A10%2C%20%22di%22%3A4234%2C%20%22ds%22%3A4234%2C%20%22de%22%3A4234%2C%20%22dc%22%3A4235%2C%20%22l%22%3A4235%2C%20%22le%22%3A4242%2C%20%22f%22%3A0%2C%20%22dn%22%3A0%2C%20%22dne%22%3A0%2C%20%22c%22%3A0%2C%20%22ce%22%3A0%2C%20%22rq%22%3A0%2C%20%22rp%22%3A0%2C%20%22rpe%22%3A1%7D%2C%20%22navigation%22%3A%7B%22ty%22%3A1%7D%7D\"></script></body></html>";


const char _html[]="<html> <head> <style> button { border: none; background-color: rgb(112, 101, 223); color: rgb(245, 255, 254); border-radius: 6px; opacity: 0.8; padding: 1%; margin:8px;font-size: 28; } .ti { text-align: center; } #getInfo{ font-family: Droid Sans Fallback; font-size: 28; margin: 5%; } #command, #info { margin-left: 5%; margin-right: 5%; padding: 3%; font-size: 28px; font-family: Droid Sans Fallback; border-style: solid; border-color: rgb(224, 238, 214); min-width: 400px; } input[type='checkbox'] { -webkit-appearance:none; width:28px; height:28px; background:white; border-radius:10px; background: #e88; border:4px solid #555; } input[type='checkbox']:checked { background: #7e7; } input { min-height: 2em; } </style> <script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js\"></script> <script> var auto = false; var timer; function fetch(){ $.getJSON(\"read\",function(list){ $.each(list, function(index, element){ console.log(index, element); $(\"#\"+index)[0].textContent = index+\" : \" + element; }); }); if (auto) timer = setTimeout(\"fetch()\", 1000); }; function command(s){ console.log(s); $.post(\"write\", s+'\\n'); }; $(document).ready(function(){ $(\"#main\").click(function(){ fetch(); $(\"#analog\")[0].style.display = \"\"; }); $(\"#auto\").click(function(){ auto = !auto; }); $(\"#set-pwm\")[0].onchange = function(){ command(JSON.stringify({setPWM:$(\"#set-pwm\")[0].value*100})); }; $(\"#cmd\").click(function(){ s={}; if ($(\"#set-time\")[0].value) s[\"setTime\"]=parseInt($(\"#set-time\")[0].value); if ($(\"#set-pwm\")[0].value) s[\"setPWM\"]=$(\"#set-pwm\")[0].value*100; if ($(\"#set-baud\")[0].value) s[\"setUARTBaud\"]=parseInt($(\"#set-baud\")[0].value); if ($(\"#send-uart\")[0].value) s[\"writeUART\"]=$(\"#send-uart\")[0].value; command(JSON.stringify(s)); }); }); </script> </head><body> <div id=\"getInfo\"> <button id=\"main\">get infomation</button> <input id=\"auto\" type=\"checkbox\" /> Auto refresh </div> <div id=\"info\" style=\"float:left\"> <p class='ti'>Information</p> <div id=\"analog\" style=\"display:none\"> <div id=\"Temperature\" style=\"float:left;display=\"></div>&nbsp;&#8451;<br> <div id=\"Voltage\" style=\"float:left\"></div>&nbsp;mV<br> <div id=\"Analog0\" style=\"float:left\"></div>&nbsp;(raw)<br> <div id=\"Analog1\" style=\"float:left\"></div>&nbsp;mV<br> <div id=\"Analog2\" style=\"float:left\"></div>&nbsp;mV<br> </div> <div id=\"time\"></div> <div id=\"uart\"></div> </div> <div id=\"command\" style=\"float:right\"> <p class='ti'>Command</p> <div style=\"float:left\"> Set uart baudrate:<br> Send via uart:<br> Set PWM:<br> Set clock:<br> </div> <div style=\"float:right\"> <input id=\"set-baud\" /> <br> <input id=\"send-uart\" /> <br> <input id=\"set-pwm\" type=\"range\"/><br> <input id=\"set-time\" /> <br> <button id=\"cmd\" style=\"float:right;padding: 6px\">commit</button> </div> </div> </body></html>";