function main_AI_loop()

    var ev;
    var wanders := 120;
    var hatelist := "animal cat barker tamed chicken sheep bird";

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
			if ( ( me.npctemplate == "dog" ) && (!ev.source.npctemplate) )
				case (RandomInt(2))
				0: PlaySoundEffect(me,0x86);
				1: PlaySoundEffect(me,0x87);
				endcase
			elseif ( (me.graphic == 0xe1)  && (!ev.source.npctemplate) )
			  PlaySoundEffect(me, 0x00e7);
			elseif ( (ev.source.script) && ( hatelist[ev.source.script] ) )
			    get_help( ev.source );
	                    Fight( ev.source );
			endif
                EVID_DAMAGED:
                EVID_ENGAGED:
		    get_help( ev.source );
                    Fight( ev.source );
		EVID_ALL_ATTACK_CMD:
                    Fight( ev.source );
            endcase
        until (! (ev := os::wait_for_event(1)) );
	endif

   endwhile     

endfunction       

function look_around()

	var hatelist := "animal cat barker tamed chicken sheep bird";
	foreach critter in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
		if ( (critter.script) && ( hatelist[critter.script] ) )
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

function get_help( opponent )

	var ev array;
	ev.+type := EVID_ALL_ATTACK_CMD;
	ev.+source := opponent;

	foreach critter in ListMobilesNearLocation( me.x, me.y, me.z, HALT_THRESHOLD, me.realm )
		if ( (critter.npctemplate == me.npctemplate) && (critter.script != "tamed") && (!critter.warmode) )
			SendEvent(critter, ev);
		endif
	endforeach

endfunction
