#define PUMP_PIN 0
#define SIPHON_PIN 1

#define	SPRAY_LOOPS 5
#define SIPHON_LOOPS 10

#define SPRAY_ON_SEC 8
#define SPRAY_OFF_SEC 16

#define SIPHON_ON_SEC 4
#define SIPHON_OFF_SEC 10

#define SOAK_SEC 5

/// @brief Initialize pump pins
/// @return True if opening files was successful
extern void init_pump_pins();

/// @brief Run the full water cycle for watering
/// @return True if opening files was successful
extern void exec_water_loop_threads();
