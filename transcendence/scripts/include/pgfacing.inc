//By Apeiron 29/12/01

use uo;

function pgface(character, object)

var mex := character.x;
var mey := character.y;
var obx := object.x;
var oby := object.y;

if (mex == obx)
  if (mey > oby)
     character.facing := 0;
  elseif (mey < oby)
     character.facing := 4;
  endif
 
elseif (mex > obx)
  if (mey < oby)
    character.facing := 5;
  elseif (mey == oby)
    character.facing := 6;
  else
    character.facing := 7;
  endif

else
  if (mey < oby)
    character.facing := 3;
  elseif (mey == oby)
    character.facing := 2;
  else
    character.facing := 1;
  endif
endif

endfunction

function getpgface(character, object)

var mex := character.x;
var mey := character.y;
var obx := object.x;
var oby := object.y;

var facing;

if (mex == obx)
  if (mey > oby)
     facing := 0;
  elseif (mey < oby)
     facing := 4;
  endif
 
elseif (mex > obx)
  if (mey < oby)
    facing := 5;
  elseif (mey == oby)
    facing := 6;
  else
    facing := 7;
  endif

else
  if (mey < oby)
    facing := 3;
  elseif (mey == oby)
    facing := 2;
  else
    facing := 1;
  endif
  
  return facing;
  
endif

endfunction


function xyface(character, x, y)

var mex := character.x;
var mey := character.y;


if (mex == x)
  if (mey > y)
     character.facing := 0;
  elseif (mey < y)
     character.facing := 4;
  endif
 
elseif (mex > x)
  if (mey < y)
    character.facing := 5;
  elseif (mey == y)
    character.facing := 6;
  else
    character.facing := 7;
  endif

else
  if (mey < y)
    character.facing := 3;
  elseif (mey == y)
    character.facing := 2;
  else
    character.facing := 1;
  endif
endif

endfunction

function GetMovCoordsByFacing(who, steps := 1)

var x, y, ret;

ret := struct;
ret.+x;
ret.+y;

if(who.facing == 0)
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