//////////////////
//
// NPC_Nerves.inc
// 
// Created: 07/09/2001 15:42
// Updated: 4/17/2003 5:45PM
//
// by Austin Heilman and TJ Houston
// http://www.tsse.net
//
/////////////////
//
// This include is used by the brain and by nerves
// to manage the various nerves that interract with
// the brain. This is like the "switch board" of the AI
//
////////////////

use uo;
use os;

// NPC Nerve Constants and functions.
include ":ai_brain:ai_include/NPC_Flags";

var g_nerves := dictionary;

//
// Reads in the #NerveInfo CProp off the npc.
// Returns a dictionary. Key is the nerve id name, the value
// is the PID of the script running for that nerve ID.
//
function LoadNerves(mobile)
	var g_nerves := GetObjProperty(mobile, "#NerveInfo");
	
	if ( g_nerves == error )
		g_nerves := dictionary;
	endif
	
	return g_nerves;
endfunction

//
// Saves the current nerve names running and their PIDs
//
function SaveNerves(mobile:=0)
	if ( !mobile )
		mobile := self();
	endif
	SetObjProperty(mobile, "#NerveInfo", g_nerves);
endfunction

//
// Starts a nerve script as nerve_name (id).
// Runs the script passed, and sends the data to
// the nerve. 
// * If the type of data is not an array, it
//   will be put into the first index of the data sent.
//   So this means, nerves should always expect an array
//   sent to them if StartNerve is used.
//
function StartNerve(nerve_name, nerve_script, data:=array)
	var process := GetNerve(nerve_name);
	if (process != error)
		//If the nerve is already running, dont start a new one
		//or the previous nerve's pid is overwritten and lost.
		return error;
	endif
	
	//Check if the data type is an array.
	//If it is not, put it in one.
	if ( lower(TypeOf(data)) != "array")
		data := array(data);
	endif
	//Add the nerve name to the array.
	data.insert(1, nerve_name);
	
	//Start the nerve script, and pass the data to it.
	process := start_script(nerve_script, data);
	if ( process.errortext )
		SysLog("g_nervescript ["+nerve_name+"]["+nerve_script+"] failed to start! ->"+process.errortext);
	else
		AddNerve(nerve_name, process);
	endif
	
	return process;
endfunction

//
// Returns a script reference for the nerve ID passed.
// Returns error if no nerves exist on the npc by that nerve name.
//
function GetNerve(nerve_name)
	if ( g_nerves.exists(nerve_name) )
		return GetProcess(g_nerves[nerve_name]);
	else
		var temp := error;
		temp.+errortext := "No nerve exists by the name " + nerve_name;
		return temp;
	endif
endfunction

//
// Adds the nerve and its pid to the NPC's NerveInfo dict.
//
function AddNerve(nerve_name, byref process)
	// Check if a nerve under that name is already running.
	KillNerve(nerve_name);
	g_nerves[nerve_name] := process.pid;
	
	SaveNerves();
endfunction

//
// Stops the script running for that nerve name.
// Removes the nerve name and info from the dictionary.
// Returns 1 if the nerve name existed and was stopped.
// Returns 0 if there was no nerve by that name.
//
function KillNerve(nerve_name)
	// Returns '1' if the nerve was found and stopped.
	if ( g_nerves.exists(nerve_name) )
		GetProcess(g_nerves[nerve_name]).kill();
		g_nerves.erase(nerve_name);
		
		SaveNerves();
		return 1;
	else
		return 0;
	endif
endfunction

//
// Stops all nerves running on the npc.
//
function StopNerves(stop_type:="")
	foreach key in (g_nerves.keys())
		if ( (stop_type == "sleep") && (CONTINUE_ON_SLEEP in GetFlags(me, key)) );
			//Do nothing.
		else
			KillNerve(key);
		endif
		sleepms(2);
	endforeach
	
	SaveNerves();
endfunction
