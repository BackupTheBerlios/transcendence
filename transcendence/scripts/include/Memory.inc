// Memory.inc
// Version: r1y2002
// © 2002 Maximilian Scherr

use uo;
use os;

// include "include/SendPacket";
include "include/client";
include "include/yesno";
// include "include/FreezeThaw";

function Memorize(who)
  SendSysMessage(who, "You start to memorize.");
  PlaySoundEffectPrivate(who, SFX_101, who);
  var mobilearray := {};
  var equipmentarray := {};
  foreach mobile in ListMobilesNearLocation(who.x, who.y, who.z, 30, who.realm)
    mobilearray.append({mobile.serial, mobile.graphic, mobile.x, mobile.y, mobile.z, mobile.facing, mobile.color});
    foreach item in ListEquippedItems(mobile)
      equipmentarray.append({mobile.serial, item.serial, item.graphic, item.layer, item.color});
    endforeach
  endforeach
  var itemarray := {};
  foreach item in ListItemsNearLocation(who.x, who.y, who.z, 30, who.realm)
    if ((item.amount == 1) && (!item.isa(POLCLASS_CORPSE)) && (!item.invisible))
      itemarray.append({item.serial, item.graphic, item.x, item.y, item.z, item.facing, item.color});
    endif
  endforeach
  PlaySoundEffectPrivate(who, SFX_FD, who);
  SetObjProperty(who, "#memory", {mobilearray, equipmentarray, itemarray});
  sleep(1);
  SendSysMessage(who, "You stop memorizing.");
endfunction

function Recall(who)
  var memory := GetObjProperty(who, "#memory");
  if (memory)
    SendSysMessage(who, "You start to recall.");
    SetObjProperty(who, "#mrecalling", 1);
    PlaySoundEffectPrivate(who, SFX_FF, who);
    Freeze(who);
    var mobilearray := memory[1];
    var packethexstring;
    var packethexstringpart1;
    var packethexstringpart2;
    var equipmentarray := memory[2];
    var graphic;
    foreach mobile in ListMobilesNearLocation(who.x, who.y, who.z, 30, who.realm)
      DeleteObject(who, mobile);
    endforeach
    foreach mobile in mobilearray
      if (mobile[1] == who.serial)
        packethexstring := "20"+ ConvertIntToHex(mobile[1], 4);
        if (who.gender)
          graphic := 403;

        else
          graphic := 402;
        endif
        packethexstring := packethexstring + ConvertIntToHex(graphic, 2);
        packethexstring := packethexstring +"00";
        packethexstring := packethexstring + ConvertIntToHex(who.color, 2);
        packethexstring := packethexstring +"00";
        packethexstring := packethexstring + ConvertIntToHex(mobile[3], 2);
        packethexstring := packethexstring + ConvertIntToHex(mobile[4], 2);
        packethexstring := packethexstring +"0000";
        packethexstring := packethexstring + ConvertIntToHex(who.facing, 1);
        packethexstring := packethexstring + ConvertIntToHex(mobile[5], 1);
        SendPacket(who, packethexstring);
      endif
    endforeach
    foreach mobile in mobilearray
      if (mobile[1] != who.serial)
        packethexstringpart1 := "78";
        packethexstringpart2 := ConvertIntToHex(mobile[1], 4) + ConvertIntToHex(mobile[2], 2);
        packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(mobile[3], 2);
        packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(mobile[4], 2);
        packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(mobile[5], 1);
        packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(mobile[6], 1);
        packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(mobile[7], 2);
        packethexstringpart2 := packethexstringpart2 +"0000";
        foreach item in equipmentarray
          if (item[1] == mobile[1])
            packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(item[2], 4);
            if (item[5] == 0)
              graphic := item[3];

            else
              graphic := item[3] + 32768;
            endif
            packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(graphic, 2);
            packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(item[4], 1);
            if (item[5] != 0)
              packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(item[5], 2);
            endif
          endif
        endforeach
        packethexstringpart2 := packethexstringpart2 +"00000000";
        var fullpackethexstringlength := (len(packethexstringpart1) + len(packethexstringpart2)) / 2 + 2;
        var fullpackethexstring := packethexstringpart1 + ConvertIntToHex(fullpackethexstringlength, 2) + packethexstringpart2;
        SendPacket(who, fullpackethexstring);
      endif
    endforeach
    var itemarray := memory[3];
    foreach item in ListItemsNearLocation(who.x, who.y, who.z, 30, who.realm)
      if (!item.invisible)
        DeleteObject(who, item);
      endif
    endforeach
    foreach item in itemarray
      packethexstringpart1 := "78";
      packethexstringpart2 := ConvertIntToHex(item[1], 4) + ConvertIntToHex(item[2], 2);
      packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(item[3], 2);
      packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(item[4], 2);
      packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(item[5], 1);
      packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(item[6], 1);
      packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(item[7], 2);
      packethexstringpart2 := packethexstringpart2 +"000000000000";
      var fullpackethexstringlength := (len(packethexstringpart1) + len(packethexstringpart2)) / 2 + 2;
      var fullpackethexstring := packethexstringpart1 + ConvertIntToHex(fullpackethexstringlength, 2) + packethexstringpart2;
      SendPacket(who, fullpackethexstring);
    endforeach
    var recstop := 0;
    while ((who.ip) && (recstop == 0))
      if (YesNo(who, "Do you want to stop recalling?"))
        recstop := 1;
      endif
    endwhile
    Thaw(who);
    PlaySoundEffectPrivate(who, SFX_FE, who);
    var whox := who.x;
    var whoy := who.y;
    var whoz := who.z;
    MoveCharacterToLocation(who, 5276, 1164, 0);
    MoveCharacterToLocation(who, whox, whoy, whoz);
    EraseObjProperty(who, "#mrecalling");
    SendSysMessage(who, "You stop recalling.");
  endif
endfunction

// the following functions have been pasted from SendPacket.inc and FreezeThaw.inc

function ConvertIntToHex(astring, alength)
  astring := Hex(astring);
  astring := CStr(astring);
  if (astring["0x"])
    astring := astring[3, len(astring)];
  endif
  if (len(astring) > alength * 2)
    return;
  endif
  while (len(astring) < alength * 2)
    astring := "0"+ astring;
  endwhile   
  return astring;
endfunction

function DeleteObject(who, lobj)
  var packethexstring := "1D"+ ConvertIntToHex(lobj.serial, 4);
  SendPacket(who, packethexstring);
endfunction

function Freeze(who)
  if (who.frozen)
    SetObjProperty(who, "#frozen", 1);
    return;

  else
    EraseObjProperty(who, "#frozen");
    who.frozen := 1;
  endif
endfunction

function Thaw(who)
  var frozen := GetObjProperty(who, "#frozen");
  if (frozen)
    EraseObjProperty(who, "#frozen");
    return;

  else
    who.frozen := 0;
  endif
endfunction

function MemorizeInItem(itm, corpse)
  //SendSysMessage(who, "You start to memorize.");
  //PlaySoundEffectPrivate(who, SFX_101, who);
  var mobilearray := {};
  var equipmentarray := {};
 
  var locs := {corpse.x, corpse.y, corpse.z};
 
  foreach mobile in ListMobilesNearLocation(locs[1], locs[2], locs[3], 30, corpse.realm)
    mobilearray.append({mobile.serial, mobile.graphic, mobile.x, mobile.y, mobile.z, mobile.facing, mobile.color});
    foreach item in ListEquippedItems(mobile)
      equipmentarray.append({mobile.serial, item.serial, item.graphic, item.layer, item.color});
    endforeach
  endforeach
  var itemarray := {};
  foreach item in ListItemsNearLocation(locs[1], locs[2], locs[3], 30, corpse.realm)
    if ((item.amount == 1) && (!item.isa(POLCLASS_CORPSE)) && (!item.invisible))
      itemarray.append({item.serial, item.graphic, item.x, item.y, item.z, item.facing, item.color});
    endif
  endforeach
  //PlaySoundEffectPrivate(itm, SFX_FD, itm);
  SetObjProperty(itm, "#memory", {mobilearray, equipmentarray, itemarray, locs});
  //sleep(1);
  //SendSysMessage(itm, "You stop memorizing.");
endfunction