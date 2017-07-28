#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <time.h>
#include <unistd.h>

#include "file_process.h"

FILE *log_file_pointer;


bool init_log_file(){
	
	if (log_file_pointer != NULL){
		fprintf(stderr,"Can't open a file while another is already open.\n");
		return false;
	}
	
	log_file_pointer = fopen("/home/pi/Documents/bonsai_log.csv","a+");
	if (log_file_pointer == NULL) {
		fprintf(stderr,"Can't open the file for writing.\n");
		return false;
	}	
	return true;
}

bool close_log_file(){
	
	append_message_to_log("Shutdown Detected...");
		
	if (log_file_pointer == NULL) {
		fprintf(stderr,"Can't close an empty file handle.\n");
		return false;
	}
	
	fclose(log_file_pointer);	
	
	return true;
}


void append_message_to_log(char* str){	
	
	if (log_file_pointer == NULL){
		fprintf(stderr,"I couldn't write to a null file handle.\n");
		return;
	}
	
	char* tag = "MSG,";
	fwrite(tag, strlen(tag), 1, log_file_pointer);
	fwrite(str, strlen(str), 1, log_file_pointer);
	insert_timestamp_return_to_log();
	
	fflush(log_file_pointer);
}


void append_error_to_log(char* str){	
	
	if (log_file_pointer == NULL){
		fprintf(stderr,"I couldn't write to a null file handle.\n");
		return;
	}
	
	char* tag = "ERR,";
	fwrite(tag, strlen(tag), 1, log_file_pointer);
	fwrite(str, strlen(str), 1, log_file_pointer);
	insert_timestamp_return_to_log();
	
	fflush(log_file_pointer);
}


void append_pump_duration_log(int start_seconds, int stop_seconds){

	if (log_file_pointer == NULL){
		fprintf(stderr,"I couldn't write to a null file handle.\n");
		return;
	}

	fprintf(log_file_pointer,"PUMP,%i,%i", start_seconds, stop_seconds);
	insert_timestamp_return_to_log();
	
	fflush(log_file_pointer);
}


void append_siphon_duration_log(int start_seconds, int stop_seconds){

	if (log_file_pointer == NULL){
		fprintf(stderr,"I couldn't write to a null file handle.\n");
		return;
	}

	fprintf(log_file_pointer,"SIPHON,%i,%i", start_seconds, stop_seconds);
	insert_timestamp_return_to_log();
	
	fflush(log_file_pointer);
}


void insert_timestamp_return_to_log(){
	
	struct timespec gettime_now;
	timespec_get(&gettime_now, TIME_UTC);
	
	fprintf(log_file_pointer,", %i UTC\r\n", (int)(gettime_now.tv_sec));
	
	fflush(log_file_pointer);
}

