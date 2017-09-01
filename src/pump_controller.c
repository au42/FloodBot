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

/// Init the wiringPi pin settings and set the pins to keep pumps off
void init_pump_pins(){

	wiringPiSetup();
	
	pinMode (PUMP_PIN, OUTPUT) ;
	pinMode (SIPHON_PIN, OUTPUT) ;

	digitalWrite (PUMP_PIN, HIGH);		// relay is active-low
	digitalWrite (SIPHON_PIN, HIGH);
}


