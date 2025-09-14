#include <stdint.h>
#include <stdbool.h>

void LedsInitDriver(uint16_t * puerto_inicial);
void LedsTurnOn(int led_number);
void LedsTurnOff(int led_number);
void LedsTurnAllOn(void);
void LedsTurnAllOff(void);
bool LedIsOn(int led_number);
