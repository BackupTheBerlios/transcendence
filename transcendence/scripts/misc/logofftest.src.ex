use uo;

include "include/eventID";
include "include/innCheck";

program logofftest(who)
  if((who.cmdlevel > 1) || (GetObjProperty(who,"justbanned")))
    return 0;
  endif
  EraseObjProperty(who, "#Online");
  var topxy, botxy;
  var safelogoff := 0;
  var item, player;
  if (CInt(GetObjProperty(who, "#camped"))== 1)
    EraseObjProperty(who, "#camped");
    safelogoff := 1;
  elseif(Inncheck(who))
    safelogoff := 1;
  endif
  if(!safelogoff)
    if(who.multi.serial)
      var house := who.multi;
      if(who.acctname == (GetObjProperty(house, "owneracct")))
        safelogoff := 1;
      else
        foreach player in (GetObjProperty(house, "friendlist"))
          if(who.serial == player)
            safelogoff := 1;
          endif
        endforeach
        foreach player in (GetObjProperty(house,"coownlist"))
          if(who.serial == player)
            safelogoff := 1;
          endif
        endforeach
      endif
    endif
  endif
  if(!safelogoff)
    staffnotify(who);
    return 300;  // wait 5 minutes
  elseif(safelogoff == 1)
    return 0;   // ok to log off
  else
    return safelogoff;
  endif
endprogram

function staffnotify(who)
  var pid := 0;
  while(!pid)
    sleepms(50);
    pid := GetGlobalProperty("#stafflist");
  endwhile
  pid := getprocess(pid);
  if(!pid)
    return;
  endif
  var k := struct;
  k.+player := who;
  k.+type  := EVID_PLAYER_DELAY;
  pid.sendevent(k);
endfunction