function effetto(x, y, z, realm, graf, col, tempo);

var anm := CreateItemAtLocation(x, y, z, graf, 1, realm);
anm.color := col;
sleep(tempo);
DestroyItem(anm);
endfunction

function bolteff(startchar, endchar, graf, col, speed)

var the_bolt := CreateItemAtLocation(startchar.x, startchar.y, startchar.z, graph, 1, startchar.realm);
the_bolt.color := col;
var direzione;
var xadv;
var yadv;
var zadv;
repeat
if (endchar.x > the_bolt.x)
xadv := the_bolt.x + 1;
elseif (the_bolt.x > endchar.x)
xadv := the_bolt.x - 1;
elseif (the_bolt.x == endchar.x)
xadv := the_bolt.x;
endif

if (endchar.y > the_bolt.y)
yadv := the_bolt.y + 1;
elseif (the_bolt.y > endchar.y)
yadv := the_bolt.y - 1;
elseif (the_bolt.y == endchar.y)
yadv := the_bolt.y;
endif

if (endchar.z > the_bolt.z)
zadv := the_bolt.z + 1;
elseif (the_bolt.z > endchar.z)
zadv := the_bolt.z - 1;
elseif (the_bolt.z == endchar.z)
zadv := the_bolt.z;
endif

MoveItemToLocation(the_bolt, xadv, yadv, zadv);
sleepms(speed);
var bolt_pos := GetPosition(the_bolt);
var targpos := GetPosition(endchar);
until bolt_pos == targpos;
endfunction

function FadeLightLevel(who, startlev, endlev, rate := 1, ratetime := 50)
 
 var i;
 if(startlev < endlev)
  for(i := startlev; i <= endlev; i := i + rate)
   SetPersonalLightLevel( who, i );
   sleepms(ratetime);
  endfor
 else
  for(i := startlev; i >= endlev; i := i - rate)
   SetPersonalLightLevel( who, i );
   sleepms(ratetime);
  endfor
 endif	
endfunction