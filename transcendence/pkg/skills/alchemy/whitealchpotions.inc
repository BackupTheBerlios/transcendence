function make_tothealpot(who)

var totheal := SendDialogGump(who, layouti, datai);
                  if (totheal[0] == 101)
                  SendSysMessage(who, "You try to make potion");
                  var has_garlic := checkreagentamount(who, 0x0f84, 50);
                  var has_mandrake := checkreagentamount(who, 0x0f86, 50);
                   if (level < 10) 
                    var probability := RandomInt(19);
                     if ((has_garlic == 1) && (has_mandrake == 1)&& (is_bottle == 1))
                        if (probability < 3)
                          PlayObjectCenteredEffect(cauldron, 0x372a, 0x0a, 0x1e );
                          PlaySoundEffect(who, SFX_SPELL_TELEPORT );
                          SendSysMessage(who, "You created the potion!");
                          CreateItemInBackpack(who, 0xdc18, 1);
                          reagentconsume(who, 0x0f84, 50);
                          reagentconsume(who, 0x0f86, 50);
                          reagentconsume(who, 0x0f0e, 1);
                          SetObjProperty(who, "walchlvl", advlevel);
                        else
                          SendSysMessage(who, "You failed to make potion!");
                        endif
                     else
                        SendSysMessage(who, "You have no bottles or reagents!");
                     endif
                   endif
                  
                   if (level >= 10)
                        if ((has_garlic == 1) && (has_mandrake == 1)&& (is_bottle == 1))

                          PlayObjectCenteredEffect(cauldron, 0x372a, 0x0a, 0x1e );
                          PlaySoundEffect(who, SFX_SPELL_TELEPORT );
                          CreateItemInBackpack(who, 0xdc18, 1);
                          reagentconsume(who, 0x0f84, 50);
                          reagentconsume(who, 0x0f86, 50);
                          reagentconsume(who, 0x0f0e, 1);
                          SendSysMessage(who, "You created the potion!");
                        else
                          SendSysMessage(who, "You have no bottles or reagents!");
                         endif
                    endif
                endif
               
endfunction



function make_protect(who)
 var protect := SendDialogGump(who, layoutii, dataii);
                  if (protect[0] == 101)
                  SendSysMessage(who, "You try to make potion");
                  var has_garlic := checkreagentamount(who, 0x0f84, 50);
                  var has_ginseng := checkreagentamount(who, 0x0f85, 40);
                  var has_drakblood := checkreagentamount(who, 0x0f82, 1);
                   if ((level > 10) && (level < 20)) 
                    var probability := RandomInt(19);
                     if ((has_garlic == 1) && (has_ginseng == 1)&& (is_bottle == 1)&& (has_drakblood == 1))
                        if (probability < 3)
                          PlayObjectCenteredEffect(cauldron, 0x372a, 0x0a, 0x1e );
                          PlaySoundEffect(who, SFX_SPELL_TELEPORT );
                          SendSysMessage(who, "You created the potion!");
                          CreateItemInBackpack(who, 0xdc24, 1);
                          reagentconsume(who, 0x0f84, 50);
                          reagentconsume(who, 0x0f86, 40);
                          reagentconsume(who, 0x0f82, 1);
                          reagentconsume(who, 0x0f0e, 1);
                          SetObjProperty(who, "walchlvl", advlevel);
                        else
                          SendSysMessage(who, "You failed to make potion!");
                        endif
                     else
                        SendSysMessage(who, "You have no bottles or reagents!");
                     endif
                   endif
                  
                   if (level >= 20)
                        if ((has_garlic == 1) && (has_ginseng == 1)&& (is_bottle == 1) && (has_drakblood == 1))

                          PlayObjectCenteredEffect(cauldron, 0x372a, 0x0a, 0x1e );
                          PlaySoundEffect(who, SFX_SPELL_TELEPORT );
                          SendSysMessage(who, "You created the potion!");
                          CreateItemInBackpack(who, 0xdc24, 1);
                          reagentconsume(who, 0x0f84, 50);
                          reagentconsume(who, 0x0f86, 40);
                          reagentconsume(who, 0x0f82, 1);
                          reagentconsume(who, 0x0f0e, 1);
                        else
                          SendSysMessage(who, "You have no bottles or reagents!");
                         endif
                    endif
                  if (level < 10)
                    SendSysMessage(who, "You aren't enough able to create this potion!");
                  endif
               
                endif
endfunction                   