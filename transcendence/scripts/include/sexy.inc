function Piss(who)
 var clothes := {};
 
 var cloth := GetEquipmentByLayer( who, 4 );
 if (cloth)
  clothes.append(cloth);
 endif
 
 cloth := GetEquipmentByLayer( who, 0x17 );
 if (cloth)
  clothes.append(cloth);
 endif
 
 cloth := GetEquipmentByLayer( who, 0x18 );
 if (cloth)
  clothes.append(cloth);
 endif
 print(cstr(clothes));
 if(who.graphic == 401)
  PlayCharAnim(who, 112);
  sleep(1);
  
  foreach cl in clothes
   print(cl.desc);
   MoveItemToContainer( cl, who.backpack );
   
  endforeach
  sleep(2);
  print("piss anm..");
  PlayCharAnim( who, 136);
 endif	
 sleep(2);
 var pee := CreateItemAtLocation( who.x, who.y, who.z, 0x122b, who.realm);
 pee.desc := "pee";
 pee.color := 55;
 var i;
 for (i := 1; i <= 10; i := i + 1)
  PlaySoundEffect( who, 577 );
  sleep(1);
 endfor
 
 foreach cl in clothes
   equipitem(who, cl);
  endforeach
endfunction