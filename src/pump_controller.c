#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>

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

/// @param cycles The number of cycles to run the siphon pump
/// Toggle the spray pump via relay a given number of cycles
/// with a predefined duty cycle and duration
void* run_spray_op(void* cycles_ptr){

	int cycles = (int)cycles_ptr;
	
	struct timespec start_time, stop_time;
	timespec_get(&start_time, TIME_UTC);
			
	for (int i = 0; i<cycles;i++){

		digitalWrite (PUMP_PIN, LOW);
		sleep(SPRAY_ON_SEC);
		digitalWrite (PUMP_PIN, HIGH);

		if (i < cycles-1){ sleep(SPRAY_OFF_SEC); }
	}

	timespec_get(&stop_time, TIME_UTC);

	return NULL;
}

/// @param cycles The number of cycles to run the siphon pump
/// Toggle the siphon pump via relay a given number of cycles
/// with a predefined duty cycle and duration
void* run_siphon_op(void* cycles_ptr){
	
	struct timespec start_time, stop_time;
		
	timespec_get(&start_time, TIME_UTC);
	
	int cycles = (int) cycles_ptr;
	for (int i = 0; i<cycles;i++){

		digitalWrite (SIPHON_PIN, LOW);
		sleep(SIPHON_ON_SEC);
		digitalWrite (SIPHON_PIN, HIGH);

		if (i < cycles-1){ sleep(SIPHON_OFF_SEC); }
	}
			
	timespec_get(&stop_time, TIME_UTC);
	
	return NULL;
}

/// Run the full water loop cycle
void exec_water_loop(){
	
	// Spray water the defined amount of cycles
	int cycles = CYCLE_LOOPS;
	run_spray_op(&cycles);

	// Complicated soak operation
	sleep(SOAK_SEC);

	// Run the spihon op after we let the bonsai soak
	cycles = SIPHON_LOOPS;
	run_siphon_op(&cycles);

}
