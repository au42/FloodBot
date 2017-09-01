#define _POSIX_C_SOURCE	199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include "camera_threads.h"


void* launch_camera_exec(void * args) {

    // Get the time for the file name
    time_t rawtime;
    struct tm *time_info;
    char camera_command[80];
    time( &rawtime );
    time_info = localtime( &rawtime );

    // Build the camera command using 'raspistill'
    strftime(camera_command,80,"raspistill -o %Y-%m-%d[%H:%M:%S]-capture.jpg", time_info);

    // Run the command after the preset delay
    printf("Camera Ready...");
    fflush(stdout);

    nanosleep((const struct timespec[]){{CAMERA_DELAY, 0}}, NULL);

    printf("Taking Picture...");
    fflush(stdout);

    //TODO: Find a way to detect if the latest pic was created successfuly (though a rsync directory could work too)
    system(camera_command);
    printf("done\n");
    
    return 0;
}