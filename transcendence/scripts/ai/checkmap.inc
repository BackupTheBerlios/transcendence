function is_grass(critt)

var xcoord := critt.x;
var ycoord := critt.y;
var thepoint := GetMapInfo(xcoord, ycoord, critt.realm);
var info := thepoint.landtile;
if ((info >= 0x0003) && (info <= 0x0007) || (info == 0x007d) || (info == 0x007e) || (info >= 0x00c0) && (info <= 0x00c3) || (info >= 0x00d8) && (info <= 0x00db) || (info >= 0x01a4) && (info <= 0x01a7))
return 1;
else
return 0;
endif
endfunction