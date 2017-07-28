 #include <wiringPi.h>
 #include <time.h>
 #include "file_process.h"
 #include "pump_controller.h"
 

int main (void)
{
	// init log file 
	init_log_file();
	
	//init pumps
	init_pump_pins();
	
	exec_water_core();

	close_log_file();
	
  return 0 ;
} 