//Chat functions library by ArT-iX

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////




function OpenChatWindow(who, nickname)
var packet := CreatePacket(0xB2, MSGLEN_VARIABLE);

packet.setInt16(1, 0);
packet.setInt16(3, 0x3ED);
packet.setInt32(5, 0);
packet.setUnicodeString(9, Cascz(nickname), 0);
packet.setInt32(packet.getSize(), 0);
packet.setInt16(1, packet.getSize());

packet.sendPacket(who);

endfunction

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

function addChannel(who, channelName)

var packet := CreatePacket(0xB2, MSGLEN_VARIABLE);

packet.setInt16(1, 0);
packet.setInt16(3, 0x3E8);
packet.setInt32(5, 0);
packet.setUnicodeString(9, Cascz(channelName), 0);
packet.setInt16(packet.getSize(), 0);
packet.setInt16(packet.getSize(), 0x30);
packet.setInt16(packet.getSize(), 0);
packet.setInt16(1, packet.getSize());

packet.sendPacket(who);

endfunction

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

function joinChannel(who, channelName)

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

var ChannelElem := channelsfile.findElement(channelName);
var UserElem := usersfile.findElement(who.serial);

if(!ChannelElem)
SendSysMessage(who, "Sorry, no channel with that name!");
return;
endif

var packet := CreatePacket(0xB2, MSGLEN_VARIABLE);

packet.setInt16(1, 0);
packet.setInt16(3, 0x3F1);
packet.setInt32(5, 0);
packet.setUnicodeString(9, Cascz(channelName), 0);
packet.setInt32(packet.getSize(), 0);

packet.setInt16(1, packet.getSize());

packet.sendPacket(who);

SetObjProperty(who, "ChatChannel", channelName);
UserElem.setProp("Channel", channelName);

var usersinchan := ChannelElem.getProp("Users");

foreach usrs in usersinchan
if(usrs != who.serial)
 AddUserToChannelPrivate(who, FindNickNameBySerial(usrs), channelName);
endif
endforeach

UnloadDataFile("ChatUsers");
UnloadDataFile("ChatChannels"); 
endfunction

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

function AddUserToChannel(who, userName, channelName)

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

if(!channelsfile)
SendSysMessage(who, "Sorry, no datafile!");
endif

var usr;
var ChannelElem := channelsfile.findElement(channelName);

if(!ChannelElem)
SendSysMessage(who, "Sorry, no channel with that name!");
return;
endif

var UsersInChannel := ChannelElem.getProp("Users");

var packet := CreatePacket(0xB2, MSGLEN_VARIABLE);

packet.setInt16(1, 0);
packet.setInt16(3, 0x3EE);
packet.setInt32(5, 0);
packet.setUnicodeString(9, Cascz("1" + userName), 0);
packet.setInt32(packet.getSize(), 0);

packet.setInt16(1, packet.getSize());

packet.sendPacket(who);

var isAlreadyLogged := 0;

foreach serial in UsersInChannel
 
 
 usr := SystemFindObjectBySerial( serial );
 if(serial != who.serial)
  packet.sendPacket(usr);
 else
  isAlreadyLogged := 1;	
 endif 
endforeach


 
if(isAlreadyLogged == 0)
UsersInChannel.append(who.serial);
endif

ChannelElem.setProp("Users", UsersInChannel);
UnloadDataFile("ChatUsers");
UnloadDataFile("ChatChannels");

endfunction

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

function AddUserToChannelPrivate(who, userName, channelName)

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

if(!channelsfile)
SendSysMessage(who, "Sorry, no datafile!");
endif

var usr;
var ChannelElem := channelsfile.findElement(channelName);

if(!ChannelElem)
SendSysMessage(who, "Sorry, no channel with that name!");
return;
endif

var UsersInChannel := ChannelElem.getProp("Users");

var packet := CreatePacket(0xB2, MSGLEN_VARIABLE);

packet.setInt16(1, 0);
packet.setInt16(3, 0x3EE);
packet.setInt32(5, 0);
packet.setUnicodeString(9, Cascz("1" + userName), 0);
packet.setInt32(packet.getSize(), 0);

packet.setInt16(1, packet.getSize());

packet.sendPacket(who);

/*foreach serial in UsersInChannel

usr := SystemFindObjectBySerial( serial );

packet.sendPacket(usr);

endforeach

UsersInChannel.append(who.serial);

ChannelElem.setProp("Users", UsersInChannel);
UnloadDataFile("ChatUsers");
UnloadDataFile("ChatChannels");*/

endfunction

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

function SendMessageToChannel(who, userName, channelName, message, lang := "ITA")

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

var usr;
var ChannelElem := channelsfile.findElement(channelName);

if(!ChannelElem)
SendSysMessage(who, "Sorry, no channel with that name!");
return;
endif

var UsersInChannel := ChannelElem.getProp("Users");

var packet := CreatePacket(0xB2, MSGLEN_VARIABLE);

packet.setInt16(1, 0);
packet.setInt16(3, 0x025);
packet.setString(5, cascz(lang));
packet.setInt16(8, 0 );
packet.setInt8(10, 0x31);

packet.setUnicodeString(11, Cascz(userName), 0);
packet.setInt16(packet.getSize(), 0);
packet.setUnicodeString(packet.getSize(), Cascz(message), 0);

packet.setInt16(packet.getSize(), 0);

packet.setInt16(1, packet.getSize());


packet.sendPacket(who);

foreach serial in UsersInChannel

if((!isIgnored(FindSerialByNickName(userName), serial)) && (serial != who.serial))
usr := SystemFindObjectBySerial( serial );

packet.sendPacket(usr);
endif
endforeach

endfunction

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

function SendPrivateMessage(who, userName, toWhom, message, lang := "ITA")

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

//var UsersInChannel := ChannelElem.getProp("Users");
var UserElem := usersfile.findelement(toWhom.serial);
var canReceive := UserElem.getProp("receivePriv");
//var ignoredUsers := UserElem.getProp("ignored");
var ignored := isIgnored(who, toWhom);

/*foreach usrs in ignoredUsers

if(usrs == userName)
isIgnored := 1;
break;
endforeach*/



var packet := CreatePacket(0xB2, MSGLEN_VARIABLE);

packet.setInt16(1, 0);
packet.setInt16(3, 0x027);
packet.setString(5, cascz(lang));
packet.setInt16(8, 0 );
packet.setInt8(10, 0x31);

packet.setUnicodeString(11, Cascz(userName), 0);
packet.setInt16(packet.getSize(), 0);
packet.setUnicodeString(packet.getSize(), Cascz(message), 0);

packet.setInt16(packet.getSize(), 0);

packet.setInt16(1, packet.getSize());

if((canReceive == 1) && (!ignored))
packet.sendPacket(toWhom);
endif

endfunction

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


function IgnoreUser(who, userName, lang := "ITA")

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

//var UsersInChannel := ChannelElem.getProp("Users");
var UserElem := usersfile.findelement(who.serial);
var ignoredUsers := UserElem.getProp("ignored");

var packet := CreatePacket(0xB2, MSGLEN_VARIABLE);

packet.setInt16(1, 0);
packet.setInt16(3, 0x03);
packet.setString(5, cascz(lang));
packet.setInt8(8, 0 );


packet.setUnicodeString(9, Cascz(userName), 0);


packet.setInt32(packet.getSize(), 0);

packet.setInt16(1, packet.getSize());


packet.sendPacket(who);

ignoredUsers.append(userName);

UserElem.setProp("ignored", ignoredUsers);

UnloadDataFile("ChatUsers");
UnloadDataFile("ChatChannels");

endfunction

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

function SendNickNameWindow(who)

var packet := CreatePacket(0xB2, 13);

packet.setInt16(1, 13);
packet.setInt16(3, 0x03EB);
packet.setInt32(5, 0);
packet.setInt32(9, 0);

packet.sendPacket(who);

endfunction

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

function whoIs(who, nickname, lang := "ITA")

var ser := FindSerialByNickName(nickname);
var char := SystemFindObjectBySerial( ser);

var packet := CreatePacket(0xB2, MSGLEN_VARIABLE);

packet.setInt16(1, 0);
packet.setInt16(3, 0x17);
packet.setString(5, cascz(lang));
packet.setInt8(8, 0 );


packet.setUnicodeString(9, Cascz(nickName), 0);
packet.setInt16(packet.getSize(), 0);
packet.setUnicodeString(packet.getSize(), Cascz(char.name), 0);
packet.setInt16(packet.getSize(), 0);

packet.setInt16(1, packet.getSize());


packet.sendPacket(who);
print(char.name);
return char.name;

endfunction

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

function isIgnored(who, byWhom)

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

var byWhomElem := usersfile.findelement(byWhom.serial);
var Whoelem := usersfile.findelement(who.serial);

var UsrName := Whoelem.getProp("NickName");

var ignoredUsers := byWhomElem.getProp("ignored");
var ignored := 0;

foreach usrs in ignoredUsers

if(usrs == UsrName)
ignored := 1;
break;
endif
endforeach

return ignored;

endfunction

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

function FindSerialByNickName(nickname)

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

var elem;
var serials := usersfile.keys();
print (serials);
foreach ser in serials
elem := usersfile.findElement(ser);
//print(elem.getProp("NickName" == nickname));
if(elem.getProp("NickName") == nickname)
return ser;
endif
endforeach
 
return 0; 

endfunction

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

function hasRegisteredNickName(who)

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

var elem := usersfile.findElement(who.serial);

if(elem)
return 1;
else
return 0;
endif

endfunction

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

function FindNickNameBySerial(who)

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

var elem := usersfile.findElement(who.serial);

if(elem)
return elem.getProp("NickName");
else
return 0;
endif

endfunction

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

function GetChannel(who)

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

var elem := usersfile.findElement(who.serial);

if(elem)
return elem.getProp("Channel");
else
return 0;
endif

endfunction

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

function RegisterNickname (serial, nickname)

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels"); 

var elem := usersfile.createElement(serial);
elem.setProp("NickName", nickname);
elem.setProp("Channel", "");
elem.setProp("ignored", {});
elem.setProp("receivePriv", 1);

UnloadDataFile("ChatUsers");
UnloadDataFile("ChatChannels");


endfunction

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

function getAllChannels()
var channelsfile := OpenDataFile("ChatChannels"); 
return channelsfile.keys();
endfunction

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

function leaveChat(who)

var usersfile := OpenDataFile("ChatUsers");
var channelsfile := OpenDataFile("ChatChannels");

var userelem := usersfile.findElement(who.serial);

var actualChannel := userelem.getProp("Channel");
var chan := channelsfile.findElement(actualChannel);
var usersInChannel := chan.getProp("Users");
var i;
for( i := 1; i <= usersInChannel.size(); i := i + 1)
if(usersInChannel[i] == who.serial)
usersInChannel.erase(i);
endif
endfor
userelem.setProp("Channel", "");
userelem.setProp("Online", 0);

UnloadDataFile("ChatUsers");
UnloadDataFile("ChatChannels");

endfunction