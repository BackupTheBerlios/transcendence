function checkbottle(who)
   var check := 0;
   var inventario := EnumerateItemsInContainer(who.backpack);
  
   foreach it in inventario
    if (it.objtype == 0x0f0e)
     check := 1;
    return check;
    endif
   endforeach
endfunction




function checkreagent(who, reagent)
   var counter := 0;
   var zaino := EnumerateItemsInContainer(who.backpack);
  
   foreach itr in zaino
     if (itr.objtype == reagent)
      
       counter := counter + 1;
       return counter;
      endif
   endforeach
  
 endfunction

function checkreagentamount(who, reagent, quantity)
var enumer;
var bckpak := EnumerateItemsInContainer(who.backpack);
foreach ita in bckpak
 if (ita.objtype == reagent)
  enumer := ita.amount;
  endif
endforeach
var check;
check := 0;
if (enumer >= quantity)
check := 1;
endif

return check;
endfunction

function reagentconsume(who, reagent, quantity)
var enumer;
var bckpak := EnumerateItemsInContainer(who.backpack);
foreach itc in bckpak
 if (itc.objtype == reagent)
  SubtractAmount(itc, quantity);
  endif
endforeach
endfunction