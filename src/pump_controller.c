#define _POSIX_C_SOURCE	199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include "file_process.h"
#include "pump_controller.h"

/// Init the wiringPi pin settings and set the pins to keep pumps off
void init_pump_pins(){

	wiringPiSetup();
	
	pinMode (PUMP_PIN, OUTPUT) ;
	pinMode (SIPHON_PIN, OUTPUT) ;

	digitalWrite (PUMP_PIN, HIGH);		// relay is active-low
	digitalWrite (SIPHON_PIN, HIGH);
}


/// Toggle the spray pump via relay a given number of cycles
/// with a predefined duty cycle and duration
void* run_spray_op(void* cycles_ptr){

	int const cycles = *((int*)cycles_ptr);
	
	struct timespec start_time, stop_time;
	timespec_get(&start_time, TIME_UTC);
			
	for (int i = 0; i<cycles;i++){

		digitalWrite (PUMP_PIN, LOW);
    	nanosleep((const struct timespec[]){{SPRAY_ON_SEC, 0}}, NULL);
		digitalWrite (PUMP_PIN, HIGH);
		
		printf("Spray cycle complete: %d of %d\n",(i+1),cycles);

		if (i < cycles-1){ nanosleep((const struct timespec[]){{SPRAY_OFF_SEC, 0}}, NULL); }
	}

	timespec_get(&stop_time, TIME_UTC);

	record_spray_data(start_time,stop_time);

	return NULL;
}


/// Toggle the siphon pump via relay a given number of cycles
/// with a predefined duty cycle and duration
void* run_siphon_op(void* cycles_ptr){
	
	int const cycles = *((int*)cycles_ptr);

	struct timespec start_time, stop_time;	
	timespec_get(&start_time, TIME_UTC);

	for (int i = 0; i<cycles;i++){

		digitalWrite (SIPHON_PIN, LOW);
		nanosleep((const struct timespec[]){{SPRAY_ON_SEC, 0}}, NULL);
		digitalWrite (SIPHON_PIN, HIGH);

		printf("Siphon cycle complete: %d of %d\n",(i+1),cycles);

		if (i < cycles-1){ nanosleep((const struct timespec[]){{SPRAY_OFF_SEC, 0}}, NULL); }
	}
			
	timespec_get(&stop_time, TIME_UTC);

	record_siphon_data(start_time,stop_time);
	
	return NULL;
}


/// Run the full water loop cycle
// NOTE: This is useless threading right now, but it will be refactored and matter later.
void exec_water_loop_threads(){

	pthread_t spray_thread, siphon_thread;
	
	// Spray water the defined amount of cycles to simulate a summer rain
	int cycles = SPRAY_LOOPS;
	pthread_create( &spray_thread, NULL, run_spray_op, &cycles);
	pthread_join(spray_thread, NULL);

	// Process the complicated & time-intensive soaking operation
	nanosleep((const struct timespec[]){{SOAK_SEC, 0}}, NULL);

	// Run the spihon op after we soak the roots and pull water out
	cycles = SIPHON_LOOPS;
	pthread_create( &siphon_thread, NULL, run_siphon_op, &cycles);
	pthread_join(siphon_thread, NULL);

}
