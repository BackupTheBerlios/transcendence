// by ArT-iX

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

function SendAOSToolTipString(towhom, onwhat, str)

var packet := CreatePacket(0xD6, MSGLEN_VARIABLE);
packet.setInt16(1, 0); // packet length
packet.setInt16(3, 1); // always 1
packet.setInt32(5, onwhat.serial); // object serial
packet.setInt16(9, 0); //always 0
packet.setInt32(11, 0x00684283);
packet.setInt32(15, 0x000FEA1B);
packet.setInt8(19, 0);
//packet.setInt8(20, 0); // string length
packet.setUnicodeString(20, cascz(str), 0);



packet.setInt8(packet.getSize(), 0);
packet.setInt32(packet.getSize(), 0);

packet.setInt16(1, packet.getSize()); //setting packet length
packet.setInt8(20, (packet.getsize() - 24)); // setting string length
packet.sendPacket(towhom);
//print ("AOSTOOLTIP: " + packet);

endfunction

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

function SendAOSToolTipByName(towhom, onwhat)

var packet := CreatePacket(0xD6, MSGLEN_VARIABLE);
packet.setInt16(1, 0); // packet length
packet.setInt16(3, 1); // always 1
packet.setInt32(5, onwhat.serial); // object serial
packet.setInt16(9, 0); //always 0
packet.setInt8(11, 0);
packet.setInt8(12, 104);
packet.setInt8(13, 66);
packet.setInt8(14, 131);
packet.setInt8(15, 0);
packet.setInt8(16, 16);
packet.setInt8(17, 5);
packet.setInt8(18, 189);
packet.setInt8(19, 0);
packet.setInt8(20, 0); // string length
packet.setInt8(21, 32);
packet.setInt8(22, 0);
packet.setInt8(23, 9);
//packet.setInt8(24, 0);
packet.setUnicodeString(24, cascz(onwhat.name), 0);
//if (len(onwhat.name) < 5)
packet.setInt8(packet.getSize(), 0);
packet.setInt8(packet.getSize(), 9);
packet.setInt8(packet.getSize(), 0);
packet.setInt8(packet.getSize(), 32);
//endif
packet.setInt8(packet.getSize(), 0);
packet.setInt32(packet.getSize(), 0);

packet.setInt16(1, packet.getSize()); //setting packet length
packet.setInt8(20, (packet.getsize() - 24)); // setting string length
packet.sendPacket(towhom);
//print ("AOSTOOLTIP: " + packet);

endfunction

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

function SendPropAOSTooltip(towhom, onwhat, objname, properties)

var firstpropID := 0x00102F32;
var str_start;

var packet := CreatePacket(0xD6, MSGLEN_VARIABLE);
packet.setInt16(1, 0);
packet.setInt16(3, 1);
packet.setInt32(5, onwhat.serial);

packet.setInt16(9, 0);

packet.setInt8(11, 0);

packet.setInt8(12, 104);

packet.setInt8(13, 131);

packet.setInt8(14, 18);


packet.setInt8(15, 0);

packet.setInt8(16, 0x0F);

packet.setInt8(17, 0xEA); 
packet.setInt8(18, 0x1B); 
packet.setInt8(19, 0); 
packet.setUnicodeString(20, cascz(objname), 0); 
packet.setInt8(20, (packet.getSize() - 20)); 
packet.setInt8(packet.getSize(), 0); 

foreach prop in properties
packet.setInt32(packet.getSize(), firstpropID); 
packet.setInt8(packet.getSize(), 0); 
str_start := packet.getSize();
packet.setUnicodeString(packet.getSize(), cascz(prop[1]), 0); 
packet.setInt16(packet.getSize(), 9); 
packet.setUnicodeString(packet.getSize(), cascz(prop[2]), 0); 
packet.setInt8(str_start, (packet.getSize() - str_start) );
packet.setInt8(packet.getSize(), 0);
firstpropID := firstPropID + 1;
endforeach

packet.setInt8(packet.getSize(), 0); 
packet.setInt32(packet.getSize(), 0); 

packet.setInt16(1, packet.getSize()); 
packet.setInt8(0, 0xD6);
//print (packet);

//print (cstr(start1));


//print ("AOSTOOLTIP4: " + packet);
packet.sendPacket(towhom);

//print(whom.desc);
endfunction

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

function SendItemAOSTooltip (towhom, what, str)

var pck := CreatePacket(0xD6, MSGLEN_VARIABLE);
pck.setInt16(1, 0);
pck.setInt16(3, 1);
pck.setInt32(5, what.serial);
pck.setInt16(9, 0);
/*packet.setInt8(11, 0);

packet.setInt8(12, 104);

packet.setInt8(13, 131);

packet.setInt8(14, 18);*/
pck.setInt32(11, 0x00688312);
/*pck.setInt8(15, 0);
pck.setInt8(16, 0x0F);
pck.setInt8(17, 0xEA);
pck.setInt8(18, 0x1B);*/
pck.setInt32(15, 0x000FEA1B);
pck.setInt8(19, 0);
//pck.setInt8(20, 0);
/*pck.setInt8(21, 32);
pck.setInt8(22, 0);
pck.setInt8(23, 9);*/
//pck.setInt8(24, 0);
pck.setUnicodeString(20, cascz(str), 0);
/*if (text[6] == "OK")
pck.setInt8(pck.getSize(), 0);
pck.setInt8(pck.getSize(), 9);
pck.setInt8(pck.getSize(), 0);
pck.setInt8(pck.getSize(), 32);
endif*/
pck.setInt8(pck.getSize(), 0);
pck.setInt32(pck.getSize(), 0);

pck.setInt16(1, pck.getSize());
pck.setInt8(20, (pck.getsize() - 24));
pck.sendPacket(towhom);
//print ("AOSTOOLTIP: " + packet);
//print(whom.desc);

endfunction

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

function SendItemAOSTooltipByItemType(towhom, itm)

if(itm.isA(POLCLASS_CONTAINER) )
            if(itm.isA(POLCLASS_SPELLBOOK))
             SendPropAOSTooltip(who, itm, itm.desc, {{"Spells", cstr(itm.countInsertedSpells() )});
            else
             SendPropAOSTooltip(who, itm, itm.desc, {{"Oggetti", cstr(len(EnumerateItemsInContainer(itm)) )},{"Peso", cstr(itm.weight) }});
            endif
else
             SendItemAOSTooltip (who, itm, itm.desc);
endif

endfunction

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

function CheckTooltipCache(client, objserial, listID)

var pck := CreatePacket(0xBF, 0x0D);

pck.setInt16(1, 0x0D);
pck.setInt16(3, 0x10);
pck.setInt32(5, objserial); 
pck.setInt32(9, 0x40000000 + listID);

pck.sendPacket(client);

endfunction

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

function SendAOSToolTipCliloc(towhom, onwhat, ClilocID, props)

var packet := CreatePacket(0xD6, MSGLEN_VARIABLE);
packet.setInt16(1, 0); // packet length
packet.setInt16(3, 1); // always 1
packet.setInt32(5, onwhat.serial); // object serial
packet.setInt16(9, 0); //always 0
packet.setInt32(11, 0x10466131);

packet.setInt8(15, 0);
packet.setInt8(16, 16);
packet.setInt8(17, 5);
packet.setInt8(18, 189);
packet.setInt8(19, 0);
packet.setInt8(20, 0); // string length
packet.setInt8(21, 32);
packet.setInt8(22, 0);
packet.setInt8(23, 9);
//packet.setInt8(24, 0);
packet.setUnicodeString(24, cascz(str), 0);
//if (len(str) < 5)
packet.setInt8(packet.getSize(), 0);
packet.setInt8(packet.getSize(), 9);
packet.setInt8(packet.getSize(), 0);
packet.setInt8(packet.getSize(), 32);
//endif
packet.setInt8(packet.getSize(), 0);
packet.setInt32(packet.getSize(), 0);

packet.setInt16(1, packet.getSize()); //setting packet length
packet.setInt8(20, (packet.getsize() - 24)); // setting string length
packet.sendPacket(towhom);
//print ("AOSTOOLTIP: " + packet);

endfunction