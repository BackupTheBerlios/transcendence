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

        cast_meteor(me);

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


function cast_meteor( caster )

	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 10);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 10);

	if (RandomInt(3) != 1)
		return;
	endif

    var parms array;

    var targets := ListMobilesInLineOfSight(me, 4);
    PerformAction(me,0x0c);

    foreach mobile in targets
      if ( (!mobile.npctemplate || mobile.script == "tamed") && (!mobile.cmdlevel))
	   var dmg := RandomInt((CInt( CInt(GetMaxHp(me)/2.5) * GetHp(me))/GetMaxHp(me)))+5;
	   PlayMovingEffect(caster, mobile,MOVING_EFFECT_FIREBALL, 10,1,1);
	   ApplyDamage(mobile, dmg);          
      endif
    endforeach

endfunction