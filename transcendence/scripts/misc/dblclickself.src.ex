use uo;
use os;
use npc;

include "include/eventID";

program dblclickself( me )
	var mount := GetEquipmentByLayer( me, 25 );
	if (!mount)
		OpenPaperdoll( me, me );
		return;
	endif
	if (me.warmode)
		OpenPaperdoll( me, me );
		return;
	endif
    var serial := GetObjProperty(mount, "serial");
	var animal := SystemFindObjectBySerial(CInt(serial));
    EraseObjProperty(animal,"serial");
    EraseObjProperty(animal,"mounted");
    EraseObjProperty(animal,"mounted_on");
	animal.facing := me.facing;
	var ev := array;
    ev.+ type;
    ev.+ source;
    ev.type := EVID_WAKEUP;
    ev.source := me;
    SendEvent(animal, ev);
    MoveCharacterToLocation(animal, me.x, me.y, me.z, MOVECHAR_FORCELOCATION);
    RestartScript(animal);
	DestroyItem( mount );
endprogram