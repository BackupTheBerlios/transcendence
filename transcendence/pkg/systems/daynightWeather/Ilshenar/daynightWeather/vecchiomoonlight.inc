// 23/4/00 original scripts by Mad & Rac, adjusted considerably by Rax

function DoMoons(wstuff)

var fphase := wstuff[1];
var tphase := wstuff[2];
var season := wstuff[8];
var year := wstuff[9];
fphase := fphase + 1;
if (fphase == 8)
	fphase := 0;
	tphase := tphase +1;
endif
wstuff[1] := fphase;
//wstuff[2] := TPhase;
if (tphase == 8)
	tphase := 0;
	season := season + 1;
	if (season == 4)
		season := 0;
	        year := year+1;
	endif

	case(season)
		0: Broadcast("The warmth of summer envelopes the land");
		1: Broadcast("Leaves begin to fall as Autumn appears");
		2: Broadcast("Winters cold hand touches the land");
		3: Broadcast("Winters touch thaws as Spring arrives");
	endcase



endif
wstuff[2] := tphase;
wstuff[8] := season;
wstuff[9] := year;
print("New Day.Felucca Phase: "+CStr(wstuff[1])+" ,Trammel Phase: "+ CStr(wstuff[2]));
SetGlobalProperty("Weather", wstuff);

endfunction

function ChangeMoonLightSet(wstuff)

var tlight := FindLight(wstuff[2]);
var flight := FindLight(wstuff[1]);
var mlight := (tlight + flight);
var moonlight := (mlight / 2);
wstuff[5] := (27 - moonlight);

endfunction

function DuskTransition(wstuff)

var dlight := wstuff[4];
var mlight := wstuff[5];
var inter_level_time := (CInt(transtime / (mlight - dlight)));
var lightamt := dlight;

while( lightamt <= mlight )
	wstuff := GetGlobalProperty("Weather");
	lightamt := lightamt + 1;
	SetRegionLightLevel("Background", lightamt);
	wstuff[6] := lightamt;
	SetGlobalProperty("Weather", wstuff);
        sleep(inter_level_time);
endwhile

endfunction

function DawnTransition(wstuff)

var dlight := wstuff[4];
var mlight := wstuff[5];
var inter_level_time := (CInt(transtime / (mlight - dlight)));
var lightamt := mlight;

while( lightamt >= dlight )
	wstuff := GetGlobalProperty("Weather");
	lightamt := lightamt - 1;
	SetRegionLightLevel("Background", lightamt);
	wstuff[6] := lightamt;
	SetGlobalProperty("Weather", wstuff);
        sleep(inter_level_time);
endwhile

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