// 23/4/00 original scripts by Mad & Rac, adjusted considerably by Rax

function DoMoons(wstuff)

var fphase := wstuff.FPhase;
var tphase := wstuff.TPhase;
var season := wstuff.season;
var year := wstuff.year;
fphase := fphase + 1;
if (fphase == 8)
	fphase := 0;
	tphase := tphase +1;
endif
wstuff.FPhase := fphase;
//wstuff[2] := TPhase;
if (tphase == 8)
	tphase := 0;
	season := season + 1;
	if (season == 4)
		season := 0;
	        year := year+1;
	        var rnd := RandomInt(100);
	         if (rnd < 10)
	          var intensity := RandomDiceRoll("1d10 + 10");
	          var parms := {1, intensity};
	          SetGlobalProperty("Glaciation", parms);
	         elseif (rnd > 93)
	          SetGlobalProperty("Siccity", 1);
	         endif
	endif

	case(season)
		0: 
		   //Broadcast("The warmth of summer envelopes the land", 3, 2432);
		   BroadCastCustomMsgByLang(  "The warmth of summer envelopes the land.", "E' arrivata l'estate.", 2432, 3, "britannia");
		   //SetSeasonForAll( SEASON_SUMMER );
		   SetSeasonForRealm( SEASON_SUMMER, "britannia" );
		1: 
		   //Broadcast("Leaves begin to fall as Autumn appears", 3, 42);
		   BroadCastCustomMsgByLang(  "Leaves begin to fall as Autumn appears.", "E' arrivato l'autunno.", 42, 3, "britannia");
		   //SetSeasonForAll( SEASON_FALL );
		   SetSeasonForRealm( SEASON_FALL, "britannia" );
		2: 
		   BroadCastCustomMsgByLang(  "Winters cold hand touches the land.", "E' arrivato l'inverno.", 1153, 3, "britannia");
		   //Broadcast("Winters cold hand touches the land", 3, 1153);
		   //SetSeasonForAll( SEASON_FALL );
		   SetSeasonForRealm( SEASON_FALL, "britannia" );
		3: //Broadcast("Winters touch thaws as Spring arrives", 3, 90);
		   BroadCastCustomMsgByLang(  "Winters touch thaws as Spring arrives.", "E' arrivata la primavera.", 90, 3, "britannia");
		   //SetSeasonForAll( SEASON_SPRING );
		   SetSeasonForRealm( SEASON_SPRING, "britannia" );
	endcase



endif
wstuff.TPhase := tphase;
wstuff.season := season;
wstuff.year := year;
print("New Day.Felucca Phase: "+CStr(wstuff.FPhase)+" ,Trammel Phase: "+ CStr(wstuff.TPhase));
SetGlobalProperty("Weather", wstuff);
return wstuff;
endfunction

function ChangeMoonLightSet(wstuff)

var tlight := FindLight(wstuff.TPhase);
var flight := FindLight(wstuff.FPhase);
var mlight := (tlight + flight);
var moonlight := (mlight / 2);
wstuff.moonlight := (27 - moonlight);
SetGlobalProperty("Weather", wstuff);

endfunction

function DuskTransition(wstuff)

var vartranstime;
var stagione := wstuff.season;
         case (stagione)
           0 : vartranstime := transtime - 300;
           1 : vartranstime := transtime;
	   2 : vartranstime := transtime + 300;
	   3 : vartranstime := transtime;
	 endcase
var dlight := wstuff.daylight;
var mlight := wstuff.moonlight;
var inter_level_time := (CInt(vartranstime / (mlight - dlight)));
var at_time := lunghezza - vartranstime;
var lightamt := dlight + GetTransitionTime(inter_level_time, at_time);

while( lightamt <= mlight )
	wstuff := GetGlobalProperty("Weather");
	lightamt := lightamt + 1;
	SetRegionLightLevel("Background", lightamt);
	wstuff.lightlevel := lightamt;
	SetGlobalProperty("Weather", wstuff);
        sleep(inter_level_time / 2);
endwhile
Broadcast("It's evening.", 3, 99);
SetRegionLightLevel("Background", mlight);
start_script("modifysky", {4});
var the_time := GetTime();
sleep(lunghezza - the_time);
endfunction

function DawnTransition(wstuff)

var dlight := wstuff.daylight;
var mlight := wstuff.moonlight;
var inter_level_time := (CInt(transtime / (mlight - dlight)));
var lightamt := mlight - GetTransitionTime(inter_level_time, transtime);

while( lightamt >= dlight )
	wstuff := GetGlobalProperty("Weather");
	lightamt := lightamt - 1;
	SetRegionLightLevel("Background", lightamt);
	wstuff.lightlevel := lightamt;
	SetGlobalProperty("Weather", wstuff);
        sleep(inter_level_time / 2);
endwhile
Broadcast("It's Morning.", 3, 91);
SetRegionLightLevel("Background", dlight);
var midday := lunghezza / 2;
var thetime := GetTime();
sleep(midday - thetime);
endfunction

function FindLight(phase)

case(phase)
	0: return 0;
	1: return 1;
	2: return 2;
	3: return 3;
	4: return 4;
	5: return 3;
	6: return 2;
	7: return 1;
endcase

endfunction

function GetTransitionTime(leveltime, transtime)

var moment := GetTime();
var diff := moment - transtime;

var timetrans := leveltime / 2; //only for my changes in dawn duration *** solo per i miei cambiamenti alla durata dell'alba
var amount := CInt(diff / timetrans);
return amount;

endfunction


