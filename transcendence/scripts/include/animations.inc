const ANIM_DIR_FORWARDS  := 0; //The animation will run the frames in normal order.
const ANIM_DIR_BACKWARDS := 1; //The animation will run the frames in reverse.
const ANIM_DEF_SPEED     := 0; //0 = fastest, 30 = way too fucken slow, 70 = wtf are you doing?


///////////




///////////////////////////////////////////////////////////////////
//Animates a character
//  who    Character to animate
//  anim   Animation ID (constant from client.inc)
//  speed  Frame delay (lesser = faster)
//  dir    Play frames backwards or forwards? (use constants at header!!!)
//////////////////////////////////////////////////////////////////////////////
function PlayCharAnim( who, anim, speed := ANIM_DEF_SPEED, dir := ANIM_DIR_FORWARDS )
    var packetstring := "6E";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(anim),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + "0001"; //Repitition
    packetstring := packetstring + fixPacketLength(Hex(dir),1);
    packetstring := packetstring + "00"; //Does this animation repeat?
    packetstring := packetstring + fixPacketLength(Hex(speed),1);
    foreach chr in ListMobilesNearLocation( who.x, who.y, who.z, 16, who.realm );
        SendPacket( chr, packetstring );
    endforeach
endfunction

//////////////////////////////////////////////////////////////////////////////
//Animates a character privately
//  who    Character to animate
//  anim   Animation ID (constant from client.inc)
//  forwho Character that sees the animation
//  speed  Frame delay (lesser = faster)
//  dir    Play frames backwards or forwards? (use constants at header!!!)
//////////////////////////////////////////////////////////////////////////////
function PlayCharAnimPrivate( who, anim, forwho, speed := ANIM_DEF_SPEED, dir := ANIM_DIR_FORWARDS )
    var packetstring := "6E";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(anim),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + "0001"; //Repitition
    packetstring := packetstring + fixPacketLength(Hex(dir),1);
    packetstring := packetstring + "00"; //Does this animation repeat?
    packetstring := packetstring + fixPacketLength(Hex(speed),1);
    SendPacket( forwho, packetstring );
endfunction

/////////////////////////////////////////////////////////////////////////////////////////
//Repitition is totally wacked mega weird shit...
//It doesnt repeat the same animation that number of times but rather cycles through that number of following animations,
//then at the end i think it plays the original in reverse... why? NFI... test coz im not sure...
//Anyway its handy if you pass "reptimes" as "1", because it will play an animation, then the same in reverse.
// eg. A person falling over, then flying back up again :D
/////////////////////////////////////////////////////////////////////////////////////////
function PlayCharAnimWithRepitition( who, anim, reptimes, speed := ANIM_DEF_SPEED, dir := ANIM_DIR_FORWARDS )
    var packetstring := "6E";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(anim),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + fixPacketLength(Hex(reptimes),2);
    packetstring := packetstring + fixPacketLength(Hex(dir),1);
    packetstring := packetstring + "01"; //Does this animation repeat?
    packetstring := packetstring + fixPacketLength(Hex(speed),1);
    foreach chr in ListMobilesNearLocation( who.x, who.y, who.z, 16, who.realm );
        SendPacket( chr, packetstring );
    endforeach
endfunction

/////////////////////////////////////////////////////////////////////////////////////////
//Above, but only seen by 'forwho'
/////////////////////////////////////////////////////////////////////////////////////////
function PlayCharAnimWithRepititionPrivate( who, anim, reptimes, forwho, speed := ANIM_DEF_SPEED, dir := ANIM_DIR_FORWARDS )
    var packetstring := "6E";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(anim),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + fixPacketLength(Hex(reptimes),2);
    packetstring := packetstring + fixPacketLength(Hex(dir),1);
    packetstring := packetstring + "01"; //Does this animation repeat?
    packetstring := packetstring + fixPacketLength(Hex(speed),1);
    SendPacket( forwho, packetstring );
endfunction

///////////////////////////////////////////////////////////////////
//Animates a character
//  who    Character to animate
//  anim   Animation ID (constant from client.inc)
//  speed  Frame delay (lesser = faster)
//  dir    Play frames backwards or forwards? (use constants at header!!!)
//////////////////////////////////////////////////////////////////////////////
function PlayCharAnim2D( who, anim, speed := ANIM_DEF_SPEED, dir := ANIM_DIR_FORWARDS )
    var packetstring := "6E";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(anim),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + "0001"; //Repitition
    packetstring := packetstring + fixPacketLength(Hex(dir),1);
    packetstring := packetstring + "00"; //Does this animation repeat?
    packetstring := packetstring + fixPacketLength(Hex(speed),1);
    foreach chr in ListMobilesNearLocation( who.x, who.y, who.z, 16, who.realm );
        if(GetObjProperty( chr, "SessionClientType") == "2D" )
         SendPacket( chr, packetstring );
        endif
    endforeach
endfunction

function PlayCharAnim3D( who, anim, speed := ANIM_DEF_SPEED, dir := ANIM_DIR_FORWARDS )
    var packetstring := "6E";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(anim),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + "0001"; //Repitition
    packetstring := packetstring + fixPacketLength(Hex(dir),1);
    packetstring := packetstring + "00"; //Does this animation repeat?
    packetstring := packetstring + fixPacketLength(Hex(speed),1);
    foreach chr in ListMobilesNearLocation( who.x, who.y, who.z, 16, who.realm );
        if(GetObjProperty( chr, "SessionClientType") == "3D" )
         SendPacket( chr, packetstring );
        endif
    endforeach
endfunction