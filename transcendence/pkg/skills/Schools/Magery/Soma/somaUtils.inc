function CopyCharacterAlignment(who, char)
 if(char.npctemplate)
  if(GetAlignment(char) == "evil")
   who.murderer := 1;
  endif
 else
  if(char.criminal)
   who.setcriminal(char.criminal);
  endif
  if(char.murderer)
   who.murderer := 1;
  endif
 endif	
endfunction