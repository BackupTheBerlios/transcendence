//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	More Skills System
//
//	Version: 1.0
//
//	Author: Vanyel (Fitzban)
//
//	email: daniele.tieghi@email.it
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

use uo;
use os;
use cfgfile;
use util;

//include "client";
include "include/attributes";
include "string";
//include "gumputil";

var MAX_NORMAL_SKILL, MAX_MORE_SKILL, MAX_SKILLS;

function UpdateValues()
	MAX_NORMAL_SKILL := GetGlobalProperty("Sk_Max_Normal_Skill");
	MAX_MORE_SKILL   := GetGlobalProperty("Sk_Max_More_Skill");
	MAX_SKILLS		 := GetGlobalProperty("Sk_Max_Skills");
endfunction

function InitMoreSkillsSystem(who:=0)
	syslog("[MSS] Inizializzazione More Skills System");

	var skillid;
	if (!who)
		var skills := GetWholeSkillConfig();
		if (skills)	// Esistono More Skill
		
			for (skillid:=0; skillid<MAX_MORE_SKILL; skillid:=skillid+1)
				SetGlobalProperty("Sk_"+skillid, lower(skills[skillid+1].name));
			endfor

			var skillsinfo:={ };
			var skillsname:=" ";
			var skillsadv:={ };
			var skillunhides:={ };
			var advinfo:={ };
			var advstring;

			var skillname;
			foreach skill in skills
				skillname := lower(skill.name);
			
				// Informazioni riguardo alla skill in SkillsInfo
				if (skill.isA(POLCLASS_NPC))
					if (skill.scriptpath)
						skillsinfo.append({skill.title, skillname, skill.skillid, ":"+skill.scriptpath+":"+skill.script});
					else
						skillsinfo.append({skill.title, skillname, skill.skillid, ":*:"+skill.script});
					endif
				else
					skillsinfo.append({skill.title, skillname, skill.skillid, ""});
				endif

				skillsname := skillsname + skillname + " ";

				if (skill.dexadv)
					advstring:=SplitWords(skill.dexadv);
					advinfo:={CInt(CDbl(advstring[1])*10), CStr(advstring[2])};
				else
					advinfo:={0, ""};
				endif
			
				if (skill.intadv)
					advstring:=SplitWords(skill.intadv);
					advinfo.append(CInt(CDbl(advstring[1])*10));
					advinfo.append(CStr(advstring[2]));
				else
					advinfo.append(0);
					advinfo.append("");
				endif
			
				if (skill.stradv)
					advstring:=SplitWords(skill.stradv);
					advinfo.append(CInt(CDbl(advstring[1])*10));
					advinfo.append(CStr(advstring[2]));
				else
					advinfo.append(0);
					advinfo.append("");
				endif
			
				skillsadv.append(advinfo);

				if (skill.unhides==0)
					skillunhides.append(0);
				else
					skillunhides.append(1);
				endif
			endforeach
			SetGlobalProperty("SkUnSorted", skillsinfo);
			SetGlobalProperty("SkSorted", SortMultiArrayByIndex(skillsinfo, 2));
			SetGlobalProperty("SkName", skillsname);
			SetGlobalProperty("SkAdvance", skillsadv);
			SetGlobalProperty("SkUnhides", skillunhides);

			// Definizione dei Titoli

			var titlesdef:={
				{"(untrained)", 0},	// TitleID = 1
				{"(Novel)", 0},		// TitleID = 2
				{"(Trained)", 0},	// TitleID = 3
				{"(Skilled)", 0},	// TitleID = 4
				{"(Journeyman)", 0},// TitleID = 5
				{"(Expert)", 0},	// TitleID = 6
				{"(Adept)", 0},		// TitleID = 7
				{"(Master)", 0},	// TitleID = 8
				{"(Grandmaster)", 0}// TitleID = 9
			};

			var index;
			for (index:=1; index<=titlesdef.size(); index:=index+1)
				titlesdef[index][2]:=CStr(GumpTextRight(titlesdef[index][1], 170, 122));
			endfor

			SetGlobalProperty("SkTitles", titlesdef);
		
			syslog("[MSS] Inizializzazione portata a termine con successo!");
		else
			syslog("[MSS] Inizializzazione fallita!");
		endif
	else
		UpdateValues();
		var oldskill;
		for (skillid:=MAX_NORMAL_SKILL; skillid<MAX_MORE_SKILL; skillid:=skillid+1)
			oldskill:=GetObjProperty(who, "Sk_"+GetGlobalProperty("Sk_"+skillid));
			if (!((oldskill) || (oldskill==0)))
				SetObjProperty(who, "Sk_"+GetGlobalProperty("Sk_"+skillid), 0);
			endif
		endfor

		if (!who.isa(4))
			SetObjProperty(who, "St_Dexterity", BaseSkillToRawSkill((GetDexterity(who)-GetDexterityMod(who))*10+1));
			SetObjProperty(who, "St_Intelligence", BaseSkillToRawSkill((GetIntelligence(who)-GetIntelligenceMod(who))*10+1));
			SetObjProperty(who, "St_Strength", BaseSkillToRawSkill((GetStrength(who)-GetStrengthMod(who))*10+1));
		endif
	endif
endfunction

function GetWholeSkillConfig()
	var skills:={ };
	var skillid := 0;

	var skillsfile := ReadConfigFile("::skills");
	if (skillsfile)
		while (1)
			if ((skillsfile[skillid]) && (skillid != 55))
				skills.append(skillsfile[skillid]);
				SysLog ("[MSS] Skill ("+SkillID+"): " + SkillsFile[SkillID].name);
			else
				break;
			endif
			skillid := skillid + 1;
		endwhile
		MAX_NORMAL_SKILL := skillid;
		SetGlobalProperty("Sk_Max_Normal_Skill", MAX_NORMAL_SKILL);

		skillsfile := ReadConfigFile(":*:moreskills");
		if (skillsfile)
			while (1)
				if (skillsfile[skillid])
					//skills.append(skillsfile[skillid]);
					SysLog ("[MSS] MoreSkill ("+SkillID+"): " + SkillsFile[SkillID].name);
				else
					break;
				endif
				skillid := skillid + 1;
			endwhile
			MAX_MORE_SKILL 	:= skillid;
			SetGlobalProperty("Sk_Max_More_Skill", MAX_MORE_SKILL);
			MAX_SKILLS 		:= skillid-1;
			SetGlobalProperty("Sk_Max_Skills", MAX_SKILLS);
			syslog("[MSS] MAX_NORMAL_SKILL: " + MAX_NORMAL_SKILL);
			syslog("[MSS] MAX_MORE_SKILL  : " + MAX_MORE_SKILL);
			syslog("[MSS] MAX_SKILLS      : " + MAX_SKILLS);
			return skills;
		else
			print("NO MORESKILLS FILES");
		endif
	endif

	syslog("[MSS] Il file di configurazione delle skill non puo' essere aperto (" + skillsfile + ") !");
	return 0;
endfunction

function GetTitleIDSkill(who, skill)
  var level:=MSSGetSkill(who, skill);
  if (level<30)
    return (1);
  elseif (level<40)
    return (2);
  elseif (level<50)
    return (3);
  elseif (level<60)
    return (4);
  elseif (level<70)
    return (5);
  elseif (level<80)
    return (6);
  elseif (level<90)
    return (7);
  elseif (level<99)
    return (8);
  else
    return (9);
  endif
endfunction

function MSSGetSkill(character, skillid)
	UpdateValues();

  if (skillid<MAX_NORMAL_SKILL)
    return (GetEffectiveSkill(character, skillid));
  elseif (skillid<MAX_MORE_SKILL)
    return (CInt(RawSkillToBaseSkill(GetObjProperty(character,"Sk_"+GetGlobalProperty("Sk_"+skillid)))/10));
  else
    var result:=error;
    result.+errortext:="Invalid parameter";

    return (result);
  endif
endfunction

function MSSGetRawSkill(character, skillid)
	UpdateValues();
  if (skillid<MAX_NORMAL_SKILL)
    return (BaseSkillToRawSkill( GetAttributeBaseValue(character, skillid)));
  elseif (skillid<MAX_MORE_SKILL)
    return (GetObjProperty(character, "Sk_"+GetGlobalProperty("Sk_"+skillid)));
  else
    var result:=error;
    result.+errortext:="Invalid parameter";

    return (result);
  endif
endfunction

function MSSAwardRawPoints(mobile, skillid, rawpoints)
	UpdateValues();
  if (skillid<MAX_NORMAL_SKILL)
    return (AwardRawSkillPoints(mobile, skillid, rawpoints));
  elseif (skillid<MAX_MORE_SKILL)
    var propname:="Sk_"+GetGlobalProperty("Sk_"+skillid);
    SetObjProperty(mobile, propname, GetObjProperty(mobile, propname)+CInt(rawpoints));

    return (1);
  else
    var result:=error;
    result.+errortext:="Invalid parameter";

    return (result);
  endif
endfunction

function MSSCheckSkill(character, skillid, difficulty, points)
	UpdateValues();
	if (skillid<MAX_MORE_SKILL)
		if (skillid<MAX_NORMAL_SKILL)
			set_critical(1);

			var result:=CheckSkill(character, skillid, difficulty, points);
			if (result)
				StatAdvance(character, skillid);
			endif

			set_critical(0);

			return (result);
		else
			if (GetGlobalProperty("SkUnhides")[skillid+1])
				character.hidden:=0;
			endif

			var propname:="Sk_"+GetGlobalProperty("Sk_"+skillid);
			//sendsysmessage(character,"skill: "+propname);

			set_critical(1);

			SetObjProperty(character, "SkRealSkill", skillid);

                        SetAttributeBaseValue(character,MAX_NORMAL_SKILL, RawSkillToBaseSkill(GetObjProperty(character,propname)) );
			var result:=CheckSkill(character, MAX_NORMAL_SKILL, difficulty, points);
			if (result)
				StatAdvance(character, skillid);
			endif
			//SetObjProperty(character, propname, GetRawSkill(character, MAX_NORMAL_SKILL));
                        SetObjProperty(character, propname, BaseSkillToRawSkill( GetAttributeBaseValue(character, MAX_NORMAL_SKILL)));

			//sendsysmessage (character, " "+result+":=CheckSkill(char,"+MAX_NORMAL_SKILL+","+difficulty+","+points+");");
		

			set_critical(0);

			return (result);
		endif
	else
		return (0);
	endif
endfunction

function StatAdvance(character, skillid)
  var skillconf:=GetGlobalProperty("SkAdvance")[skillid+1];
  if (skillconf[1]) // Dexterity
    if (RandomInt(1000)<=skillconf[1])
      MSSAwardRawDex(character, RandomDiceRoll(skillconf[2]));
    endif
  endif
  if (skillconf[3]) // Intelligence
    if (RandomInt(1000)<=skillconf[3])
      MSSAwardRawInt(character, RandomDiceRoll(skillconf[4]));
    endif
  endif
  if (skillconf[5]) // Strength
    if (RandomInt(1000)<=skillconf[5])
      MSSAwardRawStr(character, RandomDiceRoll(skillconf[6]));
    endif
  endif
endfunction


function MSSSetRawSkill(character, skillid, rawskill)
	UpdateValues();
  if (skillid<MAX_NORMAL_SKILL)
    var skillname:="SkOld_"+GetGlobalProperty("Sk_"+skillid);
    if (GetObjProperty(character, skillname))
      SetObjProperty(character, skillname, CInt(rawskill));
    endif

    return (SetRawSkill(character, skillid, rawskill));
  elseif (skillid<MAX_MORE_SKILL)
    SetObjProperty(character, "Sk_"+GetGlobalProperty("Sk_"+skillid), CInt(rawskill));

    return (0);
  else
    var result:=error;
    result.+errortext:="Invalid parameter";

    return (result);
  endif
endfunction


function MSSSetSkill(character, skillid, skill)
  MSSSetRawSkill(character, skillid, BaseSkillToRawSkill(skill*10+1));
endfunction

function MSSSetDex(character, stat)
  if (!character.isa(4))
    SetObjProperty(character, "St_Dexterity", BaseSkillToRawSkill(stat*10+1));
  endif
  SetBaseDexterity(character,stat);
endfunction

function MSSSetInt(character, stat)
  if (!character.isa(4))
    SetObjProperty(character, "St_Intelligence", BaseSkillToRawSkill(stat*10+1));
  endif
  SetBaseIntelligence(character,stat);
endfunction

function MSSSetStr(character, stat)
  if (!character.isa(4))
    SetObjProperty(character, "St_Strength", BaseSkillToRawSkill(stat*10+1));
  endif
  SetBaseStrength(character,stat);
endfunction

function MSSAwardRawDex(who, rawpoints)
  if (!who.isa(4))
    var rawstat:=GetObjProperty(who, "St_Dexterity")+CInt(rawpoints);
    SetObjProperty(who, "St_Dexterity", rawstat);
    SetBaseDexterity(who,RawSkillToBaseSkill(rawstat)/10);
  endif
endfunction

function MSSAwardRawInt(who, rawpoints)
  if (!who.isa(4))
    var rawstat:=GetObjProperty(who, "St_Intelligence")+CInt(rawpoints);
    SetObjProperty(who, "St_Intelligence", rawstat);
    SetBaseIntelligence(who,RawSkillToBaseSkill(rawstat)/10);
  endif
endfunction

function MSSAwardRawStr(who, rawpoints)
  if (!who.isa(4))
    var rawstat:=GetObjProperty(who, "St_Strength")+CInt(rawpoints);
    SetObjProperty(who, "St_Strength", rawstat);
    SetBaseStrength(who,RawSkillToBaseSkill(rawstat)/10);
  endif
endfunction

function GetConfigSkill(skillid)
	UpdateValues();
  var skillsfile;
  if (skillid<MAX_NORMAL_SKILL)
    skillsfile:=ReadConfigFile("::skills");
  elseif (skillid<MAX_MORE_SKILL)
    skillsfile:=ReadConfigFile(":*:skillsmore");
  endif

  if (skillsfile)
    return (skillsfile[skillid]);
  endif

  syslog("Skills: Kann die Skillkonfiguration nicht oeffnen ("+skillid+") !");
  return (0);
endfunction

function GetWholeSkillNames()
	UpdateValues();
  var skillnames:={ };
  var skillid;

  var skillsfile:=ReadConfigFile("::skills");
  if (skillsfile)
    for (skillid:=0; skillid<MAX_NORMAL_SKILL; skillid:=skillid+1)
      skillnames.append(skillsfile[skillid].trainname);
    endfor

    skillsfile:=ReadConfigFile(":*:skillsmore");
    if (skillsfile)
      for (skillid:=MAX_NORMAL_SKILL; skillid<MAX_MORE_SKILL; skillid:=skillid+1)
        skillnames.append(skillsfile[skillid].trainname);
      endfor

      return (skillnames);
    endif
  endif

  syslog("Skills: Kann die Skillkonfiguration nicht oeffnen ("+skillid+") !");
  return (0);
endfunction
