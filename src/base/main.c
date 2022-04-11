#include "boards.h"
#include "nrf_delay.h"

// taken from nRF5 SDK blinky example
int main(void) {

    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    /* Toggle LED0. */
    while (true)
    {
        bsp_board_led_invert(0);
        nrf_delay_ms(500);
    }
}