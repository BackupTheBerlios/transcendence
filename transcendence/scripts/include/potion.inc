include "include/attributes";
function is_reagent(what)
 
        if( (what.objtype >=  REAGENT_START) && (what.objtype <= REAGENT_STOP) )
                return  1;
        else
                return 0;
        endif
       
endfunction



function PourPotion(user,mortar)
   
        try_to_make_potion(user, "spacefill", 1, mortar, 0);

endfunction


function make_the_potion(user, mortar)


var use_on := Target( user );
    if (!use_on)
        SendSysMessage(user, "Targetting Cancelled", 0x003, 38);
        return;
    endif

if ( is_reagent(use_on) )

        var conf := ReadConfigFile("alchemy");
        if (!conf)
                print( "Couldn't open config file!");
                return;
        endif
           
        var elem := conf[use_on.objtype];
                if (!conf)
                print( "Couldn't find the element(elem)!");
        endif
           
        var possible := array;
        var tmenu := CreateMenu("Select a potion to make");
        var num_possibilities := 0;
        var selections := array;

        possible := GetConfigStringArray( elem, "potion");


        foreach thingie in possible
                if (can_make(user, thingie, use_on))
                        var titem := conf[thingie].objtype;
                        if(! titem)
                               
                        else
                                AddMenuItem( tmenu, titem, thingie );
                                num_possibilities := num_possibilities + 1;
                        endif
                else
                       
                endif
        endforeach
       
       
       
        if (num_possibilities == 0)
                SendSysMessage(user, "You can't make any potions!");
                return;
        endif

        var citem := SelectMenuItem2(user, tmenu);
        if (!citem.objtype)
                SendSysMessage(user, "Targetting canceled", 0x003, 38);
                return -1;
        endif       
        try_to_make_potion(user, possible[citem.index], 0, mortar, use_on);
else
        if (use_on.graphic == 0x0d1a)
         print("detected");
         var params := {};
         params[1] := user;
         params[2] := mortar;
         params[3] := use_on;
         start_script(":cooking:domust", params);
         return;
        endif
        SendSysMessage(user, "Hey, That's not a reagent!", 0x003, 38);

endif

endfunction

function can_make(user, potion, reg)

var skillneeded:= conf[potion].skill;

var amount_needed:= conf[potion].reagent_amount;

if (GetEffectiveSkill(user, SKILLID_ALCHEMY) >= (skillneeded-20))
        if ((reg.amount) && (reg.amount >= amount_needed))
                return 1;
	else
                return 0;
        endif
else
        return 0;
endif

endfunction


function take_regs(user, potion, reg)

        var amount_needed:= conf[potion].reagent_amount;
        SubtractAmount(reg, amount_needed);

endfunction


function try_to_make_potion(user, potion, in_mortar, mortar, reg)

var hasbottle:= 0;

if (!in_mortar)             //we have to check the skill, 'cause it's not in the mortar

	SendSysMessage(user,"You start grinding reagents..."); 

        var difficulty := conf[potion].skill;
        var points := conf[potion].points;
        var product := conf[potion].objtype;
        var cntr;
	var cx := user.x;
	var cy := user.y;

	repeat

	if (!can_make(user,potion,reg))
		SendSysMessage(user,"You stop griding reagents");
		return;
	endif

        for (cntr:= 1; cntr <= 4; cntr := cntr + 1)
                PlaySoundEffect(user, SOUND_EFFECT_GRIND);
		PerformAction( user, ANIM_SALUTE );
                sleepms(1500);
        endfor

        take_regs(user, potion, reg);       
	hasbottle:= 0;
        if (CheckSkill(user, SKILLID_ALCHEMY, difficulty, points))
                set_critical(1);
                foreach item in EnumerateItemsInContainer(user.backpack)
                        if (item.objtype == UOBJECT_EMPTY_BOTTLE)
                                SubtractAmount(item, 1);
                                hasbottle := 1;
                                break;
                        endif
                endforeach
                set_critical(0);
		if (hasbottle)
                        var thing := CreateItemInBackpack(user, product, 1);
                        PlaySoundEffect(user, SOUND_EFFECT_POUR);
                else
                        PrintTextAbovePrivate(user, "With no bottles, you are forced to store the mixture in your mortar", user);
                        SetObjProperty(mortar, "contents", product);
			SendSysMessage(user,"You stop griding reagents");
                        return;
                endif
        else
                PlaySoundEffect(user, SOUND_EFFECT_POUR);
                PrintTextAbovePrivate(user, "You pour out the useless mixture", user);
        endif

	sleep(2);
	until ((user.x != cx) || (user.y != cy));
	SendSysMessage(user,"You stop griding reagents");
	return;
else

        set_critical(1);
        foreach item in EnumerateItemsInContainer(user.backpack)
                if (item.objtype == UOBJECT_EMPTY_BOTTLE)
                        SubtractAmount(item, 1);
                        hasbottle := 1;
                        break;
                endif
                endforeach
               
                set_critical(0);

                if (hasbottle)
                        var product := GetObjProperty(mortar, "contents");
                        var thing := CreateItemInBackpack(user, product, 1);
                        PlaySoundEffect(user, SOUND_EFFECT_POUR);
                        PrintTextAbovePrivate(user, "You create the item and put it in your backpack", user);
                        EraseObjProperty( mortar, "contents" );
                        return;
                else
                        PrintTextAbovePrivate(user, "You have no bottles to pour this into", user);
                        return;
                endif
               
endif


endfunction