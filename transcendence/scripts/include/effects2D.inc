/*function fixPacketLength( packetString, byteLength )
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
endfunction*/

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
source.z, 16, source.realm );
        SendPacket( chr, packetstring );
    endforeach
endfunction

function PlayMovingEffectXYZHuefx(source, sourcex, sourcey, sourcez,
destx, desty, destz, effect, speed, loop := 0, explode := 0, color :=
0, translucent := 0)
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
source.z, 16, source.realm );
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

function Play2DObjectCenteredEffectHuefx( center, effect, speed,
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
       foreach chr in ListMobilesNearLocation( center.x, center.y, center.z, 16, center.realm );
        if(GetObjProperty( chr, "SessionClientType") == "2D" )
          SendPacket( chr, packetstring );
        endif
       endforeach
endfunction
        
function Play2DMovingEffectHuefx( source, dest, effect, speed, loop :=
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
source.z, 16, source.realm );
        if(GetObjProperty( chr, "SessionClientType") == "2D" )
        
         SendPacket( chr, packetstring );
        endif
    endforeach
endfunction

function Play2DMovingEffectXYZHuefx(source, sourcex, sourcey, sourcez,
destx, desty, destz, effect, speed, loop := 0, explode := 0, color :=
0, translucent := 0)
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
source.z, 16, source.realm );
        if(GetObjProperty( chr, "SessionClientType") == "2D" )
        SendPacket( chr, packetstring );
        endif
    endforeach
endfunction

function Play2DStationaryEffectHuefx( x, y, z, effect, speed, realm := "britannia", loop :=
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
    foreach chr in ListMobilesNearLocation( x, y, z, 16, realm );
        if(GetObjProperty( chr, "SessionClientType") == "2D" )
        SendPacket( chr, packetstring );
        endif
    endforeach
endfunction
