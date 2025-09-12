#include "led.h"

#define ALL_LEDS_OFF  0x0000;
#define FIRST_BIT     1
#define LED_TO_OFFSET 1

static uint16_t * puerto;

static uint16_t LedToMask(int led_number) {
    return FIRST_BIT << (led_number - LED_TO_OFFSET);
}

void LedsInitDriver(uint16_t * puerto_inicial) {
    puerto = puerto_inicial;
    LedsTurnAllOff();
}

void LedsTurnOn(int led_number) {
    *puerto |= LedToMask(led_number);
}

void LedsTurnOff(int led_number) {
    *puerto &= ~LedToMask(led_number);
}

void LedsTurnAllOn(void) {
    *puerto = ~ALL_LEDS_OFF;
}

void LedsTurnAllOff(void) {
    *puerto = ALL_LEDS_OFF;
}
