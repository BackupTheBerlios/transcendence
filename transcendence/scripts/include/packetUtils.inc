//packet utils functions by ArT-iX
const TYPE_INT := 0;
const TYPE_STRING := 1;
const TYPE_UCSTRING := 2;

function ClearPacket(byref packet, explicitSize := 0)

  var startOffset, i;
  
  if (explicitSize == 0)
   startOffset := 1;
  else
   startOffset := 3;	
  endif
  
  for(i := startOffset; i < packet.getSize(); i := i + 1)
   packet.setInt8(i, 0);
  endfor

endfunction

function AddPacketElement(byref packet, elementType, elementSize,  elementValue)



endfunction


function SetPacketExplictiSize(byref packet, EXPLICITSIZE_OFFSET := 1)
packet.setInt16(EXPLICITSIZE_OFFSET, packet.getSize());
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