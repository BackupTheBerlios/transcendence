function CheckForSpell3DEffects(cfgfile, thecaster, caston, spellid, fx2d := 0)
var Fx3DType := cfgfile[spellid].Fx3DType;
if(!Fx3DType)
return;
endif
var Fx3D := cfgfile[spellid].Fx3DID;
//var Fx3DCast := cfgfile[spellid].Fx3DCast;

/*if(Fx3DCast)
ParticleOnCharEffect(thecaster, Fx3DCast, 1 , 0, 0);
endif*/

if(Fx3DType == "OnChar")
ParticleOnCharEffect(caston, Fx3D, 1 , 0, 0);
elseif (Fx3DType == "Moving")
ParticleMovingEffect(thecaster, caston, fx2d,  Fx3D, 0, 5044,10, 0, 0,  0);
endif

endfunction

function Cast3DEffect(cfgfile, thecaster, spellid)
//var Fx3D := cfgfile[spellid].Fx3DID;
var Fx3DCast := cfgfile[spellid].Fx3DCast;

if(Fx3DCast)
ParticleOnCharEffect(thecaster, Fx3DCast, 1 , 0, 0);
endif

endfunction
