function checktemperature(who)
var rawtemp := GetGlobalProperty("rawtemp");
var temperature;
if (who.y <= 640)
 temperature := rawtemp - 20;
elseif ((who.y >= 641) && (who.y <= 1840))
 temperature := rawtemp - 10;
elseif ((who.y >= 1841) && (who.y <= 2530))
 temperature := rawtemp;
elseif ((who.y >= 2531) && (who.y <= 3155))
 temperature := rawtemp + 10;
elseif (who.y >= 3156)
 temperature := rawtemp + 15;
endif
return temperature;
endfunction