#include "led.h"

static uint16_t *puerto;

void LedsInitDriver(uint16_t *puerto_inicial)
{
    puerto = puerto_inicial;
    *puerto_inicial = 0x0000;
}

void LedsTurnOn(int led_number)
{

    *puerto = 1 << 2;
}