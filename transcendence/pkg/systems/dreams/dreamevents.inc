const DREAMEVENT_NEWACTOR := 0x0001;
const DREAMEVENT_NEWITEM := 0x0002;
const DREAMEVENT_2DFX := 0x0003;
const DREAMEVENT_3DFX := 0x0004;
const DREAMEVENT_PLAYMUSIC := 0x0005;
const DREAMEVENT_PLAYSOUND := 0x0006;
const DREAMEVENT_LIGHTLEVEL := 0x0007;
const DREAMEVENT_CHANGESCENE := 0x0008;
const DREAMEVENT_CHANGEPERSONALGRAPHIC := 0x0009;
const DREAMEVENT_SYSMESSAGE := 0x000a;
const DREAMEVENT_FADELIGHT := 0x000b;
const DREAMEVENT_DELETOBJ := 0x000c;
const DREAMEVENT_PAUSE := 0x000d;
const DREAMEVENT_SETWEATHER := 0x0010;
const DREAMEVENT_SETSEASON := 0x0011;

function AddActorEvent(actortype,  graphic, color, facing, x, y, z, npctemplate := "", equipment := 0, actions := 0 )
 
 var ev := struct;
 ev.+actortype := actortype;
 
 ev.+type := 1;
 ev.+graphic := graphic;
 ev.+color := color;
 ev.+facing := facing;
 ev.+x := x;
 ev.+y := y;
 ev.+z := z;
 ev.+npctemplate := npctemplate;
 ev.+equipment := equipment;
 ev.+action := actions;
 
 return ev;

endfunction

function AddItemEvent(graphic, color, facing, x, y, z )

 var ev := struct;
 ev.+type := 2;
 ev.+graphic := graphic;
 ev.+color := color;
 ev.+facing := facing;
 ev.+x := x;
 ev.+y := y;
 ev.+z := z;
 
 return ev;

endfunction

function Fx2D(fx, color, x, y, z )

 var ev := struct;
 ev.+type := 3;
 ev.+fx := fx;
 ev.+color := color;
 ev.+x := x;
 ev.+y := y;
 ev.+z := z;
 
 return ev;

endfunction

function Fx3D(fx, x, y, z )

 var ev := struct;
 ev.+type := 4;
 ev.+fx := fx;
 ev.+x := x;
 ev.+y := y;
 ev.+z := z;
 
 return ev;

endfunction

function PlayDreamMusic( musicID )

 var ev := struct;
 ev.+type := 5;
 ev.+music := musicID;

 return ev;

endfunction

function PlaySound( soundID, x, y, z )

 var ev := struct;
 ev.+type := 6;
 ev.+sound := soundID;
 ev.+x := x;
 ev.+y := y;
 ev.+z := z;
 
 return ev;

endfunction

function ChangeLight( lightlevel )

 var ev := struct;
 ev.+type := 7;
 ev.+light := lightlevel;

 return ev;

endfunction

function ChangeScene( x, y, z, realm := 0 )

 var ev := struct;
 ev.+type := 8;
 ev.+x := x;
 ev.+y := y;
 ev.+z := z;
 ev.+realm := realm;
 return ev;

endfunction

function ChangePersonalGraphic( graphic, color )

 var ev := struct;
 ev.+type := 9;
 ev.+graphic := graphic;
 ev.+color := color;

 return ev;

endfunction

function SysMessage( message, font := 3 , color := 90 )

 var ev := struct;
 ev.+type := 0xa;
 ev.+msg := message;
 ev.+font := font;
 ev.+color := color;

 return ev;

endfunction

function DelObject( objID )

 var ev := struct;
 ev.+type := 0xa;
 ev.+serial := objID;

 return ev;

endfunction

function SetDreamWeather( weathertype, level )

 var ev := struct;
 ev.+type := 0x10;
 ev.+weather := weathertype;
 ev.+level := level;

 return ev;

endfunction

function SetDreamSeason( season )

 var ev := struct;
 ev.+type := 0x10;
 ev.+season := season;
 
 return ev;

endfunction



