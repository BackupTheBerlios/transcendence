function eseguiverso(animal, who);

var verso;

case (animal.graphic)

 0xd8 : verso := 0x0079;  //mucca
 0xe7 : verso := 0x0079; //mucca2
 0xcf : verso := 0x00d7; //pecora

endcase


PlaySoundEffect(who, verso);

endfunction




