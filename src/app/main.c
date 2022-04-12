#include "boards.h"
#include "nrf_delay.h"

int app_main(void) {
    /* Toggle LED1. */
    bsp_board_led_invert(1);
    return 0;
}
