// by ArT-iX

// requires uo.inc

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


function DrawNpcfromNPCTemplate(who, npctemplate, facing, x, y, z)

var graphic;
var equipmentarray := {};
var equippeditem := struct;
equippeditem.+character;
equippeditem.+serial;
equippeditem.+graphic;
equippeditem.+layer;
equippeditem.+color;


var npcmodel := CreateNpcFromTemplate( npctemplate, 5276, 1164, 0);
SetObjProperty(npcmodel, "XYZ", {x, y, z});
npcmodel.frozen := 1;
sleep(3);
  foreach itm in ListEquippedItems( npcmodel ) 
      // print("EQP: " + itm.desc);
      equippeditem.character := npcmodel.serial;
      equippeditem.serial := itm.serial;
      equippeditem.graphic := itm.graphic;
      equippeditem.layer := itm.layer;
      equippeditem.color := itm.color;
      equipmentarray.append(equippeditem);
    endforeach    
    var packet := CreatePacket(0x78, MSGLEN_VARIABLE);
    packet.setInt16(1, 0);
    packet.setInt32(3, npcmodel.serial);
    print(cstr(npcmodel.serial));
    packet.setInt16(7, npcmodel.graphic);
    packet.setInt16(9, x);
    packet.setInt16(11, y);
    packet.setInt8(13, z);
    packet.setInt8(14, facing);
    packet.setInt16(15, npcmodel.color);
    packet.setInt16(17, 0);
    
        foreach itm in equipmentarray
          if (itm.character == npcmodel.serial)
       
            packet.setInt32(packet.getSize(), itm.serial);
            if (itm.color == 0)
              graphic := itm.graphic;

            else
              graphic := itm.graphic + 32768;
            endif
            
            packet.setInt16(packet.getSize(), graphic);
            packet.setInt8(packet.getSize(), itm.layer);
            
            if (itm.color != 0)
              packet.setInt16(packet.getSize(), itm.color);
            endif
          endif
        endforeach
        packet.setInt32(packet.getSize(), 0);
        packet.setInt16(1, packet.getSize());
        
        packet.sendPacket(who);
      
 
   var struc := struct; struc.+npcmodel; struc.+loc; struc.+serial; struc.+color; struc.+graphic;
   var loc := {x, y, z};
   struc.npcmodel := npcmodel;
   struc.graphic := npcmodel.graphic;
   struc.loc := loc;
   struc.serial := npcmodel.serial;
   struc.color := npcmodel.color;
   return struc;
endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function DrawNpc(who, graphic, color, facing, x, y, z, equipment := 0)

var item_graphic;

var equipmentarray := {};

var npcmodel := CreateNpcFromTemplate( "man", 5276, 1164, 0);
SetObjProperty(npcmodel, "XYZ", {x, y, z});
npcmodel.frozen := 1;
npcmodel.graphic := graphic;
npcmodel.color := color;



sleep(3);
  
  
    var packet := CreatePacket(0x78, MSGLEN_VARIABLE);
    packet.setInt16(1, 0);
    packet.setInt32(3, npcmodel.serial);
    print(cstr(npcmodel.serial));
    packet.setInt16(7, npcmodel.graphic);
    packet.setInt16(9, x);
    packet.setInt16(11, y);
    packet.setInt8(13, z);
    packet.setInt8(14, facing);
    packet.setInt16(15, npcmodel.color);
    packet.setInt16(17, 0);
    
        foreach itm in equipment
            var the_item := CreateItemAtLocation( 5276, 1164, 0, itm.graphic);
            the_item.color := itm.color;
            equipitem(npcmodel, the_item);
          //if (itm.character == npcmodel.serial)
       
            packet.setInt32(packet.getSize(), the_item.serial);
            if (itm.color == 0)
              item_graphic := itm.graphic;

            else
              item_graphic := itm.graphic + 32768;
            endif
            
            packet.setInt16(packet.getSize(), item_graphic);
            packet.setInt8(packet.getSize(), the_item.layer);
            
            if (itm.color != 0)
              packet.setInt16(packet.getSize(), itm.color);
            endif
          //endif
        endforeach
        packet.setInt32(packet.getSize(), 0);
        packet.setInt16(1, packet.getSize());
        
        packet.sendPacket(who);
      
 
   var struc := struct; struc.+npcmodel; struc.+loc; struc.+serial; struc.+color; struc.+graphic;
   var loc := {x, y, z};
   struc.npcmodel := npcmodel;
   struc.graphic := npcmodel.graphic;
   struc.loc := loc;
   struc.serial := npcmodel.serial;
   struc.color := npcmodel.color;
   return struc;
   
endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


function DrawNpcfromNPC(who, npcmodel, facing, x, y, z)

var graphic;
var equipmentarray := {};
var equippeditem := struct;
equippeditem.+character;
equippeditem.+serial;
equippeditem.+graphic;
equippeditem.+layer;
equippeditem.+color;


//var npcmodel := CreateNpcFromTemplate( npctemplate, 5276, 1164, 0);
//npcmodel.frozen := 1;
sleep(3);
  foreach itm in ListEquippedItems( npcmodel ) 
      // print("EQP: " + itm.desc);
      equippeditem.character := npcmodel.serial;
      equippeditem.serial := itm.serial;
      equippeditem.graphic := itm.graphic;
      equippeditem.layer := itm.layer;
      equippeditem.color := itm.color;
      equipmentarray.append(equippeditem);
    endforeach    
    var packet := CreatePacket(0x78, MSGLEN_VARIABLE);
    packet.setInt16(1, 0);
    packet.setInt32(3, npcmodel.serial);
    print(cstr(npcmodel.serial));
    packet.setInt16(7, npcmodel.graphic);
    packet.setInt16(9, x);
    packet.setInt16(11, y);
    packet.setInt8(13, z);
    packet.setInt8(14, facing);
    packet.setInt16(15, npcmodel.color);
    packet.setInt16(17, 0);
    
        foreach itm in equipmentarray
          if (itm.character == npcmodel.serial)
       
            packet.setInt32(packet.getSize(), itm.serial);
            if (itm.color == 0)
              graphic := itm.graphic;

            else
              graphic := itm.graphic + 32768;
            endif
            
            packet.setInt16(packet.getSize(), graphic);
            packet.setInt8(packet.getSize(), itm.layer);
            
            if (itm.color != 0)
              packet.setInt16(packet.getSize(), itm.color);
            endif
          endif
        endforeach
        packet.setInt32(packet.getSize(), 0);
        packet.setInt16(1, packet.getSize());
        
        packet.sendPacket(who);
      
 
   var struc := struct; struc.+npcmodel; struc.+loc; struc.+serial; struc.+color; struc.+graphic;
   var loc := {x, y, z};
   struc.npcmodel := npcmodel;
   struc.graphic := npcmodel.graphic;
   struc.loc := loc;
   struc.serial := npcmodel.serial;
   struc.color := npcmodel.color;
   return struc;
endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function DrawObject(who, graphic, color, x, y, z, facing)
 var itm := CreateItemAtLocation( 5276, 1164, 0, 3637, 1 );
 itm.graphic := graphic;
 var pck := CreatePacket(0x78, MSGLEN_VARIABLE);
 pck.setInt16(1, 0);
 pck.setInt32(3, itm.serial);
 pck.setInt16(7, itm.graphic);
 pck.setInt16(9, x);
 pck.setInt16(11, y);
 pck.setInt8(13, z);
 pck.setInt8(14, facing);
 pck.setInt16(15, color);
 pck.setInt32(17, 0);
 pck.setInt16(21, 0);
 
 pck.setInt16(1, pck.getSize());
 
 pck.sendPacket(who);
 
endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function DeleteObject (who, lobj)
  
  var pck := CreatePacket(0x1D, 5);
  pck.setInt32(1, lobj.serial);
  pck.sendPacket(who);

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function SetScene(who, x, y, z, realm := 0)
        SwitchMap(who, realm);
        var pck := CreatePacket(0x20, 19);

        pck.setInt32(1, who.serial);
        pck.setInt16(5, who.graphic);
        pck.setInt8(7, 0);
        pck.setInt16(8, who.color);
        pck.setInt8(10, 0);
        pck.setInt16(11, x);
        pck.setInt16(13, y);
        pck.setInt16(15, 0);
        pck.setInt8(17, who.facing);
        pck.setInt8(18, z);
      
        pck.sendPacket(who);
      
endfunction  

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function SetSceneHidden(who, x, y, z, realm := 0)
        SwitchMap(who, realm);
        var pck := CreatePacket(0x20, 19);

        pck.setInt32(1, who.serial);
        pck.setInt16(5, 0);
        pck.setInt8(7, 0);
        pck.setInt16(8, who.color);
        pck.setInt8(10, 0);
        pck.setInt16(11, x);
        pck.setInt16(13, y);
        pck.setInt16(15, 0);
        pck.setInt8(17, who.facing);
        pck.setInt8(18, z);
      
        pck.sendPacket(who);
      
endfunction  

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function SetSceneWithGraphic(who, graphic, color, facing,  x, y, z)

        var pck := CreatePacket(0x20, 19);

        pck.setInt32(1, who.serial);
        pck.setInt16(5, graphic);
        pck.setInt8(7, 0);
        pck.setInt16(8, color);
        pck.setInt8(10, 0);
        pck.setInt16(11, x);
        pck.setInt16(13, y);
        pck.setInt16(15, 0);
        pck.setInt8(17, facing);
        pck.setInt8(18, z);
      
        pck.sendPacket(who);
      
endfunction 

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function HallucinateSelfView(who, graphic, color, facing)

        var pck := CreatePacket(0x20, 19);

        pck.setInt32(1, who.serial);
        pck.setInt16(5, graphic);
        pck.setInt8(7, 0);
        pck.setInt16(8, color);
        pck.setInt8(10, 0);
        pck.setInt16(11, who.x);
        pck.setInt16(13, who.y);
        pck.setInt16(15, 0);
        pck.setInt8(17, facing);
        pck.setInt8(18, who.z);
      
        pck.sendPacket(who);
      
endfunction 

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function MoveChar(who, charserial, graphic, direction, color,  x, y, z)
 
 var pck := CreatePacket(0x77, 17);
 pck.setInt32(1, charserial);
 pck.setInt16(5, graphic);
 pck.setInt16(7, x);
 pck.setInt16(9, y);
 pck.setInt8(11, z);
 pck.setInt8(12, direction);
 pck.setInt16(13, color);
 pck.setInt8(15, 0);
 pck.setInt8(16, 0);

 pck.sendPacket(who);

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function MoveCharByCharModel(who, charmodel, direction, x, y, z)
 SetObjProperty(charmodel, "XYZ", {x, y, z});
 print("CHRMOD: " + cstr(charmodel.serial));
 print("CHRMOD: " + cstr(charmodel.graphic));
 print("CHRMOD: " + cstr(charmodel.color));
 var pck := CreatePacket(0x77, 17);
 pck.setInt32(1, charmodel.serial);
 pck.setInt16(5, charmodel.graphic);
 pck.setInt16(7, x);
 pck.setInt16(9, y);
 pck.setInt8(11, z);
 pck.setInt8(12, direction);
 pck.setInt16(13, charmodel.color);
 pck.setInt8(15, 0);
 pck.setInt8(16, 0);
 
 pck.sendPacket(who);

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function ChangeCharModelGraphic(who, charmodel, graphic, color, facing)
 var loc := getobjproperty(charmodel, "XYZ");
 print("CHRMOD: " + cstr(charmodel.serial));
 print("CHRMOD: " + cstr(charmodel.graphic));
 print("CHRMOD: " + cstr(charmodel.color));
 var pck := CreatePacket(0x77, 17);
 pck.setInt32(1, charmodel.serial);
 pck.setInt16(5, graphic);
 pck.setInt16(7, GetObjProperty(charmodel, loc[1]));
 pck.setInt16(9, GetObjProperty(charmodel, loc[2]));
 pck.setInt8(11, GetObjProperty(charmodel, loc[3]));
 pck.setInt8(12, facing);
 pck.setInt16(13, color);
 pck.setInt8(15, 0);
 pck.setInt8(16, 0);
 
 pck.sendPacket(who);

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function AnimCharModel(who, charmodel, animation, facing, rep := 1, forward := 0, speed := 127 )

 
 var pck := CreatePacket(0x6E, 14);
 pck.setInt32(1, charmodel.serial);
 pck.setInt16(5, animation);
 pck.setInt8(7, 0);
 pck.setInt8(8, facing);
 pck.setInt16(9, rep);
 pck.setInt8(11, forward);
 pck.setInt8(12, 0);
 pck.setInt8(13, speed);

 pck.sendPacket(who);

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function MoveCharModelToXYZ(who, charmodel)
 while(Distance( who, charmodel ) > 1)
  MoveCharByCharModel(who, charmodel, getpgface(charmodel, who), x, y, z)
 endwhile
endfunction

function GetModelMovCoordsByFacing(facing, steps := 1)

var x, y, ret;

ret := struct;
ret.+x;
ret.+y;

if(facing == 0)
 x := who.x;
 y := who.y - steps;
elseif(who.facing == 1)
 x := who.x + steps;
 y := who.y - steps;
elseif(who.facing == 2)
 x := who.x + steps;
 y := who.y;
elseif(who.facing == 3)
 x := who.x + steps;
 y := who.y + steps;
elseif(who.facing == 4)
 x := who.x;
 y := who.y + steps;
elseif(who.facing == 5)
 x := who.x - steps;
 y := who.y + steps; 
elseif(who.facing == 6)
 x := who.x - steps;
 y := who.y;
elseif(who.facing == 7)
 x := who.x - steps;
 y := who.y - steps;  
endif

ret.x := x;
ret.y := y;

return ret;

endfunction