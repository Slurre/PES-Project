#include "boards.h"
#include "nrf_delay.h"
#include "app.h"


void blink_led(void) {
    /* Toggle LED1. */
    bsp_board_led_invert(1);
}

int app_main(void) {
    blink_led();
    return 0;
}
