function fligh(mob, dir, height, tiles)

var facin;
var t;
var dirs := {};
case (dir)

"n":
facin := 0;
dirs := {mob.x, mob.y - 1};
subtractx := 0;
"ne":
facin := 1;
dirs := {mob.x + 1, mob.y - 1};
subtractx := 1;
"e":
facin := 2;
dirs := {mob.x + 1, mob.y};
subtractx := 1;
subtracty := 0;
"se":
facin := 3;
dirs := {mob.x + 1, mob.y + 1};
subtractx := 1;
subtracty := 1;
"s":
facin := 4;
dirs := {mob.x, mob.y + 1};
subtractx := 0;
subtracty := 1;
"sw":
facin := 5;
dirs := {mob.x - 1, mob.y + 1};
subtracty := 1;
"w":
facin := 6;
dirs := {mob.x - 1, mob.y};
subtracty := 0;
"nw":
facin := 7;
dirs := {mob.x - 1, mob.y - 1};
endcase

mob.facing := facin;
while (mob.z != height)
 MoveCharacterToLocation( who, dirs[1], dirs[2], who.z + 1, MOVECHAR_FORCELOCATION);
endwhile
for (t := 0; t <= tiles; t := t + 1)
MoveCharacterToLocation( who, dirs[1], dirs[2], height, MOVECHAR_FORCELOCATION);
endfor
endfunction

