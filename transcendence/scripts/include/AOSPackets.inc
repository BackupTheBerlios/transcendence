//new AOS packets by ArT-iX

function SendVisualHPloss(towhom, ofwhom, hploss)

  var packet := CreatePacket(0xBF, 11);
  packet.setInt16(1, 11);
  packet.setInt16(3, 0x22);
  packet.setInt8(5, 1);
  packet.setInt32(6, ofwhom.serial);
  packet.setInt8(10, hploss);
  packet.sendPacket(towhom);

endfunction
