//////////////////////////////////
//
// Movement.inc
// Created 7/19/2002 2:32PM
// Updated 3/25/2003 3:23PM
//
//This include was designed to handle movement in the brain
//It was a situation of pretty code vs. fewer instructions.
//So rather than having it loop and check the event over and over
//I changed it to check the event, then loop the actual movement part.
//

function Movement(ev)
	var old_pri := set_priority(50);
	case ( ev.speed )
		NEMOVE_WALK:
			case ( ev.direction )
				NEMOVE_AWAY:
					repeat
						WalkAwayFrom(ev.source);
						sleepms(3);
					until ( !MoveLoopCheck(ev) );
				NEMOVE_TOWARD:
					repeat
						WalkToward(ev.source);
						sleepms(3);
					until ( !MoveLoopCheck(ev) );
			endcase	
		NEMOVE_RUN:
			case( ev.direction )
				NEMOVE_AWAY:
					repeat
						RunAWayFrom(ev.source);
						sleepms(3);
					until ( !MoveLoopCheck(ev) );	
				NEMOVE_TOWARD:
					repeat
						RunToward(ev.source);
						sleepms(3);
					until ( !MoveLoopCheck(ev) );
			endcase
	endcase
	set_priority(old_pri);
endfunction

function MovementXYZ(ev)
	var old_pri := set_priority(50);
	case ( ev.speed )
		NEMOVE_WALK:
			case ( ev.direction )
				NEMOVE_AWAY:
					repeat
						WalkAwayFromLocation(ev.x, ev.y);
						sleepms(3);
					until ( !MoveLoopCheck(ev) );
				NEMOVE_TOWARD:
					repeat
						WalkTowardLocation(ev.x, ev.y);
						sleepms(3);
					until ( !MoveLoopCheck(ev) );
			endcase	
		NEMOVE_RUN:
			case( ev.direction )
				NEMOVE_AWAY:
					repeat
						RunAwayFromLocation(ev.x, ev.y);
						sleepms(3);
					until ( !MoveLoopCheck(ev) );	
				NEMOVE_TOWARD:
					repeat
						RunTowardLocation(ev.x, ev.y);
						sleepms(3);
					until ( !MoveLoopCheck(ev) );
			endcase
	endcase
	set_priority(old_pri);
endfunction

function MoveLoopCheck(byref ev)
	if ( Events_Waiting() )
		return 0;
	elseif ( ev.loop < 1 )
		return 0;
	elseif ( me.frozen )
		return 0;
	elseif ( me.paralyzed )
		return 0;
	endif
	if ( ev.source )
		//Dont need to worry about distance
		//in an XY movement check. It wont run in
		//circles around XY coordinates like it does
		//an object/mobile.
		if ( ev.direction == NEMOVE_TOWARD )
			if ( Distance(me, ev.source) <= 1 )
				return 0;
			endif
		endif
	endif
	
	ev.loop := ev.loop-1;
	return 1;
endfunction
