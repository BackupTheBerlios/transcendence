// Cliloc function v4.0 
// By BlahGoD and Kiwi 
// Modified by MuadDib to include arguments 

use uo; 
use basic; 

include "include/packets"; 

// Packet Arguments/Values are Little Endian punctuated 
function Cliloc(sendto, subject, color, messageID, system := 1, name := 1, values := 0) 

  if(name == 1) 
    name := subject.name; 
  endif 
  if(color == "03b2") 
    color := 996; 
  endif 
  var length := 18; 
  var namehex := ""; 
  var tester; 
  var message := fixClilocPacketLength(hex(messageID),3); 
  if(system) 
    tester := "ffffffffffff07"; 
  else 
    tester := fixClilocPacketLength(hex(subject.serial),4) + fixClilocPacketLength(hex(subject.graphic),2) + "07"; 
  endif 
  var msgCol := fixClilocPacketLength(Hex(color),2); 
  var valhex := ""; 
  if(values) 
    var count := len(name); 
    length := length + count + 30; 
    var loopcount := 1; 
    name := CAscZ(name); 
    while(loopcount < count + 1) 
      namehex := namehex + cstr(fixClilocPacketLength(hex(name[loopcount]), 1)); 
      loopcount := loopcount + 1; 
    endwhile 
    namehex := fixPacketLengthReverse( namehex, 29); 
    loopcount := 1; 
    count := len(values); 
    values := CAscZ(values); 
    while(loopcount < count + 1) 
      valhex := valhex + CStr(fixClilocPacketLength(hex(values[loopcount]), 2)); 
      loopcount := loopcount + 1; 
    endwhile 
    length := length + count; 
  else 
    var count := len(name); 
    length := length + count; 
    var loopcount := 1; 
    name := CAscZ(name); 
    while(loopcount < count + 1) 
      namehex := namehex + cstr(fixClilocPacketLength(hex(name[loopcount]), 1)); 
      loopcount := loopcount + 1; 
    endwhile 
  endif 
  length := hex(length)-"0x"; 
  var packet; 
  if(!values) 
    packet := "c1" + "00" + length + tester + msgCol + "000300" + message + namehex; 
  else 
    var tempit := len(("c10000" + tester + msgCol + "000300" + message + namehex + valhex)); tempit := tempit/2; 
    length := hex(tempit)-"0x"; 
    packet := "c1" + "00" + length + tester + msgCol + "000300" + message + namehex + valhex; 
  endif 
  SendPacket(sendto, packet); 

endfunction 

// Affix Packet Arguments/Values are Big Endian punctuated 
function ClilocAffix(sendto, subject, color, messageID, system := 1, name := 1, values := 0) 

  if(name == 1) 
    name := subject.name; 
  endif 
  if(color == "03b2") 
    color := 996; 
  endif 
  var length := 19; 
  var namehex := ""; 
  var tester; 
  var message := fixClilocPacketLength(hex(messageID),3); 
  if(system) 
    tester := "ffffffffffff00"; 
  else 
    tester := fixClilocPacketLength(hex(subject.serial),4) + fixClilocPacketLength(hex(subject.graphic),2) + "07"; 
  endif 
  var msgCol := fixClilocPacketLength(Hex(color),2); 
  var valhex := "20"; 
  if(values) 
    var count := len(name); 
    length := length + count + 30; 
    var loopcount := 1; 
    name := CAscZ(name); 
    while(loopcount < count + 1) 
      namehex := namehex + cstr(fixClilocPacketLength(hex(name[loopcount]), 1)); 
      loopcount := loopcount + 1; 
    endwhile 
    namehex := fixPacketLengthReverse( namehex, 30); 
    loopcount := 1; 
    count := len(values); 
    values := CAscZ(values); 
    while(loopcount < count + 1) 
      valhex := valhex + CStr(fixClilocPacketLength(hex(values[loopcount]), 1)); 
      loopcount := loopcount + 1; 
    endwhile 
    length := length + count; 
  else 
    var count := len(name); 
    length := length + count; 
    var loopcount := 1; 
    name := CAscZ(name); 
    while(loopcount < count + 1) 
      namehex := namehex + cstr(fixClilocPacketLength(hex(name[loopcount]), 1)); 
      loopcount := loopcount + 1; 
    endwhile 
  endif 
  length := hex(length)-"0x"; 
  var packet; 
  if(!values) 
    packet := "cc" + "00" + length + tester + msgCol + "000300" + message + "04" + namehex; 
  else 
    var tempit := len(("cc0000" + tester + msgCol + "000300" + message + "04" + namehex + valhex + "0000")); tempit := tempit/2; 
    length := hex(tempit)-"0x"; 
    packet := "cc" + "00" + length + tester + msgCol + "000300" + message + "04" + namehex + valhex + "0000"; 
  endif 
  print(packet); 
  SendPacket(sendto, packet); 

endfunction 

// Thanks to Max for this function :=) 

function fixClilocPacketLength( packetString, byteLength ) 
    if( !packetString || packetString == error ) 
        packetString := 0; 
    endif 
    packetString := cStr(packetString); 
    
    if( packetString[1,2] == "0x" ) 
        packetString := cStr(packetString[3,len(packetString)]); 
    endif 
    
    if( len(packetString) > byteLength * 2 ) 
        var extraBytes := (byteLength*2) - len(packetString); 
        return cStr(packetString[extraBytes,len(packetString)]); 
    endif 
    
    while( len(packetString) < byteLength * 2 ) 
        packetString := "0" + packetString; 
    endwhile 
    
    return packetString; 
endfunction 

/////////////////////////////////////////////////////////////// 
//Pads a string with a "0" suffix, until it is of proper length 
//  packetString   value to pad. 
//  byteLength     number of bytes. Byte counted as two chars. 
/////////////////////////////////////////////////////////////// 
function fixPacketLengthReverse( packetString, byteLength ) 
    if( !packetString || packetString == error ) 
        packetString := 0; 
    endif 
    packetString := cStr(packetString); 

    if( packetString[1,2] == "0x" ) 
        packetString := cStr(packetString[3,len(packetString)]); 
    endif 

    if( len(packetString) > byteLength * 2 ) 
//      var extraBytes := (byteLength*2) - len(packetString); 
      var extraBytes := len(packetString) - (byteLength*2) + 1; 
      return cStr(packetString[extraBytes,len(packetString)]); 
    endif 

    while( len(packetString) < byteLength * 2 ) 
        packetString := packetString + "0"; 
    endwhile 

    return packetString; 
endfunction 


// This function is used for those who have items from objtype 0 to 16383 the same 
// as the items in the tiledata. It will convert the objtype to the correct Cliloc 
// ID for it's name. Can be used in menu scripts such as crafting, etc. 
// Just remember to pass the objtype as CInt(objtype) to the function. 
// 1020000 - First tiledata name entry 
// 1036383 - Last tiledata name entry 
function ClilocObjtype(objtype) 

  if((objtype >= 0) && (objtype <= 16383) && objtype != error) 
    return CInt(objtype)+1020000; 
  else 
    return -1; 
  endif 

endfunction