function colormob(themob, colore);
var equipagg := ListEquippedItems(themob);
foreach eq in equipagg
 eq.color := colore;
endforeach
themob.color := colore;
endfunction

function dotemporarycolor(themob, colore, tempo);

var equipagg := ListEquippedItems(themob);
var moborigcol := themob.color;
SetObjProperty(themob, "origcol", moborigcol);
themob.color := colore;
foreach eq in equipagg
   SetObjProperty(eq, "orcol", eq.color);
   eq.color := colore;
endforeach
Detach();
sleep(tempo);
var restorcolor := GetObjProperty(themob, "origcol");
themob.color := restorcolor;

foreach eq in equipagg
   var restcol := GetObjProperty(eq, "orcol");
   eq.color := restcol;
endforeach

EraseObjProperty(themob, "origcol");

foreach eq in equipagg
   EraseObjProperty(eq, "orcol");
endforeach

endfunction

function lampeggio(themob, colore, tempo, ripetizione);

var repeatcounter := 0;
repeat
var equipagg := ListEquippedItems(themob);
var moborigcol := themob.color;
SetObjProperty(themob, "origcol", moborigcol);
themob.color := colore;
foreach eq in equipagg
   SetObjProperty(eq, "orcol", eq.color);
   eq.color := colore;
endforeach
Detach();
sleepms(tempo);
var restorcolor := GetObjProperty(themob, "origcol");
themob.color := restorcolor;

foreach eq in equipagg
   var restcol := GetObjProperty(eq, "orcol");
   eq.color := restcol;
endforeach

EraseObjProperty(themob, "origcol");

foreach eq in equipagg
   EraseObjProperty(eq, "orcol");
endforeach
sleepms(tempo);
repeatcounter := repeatcounter + 1;
until repeatcounter == ripetizione;
endfunction


 function sfumature(themob, startcol, endcol,  tempo, ripetizione);
var i;
var repeatcounter := 0;
var moborigcol := themob.color;
SetObjProperty(themob, "origcol", moborigcol);
var equipagg := ListEquippedItems(themob);
foreach eq in equipagg
 
  SetObjProperty(eq, "orcol", eq.color);
endforeach
repeat



if (startcol < endcol)
for (i := startcol; i <= endcol; i := i + 1)
themob.color := i;
foreach eq in equipagg
 
   eq.color := i;
endforeach

sleepms(tempo);
endfor
for (i := endcol; i >= startcol; i := i - 1)
themob.color := i;
foreach eq in equipagg
 
   eq.color := i;
endforeach
Detach();
sleepms(tempo);
endfor
endif


if (startcol > endcol)
for (i := startcol; i >= endcol; i := i - 1)
themob.color := i;
foreach eq in equipagg
 
   eq.color := i;
endforeach
Detach();
sleepms(tempo);
endfor
for (i := endcol; i <= startcol; i := i + 1)
themob.color := i;
foreach eq in equipagg
 
   eq.color := i;
endforeach
Detach();
sleepms(tempo);
endfor
endif

repeatcounter := repeatcounter + 1;
until repeatcounter == ripetizione;


var restorcolor := GetObjProperty(themob, "origcol");
themob.color := restorcolor;

foreach eq in equipagg
   var restcol := GetObjProperty(eq, "orcol");
   eq.color := restcol;
endforeach

EraseObjProperty(themob, "origcol");

foreach eq in equipagg
   EraseObjProperty(eq, "orcol");
endforeach

endfunction



//   SFUMATURE2	



function sfumature2(themob, startcol, range, updown,tempo, ripetizione);
var i;

var repeatcounter := 0;
var moborigcol := themob.color;
SetObjProperty(themob, "origcol", moborigcol);
var equipagg := ListEquippedItems(themob);
foreach eq in equipagg
 
  SetObjProperty(eq, "orcol", eq.color);
  eq.color := startcol;
 
endforeach
repeat
themob.color := startcol;


if (updown == 1)
for (i := 1; i <= range; i := i + 1)
themob.color := themob.color + 1;
foreach eq in equipagg
 
   eq.color := eq.color + 1;
endforeach

sleepms(tempo);
endfor
for (i := 1; i <= range; i := i + 1)
themob.color := themob.color - 1;
foreach eq in equipagg
 
   eq.color := eq.color - 1;
endforeach
//detach();
sleepms(tempo);
endfor
endif


if (updown == 2)
for (i := 1; i <= range; i := i + 1)
themob.color := themob.color - 1;
foreach eq in equipagg
 
   eq.color := eq.color - 1;
endforeach
//detach();
sleepms(tempo);
endfor
for (i := 1; i <= range; i := i + 1)
themob.color := themob.color + 1;
foreach eq in equipagg
 
   eq.color := eq.color + 1;
endforeach
//detach();
sleepms(tempo);
endfor
endif

repeatcounter := repeatcounter + 1;
until repeatcounter == ripetizione;


var restorcolor := GetObjProperty(themob, "origcol");
themob.color := restorcolor;

foreach eq in equipagg
   var restcol := GetObjProperty(eq, "orcol");
   eq.color := restcol;
endforeach

EraseObjProperty(themob, "origcol");

foreach eq in equipagg
   EraseObjProperty(eq, "orcol");
endforeach

endfunction



 // SFUMATURE3 (SFUMA UN RANGE DI COLORI PREDEFINITI IN ARRAY)



 function sfumature3(themob, colorrange, tempo, ripetizione);
var i;

var repeatcounter := 0;
var moborigcol := themob.color;
SetObjProperty(themob, "origcol", moborigcol);
var equipagg := ListEquippedItems(themob);
foreach eq in equipagg
 
  SetObjProperty(eq, "orcol", eq.color);
  eq.color := colorrange[1];
 
endforeach
repeat
themob.color := colorrange[1];



for (i := 1; i <= len(colorrange); i := i + 1)
themob.color := colorrange[i];
foreach eq in equipagg
 
   eq.color := colorrange[i];
endforeach

sleepms(tempo);
endfor




repeatcounter := repeatcounter + 1;
until repeatcounter == ripetizione;


var restorcolor := GetObjProperty(themob, "origcol");
themob.color := restorcolor;

foreach eq in equipagg
   var restcol := GetObjProperty(eq, "orcol");
   eq.color := restcol;
endforeach

EraseObjProperty(themob, "origcol");

foreach eq in equipagg
   EraseObjProperty(eq, "orcol");
endforeach

endfunction

function sfumatureitem( item, colorrange, tempo, ripetizione);
var i;

var repeatcounter := 0;
var origcolor := item.color;
SetObjProperty(item, "origcol", origcolor);


repeat
item.color := colorrange[1];



for (i := 1; i <= len(colorrange); i := i + 1)
item.color := colorrange[i];


sleepms(tempo);
endfor




repeatcounter := repeatcounter + 1;
until repeatcounter == ripetizione;


var restorcolor := GetObjProperty(item, "origcol");
item.color := restorcolor;



EraseObjProperty(item, "origcol");


endfunction
