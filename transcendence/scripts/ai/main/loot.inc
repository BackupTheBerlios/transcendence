include "include/npcbackpacks";

const STARTHAIR := 0x2030;
const ENDHAIR := 0x2060;

function grabloot()

	if ( GetObjProperty(me,"noloot") )
		return;
	endif

	var numitems := 0;
	var mypack := 0;
	if (!GetObjProperty(me,"serial"))
		SetObjProperty(me, "serial", me.serial);
	endif
	mypack := FindMyPack(me.serial);

	var near_items := ListItemsNearLocation(me.x, me.y, me.z,6, me.realm);

     foreach item in near_items
	if( CheckLineOfSight( me, item ) )

	var sh := GetStandingHeight( item.x, item.y, item.z, item.realm );
	if (sh.multi || sh.multi.serial)
		break;
	endif
	var info := CInt(GetMapInfo( item.x, item.y, item.realm ).landtile);
	if ((info > CInt(0x405)) && (info < CInt(0x456)))
		break;
	endif

	if ( (item.movable) && ((item.objtype < STARTHAIR || item.objtype > ENDHAIR))  )
		RunToIt(me,item);
		if ( (Distance(me, item) < 2) && (MoveItemToContainer(item, mypack)) )
				say( "*yoink*" );
				sleep(2);
				return;
		else
			return;
		endif
	elseif (item.objtype == UOBJ_CORPSE)
	    if (!CInt(GetObjProperty(item,"#ignoreit")) )
		var items := { };

		foreach thingie in EnumerateItemsInContainer(item)
		if (    (thingie.objtype < STARTHAIR || thingie.objtype > ENDHAIR)
			&& (!CInt(GetObjProperty(thingie,"#ignoreit"))) )
			items[ len(items)+1 ] := thingie;
		endif
		endforeach

		if ( len(items) )
			RunToIt(me,item);
			if (Distance(me, item) < 2)
				foreach thingie in items
				    if ( MoveItemToContainer(thingie, mypack) )
					say( "*yoink*" );
					sleep(2);
					return;
				    else
					SetObjProperty(thingie,"#ignoreit",1);
				    endif
				endforeach
			endif
		else
			SetObjProperty(item,"#ignoreit",1);
		endif

	    endif
	endif

	endif
     endforeach

endfunction

function RunToIt(me,item)

	var numsteps;
	for (numsteps := 0; numsteps < 8; numsteps := numsteps +1)
		if ( Distance(me, item) < 2 )
			return;
		else
			RunToward(item);
		endif
	endfor

endfunction