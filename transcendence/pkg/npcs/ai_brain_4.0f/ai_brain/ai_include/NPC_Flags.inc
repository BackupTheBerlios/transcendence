//
// NPC_Flags.inc
//
// Flags constants that can be assigned to nerves.
// Functions for setting and reading nerve flags.
//
// *Note: This is an extension of NPC_Nerves.inc.
//  As such, it is included inside of that include.
//
// Created: 4/17/2003 6:01PM
// Updated: 4/17/2003 6:01PM
//
// by Austin Heilman
// http://www.tsse.net
//
////////////////////////////
//
// NPC Flag Constants
//
////////////////////////////

use uo;
use os;

const CONTINUE_ON_SLEEP			:= 0x1;
// 0x2
// 0x4
// 0x8
// 0x10
// 0x20

// Global variable to store flag settings.
var g_flags := dictionary;

////////////////////////////
//
// NPC Flag Functions
//
////////////////////////////

//
// Loads the CProp called FlagInfo on the npc and puts
// it into g_flags.
//
function LoadFlags(mobile)
	g_flags := GetObjProperty(mobile, "#FlagInfo");
	if ( g_flags == error )
		g_flags := dictionary;
	endif
	
	return g_flags;
endfunction

//
// Saves g_flags as a CProp called FlagInfo on the mobile.
//
function SaveFlags(mobile)
	SetObjProperty(mobile, "#FlagInfo", g_flags);
endfunction

//
// Returns an array of flags for nerve_name.
// Returns an empty array if no flags are present.
//
function GetFlags(mobile, nerve_name)
	var flags := GetObjProperty(mobile, "#FlagInfo");
	if ( !flags.exists(nerve_name) )
		flags := array;
	else
		flags := flags[nerve_name];
	endif

	return flags;
endfunction

//
// Adds a flag to the flags array on the npc
// under the nerve_name key.
// Returns 1 if the flag was added. Returns
// error if the flag could not be added.
//
function AddFlag(mobile, nerve_name, flag)
	var cur_flags := GetFlags(mobile, nerve_name);
	if ( flag in cur_flags )
		var temp := error;
		temp.+errortext := "Error: Flag already exists in FlagSettings["+nerve_name+"]";
		return temp;
	else
		cur_flags.append(flag);
		g_flags[nerve_name] := cur_flags;
		SaveFlags(mobile);
	endif
endfunction

// 
// Removes the flag passed from the flags for the nerve.
//
function RemoveFlag(mobile, nerve_name, flag)
	var cur_flags := GetFlags(mobile, nerve_name);
	
	foreach value in cur_flags
		if ( flag == value )
			cur_flags.erase(_value_iter);
		endif
		sleepms(2);
	endforeach
	
	g_flags[nerve_name] := cur_flags;
	SaveFlags(mobile);
endfunction
