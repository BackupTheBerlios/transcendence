//**********************************************************************************************
//
//
//
//
//
//
//
//
//
//
//**********************************************************************************************






function CreateNpcModel(npctemplate)
local critt := CreateNpcFromTemplate( npctemplate, 5276, 1164, 0);
critt.frozen := 1;
local struc := struct;
struc.+ref;
struc.+model; 
struc.+graphic;
struc.+color; 
struc.+serial; 
struc.+facing; 
struc.+equip; 
struc.ref := critt;
struc.model := critt.objtype;
struc.graphic := critt.graphic;
struc.color := critt.color;
struc.serial := critt.serial;
struc.facing := critt.facing;
struc.equip := ListEquippedItems( critt );
return struc; 
endfunction


function DrawNpcfromNPCModel (who, npcmodel, x, y, z)
local graphic;
//local whos := target(who);
//local where := targetcoordinates (who);
local equipmentarray := {};
  foreach item in npcmodel.equip
      equipmentarray.append({npcmodel.serial, item.serial, item.graphic, item.layer, item.color});
    endforeach    
      var  PacketHexStringPart1 := "78";
      var   PacketHexStringPart2 := ConvertIntToHex(npcmodel.serial, 4) + ConvertIntToHex(npcmodel.graphic, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(x, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(y, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(z, 1);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(npcmodel.facing, 1);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(npcmodel.color, 2);
        PacketHexStringPart2 := PacketHexStringPart2 +"0000";
        foreach item in equipmentarray
          if (item[1] = npcmodel.serial)
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[2], 4);
            if (item[5] = 0)
              graphic := item[3];

            else
              graphic := item[3] + 32768;
            endif
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(graphic, 2);
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[4], 1);
            if (item[5] != 0)
              PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[5], 2);
            endif
          endif
        endforeach
        PacketHexStringPart2 := PacketHexStringPart2 +"00000000";
        var FullPacketHexStringLength := (len(PacketHexStringPart1) + len(PacketHexStringPart2)) / 2 + 2;
        var FullPacketHexString := PacketHexStringPart1 + ConvertIntToHex(FullPacketHexStringLength, 2) + PacketHexStringPart2;
        SendPacket(who, FullPacketHexString);
      
 /* sleep (10);
  sendsysmessage(who, "animation");
    PerformAction( whos, 1 );
   PrintTextAbove( whos, "anim" ); */
   var struc := struct; struc.+npcmodel; struc.+loc;
   var loc := {x, y, z};
   struc.npcmodel := npcmodel;
   struc.loc := loc;
   return struc;
endfunction




function DrawNpcfromNPCTemplate (who, npctemplate, x, y, z)
local graphic;
//local whos := target(who);
//local where := targetcoordinates (who);
local equipmentarray := {};
  var npcmodel := CreateNpcFromTemplate( npctemplate, 5276, 1164, 0);
  npcmodel.frozen := 1;
  foreach item in ListEquippedItems( npcmodel ) 
      equipmentarray.append({npcmodel.serial, item.serial, item.graphic, item.layer, item.color});
    endforeach    
      var  PacketHexStringPart1 := "78";
      var   PacketHexStringPart2 := ConvertIntToHex(npcmodel.serial, 4) + ConvertIntToHex(npcmodel.graphic, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(x, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(y, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(z, 1);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(npcmodel.facing, 1);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(npcmodel.color, 2);
        PacketHexStringPart2 := PacketHexStringPart2 +"0000";
        foreach item in equipmentarray
          if (item[1] = npcmodel.serial)
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[2], 4);
            if (item[5] = 0)
              graphic := item[3];

            else
              graphic := item[3] + 32768;
            endif
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(graphic, 2);
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[4], 1);
            if (item[5] != 0)
              PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[5], 2);
            endif
          endif
        endforeach
        PacketHexStringPart2 := PacketHexStringPart2 +"00000000";
        var FullPacketHexStringLength := (len(PacketHexStringPart1) + len(PacketHexStringPart2)) / 2 + 2;
        var FullPacketHexString := PacketHexStringPart1 + ConvertIntToHex(FullPacketHexStringLength, 2) + PacketHexStringPart2;
        SendPacket(who, FullPacketHexString);
      
 /* sleep (10);
  sendsysmessage(who, "animation");
    PerformAction( whos, 1 );
   PrintTextAbove( whos, "anim" ); */
   var struc := struct; struc.+npcmodel; struc.+loc;
   var loc := {x, y, z};
   struc.npcmodel := npcmodel;
   struc.loc := loc;
   return struc;
endfunction

/*function DrawNpcfromNPCTemplate (who, npctemp, x, y, z)
local graphic;
//local whos := target(who);
//local where := targetcoordinates (who);
local equipmentarray := {};
  var npcmodel := CreateNpcFromTemplate( npctemp, 5276, 1164, 0);
  npcmodel.frozen := 1;
  foreach item in ListEquippedItems( npcmodel ) 
      equipmentarray.append({npcmodel.serial, item.serial, item.graphic, item.layer, item.color});
    endforeach    
      var  PacketHexStringPart1 := "78";
      var   PacketHexStringPart2 := ConvertIntToHex(npcmodel.serial, 4) + ConvertIntToHex(npcmodel.graphic, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(x, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(y, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(z, 1);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(npcmodel.facing, 1);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(npcmodel.color, 2);
        PacketHexStringPart2 := PacketHexStringPart2 +"0000";
        foreach item in equipmentarray
          if (item[1] = npcmodel.serial)
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[2], 4);
            if (item[5] = 0)
              graphic := item[3];

            else
              graphic := item[3] + 32768;
            endif
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(graphic, 2);
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[4], 1);
            if (item[5] != 0)
              PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[5], 2);
            endif
          endif
        endforeach
        PacketHexStringPart2 := PacketHexStringPart2 +"00000000";
        var FullPacketHexStringLength := (len(PacketHexStringPart1) + len(PacketHexStringPart2)) / 2 + 2;
        var FullPacketHexString := PacketHexStringPart1 + ConvertIntToHex(FullPacketHexStringLength, 2) + PacketHexStringPart2;
        SendPacket(who, FullPacketHexString);
      
sleep (10);
  sendsysmessage(who, "animation");
    PerformAction( whos, 1 );
   PrintTextAbove( whos, "anim" ); 
   var struc := struct; struc.+npcmodel; struc.+loc;
   var loc := {x, y, z};
   struc.npcmodel := npcmodel;
   struc.loc := loc;
   return struc;
endfunction*/


function DrawNpc (who, graph, x, y, z, color, facing, equipment)
local graphic;
//local whos := target(who);
//local where := targetcoordinates (who);
local equipmentarray := {};
  var npcmodel := CreateNpcFromTemplate( "man", 5276, 1164, 0);
  npcmodel.graphic := graph;
  npcmodel.color := color;
  npcmodel.facing := facing;
  foreach item in equipment
  equipitem (npcmodel, item);
  endforeach
  npcmodel.frozen := 1;
  foreach item in ListEquippedItems( npcmodel ) 
      equipmentarray.append({npcmodel.serial, item.serial, item.graphic, item.layer, item.color});
    endforeach    
      var  PacketHexStringPart1 := "78";
      var   PacketHexStringPart2 := ConvertIntToHex(npcmodel.serial, 4) + ConvertIntToHex(npcmodel.graphic, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(x, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(y, 2);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(z, 1);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(npcmodel.facing, 1);
        PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(npcmodel.color, 2);
        PacketHexStringPart2 := PacketHexStringPart2 +"0000";
        foreach item in equipmentarray
          if (item[1] = npcmodel.serial)
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[2], 4);
            if (item[5] = 0)
              graphic := item[3];

            else
              graphic := item[3] + 32768;
            endif
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(graphic, 2);
            PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[4], 1);
            if (item[5] != 0)
              PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(item[5], 2);
            endif
          endif
        endforeach
        PacketHexStringPart2 := PacketHexStringPart2 +"00000000";
        var FullPacketHexStringLength := (len(PacketHexStringPart1) + len(PacketHexStringPart2)) / 2 + 2;
        var FullPacketHexString := PacketHexStringPart1 + ConvertIntToHex(FullPacketHexStringLength, 2) + PacketHexStringPart2;
        SendPacket(who, FullPacketHexString);
      
 /* sleep (10);
  sendsysmessage(who, "animation");
    PerformAction( whos, 1 );
   PrintTextAbove( whos, "anim" ); */
   var struc := struct; struc.+npcmodel; struc.+loc;
   var loc := {x, y, z};
   struc.npcmodel := npcmodel;
   struc.loc := loc;
   return struc;
endfunction

function drawobject(who, graphic, color, x, y, z, facing)
 local item := CreateItemAtLocation( 5276, 1164, 0, 3637, 1 );
 item.graphic := graphic;
 local PacketHexStringPart1 := "78";
      local PacketHexStringPart2 := ConvertIntToHex(item.serial, 4) + ConvertIntToHex(item.graphic, 2);
      PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(x, 2);
      PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(y, 2);
      PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(z, 1);
      PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(facing, 1);
      PacketHexStringPart2 := PacketHexStringPart2 + ConvertIntToHex(color, 2);
      PacketHexStringPart2 := PacketHexStringPart2 +"000000000000";
      var FullPacketHexStringLength := (len(PacketHexStringPart1) + len(PacketHexStringPart2)) / 2 + 2;
      var FullPacketHexString := PacketHexStringPart1 + ConvertIntToHex(FullPacketHexStringLength, 2) + PacketHexStringPart2;
      SendPacket(who, FullPacketHexString);

endfunction

function DeleteObj (who, lobj)
  var PacketHexString := "1D"+ ConvertIntToHex(lobj.serial, 4);
  SendPacket(who, PacketHexString);
endfunction

function ClearCell()
foreach item in ListItemsNearLocation( 5267, 1164, 0, 5 )
destroyitem(item);
endforeach

foreach critt in ListMobilesNearLocation( 5267, 1164, 0, 5 )
RevokePrivilege( critt, "invul" );
            setobjproperty(critt, "guardkill", 1);
            Damage( critt, critt.hp );
endforeach
endfunction







function SetScene(who, x, y, z)
local PacketHexString := "20"+ ConvertIntToHex(who.serial, 4);
       /* if (who.gender)
          graphic := 403;

        else
          graphic := 402;
        endif*/
        PacketHexString := PacketHexString + ConvertIntToHex(600, 2);
        PacketHexString := PacketHexString +"00";
        PacketHexString := PacketHexString + ConvertIntToHex(who.color, 2);
        PacketHexString := PacketHexString +"00";
        PacketHexString := PacketHexString + ConvertIntToHex(x, 2);
        PacketHexString := PacketHexString + ConvertIntToHex(y, 2);
        PacketHexString := PacketHexString +"0000";
        PacketHexString := PacketHexString + ConvertIntToHex(who.facing, 1);
        PacketHexString := PacketHexString + ConvertIntToHex(z, 1);
        SendPacket(who, PacketHexString);
endfunction   

function SetSceneWithSelfGraphic(who, x, y, z)
local PacketHexString := "20"+ ConvertIntToHex(who.serial, 4);
       /* if (who.gender)
          graphic := 403;

        else
          graphic := 402;
        endif*/
        PacketHexString := PacketHexString + ConvertIntToHex(who.graphic, 2);
        PacketHexString := PacketHexString +"00";
        PacketHexString := PacketHexString + ConvertIntToHex(who.color, 2);
        PacketHexString := PacketHexString +"00";
        PacketHexString := PacketHexString + ConvertIntToHex(x, 2);
        PacketHexString := PacketHexString + ConvertIntToHex(y, 2);
        PacketHexString := PacketHexString +"0000";
        PacketHexString := PacketHexString + ConvertIntToHex(who.facing, 1);
        PacketHexString := PacketHexString + ConvertIntToHex(z, 1);
        SendPacket(who, PacketHexString);
endfunction   

function SetSceneWithNewGraphic(who, x, y, z, graphic, facing, color)
local PacketHexString := "20"+ ConvertIntToHex(who.serial, 4);
       /* if (who.gender)
          graphic := 403;

        else
          graphic := 402;
        endif*/
        PacketHexString := PacketHexString + ConvertIntToHex(graphic, 2);
        PacketHexString := PacketHexString +"00";
        PacketHexString := PacketHexString + ConvertIntToHex(color, 2);
        PacketHexString := PacketHexString +"00";
        PacketHexString := PacketHexString + ConvertIntToHex(x, 2);
        PacketHexString := PacketHexString + ConvertIntToHex(y, 2);
        PacketHexString := PacketHexString +"0000";
        PacketHexString := PacketHexString + ConvertIntToHex(facing, 1);
        PacketHexString := PacketHexString + ConvertIntToHex(z, 1);
        SendPacket(who, PacketHexString);
endfunction 

function SetSceneinBlackAndWhite(who, x, y, z)
local PacketHexString := "20"+ ConvertIntToHex(who.serial, 4);
        if (who.gender)
          graphic := 403;

        else
          graphic := 402;
        endif
        PacketHexString := PacketHexString + ConvertIntToHex(graphic, 2);
        PacketHexString := PacketHexString +"00";
        PacketHexString := PacketHexString + ConvertIntToHex(who.color, 2);
        PacketHexString := PacketHexString +"00";
        PacketHexString := PacketHexString + ConvertIntToHex(x, 2);
        PacketHexString := PacketHexString + ConvertIntToHex(y, 2);
        PacketHexString := PacketHexString +"0000";
        PacketHexString := PacketHexString + ConvertIntToHex(who.facing, 1);
        PacketHexString := PacketHexString + ConvertIntToHex(z, 1);
        SendPacket(who, PacketHexString);
endfunction 
     
function SelfView(who, graphic, color)
local PacketHexString := "20"+ ConvertIntToHex(who.serial, 4);
        /*if (who.gender)
          graphic := 403;

        else
          graphic := 402;
        endif*/
        PacketHexString := PacketHexString + ConvertIntToHex(graphic, 2);
        PacketHexString := PacketHexString +"00";
        PacketHexString := PacketHexString + ConvertIntToHex(color, 2);
        PacketHexString := PacketHexString +"00";
        PacketHexString := PacketHexString + ConvertIntToHex(who.x, 2);
        PacketHexString := PacketHexString + ConvertIntToHex(who.y, 2);
        PacketHexString := PacketHexString +"0000";
        PacketHexString := PacketHexString + ConvertIntToHex(who.facing, 1);
        PacketHexString := PacketHexString + ConvertIntToHex(who.z, 1);
        SendPacket(who, PacketHexString);
endfunction