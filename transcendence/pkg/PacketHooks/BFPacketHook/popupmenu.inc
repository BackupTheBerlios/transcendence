// by ArT-iX
const POPUPENTRY_OPENPAPERDOLL := 0x17EB;
const POPUPENTRY_BUY := 0x17D7;
const POPUPENTRY_SELL := 0x17D8;
const POPUPENTRY_BANKBOX := 0x17D9;
const POPUPENTRY_BACKPACK := 0x1801;
const POPUPENTRY_FOLLOW := 0x17DC;
const POPUPENTRY_KILL := 0x17DF;
const POPUPENTRY_STOP := 0x17E0;
const POPUPENTRY_TRANSFER := 0x17E1;
const POPUPENTRY_STAY := 0x17E2;
const POPUPENTRY_RELEASE := 0x17E6;
const POPUPENTRY_LOOKAT := 0x17E9;
const POPUPENTRY_HIRE := 0x17E8;
const POPUPENTRY_STABLE := 0x17EE;
const POPUPENTRY_CLAIMALL := 0x17EF;
const POPUPENTRY_CLAIM := 0x17F0;
const POPUPENTRY_TAME := 0x17F2;
const POPUPENTRY_TALK := 0x1802;
const POPUPENTRY_OPEN := 0x17EA;
const POPUPENTRY_CLOSE := 0x17F3;
const POPUPENTRY_USE := 0x17F4;
const POPUPENTRY_LOOT := 0x17F5;
const POPUPENTRY_DEC_MAP := 0x1803;
const POPUPENTRY_DIG_TREAS := 0x1803;

const POPUPTAG_OPENPAPERDOLL := 0;
const POPUPTAG_BUY := 1;
const POPUPTAG_SELL := 2;
const POPUPTAG_BANKBOX := 3;
const POPUPTAG_BACKPACK := 4;
const POPUPTAG_FOLLOW := 5;
const POPUPTAG_KILL := 6;
const POPUPTAG_STOP := 7;
const POPUPTAG_TRANSFER := 8;
const POPUPTAG_STAY := 9;
const POPUPTAG_RELEASE := 10;
const POPUPTAG_LOOKAT := 11;
const POPUPTAG_HIRE := 12;
const POPUPTAG_STABLE := 13;
const POPUPTAG_CLAIMALL := 14;
const POPUPTAG_CLAIM := 15;
const POPUPTAG_TAME := 16;
const POPUPTAG_TALK := 17;
const POPUPTAG_OPEN := 18;
const POPUPTAG_CLOSE := 19;
const POPUPTAG_USE := 20;
const POPUPTAG_LOOT := 21;

const POPUPFLAG_NULL := 0;
const POPUPFLAG_COLORED := 0x20;
var PopUpPacket;

function SendPopUpMenuByScriptName(client, chr, scriptname)
PopUpPacket := CreatePacket(0xBF, MSGLEN_VARIABLE);
PopUpPacket.setInt16(1, 0);
PopUpPacket.setInt16(3, 0x14);
PopUpPacket.setInt16(5, 1);
PopUpPacket.setInt32(7, chr.serial);
if (scriptname == "merchant")
print("MERCHANT");
PopUpPacket.setInt8(11, 3);
PopUpPacket.setInt16(12, POPUPTAG_OPENPAPERDOLL);
PopUpPacket.setInt16(14, POPUPENTRY_OPENPAPERDOLL);
PopUpPacket.setInt16(16, POPUPFLAG_NULL);
PopUpPacket.setInt16(18, POPUPTAG_BUY);
PopUpPacket.setInt16(20, POPUPENTRY_BUY);
PopUpPacket.setInt16(22, POPUPFLAG_NULL);
PopUpPacket.setInt16(24, POPUPTAG_SELL);
PopUpPacket.setInt16(26, POPUPENTRY_SELL);
PopUpPacket.setInt16(28, POPUPFLAG_NULL);
PopUpPacket.setInt16(1, PopUpPacket.getsize());
elseif (scriptname == "animaltrainer")
//print("MERCHANT");
PopUpPacket.setInt8(11, 4);
PopUpPacket.setInt16(12, POPUPTAG_OPENPAPERDOLL);
PopUpPacket.setInt16(14, POPUPENTRY_OPENPAPERDOLL);
PopUpPacket.setInt16(16, POPUPFLAG_NULL);
PopUpPacket.setInt16(18, POPUPTAG_BUY);
PopUpPacket.setInt16(20, POPUPENTRY_BUY);
PopUpPacket.setInt16(22, POPUPFLAG_NULL);
PopUpPacket.setInt16(24, POPUPTAG_SELL);
PopUpPacket.setInt16(26, POPUPENTRY_SELL);
PopUpPacket.setInt16(28, POPUPFLAG_NULL);
PopUpPacket.setInt16(29, POPUPTAG_STABLE);
PopUpPacket.setInt16(30, POPUPENTRY_STABLE);
PopUpPacket.setInt16(31, POPUPFLAG_NULL);
PopUpPacket.setInt16(1, PopUpPacket.getsize());
elseif (scriptname == "banker")
print("BANKER");
PopUpPacket.setInt8(11, 3);
PopUpPacket.setInt16(12, POPUPTAG_OPENPAPERDOLL);
PopUpPacket.setInt16(14, POPUPENTRY_OPENPAPERDOLL);
PopUpPacket.setInt16(16, POPUPFLAG_NULL);
PopUpPacket.setInt16(18, POPUPTAG_BANKBOX);
PopUpPacket.setInt16(20, POPUPENTRY_BANKBOX);
PopUpPacket.setInt16(22, POPUPFLAG_NULL);
PopUpPacket.setInt16(24, POPUPTAG_BUY);
PopUpPacket.setInt16(26, POPUPENTRY_BUY);
PopUpPacket.setInt16(28, POPUPFLAG_NULL);
PopUpPacket.setInt16(1, PopUpPacket.getsize());
elseif (scriptname == "tamed")
print("TAMED");
PopUpPacket.setInt8(11, 6);
PopUpPacket.setInt16(12, POPUPTAG_RELEASE);
PopUpPacket.setInt16(14, POPUPENTRY_RELEASE);
PopUpPacket.setInt16(16, POPUPFLAG_NULL);
PopUpPacket.setInt16(18, POPUPTAG_TRANSFER);
PopUpPacket.setInt16(20, POPUPENTRY_TRANSFER);
PopUpPacket.setInt16(22, POPUPFLAG_NULL);
PopUpPacket.setInt16(24, POPUPTAG_STOP);
PopUpPacket.setInt16(26, POPUPENTRY_STOP);
PopUpPacket.setInt16(28, POPUPFLAG_NULL);
PopUpPacket.setInt16(30, POPUPTAG_STAY);
PopUpPacket.setInt16(32, POPUPENTRY_STAY);
PopUpPacket.setInt16(34, POPUPFLAG_NULL);
PopUpPacket.setInt16(36, POPUPTAG_FOLLOW);
PopUpPacket.setInt16(38, POPUPENTRY_FOLLOW);
PopUpPacket.setInt16(40, POPUPFLAG_NULL);
PopUpPacket.setInt16(42, POPUPTAG_KILL);
PopUpPacket.setInt16(44, POPUPENTRY_KILL);
PopUpPacket.setInt16(46, POPUPFLAG_NULL);
PopUpPacket.setInt16(1, PopUpPacket.getsize());
else
print("ALTRO");
if ((chr.graphic == 0x190) || (chr.graphic == 0x191)) 	
PopUpPacket.setInt8(11, 1);
PopUpPacket.setInt16(12, POPUPTAG_OPENPAPERDOLL);
PopUpPacket.setInt16(14, POPUPENTRY_OPENPAPERDOLL);
PopUpPacket.setInt16(16, POPUPFLAG_NULL);

PopUpPacket.setInt16(1, PopUpPacket.getsize());
else
PopUpPacket.setInt8(11, 1);
PopUpPacket.setInt16(12, POPUPTAG_TAME);
PopUpPacket.setInt16(14, POPUPENTRY_TAME);
PopUpPacket.setInt16(16, POPUPFLAG_NULL);

PopUpPacket.setInt16(1, PopUpPacket.getsize());
endif	
endif
print (PopUpPacket);
PopUpPacket.sendPacket(client);
return PopUpPacket;



endfunction

function SendPopUpMenuOnSelf(chr)
PopUpPacket := CreatePacket(0xBF, MSGLEN_VARIABLE);
PopUpPacket.setInt16(1, 0);
PopUpPacket.setInt16(3, 0x14);
PopUpPacket.setInt16(5, 1);
PopUpPacket.setInt32(7, chr.serial);

PopUpPacket.setInt8(11, 2);
PopUpPacket.setInt16(12, POPUPTAG_OPENPAPERDOLL);
PopUpPacket.setInt16(14, POPUPENTRY_OPENPAPERDOLL);
PopUpPacket.setInt16(16, POPUPFLAG_NULL);
PopUpPacket.setInt16(18, POPUPTAG_BACKPACK);
PopUpPacket.setInt16(20, POPUPENTRY_BACKPACK);
PopUpPacket.setInt16(22, POPUPFLAG_NULL);

PopUpPacket.setInt16(1, PopUpPacket.getSize());

print (PopUpPacket);
PopUpPacket.sendPacket(chr);
return PopUpPacket;
endfunction

function SendContainerPopup(client, ctnr)
PopUpPacket := CreatePacket(0xBF, MSGLEN_VARIABLE);
PopUpPacket.setInt16(1, 0);
PopUpPacket.setInt16(3, 0x14);
PopUpPacket.setInt16(5, 1);
PopUpPacket.setInt32(7, ctnr.serial);

PopUpPacket.setInt8(11, 2);
PopUpPacket.setInt16(12, POPUPTAG_OPEN);
PopUpPacket.setInt16(14, POPUPENTRY_OPEN);
PopUpPacket.setInt16(16, POPUPFLAG_NULL);
PopUpPacket.setInt16(18, POPUPTAG_CLOSE);
PopUpPacket.setInt16(20, POPUPENTRY_CLOSE);
PopUpPacket.setInt16(22, POPUPFLAG_NULL);

PopUpPacket.setInt16(1, PopUpPacket.getSize());

print (PopUpPacket);
PopUpPacket.sendPacket(client);
return PopUpPacket;
endfunction

function SendGeneralItemPopup(client, ctnr)
PopUpPacket := CreatePacket(0xBF, MSGLEN_VARIABLE);
PopUpPacket.setInt16(1, 0);
PopUpPacket.setInt16(3, 0x14);
PopUpPacket.setInt16(5, 1);
PopUpPacket.setInt32(7, ctnr.serial);

PopUpPacket.setInt8(11, 1);
PopUpPacket.setInt16(12, POPUPTAG_USE);
PopUpPacket.setInt16(14, POPUPENTRY_USE);
PopUpPacket.setInt16(16, POPUPFLAG_NULL);


PopUpPacket.setInt16(1, PopUpPacket.getSize());

print (PopUpPacket);
PopUpPacket.sendPacket(client);
return PopUpPacket;
endfunction

function SendCorpsePopup(client, ctnr)
PopUpPacket := CreatePacket(0xBF, MSGLEN_VARIABLE);
PopUpPacket.setInt16(1, 0);
PopUpPacket.setInt16(3, 0x14);
PopUpPacket.setInt16(5, 1);
PopUpPacket.setInt32(7, ctnr.serial);

PopUpPacket.setInt8(11, 1);
PopUpPacket.setInt16(12, POPUPTAG_LOOT);
PopUpPacket.setInt16(14, POPUPENTRY_LOOT);
PopUpPacket.setInt16(16, POPUPFLAG_NULL);


PopUpPacket.setInt16(1, PopUpPacket.getSize());

print (PopUpPacket);
PopUpPacket.sendPacket(client);
return PopUpPacket;
endfunction

