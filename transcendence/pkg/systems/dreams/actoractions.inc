const ACTORACTION_MOVEXYZ := 0x1;
const ACTORACTION_MOVETO := 0x2;
const ACTORACTION_PERFORMANIM := 0x3;
const ACTORACTION_SPEAK := 0x4;
const ACTORACTION_EQUIP := 0x5;
const ACTORACTION_UNEQUIP := 0x6;
const ACTORACTION_DIE := 0x7;
const ACTORACTION_CHANGEGRAPHIC := 0x8;
const ACTORACTION_PAUSE := 0x9;

function ActorMoveXYZ(x, y, z)

 var ev := struct;
 ev.+type := 0x1;
 ev.+x := x;
 ev.+y := y;
 ev.+z := z;
 
 return ev;
 
endfunction

function ActorMoveToObj( objID )

 var ev := struct;
 ev.+type := 0x2;
 ev.+obj := objID;
 
 return ev;
 
endfunction

function ActorPerformAnim( anim )

 var ev := struct;
 ev.+type := 0x3;
 ev.+anim := anim;
 
 return ev;
 
endfunction

function ActorSpeak( msg, font := 3, color := 0 )

 var ev := struct;
 ev.+type := 0x4;
 ev.+msg := msg;
 ev.+font := font;
 ev.+color := color;
 
 return ev;
 
endfunction

function ActorUnequip( layer )

 var ev := struct;
 ev.+type := 0x6;
 ev.+layer := layer;
 
 return ev;
 
endfunction

function ActorEquip( itemtype, color )

 var ev := struct;
 ev.+type := 0x5;
 ev.+item := itemtype;
 ev.+color := color;
 
 return ev;
 
endfunction

function ActorChangeGraphic( graphic, color )

 var ev := struct;
 ev.+type := 0x8;
 ev.+graphic := graphic;
 ev.+color := color;
 
 return ev;
 
endfunction
