var itemdefs := ReadConfigFile("::itemdesc");
const POISON_SOUND := 0x247;
const DRINK_SOUND := 0x32;
const UOBJ_EMPTY_BOTTLE := 0x0f0e;
const EFFECT_BLUE_SPARKLE  := 0x373a;
const SOUND_EFFECT_CURE	:= 0x1e1;
const EFFECT_SPARKLE  := 0x374a;
const HIT_ACTION := 0x148b;
const MOVING_EFFECT_PURPLE_POTION  := 0x0f0d;
const SOUND_EFFECT_EXPLOSION	:= 0x208;
const SOUND_EFFECT_HEAL	:= 0x1f3;
const EFFECT_EXPLOSION := 0x36b0;
//const SKILLID_TASTEID := 36;

include "include/attributes";
function checkifcandrink(character)

        if (GetObjProperty(character, "#potion"))
                if (GetObjProperty(character, "#potion") > ReadGameClock() )
                        SendSysMessage(character, "You must wait until you can drink another potion!");
                        return 0;
                else
               
                        SetObjProperty(character, "#potion", ReadGameClock() + 10);
                        return 1;
                endif
        else
                SetObjProperty(character, "#potion", ReadGameClock() + 10);
                return 1;
        endif
       

endfunction


function candrink(character)
        EraseObjProperty(character, "#potion");
endfunction

function empty_bottle(character, potion)

    PlaySoundEffect(character, DRINK_SOUND);
    CreateItemInBackpack(character, UOBJ_EMPTY_BOTTLE, 1);
    DestroyItem(potion);
    PlayObjectCenteredEffect( character, EFFECT_BLUE_SPARKLE, 10,10); 
   
endfunction

function get_potion_strength(potion)

        var potion_strength := itemdefs[potion.objtype].strength;

        return potion_strength;

endfunction

function is_poison(potion)

        var poison_level := GetObjProperty(potion, "poison_level");
        return poison_level;

endfunction

function do_poison(character, potion)


  var potion_strength := is_poison(potion);
        if (CheckSkill(character, 36, (potion_strength * 15),  (potion_strength * 15)))
                SendSysMessage(character, "That potion is poisonous!");
                return;
        endif
  empty_bottle(character, potion);
  PrintTextAbovePrivate(character, "You have been poisoned!", character);
  var poison_level :=CInt(GetObjProperty(character, "poison_level"));

    if ( poison_level > 0)
        poison_level := poison_level + potion_strength;
        SetObjProperty(character, "poison_level",CStr(poison_level));
    else
        poison_level := poison_level + potion_strength;
        SetObjProperty(character, "poison_level",CStr(poison_level));
        start_script( ":spells:poisondamage", character );
    endif

endfunction
