include "include/speech";
function main_AI_loop()

    var ev;
    var wanders := 120;
    var next_loot := ReadGameClock() + 20;
    var weap3d := GetObjProperty(Self(), "Equip3d");
    if(weap3d)
    //print("WEAP3D " + cstr(weap3d));
     //var wp := CreateItemAtLocation( Self().x, Self().y, Self().z, weap3d );
     //EquipItem( Self(), wp );
     EquipFromTemplate(Self(), weap3d );
    //else
    //print("NOWEAP");	
    endif
    EnableMainEvents();

    look_around();

    while (1)
        foreach mbs in ListMobilesNearLocation( me.x, me.y, me.z, 10, me.realm )
         if(!mbs.npctemplate)
          //SendAOSToolTipByName(ev.source, Self());
         endif
        endforeach
        PlaySoundEffect(me, mysound(me));
        if(me.npctemplate != "rogue_ent")
	if (ReadGameClock() > next_loot)
		grabloot();
		next_loot := ReadGameClock() + 10;
	else
	        if ((me.npctemplate == "robot1") || (me.npctemplate == "robot2") || (me.npctemplate == "robot3"));
	        var i;
	         for (i := 0; i <= 3; i := i + 1)
	          PlaySoundEffect(me, 541);
	         endfor
	        endif 
		wander();
	        if ((me.npctemplate == "titan") || (me.npctemplate == "cyclops") || (me.npctemplate == "giant") || (me.npctemplate == "giantdragon") || (me.npctemplate == "giantdragon2") || (GetObjProperty(me, "Race") == "giant"));
	        var i;
	         for (i := 0; i <= 3; i := i + 1)
	          PlaySoundEffect(me, 0x0121);
	         endfor
	        endif 
	        
	endif
        else
	 sleepmode(); 
        endif
	wanders := wanders +1;
        
	if (wanders > 120)
		wanders :=0;
		ev := sleepmode();
	else
		ev := os::wait_for_event( 2 );
	endif
   
	if (ev)
	  repeat
            case (ev.type)
                EVID_SPEECH:
                	RespondToSpeech(me,ev.text);
                EVID_ENTEREDAREA:
                    /*if (!ev.source.npctemplate)
                    SendAOSToolTipByName(ev.source, Self());
                    endif*/
                    if(me.npctemplate == "rogue_ent")
                    EntAppear(me);
                    endif
                    if ( (!ev.source.npctemplate) || (ev.source.script == "tamed") && (!GetObjProperty(ev.source, "EvilFriends")))
		    	var verso := mysound(me);
                        PlaySoundEffect(me, verso);
		    	get_help( ev.source );
			Fight( ev.source );
                    endif
		EVID_ALL_ATTACK_CMD:
		    Fight( ev.source );
                EVID_ENGAGED:
                EVID_DAMAGED:
		    get_help( ev.source );
		    Fight(ev.source);
            endcase
	  until (!(ev := os::wait_for_event(2)));
	endif

   endwhile     

endfunction      

function look_around()

	foreach npc in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
          if ( (!npc.npctemplate) || (npc.script == "tamed") )
                Fight( npc );
		return;
          endif
	endforeach

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED );
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction

function get_help( opponent )

	var inev;
	var ev array;
	ev.+type := EVID_ALL_ATTACK_CMD;
	ev.+source := opponent;

	set_critical(1);
	foreach critter in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
		if ( (critter.npctemplate) && (critter.script != "tamed") && (!critter.warmode) )
			SendEvent(critter, ev);
		endif
		inev := wait_for_event(0);
		if (inev == EVID_ALL_ATTACK_CMD)
			set_critical(0);
			return;
		endif
	endforeach
	set_critical(0);

endfunction

function mysound(me);

var sound;

if (me.npctemplate == "panther")
 sound := 0x00bc;

elseif (me.npctemplate == "grizzly")
 sound :=  0x00a5;
elseif (me.npctemplate == "alligator")
 sound :=  0x005b;
elseif (me.npctemplate == "polar")
 sound :=  0x00a5;
elseif (me.npctemplate == "snowleopard")
 sound :=  0x00bc;
elseif (me.npctemplate == "snowleopard2")
 sound :=  0x00bc;
 elseif (me.npctemplate == "leopard")
 sound :=  0x00bc;
elseif (me.npctemplate == "ogre")
 sound :=  0x01ad;
elseif (me.npctemplate == "ghost")
 sound :=  0x0180;
elseif (me.npctemplate == "shade")
 sound :=  0x0180;
elseif (me.npctemplate == "ghost")
 sound :=  0x0180;
elseif (me.npctemplate == "titan")
 sound :=  0x0121;
elseif (me.npctemplate == "cyclops")
 sound :=  0x0121;
elseif (me.npctemplate == "puma")
 sound :=  0x00bc;
elseif (me.npctemplate == "lioness")
 sound :=  0x00b4;
elseif (me.npctemplate == "crocodile")
 sound :=  0x005b;
elseif (me.npctemplate == "kaiman")
 sound :=  0x005b;
elseif (me.graphic  == 0x0015)
 sound :=  0x00dd;
elseif (me.graphic  == 0x0034)
 sound :=  0x00dd;
elseif (me.npctemplate == "crocodile2")
 sound :=  0x005b;
elseif ((me.graphic  == 0x3c) && (me.npctemplate != "spectraldrake"))
 sound :=  0x016f;
elseif (me.graphic  == 0xc)
 sound :=  0x016f;
elseif (me.npctemplate == "spectraldrake")
 sound := 0x0180;
elseif (me.npctemplate == "panther2")
 sound := 0x00bc;
elseif (me.npctemplate == "femdaemon")
 sound := 0x4b5;
elseif (me.npctemplate == "minordaemoness")
 sound := 0x4b2;
  
endif
return sound;
endfunction


