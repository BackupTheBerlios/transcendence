

function magicwords (who, mwords)

var checkwords;
var checkfrase :=requestinput (who, who.backpack, "Write the Magic Words for this potion :");
PrintTextAbove (who, checkfrase, FONT_NORMAL, 0x005a);
if (checkfrase == mwords)
checkwords := 1;
else
checkwords := 0;
endif

return checkwords;

endfunction



                  