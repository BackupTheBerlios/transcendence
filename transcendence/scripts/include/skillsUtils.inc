// skills library by ArT-iX
// requires Attributes.inc and cfgfile module

function GetAllSkills(who)
 
 var i;
 var file := ReadConfigFile("::skills");
  if(!file)
  print("ERROR: No skills.cfg found!");
 endif
 var skills := {};
 var skill := struct;
 skill.+id;
 skill.+name;
 skill.+value;
 
 for(i := 0; i <= GetMaxSkill() - 1; i := i + 1)
  skill.id := i;
  skill.name := file[i].name;
  skill.value := GetEffectiveSkill(who, i);
  skills.append(skill);
 endfor
 //print ("MAX SKILL: " + cstr(skills));
 return skills;
 
endfunction

function GetAllSkillsValues(who)

 var file := ReadConfigFile("::skills");
 if(!file)
  print("ERROR: No skills.cfg found!");
 endif
 var skills := {};
 
 
 for(i := 0; i <= GetMaxSkill() - 1; i := i + 1)
  skills.append(GetEffectiveSkill(who, i));
 endfor
 
 return skills;
 
endfunction

function GetMaxSkill()
 var file := ReadConfigFile("::skills");
 var sk_array := GetConfigStringKeys(file);
 return sk_array.size();  
endfunction

function CopyAllSkills(who, towhom)
 
 var i;
 var origskills := GetAllSkills(who);
 print("MAX SKILL: " + cstr(origskills.size()));
 for(i := 1; i <= origskills.size(); i := i + 1)
  SetBaseSkillBaseValue( towhom, i - 1, origskills[i].value * 10 );
 endfor
  

endfunction