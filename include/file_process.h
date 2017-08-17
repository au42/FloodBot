#include <string.h>
#include <stdbool.h>
#include <time.h>

#define LOG_FILE_NAME "floodbot_log.txt"
#define DATA_FILE_NAME "floodbot_data.csv"

/// @brief Open the log files as defined for writing
/// @return True if opening files was successful
extern bool init_log_file();

/// @brief Close the log files
/// @return True if closing files was successful
extern bool close_log_file();
