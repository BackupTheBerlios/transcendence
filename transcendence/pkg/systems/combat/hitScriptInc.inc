use uo;
use util;
use math;
use polsys;

include "include/AOSPackets";
include "include/attributes";

include "include/particles";

function DealDamage(defender, attacker, rawdamage)
  
  rawdamage := rawdamage + RandomInt( (GetEffectiveSkill(attacker, 1) ) / 20);
  //print("ATTACKER: " + attacker.name + " DEFENDER: " + defender.name); 
  if(!defender.npctemplate)
  SendVisualHPloss(defender, defender, rawdamage);
  endif
  if(!attacker.npctemplate)
  SendVisualHPloss(attacker, defender, rawdamage);
  endif
  if(defender.npctemplate == "fireelemental")
  PlayOnCharEffect(defender, 5044, layer := 3);
  endif
  ApplyRawDamage(defender, rawdamage);
  
  if((GetObjProperty(attacker, "Vampire")) || (GetObjProperty(attacker, "NecroVampire")))
   SetHp(attacker, GetHp(attacker) + rawdamage);
  endif
  var linked := GetObjProperty(defender, "LinkedAura");
  if(linked)
   ApplyRawDamage(SystemfindObjectBySerial(linked), rawdamage);
  endif
  SendColoredBlood(defender);
endfunction

function AdjustNoto(attacker, defender)
  if!(defender.dead)
	return 0;
  endif
  var karma := CInt(GetObjProperty(attacker, "Karma") );
  var fame := CInt(GetObjProperty(attacker, "Fame") );
  var vkarma := CInt(GetObjProperty(defender, "Karma") );
  var vfame := CInt(GetObjProperty(defender, "Fame") );
  var kmod := 1;
  fame := fame + CInt( (vfame / 10) / ( CInt(Log10(fame)) + 1 ) );
  if !(defender.npctemplate)
	vfame := CInt(vfame * 0.9);
  endif
  if((karma < -15) && (vkarma < -15))
	return;
  endif
  if(vkarma > 15)
	kmod := -1;
	karma := Abs(karma);
  else
	vkarma := Abs(vkarma);
  endif
  kmod := kmod * CInt( (vkarma / 10) / ( CInt(Log10(karma)) + 1 ) );
  karma := karma + kmod;
endfunction