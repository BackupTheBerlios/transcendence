function GetQuality(difficulty, skill)

var qual;
var maxlevel := difficulty + 20;
var minlevel := difficulty - 20;

if (minlevel < 0)
 minlevel := 0;
endif

var rawqual := skill - minlevel;

qual := CInt(rawqual * 2.5);

if (qual < 0)
 qual := 0;
elseif (qual > 100)
 qual := 100;
endif

return qual;

endfunction

