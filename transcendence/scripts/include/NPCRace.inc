function SetNPCRace(thenpc)

print("SETTING RACE...");
var gr := thenpc.graphic;
Print(cstr(gr));
var gnome_raceM := 183;
var gnome_raceF := 184;
var giant_raceM := 744;
var giant_raceF := 745;
var race := GetObjProperty(thenpc, "Race");
if (race)
print("razza: " + race);
else
print("NO RACE SET!");
endif

if (race == "gnome")
 if ((gr == 0x190) || (gr == gnome_raceM))
  thenpc.graphic := gnome_raceM;
  thenpc.gender := 0;
  print("gnomemale");
 elseif ((gr == 0x191) || (gr == gnome_raceF))
  thenpc.graphic := gnome_raceF;
  thenpc.gender := 1;
  print("gnomfemale");
 endif
elseif (race == "giant")
 if ((gr == 0x190) || (gr == giant_raceM))
  thenpc.graphic := giant_raceM;
  thenpc.gender := 0;
  print("giantmale");
 elseif ((gr == 0x191) || (gr == gnome_raceF))
  thenpc.graphic := giant_raceF;
  thenpc.gender := 1;
  print("giantfemale");
 endif
endif

endfunction