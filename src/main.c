 #include <wiringPi.h>
 #include <time.h>
 #include "file_process.h"
 #include "pump_controller.h"
 

int main (void)
{
	init_log_file();
	
	init_pump_pins();
	
	exec_water_loop();

	close_log_file();
	
  return 0 ;
} 
