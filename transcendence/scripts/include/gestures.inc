// gestures library by ArT-iX
// requires Polsys.em, "pgface.inc" and animations.inc


function Hello(who, towhom)
 
 pgface(who, towhom);
 PlayCharAnim3D( who, 126);

endfunction

function GoodBye(who, towhom)
 
 pgface(who, towhom);
 PlayCharAnim3D( who, 127);

endfunction

function BowFormal(who, towhom)
 
 pgface(who, towhom);
 PlayCharAnim3D( who, 105);

endfunction

function BowLesser(who, towhom)
 
 pgface(who, towhom);
 PlayCharAnim3D( who, 106);

endfunction

function Applaud(who, towhom)
 
 pgface(who, towhom);
 PlayCharAnim3D( who, 100);

endfunction

function DanceFolk(who, slp := 1, type := 1)
 
 if (type == 1)
  PlayCharAnim3D( who, 109);
 else
  PlayCharAnim3D( who, 110);
 endif	
 if(slp == 1)
  sleep(4);
 endif
endfunction

function DanceNerd(who, slp := 1)
 
 PlayCharAnim3D( who, 111);
 if(slp == 1)
  sleep(4);
 endif

endfunction

function DanceTribal(who, slp := 1)
 
 PlayCharAnim3D( who, 112);
 if(slp == 1)
  sleep(4);
 endif

endfunction

function GoodBye(who, towhom, type := 1, slp := 1)

 if (type == 1)
  PlayCharAnim3D( who, 125);
 elseif (type == 2)
  PlayCharAnim3D( who, 126);
 elseif (type == 3)
  PlayCharAnim3D( who, 126);
 endif	
 if(slp == 1)
  sleep(4);
 endif

endfunction

function CoverEars(who)
 
 PlayCharAnim3D( who, 107);

endfunction

function Victory(who, towhom, type := 1, slp := 1)
 if (type == 1)
  PlayCharAnim3D( who, 123);
 elseif (type == 2)
  PlayCharAnim3D( who, 124);
 endif	
 if(slp == 1)
  sleep(4);
 endif

endfunction

function Cry(who, anm := 1, loop := 1)
var i;
for (i := 1; i <= loop; i := i + 1)
 if(anm == 1)
  PlayCharAnim3D( who, 107);
 endif
 if(who.graphic == 401)
  PlaySoundEffect( who, 788 );
 elseif(who.graphic == 400)
  PlaySoundEffect( who, 1059 );
 endif
 sleep(1);
endfor 
endfunction


function Kiss(who, whom)
 
 pgface(who, towhom);
 PlayCharAnim3D( who, 104);

endfunction

function Negate(who)

 PlayCharAnim3D( who, 121);

endfunction

function Affermate(who)

 PlayCharAnim3D( who, 116);

endfunction

function AhAh(who)
 if(who.graphic == 401)
  PlaySoundEffect( who, 780 );
 elseif(who.graphic == 400)
  PlaySoundEffect( who, 1051 );
 endif	
 PlayCharAnim3D( who, 116);

endfunction

function Yawn(who)
 
 if(who.graphic == 401)
  PlaySoundEffect( who, 823 );
 elseif(who.graphic == 400)
  PlaySoundEffect( who, 1097 );
 endif	
 PlayCharAnim3D( who, 6);

endfunction

function Drunken(who)
 var i;
 PlayCharAnim3D( who, 295);
 for(i := 1; i <= 5; i := i + 1)
  if(who.graphic == 401)
   PlaySoundEffect( who, 799 );
  elseif(who.graphic == 400)
   PlaySoundEffect( who, 1071 );
  endif
  sleep(1);
 endfor
 PlayCharAnim3D( who, 294);
 for(i := 1; i <= 7; i := i + 1)
  if(who.graphic == 401)
   PlaySoundEffect( who, 799 );
  elseif(who.graphic == 400)
   PlaySoundEffect( who, 1071 );
  endif
  sleep(1);
 endfor
endfunction

function DrunkenAndPuke(who)
 var i;
 PlayCharAnim3D( who, 295);
 for(i := 1; i <= 5; i := i + 1)
  if(who.graphic == 401)
   PlaySoundEffect( who, 799 );
  elseif(who.graphic == 400)
   PlaySoundEffect( who, 1071 );
  endif
  sleep(1);
 endfor
 PlayCharAnim3D( who, 294);
 for(i := 1; i <= 7; i := i + 1)
  if(who.graphic == 401)
   PlaySoundEffect( who, 814 );
  elseif(who.graphic == 400)
   PlaySoundEffect( who, 1088 );
  endif
  sleep(1);
 endfor
endfunction

function AgedFidget(who)
 PlayCharAnim3D( who, 298);
endfunction

function AgedIdle(who)
 PlayCharAnim3D( who, 299);
endfunction