////////////////////////////////////////////////
//packets.inc
//  v1.1
//
//  Miscellaneous packet functions,
//    S1tH
//    Thanks to Maximilian Scherr for the following functions:
//      SetPlayerWarMode( who, value )
//      EnableChatButton( who )
//      SendIdleWarning( who )
//
//    sithilius@hotmail.com
//    38288137
////////////////////////////////////////////////

use uo;

////////////////////////////////////////////////
//Function Listing
////////////////////////////////////////////////
//SetPlayerWarMode( who, value )                   Toggle a players war mode.
//EnableChatButton( who )                          Enable the "chat" button in a player paperdoll. WARNING! See function definition.
//SendIdleWarning( who )                           Sends an idle warning telling the player they will be kicked in 1 minute if they dont do anything.
//UpdatePlayer( who, forwho, graphic )             Shows another player onscreen as having different body, until their next movement.
//PlayCharAnim( who, anim )                        Look at the definition of this one... more options you can pass (speed, forwards/backwards, etc).
//PlayCharAnimPrivate( who, anim, forwho )         See definition for more details and explanation.
//PlayCharAnimWithRepitition( ... )		   See definition for explanation.
//PlayCharAnimWithRepititionPrivate( ... )         See definition for explanation
//PlayMidiMusic( who, musicID )                    Plays some MIDI.
//SetWeatherForAll( type, num )                    Sets weather conditions for all online clients.
//SetWeatherForPlayer( who, type, num )            Sets a players weather conditions.
//DrawGamePlayer( who, body, colour )              Draws the clients character with whatever body graphic you want, without showing other clients.
//NormaliseGamePlayer( who )                       Return what the client sees of themselves to normal.
//SetOverallLightForAll( lightlevel )		   Sets the 'overall' lightlevel for all online characters.
//SetOverallLightForPlayer( who, lightlevel )      Sets the 'overall' lightlevel for a specific character.
//SetCursorHue( who, hue )                         Changes cursor colour between gold (trammel) and normal (felucca?).
//SetSeasonForAll( season )                        Sets the weather season for all online characters.
//SetSeasonForPlayer( who, season )                Sets the weather season for a specific character.
//SetQuestArrow( who, active, xLoc, yLoc )         Sets if the player has a 'quest arrow', and where its pointing to.
////////////////////////////////////////////////

const CURSOR_NORM := 0; //Felucca / Old UO
const CURSOR_GOLD := 1; //Trammel i think...

const SEASON_SPRING := 0;     //Trammel.
const SEASON_SUMMER := 1;     //Old Brittania
const SEASON_FALL := 2;       //Fall
const SEASON_WINTER := 3;     //Screwed attempt by OSI for snow. Snow has no edges and looks fucked.
const SEASON_DESOLATION := 4; //Felucca - no leaves on trees, gravestones everywhere...

const WEATHER_STARTS_TO_RAIN := 0;
const WEATHER_FIERCE_STORM   := 1;
const WEATHER_BEGINS_SNOW    := 2;
const WEATHER_STORM_BREWING  := 3;
const WEATHER_DISABLE        := 0xff;

const ANIM_DIR_FORWARDS  := 0; //The animation will run the frames in normal order.
const ANIM_DIR_BACKWARDS := 1; //The animation will run the frames in reverse.
const ANIM_DEF_SPEED     := 0; //0 = fastest, 30 = way too fucken slow, 70 = wtf are you doing?

//////////////////////////////////////////////////////////////////////////////
//Sets a characters war mode. Value:
//  1     War
//  0     Peace
//////////////////////////////////////////////////////////////////////////////
function SetPlayerWarMode( who, value )
  if( !who.acctname )
    if( who.IsA(POLCLASS_NPC) )
      return who.SetWarMode(value);
    endif
  else
    var packetstring := "72" + fixPacketLength(value, 1);
    packetstring := packetstring + "003200";
    return SendPacket(who, packetstring);
  endif
endfunction

//////////////////////////////////////////////////////////////////////////////
//Allows the player to click the "chat" button on their paperdoll.
//WARNING! If the player clicks this, POL doesn't recognize it, and will
//complain about it (quite a bit) in the console. Could be useful if you
//have an aux package listening in to enable chat though.
//////////////////////////////////////////////////////////////////////////////
function EnableChatButton( who )
  return SendPacket(who, "B90001");
endfunction

//////////////////////////////////////////////////////////////////////////////
//Sends the client a little gump saying
//"You have been idle for too long. If you do not do anything
// within the next minute, you will be logged out."
//////////////////////////////////////////////////////////////////////////////
function SendIdleWarning( who )
  return SendPacket(who, "5307");
endfunction

//////////////////////////////////////////////////////////////////////////////
//Changes another characters graphic for a specific client
//  who        Character whos graphic to change
//  forwho     Character to change for
//  graphic    New graphic to show
//////////////////////////////////////////////////////////////////////////////
function UpdatePlayer( who, forwho, graphic )
    if( !graphic )
        graphic := who.graphic;
    endif
   
    var packetstring := "77";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(graphic),2);
    packetstring := packetstring + fixPacketLength(Hex(who.x),2);
    packetstring := packetstring + fixPacketLength(Hex(who.y),2);
    packetstring := packetstring + fixPacketLength(Hex(who.z),1);
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + fixPacketLength(Hex(0),2); //Colour (doesnt work)
    packetstring := packetstring + fixPacketLength(Hex(0),1); //Flag... dunno?
    packetstring := packetstring + fixPacketLength(Hex(0),1); //Highlight colour (doesnt work)
    return SendPacket( forwho, packetstring );
endfunction

function UpdatePos( who, forwho, x,y,z )
  
   
    var packetstring := "77";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(who.graphic),2);
    packetstring := packetstring + fixPacketLength(Hex(x),2);
    packetstring := packetstring + fixPacketLength(Hex(y),2);
    packetstring := packetstring + fixPacketLength(Hex(z),1);
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + fixPacketLength(Hex(0),2); //Colour (doesnt work)
    packetstring := packetstring + fixPacketLength(Hex(0),1); //Flag... dunno?
    packetstring := packetstring + fixPacketLength(Hex(0),1); //Highlight colour (doesnt work)
    return SendPacket( forwho, packetstring );
endfunction

//////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////
//Plays MIDI music (untested)
//  who      Person who hears the music
//  musicID  MIDI to play, same as "playmusic.inc"
//////////////////////////////////////////////////
function PlayMidiMusic( who, musicid )
    var packetstring := "6D" + fixPacketLength(Hex(musicid),2);
    return SendPacket(who,packetstring);
endfunction

///////////////////////////////////////////////////////
//Sets weather for all online clients:
//  type   Weather type. Constants at header.
//  num    Number of weather effects (dots?) onscreen. Max is 70.
//  temp   Temperature. Currently has no effect...
///////////////////////////////////////////////////////
function SetWeatherForAll( type, num, temp := 0 )
    if( num > 70 )
        num := 70;
    endif
   
    var packetstring := "65";
    packetstring := packetstring + fixPacketLength(Hex(type),1);
    packetstring := packetstring + fixPacketLength(Hex(num),1);
    packetstring := packetstring + fixPacketLength(Hex(temp),1);
   
    foreach chr in EnumerateOnlineCharacters()
        SendPacket( chr, packetstring );
    endforeach
endfunction

///////////////////////////////////////////////////////
//Sets weather for a specific client:
//  type   Weather type. Constants at header.
//  num    Number of weather effects (dots?) onscreen. Max is 70.
//  temp   Temperature. Currently has no effect...
///////////////////////////////////////////////////////
function SetWeatherForPlayer( who, type, num, temp := 0 )
    if( num > 70 )
        num := 70;
    endif
   
    var packetstring := "65";
    packetstring := packetstring + fixPacketLength(Hex(type),1);
    packetstring := packetstring + fixPacketLength(Hex(num),1);
    packetstring := packetstring + fixPacketLength(Hex(temp),1);
    return SendPacket(who,packetstring);
endfunction

////////////////////////////////////////////////////
//Changes how the clients character is drawn, like
//them polymorphing but no-one else sees it :)
//  who     Client whos character will change
//  body    Body graphic to change to
//  colour  Colour for the clients body
////////////////////////////////////////////////////
function DrawGamePlayer( who, body, colour )
    var packetstring := "20";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(body),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(colour),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(who.x),2);
    packetstring := packetstring + fixPacketLength(Hex(who.y),2);
    packetstring := packetstring + "0000";
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + fixPacketLength(Hex(who.z),1);
    return SendPacket( who, packetstring );
endfunction

function DrawGamePos( who, body, colour, x, y, z )
    var packetstring := "20";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(body),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(colour),2);
    packetstring := packetstring + "00";
    packetstring := packetstring + fixPacketLength(Hex(x),2);
    packetstring := packetstring + fixPacketLength(Hex(y),2);
    packetstring := packetstring + "0000";
    packetstring := packetstring + fixPacketLength(Hex(who.facing),1);
    packetstring := packetstring + fixPacketLength(Hex(z),1);
    return SendPacket( who, packetstring );
endfunction

///////////////////////////////////////////////////////
//Tells a client what their character really looks like
//  who    Person to send to
///////////////////////////////////////////////////////
function NormaliseGamePlayer( who )
    return DrawGamePlayer( who, who.graphic, who.color );
endfunction

///////////////////////////////////////////////////////
//Sets the 'overall' (world) light for everyone online
//  light    Light level. 0 = daylight, 30 = black.
///////////////////////////////////////////////////////
function SetOverallLightForAll( light )
    var packetstring := "4F" + fixPacketLength(Hex(light),1);
    foreach chr in EnumerateOnlineCharacters()
        SendPacket(chr,packetstring);
    endforeach
endfunction

///////////////////////////////////////////////////////////
//Sets the 'overall' (world) light for a specific character
//  who     Person whos light to change.
//  light   Light level. 0 = daylight, 30 = black.
///////////////////////////////////////////////////////////
function SetOverallLightForPlayer( who, light )
    var packetstring := "4F" + fixPacketLength(Hex(light),1);
    return SendPacket(who,packetstring);
endfunction

///////////////////////////////////////////////////////////
//Change a clients cursor colour, I think this is 2.0.0+
//  who      Clients cursor to change.
//  hue      Hue type, see constants at header.
///////////////////////////////////////////////////////////
function SetCursorHue( who, hue )
    var packetstring := "BF";
    packetstring := packetstring + fixPacketLength(6,2);
    packetstring := packetstring + fixPacketLength("8",2);
    packetstring := packetstring + fixPacketLength(hue,1);
    return SendPacket(who,packetstring);
endfunction

///////////////////////////////////////////////////////////
//Changes season for all online characters...
//  season    Season type. Constants at header.
///////////////////////////////////////////////////////////
function SetSeasonForAll( season )
    var packetstring := "BC" + fixPacketLength(season,1) + "01";
    foreach chr in EnumerateOnlineCharacters()
        SendPacket(chr,packetstring);
    endforeach
endfunction

///////////////////////////////////////////////////////////
//Changes season for a specific character
//  who      Character to change for
//  season   Season type. Constants at header.
///////////////////////////////////////////////////////////
function SetSeasonForPlayer( who, season )
    var packetstring := "BC" + fixPacketLength(season,1) + "01";
    return SendPacket(who,packetstring);
endfunction

///////////////////////////////////////////////////////////
//Quest arrow pointing to a location. Must be disabled too!
//  who       Person who sees the quest arrow
//  active    Arrow Status. 0 = off, non-zero = on.
//  xLoc      X Location to point to.
//  yLoc      Y Location to point to.
///////////////////////////////////////////////////////////
function SetQuestArrow( who, active, xloc, yloc )
    var packetstring := "BA" + fixPacketLength(active,1);
    packetstring := packetstring + fixPacketLength(Hex(xloc),2);
    packetstring := packetstring + fixPacketLength(Hex(yloc),2);
    print( packetstring );
    return SendPacket(who,packetstring);
endfunction

///////////////////////////////////////////////////////////////
//Pads a string with a "0" prefix, until it is of proper length
//  packetString   value to pad.
//  byteLength     number of bytes. Byte counted as two chars.
///////////////////////////////////////////////////////////////
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

function PlayObjectCenteredEffectHuefx( center, effect, speed,
loop := 0, color := 0, translucent := 0 )
       var packetstring := "C0";
       packetstring := packetstring + "03";   
       packetstring := packetstring + fixPacketLength(Hex(center.serial),4);
       packetstring := packetstring + fixPacketLength(Hex(0),4);
       packetstring := packetstring + fixPacketLength(Hex(effect),2);
       packetstring := packetstring + fixPacketLength(Hex(0),10);
       packetstring := packetstring + fixPacketLength(Hex(speed),1); //speed
       packetstring := packetstring + fixPacketLength(Hex(loop),1);     //loop
       packetstring := packetstring + "000000000000";
       packetstring := packetstring + fixPacketLength(Hex(color),2); //color
       packetstring := packetstring + "000000";
       packetstring := packetstring + fixPacketLength(Hex(translucent),1);    //tran
       foreach chr in ListMobilesNearLocation( center.x, center.y,
center.z, 16, center.realm );
          SendPacket( chr, packetstring );
       endforeach
endfunction
        
function PlayMovingEffectHuefx( source, dest, effect, speed, loop :=
0, explode := 0, color := 0, translucent := 0)
    var packetstring := "C0";
    packetstring := packetstring + "00";   
    packetstring := packetstring + fixPacketLength(Hex(source.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(dest.serial),4);
    packetstring := packetstring + fixPacketLength(Hex(effect),2);
    packetstring := packetstring + fixPacketLength(Hex(0),10);
    packetstring := packetstring + fixPacketLength(Hex(speed),1); //speed
    packetstring := packetstring + fixPacketLength(Hex(loop),1);     //loop
    packetstring := packetstring + "000000";
    packetstring := packetstring + fixPacketLength(Hex(explode),1); //explode
    packetstring := packetstring + "0000";
    packetstring := packetstring + fixPacketLength(Hex(color),2); //color
    packetstring := packetstring + "000000";
    packetstring := packetstring + fixPacketLength(Hex(translucent),1);    //tran
    foreach chr in ListMobilesNearLocation( source.x, source.y,
source.z, 16 , source.realm);
        SendPacket( chr, packetstring );
    endforeach
endfunction

function PlayMovingEffectXYZHuefx(source, sourcex, sourcey, sourcez,
destx, desty, destz, effect, speed, loop := 0, explode := 0, color :=
0, translucent := 0, realm := "britannia")
    var packetstring := "C0";
    packetstring := packetstring + "00";   
    packetstring := packetstring + fixPacketLength(Hex(0),8);
    packetstring := packetstring + fixPacketLength(Hex(effect),2);
    packetstring := packetstring + fixPacketLength(Hex(sourcex),2);
    packetstring := packetstring + fixPacketLength(Hex(sourcey),2);
    packetstring := packetstring + fixPacketLength(Hex(sourcez),1);
    packetstring := packetstring + fixPacketLength(Hex(destx),2);
    packetstring := packetstring + fixPacketLength(Hex(desty),2);
    packetstring := packetstring + fixPacketLength(Hex(destz),1);
    packetstring := packetstring + fixPacketLength(Hex(speed),1); //speed
    packetstring := packetstring + fixPacketLength(Hex(loop),1);     //loop
    packetstring := packetstring + "000000";
    packetstring := packetstring + fixPacketLength(Hex(explode),1); //explode
    packetstring := packetstring + "0000";
    packetstring := packetstring + fixPacketLength(Hex(color),2); //color
    packetstring := packetstring + "000000";
    packetstring := packetstring + fixPacketLength(Hex(translucent),1);    //tran
    foreach chr in ListMobilesNearLocation( source.x, source.y,
source.z, 16, realm );
        SendPacket( chr, packetstring );
    endforeach
endfunction

function PlayStationaryEffectHuefx( x, y, z, effect, speed, loop :=
0, explode := 0, color := 0,translucent := 0, realm := "britannia")
    var packetstring := "C0";
    packetstring := packetstring + "02";   
    packetstring := packetstring + fixPacketLength(Hex(0),8);
    packetstring := packetstring + fixPacketLength(Hex(effect),2);
    packetstring := packetstring + fixPacketLength(Hex(x),2);
    packetstring := packetstring + fixPacketLength(Hex(y),2);
    packetstring := packetstring + fixPacketLength(Hex(z),1);
    packetstring := packetstring + fixPacketLength(Hex(0),5);
    packetstring := packetstring + fixPacketLength(Hex(speed),1); //speed
    packetstring := packetstring + fixPacketLength(Hex(loop),1);     //loop
    packetstring := packetstring + "000000";
    packetstring := packetstring + fixPacketLength(Hex(explode),1); //explode
    packetstring := packetstring + "0000";
    packetstring := packetstring + fixPacketLength(Hex(color),2); //color
    packetstring := packetstring + "000000";
    packetstring := packetstring + fixPacketLength(Hex(translucent),1);    //tran
    foreach chr in ListMobilesNearLocation( x, y, z, 16, realm );
        SendPacket( chr, packetstring );
    endforeach
endfunction

function PlayStationaryEffectHuePriv( chr, x, y, z, effect, speed, loop :=
0, explode := 0, color := 0,translucent := 0)
    var packetstring := "C0";
    packetstring := packetstring + "02";   
    packetstring := packetstring + fixPacketLength(Hex(0),8);
    packetstring := packetstring + fixPacketLength(Hex(effect),2);
    packetstring := packetstring + fixPacketLength(Hex(x),2);
    packetstring := packetstring + fixPacketLength(Hex(y),2);
    packetstring := packetstring + fixPacketLength(Hex(z),1);
    packetstring := packetstring + fixPacketLength(Hex(0),5);
    packetstring := packetstring + fixPacketLength(Hex(speed),1); //speed
    packetstring := packetstring + fixPacketLength(Hex(loop),1);     //loop
    packetstring := packetstring + "000000";
    packetstring := packetstring + fixPacketLength(Hex(explode),1); //explode
    packetstring := packetstring + "0000";
    packetstring := packetstring + fixPacketLength(Hex(color),2); //color
    packetstring := packetstring + "000000";
    packetstring := packetstring + fixPacketLength(Hex(translucent),1);    //tran
   
        SendPacket( chr, packetstring );
   
endfunction

function charlocation(chr, who, x, y, z)

var packetstring := "1b";
    packetstring := packetstring + fixPacketLength(Hex(who.serial),4); 
         packetstring := packetstring + fixPacketLength(Hex(0),4); 
       packetstring := packetstring + fixPacketLength(Hex(who.graphic),2); 
         packetstring := packetstring + fixPacketLength(Hex(x),2); 
     packetstring := packetstring + fixPacketLength(Hex(y),2); 
     packetstring := packetstring + fixPacketLength(Hex(z),2); 
     packetstring := packetstring + fixPacketLength(Hex(who.facing),1);     
 packetstring := packetstring + fixPacketLength(Hex(0),2); 
SendPacket( chr, packetstring );
endfunction

function pause(chr)
var packetstring:="33";
packetstring := packetstring + fixPacketLength(Hex(0),1);
SendPacket(chr, packetstring);

endfunction
