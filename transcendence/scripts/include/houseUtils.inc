const dirtTile := 0x31f4;


function getHouseBounds(HouseGraphic)

//var components := {};
var datas;


var multiscfg := ReadConfigFile("::multis");

if(!multiscfg)
Broadcast( "Error: no multis.cfg file!!" );
print("Error: no multis.cfg file!!");
return;
endif 
Broadcast( "multis.cfg found!!" );
print("multis.cfg found!!");

var HouseElement := multiscfg[housegraphic];

if(!HouseElement)
broadcast("Error: no multi element:" + cstr(housegraphic));
print("Error: no multi element:" + cstr(housegraphic));
return;
endif 
broadcast("multi element:" + cstr(housegraphic));
print("multi element:" + cstr(housegraphic));

var st_components := GetConfigStringArray( HouseElement, "static" );

if(!st_components)
broadcast("Error: no static elements" );
print("Error: no static elements" );
return;
endif 
broadcast(" static elements" );
print("no static elements" );

var minX, maxX, minY, maxY;
minX := 0;
maxX := 0;
minY := 0;
maxY := 0;

foreach str in st_components
//print("DataString: " + str);
//broadcast("DataString: " + str);
datas := splitwords(str);
//comp.art := cint(datas[1]);
x := cint(datas[2]);
y := cint(datas[3]);
//comp.z := cint(datas[4]);
if(x < minX)
minX := x;
endif

if(x > maxX)
maxX := x;
endif

if(y < minY)
minY := y;
endif

if(y > maxY)
maxY := y;
endif


endforeach

var xLength := maxX - minX;
var yLength := maxY - minY;

var dims := struct;
dims.+maxX := maxX;
dims.+maxY := maxY;
dims.+minX := minX;
dims.+minY := minY;
dims.+xLength := xLength;
dims.+yLength := yLength;

return dims;
endfunction