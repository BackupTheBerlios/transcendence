// Daemon Background Processes by ArT-iX
use datafile;

function RegisterDaemon(processname, proc_id)

  var proc_register := OpenDataFile(":DaemonProcesses:Processes");
  
  if(!proc_register)
   print("NO PROCESSES DATA FILE!!");
   return 0;
  endif 
  
  var elem := proc_register.findElement(processname);
  
  if(!elem)
   elem := proc_register.createElement(processname);
   elem.setProp("PID", proc_id);
  else
   elem.setProp("PID", proc_id);
  endif 



endfunction

function GetDaemonPID(processname)

  var proc_register := OpenDataFile(":DaemonProcesses:Processes");
  var P_ID;
  
  if(!proc_register)
   print("NO PROCESSES DATA FILE!!");
   return 0;
  endif 
  
  var elem := proc_register.findElement(processname);
  
  if(!elem)
   print("NO REGISTERED DAEMON!!");
   return 0;
  else
   return elem.getProp("PID");
  endif 



endfunction


