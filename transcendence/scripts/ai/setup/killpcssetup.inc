include "include/vetement";
var me := Self();

var npccfg := ReadConfigFile("npcdesc");
var speechelem := npccfg[me.npctemplate];
var flee_point := speechelem.flee_point;
var equiptm;
if (!flee_point)
        flee_point := 10;
endif

equiptm := npccfg[me.npctemplate].equip;


if (!me.backpack)
	var newbackpack := CreateItemAtLocation(5288,1176,0, 0xe75,1);
	EquipItem(me, newbackpack);
	if (npccfg[me.npctemplate].colorrange)
		var parms := SplitWords(npccfg[me.npctemplate].colorrange);
		me.color := RandomInt(CInt(parms[2]) - CInt(parms[1]))+CInt(parms[1]);
	endif
	if (npccfg[me.npctemplate].dress)
		var parms := {};
		parms[1]:= me;
		parms[2]:= npccfg[me.npctemplate].dress;
		start_script("::/misc/dressme", parms);
	elseif (equiptm)
    		set_priority(50);
       		Habille( me, equiptm );
       		set_priority(1);
	endif

	if( me.name["<random>"] )
		if ((me.graphic == 400) || (me.graphic == 401))
			me.graphic := 400 + RandomInt(2);
		endif
		if (npccfg[me.npctemplate].title)
			var title := RandomInt(20);
			var ttitle := "";

			case (title)
        	  	0: ttitle := "";
          		1: ttitle := " the townsperson";
	          	2: ttitle := " the farmer";
        	  	3: ttitle := " the sailor";
	          	4: ttitle := " the drunkard";
	          	5: ttitle := " the wanderer";
	          	6: ttitle := " the villager";
	          	7: ttitle := " the gypsie";
	          	8: ttitle := " the vagabond";
	          	9: ttitle := " the laborer";
        		default: ttitle := "";
			endcase
			var tname := randomname(me);
			SetName(me, tname + ttitle);
		else
			SetName( me, randomname( me ) );
		endif
	endif

	if ( npccfg[me.npctemplate].mount )
		var mymount := CreateItemAtLocation(5288,1176,0,0xf021,1);
		var mountparms := SplitWords(npccfg[me.npctemplate].mount);
		mymount.graphic := CInt(mountparms[1]);
		mymount.color := CInt(mountparms[2]);
		EquipItem(me, mymount);
	endif


endif