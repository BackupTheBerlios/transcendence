include "include/speech";
include "include/particles";
function main_AI_loop(next_wander := 0)

    var ev;
    var wanders := 120;
    var next_loot := ReadGameClock() + 20;

    EnableMainEvents();

    while (1)

	if (ReadGameClock() > next_wander)
	if((Self().npctemplate == "pixie") || (Self().npctemplate == "smpixie")) 
		 
		 ParticleOnCharEffect(Self(), 9021, 3);
		 PlaySoundEffect( Self(), 0x473 );
		endif
		wander();
		
		
		next_wander := ReadGameClock()+3;
		wanders := wanders +1;
		if (wanders > 120)
			wanders :=0;
			ev := sleepmode();
    		endif
	else
		ev := os::wait_for_event( 3 );
	endif

	if (ev)
        repeat
            case (ev.type)
                EVID_ENTEREDAREA:
                   if(GetObjProperty(ev.source, "DarkAura"));
			 fight(ev.source);
	           endif
                EVID_SPEECH:
		    if (!ev.source.isA(POLCLASS_NPC))
		    	wanders :=0;
		    	next_wander := ReadGameClock()+30;
		    	check_speech(ev.text, ev.source);
				RespondToSpeech(me,ev.text);
		    endif
                EVID_ENGAGED:
                EVID_DAMAGED:
                    Fight( ev.source );
		EVID_ITEM_GIVEN:
		    next_wander := ReadGameClock()+60;
		    TakeItem(ev.source,ev.item);
            endcase
        until (! (ev := os::wait_for_event(3)) );
	endif

   endwhile     

endfunction       

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED );
    EnableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED, HALT_THRESHOLD );
    EnableEvents(EVID_ITEM_GIVEN);

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED );
    DisableEvents(EVID_ITEM_GIVEN);

endfunction