include ":DaemonProcesses:processes";
include ":ilshenar_daynight:moonlight";

function ChangeWeather()

wstuff := GetGlobalProperty("Weather2");
var pweather := wstuff.type;
var season := wstuff.season;
var incdec := RandomInt(4);

case(season)
	0: incdec := incdec - 1;
	1: incdec := incdec;
	2: incdec := incdec + 1;
	3: incdec := incdec;
endcase

if (incdec <= 1)
	pweather := pweather - 1;
	if (pweather < 0)
		pweather := 0;
	endif
endif
if (incdec == 2)
	return;
endif
if (incdec >= 3)
	pweather := pweather + 1;
	if (pweather >4)
		pweather := 4;
	endif
endif

var pweathercheck := wstuff.type;

if (pweathercheck == pweather)
	if (doonce == 1)
		return;
	endif
endif

doonce := 1;

wstuff.type := pweather;
SetGlobalProperty("Weather2", wstuff);
case(pweather)
	0: SetSunny();
	1: SetOvercast();
	2: SetCloudy();
	3: SetRain();
	4: SetThunder();
endcase

SetGlobalProperty("Weather2", wstuff);
print("Ilshenar Weather Changed.");
endfunction

function SetSunny()

wstuff := GetGlobalProperty("Weather2");
wstuff.daylight := 0;
//Broadcast("The skies are clear", 3, 95);
BroadCastCustomMsgByLang(  "The skies are clear.", "Il cielo è sereno.", 95, 3, "ilshenar");
var is_day := wstuff.isDay;
var time := GetIlshenarTime(cint(GetTime()));
if (is_day == 1) 
	SetRegionLightLevel( "Ilshenar", 0);
	wstuff.lightlevel := 0;
endif
if ((time >= 1380 )&& (time < 1800))
SetRegionLightLevel( "Ilshenar", 0);
	wstuff.lightlevel := 0;
endif
SendFogToWeather( 0, 0, 0, 0);
SetGlobalProperty( "Weather2", wstuff );
endfunction

function SetOvercast()

wstuff := GetGlobalProperty("Weather2");
wstuff.daylight := 2;
//Broadcast("The skies are overcast", 3, 101);
BroadCastCustomMsgByLang(  "The skies are overcast.", "Il cielo è coperto.", 101, 3, "ilshenar");
var is_day := wstuff.isDay;
var time := GetIlshenarTime(cint(GetTime()));
var rand := randomint(100);
if(rand > 40)
 if(rand > 75)
  SendFogToWeather( 2, 0, 80, 100);
 else
  SendFogToWeather( 1, 3, 0, 0);
 endif	
else
 SendFogToWeather( 0, 0, 0, 0);	
endif
if (is_day == 1)
	SetRegionLightLevel( "Ilshenar", 2);
	wstuff.lightlevel := 2;
endif
if ((time >= 1380 )&& (time < 1800))
SetRegionLightLevel( "Ilshenar", 2);
	wstuff.lightlevel := 2;
endif

endfunction

function SetCloudy()

wstuff := GetGlobalProperty("Weather2");
wstuff.daylight := 4;
SetRegionWeatherLevel( "Ilshenar", 0, 0, 1, -1);
//Broadcast("The skies blacken, but at least it's not raining", 3, 1154);
BroadCastCustomMsgByLang(  "The skies blacken, but at least it's not raining.", "Il cielo è nuvoloso.", 1154, 3, "ilshenar");
var is_day := wstuff.isDay;
var time := GetIlshenarTime(cint(GetTime()));
var rand := randomint(100);
if(rand > 40)
 if(rand > 75)
  SendFogToWeather( 2, 0, 80, 100);
 else
  SendFogToWeather( 1, 3, 0, 0);
 endif	
else
 SendFogToWeather( 0, 0, 0, 0);	
endif
if (is_day == 1)
	SetRegionLightLevel( "Ilshenar", 4);
	wstuff.daylight := 4;
	wstuff.skytype := 5;
	start_script("modifysky", {5});
endif
if ((time >= 1380 )&& (time < 1800))
SetRegionLightLevel( "Ilshenar", 4);
	wstuff.daylight := 4;
	wstuff.skytype := 5;
	start_script("modifysky", {5});
endif


endfunction

function SetRain()

wstuff := GetGlobalProperty("Weather2");
wstuff.daylight := 6;
//Broadcast("It starts to rain", 3, 93);
BroadCastCustomMsgByLang(  "It starts to rain", "Sta piovendo.", 93, 3, "ilshenar");
var is_day := wstuff.isDay;
var time := GetIlshenarTime(cint(GetTime()));
if (is_day == 1)
	SetRegionLightLevel("Ilshenar", 6);
	wstuff.daylight := 6;
	wstuff.skytype := 5;
	start_script("modifysky", {5});
endif
if ((time >= 1380 )&& (time < 1800))
SetRegionLightLevel( "Ilshenar", 6);
	wstuff.daylight := 6;
	wstuff.skytype := 5;
	start_script("modifysky", {5});
endif
//var glaciation := GetGlobalProperty("Glaciation");



 /*
if (GetGlobalProperty("Siccity") == 1)
 return;
endif

 if (glaciation[1] == 1)
   if (glaciation[2] <= 10)
      start_script( "snowrain", 30);
     
   elseif (glaciation[2] > 10)
      start_script("snow");
    endif
elseif (!glaciation)*/
  start_script( "snowrain", 15);
//endif


endfunction			

function SetThunder()

wstuff := GetGlobalProperty("Weather2");
wstuff.daylight := 8;
//Broadcast("A storm rages overhead", 3, 98);
BroadCastCustomMsgByLang(  "A storm rages overhead", "E' arrivata una tempesta", 98, 3, "ilshenar");
var is_day := wstuff.isDay;
var time := GetIlshenarTime(cint(GetTime()));
if (is_day == 1)
	SetRegionLightLevel("Ilshenar", 8);
	wstuff.lightlevel := 8;
	wstuff.skytype := 5;
endif
if ((time >= 1380 )&& (time < 1800))
SetRegionLightLevel( "Ilshenar", 8);
	wstuff.lightlevel := 8;
	wstuff.skytype := 5;
endif
/*
var glaciation := GetGlobalProperty("Glaciation");

  if (GetGlobalProperty("Siccity") == 1)
   return;
  endif
if (glaciation[1] == 1)
 if (glaciation[2] <= 10)
   start_script( "weffect" );
   start_script( "snowrain", 30);
   return;
 elseif (glaciation[2] > 10)
  start_script( "weffect" );
  start_script("snow");
  return;
 endif
elseif (!glaciation)
*/
start_script( "weffect" );
start_script( "snowrain", 30);
//endif

endfunction

function SendFogToWeather( fogtype, density, fogstart, fogend)

var ev := struct;
//ev.+region := region;
ev.+type := fogtype;
ev.+density := density;
ev.+start := fogstart;
ev.+fogend := fogend;

var pid := GetDaemonPID("FogManagerDaemon2");

var script := getprocess(pid); 

pid.sendevent(ev);

endfunction