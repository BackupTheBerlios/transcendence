use uo;
use os;
use util;
use math;
use cfgfile;

include "include/eventID";
include "include/myUtil";
include "include/attributes";
include "../../pkg/systems/combat/equip";

program onlogon(who)
  TrackIP(who);
  RestoreMods(who);
  SetObjProperty(who,"logontime",ReadGameClock());
  EraseObjProperty(who, "IsMeditating");
  SetObjProperty(who,"LoggedIn", 1);
  start_script(":meditation:medCheck", who);
  start_script(":hooks:attributeCore", who);
  if(who.cmdlevel < 2)
    RevokePrivilege(who, "hearghosts");
  else
    var oldpack := who.backpack;
    if(oldpack.objtype != 0x966c)
      MoveItemToLocation(oldpack, 5851, 1161, 0, MOVEITEM_FORCELOCATION);
      var newpack := CreateItemAtLocation(5851, 1162, 0, 0x966c, 1);
      EquipItem(who, newpack);
      foreach thing in ListRootItemsInContainer(oldpack)
        MoveItemToContainer(thing, newpack);
      endforeach
    endif
  endif
  var mount := GetEquipmentByLayer(who, 25 );
  if(mount)
    var animal := SystemFindObjectBySerial(CInt(GetObjProperty(mount,"serial")));
    if(animal)
      EraseObjProperty(animal,"onhold");
    else
      DestroyItem(mount);
    endif
  endif
  var rm := GetObjProperty(who, "ReportMenu");
  if(rm)
    var defender;
    var rept := {};
    foreach serial in rm
      foreach chr in EnumerateOnlineCharacters()
        if(chr.serial == serial)
          defender := chr;
          break;
        endif
      endforeach
      if(!defender)
        defender := SystemFindObjectBySerial(serial, SYSFIND_SEARCH_OFFLINE_MOBILES);
      endif
      rept.append(defender);
      defender := 0;
    endforeach
    SendReportGump(who, rept);
    EraseObjProperty(who, "LoginNotify");
    EraseObjProperty(who, "ReportMenu");
  endif
  var lr := GetObjProperty(who, "LoginReport");
  if(lr)
    var reportdata := {};
    var jerk;
    foreach serial in lr
      jerk := SystemFindObjectBySerial(serial, SYSFIND_SEARCH_OFFLINE_MOBILES);
      if(jerk)
        reportdata.append(jerk);
      endif
    endforeach
    EraseObjProperty(who, "LoginReport");
  endif
  var nkarma := CStr(GetObjProperty(who, "ModKarma"));
  var nfame := CStr(GetObjProperty(who, "ModFame"));
  if(nfame)
    var ofame := GetObjProperty(who, "Fame");
    SendGainMessage(who, "Fame", CInt(nfame));
    SetObjProperty(who, "Fame", CInt(ofame) + CInt(nfame));
    EraseObjProperty(who, "ModFame");
    var karma   := CInt(GetObjProperty(who, "Karma"));
    var fame    := CInt(GetObjProperty(who, "Fame"));
    SetNotoTitle(who, karma, fame);
  endif
  if(nkarma)
    var okarma := GetObjProperty(who, "Karma");
    SendGainMessage(who, "Karma", CInt(nkarma));
    SetObjProperty(who, "Karma", CInt(okarma) + CInt(nkarma));
    EraseObjProperty(who, "ModKarma");
    var karma   := CInt(GetObjProperty(who, "Karma"));
    var fame    := CInt(GetObjProperty(who, "Fame"));
    SetNotoTitle(who, karma, fame);
  endif
  var whopack := who.backpack;
  if(!GetObjProperty(whopack, "Owner"))
    SetObjProperty(whopack, "Owner", who.serial);
  endif
  SetObjProperty(who, "LastLog", ReadGameClock() );
  if(GetObjProperty(who,"poly"))
    Detach();
    sleep(15);
    who.graphic := who.objtype;
    who.color := who.truecolor;
    EraseObjProperty(who,"poly");
  endif
  var mailkeeper := GetObjProperty(who,"mailkeeper");
  if(!mailkeeper)
    start_script(":gmtools:mailkeeper", who);
    mailkeeper := 1;
    SetObjProperty(who,"mailkeeper", 1);
  endif
  if(mailkeeper >= 60)
    mailkeeper := 1;
    SetObjProperty(who,"mailkeeper", mailkeeper);
    Detach();
    start_script(":gmtools:mailkeeper", who);
  else
    mailkeeper := mailkeeper + 1;
    SetObjProperty(who,"mailkeeper", mailkeeper);
  endif
  foreach thing in ListEquippedItems(who)
    if(Cint(GetObjProperty(thing, "#equipped")) != who.serial)
      HandleMods(who, thing);
    endif
  endforeach
  staffnotify(who);
endprogram

function TrackIP(who)
  var acct := who.acct;
  var ipstring := acct.getprop("LastIP");
  if(!ipstring)
    ipstring := {};
  endif
  var holder := {};
  var amt := len(ipstring);
  foreach thing in ipstring
    if((thing[1] != who.ip) and (amt < 20));
      holder.append(thing);
    else
      amt := amt - 1;
    endif
  endforeach
  ipstring := holder;
  var newarray := {};
  newarray.append(who.ip);
  newarray.append(who.name);
  ipstring.append(newarray);
  acct.setprop("LastIP", ipstring);
  acct.setprop("LastLogin", ReadGameClock());
endfunction

function staffnotify(who)
  var pid := GetGlobalProperty("#stafflist");;
  if (!pid)
    syslog( "Stafflist not initialized!" );
    return;
  endif
  var process := getprocess(pid);
  if(!process)
    syslog( "Can't find process for stafflist, pid=" + pid );
    return;
  endif
  var k := struct;
  if(who.cmdlevel < 2)
    k.+player := who;
    k.+type  := EVID_PLAYER_LOGIN;
    process.sendevent(k);
  else
    k.+player := who;
    k.+type   := EVID_STAFF_LOGIN;
    process.sendevent(k);
  endif
endfunction

const LONG_COUNT_DECAY_TIME := 144000; //40 hours
const SHORT_COUNT_DECAY_TIME := 28800; //8 hours

var layout := {
"page 0",
"nodispose",
"noclose",
"gumppic 0 0 206",
"gumppic 43 0 201",
"gumppic 460 0 207",
"gumppic 0 43 202",
"gumppic 43 43 200",
"gumppic 170 43 200",
"gumppic 295 43 200",
"gumppic 335 43 200",
"gumppic 43 170 200",
"gumppic 170 170 200",
"gumppic 295 170 200",
"gumppic 335 170 200",
"gumppic 43 220 200",
"gumppic 170 220 200",
"gumppic 295 220 200",
"gumppic 335 220 200",
"gumppic 460 43 203",
"gumppic 0 340 204",
"gumppic 43 340 233",
"gumppic 460 340 205",
"button 380 345 249 248 1 0 99",
"text 50 20 40 0",
"text 50 50 40 1",
"text 50 70 40 2"
};

var data := {
"Now is the time for retribution!",
"Check zero or more players to report for your murder",
"and press OKAY."
};


function SendReportGump(who, reportables)
  FillInArrays(reportables);
  var ret := SendDialogGump(who,layout,data);
  if(!ret)
    var reportdata := {};
    foreach reportable in(reportables)
	  reportdata.append(reportable.serial);
    endforeach
    SetObjProperty(who, "LoginReport", reportdata);
    return;
  endif
  foreach id in (ret.keys)
	if(id >= 10)
	  id := id-9;
	  var mob := reportables[id];
	  if(!(mob in EnumerateOnlineCharacters()))
	    SetObjProperty(mob, "LoginNotify", who.serial);
	  else
	    AdjustNoto(mob, who);
	  endif
	  AdjustMurderCounts(who, mob);
	endif
  endforeach
  foreach reportable in(who.reportables)
	who.removeReportable(reportable.serial, reportable.gameclock);
  endforeach
endfunction

function FillInArrays(reportables)
  var prev_y := 80;
  var prev_x := 40;
  var buttonret := 10;
  layout.append("page 1");
  foreach reportable in reportables
    if(!reportable.cmdlevel)
	  if(buttonret==21)
	    prev_x := 300;
	    prev_y := 80;
	  endif
	  layout.append("checkbox " + CStr(prev_x) + " " + CStr(prev_y+20) + " 210 211 0 " + buttonret);
	  data.append(reportable.name);
	  layout.append("text " + CStr(prev_x+20) + " " + CStr(prev_y+20) + " 40 " + CStr(len(data)-1));
	  prev_y := prev_y+20;
	  buttonret := buttonret+1;
    endif
  endforeach
endfunction

function AdjustMurderCounts(who, killer)
  var onlinetime := GetObjProperty(killer,"onlinetimer");
  var longcount := GetObjProperty(killer,"longmurders");
  if(!longcount)
	longcount := 0;
  endif
  longcount := longcount + 1;
  if(longcount > 4)
	killer.setMurderer(1);
	SendSysMessage(killer,"You are now known as a murderer!");
  endif
  var shortcount := GetObjProperty(killer, "shortmurders");
  if(!shortcount)
	shortcount := 0;
  endif
  shortcount := shortcount + 1;
  SetObjProperty(killer, "longmurders", longcount);
  SetObjProperty(killer, "shortmurders", shortcount);
  SetObjProperty(killer, "decaylongcountat", onlinetime + LONG_COUNT_DECAY_TIME);
  SetObjProperty(killer, "decayshortcountat", onlinetime + SHORT_COUNT_DECAY_TIME);
endfunction

var nototitles :=
{
    {"Outcast",     "Wretched",     "Nefarious", "Dread",         "Dread"},
    {"Despicable",  "Dastardly",    "Wicked",    "Evil",          "Evil"},
    {"Scoundrel",   "Malicious",    "Vile",      "Villainous",    "Dark"},
    {"Unsavory",    "Dishonorable", "Ignoble",   "Sinister",      "Sinister"},
    {"Rude",        "Disreputable", "Notorious", "Infamous",      "Dishonored"},
    {"None",        "Notable",      "Prominent", "Renowned",     ""},
    {"Fair",        "Upstanding",   "Reputable", "Distinguished", "Distinguished"},
    {"Kind",        "Respectable",  "Proper",    "Eminent",       "Eminent"},
    {"Good",        "Honorable",    "Admirable", "Noble",         "Noble"},
    {"Honest",      "Commendable",  "Famed",     "Illustrious",   "Illustrious"},
    {"Trustworthy", "Estimable",    "Great",     "Glorious",      "Glorious"}
};

function AdjustNoto(attacker, defender)
  if(attacker.isA(POLCLASS_NPC))
    return;
  endif
  var fame      := CInt(GetObjProperty(attacker, "Fame"));
  var karma   := CInt(GetObjProperty(attacker, "Karma"));
  var dkarma  := CInt(GetObjProperty(defender, "Karma"));
  var dkchk;
  dkarma := dkarma / 100.0;
  dkchk := dkarma * 10;
  var kmod      := GetKarmaLevel(karma);
  var dkmod     := GetKarmaLevel(dkchk);
  var karmagain := (0 - dkarma);
  if(kmod == dkmod)
    karmagain := karmagain / 2;
  elseif(kmod > dkmod)
    karmagain := 0;
  endif
  if(defender.isA(POLCLASS_MOBILE))
    karmagain := karmagain / 100;
  endif
  karma := karma + karmagain;
  var online := 0;
  if(!attacker.isA(POLCLASS_NPC))
    foreach char in EnumerateOnlineCharacters()
      if(char == attacker)
        online := 1;
        break;
      endif
    endforeach
    if(online == 1)
      SetObjProperty(attacker, "Karma", karma);
      SendGainMessage(attacker, "Karma", karmagain);
    else
      SetObjProperty(attacker, "ModKarma", kmod);
    endif
  else
    SetObjProperty(attacker, "Karma", karma);
  endif
  if(attacker.isA(POLCLASS_MOBILE))
    SetNotoTitle(attacker, karma, fame);
  endif
endfunction

function GetFameLevel(fame)
  var fmod := 0;
  if((fame <= 1249) && (fame >= 0))
    fmod := 1;
  elseif((fame <= 2499) && (fame >= 1250))
    fmod := 2;
  elseif((fame <= 4999) && (fame >= 2500))
    fmod := 3;
  elseif((fame <= 9999) && (fame >= 5000))
    fmod := 4;
  elseif(fame >= 10000)
    fmod := 5;
  endif
  return fmod;
endfunction

function GetKarmaLevel(karma)
  var kmod := 0;
  if(karma <= -10000)
    kmod := 1;
  elseif((karma <= -5000) && (karma >= -9999))
    kmod := 2;
  elseif((karma <= -2500) && (karma >= -4999))
    kmod := 3;
  elseif((karma <= -1250) && (karma >= -2499))
    kmod := 4;
  elseif((karma <=  -625) && (karma >= -1249))
    kmod := 5;
  elseif((karma <=   624) && (karma >=  -624))
    kmod := 6;
  elseif((karma <=  1249) && (karma >=   625))
    kmod := 7;
  elseif((karma <=  2499) && (karma >=  1250))
    kmod := 8;
  elseif((karma <=  4999) && (karma >=  2500))
    kmod := 9;
  elseif((karma <=  9999) && (karma >=  5000))
    kmod := 10;
  elseif(karma >= 10000)
    kmod := 11;
  endif
  return kmod;
endfunction

function SetNotoTitle(who, karma, fame)
  var kmod := GetKarmaLevel(karma);
  var fmod := GetFameLevel(fame);
  var newtitle := nototitles[ (kmod) ];
  newtitle := "The " + CStr(newtitle[fmod]) + " ";
  if(newtitle["None"])
    newtitle := "";
  endif
  if(fmod == 5)
    if(who.gender == 1)
      newtitle := newtitle + "Lady ";
    else
      newtitle := newtitle + "Lord ";
    endif
  endif
  if(newtitle != who.title_prefix)
    who.title_prefix := newtitle;
    SendSysMessage(who, "you are now known as " + newtitle + who.name);
  endif
endfunction

function SendGainMessage(who, type, amount)
  var msgtext := "You have ";
  if(amount < 0)
    msgtext := msgtext + "lost ";
    amount := Abs(amount);
  else
    msgtext := msgtext + "gained ";
  endif
  if(amount > 300)
    msgtext := msgtext + "a great amount of ";
  elseif(amount > 250)
    msgtext := msgtext + "alot of ";
  elseif(amount > 150)
    msgtext := msgtext + "a good amount of ";
  elseif(amount > 60)
    msgtext := msgtext + "some ";
  elseif(amount > 0)
    msgtext := msgtext + "a little ";
  else
    return 0;
  endif
  msgtext := msgtext + type + ".";
  SendSysMessage(who, msgtext);
endfunction

function RestoreMods(who)
  foreach thing in ListEquippedItems(who)
    if(GetObjProperty(thing, "Pid"))
      var holder := {};
      var gain := GetObjProperty(thing, "gain");
      if(!gain)
        gain := 5;
      endif
      var type := GetObjProperty(thing, "type");
      var tpe;
      case(type)
        "strength":     tpe := "str";
        "invisibility": tpe := "inv";
        "sight":        tpe := "vis";
        "protection":   tpe := "pro";
        "reflect":      tpe := "ref";
        "bless":        tpe := "bls";
      endcase
      holder.append(thing.serial);
      holder.append(tpe);
      holder.append(gain);
      SetObjProperty(thing, "equipped", who.serial);
      var parms := {who, thing};
      start_script(":combat:chargeUpkeep", parms);
      print("upkeep started");
    endif
  endforeach
endfunction