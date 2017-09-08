#define _POSIX_C_SOURCE	199309L
#include <time.h>
#include <pthread.h>
#include "pump_threads.h"
#include "camera_threads.h"
#include "thread_director.h"

/// Run the full water loop cycle
// NOTE: This is useless threading right now, but it will be refactored and matter later.
void start_threaded_process(){

	pthread_t spray_thread, siphon_thread, camera_thread;
    int spray_cycles = SPRAY_LOOPS;
    int siphon_cycles = SIPHON_LOOPS;

	// Create threads for spraying the water and taking a picture while doing it; then waiting until spray is done.
	pthread_create(&spray_thread, NULL, run_spray_op, &spray_cycles);
    pthread_create(&camera_thread, NULL, launch_camera_exec, NULL);
    pthread_join(spray_thread, NULL);

	// Process the complicated soaking operation
	nanosleep((const struct timespec[]){{SOAK_SEC, 0}}, NULL);

	// Create threads for siphoning water from plant basin; then wait until this completes before returning.
	pthread_create(&siphon_thread, NULL, run_siphon_op, &siphon_cycles);
	pthread_join(siphon_thread, NULL);

}