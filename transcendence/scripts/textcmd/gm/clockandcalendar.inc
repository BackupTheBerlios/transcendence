// Calendar system made by Artix 28/07/01 //


function getdate(char, modo)
var wstuff := GetGlobalProperty("Weather");
var day := wstuff[1];
var rawmonth := wstuff[2];
var month;
var season:= wstuff[8];
var year := wstuff[9];

if ((season == 0) && (rawmonth <= 3 ))
month := 1;
elseif ((season == 0) && (rawmonth >= 3))
month := 2;
elseif ((season == 1) && (rawmonth <= 3))
month := 3;
elseif ((season == 1) && (rawmonth >= 3))
month := 4;
elseif ((season == 2) && (rawmonth <= 3))
month := 5;
elseif ((season == 2) && (rawmonth >= 3))
month := 6;
elseif ((season == 3) && (rawmonth <= 3))
month := 7;
elseif ((season == 3) && (rawmonth >= 3))
month := 8;
endif

if ((rawmonth == 0) || (rawmonth == 4))
day := day + 1;
elseif ((rawmonth == 1) || (rawmonth == 5))
day := day + 9;
elseif ((rawmonth == 2) || (rawmonth == 6))
day := day + 17;
elseif ((rawmonth == 3) || (rawmonth == 7))
day := day + 25;
endif

day := CStr(day);
month := CStr(month);
year := CStr(year);
if (modo == "s")
SendSysMessage(char, day+"/"+month+"/"+year, FONT_NORMAL, 0x005a);
elseif (modo == "c")
SendSysMessage(char, "Today is day "+day+" of month "+month+" of Year "+year, FONT_NORMAL, 0x005a);
endif
return day+month+year;

endfunction



