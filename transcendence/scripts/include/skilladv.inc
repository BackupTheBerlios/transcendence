include "include/attributes";
function getoldskill(who, skill)

var oldrawskill := BaseSkillToRawSkill( GetAttributeBaseValue(who, skill) );
var oldskill := RawSkillToBaseSkill(oldrawskill);
oldskill := oldskill / 10.0;

return oldskill;

endfunction

function getincreasevalue(who, skill, oldskill)

var newrawskill := BaseSkillToRawSkill( GetAttributeBaseValue(who, skill) );
         var newskill := RawSkillToBaseSkill(newrawskill);
         newskill := newskill / 10.0;
        
                                                                                                                                 
         var increasevalue := newskill - oldskill;
return increasevalue;
endfunction
           
