 #include <wiringPi.h>
 #include <time.h>
 #include "file_process.h"
 #include "pump_controller.h"
 #include "config_module.h"

int main (void)
{
	// Step 1: Load settings and breadcrumbs
	m_config_init();
	
	// Step 2: Setup both files for logging (new thread and will signal when done)
	init_log_file();
	init_pump_pins();

	// Step 3: Init sensor and cameras

	// Step 4: Ping for internet access & Setup web API (new thread and will signal when done)
	
	// Step 5: Run water & sensor operations (new thread and will signal when done)
	exec_water_loop();

	// Step 6: Save results to cloud and files

	// Step 7: Close and safe shutdown
	close_log_file();

	
  return 0 ;
} 
