// ArT-ix 5/5/04

function GetLapHarpNote(note, octave := 0)

var notes := dictionary;

notes["do"] := 977;
notes["do#"] := 980;
notes["re"] := 982;
notes["re#"] := 984;
notes["mi"] := 986;
notes["fa"] := 988;
notes["fa#"] := 990;
notes["sol"] := 992;
notes["sol#"] := 994;
notes["la"] := 971;
notes["la#"] := 973;
notes["si"] := 975;

if(octave > 1)
octave := 1;
endif

return notes[note] + octave;

endfunction

function GetStandHarpNote(note, octave := 0)

var notes := dictionary;

notes["do"] := 1182;
notes["do#"] := 1185;
notes["re"] := 1187;
notes["re#"] := 1189;
notes["mi"] := 1191;
notes["fa"] := 1193;
notes["fa#"] := 1195;
notes["sol"] := 1197;
notes["sol#"] := 1199;
notes["la"] := 1176;
notes["la#"] := 1178;
notes["si"] := 1180;

if(octave > 1)
octave := 1;
endif

return notes[note] + octave;

endfunction

function GetLuteNote(note, octave := 0)

var notes := dictionary;

notes["do"] := 1029;
notes["do#"] := 1032;
notes["re"] := 1034;
notes["re#"] := 1037;
notes["mi"] := 1039;
notes["fa"] := 1041;
notes["fa#"] := 1043;
notes["sol"] := 1045;
notes["sol#"] := 1047;
notes["la"] := 1022;
notes["la#"] := 1024;
notes["si"] := 1026;

if(octave > 1)
octave := 1;
endif

return notes[note] + octave;

endfunction

function GetRandomNote()
 var notes := {"do", "do#", "re", "re#", "mi", "fa", "fa#", "sol", "sol#", "la", "la#", "si"};
 var rand_note := randomint(notes.size() - 1);
 if(rand_note < 1)
  rand_note := 1;
 endif 
 return notes[rand_note];
endfunction

function GetNotesArray()
 var notes := {"do", "do#", "re", "re#", "mi", "fa", "fa#", "sol", "sol#", "la", "la#", "si"};
 return notes;
endfunction

function GetNoteIndex(note)
case(note)
"do": return 1;
"do#": return 2;
"re": return 3;
"re#": return 4;
"mi": return 5;
"fa": return 6;
"sol": return 7;
"sol#": return 8;
"la": return 9;
"la#": return 10;
"si": return 11;
endcase
endfunction
