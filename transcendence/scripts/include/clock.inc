use uo;
use cfgfile;

function GetTime()
  var cfg := ReadConfigFile( "::days" );
  var elem := FindConfigElem( cfg, "WholeDay" );
  var length := GetConfigInt( elem, "Length" );
  var day_length := (60 * length);
  var x := ReadGameClock();
  var bigpart := x / day_length;
  var smallpart := bigpart * day_length;
  x := (x - smallpart);
  return ( x );
endfunction

function GetTransition()
  var cfg := ReadConfigFile( "::days" );
  var elem := FindConfigElem( cfg, "Transition" );
  var length := GetConfigInt( elem, "Length" );
  return length;
endfunction

function GetDayLength()
  var cfg := ReadConfigFile( "::days" );
  var elem := FindConfigElem( cfg, "WholeDay" );
  var length := GetConfigInt( elem, "Length" );
  return length;
endfunction

function GetTimeofDay(realm := "britannia")
  var time_sec := GetTime();
  if(realm == "ilshenar")
   time_sec := GetIlshenarTimeOfDay(time_sec);
  endif
  var length := (GetDayLength() * 60) * 1.0;
  var temp := length / time_sec;
  var raw_time := 24.0 / temp;
  var hours := CInt(raw_time);
  var remainder := raw_time - hours;
  var minutes := CInt( remainder * 60 );
  if( len(CStr(minutes)) == 1 )
	minutes := "0" + CStr(minutes);
  endif
  if( len(CStr(hours)) == 1 )
	hours := "0" + CStr(hours);
  endif
  return (hours+":"+minutes);
endfunction

function GetIlshenarTimeOfDay(time)
if(time <= 1800)
 time := time + 1800;
else
 time := time - 1800;	
endif	 
return time;
endfunction

function GetHourOfDay()
  var time := GetTimeofDay();
  var colon := find(time, ":", 1);
  return CInt(time[1, colon]);
endfunction

function HourWithinRange(hr, hrstart, hrend)
  hr := CInt(hr) + 24;
  hrstart := CInt(hrstart) + 24;
  hrend := CInt(hrend) + 24;
  if (hrstart > hrend)
	if (hr >= hrstart || hr < hrend)
	  return 1;
	endif
  else
	if (hr >= hrstart && hr <= hrend)
	  return 1;
	endif
  endif
  return 0;
endfunction