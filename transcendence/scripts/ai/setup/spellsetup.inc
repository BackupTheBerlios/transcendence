var speech;
var master;
var spells := {};
var me := Self();

var cast_pct;
var num_casts;
var count_casts;
var saywords := 1;
var summons := 3;

var will_cast;
var flee_point;

var npccfg := ReadConfigFile("npcdesc");
var speechelem := npccfg[me.npctemplate];
speech := GetConfigString(speechelem, "speech");
spells := GetConfigStringArray( speechelem, "spell" );
cast_pct := speechelem.cast_pct;
num_casts  := speechelem.num_casts;
count_casts  := speechelem.count_casts;
saywords := speechelem.saywords;
if (!cast_pct)
        cast_pct := 10;
endif
flee_point := speechelem.flee_point;
if (!flee_point)
        flee_point := 10;
endif

if (!me.backpack)
	var newbackpack := CreateItemAtLocation(me.x, me.y, me.z, 0xe75,1, me.realm);
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
	elseif (npccfg[me.npctemplate].equip)
    		EquipFromTemplate(me, npccfg[me.npctemplate].equip);
	endif

	if( me.name["<random>"] )
		if ((me.graphic == 400) || (me.graphic == 401))
			me.graphic := 400 + RandomInt(2);
		endif
		SetName( me, RandomName( me ) );
	endif

	if ( npccfg[me.npctemplate].mount )
		var mymount := CreateItemAtLocation(5288,1176,0,0xf021,1);
		var mountparms := SplitWords(npccfg[me.npctemplate].mount);
		mymount.graphic := CInt(mountparms[1]);
		mymount.color := CInt(mountparms[2]);
		EquipItem(me, mymount);
	endif

endif