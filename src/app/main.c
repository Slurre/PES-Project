#include "boards.h"
#include "nrf_delay.h"
#include "app.h"


void blink_led(void) {
    /* Toggle LED1. */
    bsp_board_led_invert(1);
}

void blink_leds(void) {
    /* Toggle all LEDs. */
    for (uint8_t i=0; i<4; i++)
        bsp_board_led_invert(i);
}

void blink_leds_delay(void) {
    /* Toggle all LEDs. */
    bsp_board_leds_on();
    nrf_delay_ms(500);
    bsp_board_leds_off();
}

void blink_leds_static(void) {
    /* Toggle all LEDs. */
    static uint8_t state = 0;
    state = !state;
    state ? bsp_board_leds_on() : bsp_board_leds_off();
}

void blink_leds_static_two(void) {
    /* Toggle all LEDs. */
    static uint8_t state = 0;
    static uint8_t next_state = 1;
    state = next_state;
    state ? bsp_board_leds_on() : bsp_board_leds_off();
    next_state = !state;
}

int app_main(void) {
    blink_leds_static_two();
    return 0;
}
