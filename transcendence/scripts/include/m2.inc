// Memory.inc
// Version: r1y2002
// © 2002 Maximilian Scherr
// Modified By ArT-iX

use uo;
use os;

// include "include/SendPacket";
include "include/client";
include "include/yesno";
//include "include/Hallucinations";
// include "include/FreezeThaw";

function MemorizeSceneAroundObject(obj)
  
  var scene := struct;
  
  scene.+mobiles;
  scene.+mobequipment;
  scene.+items;
  scene.+x;
  scene.+y;
  scene.+z;
  
  var mobil := struct;
  
  mobil.+serial;
  mobil.+graphic;
  mobil.+facing;
  mobil.+color;
  mobil.+x;
  mobil.+y;
  mobil.+z;
  mobil.+equipment;
  
  var eqp := struct;
  eqp.+character;
  eqp.+serial;
  eqp.+graphic;
  eqp.+color;
  eqp.+layer;
  
  var itm := struct;
  
  itm.+serial;
  itm.+graphic;
  itm.+facing;
  itm.+color;
  itm.+x;
  itm.+y;
  itm.+z;
  
  var mobilearray := {};
  var equipmentarray := {};
  
  scene.x := obj.x;
  scene.y := obj.y;
  scene.z := obj.z;
  
  foreach chr in ListMobilesNearLocation(obj.x, obj.y, obj.z, 30, obj.realm)
  
   mobil.serial := chr.serial; 
   mobil.graphic := chr.graphic; 
   mobil.facing := chr.facing;
   mobil.color := chr.color;
   mobil.x := chr.x;
   mobil.y := chr.y; 
   mobil.z := chr.z;
   var eqpt := {};   
   
    foreach it in ListEquippedItems(chr)
      
      eqp.character := chr.serial;
      eqp.serial := it.serial;
      eqp.graphic := it.graphic;
      eqp.color := it.color;
      eqp.layer := it.layer;
      
      eqpt.append(eqp);
      equipmentarray.append(eqp);
    endforeach
    mobil.equipment := eqpt;
    mobilearray.append(mobil);
  endforeach
  
  
  var itemarray := {};
  
  foreach it in ListItemsNearLocation(obj.x, obj.y, obj.z, 30, obj.realm)
    if ((it.amount == 1) && (!it.isa(POLCLASS_CORPSE)) && (!it.invisible))
    
        itm.serial := it.serial;
        itm.graphic := it.graphic;
        itm.facing := it.facing;
        itm.color := it.color;
        itm.x := it.x;
        itm.y := it.y;
        itm.z := it.z;
    
      itemarray.append(itm);
    
    endif
  endforeach
  
  scene.mobiles := mobilearray;
  scene.mobequipment := equipmentarray;
  scene.items := itemarray;
  
  
  return scene;
  
  
endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function MemorizeSceneAroundCoord(x, y, z, realm := "britannia")
  
  var scene := struct;
  
  scene.+mobiles;
  scene.+mobequipment;
  scene.+items;
  scene.+x;
  scene.+y;
  scene.+z;
  
  var mobil := struct;
  
  mobil.+serial;
  mobil.+graphic;
  mobil.+facing;
  mobil.+color;
  mobil.+x;
  mobil.+y;
  mobil.+z;
  mobil.+equipment;
  
  var eqp := struct;
  eqp.+character;
  eqp.+serial;
  eqp.+graphic;
  eqp.+color;
  eqp.+layer;
  
  var itm := struct;
  
  itm.+serial;
  itm.+graphic;
  itm.+facing;
  itm.+color;
  itm.+x;
  itm.+y;
  itm.+z;
  
  var mobilearray := {};
  var equipmentarray := {};
  
  foreach chr in ListMobilesNearLocation(x, y, z, 30, realm)
  
   mobil.serial := chr.serial; 
   mobil.graphic := chr.graphic; 
   mobil.facing := chr.facing;
   mobil.color := chr.color;
   mobil.x := chr.x;
   mobil.y := chr.y; 
   mobil.z := chr.z;
  var eqpt := {};   
   
    foreach it in ListEquippedItems(chr)
      
      eqp.character := chr.serial;
      eqp.serial := it.serial;
      eqp.graphic := it.graphic;
      eqp.color := it.color;
      eqp.layer := it.layer;
     
      eqpt.append(eqp);
      equipmentarray.append(eqp);
    endforeach
    mobil.equipment := eqpt;
    mobilearray.append(mobil);
  endforeach
  
  
  var itemarray := {};
  
  foreach it in ListItemsNearLocation(x, y, z, 30)
    if ((it.amount == 1) && (!it.isa(POLCLASS_CORPSE)) && (!it.invisible))
    
        itm.serial := it.serial;
        itm.graphic := it.graphic;
        itm.facing := it.facing;
        itm.color := it.color;
        itm.x := it.x;
        itm.y := it.y;
        itm.z := it.z;
    
      itemarray.append(itm);
    
    endif
  endforeach
  
  scene.mobiles := mobilearray;
  scene.mobequipment := equipmentarray;
  scene.items := itemarray;
  scene.x := x;
  scene.y := y;
  scene.z := z;
  return scene;
 
  
endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function RecallScene(who, memory)
  
  
  if (memory)
    
    Freeze(who);
    var mobilearray := memory.mobiles;
    var equipmentarray := memory.mobequipment;
    var graphic;
    
    SetSceneHidden(who, memory.x, memory.y, memory.z);
    
    foreach mob in ListMobilesNearLocation(who.x, who.y, who.z, 30, who.realm)
      DeleteObject(who, mob);
    endforeach
    
    
    foreach mob in mobilearray
      
        DrawNpc(who, mob.graphic, mob.color, mob.facing, mob.x, mob.y, mob.z, mob.equipment);
        
    endforeach
    
    var itemarray := memory.items;
    
    foreach itm in itemarray
      
      DrawObject(who, itm.graphic, itm.color, itm.x, itm.y, itm.z, itm.facing);
     
    endforeach
    var recstop := 0;
    while ((who.ip) && (recstop == 0))
      if (YesNo(who, "Do you want to stop recalling?"))
        recstop := 1;
      endif
    endwhile
    Thaw(who);
    
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

function DeleteObjectMem(who, lobj)
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
  
  SetObjProperty(itm, "#memory", {mobilearray, equipmentarray, itemarray, locs});
  
  
endfunction