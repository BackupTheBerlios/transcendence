function CreateCorpsePrivate(who, model, dir, color, x, y, z)
  
  var proto := CreateItemAtLocation(5276, 1164, 0, 0x2006);
  var serial := proto.serial;
  var pck := CreatePacket(0x1A, 0x14);
  pck.setInt16(1, 0);
  pck.setInt32(3, serial + 0x80000000);
  pck.setInt16(7, 0x2006);
  pck.setInt16(9, model);
  pck.setInt16(11, x + 0x8000);
  pck.setInt16(13, y + 0xC000);
  pck.setInt8(15, dir);
  pck.setInt8(16, z);
  pck.setInt16(17, color);
  pck.setInt8(19, 0);
  pck.setInt16(1, pck.getSize());
  //destroyitem(proto);
  pck.sendPacket(who);
  return proto;
  
endfunction

function CreateCorpseModel( who, model, dir, color, x, y, z, realm := "britannia")
  
  var proto := CreateItemAtLocation(5276, 1164, 0, 0x2006);
  var serial := proto.serial;
  var pck := CreatePacket(0x1A, 0x14);
  pck.setInt16(1, 0);
  pck.setInt32(3, serial + 0x80000000);
  pck.setInt16(7, 0x2006);
  pck.setInt16(9, model);
  pck.setInt16(11, x + 0x8000);
  pck.setInt16(13, y + 0xC000);
  pck.setInt8(15, dir);
  pck.setInt8(16, z);
  pck.setInt16(17, color);
  pck.setInt8(19, 0);
  pck.setInt16(1, pck.getSize());
  //destroyitem(proto);
  //pck.sendPacket(who);
  pck.sendAreaPacket(x, y,  10, realm);
  return proto;
  
endfunction

function CreateCorpse( model, dir, color, x, y, z, realm := "britannia")
  
  var proto := CreateItemAtLocation(x, y, z, 0x2006, realm);
  var serial := proto.serial;
  var pck := CreatePacket(0x1A, 0x14);
  pck.setInt16(1, 0);
  pck.setInt32(3, serial + 0x80000000);
  pck.setInt16(7, 0x2006);
  pck.setInt16(9, model);
  pck.setInt16(11, x + 0x8000);
  pck.setInt16(13, y + 0xC000);
  pck.setInt8(15, dir);
  pck.setInt8(16, z);
  pck.setInt16(17, color);
  pck.setInt8(19, 0);
  pck.setInt16(1, pck.getSize());
  destroyitem(proto);
  pck.sendAreaPacket(x, y, 10, realm);
  
  return proto;
  
endfunction

function EquipCorpse(who, equipment, corpse, x, y, z, realm := "britannia")
 print("EQP :" + cstr(equipment));
 var i;
 var pck := CreatePacket(0x89, MSGLEN_VARIABLE);
 pck.setInt16(1, 0);
 pck.setInt32(3, corpse.serial);
 for (i := 1; i <= equipment.size(); i := i + 1)
  print(cstr(equipment[i].layer));
  print(cstr(equipment[i].serial));
  pck.setInt8(7, equipment[i].layer);
  pck.setInt32(8, equipment[i].serial);
 endfor
 
 pck.setInt8(pck.getSize(), 0);
 pck.setInt16(1, pck.getSize());
 pck.sendPacket(who);
 pck.sendAreaPacket(x, y,  10);
 
endfunction

function CreateCorpseClone(ofwhom, x, y, z, realm)
endfunction

