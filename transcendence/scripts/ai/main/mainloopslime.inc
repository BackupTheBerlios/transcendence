function main_AI_loop(next_wander := 0)

    var ev;
    var wanders := 60;
    var next_loot := ReadGameClock() + 20;

    EnableMainEvents();

    while (1)

	if (ReadGameClock() > next_wander)
        	wander_around();
		next_wander := ReadGameClock()+1;
		wanders := wanders +1;
		if (wanders > 60)
			wanders :=0;
			ev := sleepmode();
    		endif
	else
		ev := os::wait_for_event( 3 );
	endif

        repeat

            case (ev.type)
                EVID_ENTEREDAREA:
                EVID_DAMAGED:
                EVID_ENGAGED:
                    Fight( ev.source );
                default:
		    process_noncombat_event(ev);
            endcase

        until (! (ev := os::wait_for_event(1)) );

   endwhile     

endfunction       

function look_around()

	return;

endfunction

function EnableMainEvents()

    cleareventque();
    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED );
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    cleareventque();
    DisableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction