use uo;
use os;

include "include/client";
include "include/attributes";

function summon_creature( caster,  npctemplate, cast_loc, duration )
  var thecreature;
  var thecritter;
  var magery := GetEffectiveSkill(caster, SKILLID_MAGERY);
  //var duration := 20;
  //var duration := 20 + (magery * 2);
  var parms := {};
  parms .+ script := "tamed";
  Detach();
  sleepms(100);
  
  thecritter := CreateNpcFromTemplate(npctemplate, cast_loc.x, cast_loc.y,cast_loc.z, parms, caster.realm);
  ParticleOnCharEffect(thecritter, 9521, 2);
  thecritter.facing := caster.facing;
  
  /*if(npctemplate == "summoneddaemon")
    PlaySoundEffect(caster, 535);
  else
    if(circle == 8)
      PlaySoundEffect(caster, 536);
      PerformAction(thecritter, 12);
    else
      PlaySoundEffect(caster, 534);
    endif
  endif*/
  SetObjProperty(thecritter,"master", caster.serial);
  //SetScriptController( thecritter);
  SetObjProperty(thecritter, "happiness",100);
  SetObjProperty(thecritter, "summoned",1);
  RestartScript(thecritter);
  SetBaseSkillBaseValue( thecritter, SKILLID_MAGICRESISTANCE,  magery * 10  );
  start_script("dispel",{thecritter, duration});
  return thecritter;
  //sleep(duration);
  
endfunction

function summon_creature_untamed( caster,  npctemplate, cast_loc, duration )
  var thecreature;
  var thecritter;
  var magery := GetEffectiveSkill(caster, SKILLID_MAGERY);
  //var duration := 20;
  //var duration := 20 + (magery * 2);
  /*var parms := {};
  parms .+ script := "tamed";*/
  Detach();
  sleepms(100);
  
  thecritter := CreateNpcFromTemplate(npctemplate, cast_loc.x, cast_loc.y,cast_loc.z, 0, caster.realm);
  ParticleOnCharEffect(thecritter, 9521, 2);
  thecritter.facing := caster.facing;
  
  /*if(npctemplate == "summoneddaemon")
    PlaySoundEffect(caster, 535);
  else
    if(circle == 8)
      PlaySoundEffect(caster, 536);
      PerformAction(thecritter, 12);
    else
      PlaySoundEffect(caster, 534);
    endif
  endif*/
  //SetObjProperty(thecritter,"master", caster.serial);
  //SetScriptController( thecritter);
  //SetObjProperty(thecritter, "happiness",100);
  //SetObjProperty(thecritter, "summoned",1);
  //RestartScript(thecritter);
  SetBaseSkillBaseValue( thecritter, SKILLID_MAGICRESISTANCE,  magery * 10  );
  start_script("dispel",{thecritter, duration});
  return thecritter;
  //sleep(duration);
  
endfunction

function RandomCoordModifier(coord, range)
 
 print("RandCOORD");
 var sign := RandomInt(2);
 print(cstr(sign));
 
 case sign
  0:
    print("POS");
    coord := coord + RandomInt(range);
    break;
  
  1:
     print("NEG");
     coord := coord + (0 - RandomInt(range));
     break;
  
endcase

//print(cstr(coord));
return coord;

endfunction