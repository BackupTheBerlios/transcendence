function drawobject(who, serial, graphic, x, y, z, facing, color)
      var packethexstringpart1 := "78";
      var packethexstringpart2 := ConvertIntToHex(serial, 4) + ConvertIntToHex(graphic, 2);
      packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(x, 2);
      packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(y, 2);
      packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(z, 1);
      packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(facing, 1);
      packethexstringpart2 := packethexstringpart2 + ConvertIntToHex(color, 2);
      packethexstringpart2 := packethexstringpart2 +"000000000000";
      var fullpackethexstringlength := (len(packethexstringpart1) + len(packethexstringpart2)) / 2 + 2;
      var fullpackethexstring := packethexstringpart1 + ConvertIntToHex(fullpackethexstringlength, 2) + packethexstringpart2;
      SendPacket(who, fullpackethexstring);
endfunction



function ConvertIntToHex(astring, alength)
  astring := Hex(astring);
  astring := CStr(astring);
  if (astring["0x"])
    astring := astring[3, len(astring)];
  endif
  if (len(astring) > alength * 2)
    return;
  endif
  while (len(astring) < alength * 2)
    astring := "0"+ astring;
  endwhile   
  return astring;
endfunction