const GFX_UNSHORN_SHEEP := 0xcf;
const GFX_SHORN_SHEEP := 0xdf;

function main_AI_loop()

    var ev;
    var wanders := 120;
    var nextlay := CInt(ReadGameClock() + 3600);
    var nextbark := ReadGameClock() + 30;
    var next_wander := 0;

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
                EVID_ENGAGED:
		    RunLikeHell( ev.source );
            endcase
        until (! (ev := os::wait_for_event(5)) );
	endif

	if (ReadGameClock() > nextlay)
		nextlay := ReadGameClock()+ 2600 + CInt(3800*RandomInt(2));
		CreateItemAtLocation(me.x, me.y, me.z,"egg",1, me.realm);
	endif

	if ( ReadGameClock() > nextbark )
		nextbark := ReadGameClock() + ( (RandomInt(5)+1) * 60 );
		PlaySoundEffect(me,0x70);
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
        until (! (ev := os::wait_for_event(1)) );

	endwhile

endfunction

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED + EVID_ENTEREDAREA);
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction