include "include/attributes";
function Fight( opponent )

	if ((opponent.cmdlevel > 0) || (opponent.serial == me.serial))
        	SetWarMode(0);
        	opponent := 0;
		return;
	endif

	if (opponent.multi.serial)
		if (me.multi.serial != opponent.multi.serial)
			flee(opponent);
			return;
		endif
	endif

	var oldprio := set_priority(50);

	SetOpponent( opponent );
    	prepare_for_fight( opponent );
	TurnToward( opponent );

	var loops := 0;
    	var ev;
	var waittime := 0;

    while ( (opponent) && not
	    (opponent.dead || opponent.hidden || opponent.concealed) &&
	    (dist(me,opponent) < 25) )

	if (!CloseDistance( opponent ) )
		loops := loops + 1;
		waittime := 0;
	else
		loops := 0;
		waittime := 1;
	endif

	in_combat_event_loop(opponent, loops);

	ev := wait_for_event( waittime );
	case (ev.type)
                EVID_DAMAGED:
		EVID_ENGAGED:
			if (ev.source)
			  process_combat_event(ev);
			  if (RandomInt(6)==1)
				if ((!ev.source.npctemplate) || (ev.source.script == "tamed") )
					opponent := ev.source;
			  		SetOpponent( opponent );
					TurnToward( opponent );
				endif
			  endif
			endif
                EVID_PEACEMADE:
			SetWarMode( 0 );
			SetOpponent( 0 );
			sleep(1);
			DisableCombatEvents();
			EnableMainEvents();
			return;
	endcase

    endwhile

    post_combat();
     
endfunction

function EnableCombatEvents()

    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_PEACEMADE );

endfunction

function DisableCombatEvents()

    DisableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_PEACEMADE );

endfunction

function flee(opponent)

	if (me.script == "immobile")
		sleep(2);
		return;
	endif

	var numflees := GetObjProperty(me,"#flees");

	if (numflees)
		if ( numflees > 5 )
		        if(me.realm == "britannia")
			 MoveCharacterToLocation(me,5288,1176,0,MOVECHAR_FORCELOCATION);
			else
			 MoveObjectToRealm(me, "britannia", 5288,1176,0,MOVECHAR_FORCELOCATION);	
			endif	 
			SetObjProperty(me,"guardkill",1);
			Damage( me, GetMaxHp(me) + 3 );
		else
			numflees := numflees + 1;
		endif
	else
		numflees := 1;
	endif

	SetObjProperty(me,"#flees",numflees);

	var runs := 0;
	while ( (Distance(me, opponent) < 20) && (runs < 50) )
		RunAwayFrom(opponent);
		runs := runs +1;
		wait_for_event(0);
	endwhile

	RestartScript( me );

endfunction