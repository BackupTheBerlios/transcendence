include "include/attributes";
function process_combat_event(ev)

	spellattack(ev.source);
        if (ev.type == EVID_DAMAGED)
		if ((GetHp(me) * 100/GetMaxHp(me)) < flee_point)
			flee(ev.source);
		endif
        endif

endfunction

function spellattack(opponent);

	if (Distance(me,opponent) < 2)
		var opmagery := CInt(GetEffectiveSkill(opponent,SKILLID_MAGERY));
		ApplyRawDamage(opponent, RandomInt(CInt(opmagery/15)) );
	endif

endfunction

function in_combat_event_loop(opponent, loops)

	spellattack(opponent);

	if ( loops > 100 )
		flee(opponent);
		return;
	endif
        
endfunction

function prepare_for_fight(opponent)

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function post_combat()

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	sleep(1);
	look_around();

endfunction