include "include/attributes";
function process_combat_event(ev)

	send_web(ev.source);

        if (ev.type == EVID_DAMAGED)
		if ((GetHp(me) * 100/GetMaxHp(me)) < flee_point)
			flee(ev.source);
		endif
        endif

endfunction

function in_combat_event_loop(opponent, loops)

	send_web(opponent);

	if ( loops > 100 )
		flee(opponent);
		return;
	endif

endfunction      



function post_combat()

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	num_casts := 2;

	sleep(1);
	look_around();
  
endfunction

function prepare_for_fight(opponent)

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function send_web(opponent)

	if (RandomInt(20) != 1)
		return;
	endif

	if (!CheckLineOfSight( me, opponent ))
		return;
	endif

PrintTextAbove(me, "The spider spits a web!");

//	-causes client crash-
//
//PlayMovingEffectXYZ( me.x, me.y, me.z,
//                         opponent.x, opponent.y, opponent.z,
//                         UOBJ_SPIDERWEB, 8, 0, 0 );
//
//	-causes client crash-

sleepms(1250);
CreateItemAtLocation(opponent.x, opponent.y, opponent.z,UOBJ_SPIDERWEB,  1, opponent.realm);

endfunction