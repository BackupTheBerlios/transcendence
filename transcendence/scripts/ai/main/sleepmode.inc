include "include/attributes";
function sleepmode()
        /*if(me.npctemplate == "rogue_ent")
        EntSleep(me);
        endif*/
	foreach critter in ListMobilesNearLocation( me.x,me.y,me.z, 10 , me.realm);
          if (!critter.isA(POLCLASS_NPC))
		return 0;
          endif
	endforeach

	if (GetObjProperty(me,"killme"))
		ApplyRawDamage(me,GetHp(me)+1);
	endif

	EraseObjProperty(me,"#flees");

	DisableMainEvents();
	if (GetEffectiveSkill(me, 21) > 0 )
                me.hidden := 1;
		EnableEvents(EVID_ENTEREDAREA,4);
	else
		EnableEvents(EVID_ENTEREDAREA,18);
	endif

	EnableEvents(EVID_ENGAGED);
	EnableEvents(EVID_DAMAGED);

	var ev;

	while (1)
		ev := os::wait_for_event( 120 );

		repeat

		case (ev.type)
                	EVID_ENGAGED:
			EVID_DAMAGED:
			EVID_ALL_ATTACK_CMD:
			
			        /*if((me.hidden) && (me.npctemplate == "rogue_ent"))
					 EntAppear(me);*/
					if (me.hidden) 
						me.hidden := 0;
						say("*" + me.name + " springs from hiding!*");
					endif
				/*if (me.hidden)
					me.hidden := 0;
					say("*" + me.name + " springs from hiding!*");
				endif*/
				EnableMainEvents();
				return ev;
			EVID_ENTEREDAREA:
				if ( (!ev.source.npctemplate) || (ev.source.script == "tamed") )
					
					if (me.hidden) 
						me.hidden := 0;
						say("*" + me.name + " springs from hiding!*");
					endif
					
					EnableMainEvents();
					return ev;
				endif
		endcase

		until (! (ev := os::wait_for_event(120)) );

	endwhile     

endfunction      