include "include/attributes";
function process_combat_event(ev)

	if (spellcast)
		spellattack(ev.source);
	endif

        if (ev.type == EVID_DAMAGED)
			if ( (spellcast) && ( GetHp(me) < (GetStrength(me)/2)) )
				CastSpell(me,me,"gheal");
				if( CInt(GetObjProperty(me, "poison_level")) > 1)
					CastSpell(me,me,"cure");
					CastSpell(me,ev.source,"poison");
				endif
			endif
                        if ((GetHp(me) * 100/GetMaxHp(me)) < flee_point)
                                flee(ev.source);
                        endif
        endif

endfunction

function in_combat_event_loop(opponent, loops)

	if (spellcast)
		spellattack(opponent);
	endif

	if ( loops > 100 )
		flee(opponent);
		return;
	endif

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

function post_combat()

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	if ( (spellcast) && ( GetHp(me) < (GetStrength(me)/2)) )
		CastSpell(me,me,"gheal");
	endif

	sleep(1);
	look_around();
	me.hidden := 1;

endfunction

function prepare_for_fight(opponent)

	DisableMainEvents();
	me.concealed := 1;
	var it;
 	foreach it in ListEquippedItems(me)
		DestroyItem(it);
	endforeach
	var p := CreateItemAtLocation(me.x, me.y, me.z, 0x0e75, 1, me.realm);
	EquipItem(me, p);
	me.criminal := 0;
	me.graphic := opponent.graphic;
	me.color:= opponent.color;
	me.name := opponent.name;

	foreach it in ListEquippedItems(opponent)
		var what := CreateItemInContainer(me.backpack, it.objtype, 1);
		what.color := it.color;
		what.graphic := it.graphic;
		if (it.name)
			what.name := it.name;
		endif
		EquipItem(me,what);
		SetObjProperty(what,"#noloot",1);
	endforeach
	me.criminal := 0;
	var oldprio := set_priority(50);

	var weaponone := GetEquipmentByLayer( me,  LAYER_HAND1 );
	var weapontwo := GetEquipmentByLayer( me,  LAYER_HAND2 );
	if ( (weaponone.objtype == 0x13b2) || (weapontwo.objtype == 0x13b2) )
		runaway:=0;
		CreateItemInInventory(me.backpack,0xf3f,50);
	elseif ( (weaponone.objtype == 0x0f4f) || (weapontwo.objtype == 0x0f4f) ||
		(weaponone.objtype == 0x13fd) || (weapontwo.objtype == 0x13fd) )
		runaway:=0;
		CreateItemInInventory(me.backpack,0x1bfb,50);
	elseif ( (weaponone.objtype == 0x0f4f) || (weapontwo.objtype == 0x0f4f) )
		runaway:=0;
		CreateItemInInventory(me.backpack,0x6051,25);
	else
		runaway := 100;
	endif
	me.concealed := 0;
	if ( (!weaponone) && (!weapontwo) )
		spellcast := 1;
	else
		spellcast := 0;
	endif

	EnableCombatEvents();

endfunction