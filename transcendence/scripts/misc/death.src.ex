use uo;
use os;
use util;
use cfgfile;

include "include/client";
include "include/attributes";
include "include/NPCBackpacks";
include "include/noto";
include "../../pkg/systems/spawnregion/spawnRegion";

var cfg := ReadConfigFile( "npcdesc" );

program npcdeath(corpse)
  if(GetObjProperty(corpse, "restockserial"))
    var stocklist := SystemFindObjectBySerial(CInt(GetObjProperty(corpse, "restockserial")));
    DestroyItem(stocklist);
  endif
  var killer := GetObjProperty(corpse, "LastHit");
  if((killer != error) && (!GetObjProperty(corpse, "guardkill")))
    AdjustNoto((SystemFindObjectBySerial(killer[2])), corpse);
  endif
  var char;
  var mounted_char;
  var onchars := EnumerateOnlineCharacters();
  if(GetObjProperty(corpse,"mounted"))
    char := GetObjProperty(corpse,"mounted_on");
    foreach person in onchars
      if(person.serial == CInt(char))
        mounted_char := person;
        break;
      endif
    endforeach
    dismountme(mounted_char, corpse);
  endif
  var elem := GetObjProperty(corpse, "npctemplate");
  var deathsound := 0;
  var graphic := GetObjProperty(corpse, "Graphic");
  if((graphic != 0x190) && (graphic != 0x191))
    deathsound := cfg[elem]."deathsound";
    if (deathsound)
      PlaySoundEffect(corpse, deathsound);
    endif
  endif
  set_critical(1);
  dismount(corpse);
  Run_Script_To_Completion(":spawnregion:death", corpse);
  if(GetObjProperty(corpse, "regspawn"))
	var spawnname := GetObjProperty(corpse, "regspawn");
	var numspawns := CInt(GetGlobalProperty(spawnname))-1;
	SetGlobalProperty(spawnname,numspawns);
  endif
  set_critical(0);
  if(GetObjProperty(corpse, "guardkill"))
    DestroyItem(corpse);
    return;
  endif
  if(GetObjProperty(corpse,"npctemplate") == "employee")
    foreach thing in EnumerateItemsInContainer(corpse)
      if((thing.layer) && (thing.isa(POLCLASS_WEAPON) || thing.isa(POLCLASS_ARMOR)))
        DestroyItem(thing);
      endif
    endforeach
  endif
  MoveBackpackToCorpse(corpse);
  if(GetObjProperty(corpse, "npctemplate") == "playervendor")
    var itemdesc := ReadConfigFile(":*:itemdesc");
    var elm, dsc;
    foreach thing in EnumerateItemsInContainer(corpse)
      EraseObjProperty(thing, "Vendored");
      if(GetObjProperty(thing, "Vendor"))
        DestroyItem(thing);
      else
        var oldname := GetObjProperty(thing, "OldName");
        if(oldname)
          SetName(thing, oldname);
        else
          elm := FindConfigElem(itemdesc, thing.objtype);
          dsc := itemdesc[thing.objtype].desc;
          SetName(thing, dsc);
        endif
        EraseObjProperty(thing, "Master");
        EraseObjProperty(thing, "OldName");
        EraseObjProperty(thing, "price");
      endif
    endforeach
  endif
  if(GetObjProperty(corpse, "summoned"))
    DestroyItem(corpse);
  elseif(GetObjProperty(corpse, "nocorpse"))
    foreach item in EnumerateItemsInContainer(corpse);
      MoveItemToLocation(item, corpse.x, corpse.y, corpse.z, MOVEITEM_FORCELOCATION);
    endforeach
    DestroyItem(corpse);
  else
    var corpseof := GetObjProperty(corpse,"npctemplate");
  endif
endprogram

function dismount(corpse)
	var mount := 0;GetEquipmentByLayer( corpse, 25 );
	foreach item in EnumerateItemsInContainer(corpse)
	  if (item.objtype == 0xf021)
		mount := item;
		break;
	  endif
	endforeach
	if (!mount)
	  return;
	endif
	var critter := "";
	case (mount.graphic)
	0x3ea2: critter := "horse";
	0x3e9f: critter := "horse2";
	0x3ea0: critter := "horse3";
	0x3ea1: critter := "horse4";
	0x3ea6:	critter := "llama";
	0x3ea3:	critter := "desertostard";
	0x3ea4:	critter := "frenziedostard";
	0x3ea5:	critter := "forestostard";
	endcase
	if (mount.color == 1109)
	  critter := "nightmare";
	endif
    if(!GetObjProperty(corpse,"doppelganger"))
	  var animal := CreateNpcFromTemplate(critter, corpse.x, corpse.y, corpse.z);
	  animal.color := mount.color;
    endif
	DestroyItem( mount );
endfunction

function dismountme(who, corpse)
  var mount := GetEquipmentByLayer(who, 25 );
  var clone := GetObjProperty(corpse,"npctemplate");
  var newcorpse := CreateNpcFromTemplate(clone, corpse.x, corpse.y, corpse.z);
  var serial := newcorpse.serial;
  SetObjProperty(newcorpse,"myserial", serial);
  newcorpse.color := corpse.color;
  newcorpse.facing := who.facing;
  MoveCharacterToLocation(newcorpse, who.x, who.y, who.z, MOVECHAR_FORCELOCATION);
  var x := newcorpse.x;
  var y := newcorpse.y;
  var z := newcorpse.z;
  newcorpse.facing := who.facing;
  ApplyRawDamage(newcorpse, GetHp(newcorpse)+3);
  var contain;
  foreach cpse in ListItemsAtLocation(x, y, z );
    if(CInt(GetObjProperty(cpse,"myserial")) == serial)
      contain := cpse;
      break;
    endif
  endforeach
  contain.name := corpse.name;
  foreach item in ListRootItemsInContainer(corpse)
    MoveItemToContainer(item, contain);
  endforeach
  DestroyItem(corpse);
  DestroyItem(mount);
endfunction

function ListRootItemsInContainer(container)
  var ret := { };
  foreach item in EnumerateItemsInContainer(container)
    if ( item.container.serial == container.serial )
	  ret[len(ret)+1] := item;
    endif
  endforeach
  return ret;
endfunction