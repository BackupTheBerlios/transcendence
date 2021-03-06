/////////////////////////////////////////////////////////////////
//
//   MoreSkillWin Script - Shows the Skill Window for a Player
//
//   Author: Vanyel (Fitzban)
//   eMail : daniele.tieghi@email.it
//
/////////////////////////////////////////////////////////////////

use uo;
use os;
use cfgfile;

/////////////
// Includes
/////////////

//include "include/gumputil";
include "include/moreskillssystem";
include "include/math";

/*
Global layout:={
  "page 0",
  "nodispose",
//  "resizepic 10 10 3500 300 550",
  "resizepic 10 10 1126 300 550",
  "gumppic 130 30 2100"
  */
var layout := {
		"nodispose", 
		"page 0",
		"GUMPPIC  40  40 5154", // Parte centrale del gump, contiene l'immagine 5154 
		"GUMPPIC  40 150 5154", // dimensioni X 170 Y 110                            
		"GUMPPIC  40 260 5154", //                                                   
		"GUMPPIC  40 370 5154", //                                                   
		"GUMPPIC 210  40 5154", //                                                   
		"GUMPPIC 210 150 5154", //                                                   
		"GUMPPIC 210 260 5154", //                                                   
		"GUMPPIC 210 370 5154", //                                                   
		"GUMPPIC   2   2 5150", 	// Angolo superiore sx                                 
		"GUMPPIC   2  40 5153", 	// Bordo sinistro n.1                                 
		"GUMPPIC   2 150 5153", 	// Bordo sinistro n.2                                 
		"GUMPPIC   2 260 5153", 	// Bordo sinistro n.3                              
		"GUMPPIC   2 370 5153", 	// Bordo sinistro n.3                              
		"GUMPPIC   2 480 5176", // Bottone angolo inferiore sx             
		"GUMPPIC  40 480 5157", // Bordo inferiore                                   
		"GUMPPIC 210 480 5157", //                                                   
		"GUMPPIC 380 480 5178", // Angolo inferiore dx                               
		"GUMPPIC 380  40 5155", // Bordo destro n.1                                  
		"GUMPPIC 380 150 5155", // Bordo destro n.2                                  
		"GUMPPIC 380 260 5155", // Bordo destro n.3                                  
		"GUMPPIC 380 370 5155", // Bordo destro n.3                                  
		"GUMPPIC  40   2 5151", // Bordo superiore                                    
		"GUMPPIC 210   2 5151", //                                                    
		"GUMPPIC 380   2 5172", // Angolo superiore dx                                
		"GUMPPIC 185   9 2100", // Scrittina SKILLS      
		"page 1"                            
};


var data:={ };
var pagetitles:={ };
var skillsinfo:={ };
var titles:={ };

const MAX_LINES:=30;

function MoreSkillWin(who, observer)
	set_script_option(SCRIPTOPT_NO_RUNAWAY, 1);

	skillsinfo:=GetGlobalProperty("SkSorted");
	titles:=GetGlobalProperty("SkTitles");

	var index;

		MAX_SKILLS := GetGlobalProperty("Sk_Max_Skills");

		AddSkills(who);

	var result:=SendDialogGump(observer, layout, data)[0];
	if (result[0]>0)
		//SendSysMessage(observer, "Script: " + skillsinfo[result[0]][4]);
		Detach();
		start_script(skillsinfo[result[0]][4], who);
	endif
endfunction


function AddSkills(who)
//	Local pagetitle;
	var skillinfo;
	var titleid;
	var y_pos;
	var index;
	var lines := 0;
	var page := 1;

	for (index:=1; index<=(MAX_SKILLS+1); index:=index+1)
		if (lines==MAX_LINES)
			lines:=0;
			layout.append("button 380 480 5158 5158 0 "+CStr(page+1)+" 0");
			page:=page+1;
			layout.append("page "+page);
			layout.append("button 380   2 5152 5152 0 "+CStr(page-1)+" 0");
		endif

		skillinfo:=skillsinfo[index];
	
		y_pos:=(lines*15)+35;

		if (skillinfo[4])
			layout.append("button 30 "+CStr(y_pos+4)+" 2104 2103 1 0 "+CStr(index));
		endif

		layout.append("text 50 "+CStr(y_pos)+" 0 "+CStr(data.size()));
		data.append(skillinfo[2]);
	
		var titles := GetGlobalProperty("SkTitles");
		titleid:=GetTitleIDSkill(who, skillinfo[3]);
	

		var skillraw := MSSGetRawSkill(who, skillinfo[3]);
		skillraw := RawSkillToBaseSkill(skillraw);
  		var skillrawd := Mod(skillraw, 10);
  		skillraw := skillraw / 10;
  		var skillpoints := CStr(skillraw + "." + skillrawd);
	
		layout.append("text "+GumpTextRight(titles[titleid][1], 200, 122)+" "+CStr(y_pos)+" 0 "+CStr(data.size()));
		data.append(titles[titleid][1]);
		layout.append("text "+GumpTextRight(skillpoints, 250, 122)+" "+CStr(y_pos)+" 0 "+CStr(data.size()));
		data.append(skillpoints);
	
		lines:=lines+1;
	endfor

	return (lines);
endfunction