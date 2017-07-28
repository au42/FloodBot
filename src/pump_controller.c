#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "file_process.h"
#include "pump_controller.h"
#include <wiringPi.h>


void init_pump_pins(){
	
	append_message_to_log("RESET! Initializing pumps.");
	wiringPiSetup();
		
	pinMode (PUMP_PIN, OUTPUT) ;
	pinMode (SIPHON_PIN, OUTPUT) ;
	digitalWrite (PUMP_PIN, HIGH);		// relay is active-low
	digitalWrite (SIPHON_PIN, HIGH);

}

void run_spray_op(int cycles){
	struct timespec start_time, stop_time;
		
	// save start time
	timespec_get(&start_time, TIME_UTC);
		
	// run the pump cycles
	append_message_to_log("Pump Cycle");
	
	for (int i = 0; i<cycles;i++){
		digitalWrite (PUMP_PIN, LOW);
		sleep(SPRAY_ON_SEC);
		digitalWrite (PUMP_PIN, HIGH);
		if (i < cycles-1){ sleep(SPRAY_OFF_SEC); }
	}
		
	// save end time
	timespec_get(&stop_time, TIME_UTC);
	
	// log pump op
	append_pump_duration_log(start_time.tv_sec,stop_time.tv_sec);
}

void run_siphon_op(int cycles){
	struct timespec start_time, stop_time;
		
	// save start time
	timespec_get(&start_time, TIME_UTC);
	
	// run siphon pump cycles
	append_message_to_log("Siphon Cycle");
	for (int i = 0; i<cycles;i++){
		digitalWrite (SIPHON_PIN, LOW);
		sleep(SIPHON_ON_SEC);
		digitalWrite (SIPHON_PIN, HIGH);
		if (i < cycles-1){ sleep(SIPHON_OFF_SEC); }
	}
			
	timespec_get(&stop_time, TIME_UTC);
	
	append_siphon_duration_log(start_time.tv_sec,stop_time.tv_sec);
}

void exec_water_core(){
	
	append_message_to_log("START!");
		
	run_spray_op(CYCLE_LOOPS);

	// wait for soaking and draining
	sleep(SOAK_SEC);	

	run_siphon_op(SIPHON_LOOPS);

	append_message_to_log("END!");
}
