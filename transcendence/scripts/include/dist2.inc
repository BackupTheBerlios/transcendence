/*
 *  dist( obj1, obj2 )
 *      - returns the largest of the x-distance and y-distance 
 *        between two objects.
 */

use uo;

function dist( obj1, obj2 )
    return Distance( obj1, obj2 );

            /* implements:
                while (obj1.container)
                    obj1 := obj1.container;
                endwhile
    
                while (obj2.container)
                    obj2 := obj2.container;
                endwhile

                local xd := obj1.x - obj2.x;
                local yd := obj1.y - obj2.y;
                if (xd < 0)
                    xd := -xd;
                endif
                if (yd < 0)
                    yd := -yd;
                endif
                if (xd > yd)
                    return xd;
                else
                    return yd;
                endif
            */
endfunction

function coordist( x1, y1, x2, y2 )

   var xd := x1 - x2;
   var yd := y1 - y2;
   if (xd < 0)
      xd := -xd;
   endif
   if (yd < 0)
      yd := -yd;
   endif
   if (xd > yd)
      return xd;
   else
     return yd;
   endif
endfunction

function getrelativepos(x1, y1, x2, y2)
//ritorna la posizione dell'oggetto (x2, y2) rispetto al "centro" di rotazione (x1, y1)

   if (x1 == x2)
  if (y1 > y2)
     return 0;
  elseif (y1 < y2)
     return 4;
  endif
 
elseif (x1 > x2)
  if (y1 < y2)
    return 5;
  elseif (y1 == y2)
    return 6;
  else
    return 7;
  endif

else
  if (y1 < y2)
    return 3;
  elseif (y1 == y2)
    return 2;
  else
    return 1;
  endif

endif

endfunction

function gofortarget(whox, whoy, trgx, trgy,trg, speed)
//fa giungere l'animazione a bersaglio e poi esegue un eventuale danno
while (coordist(whox, whoy, trgx, trgy)!=0)
 var correct:= 1;
 case (getrelativepos(whox, whoy, trgx, trgy))
  0: whoy := whoy -1;
  1: whox := whox +1;whoy := whoy-1;correct:= 1.5;
  2: whox := whox+1;
  3: whox := whox+1; whoy := whoy +1;correct:= 1.5;
  4: whoy := whoy +1;
  5: whox := whox-1; whoy:= whoy +1;correct:= 1.5;
  6: whox := whox-1;
  7: whox := whox -1; whoy := whoy -1;correct:= 1.5;
 endcase
trgx := trg.x;
trgy := trg.y;
 
sleepms(speed*correct);
endwhile

endfunction