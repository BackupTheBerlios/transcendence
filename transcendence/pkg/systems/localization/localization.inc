use cfgfile;

const NO_OVERRIDE := 0x10000;

const CWORDS := {};

function GetUserPreferredLanguage(user)

  var lang := GetObjProperty(user, "lang");
  if(lang)
  return lang;
  else
  return 0;
  endif	

endfunction

function SendLocalizedSysMessage(who, MsgID, lang, CustomWords := CWORDS, Override_Color := NO_OVERRIDE, Override_Font := NO_OVERRIDE)

  var color, font, msgtext, numCwords, i, lang_index;
  var file := ReadConfigFile(":Localization:messages");
  
  if(!file)
   SendSysMessage(who, "System Error: no messages config file. Contact Staff!");
   return;
  endif 
  
  if(!file[MsgID])
   SendSysMessage(who, "System Error: wrong message ID. Contact Staff!");
   return;
  endif
  
  if (Override_Color == NO_OVERRIDE)
   color := file[MsgID].Color;
  else
   color := Override_Color;
  endif
  
  if (Override_Font == NO_OVERRIDE)
   font := file[MsgID].Font;
  else
   font := Override_Font;
  endif
  
  if (lang == "ENG")
   msgtext := GetConfigString( file[MsgID], "Eng" );
   numCwords := file[MsgID].CWordsEng;
   lang_index := 1;
  elseif (lang == "ITA")
   msgtext := GetConfigString( file[MsgID], "Ita" );
   numCwords := file[MsgID].CWordsIta;
   lang_index := 2;
  else
   SendSysMessage(who, "Error getting localized language! Please Contact Staff");
  endif 
  
  if(numCwords)
  for(i := 1; i <= numCwords; i := i + 1)
   msgtext["~" + cstr(i)] := CustomWords[lang_index][i];
  endfor
  endif
   
  SendSysMessage( who, msgtext, font , color);

endfunction

function PrintLocalizedTextAbove( who, MsgID, lang, CustomWords := CWORDS, Override_Color := NO_OVERRIDE, Override_Font := NO_OVERRIDE)

  var color, font, msgtext, numCwords, i, lang_index;
  var file := ReadConfigFile(":Localization:messages");
  
  if(!file)
   SendSysMessage(who, "System Error: no messages config file. Contact Staff!");
   return;
  endif 
  
  if(!file[MsgID])
   SendSysMessage(who, "System Error: wrong message ID. Contact Staff!");
   return;
  endif
  
  if (Override_Color == NO_OVERRIDE)
   color := file[MsgID].Color;
  else
   color := Override_Color;
  endif
  
  if (Override_Font == NO_OVERRIDE)
   font := file[MsgID].Font;
  else
   font := Override_Font;
  endif
  
  foreach player in ListMobilesNearLocation( who.x, who.y, who.z, 10 )
  
  if (lang == "ENG")
   msgtext := GetConfigString( file[MsgID], "Eng" );
   numCwords := file[MsgID].CWordsEng;
   lang_index := 1;
  elseif (lang == "ITA")
   msgtext := GetConfigString( file[MsgID], "Ita" );
   numCwords := file[MsgID].CWordsIta;
   lang_index := 2;
  else
   SendSysMessage(who, "Error getting localized language! Please Contact Staff");
  endif 
  
  if(numCwords)
  for(i := 1; i <= numCwords; i := i + 1)
   msgtext["~" + cstr(i)] := CustomWords[lang_index][i];
  endfor
  endif
   
  PrintTextAbovePrivate( who, msgtext, player, font, color  );
  
  endforeach

endfunction

function PrintAutoLocalizedTextAbove( who, MsgID,  CustomWords := CWORDS, Override_Color := NO_OVERRIDE, Override_Font := NO_OVERRIDE)

  var color, font, msgtextEng, msgtextEng, numCwordsEng, numCwordsIta, i;
  var file := ReadConfigFile(":Localization:messages");
  
  if(!file)
   SendSysMessage(who, "System Error: no messages config file. Contact Staff!");
   return;
  endif 
  
  if(!file[MsgID])
   SendSysMessage(who, "System Error: wrong message ID. Contact Staff!");
   return;
  endif
  
  if (Override_Color == NO_OVERRIDE)
   color := file[MsgID].Color;
  else
   color := Override_Color;
  endif
  
  if (Override_Font == NO_OVERRIDE)
   font := file[MsgID].Font;
  else
   font := Override_Font;
  endif
  
  msgtextEng := GetConfigString( file[MsgID], "Eng" );
  numCwordsEng := file[MsgID].CWordsEng;
  msgtextIta := GetConfigString( file[MsgID], "Ita" );
  numCwordsIta := file[MsgID].CWordsIta;
  
  if(numCwordsEng)
  for(i := 1; i <= numCwordsEng; i := i + 1)
   msgtextEng["~" + cstr(i)] := CustomWords[1][i];
  endfor
  endif
  
  if(numCwordsIta)
  for(i := 1; i <= numCwordsIta; i := i + 1)
   msgtextIta["~" + cstr(i)] := CustomWords[2][i];
  endfor
  endif
  
  foreach player in ListMobilesNearLocation( who.x, who.y, who.z, 10 )
  
         if(GetUserPreferredLanguage(player) == "ENG") PrintTextAbovePrivate( who, 
         msgtextEng, player, font, color  ); 
         elseif(GetUserPreferredLanguage(player) == "ITA") PrintTextAbovePrivate( 
         who, msgtextIta, player, font, color  ); endif
   
  endforeach

endfunction

function PrintLocalizedTextAbovePrivate( who, towhom,  MsgID, lang, CustomWords := CWORDS, Override_Color := NO_OVERRIDE, Override_Font := NO_OVERRIDE)

  var color, font, msgtext, numCwords, i, lang_index;
  var file := ReadConfigFile(":Localization:messages");
  
  if(!file)
   SendSysMessage(who, "System Error: no messages config file. Contact Staff!");
   return;
  endif 
  
  if(!file[MsgID])
   SendSysMessage(who, "System Error: wrong message ID. Contact Staff!");
   return;
  endif
  
  if (Override_Color == NO_OVERRIDE)
   color := file[MsgID].Color;
  else
   color := Override_Color;
  endif
  
  if (Override_Font == NO_OVERRIDE)
   font := file[MsgID].Font;
  else
   font := Override_Font;
  endif
  
  
  
  if (lang == "ENG")
   msgtext := GetConfigString( file[MsgID], "Eng" );
   numCwords := file[MsgID].CWordsEng;
   lang_index := 1;
  elseif (lang == "ITA")
   msgtext := GetConfigString( file[MsgID], "Ita" );
   numCwords := file[MsgID].CWordsIta;
   lang_index := 2;
  else
   SendSysMessage(who, "Error getting localized language! Please Contact Staff");
  endif 
  
  if(numCwords)
  for(i := 1; i <= numCwords; i := i + 1)
   msgtext["~" + cstr(i)] := CustomWords[lang_index][i];
  endfor
  endif
   
  PrintTextAbovePrivate( who, msgtext, towhom, font, color  );

endfunction


function GetLocalizedMessageText(MsgID, lang, CustomWords := {})

  var msgtext, numCwords, i, lang_index;
  var file := ReadConfigFile(":Localization:messages");
  
  if(!file)
   SendSysMessage(who, "System Error: no messages config file. Contact Staff!");
   return;
  endif 
  
  if(!file[MsgID])
   SendSysMessage(who, "System Error: wrong message ID. Contact Staff!");
   return;
  endif
  
  if (lang == "ENG")
   msgtext := GetConfigString( file[MsgID], "Eng" );
   numCwords := file[MsgID].CWordsEng;
   lang_index := 1;
  elseif (lang == "ITA")
   msgtext := GetConfigString( file[MsgID], "Ita" );
   numCwords := file[MsgID].CWordsIta;
   lang_index := 2;
  else
   SendSysMessage(who, "Error getting localized language! Please Contact Staff");
  endif 
  
  if(numCwords)
  for(i := 1; i <= numCwords; i := i + 1)
   msgtext["~" + cstr(i)] := CustomWords[lang_index][i];
  endfor
  endif
  
  return msgtext;

endfunction

function PrintCustomTextAboveByLanguage( who, ENGText, ITAText, Color := 0, Font := 3)

 
  
  foreach player in ListMobilesNearLocation( who.x, who.y, who.z, 10 )
  
  if (GetUserPreferredLanguage(player) == "ENG")
   PrintTextAbovePrivate( who, ENGText, player, Font, Color  );
  elseif (GetUserPreferredLanguage(player) == "ITA")
   PrintTextAbovePrivate( who, ITAText, player, Font, Color  );

  endif 
  endforeach

endfunction

function PrintCustomTextAboveByLanguagePriv( who, towhom, lang, ENGText, ITAText, Color := 0, Font := 3)

  if (lang == "ENG")
   PrintTextAbovePrivate( who, ENGText, towhom, Font, Color  );
  elseif (lang == "ITA")
   PrintTextAbovePrivate( who, ITAText, towhom, Font, Color  );

  endif 
 
endfunction

function SendCustomSysMessageByLanguage( who,  lang, ENGText, ITAText, Color := 0, Font := 3)

  if (lang == "ENG")
   SendSysMessage( who, ENGText, Font, Color  );
  elseif (lang == "ITA")
   SendSysMessage( who, ITAText, Font, Color  );

  endif 
 

endfunction

function BroadCastCustomMsgByLang( ENGText, ITAText, Color := 0, Font := 3, realm := "all")

var msg;

foreach char in EnumerateOnlineCharacters() 
 if(GetUserPreferredLanguage(char) == "ENG")
   msg := ENGText;
 elseif(GetUserPreferredLanguage(char) == "ITA")
   msg := ITAText;
 endif

 if((realm == "all") || (realm == char.realm))
 
   SendSysMessage( char, msg, Font, Color  );

 endif
endforeach 

endfunction


function GetLocalizedNPCName(npc, langPropName)

var npcdesc := readconfigfile("::npcdesc");


if (!npcdesc)
print("NPCDESC non trovato!!");
return 0;
endif

if (!npcdesc[npc.npctemplate])
print("npctemplate non trovato!!");
return 0;
endif


var LocalizedName := GetConfigString( npcdesc[npc.npctemplate], langPropName );
var nome := npc.name;
if(LocalizedName)
 if (LocalizedName["<random>"])
  //print("RANDOM");
  var nomeproprio := splitwords(nome);
  LocalizedName["<random>"] := nomeproprio[1];
  //print(nomeproprio[1]);
 endif 
 return LocalizedName;
else
 return nome;
endif 	

endfunction

function SendLocalizedDialogGump(who, lang, layout, ENGText, ITAText, byref variable )
 var data;
 if(lang == "ENG")
  data := ENGText;
 elseif(lang == "ITA")
  data := ITAText;
 endif
 
 variable :=  SendDialogGump(who, layout, data);
 
endfunction