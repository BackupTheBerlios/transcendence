function GetUndeadList()

var list := {

"zombie",
"skeleton",
"bonemage",
"boneknight",
"mummy",
"headless",
"shade",
"headless",
"rotcorpse",
"wraith",
"liche",
"bonewarlock"

};

return list;

endfunction       

function GetInfernalList()   
                           
var list := {              
                           
"daemon",                  
"daemon2",                
"balron",                
"blackgatedaemon",              
"arcanedaemon",                   
"chaosdaemon", 
"fourdaemon",               
"femdaemon",                   
"minordaemoness",                
"hellcat",               
"hellhound",                  
"minordaemon",                   
"minordaemon2",
"imp",
"mongbat",
"vampirebat",              
"firegargoyle"                           
};                         
                           
return list;               
                           
endfunction                

function GetRandomInfernal()                           
                                                     
var list := GetInfernalList();                         
var npctempl := list[RandomInt(list.size() + 1)];                    
return npctempl;                                                     
                                                                     
endfunction                                                          
                
                
                

function GetRandomUndead()
           
var list := GetUndeadList();
var npctempl := list[RandomInt(list.size() + 1)];
return npctempl;
           
endfunction

function ExitFromTomb(master, tomb, npctemplate, realm, depth := 19, rate := 350)

var x, y, facing;

print("TEST!!!" + cstr(tomb.objtype));
var obj := tomb.objtype;
print(cstr(obj));

if(obj == 3799 || obj == 0xed9 || obj == 0xedb)
print("PRIMO TIPO!!!!!!!!!!!!!!");
x := tomb.x + 1;
y := tomb.y;
facing := 2;

elseif(obj == 0xed8 || obj == 0xeda || obj == 0xedc)
print("SECONDO TIPO");
x := tomb.x; 
y := tomb.y + 1;
facing := 4;
endif


var whom := CreateNpcFromTemplate( npctemplate, 5276, 1164, 0, realm);
whom.facing := facing;

whom.frozen := 1;
if(whom)
print( "CREATED!!!!!!!!!!");
endif

MoveCharacterToLocation( whom, x, y, tomb.z - depth, MOVECHAR_FORCELOCATION);
print("TOMB.Z = " + cstr(tomb.z));
print(cstr(whom.z));

var i := 1;
var h;

for (h := whom.z; h < tomb.z; h := h + 1)
MoveCharacterToLocation( whom, x, y, h, MOVECHAR_FORCELOCATION);
sleepms(rate);
endfor 
/*

while(whom.z < tomb.z)

MoveCharacterToLocation( whom, x, y, whom.z + i, MOVECHAR_FORCELOCATION);
print(cstr(whom.z));

; 

if(whom.z < tomb.z)
print("INF");
else
	print("SUP");
endif
sleepms(rate);
endwhile*/
print("exited");
whom.frozen := 0;
return whom;

endfunction
