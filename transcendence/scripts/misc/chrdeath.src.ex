use uo;
use os;
use util;

include "include/NPCBackpacks";
include "include/attributes";
include "include/statMod";
include "include/noto";
include "include/reportMurder";

program chrdeath(corpse,ghost)
  EraseObjProperty(ghost, "IsMeditating");
//  ghost.SetPoisoned(0);
  var killer := GetObjProperty(ghost, "LastHit");
  if(killer != error)
    AdjustNoto((SystemFindObjectBySerial(killer[2], SYSFIND_SEARCH_OFFLINE_MOBILES)), ghost);
  endif
  var fame := CInt(GetObjProperty(ghost, "Fame"));
  fame := (fame - CInt(fame / 20));
  SetObjProperty(ghost, "Fame", fame);
  SetObjProperty(corpse,"serial", ghost.serial);
  dismount(ghost, corpse);
  CheckForAutoRes(ghost, corpse);
  var corpsenamearray := SplitWords(corpse.name);
  var corpsenamearraylen := len(corpsenamearray);
  var x, corpsename := "";
  for (x := 4; x <= corpsenamearraylen; x := x + 1)
    corpsename := corpsename + " " + corpsenamearray[x];
  endfor
  if(len(ghost.reportables)>0)
	SendReportGump(ghost);
  endif
endprogram

function CheckForAutoRes(who, corpse)
  if(CInt(GetObjProperty(corpse, "AutoRes")) == 1)
	Resurrect(who);
	SetHp(who, GetMaxHP(who));
	SetMana(who, GetMaxMana(who));
	SetStamina(who, GetMaxStamina(who));
	var itemlist := {};
	var mypack := who.backpack;
    if(!mypack)
      return;
    endif
	foreach thing in EnumerateItemsInContainer(corpse)
	  if(thing.container == corpse)
	    if(!EquipItem(who, thing))
		  MoveItemToContainer(thing, mypack);
	    endif
	  endif
	endforeach
  endif
endfunction

function dismount(me,corpse)
  var mount := GetEquipmentByLayer( corpse, 25 );
  foreach item in EnumerateItemsInContainer(corpse)
	if (item.objtype == 0xf021)
	  mount := item;
	  break;
	endif
  endforeach
  if (!mount)
	return;
  endif
  var animal := SystemFindObjectBySerial(CInt(GetObjProperty(mount,"serial")));
  animal.facing := corpse.facing;
  EraseObjProperty(animal, "mounted");
  EraseObjProperty(animal, "mounted_on");
  MoveCharacterToLocation( animal, corpse.x, corpse.y, corpse.z, MOVECHAR_FORCELOCATION);
  DestroyItem(mount);
endfunction