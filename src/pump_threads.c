#define _POSIX_C_SOURCE	199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include "file_process.h"
#include "pump_controller.h"
#include "pump_threads.h"

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