 #include <wiringPi.h>
 #include <time.h>
 #include "file_process.h"
 #include "pump_controller.h"
 #include "config_module.h"
 #include "camera_threads.h"
 #include "thread_director.h"

int main (void)
{
	// Step 1: Load settings and breadcrumbs
	//m_config_init(); // TODO: No config needed right now, but will be useful later
	init_log_file();
	init_pump_pins();
	
	// Step 2: Mark start in data log
	struct timespec start_time, end_time;	
	timespec_get(&start_time, TIME_UTC);
	record_start_data(start_time);

	// Step 4: Ping for internet access & Setup web API (new thread and will signal when done)
	// TODO: This can come later, but for now we'll use cron jobs and rsync to keep a FTP directory updated

	// Step 5: Run full floodbot process by starting necessary threads
	start_threaded_process();

	// Step 6: Save results to files that will be later sync'd
	timespec_get(&end_time, TIME_UTC);
	record_end_data(end_time);

	// Step 7: Close and safe shutdown
	close_log_file();
	
  return 0 ;
} 
