


function countitemsinbackpack(who, oggetto)


var counter := 0;
var zaino := EnumerateItemsInContainer(who.backpack);
foreach it in zaino
if (it.objtype == oggetto)
counter := counter + 1;
endif
endforeach


return counter;
endfunction
