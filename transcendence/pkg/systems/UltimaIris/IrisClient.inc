// by ArT-iX 31/03/2004
// Warning: these functions only works with the modified iris client, customized for Transcendence
// They use a special protocol appositely created for Transcendence shard

//Custom Transcendence Iris packets are f0-ff
use polsys;


const SKYTYPE_NIGHT := 0;
const SKYTYPE_DAWN := 1;
const SKYTYPE_DAY := 2;
const SKYTYPE_SUNSET := 3;
const SKYTYPE_EVENING := 4;
const SKYTYPE_CLOUDY := 5;
const SKYTYPE_SPACE := 6;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


function Scale3DCharacter(char, scalex, scaley, scalez)
  
  var pck := CreatePacket(0xF1, 9);
  pck.setInt32(1, char.serial);
  pck.setInt8(5, scalex);
  pck.setInt8(6, scaley);
  pck.setInt8(7, scalez);
  pck.setInt8(8, 0);
  pck.sendAreaPacket(char.x, char.y, 15, char.realm);

endfunction

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


function Scale3DCharacterPrivate(who, char, scalex, scaley, scalez)
  
  var pck := CreatePacket(0xF1, 9);
  pck.setInt32(1, char.serial);
  pck.setInt8(5, scalex);
  pck.setInt8(6, scaley);
  pck.setInt8(7, scalez);
  pck.setInt8(8, 0);
  pck.sendPacket(who);

endfunction

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


function SetModelDefaultDimensions( model )
  
  var pck := CreatePacket(0xF1, 9);
  pck.setInt32(1, model.serial);
  pck.setInt8(5, 10);
  pck.setInt8(6, 10);
  pck.setInt8(7, 10);
  pck.setInt8(8, 0);
  pck.sendAreaPacket(model.x, model.y, 15, model.realm);

endfunction

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


function SetModelDefaultDimensionsPriv( who, model )
  
  var pck := CreatePacket(0xF1, 9);
  pck.setInt32(1, model.serial);
  pck.setInt8(5, 10);
  pck.setInt8(6, 10);
  pck.setInt8(7, 10);
  pck.setInt8(8, 0);
  pck.sendPacket(who);

endfunction

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


function SetTransparency( model, alpha )
  
  var pck := CreatePacket(0xF3, 6);

  pck.setInt32(1, model.serial);
  pck.setInt8(5, alpha);

  pck.sendAreaPacket(model.x, model.y, 17, model.realm);

endfunction

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

function SetTransparencyPrivate( who, model, alpha )
  
  var pck := CreatePacket(0xF3, 6);

  pck.setInt32(1, model.serial);
  pck.setInt8(5, alpha);

  pck.sendPacket(who);

endfunction

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

function SetSkyType(who, type)
 var pck := CreatePacket(0xF0, 6);
 pck.setInt16(1, 0);
 pck.setInt16(3, 1);
 pck.setInt8(5, type);
 pck.setInt16(1, pck.getSize());
 pck.sendPacket(who);
endfunction

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

function SendImmersiveFog(who, density, color1 := 5, color2 := 5, color3 := 5)
 var pck := CreatePacket(0xF0, 12);
 pck.setInt16(1, 0);
 pck.setInt16(3, 2);
 pck.setInt8(5, 1);
 pck.setInt8(6, 0);
 pck.setInt8(7, density);
 pck.setInt8(8, 1);
 pck.setInt8(9, color1);
 pck.setInt8(10, color2);
 pck.setInt8(11, color3);
 pck.setInt16(1, pck.getSize());
 pck.sendPacket(who);
endfunction

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

function SendLinearFog(who, fogstart, fogend, color1 := 5, color2 := 5, color3 := 5)
 var pck := CreatePacket(0xF0, 13);
 pck.setInt16(1, 0);
 pck.setInt16(3, 2);
 pck.setInt8(5, 1);
 pck.setInt8(6, 1);
 pck.setInt8(7, fogstart);
 pck.setInt8(8, fogend);
 pck.setInt8(9, 1);
 pck.setInt8(10, color1);
 pck.setInt8(11, color2);
 pck.setInt8(12, color3);
 pck.setInt16(1, pck.getSize());
 pck.sendPacket(who);
endfunction

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

function ClearFog(who)
 var pck := CreatePacket(0xF0, 6);
 pck.setInt16(1, 0);
 pck.setInt16(3, 2);
 pck.setInt8(5, 0);
 
 pck.setInt16(1, pck.getSize());
 pck.sendPacket(who);
endfunction
