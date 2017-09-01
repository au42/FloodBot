#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <time.h>
#include <unistd.h>

#include "file_process.h"

FILE *log_file_pointer;
FILE *data_file_pointer;


bool init_log_file(){
	
	// Not already open?
	if (log_file_pointer != NULL || data_file_pointer != NULL){
		fprintf(stderr,"Can't init files while another is already open.\n");
		return false;
	}
	
	// Open files for use
	log_file_pointer = fopen(LOG_FILE_NAME,"a");
	data_file_pointer = fopen(DATA_FILE_NAME,"a");
	
	// Files opened ok?
	if ( log_file_pointer == NULL ) {
		fprintf(stderr,"Can't open the log file for writing - actions will not be logged!\n");
	} else {
		printf("Log file OK!\n");
	}

	if ( data_file_pointer == NULL ) {
		fprintf(stderr,"Can't open the data file for writing - data will not be logged!\n");
	} else {
		printf("Data file OK!\n");
	}

	return true;
}

bool close_log_file(){
	
	// File already closed?
	if (log_file_pointer == NULL || data_file_pointer == NULL) {
		fprintf(stderr,"Can't close an empty file handle.\n");
		return false;
	}

	fclose(log_file_pointer);
	fclose(data_file_pointer);	
	
	return true;
}


bool record_spray_data(struct timespec start_time,struct timespec stop_time) {

	if (data_file_pointer == NULL){	return false; }

	char data_str[128];
	char starttime_str[128];
	int t_seconds = (int)stop_time.tv_sec - (int)start_time.tv_sec;

	// Get the time for the file name
    time_t rawtime;
    struct tm *time_info;

	rawtime = start_time.tv_sec;
    time_info = localtime( &rawtime );

    strftime(starttime_str,80,"%x - %I:%M%p", time_info);

	snprintf(data_str,127,"%s,SPRAY,%i",starttime_str,t_seconds);

	fprintf(data_file_pointer,"%s\n",data_str);
	fflush(stdout);

	return true;
}

bool record_siphon_data(struct timespec start_time, struct timespec stop_time) {

	if (data_file_pointer == NULL){	return false; }

	char data_str[128];
	char starttime_str[128];
	int t_seconds = (int)stop_time.tv_sec - (int)start_time.tv_sec;

	// Get the time for the file name
    time_t rawtime;
    struct tm *time_info;

	rawtime = start_time.tv_sec;
    time_info = localtime( &rawtime );

    strftime(starttime_str,80,"%x - %I:%M%p", time_info);

	snprintf(data_str,127,"%s,SIPHON,%i",starttime_str,t_seconds);

	fprintf(data_file_pointer,"%s\n",data_str);
	fflush(stdout);

	return true;
	
}

bool record_start_data(struct timespec start_time) {

	if (data_file_pointer == NULL){	return false; }

	char data_str[128];
	char time_str[128];

	// Get the time for the file name
    time_t rawtime;
    struct tm *time_info;

	rawtime = start_time.tv_sec;
    time_info = localtime( &rawtime );

    strftime(time_str,80,"%x - %I:%M%p", time_info);

	snprintf(data_str,127,"%s,START",time_str);

	fprintf(data_file_pointer,"%s\n",data_str);
	fflush(stdout);

	return true;
}

bool record_end_data(struct timespec end_time) {

	if (data_file_pointer == NULL){	return false; }

	char data_str[128];
	char time_str[128];

	// Get the time for the file name
    time_t rawtime;
    struct tm *time_info;

	rawtime = end_time.tv_sec;
    time_info = localtime( &rawtime );

    strftime(time_str,80,"%x - %I:%M%p", time_info);
	snprintf(data_str,127,"%s,END",time_str);

	fprintf(data_file_pointer,"%s\n",data_str);
	fflush(stdout);

	return true;
}