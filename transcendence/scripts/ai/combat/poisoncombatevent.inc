include "include/attributes";
function process_combat_event(ev)

	DoPoison(ev.source);

        if (ev.type == EVID_DAMAGED)
		if ((GetHp(me) * 100/GetMaxHp(me)) < flee_point)
			flee(ev.source);
		endif
        endif

endfunction

function in_combat_event_loop(opponent, loops)

	DoPoison(opponent);

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

function DoPoison(you)

	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 10);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 10);

	if ( (Distance(me,you)<2) && (RandomInt(4)==1) )

	var p_level := CInt(GetMaxHp(me)/10);
	var poison_level := CInt(GetObjProperty(you, "poison_level"));

	if (p_level < poison_level)
		p_level := poison_level;
	else
		SendSysMessage(you, "You have been poisoned by " + me.name +"!");
		SetObjProperty(you, "poison_level",CStr(p_level));
	endif

	start_script( ":spells:poisondamage", you );

	endif

endfunction