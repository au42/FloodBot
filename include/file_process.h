#include <string.h>
#include <stdbool.h>
#include <time.h>

#define SHOW_ON_CONSOLE

extern bool init_log_file();
extern bool close_log_file();
extern void append_message_to_log(char* str);
extern void append_error_to_log(char* str);
void append_pump_duration_log(int start_seconds, int stop_seconds);
void append_siphon_duration_log(int start_seconds, int stop_seconds);
void insert_timestamp_return_to_log();
extern int seconds_since_last_pump();