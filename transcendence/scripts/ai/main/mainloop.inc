function main_AI_loop(next_wander := 0)

    var ev;
    var looter := GetObjProperty( me, "looter" );
    var wanders := 60;
    var next_loot := ReadGameClock() + 20;
    look_around();

    EnableMainEvents();

    while (1)

	if (ReadGameClock() > next_wander)
       		wander();
		if ( (looter) && (ReadGameClock() > next_loot) )
			grabloot();
			next_loot := ReadGameClock() + 10;
		endif
		next_wander := ReadGameClock()+1;
		wanders := wanders +1;
		if (wanders > 60)
			wanders :=0;
			ev := sleepmode();
	    	endif
	else
		ev := os::wait_for_event( 1 );
	endif

        repeat

            case (ev.type)
                EVID_ENGAGED:
                EVID_DAMAGED:
		    Fight( ev.source );
                EVID_ENTEREDAREA:
                    if ((!ev.source.npctemplate) || (ev.source.script == "tamed") )
			Fight( ev.source );
                    endif
                default:
                        process_noncombat_event(ev);
            endcase

        until (! (ev := os::wait_for_event(1)) );

   endwhile     

endfunction

function look_around()

	foreach critter in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
          if ((!critter.npctemplate) || (critter.script == "tamed") )
                    Fight( critter );
		    return;
          endif
	endforeach

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