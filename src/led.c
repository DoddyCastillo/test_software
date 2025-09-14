#include "led.h"
#include "errores.h"
#include <stdbool.h>

#define ALL_LEDS_OFF  0x0000
#define FIRST_BIT     1
#define LED_TO_OFFSET 1

static uint16_t * puerto;

static uint16_t LedToMask(int led_number) {
    return FIRST_BIT << (led_number - LED_TO_OFFSET);
}

static bool IsLedValid(int led) {
    bool result = led >= 1 && led <= 16;
    if (!result) {
        Alerta("El led no es valido");
    }
    return result;
}

void LedsInitDriver(uint16_t * puerto_inicial) {
    puerto = puerto_inicial;
    LedsTurnAllOff();
}

void LedsTurnOn(int led_number) {
    if (!IsLedValid(led_number)) {
        return;
    }
    *puerto |= LedToMask(led_number);
}

void LedsTurnOff(int led_number) {
    if (!IsLedValid(led_number)) {
        return;
    }
    *puerto &= ~LedToMask(led_number);
}

void LedsTurnAllOn(void) {
    *puerto = ~ALL_LEDS_OFF;
}

void LedsTurnAllOff(void) {
    *puerto = ALL_LEDS_OFF;
}

bool LedIsOn(int led_number) {
    if (!IsLedValid(led_number)) {
        return false;
    }
    return (*puerto & LedToMask(led_number)) != 0;
}
