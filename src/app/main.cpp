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

int app_main(void) {
    blink_leds();
    return 0;
}
