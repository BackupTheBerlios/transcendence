include "include/attributes";
function process_combat_event(ev)

        if (ev.type == EVID_DAMAGED)
		if ((GetHp(me) * 100/GetMaxHp(me)) < flee_point)
			flee(ev.source);
		elseif (GetHp(me) < GetMaxHp(me)/2)
			ApplyHealing();
		endif
	endif

endfunction

function in_combat_event_loop(opponent, loops)

	if ( loops > 100 )
		flee(opponent);
		return;
	endif

endfunction

function post_combat()

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	sleep(1);
	look_around();

endfunction

function prepare_for_fight(opponent)

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function ApplyHealing()

	if ( GetObjProperty(me,"#lasthealed") > ReadGameClock())
		SetHp(me, GetHp(me) + (RandomInt(GetMaxHp(me) - GetHp(me))+1));
		SetObjProperty(me,"#lasthealed", ReadGameClock()+20);
	endif

endfunction