#define PUMP_PIN 0
#define SIPHON_PIN 1

#define	CYCLE_LOOPS 5
#define SIPHON_LOOPS 10

#define SPRAY_ON_SEC 8
#define SPRAY_OFF_SEC 16

#define SIPHON_ON_SEC 6
#define SIPHON_OFF_SEC 18

#define SOAK_SEC 5

extern void init_pump_pins();
extern void exec_water_core();
