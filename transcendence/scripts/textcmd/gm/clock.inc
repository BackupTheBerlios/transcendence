use uo;
use cfgfile;

function GetTime()

    var cfg := ReadConfigFile( "::days" );
    var elem := FindConfigElem( cfg, "WholeDay" );
    var length := GetConfigInt( elem, "Length" );
    var day_length := (60 * length);

//Print("DayLength: " + day_length);

    var x := ReadGameClock();

//Print("Read Game Clock: " + x);

    var bigpart := x / day_length;

//Print("Bigpart: " + bigpart);

    var smallpart := bigpart * day_length;
    x := (x - smallpart);

//Print("Time of Day: " + x);
//Print("The Day is " + day_length/60 + " minutes long.");

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

// Returns time in the format "hour:minutes", where hour = 00-23
function GetTimeofDay()

    var time_sec := GetTime();
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

// Returns a number of the hour of the day (1-24);
function GetHourOfDay()
    var time := GetTimeofDay();
    var colon := find(time, ":", 1);

	return CInt(time[1, colon]);
endfunction

function GetTimeofTheDay()

    var time_sec := GetTime();
    var length := (GetDayLength() * 60) * 1.0;

    var temp := length / time_sec;
    var raw_time := 24.0 / temp;

    var hours := CInt(raw_time);
   
    var remainder := raw_time - hours;
    var minutes := CInt( remainder * 60 );
     hours := hours - 5;
    if( len(CStr(minutes)) == 1 )
	minutes := "0" + CStr(minutes);
    endif

    if( len(CStr(hours)) == 1 )
	hours := "0" + CStr(hours);
    endif
   
    return (hours+":"+minutes);

endfunction
