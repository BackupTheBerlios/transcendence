// NPC library by ArT-iX
use cfgfile;

function GetNPCDescriptor(npctemplate)

var cfgfile := ReadConfigFile("npcdesc");
var npctemp := cfgfile[npctemplate];

if(!cfgfile)
 print("System Error: GetNPCDescriptor:no npcdesc found!");
 return;
endif

if(!npctemp)
 print("System Error:  GetNPCDescriptor:no npctemplate found!");
 return;
endif

return npctemp;

endfunction

function SetNPCScript(thenpc, script)

thenpc.script := script;
RestartScript(thenpc); 

endfunction

function GetNPCCathegory(npctemplate)

var cfgfile := ReadConfigFile("::npcdesc");
var npctemp := cfgfile[npctemplate];

if(!cfgfile)
 print("System Error: GetNPCDescriptor:no npcdesc found!");
 return;
endif

if(!npctemp)
 print("System Error:  GetNPCDescriptor:no npctemplate found!");
 return;
endif

if(npctemp.Cathegory)
 return npctemp.Cathegory;
else
 return 0;
endif
 
endfunction

function GetNPCSubCathegory(npctemplate)

var cfgfile := ReadConfigFile("::npcdesc");
var npctemp := cfgfile[npctemplate];

if(!cfgfile)
 print("System Error: GetNPCDescriptor:no npcdesc found!");
 return;
endif

if(!npctemp)
 print("System Error:  GetNPCDescriptor:no npctemplate found!");
 return;
endif

if(npctemp.SubCathegory)
 return npctemp.SubCathegory;
else
 return 0;
endif
 
endfunction

function IsFamiliar(npc1, npc2)

var npctemp1, npctemp2;

npctemp1 := npc1.npctemplate;
npctemp1 := npc2.npctemplate;

if(GetNPCSubCathegory(npctemp1) == GetNPCSubCathegory(npctemp2))
 return 1;
else
 return 0;
endif

endfunction

function GetNPCProperty(npctemplate, propertyname)

var cfgfile := ReadConfigFile("::npcdesc");
var npctemp := cfgfile[npctemplate];

if(!cfgfile)
 print("System Error: GetNPCDescriptor:no npcdesc found!");
 return;
endif

if(!npctemp)
 print("System Error:  GetNPCDescriptor:no npctemplate found!");
 return;
endif

var prop := GetConfigString( npctemp, propertyname );

if(!prop)
 return 0;
endif

var i;
var isNumber := 0;

for (i := 0; i <= 9; i := i + 1)
if(prop[1] == cstr(i))
 isNumber := 1;
endif
endfor

if (isNumber == 1)
prop := cint(prop);
endif

return prop;
 
endfunction

function IsHuman(npctemplate)

var cfgfile := ReadConfigFile("::npcdesc");
var npctemp := cfgfile[npctemplate];

if(!cfgfile)
 print("System Error: GetNPCDescriptor:no npcdesc found!");
 return;
endif

if(!npctemp)
 print("System Error:  GetNPCDescriptor:no npctemplate found!");
 return;
endif

if((npctemp.Cathegory == "Human")) 
 return 1;
else
 return 0;
endif
 
endfunction

function IsAnimal(npctemplate)

var cfgfile := ReadConfigFile("::npcdesc");
var npctemp := cfgfile[npctemplate];

if(!cfgfile)
 print("System Error: GetNPCDescriptor:no npcdesc found!");
 return;
endif

if(!npctemp)
 print("System Error:  GetNPCDescriptor:no npctemplate found!");
 return;
endif

if((npctemp.Cathegory == "Animal")) 
 return 1;
else
 return 0;
endif
 
endfunction

function IsMonster(npctemplate)

var cfgfile := ReadConfigFile("::npcdesc");
var npctemp := cfgfile[npctemplate];

if(!cfgfile)
 print("System Error: GetNPCDescriptor:no npcdesc found!");
 return;
endif

if(!npctemp)
 print("System Error:  GetNPCDescriptor:no npctemplate found!");
 return;
endif

if((npctemp.Cathegory == "Monster")) 
 return 1;
else
 return 0;
endif
 
endfunction

function SetNaked(thenpc)
foreach it in ListEquippedItems(thenpc)
 DestroyItem(it); 
endforeach
endfunction

function GetAlignment(thenpc)
 var cfgfile := ReadConfigFile("::npcdesc");
 var npctemp := cfgfile[thenpc.npctemplate];
 return npctemp.alignment;
endfunction


