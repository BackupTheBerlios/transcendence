function ChangeCharGraphic(who, graphic)

var pck := CreatePacket(0x78, MSGLEN_VARIABLE);
who.graphic := graphic;
pck.setInt16(1,0);
//pck.setInt16(1, 0);
    pck.setInt32(3, who.serial);
    pck.setInt16(7, graphic);
    pck.setInt16(9, who.x);
    pck.setInt16(11, who.y);
    pck.setInt8(13, who.z);
    pck.setInt8(14, who.facing);
    pck.setInt16(15, who.color);
    pck.setInt16(17, 0);
    foreach itm in ListEquippedItems(who) 
    //print (cstr(itm.graphic));
          //if (itm.character == who.serial)
            //print("OK");
            pck.setInt32(pck.getSize(), itm.serial);
            if (itm.color == 0)
              graphic := itm.graphic;

            else
              graphic := itm.graphic + 32768;
            endif
            
            pck.setInt16(pck.getSize(), graphic);
            pck.setInt8(pck.getSize(), itm.layer);
            
            if (itm.color != 0)
              pck.setInt16(pck.getSize(), itm.color);
            endif
          //endif
        endforeach
     pck.setInt32(pck.getSize(), 0);
     pck.setInt16(1, pck.getSize());
        foreach char in ListMobilesNearLocation( who.x, who.y, who.z, 10, who.realm )
         pck.sendPacket(char);
        endforeach
     //pck.sendAreaPacket(who.x, who.y, 10, who.realm);   
endfunction
