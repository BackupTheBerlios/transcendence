// Audio Library by ArT-iX

function PlayOnObjSoundEffect(obj, effect, volume := 0, singleplay := 1, range := 10)
 
 var packet := CreatePacket(0x54, 0x0c);
 packet.setInt8(1, singleplay);
 packet.setInt16(2, effect - 1);
 packet.setInt16(4, volume);
 packet.setInt16(6, obj.x);
 packet.setInt16(8, obj.y);
 packet.setInt16(10, obj.z);
 
 packet.sendAreaPacket(obj.x, obj.y, range, obj.realm);
 
endfunction

function PlayOnObjSoundEffectPrivate(obj, towhom, effect, volume := 0, singleplay := 1)
 
 var packet := CreatePacket(0x54, 0x0c);
 packet.setInt8(1, singleplay);
 packet.setInt16(2, effect - 1 );
 packet.setInt16(4, volume);
 packet.setInt16(6, obj.x);
 packet.setInt16(8, obj.y);
 packet.setInt16(10, obj.z);
 
 packet.sendPacket(towhom);
 
endfunction

function PlayXYZSoundEffect(x, y, z, effect, realm := "britannia", volume := 0, singleplay := 1, range := 10)
 
 var packet := CreatePacket(0x54, 0x0c);
 packet.setInt8(1, singleplay);
 packet.setInt16(2, effect - 1);
 packet.setInt16(4, volume);
 packet.setInt16(6, x);
 packet.setInt16(8, y);
 packet.setInt16(10, z);
 
 packet.sendAreaPacket(x, y, range, realm);
 
endfunction

function PlayXYZSoundEffectPrivate(x, y, z, towhom, effect, volume := 0, singleplay := 1)
 
 var packet := CreatePacket(0x54, 0x0c);
 packet.setInt8(1, singleplay);
 packet.setInt16(2, effect - 1);
 packet.setInt16(4, volume);
 packet.setInt16(6, x);
 packet.setInt16(8, y);
 packet.setInt16(10, z);
 
 packet.sendPacket(towhom);
 
endfunction

function PlayDigitalMusic(who, musicID)

 var packet := CreatePacket(0x60, 3);
 packet.setInt16(1, musicID);
 packet.sendPacket(who);
 
endfunction

function PlayAreaDigitalMusic(x, y, musicID, realm := "britannia", range := 10)

 var packet := CreatePacket(0x60, 3);
 packet.setInt16(1, musicID);
 packet.sendAreaPacket(x, y, range, realm);
 
endfunction