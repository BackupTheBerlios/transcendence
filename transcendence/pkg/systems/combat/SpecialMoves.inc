//include "include/packets";

function ProcessSpecialMoves (attacker, defender, weapon, byref armor, byref basedamage, byref rawdamage )
var MoveID := GetObjProperty(attacker, "SpecMov");
if(!MoveID)
return;
endif

if (MoveID == 1)

 ArmorIgnore(attacker, defender, weapon, armor, basedamage, rawdamage);

elseif (MoveID == 2)

 BleedAttack(attacker, defender, weapon, armor, basedamage, rawdamage);
 
elseif (MoveID == 3)

 //ConcussionBlow(attacker, defender, weapon, armor, basedamage, rawdamage);
 
elseif (MoveID == 4)

 CrushinBlow(attacker, defender, weapon, armor, basedamage, rawdamage);

elseif (MoveID == 5)

 Disarm(attacker, defender, weapon, armor, basedamage, rawdamage);
  
elseif (MoveID == 6)

 Dismount(attacker, defender, weapon, armor, basedamage, rawdamage); 
 
elseif (MoveID == 7)

 DoubleStrike(attacker, defender, weapon, armor, basedamage, rawdamage); 
 
elseif (MoveID == 8)

 //Infect(attacker, defender, weapon, armor, basedamage, rawdamage); 
 
elseif (MoveID == 9)

 //MortalStrike(attacker, defender, weapon, armor, basedamage, rawdamage); 
 
elseif (MoveID == 10)

 //MovingShot(attacker, defender, weapon, armor, basedamage, rawdamage); 
 
elseif (MoveID == 11)

 ParalyzingBlow(attacker, defender, weapon, armor, basedamage, rawdamage); 

elseif (MoveID == 12)

 ShadowStrike(attacker, defender, weapon, armor, basedamage, rawdamage); 
 
elseif (MoveID == 13)

 WhirlwindAttack(attacker, defender, weapon, armor, basedamage, rawdamage); 
 
endif
endfunction

function DeactivateSpecialMovesIcons(who)
var packet := CreatePacket(0xBF, 5);
packet.setInt16(1, 5);
packet.setInt16(3, 0x21);
packet.sendPacket(who);
endfunction

function DeactivateSpecialMove(who)
DeactivateSpecialMovesIcons(who);
EraseObjProperty(who, "SpecMov");
endfunction

function ArmorIgnore(attacker, defender, weapon, byref armor, byref basedamage, byref rawdamage)

SendsysMessage(attacker, "You trapass enemy's armor");
SendsysMessage(defender, "You've been hit through your armor");
rawdamage := basedamage;
DeactivateSpecialMove(Attacker);

endfunction

function BleedAttack(attacker, defender, weapon, byref armor, byref basedamage, byref rawdamage)

SendsysMessage(attacker, "You made your enemy bleed");
SendsysMessage(defender, "You're bleeding");
//rawdamage := basedamage;
var parms := {defender, rawdamage};
if(!start_script(":SpecialMoves:Bleeding", parms))
SendSysMessage(attacker, "Bleed script not found!!");
endif
DeactivateSpecialMove(Attacker);

endfunction

function CrushinBlow(attacker, defender, weapon, byref armor, byref basedamage, byref rawdamage)

/*if(!GetEquipmentByLayer( defender, 25 ))
return;
endif*/
print("OLDDAMAGE: " + cstr(rawdamage));
SendsysMessage(attacker, "You hit very hardly!!");
SendsysMessage(defender, "You've been hit very harldy!");
rawdamage := rawdamage + (rawdamage / 2);
PlayCharAnim( attacker, 227 );
////start_script(":SpecialMoves:Bleeding", defender);
DeactivateSpecialMove(Attacker);

endfunction

function Disarm(attacker, defender, weapon, byref armor, byref basedamage, byref rawdamage)

var weap := GetEquipmentByLayer( defender, 1 );
if(!weap)
if(GetEquipmentByLayer( defender, 2 ).isA(POLCLASS_WEAPON))
weap := GetEquipmentByLayer( defender, 2 );
endif
endif

SendsysMessage(attacker, "You disarm your enemy!!");
SendsysMessage(defender, "You've been disarmed by your enemy's hit!");
//rawdamage := rawdamage + (rawdamage / 10);
//start_script (":SpecialMoves:Dismount", defender);
//start_script(":SpecialMoves:Bleeding", defender);

MoveItemToLocation( weap, defender.x, defender.y, defender.z );

DeactivateSpecialMove(Attacker);

endfunction


function Dismount(attacker, defender, weapon, byref armor, byref basedamage, byref rawdamage)

if(!GetEquipmentByLayer( defender, 25 ))
return;
endif

SendsysMessage(attacker, "You made your enemy dismount");
SendsysMessage(defender, "You've been dismounted by your enemy's hit!");
rawdamage := rawdamage + (rawdamage / 10);
start_script (":SpecialMoves:Dismount", defender);
//start_script(":SpecialMoves:Bleeding", defender);
DeactivateSpecialMove(Attacker);

endfunction

function DoubleStrike(attacker, defender, weapon, byref armor, byref basedamage, byref rawdamage)



SendsysMessage(attacker, "You hit twice!");
SendsysMessage(defender, "You've been hit twice!");
PlayCharAnim( attacker, 204 );
DealDamage( defender, attacker,rawdamage);
SendVisualHPloss(attacker, defender, rawdamage);
DeactivateSpecialMove(Attacker);

endfunction

function ParalyzingBlow(attacker, defender, weapon, byref armor, byref basedamage, byref rawdamage)



SendsysMessage(attacker, "You paralyze your enemy!");
SendsysMessage(defender, "You've been paralyzed by enemy!");
PlayCharAnim( attacker, 204 );
//DealDamage( defender, attacker,rawdamage);
//SendVisualHPloss(attacker, defender, rawdamage);
defender.frozen := 1;
Detach(); 
sleep(10);
defender.frozen := 0;
DeactivateSpecialMove(Attacker);

endfunction

function WhirlwindAttack(attacker, defender, weapon, byref armor, byref basedamage, byref rawdamage)

/*if(!GetEquipmentByLayer( defender, 25 ))
return;
endif*/

SendsysMessage(attacker, "You hit all your enemies");
//SendsysMessage(defender, "You hit all your enemies");
var fac := attacker.facing;
foreach mob in ListMobilesNearLocation( attacker.x,attacker.y,attacker.z, 1 )
if(mob.serial != defender.serial)
pgface(attacker, mob);
PlayCharAnim( attacker, 204); //210 );
DealDamage(mob, attacker, rawdamage);
SendVisualHPloss(attacker, mob, rawdamage);
SendEvent( mob, 0x00000002);

endif
endforeach
attacker.facing := fac;
//rawdamage := rawdamage + (rawdamage / 10);
//start_script (":SpecialMoves:Dismount", defender);
//start_script(":SpecialMoves:Bleeding", defender);
DeactivateSpecialMove(Attacker);

endfunction

function ShadowStrike(attacker, defender, weapon, byref armor, byref basedamage, byref rawdamage)

/*if(!GetEquipmentByLayer( defender, 25 ))
return;
endif*/

SendsysMessage(attacker, "You hide after attack!!");
SendsysMessage(defender, "Your enemy disappeared!!");
//rawdamage := rawdamage + (rawdamage / 2);
////start_script(":SpecialMoves:Bleeding", defender);

attacker.hidden := 1;
DeactivateSpecialMove(Attacker);

endfunction


function PlayCharAnim( who, anim, speed := 0, dir := 0)
    var packetstring := "6E";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(anim),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + "0001"; //Repitition
    packetstring := packetstring + fixPacketLength(Hex(dir),1);
    packetstring := packetstring + "00"; //Does this animation repeat?
    packetstring := packetstring + fixPacketLength(Hex(speed),1);
    foreach chr in ListMobilesNearLocation( who.x, who.y, who.z, 16 );
        SendPacket( chr, packetstring );
    endforeach
endfunction