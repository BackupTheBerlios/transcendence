// 3D Particle effects by ArT-iX

//////////////CONSTANTS///////////////////////

const PART_FUOCOPERM := 8011;
const PART_FULMINE := 5031;
const PART_RIFRAZ_VERDI := 9935;
const PART_AURANERA := 9909;
const PART_AZURE_FIREBALL := 3043;
const PART_STAR_EXPLO := 4043;
const PART_AURA_RING := 5004;
const PART_ASC_PARTICLES := 5007;
const PART_SPIRAL_FIRERING := 5008;
const PART_MEDUSA_AURA := 5009;
const PART_ASC_SPIRAL := 5010;
const PART_AMULTICOLOR_GLOWS := 5011;
const PART_ASC_SPIRAL_SMALL := 5012;
const PART_DESC_BLUESPIRAL := 5013;
const PART_BLUE_STICKS := 5014;


///////////////////////////////////////////////


function Play3DLightningBoltEffect(who)
var PacketHexString := "C703"+ ConvertIntToHex(who.serial, 4);
PacketHexString := PacketHexString
+"0000000000000E260A15000E260A1500000000000000000000000000000013A700000000";
PacketHexString := PacketHexString + ConvertIntToHex(who.serial, 4);
PacketHexString := PacketHexString +"030000";
foreach mobile in ListMobilesNearLocationEx(who.x, who.y, who.z,
20, LISTEX_FLAG_NORMAL + LISTEX_FLAG_HIDDEN + LISTEX_FLAG_GHOST, who.realm)
//if ((mobile.ip) and (GetObjProperty(mobile, "3dclientversion")))
SendPacket(mobile, PacketHexString);
//endif
endforeach
endfunction

function PlayOnCharEffect(char, effect, layer := 3)
var PacketHexString := "C703"+ ConvertIntToHex(char.serial, 4);
effect := ConvertIntToHex(effect, 2);
//effect := "13a7";
PacketHexString := PacketHexString
+"0000000000000E260A15000E260A15000000000000000000000000000000" + effect + "00000000";
PacketHexString := PacketHexString + ConvertIntToHex(char.serial, 4);
PacketHexString := PacketHexString + "03" + "0000";
foreach mobile in ListMobilesNearLocationEx(char.x, char.y, char.z, 20, LISTEX_FLAG_NORMAL + LISTEX_FLAG_HIDDEN + LISTEX_FLAG_GHOST, char.realm)
//if ((mobile.ip) and (GetObjProperty(mobile, "3dclientversion")))
SendPacket(mobile, PacketHexString);
//endif
endforeach
endfunction

////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////



function PlayMovingParticleEffect(src, dest, fx2D,  effect, fx2, fx3,  speed := 10)
var PacketHexString := "C700"+ ConvertIntToHex(src.serial, 4);
effect := ConvertIntToHex(effect, 2);
var destserial := ConvertIntToHex(dest.serial, 4);
speed := ConvertIntToHex(speed, 1);
fx2 := ConvertIntToHex(fx2, 2);
fx3 := ConvertIntToHex(fx3, 2);
fx2D := ConvertIntToHex(fx2D, 2);

PacketHexString := PacketHexString
+ destserial + fx2D + ConvertIntToHex(src.x, 2) + ConvertIntToHex(src.y, 2) + ConvertIntToHex(src.z, 1) + ConvertIntToHex(dest.x, 2) + ConvertIntToHex(dest.y, 2) + ConvertIntToHex(dest.z, 1) + speed + "00000000010000003f00000000" + effect + "0FCB" + fx2;
PacketHexString := PacketHexString + ConvertIntToHex(0, 4);
PacketHexString := PacketHexString + "FF" + fx3;
foreach mobile in ListMobilesNearLocationEx(src.x, src.y, src.z, 20, LISTEX_FLAG_NORMAL + LISTEX_FLAG_HIDDEN + LISTEX_FLAG_GHOST, who.realm)
//if ((mobile.ip) and (GetObjProperty(mobile, "3dclientversion")))
SendPacket(mobile, PacketHexString);
//print(PacketHexString);
//endif
endforeach
endfunction

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


function ParticleMovingEffect(src, dest, effect2D,  effect3D, explode := 0, explodefx := 5044,speed := 10, duration := 0, fstrike := 0, fixdir := 0)

var packet := CreatePacket(0xC7, MSGLEN_VARIABLE);
packet.setInt8(1, 0); // effetto movimento
packet.setInt32(2, src.serial);
packet.setInt32(6, dest.serial);
packet.setInt16(10, effect2D);
packet.setInt16(12, src.x);
packet.setInt16(14, src.y);
packet.setInt8(16, src.z);
packet.setInt16(17, dest.x);
packet.setInt16(19, dest.y);
packet.setInt8(21, dest.z);
packet.setInt8(22, speed);
packet.setIn8(23, duration);
packet.setInt16(24, fstrike);
packet.setInt8(26, fixdir);
packet.setInt8(27, explode);
packet.setInt32(28, 0);
packet.setInt32(32, 0);
packet.setInt16(36, effect3D);
if(explode == 1)
packet.setInt16(38, explodefx);
else
packet.setInt16(38, 0);	
endif
packet.setInt16(40, 0x211); //fx2
packet.setInt32(42, 0);
packet.setInt8(46, 0xFF);
packet.setInt16(47, 0); // fx3

packet.sendAreaPacket(src.x, src.y, 10, src.realm);

endfunction

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


function ParticleMovingEffectXYZ(srcx, srcy, srcz, destx, desty, destz, effect2D,  effect3D, realm := "britannia",explode := 0, explodefx := 5044,speed := 10, duration := 0, fstrike := 0, fixdir := 0)

var packet := CreatePacket(0xC7, MSGLEN_VARIABLE);
packet.setInt8(1, 0); // effetto movimento
packet.setInt32(2, 0);
packet.setInt32(6, 0);
packet.setInt16(10, effect2D);
packet.setInt16(12, srcx);
packet.setInt16(14, srcy);
packet.setInt8(16, srcz);
packet.setInt16(17, destx);
packet.setInt16(19, desty);
packet.setInt8(21, destz);
packet.setInt8(22, speed);
packet.setIn8(23, duration);
packet.setInt16(24, fstrike);
packet.setInt8(26, fixdir);
packet.setInt8(27, explode);
packet.setInt32(28, 0);
packet.setInt32(32, 0);
packet.setInt16(36, effect3D);
if(explode == 1)
packet.setInt16(38, explodefx);
else
packet.setInt16(38, 0);	
endif
packet.setInt16(40, 0x211); //fx2
packet.setInt32(42, 0);
packet.setInt8(46, 0xFF);
packet.setInt16(47, 0); // fx3

packet.sendAreaPacket(srcx, srcy, 10, realm);

endfunction

///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////


function ParticleOnCharEffect(onwhom, effect3D, layer , speed := 0, duration := 0)

var packet := CreatePacket(0xC7, 0x31);
packet.setInt8(1, 3); // effetto object centered
packet.setInt32(2, onwhom.serial);
packet.setInt32(6, 0);
packet.setInt16(10, 0);
//packet.setInt16(12, onwhom.x);
packet.setInt16(12, 0xE26);
//packet.setInt16(14, onwhom.y);
packet.setInt16(14, 0xA15);
//packet.setInt8(16, onwhom.z + 7);
packet.setInt8(16, 0);
//packet.setInt16(17, onwhom.x);
packet.setInt16(17, 0xE26);
//packet.setInt16(19, onwhom.y);
packet.setInt16(19, 0xA15);
//packet.setInt8(21, onwhom.z + 7);
packet.setInt8(21, 0);
packet.setInt8(22, speed);
packet.setIn8(23, duration);
packet.setInt16(24, 0);
packet.setInt8(26, 0);
packet.setInt8(27, 0);
packet.setInt32(28, 0);
packet.setInt32(32, 0);
packet.setInt16(36, effect3D);
//if(explode = 1)

//else
packet.setInt16(38, 0);	
//endif
packet.setInt16(40, 0); //fx2
packet.setInt32(42, onwhom.serial);
packet.setInt8(46, layer);
packet.setInt16(47, 0); // fx3
//print(packet);
var check_str := packet.sendAreaPacket(onwhom.x, onwhom.y, 10, onwhom.realm);
print("SENDAREA STR: " + cstr(check_str));
endfunction

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

function ParticleStationaryEffect(x, y, z, effect3D, realm := "britannia", speed := 0, duration := 0)

var packet := CreatePacket(0xC7, MSGLEN_VARIABLE);
packet.setInt8(1, 2); // effetto object centered
packet.setInt32(2, 0);
packet.setInt32(6, 0);
packet.setInt16(10, 0);
packet.setInt16(12, x);
packet.setInt16(14, y);
packet.setInt8(16, z);
packet.setInt16(17, x);
packet.setInt16(19, y);
packet.setInt8(21, z);
packet.setInt8(22, speed);
packet.setIn8(23, duration);
packet.setInt16(24, 0);
packet.setInt8(26, 0);
packet.setInt8(27, 0);
packet.setInt32(28, 0);
packet.setInt32(32, 0);
packet.setInt16(36, effect3D);
//if(explode = 1)

//else
packet.setInt16(38, 0);	
//endif
packet.setInt16(40, 0); //fx2
packet.setInt32(42, 0);
packet.setInt8(46, 0);
packet.setInt16(47, 0); // fx3

packet.sendAreaPacket(x, y, 10, realm);

endfunction

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

function ParticleStationaryEffectPrivate(who, x, y, z, effect3D,  speed := 0, duration := 0)

var packet := CreatePacket(0xC7, MSGLEN_VARIABLE);
packet.setInt8(1, 2); // effetto object centered
packet.setInt32(2, 0);
packet.setInt32(6, 0);
packet.setInt16(10, 0);
packet.setInt16(12, x);
packet.setInt16(14, y);
packet.setInt8(16, z);
packet.setInt16(17, x);
packet.setInt16(19, y);
packet.setInt8(21, z);
packet.setInt8(22, speed);
packet.setIn8(23, duration);
packet.setInt16(24, 0);
packet.setInt8(26, 0);
packet.setInt8(27, 0);
packet.setInt32(28, 0);
packet.setInt32(32, 0);
packet.setInt16(36, effect3D);
//if(explode = 1)

//else
packet.setInt16(38, 0);	
//endif
packet.setInt16(40, 0); //fx2
packet.setInt32(42, 0);
packet.setInt8(46, 0);
packet.setInt16(47, 0); // fx3

packet.sendPacket(who);

endfunction

///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Particle On Item Effect//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

function ParticleOnItemEffect(itm, effect3D,  speed := 0, duration := 0)

var packet := CreatePacket(0xC7, MSGLEN_VARIABLE);
packet.setInt8(1, 2); // effetto object centered
packet.setInt32(2, 0);
packet.setInt32(6, 0);
packet.setInt16(10, 0);
packet.setInt16(12, itm.x);
packet.setInt16(14, itm.y);
packet.setInt8(16, itm.z);
packet.setInt16(17, itm.x);
packet.setInt16(19, itm.y);
packet.setInt8(21, itm.z);
packet.setInt8(22, speed);
packet.setIn8(23, duration);
packet.setInt16(24, 0);
packet.setInt8(26, 0);
packet.setInt8(27, 0);
packet.setInt32(28, 0);
packet.setInt32(32, 0);
packet.setInt16(36, effect3D);
//if(explode = 1)

//else
packet.setInt16(38, 0);	
//endif
packet.setInt16(40, 0); //fx2
packet.setInt32(42, 0);
packet.setInt8(46, 0);
packet.setInt16(47, 0); // fx3

packet.sendAreaPacket(itm.x, itm.y, 10, itm.realm);

endfunction

////////////////////////////////////////////////////////////////////////

function ParticleOnCharEffectWithSound(onwhom, effect3D, layer , soundFX, speed := 0, duration := 0)
ParticleOnCharEffect(onwhom, effect3D, layer , speed, duration);
PlaySoundEffect( who, soundFX );
endfunction

///////////////////////////////////////////////////////////////////////

function ParticleMovingEffectWithSound(src, dest, effect2D,  effect3D, soundFX, explode := 0, explodefx := 5044,speed := 10, duration := 0, fstrike := 0, fixdir := 0)
ParticleMovingEffect(src, dest, effect2D,  effect3D, explode , explodefx ,speed , duration , fstrike , fixdir );
PlaySoundEffect( who, soundFX );
endfunction

////////////////////////////////////////////////////////////////////////

function ParticleStatEffectWithSound(x, y, z, effect3D, soundFX, realm := "britannia", speed := 0, duration := 0)
ParticleStationaryEffect(x, y, z, effect3D,  realm, speed , duration );
PlaySoundEffect( who, soundFX );
endfunction

////////////////////////////////////////////////////////////////////////

function PlaySequentialEffects(onwhom, effectsarray)
var fxID;
var fxDuration;
foreach fx in
fxID := fx[1];
fxDuration := fx[2];
ParticleOnCharEffect(onwhom, fxID, 2 , 0,  0);
sleepms(fxDuration);
endforeach
endfunction

////////////////////////////////////////////////////////////////////////

function PlaySequentialEffectsWithSound(onwhom, effectsarray)
var fxID;
var fxDuration;
var soundFX;

foreach fx in
fxID := fx[1];
fxDuration := fx[2];
soundFX := fx[3];;
ParticleOnCharEffect(onwhom, fxID, 2 , 0,  0);
PlaySoundEffect( who, soundFX );
sleepms(fxDuration);
endforeach
endfunction


//////////////////////////////////////////////////////////////////////////










function ConvertIntToHex(astring, alength)
astring := Hex(astring);
astring := CStr(astring);
if (astring["0x"])
astring := astring[3, len(astring)];
endif
if (len(astring) > alength * 2)
return;
endif
while (len(astring) < alength * 2)
astring := "0"+ astring;
endwhile
return astring;
endfunction

function fixPacketLength( packetString, byteLength )
    if( !packetString || packetString == error )
        packetstring := 0;
    endif
    packetstring := CStr(packetstring);
   
    if( packetstring[1,2] == "0x" )
        packetstring := CStr(packetstring[3,len(packetstring)]);
    endif
   
    if( len(packetstring) > byteLength * 2 )
        var extrabytes := (byteLength*2) - len(packetstring);
        return CStr(packetstring[extrabytes,len(packetstring)]);
    endif
   
    while( len(packetstring) < byteLength * 2 )
        packetstring := "0" + packetstring;
    endwhile
   
    return packetstring;
endfunction
/*
0xC0 Packet

Last Modified on Friday, 26-Jul-2002  

 

 

(yet another) Graphical Effect (36 Bytes)

BYTE cmd 
BYTE type 
BYTE[4] sourceSerial 
BYTE[4] targetSerial 
BYTE[2] itemID 
BYTE[2] xSource 
BYTES[2] ySource 
BYTE zSource 
BYTE[2] xTarget 
BYTE[2] yTarget 
BYTE zTarget 
BYTE speed 
BYTE duration 
BYTE[2] unk // On OSI, flamestrikes are 0x0100 
BYTE fixedDirection 
BYTE explodes 
BYTE[4] hue 
BYTE[4] renderMode 
 Server message

0x70 Packet

Last Modified on Friday, 20-Nov-1998 

Graphical Effect (28 bytes) 

·        BYTE cmd 

·        BYTE direction type 

·        00 = go from source to dest 

·        01 = lightning strike at source 

·        02 = stay at current x,y,z 

·        03 = stay with current source character id 

·        BYTE[4] character id 

·        BYTE[4] target id

·        BYTE[2] model of the first frame of the effect

·        BYTE[2] xLoc 

·        BYTE[2] yLoc 

·        BYTE zLoc 

·        BYTE[2] xLoc of target 

·        BYTE[2] yLoc of target 

·        BYTE zLoc of target 

·        BYTE speed of the animation

·        BYTE duration (0=really long, 1= shortest)

·        BYTE[2] unknown2 (0 works)

·        BYTE adjust direction during animation (1=no)

·        BYTE explode on impact  

 

0xC7 Packet

Last Modified on Sunday, 28-Jul-2002  

 

3D client particle effect (49 Bytes)

BYTE cmd 
BYTE[35]…. Preamble … exactly like 0xC0 
BYTE[2] effect # (see particleffect subdir!) 
BYTE[2] explode effect # (0 if no explosion) 
BYTE[2] additional effect # that’s only used for moving effects, 0 otherwise 
BYTE[4]  if target is item (type 2) that’s itemId, 0 otherwise 
BYTE  layer (of the character, e.g left hand, right hand, … 0-4, 0xff: moving effect or target is no char) 
BYTE [2] yet another (unknown) additional effect that’s only set for moving effect, 0 otherwise        
 

Note: 2d clients understand it as well, but default to “old effects”.

 



*/