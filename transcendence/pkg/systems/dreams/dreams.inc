// by ArT-iX 14/03/2004
// requires hallucinations.inc, uo.inc

function InitScene(scene_x, scene_y, scene_z, scene_realm := 0, lightlevel := 0, hidden := 0)

 var scene := struct;
 scene.+x;
 scene.+y;
 scene.+z;
 scene.+realm;
 scene.+mobiles;
 scene.+items;
 scene.+mobequipment;
 scene.+lightlevel;
 scene.+events;
 scene.+hidden := hidden;
 
 scene.x := scene_x;
 scene.y := scene_y;
 scene.z := scene_z;
 scene.realm := scene_realm;
 scene.lightlevel := lightlevel;
 scene.mobiles := {};
 scene.items := {};
 scene.mobequipment := {};
 scene.events := {};
 
 return scene;
 
endfunction

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

function CreateActor(graphic, color, facing, x, y, z, equipment := 0, actions := {} )
 
 var actor := struct;
 actor.+type;
 actor.+graphic;
 actor.+color;
 actor.+facing;
 actor.+x;
 actor.+y;
 actor.+z;
 actor.+equipment;
 actor.+actions; 
 
 actor.type := "custom";
 actor.graphic := graphic;
 actor.color := color;
 actor.facing := facing;
 actor.x := x;
 actor.y := y;
 actor.z := z;
 actor.equipment := equipment;
 actor.actions := actions; 

 return actor;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

function CreateActorFromNPCTemplate(npctemplate, facing, color, x, y, z, actions := {})
 
 var actor := struct;
 actor.+type;
 actor.+npctemplate;
 //actor.+graphic;
 actor.+color;
 actor.+facing;
 actor.+x;
 actor.+y;
 actor.+z;
 actor.+equipment;
 actor.+actions; 
 
 actor.type := "template";
 actor.npctemplate := npctemplate;
 //actor.graphic := graphic;
 actor.color := color;
 actor.facing := facing;
 actor.x := x;
 actor.y := y;
 actor.z := z;
 //actor.equipment := equipment;
 actor.actions := actions; 

 return actor;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

function AddActorToScene(actor, byref scene)
 
 var scenemobiles := scene.mobiles;
 scenemobiles.append(actor);
 scene.mobiles := scenemobiles;
 return scene;
  
endfunction

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


function CreateItem(graphic, color, facing, x, y, z, events := 0 )
 
 var itm := struct;
 itm.+graphic;
 itm.+color;
 itm.+facing;
 itm.+x;
 itm.+y;
 itm.+z;
 itm.+events; 
 
 
 itm.graphic := graphic;
 itm.color := color;
 itm.facing := facing;
 itm.x := x;
 itm.y := y;
 itm.z := z;
 itm.events := events; 

 return itm;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

function AddItemToScene(item, byref scene)
 
 var sceneitems := scene.items;
 scenitems.append(actor);
 scene.items := sceneitems;
 return scene;
  
endfunction

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

function InitActionSequence()

 var sequence := {};
 return sequence;
 
endfunction

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

function CreateAction(actiontype, time)
 
 //var action := struct;
 //action.+type;
 actiontype.+time;
 
 //action.type := actiontype;
 actiontype.time := time;
 print("AZIONE : " + cstr(actiontype));
 return actiontype;
 
endfunction

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

function AddActionToSequence(action, byref sequence)
 
 
 sequence.append(action);
 return sequence;
 
endfunction

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

function CreateDreamEvent(event, time)
 
 //var event := struct;
 //event.+type;
 print(cstr(event));
 event.+time;
 event.time := time;
 print(cstr(event));
 return event;
 
endfunction

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

function AddEventToScene(event, byref scene)
 
 var events := scene.events;
 //print("ADD EVENT: " + cstr(event));
 events.append(event);
 scene.events := events;
 return scene;
 
endfunction

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

function CreateDream(name, scene, music := 0, generator := "", type := "")

 var dream := struct;
 dream.+name;
 dream.+generator;
 dream.+type;
 dream.+music;
 dream.+scene;
 
 dream.name := name;
 dream.music := music;
 dream.generator := generator;
 dream.type := type;
 dream.scene := scene;

 return dream;

endfunction

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

function StartDream(who, dream, duration := 0)

 if(dream.music != 0)
  PlayDigitalMusic(who, dream.music);
 endif
 
 //who.frozen := 0;
 var whorealm := who.realm;
 var scene := dream.scene;
 
 var mobilearray := scene.mobiles;
 var equipmentarray := scene.mobequipment;
 var graphic;
 
 if(scene.hidden == 1)
  SetSceneHidden(who, scene.x, scene.y, scene.z, scene.realm);
 else
  SetScene(who, scene.x, scene.y, scene.z, scene.realm);
 endif
 /*
  foreach mob in ListMobilesNearLocation(who.x, who.y, who.z, 30)
    DeleteObject(who, mob);
  endforeach
   */ 
   var chr;
   
  foreach mob in mobilearray
      
      if(mob.type == "custom")  
        chr := DrawNpc(who, mob.graphic, mob.color, mob.facing, mob.x, mob.y, mob.z, mob.equipment);
        start_script(":Dreams:actions_performer", {who, chr.npcmodel, mob.actions});
      elseif(mob.type == "template")
      	chr := DrawNpcfromNPCTemplate(who, mob.npctemplate, mob.facing, mob.x, mob.y, mob.z);
      	
      	start_script(":Dreams:actions_performer", {who, chr.npcmodel, mob.actions});
      endif	  
  endforeach
  
  var itemarray := scene.items;
    
    foreach itm in itemarray
      
      DrawObject(who, itm.graphic, itm.color, itm.x, itm.y, itm.z, itm.facing);
     
    endforeach
    
    var evs := scene.events;
    var evs_duration := 0;
    
    foreach ev in evs
     evs_duration := evs_duration + ev.time;
    endforeach
    
    duration := evs_duration + duration;
    
    start_script(":Dreams:eventperformer", {who, dream});
    
    //////// DA MODIFICARE
    
    /*var recstop := 0;
    while ((who.ip) && (recstop == 0))
      if (YesNo(who, "Do you want to stop recalling?"))
        recstop := 1;
      endif
    endwhile*/
    //Thaw(who);
    sleep(duration);
    who.frozen := 0;
    var whox := who.x;
    var whoy := who.y;
    var whoz := who.z;
    if(who.realm == "britannia")
    MoveCharacterToLocation(who, 5276, 1164, 0);
    else
    MoveObjectToRealm(who, "britannia", 5276, 1164, 0);
endif
if(whorealm == who.realm)
    MoveCharacterToLocation(who, whox, whoy, whoz);
else
 MoveObjectToRealm(who, whorealm, whox, whoy, whoz);	
endif	    
    //EraseObjProperty(who, "#mrecalling");
    SendSysMessage(who, "You awake from dream.");
	
endfunction

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

function GetRealmStringFromRealmID(realmid)
case(realmid)
0: return "britannia"; 
1: return "britannia_alt"; 
2: return "ilshenar"; 
3: return "malas"; 
endcase
endfunction



