function checkmount(who)

  var mount := GetEquipmentByLayer(who, LAYER_MOUNT);
  var chck;
  if (!mount)
  chck := 0;
  else
  chck := 1;
  endif
  
  return chck;

endfunction



                 