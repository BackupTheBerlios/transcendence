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
//include "include/moreskillssystem";
include "include/math";
//include "include/attributes";

/*
Global layout:={
  "page 0",
  "nodispose",
//  "resizepic 10 10 3500 300 550",
  "resizepic 10 10 1126 300 550",
  "gumppic 130 30 2100"
  */
var gumpstyle;
 
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
var skillscfg;
var MAX_LINES:=30;
var MAX_SKILLS;
var textcolor;
var frecciasu;
var frecciagiu;
var xpos;
var ypos;
var buttonpos; 
var xdetract;

function NewSkillWin(who, observer)
	set_script_option(SCRIPTOPT_NO_RUNAWAY, 1);
	skillscfg := ReadConfigFile("::skills");
        gumpstyle := GetObjProperty( observer, "SkillWinStyle" );
        xpos := " 50 ";
        buttonpos := " 40 ";
        textcolor := " 0 ";
        frecciasu := struct;
        frecciagiu := struct;
        frecciasu.+grafica := "5152 5152";
        frecciasu.+x := " 380";
        frecciasu.+y := " 2";
        frecciagiu.+grafica := " 5158 5158";
        frecciagiu.+x := " 380";
        frecciagiu.+y := " 480";
        xdetract := 0;
        ypos := 35;

        if (gumpstyle)
        if (gumpstyle == 1)
        
        frecciasu.grafica := " 2705 2705";
        frecciasu.x := " 356";
        frecciasu.y := " 31";
        frecciagiu.grafica := " 2706 2706";
        frecciagiu.x := " 356";
        frecciagiu.y := " 470";
        
        xpos := " 62 ";
        buttonpos := " 45 ";
        textcolor := " 910 ";
        MAX_LINES := 27;
        xdetract := 44;
        ypos := 55;
        
        layout := {
		"nodispose", 
		"page 0",
		"GUMPPIC  40  40 5124", // Parte centrale del gump, contiene l'immagine 5154 
		"GUMPPIC  40 150 5124", // dimensioni X 170 Y 110                            
		"GUMPPIC  40 260 5124", //                                                   
		"GUMPPIC  40 370 5124", //                                                   
		"GUMPPIC 198  40 5124", //                                                   
		"GUMPPIC 198 150 5124", //                                                   
		"GUMPPIC 198 260 5124", //                                                   
		"GUMPPIC 198 370 5124", //                                                   
		"GUMPPIC   30  30 5120", 	// Angolo superiore sx                                 
		"GUMPPIC   30  40 5123", 	// Bordo sinistro n.1                                 
		"GUMPPIC   30 150 5123", 	// Bordo sinistro n.2                                 
		"GUMPPIC   30 260 5123", 	// Bordo sinistro n.3                              
		"GUMPPIC   30 370 5123", 	// Bordo sinistro n.3                              
		"GUMPPIC   30 480 5126", // Bottone angolo inferiore sx             
		"GUMPPIC  40 480 5127", // Bordo inferiore                                   
		"GUMPPIC 198 480 5127", //                                                   
		"GUMPPIC 356 480 5128", // Angolo inferiore dx                               
		"GUMPPIC 356  40 5125", // Bordo destro n.1                                  
		"GUMPPIC 356 150 5125", // Bordo destro n.2                                  
		"GUMPPIC 356 260 5125", // Bordo destro n.3                                  
		"GUMPPIC 356 370 5125", // Bordo destro n.3                                  
		"GUMPPIC  40   30 5121", // Bordo superiore                                    
		"GUMPPIC 198   30 5121", //                                                    
		"GUMPPIC 356   30 5122", // Angolo superiore dx                                
		"GUMPPIC 165   34 2100", // Scrittina SKILLS      
		"CHECKERTRANS 42 57 310 410",
		"page 1"                            
                };
        endif
        endif
	//skillsinfo:=GetGlobalProperty("SkSorted");
	//titles:=GetGlobalProperty("SkTitles");

	var index;

		MAX_SKILLS := 55;

		AddSkills(who);

	var result:=SendDialogGump(observer, layout, data)[0];
	if (result[0]>0)
		//SendSysMessage(observer, "Script: " + skillsinfo[result[0]][4]);
		Detach();
		var scriptname;
		 
		if(skillscfg[result[0]].scriptpath)
	        scriptname := ":" + skillscfg[result[0]].scriptpath + ":" + skillscfg[result[0]].script;
	        else
		scriptname := ":*:" + skillscfg[result[0]].script;
	        endif
	        SendSysMessage(observer, "Script: " + scriptname);
		start_script(scriptname, who);
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

	for (index:=1; index<=(MAX_SKILLS); index:=index+1)
		if (lines==MAX_LINES)
			lines:=0;
			layout.append("button" + frecciagiu.x + frecciagiu.y + frecciagiu.grafica + " 0 "+CStr(page+1)+" 0");
			page:=page+1;
			layout.append("page "+page);
			layout.append("button" + frecciasu.x + frecciasu.y + frecciasu.grafica + " 0 "+CStr(page-1)+" 0");
		endif

		skillinfo:=skillscfg[index];
	
		y_pos:=(lines*15)+ypos;

		if (skillinfo.script)
			layout.append("button" + buttonpos + CStr(y_pos+4)+" 2104 2103 1 0 "+CStr(index));
		endif

		layout.append("text" + xpos + +CStr(y_pos)+ textcolor +CStr(data.size()));
		data.append(skillinfo.name);
	
		//var titles := GetGlobalProperty("SkTitles");
		//titleid:=GetTitleIDSkill(who, skillinfo[3]);
	

		/*var skillraw := MSSGetRawSkill(who, skillinfo[3]);
		skillraw := RawSkillToBaseSkill(skillraw);
  		var skillrawd := Mod(skillraw, 10);
  		skillraw := skillraw / 10;*/
  		var skillpoints := GetEffectiveSkill(who, skillinfo.skillid);
	
		//layout.append("text "+GumpTextRight(cstr(skillinfo.skillid), 200, 122)+" "+CStr(y_pos)+" 0 "+CStr(data.size()));
		//data.append(cstr(skillinfo.skillid));//data.append(titles[titleid][1]);
		layout.append("text "+GumpTextRight(skillpoints, 250 - xdetract, 122)+" "+CStr(y_pos)+ textcolor +CStr(data.size()));
		data.append(cstr(skillpoints));
	        //print(skillinfo.name + " " + cstr(skillinfo.skillid) + " " + cstr(skillpoints) );
		lines:=lines+1;
	endfor

	return (lines);
endfunction