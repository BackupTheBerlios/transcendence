include "include/attributes";
function process_combat_event(ev)

	spellattack(ev.source);

	case (ev.type)
        	EVID_DAMAGED:
			if ( GetHp(me) < (GetStrength(me)/2))
				CastSpell(me,me,"gheal");
				if( CInt(GetObjProperty(me, "poison_level")) > 1)
					CastSpell(me,me,"cure");
					CastSpell(me,ev.source,"poison");
				endif
			endif
                        if ((GetHp(me) * 100/GetMaxHp(me)) < flee_point)
                                flee(ev.source);
                        endif
			break;
        	default: break;
	endcase

endfunction

function spellattack(opponent)

	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	if (RandomInt(2)==1)
		sleep(1);
		cast_offensive_spell(me,opponent);
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);

endfunction

function in_combat_event_loop(opponent, loops)

	spellattack(opponent);

	if ( loops > 100 )
		flee(opponent);
		return;
	endif

endfunction

function prepare_for_fight(opponent)

	if (!CInt(GetObjProperty(me, "mr")))
		CastSpell(me,me,"reflect");
	endif

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function post_combat()

	if ( GetHp(me) < (GetStrength(me)/2))
		CastSpell(me,me,"gheal");
	endif

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	summons := 1;

	sleep(1);
	look_around();
 
endfunction