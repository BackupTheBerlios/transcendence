// Custom House library by ArT-iX 29/12/2003
// requires core modules polsys, cfgfile, datafile



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function SendCustomHouseTool(who, houseserial)
var packet := CreatePacket(0xBF, 17);
packet.setInt16(1, 17);
packet.setInt16(3, 0x20);
packet.setInt32(5, houseserial);
packet.setInt8(9, 4);
packet.setInt16(10, 0);
packet.setInt8(12, 0xFF);
packet.setInt32(13, 0xFF);

packet.sendPacket(who);
print(packet);

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function CloseCustomHouseTool(who, houseserial)
var packet := CreatePacket(0xBF, 17);
packet.setInt16(1, 17);
packet.setInt16(3, 0x20);
packet.setInt32(5, houseserial);
packet.setInt8(9, 5);
packet.setInt16(10, 0);
packet.setInt8(12, 0xFF);
packet.setInt32(13, 0xFF);

packet.sendPacket(who);

//endif
endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function SendRevisionInfo(who, houseserial, revision)

var packet := CreatePacket(0xBF, 13);
packet.setInt16(1, 13);
packet.setInt16(3, 0x1D);
packet.setInt32(5, houseserial);
packet.setInt32(9, revision);


packet.sendPacket(who);
print(packet);

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function SendCustomHouse(who, houseserial, revision, components)

var i, artwork, x, y, z;
var packet := CreatePacket(0xD8, MSGLEN_VARIABLE);

// Prologo

packet.setInt16(1, 0); //Size
packet.setInt8(3, 0); // Compression Type
packet.setInt8(4, 0);
packet.setInt32(5, houseserial);
packet.setInt32(9, revision);
packet.setInt16(13, components.size());
packet.setInt16(15, (components.size() * 5));

//Dati

for (i := 1; i <= components.size(); i := i + 1)

artwork := components[i].art;
x := components[i].x;
y := components[i].y;
z := components[i].z;

if(x < 0)
x := 0xFF + (x + 1);
endif
if(y < 0)
y := 0xFF + (y + 1);
endif
if(x < 0)
z := 0xFF + (z + 1);
endif

packet.setInt16(packet.getSize(), artwork);
packet.setInt8(packet.getSize(), x);
packet.setInt8(packet.getSize(), y);
packet.setInt8(packet.getSize(), z);

endfor

packet.setInt16(1, packet.getSize());

packet.sendPacket(who);
//print(packet);
endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function GetHouseStandardComponents(housegraphic)

var components := {};
var datas;
var comp := struct;
comp.+art ;
comp.+x;
comp.+y;
comp.+z;

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

foreach str in st_components
print("DataString: " + str);
broadcast("DataString: " + str);
datas := splitwords(str);
comp.art := cint(datas[1]);
comp.x := cint(datas[2]);
comp.y := cint(datas[3]);
comp.z := cint(datas[4]);

components.append(comp);

endforeach 

return components;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////



function GetCustomHouseComponents(houseserial)


var dfile := OpenDataFile(":CustomHouseDesignTool:CustomHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif



var components := HouseElement.getProp("Components");


return components;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////



function GetCommittedHouseComponents(houseserial)


var dfile := OpenDataFile(":CustomHouseDesignTool:CommittedHouses");
if(!dfile)

print("Error: no Committed Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif



var components := HouseElement.getProp("Components");


return components;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function GetCustomHouseRevision(houseserial)


var dfile := OpenDataFile("CustomHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif



var revision := HouseElement.getProp("Revision");


return revision;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function DeleteCustomHouseComponent(who, houseserial,  point)

var i;
var itm;
var dfile := OpenDataFile("CustomHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif


var components := HouseElement.getProp("Components");

for(i := 1; i <= len(components); i := i + 1)
itm := components[i];
if((itm.x == point.x) && (itm.y == point.y) && (itm.z == point.z))
components.erase(i);
SendSysMessage(who, "Erased");
endif
endfor

HouseElement.setProp("Components", components);

UnloadDataFile("CustomHouses") ;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function AddCustomHouseComponent(who, houseserial,  comp)

var i, substitution;
var itm;
var dfile := OpenDataFile("CustomHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif


var components := HouseElement.getProp("Components");
substitution := 0;

for(i := 1; i <= len(components); i := i + 1)
itm := components[i];
if((itm.x == comp.x) && (itm.y == comp.y) && (itm.z == comp.z))
sendsysmessage(who, "substitution. OLD ART:" + cstr(components[i].art)+ " NEW ART: " + comp.art);
components[i].art := comp.art;
substitution := 1;
print("substitution");

endif

endfor

if(substitution == 0)
components.append(comp) ;
endif

HouseElement.setProp("Components", components);

UnloadDataFile("CustomHouses") ;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function ClearCustomHouseComponents(who, houseserial)


//var itm;
var dfile := OpenDataFile("CustomHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif


var components := {};





HouseElement.setProp("Components", components);

UnloadDataFile("CustomHouses") ;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function IncreaseCustomHouseRevision (houseserial)

var dfile := OpenDataFile("CustomHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif

var revision := HouseElement.getProp("Revision");

revision := cint(revision) + 1;

HouseElement.setProp("Revision", revision);

UnloadDataFile("CustomHouses") ;

return revision;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function isFirstCustomization (houseserial)

var dfile := OpenDataFile("CustomHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 1;
endif

return 0;

endfunction


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function isCommited(houseserial)

var dfile := OpenDataFile("CustomHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif

var committed := HouseElement.getProp("Committed");

if((!committed) || (committed == 0) )
return 0;
endif

return 1;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


function GetLastCommission(houseserial)

var dfile := OpenDataFile("CustomHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif

var committed := HouseElement.getProp("LastCommitted");

if((!committed) || (committed == 0) )
return 0;
else

return committed;

endif

endfunction


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function GetHouseBaseComponents(housegraphic)

var components := {};
var datas;
var comp := struct;
comp.+art ;
comp.+x;
comp.+y;
comp.+z;

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
if(cint(datas[4]) <= 5)
comp.art := cint(datas[1]);
comp.x := cint(datas[2]);
comp.y := cint(datas[3]);
comp.z := cint(datas[4]);

if(comp.x < minX)
minX := comp.x;
endif

if(comp.x > maxX)
maxX := comp.x;
endif

if(comp.y < minY)
minY := comp.y;
endif

if(comp.y > maxY)
maxY := comp.y;
endif

components.append(comp);
endif
endforeach 
var i,q;
for (i := minX + 1; i <= maxX ; i := i + 1)
for(q := minY + 1; q <= maxY - 1; q := q + 1 )
comp.art := 0x31f4;
comp.x := i;
comp.y := q;
comp.z := 7;
components.append(comp);
endfor
endfor

return components;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function GetLastRevision (houseserial)

var dfile := OpenDataFile(":CustomHouseDesignTool:CustomHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif

var revision := HouseElement.getProp("Revision");



return revision;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function GetLastCommissionRevision (houseserial)

var dfile := OpenDataFile(":CustomHouseDesignTool:CommittedHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif

var revision := HouseElement.getProp("Revision");



return revision;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function GetHouseCustomizerSerial (houseserial)

var dfile := OpenDataFile(":CustomHouseDesignTool:CommittedHouses");
if(!dfile)

print("Error: no Custom Houses Datafile !!");
return;
endif 

var HouseElement := dfile.findElement(houseserial); 

if(!HouseElement)
return 0;
endif

var cust := HouseElement.getProp("Customizer");



return cust;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function GetStairsComponents(stairsGraphic)

if((stairsGraphic < 0x1db0) && (stairsGraphic > 0x1dd7))
print("no stairs");
return;
endif


var components := {};
var datas;
var comp := struct;
comp.+art ;
comp.+x;
comp.+y;
comp.+z;

var multiscfg := ReadConfigFile("::multis");



if(!multiscfg)
Broadcast( "Error: no multis.cfg file!!" );
print("Error: no multis.cfg file!!");
return;
endif 

Broadcast( "multis.cfg found!!" );
print("multis.cfg found!!");

var StairsElement := multiscfg[stairsGraphic];

if(!StairsElement)
broadcast("Error: no multi element:" + cstr(stairsgraphic));
print("Error: no multi element:" + cstr(stairsgraphic));
return;
endif 

broadcast("multi element:" + cstr(stairsgraphic));
print("multi element:" + cstr(stairsgraphic));

var st_components := GetConfigStringArray( StairsElement, "static" );

if(!st_components)
broadcast("Error: no static elements" );
print("Error: no static elements" );
return;
endif 

broadcast(" static elements" );
print("no static elements" );

foreach str in st_components
print("DataString: " + str);
broadcast("DataString: " + str);
datas := splitwords(str);
comp.art := cint(datas[1]);
comp.x := cint(datas[2]);
comp.y := cint(datas[3]);
comp.z := cint(datas[4]);

components.append(comp);

endforeach 

return components;

endfunction


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

function AdaptStairsPosition(StairsID, X, Y, Z )

var StairsComps := GetStairsComponents(StairsID);

if(X > 240)
X := 0 - (256 - X);
endif

if(Y > 240)
Y := 0 - (256 - Y);
endif

var fixedComps := {};

foreach comp in StairsComps

comp.x := comp.x + X;
comp.y := comp.y + Y;
comp.z := comp.z + Z;

fixedComps.append(comp);

endforeach

return fixedComps;

endfunction

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

function GetHouseDimensions(housegraphic)


var datas;
var comp := struct;

comp.+x;
comp.+y;
comp.+z;

var multiscfg := ReadConfigFile("::multis");

if(!multiscfg)
Broadcast( "Error: no multis.cfg file!!" );
print("Error: no multis.cfg file!!");
return;
endif 



var HouseElement := multiscfg[housegraphic];

if(!HouseElement)
broadcast("Error: no multi element:" + cstr(housegraphic));
print("Error: no multi element:" + cstr(housegraphic));
return;
endif 



var st_components := GetConfigStringArray( HouseElement, "static" );

if(!st_components)
broadcast("Error: no static elements" );
print("Error: no static elements" );
return;
endif 


var minX, maxX, minY, maxY, maxZ;

minX := 0;
maxX := 0;
minY := 0;
maxY := 0;
maxZ := 0;

foreach str in st_components

datas := splitwords(str);

comp.x := cint(datas[2]);
comp.y := cint(datas[3]);
comp.z := cint(datas[4]);


if(comp.x < minX)
minX := comp.x;
endif

if(comp.x > maxX)
maxX := comp.x;
endif

if(comp.y < minY)
minY := comp.y;
endif

if(comp.y > maxY)
maxY := comp.y;
endif

if(comp.z > maxZ)
maxZ := comp.z;
endif

endforeach 

var XLength := maxX - minX;
var YLength := maxY - minY;

var Dims := struct;

Dims.+right := maxX;
Dims.+bottom := maxY;
Dims.+left := minX;
Dims.+top := minY;
Dims.+width := XLength;
Dims.+heigth := YLength;
Dims.+Zheigth := maxZ;

return Dims;

endfunction