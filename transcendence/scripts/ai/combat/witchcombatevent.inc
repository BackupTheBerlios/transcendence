include "include/attributes";
function PlayObjectCenteredEffectHuefx( center, effect, speed,
loop := 0, color := 0, translucent := 0 , realm := "britannia")
       var packetstring := "C0";
       packetstring := packetstring + "03";   
       packetstring := packetstring + fixPacketLength(Hex(center.serial),4);
       packetstring := packetstring + fixPacketLength(Hex(0),4);
       packetstring := packetstring + fixPacketLength(Hex(effect),2);
       packetstring := packetstring + fixPacketLength(Hex(0),10);
       packetstring := packetstring + fixPacketLength(Hex(speed),1); //speed
       packetstring := packetstring + fixPacketLength(Hex(loop),1);     //loop
       packetstring := packetstring + "000000000000";
       packetstring := packetstring + fixPacketLength(Hex(color),2); //color
       packetstring := packetstring + "000000";
       packetstring := packetstring + fixPacketLength(Hex(translucent),1);    //tran
       foreach chr in ListMobilesNearLocation( center.x, center.y,
center.z, 16 , realm);
          SendPacket( chr, packetstring );
       endforeach
endfunction

function process_combat_event(ev)

	//local parms array;
		//parms[1] := "#MOB";
		//parms[2] := caster;
		//parms[3] := cast_on;
	if (!GetObjProperty(ev.source, "trasformed"))
	negapolymorph(ev.source);
	endif
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

function negapolymorph(enemy)

var origform := enemy.graphic;
	var origstr := GetStrength(enemy);
     
	var critgroup;
	var thecreature;

	if (!GetObjProperty(enemy,"origform"))
	
            SetObjProperty(enemy,"origform",enemy.graphic);
	endif

	if (!GetObjProperty(enemy,"origstr"))
            SetObjProperty(enemy,"origstr",GetStrength(enemy));

      //else
		//PlaySoundEffect(,0x005d);
		//PlayObjectCenteredEffect(enemy, 0x3735,0x0a, 0x1e);
		//caster.mana := caster.mana + 40;
		//SendSysMessage(caster,"Trasformalo.");
		//return;
	endif


	
		critgroup := 0;


	var critter := RandomInt(6);

	case (critgroup)
		0:
		case (critter)
		 0: thecreature := 238;	//topo


		 1: thecreature := 208;	//gallina
		 2: thecreature := 203;	//maiale
		 3: thecreature := 207;	//sheep
		 4: thecreature := 6;	//bird
		 5: thecreature := 201;	//cat
		endcase
	
	endcase
      say("Per i poteri degli inferi, in vile creatura trasformati!!");
      PerformAction(me, 0x0011);
      SetObjProperty(enemy, "trasformed", 1);
      PlaySoundEffect(enemy, 0x011e);
      //effetto (enemy.x, enemy.y, enemy.z, 0x372a, 0, 3 );
	PlayObjectCenteredEffectHuefx(enemy, 0x372a, 10,
10, color := 0, translucent := 0 );
	enemy.graphic := thecreature;
      SetBaseStrength(enemy,20);
	var params := enemy;

	start_script( ":controlscripts:negapolycontrol", params );

	/*detach();
	sleep(120);*/

endfunction

function fixPacketLength( packetstring, byteLength )
    if( !packetstring || packetstring == error )
        packetstring := 0;
    endif
    packetstring := CStr(packetstring);
   
    if( packetstring[1,2] == "0x" )
        packetstring := CStr(packetstring[3,len(packetstring)]);
    endif
   
    if( len(packetstring) > byteLength * 2 )
        var extrabytes := (byteLength*2) - len(packetstring);
        return CStr(packetstring[extrabytes,len(packetstring)]);
    endif
   
    while( len(packetstring) < byteLength * 2 )
        packetstring := "0" + packetstring;
    endwhile
   
    return packetstring;
endfunction