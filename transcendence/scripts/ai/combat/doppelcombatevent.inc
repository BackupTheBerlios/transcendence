include "include/attributes";
function process_combat_event(ev)

	spellattack(ev.source);
        case (ev.type)
                EVID_DAMAGED:
			check_for_change();
                       	if (will_cast)
                       		if ( GetHp(me) < (GetStrength(me)/2))
                                	CastSpell(me,me,"gheal");
					if( CInt(GetObjProperty(me, "poison_level")>1) )
						CastSpell(me,me,"cure");
                       			endif
                       		endif
                       	endif
                        if ((GetHp(me) * 100/GetMaxHp(me)) < flee_point)
                                flee(ev.source);
                        endif
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
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);
	elseif ( (will_breathe) && (RandomInt(3) == 1) )
		breathe_meteor(me);
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 10);
	else
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);
        endif

	check_for_change();

endfunction

function in_combat_event_loop(opponent, loops)

	spellattack(opponent);

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

	summons := 1;

	sleep(1);
	look_around();

endfunction

function prepare_for_fight(opponent)

	if (GetObjProperty(me, "mr") != "1")
		SetObjProperty(me, "mr", "1");
	endif

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function breathe_meteor( caster )
    var parms := array;
   

    var targets := ListMobilesInLineOfSight(me, 4);
    PerformAction(me,0x0c);

    foreach mobile in targets
     
	   var dmg := RandomInt((CInt(70* GetHp(me))/GetMaxHp(me)))+5;
	   PlayMovingEffect(caster, mobile,MOVING_EFFECT_FIREBALL, 10,1,1);
	   ApplyDamage(mobile, dmg);         

    endforeach


endfunction


function check_for_change()

if (GetHp(me) < (GetStrength(me) /5))
        if (num_changes >= len(graphics))
                return;
        else
                num_changes := num_changes + 1;
                SetHp(me, me.strength);
                var parm := SplitWords(graphics[num_changes]);
                var form := CInt(parm[1]);
                print("graphic is " + form);
                var clr := CInt(parm[2]);
                will_cast := CInt(parm[4]);
                will_breathe := CInt(parm[3]);
                me.graphic := form;
                me.color := clr;
                PrintTextAbove(me, "The creature changes shape!");
       endif
endif

endfunction