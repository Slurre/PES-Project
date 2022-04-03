#include "boards.h"
#include "nrf_delay.h"

// taken from nRF5 SDK blinky example
int main(void) {

    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    /* Toggle LEDs. */
    while (true)
    {
        for (int i = 0; i < LEDS_NUMBER; i++)
        {
            bsp_board_led_invert(i);
            nrf_delay_ms(500);
        }
    }
}
