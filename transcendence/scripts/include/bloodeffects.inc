// blood effects by ArT-iX

function SendColoredBlood(victim)
  //print("BLOODEFFECT");
  var bloodcolor := 0;
  var npcdesc := readconfigfile("::npcdesc");
  if (!npcdesc)
  print ("Error: no npcdesc");
  endif
  
  if (victim.npctemplate)
  if(npcdesc[victim.npctemplate].BloodColor)
  bloodcolor := npcdesc[victim.npctemplate].BloodColor;
  if(bloodcolor == "noblood")
  return;
  endif
  endif
  else
  //	print("NOBLOODCOLOR");
  endif
  
  
  var objid;
  
  case (randomint(3) + 1)
  1: objid := 0x122b;
  2: objid := 0x122c;
  3: objid := 0x1cff;
  endcase
  
  var posx;
  var posy;
  
  case(randomint(3) + 1)
  1: posx := victim.x;
  2: posx := victim.x + 1;
  3: posx := victim.x - 1;
  
  endcase
  case(randomint(3) + 1)
  1: posy := victim.y;
  2: posy := victim.y + 1;
  3: posy := victim.y - 1;
  
  endcase
  
  var blooditm := CreateItemAtLocation( posx, posy, victim.z, objid, 1, victim.realm );
  blooditm.movable := 0;
  blooditm.decayAt := (readgameclock() + 20);
  blooditm.color := bloodcolor;
endfunction