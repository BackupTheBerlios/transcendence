// by ArT-iX

use uo;
use os;
use polsys;


const UOMAP_TRAMMEL := 0;
const UOMAP_FELUCCA := 1;
const UOMAP_ILSHENAR := 2;
const UOMAP_MALAS := 3;

const UOWEATHER_RAIN := 0;
const UOWEATHER_FIERCESTORM := 1;
const UOWEATHER_SNOW := 2;
const UOWEATHER_STORMBREWING := 3;


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

function MovePlayerByPathFind(who, x, y, z)
  
  var i;
  for(i := 0; i <= 20; i:= i + 1)
    var pck := CreatePacket(0x38, 7);
    pck.setInt16(1, x);
    pck.setInt16(3, y);
    pck.setInt16(5, z);
    pck.sendPacket(who);
  endfor

endfunction

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


function MovePlayer(who, direction, steps := 1)
  
  var i;
  var pck := CreatePacket(0x97, 2);
  pck.setInt8(1, direction);
  for(i := 1; i <= steps; i:= i + 1)
    pck.sendPacket(who);
  endfor
  
endfunction


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

function SetWeatherForPlayer2(who, weathertype, intensity, temperature := 0)
 var pck := CreatePacket(0x65, 4);
 pck.setInt8(1, weathertype);
 pck.setInt8(2, intensity);
 pck.setInt8(3, temperature);
 pck.sendPacket(who);
endfunction

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

function SetWeatherForRange(x, y, weathertype, intensity, range, realm := "britannia", temperature := 0)
 var pck := CreatePacket(0x65, 4);
 pck.setInt8(1, weathertype);
 pck.setInt8(2, intensity);
 pck.setInt8(3, temperature);
 pck.sendAreaPacket(x, y, range, realm);
endfunction

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

function SetWeatherForWorld(weathertype, intensity, temperature := 0)
 var pck := CreatePacket(0x65, 4);
 pck.setInt8(1, weathertype);
 pck.setInt8(2, intensity);
 pck.setInt8(3, temperature);
 foreach chr in EnumerateOnlineCharacters()
  pck.sendPacket(chr);
 endforeach 
endfunction

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

function SwitchMap(who, mapID)
 
 var pck := CreatePacket(0xBF, 6);
 pck.setInt16(1, 6);
 pck.setInt16(3, 8);
 pck.setInt8(5, mapID);
 pck.sendPacket(who);
 
endfunction

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

function SwitchMapToCoordinates(who, mapID, x, y, z)
 
 var pck := CreatePacket(0xBF, 6);
 pck.setInt16(1, 6);
 pck.setInt16(3, 8);
 pck.setInt8(5, mapID);
 pck.sendPacket(who);
 
 MoveCharacterToLocation( who, x, y, z, MOVECHAR_FORCELOCATION);
 
endfunction

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

function SetPersonalLightLevel( who, light )
 
 var pck := CreatePacket(0x4F, 2);
 pck.setInt8(1, light);
 pck.sendPacket(who);

endfunction
    
/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////// 
    
function SetSeason( who, season )
    var pck := CreatePacket(0xBC, 2);
    pck.setInt8(1, season);
    pck.sendPacket(who);
endfunction

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////// 
    
function SetSeasonForRealm( season, realm )
    var pck := CreatePacket(0xBC, 2);
    pck.setInt8(1, season);
    foreach char in EnumerateOnlineCharacters() 
    if(char.realm == realm)
     pck.sendPacket(char);
    endif 
    endforeach
endfunction