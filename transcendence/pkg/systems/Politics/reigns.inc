const ABS_MONARCHY := 0;
const PARL_MONARCHY := 1;
const OLIGARCHY : 2;
const REPUBLIC := 3;

function InitReignStruct()

  var Reign := struct;

  Reign.+name;
  Reign.+type;
  Reign.+territory;
  Reign.+governor;
  Reign.+towns;
  Reign.+capitol;
  Reign.+economy;
  Reign.+citizens;
  Reign.+enemies;
  Reign.+allies;
  
  return Reign;
  
endfunction  

function CreateReign(name, type)
 var Reign := InitReignStruct();
 Reign.name := name;
 Reign.type := type;
 return Reign;
endfunction

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

function ChangeReignType(byref reign, type)
 reign.type := type;
endfunction




  


