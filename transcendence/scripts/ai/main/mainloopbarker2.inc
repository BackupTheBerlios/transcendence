function main_AI_loop()

    var ev;
    var wanders := 120;
    var mynoise := bark();

    EnableMainEvents();

    while (1)

	//wander();
	wanders := wanders +1;
	var a;
	for (a:=0; a<=3; a:=a+1);
	PerformAction(Self(), 0x0003);
	sleep(1);
	endfor
	if (wanders > 120)
		wanders :=0;
		ev := sleepmode();
	else
	
		ev := os::wait_for_event( 2 );
	endif
        if (Self().npctemplate == "bird")
          var cfg := ReadConfigFile(":farming:plants");
          if (!cfg)
           say("Error");
          endif
          var myself := Self();
          foreach it in ListItemsNearLocation( myself.x, myself.y, myself.z, 4, myself.realm )
	   
	    if (cfg[it.graphic])
	      say("OK");
	      var done := 0;
               while(done == 0)

                  if (!WalkToward( it ));
                   done := 1;
                  endif
                 if (Distance(Self(), it) <  1)
                  done := 1;
                 endif
                SetObjProperty(Self(), "walking", 1);
               

               endwhile
	    PerformAction(Self(), 3);
	    var dam := GetObjProperty(it, "tempdam");
	    if (!dam)
	     dam := 0;
	    endif
	    dam := dam + 2;
	    SetObjProperty(it, "tempdam", dam);
	    endif
	  endforeach
	endif
	if (ev)
        repeat
	    case (ev.type)
		EVID_ENTEREDAREA:
		    
                   if(GetObjProperty(ev.source, "DarkAura"));
			 fight(ev.source);
	           endif
                    if (!ev.source.npctemplate)
                     //SendAOSToolTipByName(ev.source, Self());
                    endif
		    if (!ev.source.isA(POLCLASS_NPC))
		    	PlaySoundEffect(me, mynoise);
		    endif
                EVID_DAMAGED:
                    Fight( ev.source );
                EVID_ENGAGED:
		    RunLikeHell( ev.source );
            endcase
        until (! (ev := os::wait_for_event(2)) );
	endif

   endwhile     

endfunction       

function RunLikeHell(opponent)

	var ev;
	while ( (opponent) && not
	    (opponent.dead || opponent.hidden || opponent.concealed) &&
	    (dist(me,opponent) < 25) )

	    RunAwayFrom( opponent );

        repeat
	    case (ev.type)
                EVID_DAMAGED:
		    if ( RandomInt(3)==1 )
                    	Fight( ev.source );
		    	return;
		    endif
            endcase
        until (! (ev := os::wait_for_event(1)) );

	endwhile

endfunction

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_LEFTAREA + EVID_DISENGAGED + EVID_OPPONENT_MOVED);
    EnableEvents( EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( EVID_SPEECH + EVID_ENGAGED + EVID_DAMAGED + EVID_ENTEREDAREA);

endfunction

function bark()

	var noise := 0;
	case (me.graphic)
	0x06://bird
		case (RandomInt(3))
		0: noise := 0x1b;
		1: noise := 0x18;
		2: noise := 0x277;
		endcase
	0xc9://cat	
		noise := 0x6b;
	0xe7:
	0xe9:
	0xe8:
	0xd8://cow
		noise := 0x7a;
	0xd9://dog
		case (RandomInt(2))
		0: noise := 0x86;
		1: noise := 0x87;
		endcase
	0xd1://goat
		case (RandomInt(2))
		0: noise := 0x9a;
		1: noise := 0x9b;
		endcase
	0xcb://pig
		noise := 0xc6;
	0xcc:
	0xc8:
	0xe2:
	0xe4://horses
		case (RandomInt(4))
		0: noise := 0xa9;
		1: noise := 0xaa;
		2: noise := 0xab;
		3: noise := 0xac;
		endcase
	0x51://toad
		case (RandomInt(4))
		0: noise := 0x267;
		1: noise := 0x268;
		2: noise := 0x26a;
		3: noise := 0x26d;
		endcase
	0xd3://bears
		case (RandomInt(5))
		0: noise := 0xa4;
		1: noise := 0xa5;
		2: noise := 0xa6;
		3: noise := 0xa7;
		3: noise := 0xa8;
		endcase
	0x1d://gorilla
		case (RandomInt(3))
		0: noise := 0x9f;
		1: noise := 0xa0;
		2: noise := 0xa2;
		endcase
	endcase

	return noise;

endfunction