function main_AI_loop()

    var ev;
    var wanders := 120;

    EnableMainEvents();

    while (1)

	wander();
	wanders := wanders +1;
        var a;
	for (a:=0; a<=RandomInt(5); a:=a+1);
	PerformAction(Self(), 0x0003);
	sleep(1);
	endfor
	if (wanders > 120)
		wanders :=0;
		ev := sleepmode();
	else
		ev := os::wait_for_event( 3 );
	endif

	if (ev)
        repeat
	    case (ev.type)
                EVID_DAMAGED:
                    Fight( ev.source );
                EVID_ENGAGED:
		    RunLikeHell( ev.source );
		EVID_ENTEREDAREA:
		    
                   if(GetObjProperty(ev.source, "DarkAura"));
			 fight(ev.source);
	           endif
                if (!ev.source.npctemplate)
                //SendAOSToolTipByName(ev.source, Self());
                endif    
            endcase
        until (! (ev := os::wait_for_event(3)) );
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
		    if ( RandomInt(3)==1 )
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

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction