// by ArT-iX

function ShowPlayerOptionsPanel(who, expanded := 0)
 
 var width, height, butt_graph, butt_x, submenu;
 submenu := 0;
 if(expanded == 0)
  width := 90;
  height := 40;
  butt_graph := 0x25e8;
  butt_x := 72;
 else
  width := 150;
  height := 300;
  butt_graph := 0x25e4;
  butt_x := 132;
 endif
 
 var l := 
 {
  "page 0",
  "resizepic 10 50 83 " + cstr(width) + " " + cstr(height),
  "checkertrans 10 50 " + cstr(width) + " " + cstr(height),
  "button " + cstr(butt_x) + " 62 " + cstr(butt_graph) + " " + cstr(butt_graph + 1) + " 1 0 1" , //+ cstr(expanded + 1),
  "text 24 59 1153 0",
  "page 1"
 };
 
 var d :=
 {
  "Options", 
  "Client",
  "Language",
  "Graphics",
  "Settings",
  "T2A",
  "Renaissance",
  "LBR",
  "AOS",
  "Italian",
  "English",
  "Skill Window",
  "Scroll",
  "Transparent"
 };
 
 var d_i := 
  {
  "Opzioni",
  "Client",
  "Lingua",
  "Grafica",
  "Impostazioni",
  "T2A",
  "Renaissance",
  "LBR",
  "AOS",
  "Italiano",
  "Inglese",
  "Finestra Skills",
  "Pergamena",
  "Trasparente"
   };
 
 if(expanded == 1)
 
  l.append("text 24 89 1153 1");
  l.append("button 132 93 9702 9703 0 2 0");
  l.append("text 24 119 1153 2");
  l.append("button 132 123 9702 9703 0 3 0");
  l.append("text 24 149 1153 3");
  l.append("button 132 153 9702 9703 0 4 0");
  l.append("text 24 179 1153 4");
  l.append("button 132 183 9702 9703 0 5 0");
  l.append("page 2");
  l.append("button 112 62 9706 9707 0 1 0");
  l.append("text 24 89 1153 5");
  l.append("button 132 93 9702 9703 1 0 101");
  l.append("text 24 119 1153 6");
  l.append("button 132 123 9702 9703 1 0 102");
  l.append("text 24 149 1153 7");
  l.append("button 132 153 9702 9703 1 0 103");
  l.append("text 24 179 1153 8");
  l.append("button 132 183 9702 9703 1 0 104");
  l.append("page 3");
  l.append("button 112 62 9706 9707 0 1 0");
  l.append("text 24 89 1153 9");
  l.append("button 132 93 9702 9703 1 0 201");
  l.append("text 24 119 1153 10");
  l.append("button 132 123 9702 9703 1 0 202");
  l.append("page 4");
  l.append("button 112 62 9706 9707 0 1 0");
  l.append("text 21 89 90 11");
  l.append("text 24 109 1153 12");
  l.append("button 132 113 9702 9703 1 0 301");
  l.append("text 24 139 1153 13");
  l.append("button 132 143 9702 9703 1 0 302");

 endif
 
 if(GetUserPreferredLanguage(who) == "ENG")
  return SendDialogGump(who, l, d);
 elseif(GetUserPreferredLanguage(who) == "ITA")
  return SendDialogGump(who, l, d_i);
 endif	 
 
endfunction


function ShowPlayerCmdsPanel(who, expanded := 0)
 
 var width, height, butt_graph, butt_x, submenu;
 submenu := 0;
 if(expanded == 0)
  width := 90;
  height := 40;
  butt_graph := 0x25e8;
  butt_x := 72;
 else
  width := 150;
  height := 300;
  butt_graph := 0x25e4;
  butt_x := 132;
 endif
 
 var l := 
 {
  "page 0",
  "resizepic 10 50 83 " + cstr(width) + " " + cstr(height),
  "checkertrans 10 50 " + cstr(width) + " " + cstr(height),
  "button " + cstr(butt_x) + " 62 " + cstr(butt_graph) + " " + cstr(butt_graph + 1) + " 1 0 1" , //+ cstr(expanded + 1),
  "text 24 59 1153 0",
  "page 1"
 };
 
 var d :=
 {
  "Commands", 
  "c",
  "dc",
  "consider",
  "Settings",
  "T2A",
  "Renaissance",
  "LBR",
  "AOS",
  "Italian",
  "English",
  "Skill Window",
  "Scroll",
  "Transparent"
 };
 
 var d_i := 
  {
  "Comandi",
  "c",
  "dc",
  "consider",
  "Impostazioni",
  "T2A",
  "Renaissance",
  "LBR",
  "AOS",
  "Italiano",
  "Inglese",
  "Finestra Skills",
  "Pergamena",
  "Trasparente"
   };
 
 if(expanded == 1)
 /*
  l.append("text 24 89 1153 1");
  l.append("button 132 93 9702 9703 0 2 0");
  l.append("text 24 119 1153 2");
  l.append("button 132 123 9702 9703 0 3 0");
  l.append("text 24 149 1153 3");
  l.append("button 132 153 9702 9703 0 4 0");
  l.append("text 24 179 1153 4");
  l.append("button 132 183 9702 9703 0 5 0");*/
  //l.append("page 2");
  l.append("button 112 62 9706 9707 0 1 0");
  l.append("text 24 89 1153 5");
  l.append("button 132 93 9702 9703 1 0 101");
  l.append("text 24 119 1153 6");
  l.append("button 132 123 9702 9703 1 0 102");
  l.append("text 24 149 1153 7");
  l.append("button 132 153 9702 9703 1 0 103");
  l.append("text 24 179 1153 8");
  l.append("button 132 183 9702 9703 1 0 104");
  l.append("page 3");
  l.append("button 112 62 9706 9707 0 1 0");
  l.append("text 24 89 1153 9");
  l.append("button 132 93 9702 9703 1 0 201");
  l.append("text 24 119 1153 10");
  l.append("button 132 123 9702 9703 1 0 202");
  l.append("page 4");
  l.append("button 112 62 9706 9707 0 1 0");
  l.append("text 21 89 90 11");
  l.append("text 24 109 1153 12");
  l.append("button 132 113 9702 9703 1 0 301");
  l.append("text 24 139 1153 13");
  l.append("button 132 143 9702 9703 1 0 302");

 endif
 
 if(GetUserPreferredLanguage(who) == "ENG")
  return SendDialogGump(who, l, d);
 elseif(GetUserPreferredLanguage(who) == "ITA")
  return SendDialogGump(who, l, d_i);
 endif	 
 
endfunction