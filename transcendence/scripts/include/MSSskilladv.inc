function getoldskill(who, skill)

var oldrawskill := MSSGetRawSkill(who, skill);
var oldskill := RawSkillToBaseSkill(oldrawskill);
oldskill := oldskill / 10.0;

return oldskill;

endfunction

function getincreasevalue(who, skill, oldskill)

var newrawskill := MSSGetRawSkill(who, skill);
         var newskill := RawSkillToBaseSkill(newrawskill);
         newskill := newskill / 10.0;
        
                                                                                                                                 
         var increasevalue := newskill - oldskill;
return increasevalue;
endfunction
           