function main_AI_loop()

    var ev;
    var wanders := 120;
    var hatelist := "bird eagle rat chicken";

    EnableMainEvents();

    while (1)

	wander();
	wanders := wanders +1;

	if (wanders > 120)
		wanders :=0;
		ev := sleepmode();
	else
		ev := os::wait_for_event( 2 );
	endif

	if (ev)
        repeat
	    case (ev.type)
		EVID_ENTEREDAREA:
		    if (!ev.source.isA(POLCLASS_NPC))
		    	PlaySoundEffect(me, 0x6b);
		    elseif ( hatelist[ev.source.npctemplate] )
	            	Fight( ev.source );
		    endif
		    
                    if(GetObjProperty(ev.source, "DarkAura"));
			 fight(ev.source);
	            endif
                EVID_DAMAGED:
                EVID_ENGAGED:
                    Fight( ev.source );
            endcase
        until (! (ev := os::wait_for_event(2)) );
	endif

   endwhile     

endfunction       

function look_around()

	var hatelist := "bird eagle rat chicken";
	foreach critter in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
		if ( (critter.npctemplate) && ( hatelist[critter.npctemplate] ) )
			Fight( critter );
			return;
		endif
	endforeach

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED);
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction