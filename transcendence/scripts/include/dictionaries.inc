function GetIndexByKey(the_key, the_dictionary)
  var keys := the_dictionary.keys();
  var i;
  for(i := 1; i <= keys.size(); i := i + 1)
  if(the_key == keys[1])
  return i;
  endif
  endfor
endfunction

function GetValueByindex(indx, the_dictionary)
 var keys := the_dictionary.keys();
 var the_key := keys[indx];
 return dictionary[the_key];
endfunction

function GetKeyByindex(indx, the_dictionary)
 var keys := the_dictionary.keys();
 return keys[indx];
endfunction

