


function getdate(char, modo)
var wstuff := GetGlobalProperty("Weather");
var day := wstuff.FPhase;
var rawmonth := wstuff.TPhase;
var month;
var season:= wstuff.season;
var year := wstuff.year;

if ((season == 0) && (rawmonth < 5))
month := 1;
elseif ((season == 0) && (rawmonth > 5))
month := 2;
elseif ((season == 1) && (rawmonth < 5))
month := 3;
elseif ((season == 1) && (rawmonth > 5))
month := 4;
elseif ((season == 2) && (rawmonth < 5))
month := 5;
elseif ((season == 2) && (rawmonth > 5))
month := 6;
elseif ((season == 3) && (rawmonth < 5))
month := 7;
elseif ((season == 3) && (rawmonth > 5))
month := 8;
endif

day := CStr(day);
month := CStr(month);
year := CStr(year);
if (modo == "s")
SendSysMessage(char, day+"/"+month+"/"+year, FONT_NORMAL, 90);
elseif (modo == "c")
SendSysMessage(char, "Today is day "+day+" of month "+month+" of Year "+year, FONT_NORMAL, 90);
endif
return day+month+year;

endfunction



