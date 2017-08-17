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
		printf("Log file OK!");
	}

	if ( data_file_pointer == NULL ) {
		fprintf(stderr,"Can't open the data file for writing - data will not be logged!\n");
	} else {
		printf("Data file OK!");
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


