include "include/attributes";
function eatgrass(the_animal, char);

var xpos := the_animal.x;
var ypos := the_animal.y;

var thetile := GetMapInfo(xpos,ypos, the_animal.realm);
var tileinfo := thetile.landtile;
var ability := GetEffectiveSkill(char, SKILLID_HERDING);
var diffi := GetHarvestDifficulty("grass", xpos, ypos, tileinfo, the_animal.realm);
var success := CheckSkill(char, SKILLID_HERDING, diffi, 10);

if (success)

 var i;
 for (i := 0;i <= 3; i := i+1)
 eseguiverso(the_animal, char);
 PerformAction(the_animal, 0x0003);
 sleep(2);
 PerformAction(the_animal, 0x0003);
 sleep(2);
 PerformAction(the_animal, 0x0003);
 sleep(2);
 var amount := CInt(ability/10);
 var num := HarvestResource("grass", xpos, ypos, 1, amount);
 var alreadyeaten := GetObjProperty(the_animal, "eatengrass");
 if (!alreadyeaten)
  alreadyeaten := 0;
 endif
 var eat := alreadyeaten + num;
 SetObjProperty(the_animal, "eatengrass", eat);
 if (GetObjProperty(the_animal, "eatengrass") > 50)
   SendSysMessage(char, the_animal.name + " is stuffed!", FONT_NORMAL, 0x005a);
  
   SetObjProperty(the_animal, "eatengrass", 50);
   return;
 endif 
 var csl := RandomInt(100);
  if(csl < GetEffectiveSkill(char, SKILLID_HERDING))
    SetQuality(the_animal, char, num);
      if (GetObjProperty(the_animal, "milkquality") > 50)
        SetObjProperty(the_animal, "milkquality", 50);
      endif

  endif
 SendSysMessage(char, the_animal.name + " is eating the grass", FONT_NORMAL, 0x005a);
endfor
else

  SendSysMessage(char, the_animal.name + " doesn't like that grass!", FONT_NORMAL, 38);
  return;
endif  
endfunction


function SetQuality(theanim, char, num)

var val := GetObjProperty(theanim, "milkquality");
if (!val)
val := 0;
endif

var rnd := RandomInt(100);
var his_skill := GetEffectiveSkill(char, SKILLID_HERDING);
var rest := 100 - CInt(his_skill);
if (rnd < his_skill)
 var subval := rest/10;
 var subtract := RandomInt(subval);
 var award := num - subtract;
 val := val + award;
else
 val := val;
 var probdesease := RandomInt(100);
 var decreasevalue := CInt(his_skill / 10);
 decreasevalue := CInt(decreasevalue / 2) - 1;

 if (probdesease < 5 - decreasevalue)
  if (!GetObjProperty(theanim, "desease"))
  SetObjProperty(theanim, "desease", 1);
  endif
 else
  return;
 endif
endif

SetObjProperty(theanim, "milkquality", val);
if (GetObjProperty(theanim, "milkquality") < 0)
 SetObjProperty(theanim, "milkquality", 0);
endif

return val;
endfunction


