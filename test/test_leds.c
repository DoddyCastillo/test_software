/*
prender un led y apagarlo en ambos extremos
prender y apagar todos los leds
prender algunos leds mas de una vez y verificar que sigue prendido
apagar algunos leds mas de una vez y verificar que siguen apagados
prender algunos leds, despues prender todos y comprobar que todos los leds quedan prendidos
prender todos, apagar algunos, apagar todos y comprobar que todos los leds quedan apagados
consultar el estado de un led encendido y comprobar que es correcto
consultar el estado de un led apagado y comprobar que es correcto
*/

#include "unity.h"
#include "led.h"
#include "mock_errores.h"

uint16_t puerto_inicial;

void setUp(void) {
    LedsInitDriver(&puerto_inicial);
}

void tearDown(void) {
}

// iniciar el driver y revisar que todos los leds esten apagados
void test_al_iniciar_todos_los_leds_estan_apagados(void) {
    uint16_t puerto_inicial = 0xFFFF;

    LedsInitDriver(&puerto_inicial);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_inicial);
}

// prender un led y verificar que no cambia el resto
void test_prender_un_led_verificiar_no_cambie_los_demas(void) {
    LedsTurnOn(3);
    TEST_ASSERT_EQUAL_HEX16(1 << 2, puerto_inicial);
}

// prender un led cualquiera y apagarlo
void test_prender_un_led_cualquiera_y_apagarlo(void) {
    LedsTurnOn(5);
    LedsTurnOff(5);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_inicial);
}

// prender mas de un led, apagar uno y verificar que el resto siguen sin cambios
void test_prender_mas_de_un_led_apagar_uno_y_verificar_que_el_resto_sigue_sin_cambios(void) {
    LedsTurnOn(3);
    LedsTurnOn(5);
    LedsTurnOff(5);
    TEST_ASSERT_EQUAL_HEX16(1 << 2, puerto_inicial);
}

// tratar de manipular un led fuera de rango y comprobar que se genera un error
void test_tratar_de_manipular_un_led_fuera_de_rango_y_comprobar_que_se_genera_un_error(void) {

    // RegistrarMensaje_Expect(ALERTA, "LedsTurnOn", 0, "El led no es valido");
    // RegistrarMensaje_IgnoreArg_linea();
    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOn(0);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_inicial);

    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOn(17);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_inicial);
}

void test_tratar_de_apagar_leds_fuera_de_rango_y_comprobar_que_se_genera_un_error(void) {
    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOff(0);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_inicial);

    RegistrarMensaje_ExpectAnyArgs();
    LedsTurnOff(17);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_inicial);
}

// prender todos los leds y verificar
void test_prender_todos_los_leds(void) {

    LedsTurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puerto_inicial);
}

// apagar todos los leds y verificar
void test_apagar_todos_los_leds(void) {
    LedsTurnAllOn();
    LedsTurnAllOff();
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_inicial);
}

// consultar el estado de un led encendido y comprobar que es correcto
void test_consultar_el_estado_de_un_led_encendido_y_comprobar_que_es_correcto(void) {
    LedsTurnOn(8);
    LedIsOn(8);
    TEST_ASSERT_EQUAL_HEX16(1 << 7, puerto_inicial);
}

// consultar el estado de un led apagado y comprobar que es correcto
void test_consultar_el_estado_de_un_led_apagado_y_comprobar_que_es_correcto(void) {
    LedsTurnOff(8);
    LedIsOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_inicial);
}
