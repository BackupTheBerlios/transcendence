const GFX_UNSHORN_SHEEP := 0xcf;
const GFX_SHORN_SHEEP := 0xdf;

include "include/attributes";
function main_AI_loop()

    var ev;
    var wanders := 120;
    var next_wander := 0;
    var next_regrow := ReadGameClock() + 1800;
    var nextbark := ReadGameClock() + 30;

    EnableMainEvents();

    while (1)

	if (ReadGameClock() > next_wander)
		wander();
		next_wander := ReadGameClock()+5;
		wanders := wanders +1;
		if (wanders > 120)
			wanders :=0;
			ev := sleepmode();
	    	endif
	else
		ev := os::wait_for_event( 5 );
	endif

	if (ev)
        repeat
	    case (ev.type)
                EVID_DAMAGED:
                EVID_ENTEREDAREA:
			if ( ( me.npctemplate == "sheep" ) && (!ev.source.npctemplate) )
				case (RandomInt(2))
				 0: PlaySoundEffect(me,0xd7);
				 1: PlaySoundEffect(me,0xd8);
			        endcase
			endif
			if(GetObjProperty(ev.source, "DarkAura"));
			 fight(ev.source);
			endif
                EVID_ENGAGED:
		    RunLikeHell( ev.source );
            endcase
        until (! (ev := os::wait_for_event(1)) );
	endif

	if (ReadGameClock() > next_regrow)
		next_regrow := ReadGameClock()+1800;
		if ( me.graphic == GFX_SHORN_SHEEP )
			me.graphic := GFX_UNSHORN_SHEEP;
		endif
		if ( RandomInt(1000)==1 )
			Damage( me, GetMaxHp(me) + 3 );
		endif
	endif

	if ( ReadGameClock() > nextbark )
		nextbark := ReadGameClock() + ( (RandomInt(5)+1) * 60 );
		case (RandomInt(2))
		0: PlaySoundEffect(me,0xd7);
		1: PlaySoundEffect(me,0xd8);
		endcase
	endif

   endwhile     

endfunction       

function RunLikeHell(opponent)

	var ev;
	while ( (opponent) && not
	    (opponent.dead || opponent.hidden || opponent.concealed) &&
	    (dist(me,opponent) < 25) )

	    RunAwayFrom( opponent );

        repeat
	    case (ev.type)
                EVID_DAMAGED:
		    if ( RandomInt(3) == 1 )
                    	Fight( ev.source );
		    	return;
                    endif
            endcase
        until (! (ev := os::wait_for_event(1)) );

	endwhile

endfunction

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_ENTEREDAREA + EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED);
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_ENGAGED + EVID_DAMAGED);

endfunction