function rogue_ent_setup(me)


var trunk_objtype;
	var leaves_objtype;
	case (RandomInt(15))
		0:	trunk_objtype := 0xccd;
			leaves_objtype := 0xcce;
		1:	trunk_objtype := 0xcd0;
			leaves_objtype := 0xcd1;
		2:	trunk_objtype := 0xcd3;
			leaves_objtype := 0xcd4;
		3:	trunk_objtype := 0xcd6;
			leaves_objtype := 0xcd7;
		4:	trunk_objtype := 0xcda;
			leaves_objtype := 0xcdb;
		5:	trunk_objtype := 0xcdd;
			leaves_objtype := 0xcde;
		6:	trunk_objtype := 0xce0;
			leaves_objtype := 0xce1;
		7:	trunk_objtype := 0xce3;
			leaves_objtype := 0xce4;
		8:	trunk_objtype := 0xce6;
			leaves_objtype := 0xce7;
		9:	trunk_objtype := 0xd94;
			leaves_objtype := 0xd96;
		10:	trunk_objtype := 0xd98;
			leaves_objtype := 0xd9a;
		11:	trunk_objtype := 0xd9c;
			leaves_objtype := 0xd9e;
		12:	trunk_objtype := 0xda0;
			leaves_objtype := 0xda2;
		13:	trunk_objtype := 0xda4;
			leaves_objtype := 0xda6;
		14:	trunk_objtype := 0xda8;
			leaves_objtype := 0xdaa;
	endcase;

SetObjProperty(me, "treetype", {trunk_objtype, leaves_objtype});
me.hidden := 1;
me.frozen := 1;
var item_trunk := CreateItemAtLocation (me.x, me.y, me.z, trunk_objtype, 1, me.realm);
	item_trunk.movable := 0;
	var item_leaves := CreateItemAtLocation (me.x, me.y, me.z, leaves_objtype, 1, me.realm);
	item_leaves.movable := 0;
SetObjProperty(me, "tree", {item_trunk.serial, item_leaves.serial});
endfunction

function EntAppear(me)

var tree;
tree := GetObjProperty(me, "tree");
sleep(5);
destroyitem (SystemFindObjectBySerial( tree[1]));
destroyitem (SystemFindObjectBySerial( tree[2]));

me.frozen := 0;
me.hidden := 0;
endfunction

function EntSleep(me)

var treetype := GetObjProperty(me, "treetype");
var trunk_objtype := treetype[1];
var leaves_objtype := treetype[2];
if(!me.hidden)
var item_trunk := CreateItemAtLocation (me.x, me.y, me.z, trunk_objtype, 1, me.realm);
	item_trunk.movable := 0;
	var item_leaves := CreateItemAtLocation (me.x, me.y, me.z, leaves_objtype, 1, me.realm);
	item_leaves.movable := 0;
SetObjProperty(me, "tree", {item_trunk.serial, item_leaves.serial});
endif

me.hidden := 1;
me.frozen := 1;

endfunction